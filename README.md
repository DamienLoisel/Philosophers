# Philosophers

## Description

The **Philosophers** project at 42 involves simulating a scenario where philosophers are seated at a table, each trying to eat while sharing forks with their neighbors. The challenge is to ensure that all philosophers can eat without causing deadlock or starvation. This project tests your understanding of concurrency, synchronization, and process management.

## Features

- **Dining Philosophers Simulation**: Implement a simulation where philosophers alternate between thinking and eating.
- **Concurrency Control**: Use mutexes to manage access shared resources (forks) and avoid deadlock and starvation.
- **Philosopher Behavior**: Each philosopher needs to wait for both forks to be available before eating and must release them after eating.
- **Configuration Options**: Allow configuring the number of philosophers, the time they spend thinking, eating, sleeping and the numbers of time they can eat before they're full(optional).

## Examples

- **A philosopher dies**:
  
![image](https://github.com/user-attachments/assets/ae532d2e-e224-4ffd-8606-109f5a071304)

- **No one dies because they can each eat 2 times**:

![image](https://github.com/user-attachments/assets/b13c604b-b3b1-4811-9e73-66142039cf9e)


