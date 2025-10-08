# Search Algorithms Guide

This guide explains the **basic search algorithms** you’ll use most often:
**Linear Search**, **Lower Bound**, and **Binary Search**.

---

## 1. Linear Search

### Idea

* Go through the array **one element at a time** until you find the target.
* Works on **any array** (sorted or unsorted).
* Time Complexity: **O(n)**

### Example

```
Array: [4, 2, 9, 7, 5]
Find: 7
Steps: check 4 → 2 → 9 → 7 ✅ found
```

---

## 2. Lower Bound

### Idea

* Finds the **first index** where the element is **not less than (≥)** the target.
* Works only on **sorted arrays**.
* Time Complexity: **O(log n)**

### Example

```
Array: [1, 3, 3, 5, 7, 9]
Target: 4
lower_bound → index 3 (value = 5)
```

---

## 3. Binary Search

### Idea

* Repeatedly split the array in half to search for the target.
* Works only on **sorted arrays**.
* Time Complexity: **O(log n)**

### Example

```
Array: [1, 3, 5, 7, 9, 11]
Target: 7
Steps: mid=5 → target > 5 → search right half → mid=7 ✅ found
```

## 4. Learn More

* [GeeksforGeeks – Linear Search](https://www.geeksforgeeks.org/linear-search/)
* [GeeksforGeeks – Binary Search](https://www.geeksforgeeks.org/binary-search/)
* [GeeksforGeeks – Binary Search and Lower Bound](https://www.geeksforgeeks.org/dsa/implement-lower-bound/)
