# Game-of-Pong (in Progress)

# Game-of-Pong 

Embedded OS and RTE based implementation of the Game of Pong on an Embedded Target (Psoc).
This implementation has the benefits in ...
1. **Decoupling**: Application logic and Driver logic is seperated. Statemachine doesnt directly access display Hardware.
2. **Asynchronous Updates**: Display rendering doesn't block the FSM or the communication logic.
3. **Modular Design**: It is easy to extend the Input Events, Statemachine logic or add/swap Hardware.

## RTE Design

<img width="1017" height="697" alt="grafik" src="https://github.com/user-attachments/assets/bb499764-fe2a-4bbd-88bb-4c556067f5eb" />



### General ###
The input task, executes the runnables joystick and button. Those use the joystick driver and button driver respectively.
Their task is to transform the driver data into an event for the statemachine. 

The Statemachine is implemented inside the control task. Its task is to Configure the global Object OO_PONG_MAIN.

The HMI task is triggered periodically every 250 ms. Its task is to read out the OO_PONG_MAIN and writes the data to the display.

All Runnables are implemented in one software component.

### Design Considerations ###
In Order to prevent Race Conditions and Data Loss (regarding the Signals), the safest method is to implement the whole
Game/System into a single Task. With this approach there are no Data Races (e.g. Statemachine reads while Joystick is writing).
Since Sender and Receiver Runnables are executed sequentially, the implementation can be safe, when designed carefully.

#### Event Extension

Since it could be possible to add some events like a information via UART, which game to play, the input task could be seperate from the 
Control task. 

#### Realtime Tasks

Futhermore the HMI display is not a Realtime application. So here it could make sense to put higher priority on the Input Task and the Control task(Statemachine).

#### Priorities (Design not yet finished)

Implemented are 3 different Tasks. The questions for the priority can be solved with the following considerations:

1. **Cyclic Control Task**

   1.1 **Receiver has higher Priority than Sender:**

   Receiver reads outdated data. A fix could be a mailbox to buffer the data.
   
   1.2 **Sender and Receiver same Prio or Sender has higher Prio:**

   Race Condition. (Overwrite of Signals) A fix could be an Eventqueue.
   
3. **Event Driven Control Task**

   2.1. **Receiver has higher Priority than Sender:**

   This Configuration works in this szenario. Even if the input runnables would be not both in one task, there would be no races.
   
   2.2 **Sender and Receiver same Prio or Sender has higher Prio:**

   Button Signal would overwrite joystick signal always.

#### Mailbox

The mailbox works as a ringbuffer which holds variable datatypes, typedef structs included. With this it is possible to have no race conditions.
Attention has to be payed to the fillLevel and the PUT and GET functions of the Mailbox. Here Mutexes are used to make the Buffer threadsafe.
The benefits of the Mailbox is the flexibility for futher extensions. Priority decisions are not fixed and will have no impact the correct behaviour of the system.

**Conclusion**

1. One cyclic input task for both button and joystick runnable. Eventsignal is output signal for both runnables. 
2. Control task listens onDataUpdate of Eventsignal. No Events lost, since execution of Statemachine is faster than 10ms.
3. Mailbox between input and control task, in case of extension of the input. Maybe another input task is added in future.

4. **No Mailbox needed between control task and output task. Three different signalobjects would do the job.**

## Statemachine (needs to be redesigned: one menue for all the games)

<img width="830" height="612" alt="grafik" src="https://github.com/user-attachments/assets/2c54cbd7-d191-4327-a2d6-e1ba19c42c66" />

**Brief**

The Task of the Statemachine is to receive input Events and considering the current state, configure the Signalobjects, read out by the hmi runnable.

**Core Concepts**

| Concept | Description   |
| --------| ------------------------------------------------------------------ |
| State   | A condition the system can be in (e.g., Stopped, Playing)          |
| Event   | External or internal input triggering change (e.g., button press)  |
| Action  | What the system does during a transition (e.g., play song)         |
| Guard   | A condition that must be true for a transition to occur            |

The transition order is **State Exit** -> **Transition Action** -> **State Entry**.

## Deeper View into Statemachine implementation Strategies:

**Switch Case:**

