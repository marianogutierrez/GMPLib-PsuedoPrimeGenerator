prog2_1.h && prog2_1.c:
    This program implments a singly linked list in C in order to use the list
    as a queue. My implementation implements memory managemnet to ensure I don't
    have garbage my, e.g. remove the head pointer so I must adjust the list, but
    I free the old head pointer space to ensure no memory leaks.
    The queue's enqueue and dequeue aAddLast and removeFirst in order to get FIFO behavior.
    In the header, I added a tail as noted as being ok to do in order to get O(1)
    behavior for addLast rather than O(n), without as I would have to iterate n
    times to get to the end of the list.
    
    Note: The programs' functions are all thead safe via use of mutexes.
    
prog2_2.c
    Arguments: K (number of pseudo primes to print) and B (number of bits )
    This program makes use of the first to create a queue in order to 
    produce psuedo prime numbers. In order to produce large amount of numbers
    the program makes use of the gmp library, used by inlucding <gmp.h>, first downloading of course,
    the program is then hardocoded to send four threads to produce the prime numbers
    the numbers are then printed each on a new line.
    
    Note: the numbers will be at least B bits, this is the purpose of the arg. 
    
    
    Compilation line: gcc prog2_2.c prog2_1.c -l pthread -lgmp  -g -o  prog2_2

    
