#define _DEFAULT_SOURCE
#define _FILE_OFFSET_BITS 64

#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

#include <string.h>

#define FALSE 0
#define TRUE 1

#define PATH_MAX 4096

typedef int bool;

enum { 
    maxlongStrLen = 30
};

int
main(int argc, char *argv[])
{
    ssize_t in_read;
    int exit_code = 0;

    struct stat sb;
    char pathname[PATH_MAX];

    long long size = 0;
    char symbol;
    long long ind = -1;
    bool is_read = FALSE;

    while (TRUE) {
        ind = -1;
        pathname[0] = '\0';
        is_read = FALSE;
        while ((in_read = read(0, &symbol, sizeof(symbol))) > 0 ) {
            if (!is_read && ( symbol == '\n' || symbol == '\t')) {
                continue;
            } else if (is_read && ( symbol == '\n' || symbol == '\t')) {
                break;
            }
        
            is_read = TRUE;
            pathname[++ind] = symbol;
            pathname[ind + 1] = '\0';
        }

        if (-1 == in_read) {
            exit_code = 1;
            return exit_code;
        }
        
	if (strlen(pathname)) {
		lstat(pathname, &sb);
		if (!S_ISREG(sb.st_mode)) {
			if (in_read == 0) {
				break;
		        }
		    continue;
		}
	
		size += sb.st_size;
        }
        if (in_read == 0) {
            break;
        }
    }

    char curValStr[maxlongStrLen + 1] = "";
    snprintf(curValStr, sizeof(curValStr), "%lld", size);       
    write(1, curValStr, strlen(curValStr));

    return exit_code;
}
