#include <stdio.h> //Standart giriþ-çýkýþ iþlemleri (printf, scanf, fgets gibi) için gereklidir.
#include <string.h> //Karakter dizileri (string) üzerinde iþlemler (strlen gibi) yapmak için kullanýlýr.
#include "file_manager.h" //Projenin temel fonksiyonlarýný barýndýran yazdýðýmýz özel baþlýk dosyasýdýr.

void centerText(const char* text) {
    int width = 80;    //Ekranýn varsayýlan geniþliðini belirler
    int len = strlen(text);   //Gönderilen metnin uzunluðunu hesaplar.
    int padding = (width - len) / 2;   //Metni ortalamak için gereken boþluk sayýsýný hesaplar.
    int i;
    if (padding < 0) padding = 0;
    for (i = 0; i < padding; i++) printf(" ");   //Hesaplanan boþluk kadar ekrana boþluk karakteri basar ve ardýndan metni yazdýrýr.
    printf("%s\n", text);
}

void trim(char* str) { //fgets kullanýldýðýnda metnin sonuna \n (yeni satýr) karakteri eklenir. trim fonksiyonu, string'in son karakteri \n ise onu \0 (null karakteri) ile deðiþtirerek temizler.
    size_t len = strlen(str);
    if(len > 0 && str[len-1] == '\n') str[len-1] = '\0';
}

