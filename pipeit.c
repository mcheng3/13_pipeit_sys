#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void parent(int fd[], int n){
	
	write(fd[1], &n, sizeof(n));
	close(fd[1]);
	printf("[parent] sending: %d\n", n);
	int c;
	read(fd[0], &c, sizeof(c));
	close(fd[0]);
	printf("[parent] received: %d\n", c);

}

void child(int fd[]){
	int n;
	read(fd[0], &n, sizeof(n));
	close(fd[0]);
	printf("[child] multiplying 9 by: %d\n", n);	
	n = n * 9;
	write(fd[1], &n, sizeof(n));
	close(fd[1]);
}

int main(){
	int fd[2];
	pipe(fd);
	int f = fork();
	
	if(f == -1){
		perror("Pipe not opened");
		exit(1);
	}

	if(f){
		parent(fd, 15);
		wait(NULL);
	}
	else{
		child(fd);
	}

	return 0;

}