The easiest implementation strategy is the switch case pattern. Here each "case" stands for an state. The "if" and "else if" checks the events. Actions are called during transition and "state" is updated during transition. 

The benefits here are:
   1. simple to debug
   2. fast and flexible
   3. good for flat and small statemachines
The drawbacks are:
   1. Becomes hard to maintain as project growes

**Full Transition Table:**

Structure:

‘‘‘typedef struct {
  STATE_State_t fromState;
  STATE_State_t toState;
  STATE_Event_t event;
  STATE_GuardPtr_t guard;
  STATE_ActionPtr_t action;
} STATE_stateTransition_t;‘‘‘

An table of the type STATE_stateTransition_t describes the whole Statemachine. Here the full table needs to be implemented. A function processEvent will parse the table, check if the incoming event fits the table, checks for guards and actions. This function also updates the current state of the statemachine. A global variable STATE_State_t currentState should save the state.

Benefits of the Full Transition Table method:
   1. Good readability
   2. Flexible (any number of actions, guards)
      
Drawbacks:
   1. Slow, since every event scans the entire table
   2. Bad memory footprint if many transitions

**Design Concept 2: Explicit Transition Table**

Similar to full Transition Table but instead of parsing the whole table, an index is calculated (state * event) to access the transition. Since the index calculation relies of the whole implementation of the state/event combinations, the full transition table needs to be stored.

Benefits of the Explicit Transition Table method:
   1. Fast Lookup
   2. Good for many transitions
      
Drawbacks:
   1. Limited to one guard/action per transition
   2. Waste space for unused transitions

**Design Concept 3: Two-Layer Transition Table (Used)**

Each state has its own transition list. (inner tables)
An outer table maps states to their transition sets. 
The outer Table is small, so an iteration through the whole table is sensible.

Example: Game of Pong (statemachine.h)

‘‘‘
const STATE_outerTransition_Container_t GAMES_Container_Transitions [] = { 

/*      FROM STATE         INNER TABLE          SIZE  (inner)*/    

};
‘‘‘

const STATE_innerTransition_Container_t STATE_GAMES_PONG_Transitions[] = { 

/*    EVENT      TO_STATE    GUARD    TRANSITIONACTION */

};

const STATE_innerTransition_Container_t STATE_GAMES_MENUE_Transitions[] = { 

/*    EVENT      TO_STATE    GUARD    TRANSITIONACTION */

};
            TRANSITIONACTION*/
const STATE_innerTransition_Container_t STATE_GAMES_PAUSE_Transitions[] = { 

/*    EVENT      TO_STATE    GUARD    TRANSITIONACTION */

};

Benefits: 
   1. Good performance
   2. Very flexible and scalable
   3. Best memory efficiency

Drawbacks:
   1. More complex implementation


**Statemachines Design Improvements**

Instead of introducing extra flags like "pong_isSet", consider to represent it as a new state in the statemachine. In most cases, if the flag alters how the system behaves, it should be a state. 

Instead of using a global bitmask, use enum events. A bitmask, makes it possible to store many events in a single variable. This is a compact way of implementing, since it fastens the set and clear. It also enables combining events for multiple sources. (e.g., SetEvent(ev_button1 | ev_timeout).
But the processing can be more complex, since it has to be identified which is tha active bit.

**Hirarchical State Machines(Used)**

Always try to flatten hierachical state machines into simple flat statemachines.

Active Object:

An object with its own statemachine, responding to events. Multiple instances share FSM logic but hold private state. FSM state is not modified externally only via events.

Divide and Conquer:

1. Break down complex FSM into smaller, independent FSMs
2. Each widget becomes and active object
3. The container coordinates them and handles shared actions


**Challenges in Active Object FSM Design**

Summary: The finite statemachines are implemented like objects in C. There are multiple instances of those "Classes". Each instance has it's own state and configuration. Events are dispatched to these FSM's independently.

Challenges: 
   1. No inheritance in C: If two active objects have slightly different properties, a config struct has to be implemented, in order to distinguish between the objects. Each FSM instance receives a pointer to it's config. So logic remains same but acts slightly different. A better approach in this case (Pong) would have been to implement a config struct instead of putting all the data into the Signal Objects.

...
