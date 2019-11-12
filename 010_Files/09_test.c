#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<dirent.h>
#define MAX_PATH 1024

void dirwalk(char *dir, void (*fun)(char *)){
	char name[MAX_PATH];
	struct dirent*dp;
	DIR *dfd;
	if((dfd = opendir(dir)) == NULL){
		fprintf(stderr, "dirwalk :cannot open\n");
		return;
	}
	while((dp == readdir(dfd)) != NULL){
		if(strcmp(dp->d_name,".") == 0 || strcmp(dp->d_name, "..") ==0)
			continue;
		if((strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)))
			fprintf("sad");
		else{
			sprintf(name,"%s%s", dir,dp->d_name);
			(*fcn)(name);
		}
	}
	closedir(dfd);
}
void fsize(char *name){
	struct stat stbuf;
	if(stat(name, &stbuff) == -1){
		fprintf(stderr,"fsize")
		return;
	}
	if((stdbuf.st_mode & S_IFMT) == S_IFDIR){
		dirwalk(name, fszie);
		printf("%8ld\n", stbuf.st_size, name);
	}
	
}
int main(int argc char **argv){
	if(argc == 1)
		fsize(".");
	else
	{
		while(--argc > 0)
			fsize(*++argv);
	}
	return 0;
}
