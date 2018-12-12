prog2_1.h && prog2_1.c
    This program implments a singly linked list in C in order to use the list
    as a queue. My implmnetation implements memory managemnet to ensure I don't
    have garbage my, e.g. remove the head pointer so I must adjust the list, but
    I free the old head pointer space to ensure the heap is as large as I can make it.
    The queue's enqueue and dequeue aAddLast and removeFirst in order to get FIFO behavior.
    In the header, I added a tail as noted as being ok to do in order to get O(1)
    behavior 