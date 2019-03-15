#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/home/diondevara/modul2/soal1/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    DIR *d;
    struct dirent *dir;
    d=opendir(".");
    if(d!=NULL)
    {
	while((dir=readdir(d))!=NULL)
	{
	    char name1[200],name2[200];
	    char folder[200]="/home/diondevara/modul2/gambar/";
	    char *file=dir->d_name;
	    int length;
	    length=strlen(file);
	    if(file[length-4] == '.' && file[length-3] == 'p' && file[length-2] == 'n' && file[length-1] == 'g')
	    {
		strcpy(name1,file);
		strcpy(name2,file);
		length=strlen(name1);
		name1[length-4]='\0';
		strcat(name1,"_grey.png");
		strcat(folder,name1);
		rename(name2,folder);
	    }
	}
	closedir(d);
    }
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}
