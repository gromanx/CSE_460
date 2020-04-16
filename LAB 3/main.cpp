/* Gladys Roman
 * CSE460 LAB3
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main(int argc, char *arg[]){
	if(argc < 3){ //checking for correct # of arguments
		cout << "error myCat: not enough arguments\n"; //if # of arguments is incorrect, cout error message and end program
		return 0;
	}
	
	int status; //status declaration for the wait function
	pid_t fork_return;
   	fork_return  = fork( ); //program forks here
	
	if(fork_return > 0){ //parent process
		wait(&status); //waits for the child to finish
		cout << "In the PARENT process\n";
		cout << "PID: " << getpid() << ", PPID: " << getppid() << ", GRPID: " << getpgrp() << endl; //printing data from the parent
	}

	else if(fork_return == 0){ //child process
		cout << "In the CHILD process Trying to Meow\n";
		cout << "PID: " << getpid() << ", PPID: " << getppid() << ", GRPID: " << getpgrp() << endl; //printing data from the child
	 execl("/bin/cat", "cat", "-n", arg[1], "-", arg[2], NULL); //calls cat and uses file1 & file2, which were passed as arguments at the beginnning of the program
	}

	return 0;
}
