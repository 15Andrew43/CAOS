#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int parseFromTo(const char* str, int from, int to) {
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
	return strtol(str_number, NULL, 10);
}

void ReadDate(const char* date, struct tm* struct_time) {

	int year = parseFromTo(date, 0, 4);
	int mon = parseFromTo(date, 5, 7);
	int day = parseFromTo(date, 8, 10);

	int hour = parseFromTo(date, 11, 13);
	int mins = parseFromTo(date, 14, 16);

	struct_time->tm_year = year - 1900;
	struct_time->tm_mon = mon - 1;
	struct_time->tm_mday = day;
	struct_time->tm_isdst = -1;
	struct_time->tm_hour = hour;
	struct_time->tm_min = mins;
	struct_time->tm_sec = 0;
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
	struct tm struct_time; 
	struct tm struct_new_time;


	fgets(date, sizeof(date), stdin);

	ReadDate(date, &struct_time);

	time_t time = mktime(&struct_time);
	
	time_t new_time;


	while (fgets(date, sizeof(date), stdin)) {
		if (date[0] == '\n') {
			continue;
		}
	
		ReadDate(date, &struct_new_time);

		new_time = mktime(&struct_new_time);

		time_t delta = new_time - time;

		printf("%ld\n", delta/60);

		time = new_time;
	}
}