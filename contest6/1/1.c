#include <sys/types.h>
#include <unistd.h>

#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <stdio.h>

#include <string.h>

enum { 
    maxIntStrLen = 15
};

struct Item {
  int value;
  u_int32_t next_pointer;
};

void MyExit(int in) {
	close(in);
}


int
main(int argc, char *argv[])
{
    int exit_code = 0;
    int in = open(argv[1], O_RDONLY);
    if (-1 == in) {
        exit_code = 1;
        MyExit(in);
        return exit_code;
    }

    ssize_t in_read;
    struct Item item;
    
    while ( (in_read = read(in, &item, sizeof(item))) > 0 ) {
    	char curValStr[maxIntStrLen + 1] = "";
    	snprintf(curValStr, sizeof(curValStr), "%d ", item.value);
        if (-1 == write(1, curValStr, strlen(curValStr))) {
                exit_code = 2;
                MyExit(in);
                return exit_code;
        }
        if (item.next_pointer == 0) {
            break;
        }
        if (-1 == lseek(in, item.next_pointer, SEEK_SET)) {
            exit_code = 3;
            MyExit(in);
            return exit_code;
        }
    }
    if (-1 == in_read) {
        exit_code = 2;
        MyExit(in);
        return exit_code;
    } 
    MyExit(in);
    return exit_code;   
}
