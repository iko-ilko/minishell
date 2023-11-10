#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int arc, char **arv, char **envp)
{
	//printf("%s\n", arv[1]);
	int fd = open("./b",  O_WRONLY | O_CREAT | O_APPEND, 0644);

	dup2(fd, 1);
	if (strcmp(arv[1], "cat") != 0)
		return 0;
	printf("??\n");
	execve("./usr/bin/cat", &arv[2], envp);
}