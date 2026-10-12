
# Multistage Graph Using Dynamic Programming

## Aim
To implement a multistage graph algorithm in C++ to find the minimum-cost path from a source node in Stage 0 to a destination node in the final stage.

## Description
A multistage graph is a directed graph whose vertices are divided into ordered stages. Edges connect nodes across stages. Dynamic programming is used to calculate the minimum remaining cost from each node to the final stage.

This implementation also supports live edge-cost updates and recalculates the optimal costs and paths after an update.

## Features
- Accepts the number of stages and nodes in each stage.
- Accepts directed edges and their costs.
- Validates node IDs and rejects negative edge costs.
- Calculates minimum costs using dynamic programming.
- Reconstructs an optimal path from a Stage-0 node.
- Supports live edge-cost updates using a multiplier.
- Displays final minimum costs and the final optimal path.

## Algorithm
1. Read the number of stages and the number of nodes in each stage.
2. Assign node IDs to stages in order, starting from node 0.
3. Read the directed edges and their costs.
4. Initialize the minimum cost of every node in the final stage to zero.
5. Process the earlier stages in reverse order.
6. For each node, calculate the minimum of `edge cost + minimum cost of the destination node`.
7. Store the next node to reconstruct the optimal path.
8. Apply any live edge-cost updates and recalculate the minimum costs.
9. Display the final results and optimal path.

## Sample Input
The sample input is provided in `input.txt`.

It defines 3 stages, 6 nodes, 8 edges, and one live edge-cost update.

## Sample Output
The program output is saved in `output.txt`.

For the supplied test case, the initial minimum costs are:
- Node 0: 5.00
- Node 1: 3.00

After updating the cost of edge `2 -> 4` with multiplier `2`, the final minimum costs are:
- Node 0: 7.00
- Node 1: 3.00

The final optimal path from node 0 is `0 -> 3 -> 4`, with total cost `7.00`.

## Time Complexity
For one dynamic programming calculation, the time complexity is `O(V + E)`, where `V` is the number of vertices and `E` is the number of edges, assuming the graph follows the multistage ordering.

Each live update triggers another dynamic programming calculation.

## Space Complexity
The space complexity is `O(V + E)` for the adjacency list, minimum-cost array, next-node array, and stage information.

## Requirements
- C++ compiler supporting C++17 or later
- GCC / MinGW-w64 or another compatible compiler

## Compile and Run

### Windows PowerShell
```powershell
g++ -std=c++17 multistage_graph.cpp -o multistage_graph.exe
.\multistage_graph.exe
```

### Generate output.txt from the sample input
```powershell
.\multistage_graph.exe < input.txt > output.txt
```

## Files
- `multistage_graph.cpp` — C++ implementation
- `input.txt` — sample test input
- `output.txt` — saved program output
- `README.md` — project documentation

## Author
Sanika Patil
