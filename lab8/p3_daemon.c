// 3.Write a C program such that it initializes itself as a daemon Process.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
void create_daemon()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        exit(EXIT_SUCCESS); //kill parent
    }

    
    if (setsid() < 0)  // create new session and child becomes session leader and process group leader, has no controlling terminal
    {
        exit(EXIT_FAILURE);  
    }
    umask(0); // remove inherited masks

    if (chdir("/") < 0)
    {
        exit(EXIT_FAILURE);
    }

//     /dev/null discards all input/output.

// Opening this ensures the daemon won’t accidentally read from/write to the terminal.
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);



    // Close the actual standard file descriptors so they don’t interfere.
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
int main()
{
    create_daemon();
    openlog("daemon_ex", LOG_PID, LOG_DAEMON);
    while (1)
    {
        syslog(LOG_NOTICE, "Daemon is running...\n");
        sleep(30);
    }
    closelog();
    return EXIT_SUCCESS;
}