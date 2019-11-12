#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#define MSG_TRY "try angin\n"

int main(){
	
	char buff[10];
	int fd, i, n;
	fd = open("dev/tty", O_RDONLY|O_NONBLOCK);
	if(fd < 0){
		printf("ERROR dev/tty!\n");
		exit(1);	
	}

	tryagain:
	n = read(fd, buff, 10);
	if(n < 0){
		if(errno == EAGAIN){
			sleep(1);
			write(STDOUT_FILENO, MSG_TRY, strlen(MSG_TRY));
			goto tryagain;
		}	
		perror("read /dev/tty");
		exit(1);
	}
	write(STDOUT_FILENO,buff,n);
	close(fd);
	return 0;
}
