#ifndef FILE_MANAGER_H //Eðer FILE_MANAGER_H daha önce tanýmlanmadýysa, aþaðýdaki kodlarý derlemeye dahil et demektir.
#define FILE_MANAGER_H //Bu sembolü tanýmlar. Bu teknik, dosyanýn bir projede yanlýþlýkla birden fazla kez dahil edilmesini (include edilmesini) ve çakýþma yaþanmasýný engeller.

#include "file_record.h" //FileManager içinde kullanýlacak olan dosya verilerinin (muhtemelen FileRecord struct'ý) tanýmlandýðý dosyayý dahil eder.

// FileManager yapýsýnýn tanýmý
typedef struct FileManager FileManager; /*Bu, opak iþaretçi denilen bir yöntemdir.
 FileManager yapýsýnýn içeriðini (struct'ýn içindeki deðiþkenleri) burada deðil, .c dosyasýnda tanýmlayacaðýnýzý belirtir. 
 Kullanýcý tarafý FileManager yapýsýnýn detaylarýný görmez, sadece bir "yönetici" nesnesi olduðunu bilir. Bu, kapsülleme prensibidir.*/

// Temel sistem fonksiyonlarý
FileManager* createManager(); //Hafýzada yeni bir dosya yöneticisi oluþturur ve onun adresini döndürür.
void addFile(FileManager* mgr, const char* name, const char* ext, double sizeMB, const char* cDate);//Listeye yeni bir dosya kaydý ekler. Parametre olarak isim, uzantý, boyut ve tarih alýr.
void deleteFile(FileManager* mgr, const char* name); //Ýsmine göre dosyayý listeden siler.
void searchFile(FileManager* mgr, const char* name); //Belirtilen isimdeki dosyayý arar ve bilgilerini ekrana basar.
void listAllFiles(FileManager* mgr); //Sistemdeki tüm dosyalarý döngüye girerek listeler.
void sortFilesBySize(FileManager* mgr); //Dosyalarý boyutlarýna göre küçükten büyüðe sýralar.
void updateFileDate(FileManager* mgr, const char* name, const char* newDate); //Ýlgili dosyanýn tarihini günceller.
double calculateTotalSize(FileManager* mgr); //Tüm dosyalarýn boyutlarýný toplayýp sistemin doluluk oranýný MB cinsinden döndürür.
void deleteAllFiles(FileManager* mgr); //Sistemdeki tüm dosyalarý temizler (hafýzayý boþaltýr).

// Kalýcýlýk için eklediðimiz dosya fonksiyonlarý
void saveToFile(FileManager* mgr, const char* filename); //Hafýzadaki tüm verileri filename isimli metin dosyasýna yazar.
void loadFromFile(FileManager* mgr, const char* filename); //Program açýlýrken filename dosyasýndaki verileri okur ve hafýzadaki FileManager yapýsýna yükler.

#endif //Dosyanýn sonuna gelindiðinde bloðu kapatýr.

/*Bu .h dosyasý, bir "menü" gibidir. 
main.c dosyanýz, "Bana addFile fonksiyonunu ver" dediðinde, bu baþlýk dosyasý sayesinde addFile fonksiyonunun nasýl bir parametre almasý gerektiðini bilir.*/
