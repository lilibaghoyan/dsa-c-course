# Data Structures in C — Graphs, Traversals, and Shortest Path Algorithms

This lecture covers **graph representations**, **traversal algorithms** (DFS & BFS), **shortest path algorithms** (Dijkstra, Bellman-Ford), and **minimum spanning trees** with detailed implementations and complexity analysis.

---

## Topics Covered

### 1. Graph Fundamentals

#### Concept

A **graph** G = (V, E) consists of:
* **V**: Set of vertices (nodes)
* **E**: Set of edges (connections between vertices)

**Types of Graphs:**

1. **Directed vs Undirected**
   * **Directed (Digraph)**: Edges have direction (A → B)
   * **Undirected**: Edges are bidirectional (A ↔ B)

2. **Weighted vs Unweighted**
   * **Weighted**: Edges have costs/weights
   * **Unweighted**: All edges have equal weight (or weight = 1)

3. **Other Types**
   * **Cyclic vs Acyclic**: Contains cycles or not
   * **Connected vs Disconnected**: All vertices reachable or not
   * **Dense vs Sparse**: Many edges vs few edges

**Terminology:**
* **Degree**: Number of edges connected to a vertex
* **Path**: Sequence of vertices connected by edges
* **Cycle**: Path that starts and ends at the same vertex
* **Connected Component**: Maximal set of connected vertices

