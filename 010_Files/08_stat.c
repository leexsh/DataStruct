#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>


int main(){
	
	char buff[10];
	struct stat st;
	st = stat(buff)
	switch(st.st_mode & S_IFMT){
		case 1:
		break;
		case 2:
		break;
		
	}
	fd = open("word", O_RDONLY|O_CREAT, 0664);
	if(fd < 0){
		printf("CREATE FILE FAILED!\n");
		exit(1);	
	}

	close(fd);
	return 0;
}
