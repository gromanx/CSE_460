/* Gladys Roman
 * CSE460 
 * touch.c
 */


#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]){
	int n = argc;
	for(int i = 1 ; i <= n ; i++){
		if(open(argv[i], O_CREATE) < 0){
			printf(i, "cp: cannout create %s \n", argv[i]);
			exit();
		}
	}
}
			
