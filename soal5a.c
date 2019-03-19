#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/diondevara/log/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    // main program here
    time_t times = time(NULL);
    struct tm tm = *localtime(&times);//mencari waktu lokal
    char folder[200];
    strftime(folder, sizeof(folder), "%d:%m:Y-%H:%M", &tm);//format waktu
    mkdir(folder,0777);//buat folder
    for(int minute=1;minute<=30;minute++)
    {
	FILE *slog = fopen("/var/log/syslog", "r");//membuka syslog
	FILE *destination;
	char dest;
	char minutestr[200];
	sprintf(minutestr," %d", minute);//mengubah integer ke string
	char file[100] = "/home/diondevara/log/";
    	strcat (file, folder);
	strcat (file, "/log");
	strcat (file, minutestr);
	strcat (file, ".log");
	printf ("%s\n", file);
    	destination = fopen(file, "a+");//open file 
	dest = fgetc(slog);//mendapat input dari syslog
	while(dest!=EOF)//cek apakah end of file atau tidak
	{
	    fputc(dest, destination);//write input syslog ke file
	    dest = fgetc(slog);//mendapat input dari syslog
	}
	fclose(slog);
	fclose(destination);
	sleep(60);
    }
    
  }
  
  exit(EXIT_SUCCESS);
}
