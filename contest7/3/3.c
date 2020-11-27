#include <stdio.h>

#define true 1
#define false 0
#define PATH_MAX 4096

typedef int bool;

int MyStrlen(const char* path) {
	int ind = -1;
	while (path[++ind]) {}
	return ind;
}

void RidOfDoubleSlash(char* path) {
	int new_str_ind = -1;
	int old_str_ind = -1;
	bool met_slash = false;
	while (path[++old_str_ind]) {
		if (path[old_str_ind] != '/') {
			path[++new_str_ind] = path[old_str_ind];
			met_slash = false;
		} else if (path[old_str_ind] == '/') {
			if (met_slash) {
				continue;
			} else {
				path[++new_str_ind] = path[old_str_ind];
				met_slash = true;
			}
		}
	}
	path[++new_str_ind] = path[old_str_ind];
}

void FixRelativeSteps(char* path) {
	int len = MyStrlen(path);
	int new_str_ind = 0;
	int old_str_ind = 0;
	int slash_indexes[PATH_MAX/2];
	int slash_ind = -1;
	while (path[old_str_ind]) {
		if (path[old_str_ind] == '/') {
			slash_indexes[++slash_ind] = new_str_ind;
			path[new_str_ind] = path[old_str_ind];
			++old_str_ind;
			++new_str_ind;
		} else if (path[old_str_ind] == '.') {
			if (old_str_ind + 1 < len && path[old_str_ind+1] == '/') {
				old_str_ind += 2;
			} else if ((old_str_ind + 2 < len && path[old_str_ind+1] == '.' 
						&& path[old_str_ind+2] == '/')) { // "../"
				new_str_ind = slash_indexes[--slash_ind] + 1;
				old_str_ind += 3;
			}
		} else {
			path[new_str_ind] = path[old_str_ind];
			++old_str_ind;
			++new_str_ind;
		}
	}
	path[new_str_ind] = path[old_str_ind];
}

extern void normalize_path(char* path) {
	RidOfDoubleSlash(path);
	FixRelativeSteps(path);
}

// int main(int argc, char *argv[]) {
// 	normalize_path(argv[1]);
// 	printf("%s\n", argv[1]);
// 	return 0;
// }