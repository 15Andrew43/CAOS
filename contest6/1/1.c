#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>

enum { 
    maxIntStrLen = 15
};

int
main(int argc, char *argv[])
{

    int exit_code = 0;
    int in = open(argv[1], O_RDONLY);
    if (-1==in) {
        exit_code = 1;
        goto finally;
    }

    ssize_t in_read, out_d_read, out_o_read;
    int value;
    u_int32_t next_pointer;
    
    while ((in_read=read(in, &value, sizeof(value)))>0) {
    	char curValStr[maxIntStrLen + 1] = "";
    	snprintf(curValStr, sizeof(curValStr), "%d ", value);
        if (-1==write(1, curValStr, sizeof(curValStr))) {
                exit_code = 2;
                goto finally;
        }
        if ((in_read=read(in, &next_pointer, sizeof(next_pointer)))>0) {
            if (next_pointer == 0) {
                break;
            }
            if (-1==lseek(in, next_pointer, SEEK_SET)) {
                exit_code = 3;
                goto finally;
            }
        }
        if (-1==in_read) {
            exit_code = 2;
            goto finally;
        }        
    }
    if (-1==in_read) {
        exit_code = 2;
        goto finally;
    }
 finally:
    close(in);
    return exit_code;
}
