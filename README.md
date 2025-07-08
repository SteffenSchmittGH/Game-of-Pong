# Game-of-Pong
Embedded OS and RTE based implementation of the Game of Pong on an Embedded Target (Psoc).
This implementation has the benefits in ...
1. **Decoupling**: Application logic and Driver logic is seperated. Statemachine doesnt directly access display Hardware.
2. **Asynchronous Updates**: Display rendering doesn't block the FSM or the communication logic.
3. **Modular Design**: It is easy to extend the Input Events, Statemachine logic or add/swap Hardware.

## RTE Design
![rte_design](https://github.com/user-attachments/assets/b52d2bf2-cfad-4071-b22a-b264809ac010)
## Statemachine
![pong_statemachine](https://github.com/user-attachments/assets/be111dd6-a01f-4e09-9e00-ab2f5efd9f30)
## UML
![pong_uml](https://github.com/user-attachments/assets/2e3ad71d-5371-46c0-bd21-b503443f52a4)


