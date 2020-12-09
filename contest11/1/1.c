#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

volatile sig_atomic_t number = 0;
volatile sig_atomic_t must_exit = 0;

void handle_sigusr1(int signum)
{
    number++;
 	printf("%d\n", number);   
 	fflush(stdout);
}

void handle_sigusr2(int signum)
{
    number *= (-1);
    printf("%d\n", number);
    fflush(stdout);
}
void handle_sigterm(int signum)
{
    must_exit = 1;
}

int main()
{	
    struct sigaction action1;
    memset(&action1, 0, sizeof(action1));
    action1.sa_handler = handle_sigusr1;
    action1.sa_flags = SA_RESTART;
    sigaction(SIGUSR1, &action1, NULL);

    struct sigaction action2;
    memset(&action2, 0, sizeof(action2));
    action2.sa_handler = handle_sigusr2;
    action2.sa_flags = SA_RESTART;
    sigaction(SIGUSR2, &action2, NULL);
    
    struct sigaction action_term;
    memset(&action_term, 0, sizeof(action_term));
    action_term.sa_handler = handle_sigterm;
    action_term.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &action_term, NULL);

    printf("%d\n", getpid());
    fflush(stdout);
    scanf("%d", &number);
    fflush(stdin);

    while (! must_exit) {
        pause();
    }
}