**References**
* [Graph Data Structure (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/graph-data-structure-and-algorithms/)
* [Introduction to Graphs (Programiz)](https://www.programiz.com/dsa/graph)

---

### 2. Graph Representations

#### A. Adjacency Matrix

A 2D array where `matrix[i][j] = 1` if there's an edge from vertex i to vertex j.

**Implementation:**

```c
#define MAX_VERTICES 100

struct Graph {
    int num_vertices;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
};

struct Graph* create_graph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->num_vertices = vertices;
    
    // Initialize matrix to 0
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graph->adj_matrix[i][j] = 0;
    
    return graph;
}

void add_edge(struct Graph* graph, int src, int dest, int weight) {
    graph->adj_matrix[src][dest] = weight;
    // For undirected graph: graph->adj_matrix[dest][src] = weight;
}
```

**For Weighted Graphs:**
```c
// Store weight instead of 1
// Use 0 or INT_MAX for no edge
graph->adj_matrix[src][dest] = weight;
```

**Trade-offs:**
✅ O(1) edge lookup
✅ Simple to implement
✅ Good for dense graphs
❌ O(V²) space (wasteful for sparse graphs)
❌ O(V²) to iterate all edges

---

#### B. Adjacency List

An array of linked lists. Each vertex has a list of its neighbors.

**Implementation:**

```c
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct Graph {
    int num_vertices;
    struct Node** adj_lists;  // Array of linked lists
};

struct Graph* create_graph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->num_vertices = vertices;
    graph->adj_lists = malloc(vertices * sizeof(struct Node*));
    
    for (int i = 0; i < vertices; i++)
        graph->adj_lists[i] = NULL;
    
    return graph;
}

void add_edge(struct Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->vertex = dest;
    new_node->weight = weight;
    new_node->next = graph->adj_lists[src];
    graph->adj_lists[src] = new_node;
    
    // For undirected graph, add reverse edge
    new_node = malloc(sizeof(struct Node));
    new_node->vertex = src;
    new_node->weight = weight;
    new_node->next = graph->adj_lists[dest];
    graph->adj_lists[dest] = new_node;
}
```

**Trade-offs:**
✅ O(V + E) space (efficient for sparse graphs)
✅ O(degree(v)) to iterate neighbors
✅ Industry standard for most applications
❌ O(degree(v)) edge lookup
❌ Slightly more complex

**References**
* [Graph Representations (GeeksforGeeks)](https://www.geeksforgeeks.org/graph-and-its-representations/)
* [Adjacency List vs Matrix](https://www.geeksforgeeks.org/comparison-between-adjacency-list-and-adjacency-matrix-representation-of-graph/)

---

### 3. Depth-First Search (DFS)

#### Concept

**DFS** explores as far as possible along each branch before backtracking. Uses a **stack** (or recursion).

**Algorithm:**
1. Start at a vertex
2. Mark it as visited
3. Recursively visit all unvisited neighbors
4. Backtrack when no unvisited neighbors remain

#### Implementation (Recursive)

```c
void dfs_util(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    struct Node* temp = graph->adj_lists[vertex];
    while (temp != NULL) {
        int adj_vertex = temp->vertex;
        if (!visited[adj_vertex])
            dfs_util(graph, adj_vertex, visited);
        temp = temp->next;
    }
}

void dfs(struct Graph* graph, int start_vertex) {
    int visited[MAX_VERTICES] = {0};
    dfs_util(graph, start_vertex, visited);
}
```

#### Implementation (Iterative with Stack)

```c
void dfs_iterative(struct Graph* graph, int start_vertex) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES], top = -1;
    
    stack[++top] = start_vertex;
    
    while (top >= 0) {
        int vertex = stack[top--];
        
        if (visited[vertex]) continue;
        
        visited[vertex] = 1;
        printf("%d ", vertex);
        
        struct Node* temp = graph->adj_lists[vertex];
        while (temp != NULL) {
            if (!visited[temp->vertex])
                stack[++top] = temp->vertex;
            temp = temp->next;
        }
    }
}
```

#### Applications

* **Cycle Detection**: Detect cycles in graphs
* **Topological Sorting**: Order tasks with dependencies
* **Connected Components**: Find all connected subgraphs
* **Path Finding**: Find if path exists between two vertices
* **Maze Solving**: Explore all possible paths

**Complexity:**
* Time: O(V + E) — visits each vertex and edge once
* Space: O(V) — recursion stack or visited array

**References**
* [DFS Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/)
* [DFS Visualization](https://visualgo.net/en/dfsbfs)
* [DFS Applications](https://www.geeksforgeeks.org/applications-of-depth-first-search/)

---

### 4. Breadth-First Search (BFS)

#### Concept

**BFS** explores all neighbors at the current depth before moving to the next level. Uses a **queue**.

**Algorithm:**
1. Start at a vertex, mark as visited, enqueue it
2. While queue not empty:
   * Dequeue a vertex
   * Visit all unvisited neighbors
   * Mark them visited and enqueue them

#### Implementation

```c
void bfs(struct Graph* graph, int start_vertex) {
    int visited[MAX_VERTICES] = {0};
    int queue[MAX_VERTICES], front = 0, rear = -1;
    
    visited[start_vertex] = 1;
    queue[++rear] = start_vertex;
    
    while (front <= rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);
        
        struct Node* temp = graph->adj_lists[vertex];
        while (temp != NULL) {
            int adj_vertex = temp->vertex;
            if (!visited[adj_vertex]) {
                visited[adj_vertex] = 1;
                queue[++rear] = adj_vertex;
            }
            temp = temp->next;
        }
    }
}
```

#### Applications

* **Shortest Path** (unweighted graphs): BFS finds shortest path
* **Level Order Traversal**: Process nodes level by level
* **Web Crawling**: Explore web pages by links
* **Social Networks**: Find friends within N degrees
* **GPS Navigation**: Find nearest locations

**Complexity:**
* Time: O(V + E)
* Space: O(V) — queue and visited array

**References**
* [BFS Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/)
* [BFS vs DFS](https://www.geeksforgeeks.org/difference-between-bfs-and-dfs/)
* [BFS Shortest Path](https://www.geeksforgeeks.org/shortest-path-unweighted-graph/)

---

### 5. DFS vs BFS Comparison

| Aspect | DFS | BFS |
|--------|-----|-----|
| Data Structure | Stack (recursion) | Queue |
| Memory | O(h) — height | O(w) — width |
| Path Found | Not necessarily shortest | Shortest (unweighted) |
| Use Case | Cycle detection, topological sort | Shortest path, level order |
| Implementation | Simpler (recursive) | Requires queue |

**When to Use:**
* **DFS**: Finding any path, detecting cycles, topological sorting, solving puzzles
* **BFS**: Finding shortest path, nearest neighbor, level-based processing

---

### 6. Dijkstra's Algorithm

#### Concept

**Dijkstra's algorithm** finds the shortest path from a source vertex to all other vertices in a **weighted graph with non-negative weights**.

**Algorithm:**
1. Initialize distances: source = 0, all others = ∞
2. Use a priority queue (min-heap) to process vertices
3. For current vertex, update distances to all neighbors
4. Mark vertex as processed
5. Repeat until all vertices processed

#### Implementation

```c
#define INF 999999

struct MinHeapNode {
    int vertex;
    int distance;
};

struct MinHeap {
    int size;
    int capacity;
    int* pos;  // Position of vertices in heap
    struct MinHeapNode** array;
};

// Helper: Create min heap
struct MinHeap* create_min_heap(int capacity) {
    struct MinHeap* heap = malloc(sizeof(struct MinHeap));
    heap->pos = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = malloc(capacity * sizeof(struct MinHeapNode*));
    return heap;
}

// Helper: Swap two nodes
void swap_nodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Helper: Heapify at index
void min_heapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    
    if (left < heap->size && 
        heap->array[left]->distance < heap->array[smallest]->distance)
        smallest = left;
    
    if (right < heap->size && 
        heap->array[right]->distance < heap->array[smallest]->distance)
        smallest = right;
    
    if (smallest != idx) {
        // Update positions
        struct MinHeapNode* smallest_node = heap->array[smallest];
        struct MinHeapNode* idx_node = heap->array[idx];
        heap->pos[smallest_node->vertex] = idx;
        heap->pos[idx_node->vertex] = smallest;
        
        swap_nodes(&heap->array[smallest], &heap->array[idx]);
        min_heapify(heap, smallest);
    }
}

// Extract minimum node
struct MinHeapNode* extract_min(struct MinHeap* heap) {
    if (heap->size == 0) return NULL;
    
    struct MinHeapNode* root = heap->array[0];
    struct MinHeapNode* last = heap->array[heap->size - 1];
    heap->array[0] = last;
    
    heap->pos[root->vertex] = heap->size - 1;
    heap->pos[last->vertex] = 0;
    
    heap->size--;
    min_heapify(heap, 0);
    
    return root;
}

// Decrease distance value
void decrease_key(struct MinHeap* heap, int vertex, int distance) {
    int i = heap->pos[vertex];
    heap->array[i]->distance = distance;
    
    while (i && heap->array[i]->distance < heap->array[(i - 1) / 2]->distance) {
        heap->pos[heap->array[i]->vertex] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2]->vertex] = i;
        swap_nodes(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Main Dijkstra's algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->num_vertices;
    int dist[MAX_VERTICES];
    struct MinHeap* heap = create_min_heap(V);
    
    // Initialize distances
    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        heap->array[v] = malloc(sizeof(struct MinHeapNode));
        heap->array[v]->vertex = v;
        heap->array[v]->distance = dist[v];
        heap->pos[v] = v;
    }
    
    // Source distance = 0
    dist[src] = 0;
    decrease_key(heap, src, dist[src]);
    heap->size = V;
    
    // Process all vertices
    while (heap->size > 0) {
        struct MinHeapNode* min_node = extract_min(heap);
        int u = min_node->vertex;
        
        // Traverse all neighbors of u
        struct Node* temp = graph->adj_lists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            
            // If v is in heap and distance can be reduced
            if (heap->pos[v] < heap->size && 
                dist[u] != INF && 
                temp->weight + dist[u] < dist[v]) {
                dist[v] = dist[u] + temp->weight;
                decrease_key(heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }
    
    // Print distances
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
```

#### Simplified Version (Without Min-Heap)

```c
void dijkstra_simple(struct Graph* graph, int src) {
    int V = graph->num_vertices;
    int dist[MAX_VERTICES];
    int visited[MAX_VERTICES] = {0};
    
    // Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;
    
    for (int count = 0; count < V - 1; count++) {
        // Find minimum distance vertex
        int min = INF, min_index;
        for (int v = 0; v < V; v++)
            if (!visited[v] && dist[v] <= min) {
                min = dist[v];
                min_index = v;
            }
        
        int u = min_index;
        visited[u] = 1;
        
        // Update distances
        struct Node* temp = graph->adj_lists[u];
        while (temp != NULL) {
            int v = temp->vertex;
            if (!visited[v] && dist[u] != INF && 
                dist[u] + temp->weight < dist[v])
                dist[v] = dist[u] + temp->weight;
            temp = temp->next;
        }
    }
    
    // Print results
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
```

**Complexity:**
* With Min-Heap: O((V + E) log V)
* Without Min-Heap: O(V²)
* Space: O(V)

**Limitations:**
❌ Does NOT work with negative edge weights
✅ Works only on directed or undirected graphs with non-negative weights

**References**
* [Dijkstra's Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)
* [Dijkstra Visualization](https://visualgo.net/en/sssp)
* [Dijkstra Step-by-Step](https://www.programiz.com/dsa/dijkstra-algorithm)

---

### 7. Bellman-Ford Algorithm

#### Concept

**Bellman-Ford** finds shortest paths from a source vertex to all others, and **can handle negative edge weights**. It also detects negative cycles.

**Algorithm:**
1. Initialize distances: source = 0, others = ∞
2. Relax all edges V-1 times
3. Check for negative cycles (one more iteration)

#### Implementation

```c
struct Edge {
    int src, dest, weight;
};

struct GraphEdgeList {
    int V, E;
    struct Edge* edges;
};

void bellman_ford(struct GraphEdgeList* graph, int src) {
    int V = graph->V;
    int E = graph->E;
    int dist[MAX_VERTICES];
    
    // Initialize distances
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;
    
    // Relax all edges V-1 times
    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = graph->edges[j].src;
            int v = graph->edges[j].dest;
            int weight = graph->edges[j].weight;
            
            if (dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    
    // Check for negative cycles
    for (int j = 0; j < E; j++) {
        int u = graph->edges[j].src;
        int v = graph->edges[j].dest;
        int weight = graph->edges[j].weight;
        
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }
    
    // Print distances
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}
```

**Complexity:**
* Time: O(V × E)
* Space: O(V)

**When to Use:**
✅ Graph has negative edge weights
✅ Need to detect negative cycles
❌ Slower than Dijkstra for non-negative weights

**References**
* [Bellman-Ford Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/)
* [Negative Cycles Explained](https://www.geeksforgeeks.org/detect-negative-cycle-graph-bellman-ford/)

---

### 8. Minimum Spanning Tree (MST)

#### Concept

A **spanning tree** of a graph is a subgraph that:
* Connects all vertices
* Is a tree (no cycles)
* Has V-1 edges

A **Minimum Spanning Tree** is a spanning tree with minimum total edge weight.

---

#### A. Prim's Algorithm

**Greedy approach**: Start with one vertex, repeatedly add the cheapest edge that connects a new vertex.

```c
void prim_mst(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int parent[MAX_VERTICES];  // Store MST
    int key[MAX_VERTICES];     // Minimum weight edge
    int mst_set[MAX_VERTICES]; // Vertices in MST
    
    // Initialize
    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mst_set[i] = 0;
    }
    
    key[0] = 0;
    parent[0] = -1;
    
    for (int count = 0; count < V - 1; count++) {
        // Find minimum key vertex not in MST
        int min = INF, min_index;
        for (int v = 0; v < V; v++)
            if (!mst_set[v] && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        
        int u = min_index;
        mst_set[u] = 1;
        
        // Update key values of adjacent vertices
        for (int v = 0; v < V; v++)
            if (graph[u][v] && !mst_set[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
    }
    
    // Print MST
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
}
```

**Complexity:** O(V²) or O(E log V) with min-heap

---

#### B. Kruskal's Algorithm

**Greedy approach**: Sort all edges by weight, add edges to MST if they don't create a cycle.

Requires **Union-Find** (Disjoint Set Union) data structure:

```c
struct Subset {
    int parent;
    int rank;
};

// Find with path compression
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Union by rank
void union_sets(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare function for qsort
int compare_edges(const void* a, const void* b) {
    struct Edge* edge1 = (struct Edge*)a;
    struct Edge* edge2 = (struct Edge*)b;
    return edge1->weight - edge2->weight;
}

void kruskal_mst(struct GraphEdgeList* graph) {
    int V = graph->V;
    int E = graph->E;
    struct Edge result[MAX_VERTICES];
    int e = 0, i = 0;
    
    // Sort edges by weight
    qsort(graph->edges, E, sizeof(graph->edges[0]), compare_edges);
    
    // Allocate memory for subsets
    struct Subset* subsets = malloc(V * sizeof(struct Subset));
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }
    
    // Pick smallest edge and check if it forms cycle
    while (e < V - 1 && i < E) {
        struct Edge next_edge = graph->edges[i++];
        
        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);
        
        if (x != y) {
            result[e++] = next_edge;
            union_sets(subsets, x, y);
        }
    }
    
    // Print MST
    printf("Edge \tWeight\n");
    for (i = 0; i < e; i++)
        printf("%d - %d \t%d\n", result[i].src, result[i].dest, 
               result[i].weight);
    
    free(subsets);
}
```

**Complexity:** O(E log E) or O(E log V) — dominated by sorting

**References**
* [Prim's Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/)
* [Kruskal's Algorithm (GeeksforGeeks)](https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-algorithm-greedy-algo-2/)
* [MST Visualization](https://visualgo.net/en/mst)

---

## Algorithm Comparison Summary

| Algorithm | Problem | Graph Type | Time Complexity | Space | Notes |
|-----------|---------|------------|-----------------|-------|-------|
| **DFS** | Traversal | Any | O(V + E) | O(V) | Uses stack/recursion |
| **BFS** | Traversal, Shortest Path | Any, Unweighted | O(V + E) | O(V) | Uses queue |
| **Dijkstra** | Shortest Path | Weighted, Non-negative | O((V+E) log V) | O(V) | Greedy approach |
| **Bellman-Ford** | Shortest Path | Weighted, Can be negative | O(V × E) | O(V) | Detects negative cycles |
| **Prim** | Minimum Spanning Tree | Weighted, Undirected | O(V²) or O(E log V) | O(V) | Grows tree from vertex |
| **Kruskal** | Minimum Spanning Tree | Weighted, Undirected | O(E log E) | O(V + E) | Sorts edges first |

---

## When to Use Each Algorithm

**Traversal:**
* **DFS**: Detect cycles, topological sort, path existence, maze solving
* **BFS**: Shortest path (unweighted), level-order, nearest neighbor

**Shortest Path:**
* **Dijkstra**: Single-source shortest path, non-negative weights, GPS routing
* **Bellman-Ford**: Handles negative weights, currency arbitrage, network routing

**Minimum Spanning Tree:**
* **Prim**: Dense graphs, network design, clustering
* **Kruskal**: Sparse graphs, easier to implement, union-find practice

---

## Advanced Topics (Brief Overview)

### Floyd-Warshall Algorithm
Finds shortest paths between **all pairs** of vertices.
* Time: O(V³)
* Space: O(V²)
* Works with negative weights (but not negative cycles)

### A* Search
Enhanced Dijkstra using heuristics for faster pathfinding.
* Used in: Games, GPS navigation, robotics
* Time: Depends on heuristic quality

### Topological Sort
Orders vertices in a DAG (Directed Acyclic Graph) such that for every edge u → v, u comes before v.
* Uses: Task scheduling, build systems, course prerequisites
* Time: O(V + E) using DFS

**References**
* [Floyd-Warshall Algorithm](https://www.geeksforgeeks.org/floyd-warshall-algorithm-dp-16/)
* [A* Search Algorithm](https://www.geeksforgeeks.org/a-search-algorithm/)
* [Topological Sorting](https://www.geeksforgeeks.org/topological-sorting/)

---

## Further Reading

### Graph Fundamentals
* [Graph Theory Tutorial (GeeksforGeeks)](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/)
* [Graph Representations Deep Dive](https://www.geeksforgeeks.org/graph-and-its-representations/)
* [Visualgo — Graph Visualizations](https://visualgo.net/en)

### Traversals
* [DFS and BFS Comparison](https://www.geeksforgeeks.org/difference-between-bfs-and-dfs/)
* [Graph Traversals Tutorial](https://www.programiz.com/dsa/graph-dfs)
* [Interactive DFS/BFS](https://www.cs.usfca.edu/~galles/visualization/DFS.html)

### Shortest Path Algorithms
* [Dijkstra's Algorithm Tutorial](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)
* [Bellman-Ford Explained](https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/)
* [Shortest Path Algorithms Comparison](https://www.geeksforgeeks.org/difference-between-dijkstras-algorithm-and-bellman-ford-algorithm/)

### Minimum Spanning Trees
* [MST Algorithms Guide](https://www.geeksforgeeks.org/introduction-to-minimum-spanning-tree-mst/)
* [Prim vs Kruskal](https://www.geeksforgeeks.org/difference-between-prims-and-kruskals-algorithm-for-mst/)
* [Union-Find Data Structure](https://www.geeksforgeeks.org/union-find/)

### Video Lectures
* [MIT OCW — Graph Algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/resources/lecture-13-breadth-first-search-bfs/)
* [Stanford — Graph Search Algorithms](https://www.youtube.com/watch?v=AfSk24UTFS8)

### Practice Problems
* [LeetCode — Graph Problems](https://leetcode.com/tag/graph/)
* [HackerRank — Graph Theory](https://www.hackerrank.com/domains/algorithms/graph-theory)
* [Codeforces — Graph Problems](https://codeforces.com/problemset?tags=graphs)

---

## Assignment

Implement the following in C:

### Part 1: Graph Representation & Traversal
1. **Create a Graph ADT**
   * Implement both adjacency matrix and adjacency list representations
   * Support directed and undirected graphs
   * Functions: `create_graph()`, `add_edge()`, `print_graph()`

2. **Implement DFS and BFS**
   * Both recursive and iterative versions of DFS
   * BFS using a queue
   * Test on a graph with at least 10 vertices
   * Print traversal order for both algorithms

### Part 2: Shortest Path Algorithms
3. **Dijkstra's Algorithm**
   * Implement Dijkstra's algorithm (simple version or with min-heap)
   * Test on a weighted graph with at least 8 vertices
   * Print shortest distances from source to all vertices
   * Print the actual shortest path

### Part 2: Shortest Path Algorithms (continued)

4. **Bellman-Ford Algorithm**
   * Implement Bellman-Ford algorithm
   * Test with a graph containing negative edge weights
   * Include a test case that detects a negative cycle
   * Compare results with Dijkstra on graphs with non-negative weights

### Part 3: Minimum Spanning Tree

5. **Prim's Algorithm**
   * Implement Prim's MST algorithm
   * Test on a weighted undirected graph with at least 7 vertices
   * Print the MST edges and total weight

6. **Kruskal's Algorithm**
   * Implement Kruskal's MST algorithm
   * Implement Union-Find data structure with path compression
   * Test on the same graph as Prim's and verify both produce MSTs of equal weight

### Part 4: Comprehensive Analysis

7. **Performance Comparison**
   * Create test graphs of varying sizes (100, 500, 1000 vertices)
   * Measure and compare execution times for:
     - DFS vs BFS traversal
     - Dijkstra vs Bellman-Ford (on graphs with non-negative weights)
     - Prim vs Kruskal MST
   * Create a table showing results
   * Analyze: Which performs better on sparse vs dense graphs?

8. **Real-World Application**
   * Implement a simple **GPS routing system**:
     - Model a city map with intersections (vertices) and roads (weighted edges)
     - Use Dijkstra to find shortest path between two points
     - Display the route with distance
   * OR implement a **social network analyzer**:
     - Model friendships as an undirected graph
     - Find shortest path between two people (degrees of separation)
     - Find all people within N degrees of a person (BFS)
     - Identify connected components (friend groups)

### Bonus Challenges

9. **Topological Sort**
   * Implement topological sorting using DFS
   * Create a course prerequisite graph
   * Output a valid course ordering

10. **Cycle Detection**
   * Implement cycle detection in directed graphs using DFS
   * Implement cycle detection in undirected graphs
   * Test with various cyclic and acyclic graphs

11. **All-Pairs Shortest Path**
   * Implement Floyd-Warshall algorithm
   * Compare with running Dijkstra from each vertex
   * Measure time complexity differences

12. **A* Pathfinding**
   * Implement A* search algorithm
   * Use Manhattan distance heuristic
   * Create a grid-based maze solver
   * Compare performance with Dijkstra

### Submission Requirements

**Code Requirements:**
* Well-commented code
* Proper memory management (no leaks!)
* Error handling for edge cases
* Modular design with separate functions

**Documentation:**
* README with compilation instructions
* Brief explanation of each implementation
* Sample outputs for each algorithm

**Report (2-3 pages):**
* Algorithm complexities (theoretical vs measured)
* Performance comparison results with graphs/tables
* Discussion of trade-offs between different approaches
* Insights from real-world application implementation

### Test Cases to Include

For each algorithm, test with:
* Small graph (hand-verified results)
* Large graph (performance testing)
* Edge cases:
  - Disconnected graph
  - Single vertex
  - Complete graph
  - Graph with cycles
  - Graph with negative weights (where applicable)

---

## Common Pitfalls & Tips

### Memory Management
```c
// Always free allocated memory
void free_graph(struct Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        struct Node* current = graph->adj_lists[i];
        while (current != NULL) {
            struct Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adj_lists);
    free(graph);
}
```

### Avoiding Common Errors

1. **Array Bounds**
```c
// Always check bounds
if (vertex >= 0 && vertex < graph->num_vertices) {
    // Safe to access
}
```

2. **Visited Array Initialization**
```c
// Initialize visited array before each traversal
int visited[MAX_VERTICES] = {0};  // All zeros
// Or use memset
memset(visited, 0, sizeof(visited));
```

3. **Queue/Stack Overflow**
```c
// Check before push
if (top < MAX_VERTICES - 1) {
    stack[++top] = vertex;
} else {
    fprintf(stderr, "Stack overflow!\n");
}
```

4. **NULL Pointer Checks**
```c
// Always check before dereferencing
if (graph == NULL || graph->adj_lists[vertex] == NULL) {
    return;
}
```

### Debugging Tips

**Visualize Your Graph:**
```c
void print_graph(struct Graph* graph) {
    printf("\nGraph Adjacency List:\n");
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Vertex %d: ", i);
        struct Node* temp = graph->adj_lists[i];
        while (temp) {
            printf("-> %d(w=%d) ", temp->vertex, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}
```

**Trace Algorithm Steps:**
```c
// Add debug prints (remove for final submission)
#ifdef DEBUG
    printf("Visiting vertex %d, distance = %d\n", u, dist[u]);
#endif
```

**Use Valgrind for Memory Leaks:**
```bash
gcc -g -o graph graph.c
valgrind --leak-check=full ./graph
```

---

## Sample Test Graph

Here's a weighted directed graph to test your implementations:

```
Vertices: 6 (0-5)
Edges with weights:
0 -> 1 (4)
0 -> 2 (2)
1 -> 2 (1)
1 -> 3 (5)
2 -> 3 (8)
2 -> 4 (10)
3 -> 4 (2)
3 -> 5 (6)
4 -> 5 (3)
```

**Expected Results:**

**DFS from 0:** 0 → 1 → 2 → 3 → 4 → 5 (or similar, order may vary)

**BFS from 0:** 0 → 1 → 2 → 3 → 4 → 5

**Dijkstra from 0:**
* 0 → 0: 0
* 0 → 1: 4
* 0 → 2: 2
* 0 → 3: 9
* 0 → 4: 11
* 0 → 5: 14

**Path from 0 to 5:** 0 → 2 → 3 → 4 → 5 (cost: 14)

---

## Code Template to Get Started

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// Node structure for adjacency list
struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

// Graph structure
struct Graph {
    int num_vertices;
    struct Node** adj_lists;
};

// Function prototypes
struct Graph* create_graph(int vertices);
void add_edge(struct Graph* graph, int src, int dest, int weight, int is_directed);
void print_graph(struct Graph* graph);
void dfs(struct Graph* graph, int start);
void bfs(struct Graph* graph, int start);
void dijkstra(struct Graph* graph, int src);
void bellman_ford_graph(struct Graph* graph, int src);
void free_graph(struct Graph* graph);

// Main function for testing
int main() {
    // Create graph
    struct Graph* graph = create_graph(6);
    
    // Add edges
    add_edge(graph, 0, 1, 4, 1);
    add_edge(graph, 0, 2, 2, 1);
    add_edge(graph, 1, 2, 1, 1);
    add_edge(graph, 1, 3, 5, 1);
    add_edge(graph, 2, 3, 8, 1);
    add_edge(graph, 2, 4, 10, 1);
    add_edge(graph, 3, 4, 2, 1);
    add_edge(graph, 3, 5, 6, 1);
    add_edge(graph, 4, 5, 3, 1);
    
    // Print graph
    print_graph(graph);
    
    // Test traversals
    printf("\nDFS traversal starting from vertex 0:\n");
    dfs(graph, 0);
    
    printf("\n\nBFS traversal starting from vertex 0:\n");
    bfs(graph, 0);
    
    // Test shortest path
    printf("\n\nDijkstra's shortest path from vertex 0:\n");
    dijkstra(graph, 0);
    
    // Clean up
    free_graph(graph);
    
    return 0;
}

// TODO: Implement all functions
struct Graph* create_graph(int vertices) {
    // Your implementation here
    return NULL;
}

void add_edge(struct Graph* graph, int src, int dest, int weight, int is_directed) {
    // Your implementation here
}

// ... implement remaining functions
```

---

## Grading Rubric

| Component | Points | Criteria |
|-----------|--------|----------|
| **Graph Representation** | 15 | Both adjacency list and matrix implemented correctly |
| **DFS Implementation** | 10 | Recursive and iterative versions work correctly |
| **BFS Implementation** | 10 | Correct implementation with queue |
| **Dijkstra's Algorithm** | 15 | Correct shortest path computation |
| **Bellman-Ford Algorithm** | 15 | Handles negative weights, detects cycles |
| **MST Algorithms** | 15 | Both Prim and Kruskal implemented |
| **Performance Analysis** | 10 | Comprehensive testing and comparison |
| **Code Quality** | 5 | Clean, commented, modular code |
| **Report** | 5 | Clear documentation and analysis |
| **Bonus Challenges** | +10 | Extra credit for advanced implementations |
| **Total** | 100 (+10) | |

---

## Additional Resources

### Books
* **Introduction to Algorithms (CLRS)** — Chapters 22-25 (Graph Algorithms)
* **Data Structures and Algorithm Analysis in C** by Mark Allen Weiss
* **The Algorithm Design Manual** by Steven Skiena

### Online Courses
* [MIT 6.006 — Graph Algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/)
* [Stanford CS161 — Design and Analysis of Algorithms](https://www.coursera.org/learn/algorithms-graphs-data-structures)
* [Princeton Algorithms Course](https://www.coursera.org/learn/algorithms-part2)

### Interactive Learning
* [VisuAlgo — Graph Visualizations](https://visualgo.net/en/graphds)
* [USFCA Data Structure Visualizations](https://www.cs.usfca.edu/~galles/visualization/Algorithms.html)
* [Graph Online](https://graphonline.ru/en/) — Create and test graphs

### Practice Platforms
* [LeetCode Graph Problems](https://leetcode.com/tag/graph/)
  - Recommended: 200, 207, 210, 261, 547, 684, 743, 785, 797
* [HackerRank Graph Theory](https://www.hackerrank.com/domains/algorithms/graph-theory)
* [Codeforces Graph Tag](https://codeforces.com/problemset?tags=graphs)
* [SPOJ Classical Problems](https://www.spoj.com/problems/classical/)

### Research Papers
* [Dijkstra's Original Paper (1959)](https://doi.org/10.1007%2FBF01386390)
* [Bellman-Ford Algorithm History](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)

### Tools for Visualization
* **Graphviz** — Generate graph visualizations from code
* **NetworkX (Python)** — For prototyping graph algorithms
* **Gephi** — Interactive graph visualization

---

## Real-World Applications

### 1. Social Networks
* **Friend recommendations**: BFS to find friends-of-friends
* **Influence spreading**: DFS to track information propagation
* **Community detection**: Connected components

### 2. Navigation Systems
* **GPS routing**: Dijkstra/A* for shortest path
* **Traffic updates**: Dynamic edge weights
* **Multi-destination routing**: Modified Dijkstra

### 3. Network Routing
* **Internet routing**: Bellman-Ford in routing protocols
* **Network topology**: MST for efficient networks
* **Load balancing**: Multiple path finding

### 4. Compiler Design
* **Dependency resolution**: Topological sort
* **Control flow analysis**: DFS
* **Dead code elimination**: Graph reachability

### 5. Game Development
* **Pathfinding**: A* algorithm
* **AI decision trees**: DFS/BFS
* **Map generation**: MST for connected worlds

### 6. Recommendation Systems
* **Collaborative filtering**: Graph-based similarity
* **Content discovery**: BFS for related items
* **User clustering**: Connected components
