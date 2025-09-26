#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXARGS     20
#define ARGLEN      100

int execute( char *arglist[] );

int main() {
	char *arglist[MAXARGS+1];
	int numargs;
	char argbuf[ARGLEN];
	char *makestring();

	numargs = 0;
	while ( numargs < MAXARGS ){
		printf("Arg[%d]? ", numargs);
		if( fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n' ) {
			arglist[numargs++] = makestring(argbuf);
		} else {
			if( numargs > 0) {
				arglist[numargs] = NULL;
				execute( arglist );
				numargs = 0;
			}
		}
	}
	return 0;
}

int execute( char *arglist[] ) {
	pid_t pid;
	int status;

	pid = fork();

	if (pid < 0) {
		perror("Fork Failed");
		return -1;
	}
	else if (pid == 0) {
		if (execvp(arglist[0], arglist) < 0) {
			perror("exec failed");
			exit(1);
		}
	
	}
	else{
		wait(&status);
	}
	
	return status;
}

char * makestring( char *buf) {
	char    *cp;
	buf[strlen(buf)-1] = '\0';
	cp = malloc( sizeof(char)*(strlen(buf)+1) );
	if ( cp == NULL ) {
		fprintf(stderr,"no memory\n");
		exit(1);
	}
	strcpy(cp, buf);
	return cp;
}
