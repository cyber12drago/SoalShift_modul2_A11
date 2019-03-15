# SoalShift_modul2_A11

# Soal 1
1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

### Langkah-langkah
- Membuka directory stream
> d=opendir(".");
- Mengecek apakah directory kosong atau tidak
> if(d!=NULL)
    {
        while((dir=readdir(d))!=NULL)
...
- Menyimpan nama file dalam bentuk string ke variabel "file"
> char *file=dir->d_name;
- Menyimpan "/home/diondevara/modul2/gambar/" yang merupakan path ke file tujuan akan disimpan ke array "folder"
> char folder[200]="/home/diondevara/modul2/gambar/";
- Menyimpan panjang string variabel "file" ke dalam variabel "length"
> length=strlen(file);
- Mengecek apakah file memiliki ekstensi ".png" atau tidak
> if(file[length-4] == '.' && file[length-3] == 'p' && file[length-2] == 'n' && file[length-1] == 'g')
            {
...
- Copy isi variabel "file" yang berisi nama file ke array "nama1" dan "nama2"
> strcpy(name1,file);
> strcpy(name2,file);
- Menyimpan panjang string dari "name1" ke dalam "length"
> length=strlen(name1);
- Menghilangkan ".png" dari "name1"
> name1[length-4]='\0';
- Menambahkan "_grey.png" ke dalam array "name1"
> strcat(name1,"_grey.png");
- Copy isi array "name1" ke dalam array "folder"
> strcat(folder,name1);
- Melakukan rename terhadap "name2" sehingga path file berubah
> rename(name2,folder);
- Setelah loop dari "while((dir=readdir(d))!=NULL)" berakhir maka directory stream ditutup
> ... 
}
        closedir(d);

# Soal 2
2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

```bash
#!/bin/bash
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
```

Soal ini menyuruh kita menghapus file elen.ku pada folder hatiku yang memiliki owner dan group "www-data". Untuk itu kita membuat struct untuk menyimpan user id owner dan group. Lalu setelah itu kita bandingkan apakah owner dan group adalah "www-data. Jika sama maka elen.ku akan dihapus.

Note: untuk mengubah permission menjadi 777 jadikan string 0777

# Soal 4

Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.


```bash
#!/bin/bash

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
       startt  = time(NULL);
       endt   = makan.st_atime;
       //printf("%ld"  "%ld"   "%f",startt,endt,difftime(startt,endt));
       if(difftime(startt,endt)<=30){
         cek++;
         sprintf(nama_file2, "%s%d.txt",nama_file2,cek);
         nama_file=fopen(nama_file2,"w");
         fclose(nama_file);
       }
     }
    
  sleep(5);
 }
  
  exit(EXIT_SUCCESS);
}
}

```

Di soal ini kita mengambil waktu akses dari file dan dari sistem kitaa dan  jika file pernah diakses kurang dari atau sama dengan 30 detik yang lalu dan maka akan membuat file makansehat(int).txt
