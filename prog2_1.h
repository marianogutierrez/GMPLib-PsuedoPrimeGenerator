#include <gmp.h>
#include <pthread.h>
typedef struct tsafenode { // NOTE NODE CLASS
  struct tsafenode *next;
  mpz_t number;
} TSAFENODE;

typedef struct tsafelist { // NOTE LIST
  pthread_mutex_t *mutex;
  TSAFENODE *head; // should have
  TSAFENODE *tail; // can have this.
} TSAFELIST;

typedef struct tsafereturndata { // NOTE DATA TO RETURN
  int isValid;// true: 1 false: 0
  mpz_t value;
} TSAFEDATA;

// NOTE METHODS
TSAFELIST* tsafeConstruct(); // allocate on the HEAP
void tSafeDestruct(TSAFELIST*); // no need for names
void tSafeEnqueue(TSAFELIST* , mpz_t);
TSAFEDATA tSafeDequeue(TSAFELIST * ); // get item from the front and return it.
// IF there is no element in the front is valid should be set to false and return the TSAFEDATA


// THE ABOVE OPERATES FIFO ala queue