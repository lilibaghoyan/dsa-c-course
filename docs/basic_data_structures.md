# Data Structures in C — Arrays, Linked Lists, Stacks, and Queues

This lecture covers the **implementation details**, **trade-offs**, and **practical usage** of fundamental data structures in C.
You’ll also find reference links and an **assignment** at the end.

---

## Topics Covered

### 1. Arrays

#### Concept

An **array** is a contiguous block of memory that stores elements of the same type.
Accessing elements is **O(1)**, but inserting or deleting in the middle is costly.

#### Operations

* Access: `O(1)`
* Insertion: `O(n)` (worst case)
* Deletion: `O(n)`
* Resize (for dynamic arrays): `O(n)` (but amortized `O(1)` for append)

#### Trade-offs

✅ Fast random access
❌ Fixed size (for static arrays)
❌ Costly insertions/deletions

#### Dynamic Arrays in C

Implemented using `malloc` and `realloc`.

**Example:**

```c
int *arr = malloc(capacity * sizeof(int));
if (size == capacity) {
    capacity *= 2;
    arr = realloc(arr, capacity * sizeof(int));
}
```

**Amortized Analysis:**
Although resizing takes `O(n)` time occasionally, the average time per `push_back` operation remains `O(1)`.

**References**

* [GeeksforGeeks: Dynamic Arrays in C](https://www.geeksforgeeks.org/dynamic-array-in-c/)
* [CS50: Resizing arrays](https://cs50.harvard.edu/x/2022/notes/5/#resizing-arrays)

---

### 2. Linked Lists

#### Concept

A **linked list** consists of nodes where each node contains:

* data
* pointer to the next node

#### Singly Linked List

Each node points only to the next node.

**Example:**

```c
struct Node {
    int data;
    struct Node* next;
};
```

**Insertion at beginning (O(1)):**

```c
void push_front(struct Node** head, int value) {
    struct Node* new_node = malloc(sizeof(struct Node));
    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
}
```

#### Trade-offs

✅ Dynamic size
✅ Fast insertion/deletion at head
❌ No random access
❌ Extra memory for pointers

**References**

* [GeeksforGeeks: Linked List in C](https://www.geeksforgeeks.org/dsa/what-is-linked-list/)
* [Visualgo Linked List Visualization](https://visualgo.net/en/list)

---

### 3. Stack

#### Concept

A **stack** is a Last-In-First-Out (LIFO) structure.
You can implement it using an array or linked list.

**Common Operations**

* `push(x)` — insert element on top
* `pop()` — remove top element
* `top()` — get top element without removing it

#### Array-based Implementation

```c
#define MAX 100
int stack[MAX], top = -1;

void push(int x) {
    stack[++top] = x;
}

int pop() {
    return stack[top--];
}
```

#### Linked List Implementation

```c
struct Node {
    int data;
    struct Node* next;
};
```

**References**

* [GeeksforGeeks: Stack Data Structure](https://www.geeksforgeeks.org/dsa/stack-data-structure/)

---

### 4. Queue

#### Concept

A **queue** is a First-In-First-Out (FIFO) structure.
Like a stack, it can be implemented with arrays or linked lists.

**Common Operations**

* `enqueue(x)` — add element at the end
* `dequeue()` — remove element from the front

#### Array-based Queue

```c
#define MAX 100
int queue[MAX], front = 0, rear = -1;

void enqueue(int x) { queue[++rear] = x; }
int dequeue() { return queue[front++]; }
```

#### Linked List Queue

```c
struct Node { int data; struct Node* next; };
struct Queue { struct Node *front, *rear; };
```

**References**

* [GeeksforGeeks: Queue Data Structure](https://www.geeksforgeeks.org/dsa/queue-data-structure/)
* [Queue Implementation in C](https://www.geeksforgeeks.org/dsa/introduction-and-array-implementation-of-queue/)

---

## Trade-offs Summary

| Structure     | Access | Insert       | Delete       | Memory                 | Notes               |
| ------------- | ------ | ------------ | ------------ | ---------------------- | ------------------- |
| Array         | O(1)   | O(n)         | O(n)         | Compact                | Fixed size          |
| Dynamic Array | O(1)*  | O(n)*        | O(n)         | Slight overhead        | Amortized O(1) push |
| Linked List   | O(n)   | O(1) at head | O(1) at head | Extra pointer per node | No random access    |
| Stack         | O(1)   | O(1)         | O(1)         | Minimal                | LIFO                |
| Queue         | O(1)   | O(1)         | O(1)         | Minimal                | FIFO                |

---

## Amortized Analysis (Dynamic Array)

When dynamic arrays resize (usually doubling capacity), the `realloc` operation costs `O(n)` but happens rarely.
If you push `n` elements, the total cost is `O(n)`, so the **amortized cost per operation** is `O(1)`.

**References**

* [Amortized Analysis (GeeksforGeeks)](https://www.geeksforgeeks.org/analysis-algorithms-set-5-amortized-analysis-introduction/)
* [MIT 6.046J: Amortized Analysis Lecture](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-046j-design-and-analysis-of-algorithms-spring-2015/lecture-videos/lecture-7-amortized-analysis-union-find/)

---

## Further Reading

* [GeeksforGeeks Data Structures Index](https://www.geeksforgeeks.org/dsa/dsa-tutorial-learn-data-structures-and-algorithms/)
* [Programiz C Data Structures](https://www.programiz.com/dsa)
* [Visualgo (Interactive Visualizations)](https://visualgo.net/en)
