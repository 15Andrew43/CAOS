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
	for (int i = 0; i < strlen(file_name); ++i) {
		dir_path[len + i] = file_name[i];
	}
	dir_path[strlen(dir_path)] = '\0';
	return dir_path;
}

void DFS(char* dir_path, long long int* size) {
	int dirfd = open(dir_path, O_RDONLY);
	DIR* dir = fdopendir(dirfd);
	struct dirent *entry;
	struct stat st;
	printf("%s\n", dir_path);
	while ((entry=readdir(dir))) {
		printf("%s\n", "pep");
		printf("%s\n", entry->d_name);
		printf("%s\n\n\n", concat(dir_path, entry->d_name));
		lstat(dir_path, &st);
		if (S_ISREG(st.st_mode)) {
			*size += st.st_size;
		}
		if (S_ISDIR(st.st_mode) && strncmp(entry->d_name, ".", 1)) {
			printf("%s\n", "lolpepkek");
			printf("%s\n", entry->d_name);
			DFS(concat(dir_path, entry->d_name), size);
		}
	}
}

long long int getRegularSize(char* dir_path) {
	long long int size = 0;
	DFS(dir_path, &size);
	return size;
}

int main(int argc, char *argv[]) 
{
	char* str = malloc(sizeof(char) * 10);
	str[0] = 'a';
	if (!strncmp(str, "vcd", 1)) {
		printf("%s\n", "========================================");
	}
	char* dir_path = malloc(PATH_MAX * sizeof(char));
	dir_path = argv[1];
	printf("%lld\n", getRegularSize(dir_path));
	free(dir_path);
	return 0;	
}