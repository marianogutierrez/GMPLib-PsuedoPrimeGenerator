
#include <stdio.h>
#include <stdlib.h>
#include "prog2_1.h"

// constructor that allocates it all on the heap
// all pointers within the struct MUST be malloc;d
TSAFELIST* tsafeConstruct() {
  TSAFELIST *list = (TSAFELIST*) malloc(sizeof(TSAFELIST));
  (list -> mutex) = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t));
  pthread_mutex_init(list -> mutex,NULL);
  list -> head = NULL;
  list -> tail = NULL;
  return list;
}

// Free things LIFO
void tSafeDestruct(TSAFELIST *list) {
  // some sorta loop to free all the nodes
  pthread_mutex_destroy(list -> mutex);
  TSAFENODE* tmpNode; // to traverse the list
  while(list -> head != NULL) {
    tmpNode = list -> head;
    list -> head = list -> head -> next;
    free(tmpNode);
  }
  //free(list); NOTE: not proper bc passed by value. + dont't need but func def does not help.
  // would need to do **list, and then do *list = NULL;
  // Safer to simply call this then free then set ptr to NULL
}

// Essentially Add Last Seems very legit and I tested it and it is working
void tSafeEnqueue(TSAFELIST* list, mpz_t num) {
  pthread_mutex_lock(list -> mutex); // lock before ds manipulation..
  TSAFENODE *newNode = (TSAFENODE*)malloc(sizeof(TSAFENODE));
  mpz_init(newNode -> number);
  mpz_set(newNode -> number, num);
  //newNode -> x = 5; // NOTE: DELETE later
  // Empty List...
  if(list -> head == NULL) {
    list -> head = newNode; // make the head the new node
    list -> head -> next = NULL; // only node so points to null
    list -> tail = list -> head; // tail is also the newNode since there is nothing else.
    //return;
  }
  else {
  // standard case
  list -> tail -> next = newNode; // appended to the end of the list.
  list -> tail = newNode; // the newNode is the new tail.
  list -> tail -> next = NULL; // the tail points to nada
}
  pthread_mutex_unlock((list -> mutex)); // done manipulating the ds
}

// remove first.
TSAFEDATA tSafeDequeue(TSAFELIST * list) {
  TSAFEDATA data;
  pthread_mutex_lock(list -> mutex); // Begin manipulation
  //
  if(list -> head == NULL) { // the list is empty...
    data.isValid = 0; // false is zero // and so we return a TSAFEDATA with invalid status.
  }
  else {
    mpz_init(data.value); // retrieve from the head always
    mpz_set(data.value, list -> head -> number);
    if(list -> head  -> next == NULL) {  // NOTE: single element case:
      free(list -> head); // avoid mem leaks.
      list -> head = NULL; // empty the list.
      list -> tail = NULL;
    }
    else {  //standard case multiple node case
      TSAFENODE *oldHead = (TSAFENODE*)malloc(sizeof(TSAFENODE)); // else get seg fault. done to clean up
      oldHead = list -> head;
      list -> head = list -> head -> next;
      free(oldHead);
    }
    data.isValid = 1; // one is true; the retrieval was successful
  } // end big else
  pthread_mutex_unlock((list -> mutex));
  return data;
}
