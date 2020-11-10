#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int parseFromTo(char* str, int from, int to) {
	int read_on = 0;
	char str_number[5];
	int ind = -1;
	for (int i = 0; i < strlen(str); ++i) {
		if (i == to) {
			read_on = 0;
			break;
		}
		if (i == from) {
			read_on = 1;
		}
		if (read_on) {
			str_number[++ind] = str[i];
		}
	}
	str_number[++ind] = '\0';
	printf("%s\n", str_number);
	return strtol(str_number, NULL, 10);
}

int main(int argc, char *argv[]) 
{
//	YYYY-MM-DD HH:mm 
	char date[17];
	int first_time = 1;
	int year, new_year;
	int mon, new_mon;
	int day, new_day;
	int hour, new_hour;
	int mins, new_mins;
	struct tm struct_time, struct_new_time;
	struct tm struct_delta;

	year = parseFromTo(date, 0, 4);
	mon = parseFromTo(date, 5, 7);
	day = parseFromTo(date, 8, 10);

	hour = parseFromTo(date, 11, 13);
	mins = parseFromTo(date, 14, 16);
	printf("%d %d %d %d %d\n", year, mon, day, hour, mins);

	struct_time.tm_year = year - 1900;
	struct_time.tm_mon = mon - 1;
	struct_time.tm_mday = day + 1;
	struct_time.tm_isdst = -1;
	struct_time.tm_hour = hour; //????????
	struct_time.tm_min = mins; // ??????????????

	time_t time = mktime(&struct_time);

	while (fgets(date, sizeof(date), stdin)) {
		new_year = parseFromTo(date, 0, 4);
		new_mon = parseFromTo(date, 5, 7);
		new_day = parseFromTo(date, 8, 10);

		new_hour = parseFromTo(date, 11, 13);
		new_mins = parseFromTo(date, 14, 16);
		printf("%d %d %d %d %d\n", year, mon, day, hour, mins);

		new_struct_time.tm_year = new_year - 1900;
		new_struct_time.tm_mon = new_mon - 1;
		new_struct_time.tm_mday = new_day + 1;
		new_struct_time.tm_isdst = -1;
		new_struct_time.tm_hour = new_hour; //????????
		new_struct_time.tm_min = new_mins; // ??????????????

		new_time = mktime(&struct_time);

		time_t delta = new_time - time;

		struct_delta = localtime(&delta);

		printf("%d\n", );

	}

	
	// int dirfd = open(dir_path, O_RDONLY | O_DIRECTORY);
	// DIR* dir = fdopendir(dirfd);
	// struct dirent *entry;
	// struct stat st;
	// struct tm struct_time;
	// memset(&struct_time, 0, sizeof(struct_time));
	struct_time.tm_year = year - 1900;
	struct_time.tm_mon = mon - 1;
	struct_time.tm_mday = day + 1;
	struct_time.tm_isdst = -1;
	// time_t max_time = mktime(&struct_time);
	// while ((entry=readdir(dir))) {
	// 	fstatat(dirfd, entry->d_name, &st, 0);
	// 	time_t modified = st.st_mtime;
	// 	if (modified > max_time) {
	// 		printf("%s\n", entry->d_name);
	// 	}
	// }
}