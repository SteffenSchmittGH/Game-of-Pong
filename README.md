# Game-of-Pong
Embedded OS and RTE based implementation of the Game of Pong on an Embedded Target (Psoc).
This implementation has the benefits in ...
1. **Decoupling**: Application logic and Driver logic is seperated. Statemachine doesnt directly access display Hardware.
2. **Asynchronous Updates**: Display rendering doesn't block the FSM or the communication logic.
3. **Modular Design**: It is easy to extend the Input Events, Statemachine logic or add/swap Hardware.

## RTE Design
![rte_design](https://github.com/user-attachments/assets/b52d2bf2-cfad-4071-b22a-b264809ac010)
### Design Considerations ###
In Order to prevent Race Conditions and Data Loss (regarding the Signals), the safest method is to implement the whole
Game/System into a single Task. With this approach there are no Data Races (e.g. Statemachine reads while Joystick is writing).
Since Sender and Receiver Runnables are executed sequentially, the implementation can be safe, when designed carefully.
**Event Extension**
Since it could be possible to add some events like a information via UART, which Game to play, the input Task could be seperate from the 
Control Task. 
**Realtime Tasks**
Futher more the HMI Display is not a Realtime application. So here it could make sense to put higher priority on the Input Task and the Control Task(Statemachine).
**Priorities**
Implemented are 3 different Tasks. The questions for the priority can be solved with the following considerations:
1. Receiver has higher Priority than Sender: Receiver reads outdated data. A fix could be a mailbox to buffer the data.
2. Sender and Receiver same Prio or Sender has higher Prio: Race Condition. (Overwrite of Signals) A fix could be an Eventqueue.
**Mailbox**
The mailbox works as a ringbuffer which holds variable datatypes, typedef structs included. With this it is possible to have no race conditions.
Attention has to be payed to the fillLevel and the PUT and GET functions of the Mailbox. Here Mutexes are used to make the Buffer threadsafe.

## Statemachine
![pong_statemachine](https://github.com/user-attachments/assets/be111dd6-a01f-4e09-9e00-ab2f5efd9f30)
## UML
![pong_uml](https://github.com/user-attachments/assets/2e3ad71d-5371-46c0-bd21-b503443f52a4)


