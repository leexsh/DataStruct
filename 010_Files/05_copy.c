#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>


int main(int argc, char *argv[]){
	if(argc < 3)
	{	
		printf("ERROR");
		exit(1);
	}
	int fd1;
	int fd2;

	fd1 = open(argv[1], O_RDONLY);
	if(fd1 < 0){
		printf("READ ERROR");
		exit(1);
	}
	fd2 = open(argv[2], O_WRONLY|O_CREAT, 0664);
	if(fd2 < 0){
		printf("WRITE FILE FAILED!\n");
		exit(1);	
	}

	int n;
	int buf[10] = {0};
	while((n = read(fd1, buf,5)) != 0){
		write(fd2,buf,n);	
	}
	//close(fd);
	return 0;
}
