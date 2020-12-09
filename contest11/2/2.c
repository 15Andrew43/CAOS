#include <sys/signalfd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void read_line(FILE *from) {
	char buffer[4096];
	memset(buffer, 0, sizeof(buffer));
	fgets(buffer, sizeof(buffer), from);
	fputs(buffer, stdout);
	fflush(stdout);
}


int main(int argc, char *argv[]) {
	// separate masks
	sigset_t block_mask, catch_mask;
	sigfillset(&block_mask);
	sigemptyset(&catch_mask);
	for (int i = 0; i < argc; ++i) {
		sigaddset(&catch_mask, SIGRTMIN + i);
	}

	sigprocmask(SIG_BLOCK, &block_mask, NULL);
	int fd = signalfd(-1, &catch_mask, 0);

	// open files
	FILE* files[argc - 1];
	for (int i = 1; i < argc; ++i) {
		files[i - 1] = fopen(argv[i], "r");
	}

	
	struct signalfd_siginfo siginfo;
	int idx;
	while (1) {
		read(fd, &siginfo, sizeof(siginfo));
		idx = siginfo.ssi_signo - SIGRTMIN;
		if (0 == idx) {
			break;
		} else {
			read_line(files[idx - 1]);
		}
	}
	close(fd);
	for (int i = 1; i < argc; ++i) {
		fclose(files[i - 1]);
	}
}
