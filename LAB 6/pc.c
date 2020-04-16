/* GLadys Roman
 * CSE460 LAB6
 */

#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define TRUE 1
#define BUFFER_SIZE 5
#define LOOPS 10

pthread_mutex_t mutex; //mutex lock
sem_t full, empty; //semaphore
int buffer[BUFFER_SIZE]; //buffer
int in, out; //buffer counter

pthread_t tid; //tid
pthread_attr_t attr; //set of thread attributes

void *producer(void *param); //producer thread
void *consumer(void *param); //consumer thread 

void initializeData() {
	pthread_mutex_init(&mutex, NULL); //initialize mutex lock
	sem_init(&full, 0, 0); //full semaphore initialized to 0
	sem_init(&empty, 0, BUFFER_SIZE); //empty semaphore initialized to the buffer size
	pthread_attr_init(&attr); //defau;t attributes
	//default buffer
	in = 0;
	out = 0;
}

void *producer(void *param){
	int item;
	int i = 0;

	while(i < LOOPS){
		item = rand() % 1000; //generates random num
		sem_wait(&empty); //get empty lock
		pthread_mutex_lock(&mutex); //get mutex lock

		if((in + 1) % BUFFER_SIZE == out){
			printf("Error the buffer is full \n");
		}
		else{
			buffer[in] = item;
			in = ((in + 1) % BUFFER_SIZE);
			printf("Producer [%1u] produced %d\n", pthread_self(), item);
		}
		i++;
		pthread_mutex_unlock(&mutex); //release mutex lock
		sem_post(&full); //signal full
	}
}

void *consumer(void *param){
 	int item;
        int i = 0;

        while(i < LOOPS){
		sem_wait(&full); //get full lock
                pthread_mutex_lock(&mutex); //get mutex lock
		
		if(in == out){
			printf("Error: the buffer is empty\n");
		}
		else{
			//consume an item and remove it from the buffer
			item = buffer[out];
			out = ((out + 1) % BUFFER_SIZE);
			printf("    Consumer [%1u] consumed %d\n", pthread_self(), item);
		}
		i++;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty); //signal empty
	}
}

int main(int argc, char *argv[]){
	int i; //loop counter
	if(argc != 3){
		fprintf(stderr, "USAGE:./pc \n");
	} //verify # of arguments

	int numProd = atoi(argv[1]); //producer threads
	int numCons = atoi(argv[2]); //consumer threads

	initializeData();

	for(int i = 0; i < numProd ; i++){
		pthread_create(&tid, &attr, producer, NULL);
	}

	for(int i = 0; i < numCons; i++){
		pthread_create(&tid, &attr, consumer, NULL);
	}

	sleep(1);

	printf("Exit the program \n");
	exit(0);

}
