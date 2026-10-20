#include <stdio.h>//Standart giriþ-çýkýþ iþlemleri (printf, scanf, fgets gibi) için gereklidir.
#include <stdlib.h>//programlarýn bellek yönetimi, dönüþüm iþlemleri, sayý üretimi ve sistemle iletiþim gibi temel ihtiyaçlarýný karþýlayan fonksiyonlarý barýndýran bir baþlýk dosyasýdýr.
#include <string.h>//Karakter dizileri (string) üzerinde iþlemler (strlen gibi) yapmak için kullanýlýr.
#include "file_manager.h" //Projenin temel fonksiyonlarýný barýndýran yazdýðýmýz özel baþlýk dosyasýdýr.

#define MAX_SINGLE_FILE_LIMIT 1024.0 //bir dosya girerken girilebilecek en büyük mb sýnýrý
#define MAX_TOTAL_SYSTEM_LIMIT 8192.0 //tüm sistemin mb cinsinden kapasitesi

typedef struct Node {
    FileRecord* record;
    struct Node* next;
} Node;
//Node (Düðüm): Bir "vagon" gibidir. Ýçinde bir dosya kaydý (record) ve bir sonraki vagonun adresi (next) bulunur.
struct FileManager {
    Node* head;
};
//FileManager: Listenin baþýný (head) tutan bir bekçidir. head boþsa (NULL), liste boþtur.

// --- DOSYADAN YÜKLEME ---
void loadFromFile(FileManager* mgr, const char* filename) {
//loadFromFile: Program baþlarken çalýþýr. veriler.txt dosyasýný okur, her satýrý parçalar (sscanf) ve malloc ile hafýzada yeni bir düðüm oluþturup listeye ekler.
    FILE* file = fopen(filename, "r");
    if (!file) return;
    
    char line[300], name[150], ext[20], cDate[30], mDate[30];
    double size;
    
    while (fgets(line, sizeof(line), file)) {
        if(sscanf(line, "%[^|]|%[^|]|%lf|%[^|]|%s", name, ext, &size, cDate, mDate) == 5) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->record = createRecord(name, ext, size, cDate, mDate);
            newNode->next = mgr->head;
            mgr->head = newNode;
        }
    }
    fclose(file);
}

// --- DOSYAYA KAYDETME ---
void saveToFile(FileManager* mgr, const char* filename) {
//saveToFile: Listenin baþýndan sonuna kadar gezer (curr = curr->next), her bir düðümdeki bilgileri | karakteri ile ayýrarak metin dosyasýna yazar.
    FILE* file = fopen(filename, "w");
    if (!file) return;
    
    Node* curr = mgr->head;
    while (curr) {
        fprintf(file, "%s|%s|%.2f|%s|%s\n", 
            getFileName(curr->record), getFileExt(curr->record), 
            getFileSizeMB(curr->record), getCreateDate(curr->record), getModDate(curr->record));
        curr = curr->next;
    }
    fclose(file);
}

// --- TARÝH KONTROLÜ ---
int isValidDate(const char* dateStr) {
/*isValidDate: Tarihi GG.AA.YYYY formatýnda doðrular. 
Artýk yýllarý (þubatýn 29 çekmesi) ve her ayýn gün sýnýrlarýný hesaplayarak girilen tarihin takvimde var olup olmadýðýný anlar.*/
    int d, m, y;
    int len = strlen(dateStr);
    if (len < 8 || len > 10) return 0;
    int dotCount = 0;
    int i;
    for(i = 0; i < len; i++) if(dateStr[i] == '.') dotCount++;
    if(dotCount != 2) return 0;
    char extra;
    if (sscanf(dateStr, "%d.%d.%d%c", &d, &m, &y, &extra) != 3) return 0;
    if (y < 1900 || y > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) daysInMonth[2] = 29;
    if (d < 1 || d > daysInMonth[m]) return 0;
    return 1;
}

int isValidName(const char* name) {
//isValidName: Dosya isminde Windows veya Linux sistemlerinde yasaklý olan (<, >, :, vb.) karakterlerin olup olmadýðýný kontrol eder.
    if (strlen(name) > 100) return -1;
    const char* forbidden = "<>:\"/\\|?*";
    int i;
    for (i = 0; name[i] != '\0'; i++) if (strchr(forbidden, name[i])) return 0;
    return 1;
}

FileManager* createManager() {
//createManager: Sistemi baþlatýr. head deðerini NULL yaparak boþ bir liste baþlatýr ve varsa kayýtlý dosyalarý diski okuyarak listeye yükler.
    FileManager* mgr = (FileManager*)malloc(sizeof(FileManager));
    mgr->head = NULL;
    loadFromFile(mgr, "veriler.txt"); //kayýt et
    return mgr;
}

double calculateTotalSize(FileManager* mgr) { 
    double total = 0;// 1. Baþlangýçta toplamý 0 olarak belirle.
    Node* curr;// 2. Listeyi gezmek için bir "geçici iþaretçi" (curr) tanýmla.
    // 3. Döngü (Listenin baþýndan sonuna kadar gez)
    // curr = mgr->head : Listenin baþýndan baþla.
    // curr != NULL    : " curr boþ deðilse (listenin sonuna gelmediysen) devam et" demektir.
    // curr = curr->next : Her adýmda bir sonraki düðüme (vagon) geç.
    for (curr = mgr->head; curr != NULL; curr = curr->next) total += getFileSizeMB(curr->record);
    // 4. Boyutu ekle
    // getFileSizeMB(curr->record): O anki düðümdeki dosyanýn boyutunu al.
    // total += ... : Bunu mevcut toplama ekle.
    return total;// Hesaplanan toplam boyutu döndür.
}

