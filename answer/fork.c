#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	pid_t pid = fork();

	if (pid < 0) {
		perror("Fork Failer");
		exit(1);
	}
	else if (pid == 0) {
		execlp("ls", "ls", "-lt", (char *)NULL);

		perror("exec failed");
		exit(1);
	}
	else {
		wait(NULL);
		printf("Child process is done\n");
	}

	return 0;
}
