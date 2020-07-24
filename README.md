# ECS152 - Project 1 
Made by Georgia Nigri and Near Wu

## Description:
This project a discrete event simulator that studies the behavior of an IEE 802.x based Network. 

## Files:
### main.cpp:
It implements the simulator (Initialization, Processing an Arrival Event and Procession a Departure Event) and it implements the Queue that acts as the buffer.
### Event.cpp
It creates the Event structure.
### GEL.cpp
It creates the GEL (Global Event List) class that stores in increase order of time theEvents in a linked list. The class also contains the insert and remove functions that can add and remove Events from the list.  
### packet.cpp
It creates the the packet structure.

## Installation:
The code can be installed by compiling the main.cpp file.

## Usage:
we change the values of mu, lambda and MAXBUFFER on main (lines 12-14) to simulate systems.
```cpp
double mu = 1; // service rate
double lambda = 0.8; // rate
const int MAXBUFFER = 20; //can change the size; infinite if -1
```
The expected output will be:
```
drop number: 0
utilization: 0.810632
mean queue length: 4.259810
```

