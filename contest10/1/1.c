#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 4096

int main(int argc, char *argv[]) {
	char* file_c = argv[1];
	int pipe_er_out[2];
	
	if (pipe(pipe_er_out) == -1) {
		perror("pipe error");
		exit(1);
	}
	
	pid_t pid = fork();
	
	if (pid != 0) {
		close(pipe_er_out[1]);
		dup2(pipe_er_out[0], 0);
		close(pipe_er_out[0]);
		
		int cnt_warnings = 0;
		int cnt_errors = 0;
	
		int line, col;
		int last_warning_line = -1;
		int last_error_line = -1;
		char buffer[MAX_LEN];
		char* pos;

		while (fgets(buffer, sizeof(buffer), stdin) > 0) {
								
			pos = strchr(buffer, ':');

			if (pos) {
				if (sscanf(pos, ":%d:%d", &line, &col) == 2) {
					if (strstr(pos, "warning") && line != last_warning_line) {
						last_warning_line = line;
						++cnt_warnings;
					} else if (strstr(pos, "error") && line != last_error_line) {
						last_error_line = line;
						++cnt_errors;
					}
				}
			}
		}
		printf("%d\n%d\n", cnt_errors, cnt_warnings);
		waitpid(pid, NULL, 0);
	} else {
	// child 		
		dup2(pipe_er_out[1], 2); // stderr
		close(pipe_er_out[1]);
		execlp("gcc", "gcc", file_c, "-Wall", "-o", "kek", NULL);
	}
	remove("kek");
	return 0;
}
