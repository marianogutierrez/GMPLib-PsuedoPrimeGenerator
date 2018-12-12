#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "prog2_1.h"

mpz_t globalCounter;
pthread_mutex_t counterguard = PTHREAD_MUTEX_INITIALIZER;
TSAFELIST *numberList;

// mpz_t is pass by reference 3.5 paramter conventions; however would still need to lock
void getNextNum(mpz_t num) { // will not work without paramter for bit size
  pthread_mutex_lock(&counterguard);
  mpz_set(num,globalCounter);
  // set to  width + 1 (main) then I can just add by 2
  mpz_add_ui(globalCounter,globalCounter,2); // add two get the next odd number
  pthread_mutex_unlock(&counterguard);
}

void * generatePrimes(void* arguement) { //amt of bits for each num
  //unsigned long int min = (unsigned long int) minNum;
  mpz_t increase;
  mpz_init(increase);
  mpz_set(increase,arguement);
  for(;;) {
  getNextNum(increase); // send parameter, mpz_t call by reference
  if(mpz_probab_prime_p(increase,100000) >= 1) { // prime or psuedoprime is ok
    tSafeEnqueue(numberList,increase);
  }
 } // inf loop end
} // method end

int main(int argc, char const *argv[]) {
  printf("%s\n","Assignment #2-1, Mariano Gutierrez, margutierrez75@gmail.com");
  if(argc < 3) {
    printf("%s\n", "Not enough args, numbe of pseudo prime and bit length");
    return 1;
  }

  numberList = tsafeConstruct(); // don't just malloc!
  int k = atoi(argv[1]); //  we want k pusedoprimes
  unsigned long int reqBits = atoi(argv[2]);
  mpz_init_set_str(globalCounter,"0",10);
  mpz_set_si(globalCounter,k); // global Counter set to K prime numbers

// step by step... Get num bits to 2^bits then add 1 then send off
  mpz_t bits;
  mpz_init(bits);
  mpz_t base;
  mpz_init_set_str(base,"2",10);
  mpz_pow_ui(globalCounter,base,reqBits); // bits = 2^1024
  mpz_add_ui(globalCounter,globalCounter,1); // bits = 1 + 2^1024


  // works with small nums...
  //unsigned long int toSend = ( (unsigned long int) pow(2,reqBits) ) + 1;
  //printf("should be big: %lu\n",toSend );

  // start the threads up
  pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t)* 4);
  for(int i = 0; i < 4; i++) {
    pthread_create(threads+i,NULL,generatePrimes, (void*) bits );
  }

  // continuously Dequeue
  TSAFEDATA data;
  while(k != 0 ) { //returns 1 if true
    data = tSafeDequeue(numberList);
    if(data.isValid) {
      k--;
      gmp_printf("%Zd\n", data.value);
    }else{
      usleep(1000); // standard and in milliseconds
    }
  }

  tSafeDestruct(numberList); // free list mem.
  return 0; /// will kill all the threads pg.623 Kerrisk
}
