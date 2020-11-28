#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int GetDigitFromLongStr(const char* str, int ind_from, int ind_to) {
	int read_on = 0;
	char str_number[5];
	int ind = -1;
	for (int i = 0; i < strlen(str); ++i) {
		if (i == ind_to) {
			read_on = 0;
			break;
		}
		if (i == ind_from) {
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

	int year = GetDigitFromLongStr(date, 0, 4);
	int mon = GetDigitFromLongStr(date, 5, 7);
	int day = GetDigitFromLongStr(date, 8, 10);

	int hour = GetDigitFromLongStr(date, 11, 13);
	int mins = GetDigitFromLongStr(date, 14, 16);

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
