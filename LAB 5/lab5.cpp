/* Gladys Roman
 * CSE460 LAB5
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

const int NT = 3;
const int MAX = 25; //max buffer
pthread_mutex_t output_lock;
int *times = new int[NT];
int buffer = 0;

void * add_one( void *num );

int main(int argc, char *argv[]){
	pthread_t *thread_ids;
	void *p_status;
	
	for(int i = 0; i < NT ; i++){
		times[i] = 0;
	}

	//Set up an output lock so that threads wait their turn to speak.
  	if (pthread_mutex_init(&output_lock, NULL) != 0)
   	{
     		 perror("Could not create mutex for output: ");
      		return 1;
   	}

	thread_ids = new pthread_t[NT];

	// generate threads 
   	for (int i = 0; i < NT; i++)
   	{
      		int *arg = new int;
      		*arg = i;
      		if( pthread_create(&thread_ids[i],NULL, add_one ,arg) > 0)
      		{
            		perror("creating thread: ");
            		return 2;
      		}	
   	}

	 // join threads and print their return values
   	for (int i = 0; i < NT; i++)
   	{
      		if (pthread_join(thread_ids[i], &p_status) != 0)
      		{
        		 perror("trouble joining thread: ");
         		return 3;
      		}		

      		//Threads may still be building their return, so lock stdout
     		if (pthread_mutex_lock(&output_lock) != 0)
      		{
          		perror("Could not lock output: ");
          		return 4;
      		}	
      		cout << "Thread " << i << ": " << (char *)p_status << endl;
     		 if (pthread_mutex_unlock(&output_lock) != 0)
      		{
          		perror("Could not unlock output: ");
          		return 5;
      		}

      		delete [] (char *)p_status;
   	
	}		
	
	cout << "Total buffer accesses: " << times[0] + times[1] + times[2] << endl;

	delete [] times;

	return 0;
}

void * add_one( void *num ){
	int t_num = *(int *)num;
	char *msg = new char[255];
	
	while( buffer < MAX){
		if(pthread_mutex_lock(&output_lock) != 0){
			perror("Could not lock output: ");
			exit(4);
		}

		cout << "TID: " << pthread_self() << "PID : " << getpid() << " Buffer: " << buffer << endl;
		buffer++;
		times[t_num]++;

		if(pthread_mutex_unlock(&output_lock) != 0){
			perror("Could not unlock output: ");
			exit(5);
		}

		if(times[t_num] > MAX/3){
                        sleep(0.5);
                }

		//return msg
		snprintf(msg, 255, "TID %1u works on buffer %d times", pthread_self(), times[t_num]);
	}
		return msg;	
}