void addFile(FileManager* mgr, const char* name, const char* ext, double sizeMB, const char* cDate) {
    // 1. AYNI ÝSÝM KONTROLÜ
    Node* check = mgr->head;
    while(check) { // Listenin baþýndan sonuna kadar gez
        if(strcmp(getFileName(check->record), name) == 0) { // Eðer ayný isimde kayýt varsa
            printf("\n[HATA] '%s' isminde bir dosya zaten mevcut!\n", name); 
            return; // Fonksiyondan çýk, ekleme yapma
        }
        check = check->next; // Bir sonraki düðüme geç
    }

    // 2. DÝÐER KONTROLLER
    // Boyut 0'dan küçük mü? 1GB'dan büyük mü?
    if (sizeMB <= 0 || sizeMB > MAX_SINGLE_FILE_LIMIT) { printf("\n[HATA] Gecersiz boyut!\n"); return; }
    // Toplam sistem alaný 8GB'ý geçiyor mu?
    if (calculateTotalSize(mgr) + sizeMB > MAX_TOTAL_SYSTEM_LIMIT) { printf("\n[HATA] Kapasite asimi!\n"); return; }
    // Ýsimde yasak karakter var mý veya tarih hatalý mý?
    if (isValidName(name) != 1 || !isValidDate(cDate)) { printf("\n[HATA] Gecersiz isim veya tarih!\n"); return; }
    
    Node* newNode = (Node*)malloc(sizeof(Node)); // Bellekte yeni bir vagon ayýr
    newNode->record = createRecord(name, ext, sizeMB, cDate, cDate); // Bilgileri doldur
    newNode->next = mgr->head; // Yeni vagonu listenin baþýna tak
    mgr->head = newNode; // "Yeni baþ" artýk bu vagon oldu
    
    saveToFile(mgr, "veriler.txt"); // Diske kaydet
    printf("\n[BASARI] %s eklendi.\n", name);
}

void listAllFiles(FileManager* mgr) {
    if (!mgr->head) { printf("\nListe bos.\n"); return; } //liste boþ ise kayýtlý bir dosya bulunamadýysa
    Node* curr = mgr->head;
    printf("\n%-25s %-8s %-10s %-15s %-15s\n", "ISIM", "UZT", "MB", "OLUSTURMA", "DEGISTIRME"); //var olan dosyalarý listeler.
    printf("\n");
    while (curr) { printRecord(curr->record); curr = curr->next; }
}

void deleteFile(FileManager* mgr, const char* name) {
	// Silinecek düðümü bulana kadar ilerle (prev, silinecek olanýn bir öncesini tutar)
    Node *curr = mgr->head, *prev = NULL;
    while(curr && strcmp(getFileName(curr->record), name) != 0) { prev = curr; curr = curr->next; }
    if(!curr) { printf("\n[HATA] Bulunamadi.\n"); return; } // Hiç bulunamadýysa hata ver
    // Baðlantýyý kopar:
    if(!prev) mgr->head = curr->next; // Silinecek olan en baþtaysa, baþý bir sonrakine kaydýr
	else prev->next = curr->next; // Arada bir yerdeyse, öncesini sonrasýna baðla (aradaki curr'u devre dýþý býrak)
    destroyRecord(curr->record); 
	free(curr); // Sonra düðümü bellekten sil
    saveToFile(mgr, "veriler.txt"); // Dosyayý güncelle
    printf("\n[BASARI] Silindi.\n");
}
//dosya tarihi güncelleme kýsmý
void updateFileDate(FileManager* mgr, const char* name, const char* newDate) {
    if (!isValidDate(newDate)) return;
    Node* curr;
    for(curr = mgr->head; curr; curr = curr->next) {
        if(strcmp(getFileName(curr->record), name) == 0) { 
            setModDate(curr->record, newDate); 
            saveToFile(mgr, "veriler.txt");
            printf("\n[BASARI] Guncellendi.\n");
            return; 
        }
    }
    printf("\n[HATA] Bulunamadi.\n");
}

void sortFilesBySize(FileManager* mgr) {
    if (!mgr->head) return;
    Node* i;
    for (i = mgr->head; i != NULL; i = i->next) { // Her düðüm için
        Node* j;
        for (j = i->next; j != NULL; j = j->next) { // Geri kalan her düðümü karþýlaþtýr
            if (getFileSizeMB(i->record) > getFileSizeMB(j->record)) { // Eðer önündeki daha büyükse
                FileRecord* temp = i->record; i->record = j->record; j->record = temp; // Adresleri takas et (yer deðiþtirme)
            }
        }
    }
}
// Dosya arama kýsmý
void searchFile(FileManager* mgr, const char* name) {
    Node* curr;
    for(curr = mgr->head; curr; curr = curr->next) {
        if(strcmp(getFileName(curr->record), name) == 0) { printRecord(curr->record); return; }
    }
    printf("\n[HATA] Bulunamadi.\n");
}

void deleteAllFiles(FileManager* mgr) {
    Node* curr = mgr->head; 
    while(curr) { Node* next = curr->next; // Silmeden önce bir sonraki düðümü sakla
	destroyRecord(curr->record); // Kaydý yok et
	free(curr); // Düðümü hafýzadan at
	curr = next; } // Sakladýðýn düðüme geç
    mgr->head = NULL; // Artýk liste tamamen boþ
    saveToFile(mgr, "veriler.txt"); // Disk dosyasýný da boþalt
    printf("\n[SISTEM] Liste temizlendi.\n");
}
