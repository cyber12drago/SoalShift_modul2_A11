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

# Soal 3

Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. Buatlah program C yang dapat : i) mengekstrak file zip tersebut. ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. Catatan:
Gunakan fork dan exec. Gunakan minimal 3 proses yang diakhiri dengan exec. Gunakan pipe Pastikan file daftar.txt dapat diakses dari text 
editor

Langkah-Langkah :

1. buat child 1 dengan fork

2. unzip campur.zip dengan fungsi exec

3. buat child 2 

4. jalankan fungsi touch untuk membuat daftar.txt dengan fungsi exec

5. buat child 3

6. simpan output dari child 3 dengan pipe

7. buatlah fungsi exec untuk menjalankan fungsi ls untuk membuat list file di folder campur2

8. buatlah pipe untuk membaca output yang disimpan dalam pipe sebelumnya

9. buatlah fungsi untuk membuat file sementara untuk membaca output dari pipe

10. buatlah fungsi untuk membuka file daftar.txt untuk kemudian di write

11. buatlah fungsi untuk mendapatkan data dari file sementara tsb yang nanti nya akan diprint di daftar.txt

12. buatlah fungsi print untuk mengeprint data list ke daftar.txt


# Soal 4

Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.


```bash
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

# Soal 5
Membuat program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Dengan Keterangan:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

## Soal A
```
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
	char file[100] = "/home/diondevara/log/";//path tujuan
    	strcat (file, folder);//menambahkan string dari "folder"
	strcat (file, "/log");//menambahkan "/log" 
	strcat (file, minutestr);//menambahkan iterasi menit
	strcat (file, ".log");//menambahkan".log"
	printf ("%s\n", file);//print string "file"
    	destination = fopen(file, "a+");//open file 
	dest = fgetc(slog);//mendapat input dari syslog
	while(dest!=EOF)//cek apakah end of file atau tidak
	{
	    fputc(dest, destination);//write input syslog ke file
	    dest = fgetc(slog);//mendapat input dari syslog
	}
	fclose(slog);//tutup syslog
	fclose(destination);//tutup file tujuan
	sleep(60);//delay selama 1 menit
    }
    
  }
  
  exit(EXIT_SUCCESS);
}
```
## Soal B
```
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
    char proses[20] = {"soal5a"};//nama proses yang akan di-kill
    char *argv[3] = {"killall", proses, NULL};//argumen killall
    execv("/usr/bin/killall", argv);//eksekusi argumen
}
```
