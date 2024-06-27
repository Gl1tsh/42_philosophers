# PHILOSOPHER
<p align="center">
  <img width="1256" alt="philosopher_run" src="https://github.com/Gl1tsh/42_philosophers/assets/69108289/65cde525-a657-4818-9e48-037123029c97">
</p>

The Philosopher project at 42 school is a classic problem in concurrent programming known as the "Dining Philosophers Problem." The objective of the project is to implement a simulation of this problem using threads and mutexes in C.

This project introduces students to several key concepts in concurrent programming, including:

- *Threads*: Students must create multiple threads, each representing a philosopher, to simulate the concurrent execution of the dining philosophers problem.

- *Mutexes*: Mutexes are used to control access to shared resources, such as forks in this case, to prevent race conditions and ensure thread safety.

- *Deadlock Avoidance*: Students must implement a solution to avoid deadlock, a situation where each philosopher holds one fork and is waiting for the other, resulting in a deadlock.

- *Resource Allocation*: The project requires efficient allocation and management of resources, such as forks, to ensure that each philosopher can eat when they are able to do so.

- *Concurrency Control*: Proper synchronization mechanisms, such as mutex locks and conditional variables, are used to control the execution flow of threads and prevent conflicts in accessing shared resources.

- *Simulation*: The project involves simulating the behavior of philosophers, including their actions of thinking, picking up forks, eating, and releasing forks.

In summary, the Philosopher project provides students with practical experience in concurrent programming and synchronization techniques using threads and mutexes in C. It allows them to explore the complexities of concurrent systems and understand the challenges involved in designing and implementing concurrent algorithms.

# How to launch :

## First step
- You need to clone the repository with the following command in the terminal: 

```git clone https://github.com/Gl1tsh/42_philosophers.git```

- Now you need to enter the folder of the clone you've made

## Start the program

- Run the command: ```make```
- Once compiled, launch it with the next commands :

```./philo <number of philo> <time_to_die> time_to_eat> <time_to_sleep>```

- Exemple, you can copy past this : ```./philo 4 410 200 200```

- If you want to limit the number of times they eat, you can also use the following command at the end. :

```./philo <number of philo> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>```
- Exemple, you can copy past this : ```./philo 5 800 200 200 7```

The following commands allow you to test the program with the death of a philosopher and see how the program reacts.
The logic behind this is that if the fork rotation is not fast enough in relation to the time between meals, there will inevitably be deaths from starvation.
- Exemple, you can copy past this : ```./philo 4 310 200 100```
