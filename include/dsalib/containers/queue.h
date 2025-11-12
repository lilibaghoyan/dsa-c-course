#ifndef DSALIB_QUEUE_H
#define DSALIB_QUEUE_H

#define MAX_SIZE 100

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
    int item[MAX_SIZE];
    int front;
    int tail;
} dsalib_queue_t;

void dsalib_queue_init(dsalib_queue_t *q);
int dsalib_queue_is_empty(dsalib_queue_t *q);
int dsalib_queue_is_full(dsalib_queue_t *q);
void dsalib_queue_enqueue(dsalib_queue_t *q, int value);
int dsalib_queue_dequeue(dsalib_queue_t *q);
int dsalib_queue_peek(dsalib_queue_t *q);
int dsalib_queue_size(dsalib_queue_t *q);

#endif // DSALIB_QUEUE_H
