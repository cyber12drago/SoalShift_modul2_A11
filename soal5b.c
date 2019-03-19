#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


int main() 
{
    char proses[20] = {"soal5a"};
    char *argv[3] = {"killall", proses, NULL};
    execv("/usr/bin/killall", argv);
}
