# Data Structures in C — Hash Tables, Trees, and Binary Search Trees

This lecture covers **hash tables**, **hash functions**, **collision resolution strategies**, and **tree data structures** with detailed implementation examples and complexity analysis.

---

## Topics Covered

### 1. Hash Tables

#### Concept

A **hash table** (or hash map) is a data structure that maps keys to values using a **hash function**. It provides average-case **O(1)** access, insertion, and deletion — making it one of the most efficient data structures for lookup operations.

**Key Components:**
* **Hash Function**: Converts keys into array indices
* **Buckets/Slots**: Storage locations in the underlying array
* **Collision Resolution**: Strategy for handling multiple keys that hash to the same index

#### Hash Functions

A good hash function should:
* Distribute keys uniformly across the table
* Be deterministic (same key → same hash)
* Be fast to compute

**Common Hash Functions:**

```c
// Division method
unsigned int hash_division(int key, int table_size) {
    return key % table_size;
}

// Multiplication method
unsigned int hash_multiplication(int key, int table_size) {
    double A = 0.6180339887; // (√5 - 1) / 2
    return (int)(table_size * (key * A - (int)(key * A)));
}

// String hashing (djb2 algorithm)
unsigned long hash_string(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash;
}
```

**References**
* [Hash Function Basics (GeeksforGeeks)](https://www.geeksforgeeks.org/what-are-hash-functions-and-how-to-choose-a-good-hash-function/)
* [Introduction to Hashing (CP-Algorithms)](https://cp-algorithms.com/string/string-hashing.html)

---

### 2. Collision Resolution Strategies

When two keys hash to the same index, we have a **collision**. There are two main approaches:

#### A. Open Addressing (Closed Hashing)

All elements are stored **directly in the hash table array**. When a collision occurs, we probe for the next available slot.

**Probing Methods:**

1. **Linear Probing**
   * Check next slot sequentially: `(hash + i) % size`
   * Simple but causes **primary clustering**

```c
int insert_linear(int table[], int size, int key) {
    int index = key % size;
    int i = 0;
    while (table[(index + i) % size] != EMPTY) {
        i++;
        if (i == size) return -1; // Table full
    }
    table[(index + i) % size] = key;
    return (index + i) % size;
}
```

2. **Quadratic Probing**
   * Check slots: `(hash + i²) % size`
   * Reduces primary clustering but can cause **secondary clustering**

```c
int insert_quadratic(int table[], int size, int key) {
    int index = key % size;
    int i = 0;
    while (table[(index + i*i) % size] != EMPTY) {
        i++;
        if (i == size) return -1;
    }
    table[(index + i*i) % size] = key;
    return (index + i*i) % size;
}
```

3. **Double Hashing**
   * Uses second hash function: `(hash1(key) + i * hash2(key)) % size`
   * Best open addressing method — minimizes clustering

```c
int hash2(int key, int size) {
    return 7 - (key % 7); // Common choice: prime < size
}

int insert_double(int table[], int size, int key) {
    int index = key % size;
    int step = hash2(key, size);
    int i = 0;
    while (table[(index + i * step) % size] != EMPTY) {
        i++;
        if (i == size) return -1;
    }
    table[(index + i * step) % size] = key;
    return (index + i * step) % size;
}
```

**Trade-offs:**
✅ No extra memory for pointers
✅ Better cache performance
❌ Performance degrades with high load factor
❌ Deletion is complex (need tombstones)

**References**
* [Open Addressing (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/open-addressing-collision-handling-technique-in-hashing/)
* [Double Hashing Explained](https://www.geeksforgeeks.org/double-hashing/)

---

#### B. Separate Chaining (Open Hashing)

Each table slot contains a **linked list** (or other data structure) of all elements that hash to that index.

**Implementation:**

```c
struct Node {
    int key;
    int value;
    struct Node* next;
};

struct HashTable {
    int size;
    struct Node** buckets; // Array of linked list heads
};

struct HashTable* create_table(int size) {
    struct HashTable* table = malloc(sizeof(struct HashTable));
    table->size = size;
    table->buckets = calloc(size, sizeof(struct Node*));
    return table;
}

void insert_chaining(struct HashTable* table, int key, int value) {
    int index = key % table->size;
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->key = key;
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

int search_chaining(struct HashTable* table, int key) {
    int index = key % table->size;
    struct Node* current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key)
            return current->value;
        current = current->next;
    }
    return -1; // Not found
}
```

**Trade-offs:**
✅ Simple to implement
✅ Never "fills up" — can handle high load factors
✅ Easy deletion
❌ Extra memory for pointers
❌ Poor cache locality

**References**
* [Separate Chaining (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/separate-chaining-collision-handling-technique-in-hashing/)
* [Hash Table Visualization](https://www.cs.usfca.edu/~galles/visualization/OpenHash.html)

---

### 3. Hash Table Complexity

| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Search    | O(1)        | O(n)       |
| Insert    | O(1)        | O(n)       |
| Delete    | O(1)        | O(n)       |

**Load Factor (α):**
* α = n / m (n = elements, m = table size)
* Keep α < 0.7 for open addressing
* Separate chaining works well even with α > 1
* When α exceeds threshold, **rehash** (resize table and reinsert all elements)

**References**
* [Hash Table Performance Analysis](https://www.geeksforgeeks.org/load-factor-and-rehashing/)

---

### 4. Trees

#### Concept

A **tree** is a hierarchical data structure consisting of nodes connected by edges. Each node can have **child nodes**, and there's exactly one **root node** with no parent.

**Terminology:**
* **Root**: Top node with no parent
* **Leaf**: Node with no children
* **Height**: Longest path from root to leaf
* **Depth**: Distance from root to a node
* **Subtree**: Tree formed by a node and its descendants

**Basic Tree Node:**

```c
struct TreeNode {
    int data;
    struct TreeNode* children[MAX_CHILDREN]; // General tree
    int num_children;
};
```

**Properties:**
* N nodes → N-1 edges
* Exactly one path between any two nodes
* Adding an edge creates a cycle

**References**
* [Tree Data Structure (GeeksforGeeks)](https://www.geeksforgeeks.org/introduction-to-tree-data-structure/)
* [Tree Terminology Guide](https://www.geeksforgeeks.org/dsa/tree-traversals-inorder-preorder-and-postorder/)

---

### 5. Binary Trees

#### Concept

A **binary tree** is a tree where each node has **at most two children**: left and right.

**Node Structure:**

```c
struct BinaryTreeNode {
    int data;
    struct BinaryTreeNode* left;
    struct BinaryTreeNode* right;
};
```

#### Types of Binary Trees

1. **Full Binary Tree**: Every node has 0 or 2 children
2. **Complete Binary Tree**: All levels filled except possibly the last (filled left to right)
3. **Perfect Binary Tree**: All internal nodes have 2 children, all leaves at same level
4. **Balanced Binary Tree**: Height difference between left and right subtrees ≤ 1

#### Tree Traversals

**1. Inorder (Left, Root, Right):**
```c
void inorder(struct BinaryTreeNode* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}
```

**2. Preorder (Root, Left, Right):**
```c
void preorder(struct BinaryTreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}
```

**3. Postorder (Left, Right, Root):**
```c
void postorder(struct BinaryTreeNode* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}
```

**References**
* [Binary Tree Basics](https://www.geeksforgeeks.org/dsa/binary-tree-data-structure/)
* [Tree Traversal Visualization](https://visualgo.net/en/bst)

---

### 6. Binary Search Trees (BST)

#### Concept

A **Binary Search Tree** is a binary tree with the **BST property**:
* All values in the **left subtree** < node's value
* All values in the **right subtree** > node's value
* Both subtrees are also BSTs

This property enables **efficient searching**, similar to binary search on arrays.

#### Operations

**1. Search: O(h)** where h = height

```c
struct BinaryTreeNode* search(struct BinaryTreeNode* root, int key) {
    if (root == NULL || root->data == key)
        return root;
    
    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}
```

**2. Insert: O(h)**

```c
struct BinaryTreeNode* insert(struct BinaryTreeNode* root, int key) {
    if (root == NULL) {
        struct BinaryTreeNode* node = malloc(sizeof(struct BinaryTreeNode));
        node->data = key;
        node->left = node->right = NULL;
        return node;
    }
    
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    
    return root;
}
```

**3. Delete: O(h)**

Three cases:
* **Leaf node**: Simply remove
* **One child**: Replace node with its child
* **Two children**: Replace with inorder successor (smallest in right subtree)

```c
struct BinaryTreeNode* find_min(struct BinaryTreeNode* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

struct BinaryTreeNode* delete_node(struct BinaryTreeNode* root, int key) {
    if (root == NULL) return root;
    
    if (key < root->data)
        root->left = delete_node(root->left, key);
    else if (key > root->data)
        root->right = delete_node(root->right, key);
    else {
        // Node to delete found
        if (root->left == NULL) {
            struct BinaryTreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct BinaryTreeNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // Two children: get inorder successor
        struct BinaryTreeNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    return root;
}
```

#### BST Complexity

| Operation | Average Case | Worst Case |
|-----------|--------------|------------|
| Search    | O(log n)    | O(n)       |
| Insert    | O(log n)    | O(n)       |
| Delete    | O(log n)    | O(n)       |

**Note:** Worst case occurs when tree becomes skewed (essentially a linked list). **Balanced BSTs** (AVL, Red-Black) guarantee O(log n).

**References**
* [Binary Search Trees (GeeksforGeeks)](https://www.geeksforgeeks.org/dsa/binary-search-tree-data-structure/)
* [BST Visualization](https://visualgo.net/en/bst)

---

## Comparison Summary

| Data Structure | Search      | Insert      | Delete      | Use Cases                    |
|----------------|-------------|-------------|-------------|------------------------------|
| Hash Table     | O(1) avg    | O(1) avg    | O(1) avg    | Fast lookups, caches         |
| Binary Tree    | O(n)        | O(n)        | O(n)        | Hierarchical data            |
| BST            | O(log n)*   | O(log n)*   | O(log n)*   | Ordered data, range queries  |

\* Average case for balanced trees

---

## When to Use Each Structure

**Hash Tables:**
* Need fastest possible lookup
* Don't need ordered data
* Keys have good hash function
* Examples: Caches, symbol tables, frequency counting

**Binary Trees:**
* Hierarchical relationships
* File systems, organization charts
* Expression trees

**Binary Search Trees:**
* Need both fast lookup AND sorted order
* Range queries (find all values between x and y)
* Finding min/max, predecessor/successor
* Examples: Database indexing, autocomplete

---

## Further Reading

### Hash Tables
* [Hash Tables — The Complete Guide](https://www.geeksforgeeks.org/hashing-data-structure/)
* [Hash Functions Deep Dive](https://research.cs.vt.edu/AVresearch/hashing/)
* [Interactive Hash Table Visualization](https://www.cs.usfca.edu/~galles/visualization/Hashing.html)

### Trees & BST
* [Tree Data Structures Tutorial](https://www.geeksforgeeks.org/tree-data-structure/)
* [Binary Search Trees — Complete Guide](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
* [Visualgo — Tree Visualizations](https://visualgo.net/en/bst)
* [MIT OCW — Binary Search Trees Lecture](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/resources/lecture-5-binary-search-trees-bst-sort/)

---

## Assignment

Implement the following in C:

1. **Hash Table with Separate Chaining**
   * Create, insert, search, and delete operations
   * Implement rehashing when load factor > 0.7
   * Test with at least 100 elements

2. **Binary Search Tree**
   * Implement insert, search, delete, and all three traversals
   * Write a function to check if a tree is a valid BST
   * Implement `find_min()`, `find_max()`, and `height()` functions

3. **Comparison Analysis**
   * Compare average search times for hash table vs BST with 10,000 random integers
   * Measure and report: insertion time, search time, memory usage
   * Submit a brief report with your findings

**Bonus Challenge:** Implement open addressing with linear probing and compare its performance to separate chaining.

---
