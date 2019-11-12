#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>


int main(){
	

	int i = 0;
	char buff[30] = {0};
	while(1){
		sprintf(buff,"file%d", i++);
		
		int fd;
		fd = open(buff, O_RDONLY|O_CREAT, 0664);
		if(fd < 0){
			printf("CREATE FILE FAILED!\n");
			exit(1);	
		}
	}
	return 0;
}
