#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>

#include <string.h>


/*
stat(pathname, &sb);
           if ((sb.st_mode & S_IFMT) == S_IFREG) {
               // Handle regular file 
           }

stat(pathname, &sb);
           if (S_ISREG(sb.st_mode)) {
               // Handle regular file 
           }
*/
enum { 
    maxIntStrLen = 15
};

int
main(int argc, char *argv[])
{
    int exit_code = 0;
    int in;
    struct stat sb;
    char* pathname;

    int size = 0;


    for (int i = 0; i < argc; ++i) {

        pathname = argv[i+1];
        stat(pathname, &sb);
        if (!S_ISREG(sb.st_mode)) {
            continue;
        }
        in = open(pathname, O_RDONLY);
        if (-1==in) {
            exit_code = 1;
        }
        size += lseek(in, 0, SEEK_END);
        close(in);
    }

    char curValStr[maxIntStrLen + 1] = "";
    snprintf(curValStr, sizeof(curValStr), "%d ", size);       
    write(1, curValStr, strlen(curValStr));


 finally:
    close(in);
    return exit_code;
}
