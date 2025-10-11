#ifndef DSALIB_QUEUE_H
#define DSALIB_QUEUE_H

/**
 * @brief Queue data structure using circular array.
 *
 * A queue is a First-In-First-Out (FIFO) data structure.
 * Elements are added at the rear and removed from the front.
 *
 * This implementation uses a circular buffer to avoid unnecessary
 * memory moves when dequeuing elements.
 *
 * Time Complexities:
 * - Enqueue: O(1) amortized (O(n) when resizing)
 * - Dequeue: O(1)
 * - Peek: O(1)
 * - IsEmpty: O(1)
 * - Size: O(1)
 */
typedef struct {
    // TODO
} dsalib_queue_t;

// TODO

#endif // DSALIB_QUEUE_H
