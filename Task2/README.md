## Task2
An assignment on Process Scheduling. 


### Implemented by:
[@AhmedEssamDakrory]( https://github.com/AhmedEssamDakrory )
[@karashily]( https://github.com/karashily )

### Prerequisites

* g++
```sh
apt-get install g++
```
* python
```sh
add-apt-repository ppa:jonathonf/python-3.6
apt-get install python3.6
```
### Usage

1. Build the c++ file using g++ by typing:
```sh
g++ task2.cpp -o task2.out
```
2. Run the program
```sh
./task2
```
3. It will ask you to:
```sh
   1.Enter the input file name (input1.txt and input2.txt are two valid inputs feel free to use them).
   (input file format):
      first line contains a number n which is the number of processes.
      then each of the next n lines contains 3 integers ( arriving time , burst time and priority) respectively. 
   2.Choose one of the implemented scheduling algorithms to run.
   3.Specify the “Context Switching” time.
   4.Specify the “Time Quantum” in case of choosing RoundRobin.
```
4. Then run the python file to plot the timing diagram.
```sh
python plot.py
```

### Output
1. A visual graph that shows the generatedschedule
2. some statistics(turn-around time and waiting time for each process ... etc) in the statistics.txt file.
