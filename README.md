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

