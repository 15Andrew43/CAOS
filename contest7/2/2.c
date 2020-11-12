#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#include <limits.h>


char* concat(char* dir_path, const char* file_name) {
	int len = strlen(dir_path);
	dir_path[len] = '/';
	for (int i = 0; i < strlen(file_name); ++i) {
		dir_path[len + i + 1] = file_name[i];
	}
	dir_path[len + strlen(file_name) + 1] = '\0';
	return dir_path;
}

void DFS(char* dir_path, long long int* size) {
	int dirfd = open(dir_path, O_RDONLY);
	DIR* dir = fdopendir(dirfd);
	struct dirent *entry;
	struct stat st;
	//printf("%s\n", dir_path);
	while ((entry=readdir(dir))) {
		// //printf("%s\n", "pep");
		// //printf("%s\n", entry->d_name);
		
		char buff[PATH_MAX];
		strcpy(buff, dir_path);
		
		concat(buff, entry->d_name);
		//printf("%s\n\n\n", concat(buff, entry->d_name));
		lstat(buff, &st);
		if (S_ISREG(st.st_mode)) {
			//printf("file : %s\n", entry->d_name);
			//printf("%lld\n", st.st_size);
			*size += st.st_size;
		}
		if (S_ISDIR(st.st_mode) && strncmp(entry->d_name, ".", 1)) {
			// //printf("%s\n", "lolpepkek");
			//printf("directiry : %s\n", entry->d_name);
			DFS(buff, size);
		}
	}
}

long long int getRegularSize(char* dir_path) {
	long long int size = 0;
	DFS(dir_path, &size);
	//printf("%lld\n", size);
	return size;
}

int main(int argc, char *argv[]) 
{
	char* dir_path = malloc(PATH_MAX * sizeof(char));
	dir_path = argv[1];
	printf("%lld\n", getRegularSize(dir_path));
	return 0;	
}
