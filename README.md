# DSQuestion
Solution to a data structure course question


Question: A car wash has a maximum service capacity of k cars, where one is being washed and k − 1 are in line. Each wash takes 3 minutes. When a new customer arrives, the system either serves them immediately if it is completely free, puts them in line, or rejects them if there are already k cars being serviced. Write a program in the C language that receives as input integers n ≥ 1 and k ≥ 0 and a binary vector V of size n, for example, 001011100111000111, where the i-th bit from left to right is "1" if a new customer arrives at the i-th minute, and "0" if no new customer arrives at the i-th minute. The program should calculate how many cars have been washed by the system until the n-th minute. Use a queue implemented with dynamic allocation to represent the system at each passing minute, remembering that the queue can hold a maximum of k cars.
