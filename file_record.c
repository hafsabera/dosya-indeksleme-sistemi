/*Bu dosya, sistemin en küçük yapý taþý olan "Dosya Kaydý" (FileRecord) nesnesini temsil eder. 
file_manager.h sistemin yöneticisi ise, bu dosya da o yöneticinin elindeki tekil dosyalarýn özelliklerini (adý, boyutu, tarihi) yöneten yapýdýr.*/

#include <stdio.h>//Standart giriþ-çýkýþ iþlemleri (printf, scanf, fgets gibi) için gereklidir.
#include <stdlib.h>//programlarýn bellek yönetimi, dönüþüm iþlemleri, sayý üretimi ve sistemle iletiþim gibi temel ihtiyaçlarýný karþýlayan fonksiyonlarý barýndýran bir baþlýk dosyasýdýr.
#include <string.h>//Karakter dizileri (string) üzerinde iþlemler (strlen gibi) yapmak için kullanýlýr.
#include "file_record.h" //Projenin temel fonksiyonlarýný barýndýran yazdýðýmýz özel baþlýk dosyasýdýr.


struct FileRecord {
    char name[101]; // Dosya ismi için ayrýlmýþ 101 karakterlik bir kutu
    char ext[11]; // Uzantý için 11 karakterlik kutu
    double sizeMB; // Boyut için sayýsal alan
    char createDate[20]; // Tarih metni
    char modDate[20]; // Deðiþiklik tarihi metni
};

FileRecord* createRecord(const char* name, const char* ext, double sizeMB, const char* cDate, const char* mDate) {
    FileRecord* fr = (FileRecord*)malloc(sizeof(FileRecord));
    /*malloc komutuyla bilgisayara "Bana þu kadar byte'lýk bir yer ayýr, buraya yeni bir dosya sýðdýracaðým" diyoruz. 
	Fonksiyon, oluþturduðu bu "yerin" adresini (pointer) döndürüyor.*/
    strncpy(fr->name, name, 100);
    fr->name[100] = '\0';
    strncpy(fr->ext, ext, 10);
    fr->ext[10] = '\0';
    fr->sizeMB = sizeMB;
    strcpy(fr->createDate, cDate);
    strcpy(fr->modDate, mDate);
    // atama iþlemleri
    return fr;
}

void destroyRecord(FileRecord* record) { free(record); }
/*Ýþimiz bittiðinde, "Artýk bu dosyaya ihtiyacým yok, bu alaný belleðe geri ver" diyoruz.
Eðer bunu yapmazsak, sisteminiz sürekli RAM tüketir (buna bellek sýzýntýsý denir).*/
const char* getFileName(FileRecord* record) { return record->name; }
const char* getFileExt(FileRecord* record) { return record->ext; }
double getFileSizeMB(FileRecord* record) { return record->sizeMB; }
const char* getCreateDate(FileRecord* record) { return record->createDate; }
const char* getModDate(FileRecord* record) { return record->modDate; }

void setModDate(FileRecord* record, const char* newDate) {
    if (record != NULL) strcpy(record->modDate, newDate);
}
/*FileRecord'un içindeki verilere dýþarýdan (örneðin main.c içinden) direkt eriþmek yerine, bu "kapýcý" fonksiyonlarý kullanýyoruz. 
Bu, kodumuzun bozulmasýný engeller; güvenli bir yöntemdir.*/

void printRecord(FileRecord* record) {
	//Verileri ham haliyle deðil, bir tablo gibi düzgün görünmesi için hizalayarak (tablo satýrý gibi) yazdýrýyoruz.
    printf("%-25s %-8s %-10.2f %-15s %-15s\n", 
           record->name, record->ext, record->sizeMB, 
           record->createDate, record->modDate);
}