int main() {
    FileManager* mySystem = createManager(); //Dosya sistemini yönetmek için gerekli olan yapýyý memory'de yer ayýrarak oluþturur.
    int choice;
    char name[150], ext[20], cDate[30], mDate[30];
    double sizeMB;

    while(1) {  //Sonsuz bir döngü baþlatýr; bu sayede kullanýcý "0" ile çýkana kadar program sürekli çalýþýr.
        printf("\n\n");
        //centerText kullanýlarak menü seçenekleri düzenli bir þekilde ekrana basýlýr.
        centerText("**************************************************");
        centerText("*     DOSYA YONETIM SISTEMI     *");
        centerText("**************************************************");
        centerText("1. Yeni Dosya Kaydi Olustur                       ");
        centerText("2. Sistemdeki Tum Dosyalari Listele               ");
        centerText("3. Dosyalari Boyuta Gore Sirala                   ");
        centerText("4. Isim ile Dosya Sorgulama                       ");
        centerText("5. Kayitli Bir Dosyayi Sil                        ");
        centerText("6. Dosya Degistirilme Tarihini Guncelle           ");
        centerText("7. Sistem Kapasite Durumunu Gor                   ");
        centerText("8. Tum Listeyi Kalici Olarak Temizle              ");
        centerText("0. Sistemden Guvenli Cikis                        ");
        centerText("**************************************************");
        
        printf("\n               Seciminiz: ");
        if(scanf("%d", &choice) != 1) { //scanf("%d", &choice) ile kullanýcýnýn seçimini alýr.
            while(getchar() != '\n'); // getchar(); ise scanften kalan "enter" karakterini temizleyerek bir sonraki fgets iþleminin hata vermesini önler. 
            continue;
        }
        getchar();/*scanf kullanýmý sonrasýnda getchar() kullanarak giriþ tamponunu temizliyor. 
		Bu, C dilinde çok önemli bir pratiktir, aksi takdirde sonraki fgets komutlarý "enter" tuþunu okuyup kullanýcýdan veri almadan geçebilirdi.*/
		
//Program, kullanýcýnýn seçimine göre ilgili fonksiyonu file_manager.h üzerinden çaðýrýr
        if(choice == 1) {
        	
        	/*Kullanýcýdan isim, uzantý, boyut ve tarih verilerini alýr.
			 do-while döngüleri ile hatalý giriþleri engeller (örn: 100 karakterden uzun isim veya negatif boyut girilemez).
			  Veriler alýndýktan sonra addFile ile listeye ekler ve saveToFile ile verileri veriler.txt dosyasýna yazar.*/
			  
            printf("\n--- Yeni Dosya Ekleme ---\n");
            do {
                printf("Isim: "); fgets(name, 100, stdin); trim(name);
                if(isValidName(name) == -1) printf("[HATA] Isim 100 karakterden uzun olamaz!\n");
                else if(isValidName(name) == 0) printf("[HATA] Isimde yasakli karakter kullanilamaz!\n");
            } while(isValidName(name) != 1);
            //isValidName ve isValidDate fonksiyonlarý, kullanýcýdan alýnan verilerin mantýksal olarak doðru olduðunu garantiler.

            printf("Uzanti: "); fgets(ext, 10, stdin); trim(ext);
            
            do {
                printf("Boyut (MB): ");
                if(scanf("%lf", &sizeMB) != 1) { while(getchar() != '\n'); sizeMB = 0; }
                getchar();
                if(sizeMB <= 0) printf("[HATA] Boyut 0 veya negatif olamaz!\n");
                else if(sizeMB > 1024.0) printf("[HATA] Tek dosya 1 GB sinirini asamaz!\n");
            } while(sizeMB <= 0 || sizeMB > 1024.0);

            do {
                printf("Tarih (GG.AA.YYYY): "); fgets(cDate, 20, stdin); trim(cDate);
                if(!isValidDate(cDate)) printf("[HATA] Gecersiz tarih formati!\n");
            } while(!isValidDate(cDate));
            //isValidName ve isValidDate fonksiyonlarý, kullanýcýdan alýnan verilerin mantýksal olarak doðru olduðunu garantiler.

            addFile(mySystem, name, ext, sizeMB, cDate);
            saveToFile(mySystem, "veriler.txt"); // Dosya eklenince kaydet
        }
        else if(choice == 2) {
        	//listAllFiles fonksiyonu ile mevcut tüm dosyalarý ekrana yazdýrýr.
        	printf("\n--- Mevcut Dosya Listesi ---\n");
            listAllFiles(mySystem);
        }
        else if(choice == 3) {
        	//sortFilesBySize ile dosyalarý boyuta göre dizip listAllFiles ile ekrana basar.
        	printf("\n--- Boyuta Gore Dosya Listesi ---\n");
            sortFilesBySize(mySystem);
            listAllFiles(mySystem);
        }
        else if(choice == 4) {
        	//searchFile ile isme göre dosya arar.
            do {
                printf("\nSorgulanacak Dosya Ismi: "); fgets(name, 100, stdin); trim(name);
                if(isValidName(name) != 1) printf("[HATA] Gecersiz isim!\n");
            } while(isValidName(name) != 1);
            searchFile(mySystem, name);
        }
        else if(choice == 5) {
        	//Ýsim doðrulamasý yaptýktan sonra deleteFile ile ilgili dosyayý listeden kaldýrýr ve dosyayý güncelleyerek kaydeder.
            do {
                printf("\nSilinecek Dosya Ismi: "); fgets(name, 100, stdin); trim(name);
                if(isValidName(name) != 1) printf("[HATA] Gecersiz isim!\n");
            } while(isValidName(name) != 1);
            deleteFile(mySystem, name);
            saveToFile(mySystem, "veriler.txt"); // Silince kaydet
        }
        else if(choice == 6) {
        	//Mevcut bir dosyanýn tarihini deðiþtirmek için updateFileDate fonksiyonunu kullanýr.
            do {
                printf("\nGuncellenecek Dosya Ismi: "); fgets(name, 100, stdin); trim(name);
                if(isValidName(name) != 1) printf("[HATA] Gecersiz isim!\n");
            } while(isValidName(name) != 1);
            //isValidName ve isValidDate fonksiyonlarý, kullanýcýdan alýnan verilerin mantýksal olarak doðru olduðunu garantiler.
            
            do {
                printf("Yeni Tarih (GG.AA.YYYY): "); fgets(mDate, 20, stdin); trim(mDate);
                if(!isValidDate(mDate)) printf("[HATA] Gecersiz tarih formatý!\n");
            } while(!isValidDate(mDate));
            //isValidName ve isValidDate fonksiyonlarý, kullanýcýdan alýnan verilerin mantýksal olarak doðru olduðunu garantiler.
            updateFileDate(mySystem, name, mDate);
            saveToFile(mySystem, "veriler.txt"); // Güncelleme sonrasý kaydet
        }
        else if(choice == 7) {
        	/*calculateTotalSize ile toplam kullanýlan alaný hesaplar. 
			8192 MB (8 GB) sýnýrý üzerinden kalan boþluðu ve yüzde doluluk oranýný hesaplayýp ekrana detaylý rapor verir.*/
			
            double current = calculateTotalSize(mySystem);
            printf("\n--------------------------------------------------");
            printf("\n       SISTEM KAPASITE BILGISI (8 GB SINIRI)");
            printf("\n--------------------------------------------------");
            printf("\nKullanilan Alan : %.2f MB", current);
            printf("\nKalan Kapasite  : %.2f MB", 8192.0 - current);
            printf("\nDoluluk Orani   : %%%.2f", (current / 8192.0) * 100);
            printf("\n--------------------------------------------------\n");
        }
        else if(choice == 8) {
        	//deleteAllFiles ile tüm listeyi hafýzadan siler ve veriler.txt dosyasýný boþaltýr.
            deleteAllFiles(mySystem);
            saveToFile(mySystem, "veriler.txt"); // Temizleme sonrasý kaydet
        }
        else if(choice == 0) {
        	//break; komutu ile while döngüsünü sonlandýrýr ve programý kapatýr.
            printf("\n");
            centerText("Sistem kapatiliyor...");
            break;
        }
        else {
            printf("\n[UYARI] Gecersiz secim! Lutfen listedeki rakamlardan birini girin.\n");
        }
    }
    return 0;
}
