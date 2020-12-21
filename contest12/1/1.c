#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_PATH 4096

volatile int is_end_of_exe = 0;
volatile int is_closed_connection = 0;
volatile int sock = 0;
volatile int directory_fd = 0;

void my_handler(int signum)
{
    is_end_of_exe = 1;
    if(is_closed_connection == 1){
        close(sock);
        close(directory_fd);
        exit(1);
    }
}


int main(int argc, char **argv)
{
    in_port_t port = htons(strtol(argv[1], NULL, 10));
    char* path = argv[2];

    struct sigaction sig;
    memset(&sig, 0, sizeof(sig));
    sig.sa_handler = my_handler;
    sig.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &sig, NULL);
    sigaction(SIGINT, &sig, NULL);


    sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr("127.0.0.1"), // localhost
            .sin_port = port
    };
    bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sock, 10);


    directory_fd = open(path, O_DIRECTORY);
	int connect_fd;
	
    while (is_end_of_exe != 1) {
        is_closed_connection = 1;

        if (-1 == (connect_fd = accept(sock, NULL, NULL))) {
        	continue;
        }    

        is_closed_connection = 0;
        FILE* file = fdopen(connect_fd, "r");
        char file_name[MAX_PATH];
        fscanf(file, "GET %s HTTP/1.1", file_name);
        char result[MAX_PATH];

        if (-1 == faccessat(directory_fd, file_name, F_OK, 0)) {
            
            strcat(result, "HTTP/1.1 404 Not Found\r\nContent-Length: 0\r\n\r\n");
            write(connect_fd, result, strlen(result));

            close(connect_fd);
        } else if (-1 == faccessat(directory_fd, file_name, R_OK, 0)) {

            strcat(result, "HTTP/1.1 403 Forbidden\r\nContent-Length: 0\r\n\r\n");
            write(connect_fd, result, strlen(result));

            close(connect_fd);
        } else {

            strcat(result, "HTTP/1.1 200 OK\r\n");
            write(connect_fd, result, strlen(result));

            int file_fd = openat(directory_fd, file_name, 0, "r");

            struct stat stat_buffer;
            fstat(file_fd, &stat_buffer);

            result[0] = '\0';

            snprintf(result, sizeof(result), "Content-Length: %ld\r\n\r\n", stat_buffer.st_size);
            write(connect_fd, result, strlen(result));

            char file_content[MAX_PATH];
            int cnt_chars = 0;
            while ((cnt_chars = read(file_fd, file_content, sizeof(file_content))) > 0) {
                if (-1 == write(connect_fd, file_content, cnt_chars)) {
                    close(connect_fd);
                    break;
                }
            }
        }

        close(connect_fd);
    }

    close(sock);
    close(directory_fd);

    return 0;
}
