/* Gladys Roman
 * LAB4
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
        if(argc < 2){ //checking for correct # of arguments
                cout << "error: not enough arguments\n"; //if # of arguments is incorrect, cout error message and end program
                return 1;
        }

        int status; //status declaration for the wait function
        
	pid_t fork_return;
        fork_return  = fork( ); //program forks here; creates child
	
	//error check for fork
	if(fork_return < 0){
		cout << "Error creating child. Goodbye...\n";
		exit(1);
	}
	//in parent
	if(fork_return > 0){
	wait(&status);
	cout << "This is the Parent Process\n";	
	int fd;
	int n_char = 0;
	char buffer[20];
	fd = open(argv[1], O_RDONLY, S_IREAD | S_IWRITE); //permission for user to read and write
	if(fd == -1){
		perror(argv[1]);
  		exit(1);
         }
	n_char = read(fd, buffer, 20);
	if(n_char == -1){
		perror(argv[0]);
		exit(1);
	}

	n_char = write(1, buffer, n_char);
	 if(n_char == -1){
                perror(argv[0]);
                exit(1);
        }
	close(fd);
	}

	//Child
	if(fork_return == 0){
		int fd;
		fd = open(argv[1], O_WRONLY | O_CREAT, S_IREAD | S_IWRITE);
		int n_char = 0;
	        char buffer[100];
		if(fd == -1){
			perror(argv[1]);
			exit(1);
		}
		
		n_char = read(0, buffer, 20);
		  if(n_char == -1){
                perror(argv[0]);
                exit(1);
	        }
		
		n_char = write(fd, buffer, n_char);
		if(n_char == -1){
                perror(argv[0]);
                exit(1);
        	}
        	close(fd);

		}
	return 0;
	
}
