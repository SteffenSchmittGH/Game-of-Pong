# Game-of-Pong 
Embedded OS and RTE based implementation of the Game of Pong on an Embedded Target (Psoc).
This implementation has the benefits in ...
1. **Decoupling**: Application logic and Driver logic is seperated. Statemachine doesnt directly access display Hardware.
2. **Asynchronous Updates**: Display rendering doesn't block the FSM or the communication logic.
3. **Modular Design**: It is easy to extend the Input Events, Statemachine logic or add/swap Hardware.

## RTE Design

![rte_design](https://github.com/user-attachments/assets/b52d2bf2-cfad-4071-b22a-b264809ac010)

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

![pong_statemachine](https://github.com/user-attachments/assets/be111dd6-a01f-4e09-9e00-ab2f5efd9f30)

The Task of the Statemachine is to receive input Events and considering the current state, configure the Signalobjects, read out by the hmi runnable.


## UML

![pong_uml](https://github.com/user-attachments/assets/2e3ad71d-5371-46c0-bd21-b503443f52a4)

This UML describes the Datastructure of the Pong Objects in pong_games.h. This object is read by the HMI output task, which updates the tft display.


