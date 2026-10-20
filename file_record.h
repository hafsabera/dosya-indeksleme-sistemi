#ifndef FILE_RECORD_H
#define FILE_RECORD_H
//bu dosyanýn projeye birden fazla kez dahil edilmesini engeller.

typedef struct FileRecord FileRecord;
/* bir opak iþaretçi kullanýmýdýr. 
FileRecord'un içindeki deðiþkenlerin (ad, boyut gibi) neler olduðunu burada deðil, .c dosyasýnda gizli tutuyoruz. 
Bu sayede, FileRecord'un yapýsýný deðiþtirirsek (örneðin dosya sahibi bilgisi eklerseniz),
bu yapýyý kullanan diðer dosyalarý (main.c gibi) yeniden derlemek zorunda kalmayýz.*/

FileRecord* createRecord(const char* name, const char* ext, double sizeMB, const char* cDate, const char* mDate);
//Bir dosyayý temsil eden yeni bir nesne oluþturur. Ad, uzantý, boyut ve tarihleri parametre olarak alýr ve bellekten yer ayýrýp yeni kaydý döndürür.
void destroyRecord(FileRecord* record);
//Bellekte oluþturulan bir kayýtla iþiniz bittiðinde, o kayýt için ayrýlan belleði free komutuyla serbest býrakýr. Bellek sýzýntýlarýný önlemek için kritiktir.

const char* getFileName(FileRecord* record); //Dosyanýn ismini döndürür.
const char* getFileExt(FileRecord* record); //Dosya uzantýsýný döndürür.
double getFileSizeMB(FileRecord* record); //Dosyanýn boyutunu (double olarak) döndürür.
const char* getCreateDate(FileRecord* record); //Dosyanýn oluþturulma tarihini döndürür.
const char* getModDate(FileRecord* record); //Dosyanýn son deðiþtirilme tarihini döndürür.
void setModDate(FileRecord* record, const char* newDate); //Dosyanýn deðiþtirilme tarihini dýþarýdan güncelleyebilmenizi saðlar.

void printRecord(FileRecord* record);
//Bu fonksiyon, tek bir dosya kaydýnýn bilgilerini (örneðin: Dosya.txt | 5MB | 20.04.2026) düzenli bir formatta ekrana basar.
#endif

/*file_record.h dosyasý, bir "Veri Nesnesi" modelidir.

Sistemdeki Hiyerarþi:

Main: Kullanýcýdan girdileri alýr.

FileManager: FileRecord nesnelerini bir liste (Linked List/Array) halinde toplar ve yönetir.

FileRecord: Tek bir dosyanýn bilgilerini (ad, tarih, boyut) güvenli bir þekilde saklar.*/
