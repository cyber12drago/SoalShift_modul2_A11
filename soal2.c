#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

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

  if ((chdir("/home/cyber12drago/Modul_2")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
    char nama_file[]="/home/cyber12drago/Modul_2/hatiku/elen.ku";
    struct stat sta;
    char cek[]="www-data";

    if(stat(nama_file,&sta)==0){
	char mode[] = "0777";
        int i;
        i = atoi(mode);
        chmod(nama_file,i);

        if(((strcmp(getpwuid(sta.st_uid)->pw_name,cek))==0) && ((strcmp(getgrgid(sta.st_gid)->gr_name,cek))==0)){
		remove(nama_file);
        }
    }
    sleep(3);
  }
  
  exit(EXIT_SUCCESS);
}
