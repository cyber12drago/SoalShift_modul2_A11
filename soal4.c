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
#include <string.h>


int main(){
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

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int cek=0;
while(1) {
    FILE * nama_file;
    char nama_file1[]="/home/cyber12drago/Documents/makanan/makan_enak.txt";
    char nama_file2[]="/home/cyber12drago/Documents/makanan/makan_sehat";
    char angka[100];
    struct stat makan;
    time_t startt,endt;

    if(stat(nama_file1,&makan)==0){
       startt  = time(&startt);
       endt   = makan.st_atime;
       char temukan[100];
       //printf("%ld"  "%ld"   "%f",startt,endt,difftime(startt,endt));
       if(difftime(startt,endt)<=30){
         cek++;
         sprintf(temukan, "%d.txt",cek);
         strcat(nama_file2,temukan);
         nama_file=fopen(nama_file2,"w");
         fclose(nama_file);
       }
     }
    
  sleep(5);
 }
  
  exit(EXIT_SUCCESS);
}
