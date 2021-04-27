#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "BENSCHILLIBOWL.h"

// Feel free to play with these numbers! This is a great way to
// test your implementation.
#define BENSCHILLIBOWL_SIZE 100
#define NUM_CUSTOMERS 20
#define NUM_COOKS 10
#define ORDERS_PER_CUSTOMER 2
#define EXPECTED_NUM_ORDERS NUM_CUSTOMERS * ORDERS_PER_CUSTOMER

// Global variable for the restaurant.
BENSCHILLIBOWL *bcb;


void* BENSCHILLIBOWLCustomer(void* tid) {
  int customer_id = *((int*) tid);
  
  int a;
  for (a = 0; i<ORDERS_PER_CUSTOMER; a++){
    Order* tempOrder = (Order *) malloc(sizeof(Order));
    tempOrder->menu_item = PickRandomMenuItem();
    tempOrder->customer_id = customer_id;
    tempOrder->next = NULL;
    
    AddOrder(bcb, tempOrder);
  }
}


void* BENSCHILLIBOWLCook(void* tid) {
  int cook_id = *((int*) tid);
	int orders_fulfilled = 0;
  
  Order* order = GetOrder(bcb);
  while (order){
    free(order);
    orders_fulfilled+=1;
    order = GetOrder(bcb);
  }
	printf("Cook #%d fulfilled %d orders\n", cook_id, orders_fulfilled);
	return NULL;
}


int main() {
  
  bcb = OpenRestaurant(BENSCHILLIBOWL_SIZE, EXPECTED_NUM_ORDERS);
  
  pthread_t customersThreads[NUM_CUSTOMERS];
  pthread_t cooksThreads[NUM_COOKS];
  
  int customerId[NUM_CUSTOMERS];
  int cookId[NUM_COOKS];
  
  int b;
  
  for (b = 0; i<NUM_CUSTOMERS; b++){
    customerId[b] = b;
    pthread_create(&customersThreads[b], NULL, BENSCHILLIBOWLCustomer, &customerId[b]);
  }
  
  for (b = 0; i<NUM_COOKS; b++){
    cookId[b] = i;
    pthread_create(&cooksThreads[b], NULL, BENSCHILLIBOWLCook, &cookId[b]);
  }
  
  for (b = 0; i<NUM_CUSTOMERS; b++){
    pthread_join(customersThreads[b], NULL);
  }
  
  for (b = 0; i<NUM_COOKS; b++){
    pthread_join(cooksThreads[b], NULL);
  }
  
  CloseRestaurant(bcb); 
  
  return 0;
}