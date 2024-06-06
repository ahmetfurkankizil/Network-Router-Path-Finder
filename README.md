# Network-Router-Path-Finder

## Overview

The Network Router Path Finder is a system designed to manage and analyze the connections between routers within a network. This project provides functionality to determine the minimum number of routers that a packet must traverse to reach its destination and to compute the diameter of the network graph. The diameter is defined as the longest of the shortest paths between any two routers in the network.

## Features

1. **Shortest Path Calculation:** Determines the minimum number of routers a packet needs to visit to reach its destination, and lists the IDs of these routers in order.
2. **Graph Diameter Calculation:** Computes the diameter of the network, which is the longest of the shortest paths between any two routers.

## Input File Format

The input file provides the details about the routers and their connections. The structure of the file is as follows:

- The first line contains the number of routers.
- Each subsequent line contains the information for a specific router in the format:
  ```
  <router id> <degree> <neighbor id 1> <neighbor id 2> ... <neighbor id N>
  ```
  - **Router ID:** Unique identifier for the router.
  - **Degree:** Number of direct connections (neighbors) this router has.
  - **Neighbor ID:** IDs of the routers directly connected to this router.

### Example Input File

```
9
0 3 1 2 3
1 2 0 4
2 3 0 5 6
3 2 0 7
4 1 1
5 1 2
6 1 2
7 1 3
8 0
```

## Command Line Arguments

The program accepts three command line arguments:

1. **Input File Name:** The name of the file containing the router map.
2. **Source Router:** The ID of the router where the packet starts.
3. **Destination Router:** The ID of the router where the packet needs to be delivered.

## Usage

Compile the program to create an executable named `pathFinder`. Run the executable with the required command line arguments.

```bash
./pathFinder <input_file> <source_router> <destination_router>
```

### Example Command

```bash
./pathFinder network_map.txt 0 4
```

## Output

The program outputs two main pieces of information:

1. **Minimum Number of Routers:** The minimum number of routers a packet must visit to travel from the source router to the destination router, along with the sequence of router IDs in the visiting order.
2. **Network Diameter:** The diameter of the network, which is the longest of the shortest paths between any two routers.

### Example Output

```
Minimum number of routers to visit: 3
Path: 0 -> 1 -> 4

Diameter of the network: 4
```

## Implementation Details

### Graph Representation

The network is represented as an undirected graph using adjacency lists. Each router is a node, and each direct connection (cable) is an edge.

### Algorithms Used

- **Breadth-First Search (BFS):** Used to compute the shortest path between the source and destination routers.

## Code Structure

- **main.cpp:** Contains the main function and handles command line arguments.
- **graph.hpp:** Header file defining the Graph class and its methods.
- **graph.cpp:** Implementation of the Graph class methods.

### Graph Class Methods

- `Graph(const std::string &filename)`: Constructor that reads the input file and initializes the graph.
- `std::vector<int> shortestPath(int src, int dest)`: Returns the shortest path from `src` to `dest`.
- `int computeDiameter()`: Computes and returns the diameter of the graph.

## Build Instructions

To compile the program, use a C++ compiler such as `g++`.

```bash
g++ -o pathFinder main.cpp graph.cpp
```

## Conclusion

The Network Router Path Finder provides a robust solution for managing and analyzing network connections. By efficiently calculating the shortest path and the network diameter, it ensures optimal routing and helps in understanding the network topology better.
