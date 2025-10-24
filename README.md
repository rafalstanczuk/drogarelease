# Path Finding Algorithm - Droga Release

## Overview

This C++ application implements a **greedy path-finding algorithm** that navigates through a 2D matrix by always moving to the neighboring cell with the highest value. The algorithm simulates a "path" that starts from a user-defined position and continues until no more valid moves are available.

## Algorithm Analysis

### Core Algorithm: Greedy Maximum Neighbor Selection

The main algorithm follows these steps:

1. **Matrix Initialization**: Creates an m×n matrix with random values (0-999)
2. **Neighbor Mapping**: Establishes 4-directional connectivity (up, right, down, left)
3. **Greedy Navigation**: At each step, moves to the unvisited neighbor with the highest value
4. **Termination**: Stops when no valid neighbors remain

### Key Components

#### 1. Element Class
```cpp
class Element {
    int near[4];        // Neighbor indices: [up, right, down, left]
    bool zdeptane;      // Visited flag
    int wartosc;        // Cell value
    int id;             // Unique identifier
}
```

#### 2. Matrix Class (Macierz)
- **Grid Construction**: Builds 2D matrix with proper neighbor relationships
- **Boundary Handling**: Special logic for corners and edges
- **Visualization**: Multiple display modes (values, IDs, visited status)

#### 3. Path Finding Algorithm
```cpp
int znajdz_max_sasiada(vector<Element> *elementy) {
    // 1. Collect all unvisited neighbors
    // 2. Sort by value (ascending)
    // 3. Return ID of highest value neighbor
}
```

### Algorithm Complexity

- **Time Complexity**: O(k × log(4)) = O(k) where k is path length
  - Each step: O(4) to check neighbors + O(4 log(4)) to sort = O(1)
  - Total: O(k) where k ≤ m×n
- **Space Complexity**: O(m×n) for matrix storage
- **Path Length**: Maximum m×n steps (visits each cell at most once)

### Algorithm Characteristics

#### Strengths:
- **Simple Implementation**: Easy to understand and debug
- **Deterministic**: Same input always produces same path
- **Memory Efficient**: O(1) additional space per step
- **Visual Feedback**: Real-time path visualization

#### Limitations:
- **Greedy Nature**: May not find optimal paths
- **Local Optimization**: No global path planning
- **No Backtracking**: Cannot recover from poor local choices

### Execution Flow

1. **Input Phase**:
   - Matrix dimensions (m, n)
   - Starting position (i₀, j₀)

2. **Initialization Phase**:
   - Generate random matrix
   - Mark starting position as visited
   - Display initial state

3. **Main Loop**:
   ```
   while (valid_neighbors_exist) {
       find_maximum_neighbor()
       move_to_neighbor()
       mark_as_visited()
       display_progress()
   }
   ```

4. **Output Phase**:
   - Final path visualization
   - Results saved to `wyniki.txt`

## Sample Execution

The algorithm was tested with a 10×12 matrix starting at position (2,4):

### Path Sequence:
```
Start: 777 → 835 → 887 → 631 → 517 → 942 → 743 → 977 → 729 → 826 → 890 → 706 → 296 → 492 → 691 → 334 → 556 → 927 → 34 → 168 → 392 → 814 → 686 → 552 → 839 → 785 → 827 → 711 → 25 → 428 → 411 → 657 → 582 → 841 → 472 → 653
```

### Key Observations:
- **Path Length**: 36 steps
- **Value Range**: 25 to 977
- **Termination**: No more valid neighbors
- **Coverage**: Visited approximately 30% of matrix

## Technical Implementation

### Data Structures:
- **Vector<Element>**: Dynamic array for matrix elements
- **Map<pair<int,int>, int>**: Coordinate-to-index mapping
- **IW Class**: Helper for neighbor value sorting

### Memory Management:
- Dynamic allocation for matrix
- Automatic cleanup via destructors
- File I/O for result persistence

### Visualization Features:
- **Border Detection**: 'B' for border cells, 'C' for center cells
- **Value Display**: 5-column formatted output
- **Progress Tracking**: Real-time visited status
- **Step-by-step Logging**: Complete execution trace

## Usage

### Compilation:
```bash
g++ -o droga main.cpp
```

### Execution:
```bash
./droga
```

### Input Format:
```
Matrix dimensions: m n
Starting position: i_0 j_0
```

### Output:
- Console display with real-time updates
- `wyniki.txt` file with complete execution log

## Applications

This algorithm could be adapted for:
- **Game AI**: Simple pathfinding in grid-based games
- **Resource Collection**: Gathering items in order of value
- **Optimization Problems**: Local search heuristics
- **Educational Purposes**: Understanding greedy algorithms

## Limitations and Future Improvements

### Current Limitations:
1. **No Global Optimization**: Pure greedy approach
2. **No Obstacle Avoidance**: Assumes all cells are accessible
3. **Fixed Movement Pattern**: Only 4-directional movement
4. **No Weighted Paths**: Values don't represent movement costs

### Potential Enhancements:
1. **A* Algorithm**: Add heuristic for better pathfinding
2. **Backtracking**: Allow path revision
3. **Multiple Objectives**: Balance value vs. distance
4. **Dynamic Weights**: Time-dependent value changes
5. **Parallel Processing**: Multi-threaded neighbor evaluation

## Conclusion

This implementation demonstrates a classic greedy algorithm for pathfinding in a 2D grid. While simple and efficient, it serves as an excellent foundation for understanding more complex pathfinding algorithms and optimization problems. The visual feedback and step-by-step execution make it particularly valuable for educational purposes.

---

**Created**: January 17, 2011  
**Language**: C++  
**License**: Educational/Research Use
