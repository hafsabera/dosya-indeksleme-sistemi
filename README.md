================================================================================
                    MODULER DOSYA INDEKSLEME SISTEMI
           Derleme, Calistirma ve Kullanim Kilavuzu (README)
================================================================================
Bu kılavuz, projenin bilgisayarınızda sorunsuz bir şekilde kurulması, derlenmesi (çalışabilir hale getirilmesi) ve test edilmesi için hazırlanmıştır.
--------------------------------------------------------------------------------
1. PROJE DOSYA YAPISI
--------------------------------------------------------------------------------

Projenin moduler yapisini ve kapsulleme (encapsulation) kurallarini saglamak
icin kodlarimiz 5 ana dosyaya bolunmustur:

    main.c
        Ana menuyu ve kullanici ara yuzunu yoneten merkez dosya.

    file_manager.c & file_manager.h
        Dosya ekleme, silme, arama ve siralama islemlerinin yapildigi
        "Dosya Yoneticisi" modulu.

    file_record.c & file_record.h
        Tek bir dosyanin bilgilerini (isim, boyut, tarih) guvenle saklayan
        "Dosya Kaydi" modulu.

    veriler.txt
        Program kapandiginda verilerin kaybolmamasi icin sistem tarafindan
        otomatik olusturulan veri dosyasi.


--------------------------------------------------------------------------------
2. SISTEMI CALISTIRMA ADIMLARI
--------------------------------------------------------------------------------

Sistemi bilgisayarinizda calistirmak icin iki kolay yontemden birini
secebilirsiniz:


YONTEM A: Dev-C++ (veya benzeri bir IDE) ile Calistirma (En Kolay Yol)
---------------------------------------------------------------------------

Eger kodlari yazarken Dev-C++ programi kullaniyorsaniz su adimlari takip edin:

    1. Bilgisayarinizda bos bir klasor acin ve yukaridaki 5 dosyayi bu
       klasorun icine koyun.

    2. Dev-C++ uygulamasini acin ve
       File -> New -> Project...
       yolunu izleyerek yeni bir C Project (Console Application) olusturun.

    3. Olusturdugunuz bu projeyi, kodlarinizin oldugu klasore kaydedin.

    4. Sol taraftaki proje listesine sag tiklayarak "Add to Project" deyin
       ve klasordeki 3 adet .c ve 2 adet .h dosyasini projeye ekleyin.

    5. Ust menuden
       Tools -> Compiler Options -> Settings -> Code Generation
       kismina gelin. Language standard (-std) secenegini
       ISO C11 veya GNU C11 yapin.
       (Bu ayar, for dongulerimizin hatasiz calismasini saglar.)

    6. main.c sekmesi acikken klavyenizden F11 tusuna basarak programi
       derleyin ve calistirin.


YONTEM B: Terminal (Komut Satiri / GCC) ile Calistirma
-------------------------------------------------------

NOT: GCC, bilgisayarinizin C dilinde yazilmis kodlari anlayip programa
donusmesini saglayan derleyicinin addir.

Kodlarin oldugu klasorun icinde bir terminal (komut satiri) acarak su
komutlari yazmaniz yeterlidir:

    Windows Kullanicilari Icin Derleme ve Calistirma:
    -------------------------------------------------
        gcc main.c file_manager.c file_record.c -o dosya_sistemi.exe
        dosya_sistemi.exe

    Linux / macOS Kullanicilari Icin Derleme ve Calistirma:
    -------------------------------------------------------
        gcc main.c file_manager.c file_record.c -o dosya_sistemi
        ./dosya_sistemi

NOT: Derleme yaparken baslik dosyalarini (.h) komuta eklemenize gerek
yoktur; bilgisayar onlari kodun icindeki #include satirlarindan otomatik
bulur.


--------------------------------------------------------------------------------
3. ORNEK KULLANIM VE TEST SENARYOLARI
--------------------------------------------------------------------------------

Program basladiginda karsiniza 8 secenekli interaktif bir menu gelecektir.
Sistemin dogrulugunu teyit etmek icin asagidaki test adimlarini
uygulayabilirsiniz:

    1. Normal Durum (Dosya Ekleme):
       ------------------------------
       Menuden 1 secin. Isim olarak "rapor", uzanti olarak "pdf",
       boyut olarak "15.5" ve tarih olarak "15.05.2026" girin.
       Dosyanin basariyla eklendigini goreceksiniz.

    2. Yinelenen Kayit Engeli:
       ------------------------
       Az once eklediginiz "rapor" ismini tekrar eklemeyi deneyin.
       Sistem
           [HATA] Ayni isimde dosya zaten mevcut!
       uyarisi vererek islemi engelleyecektir.

    3. Tarih Kontrolu:
       -----------------------
       Yeni dosya eklerken tarih kismina "31.02.2026" gibi takvimde
       olmayan gecersiz bir tarih yazin. Sistem hatayi algilayip
       kaydi reddedecektir.

    4. Uc Durum (Bos Sistem Kontrolu):
       --------------------------------
       Eger sistemde hic dosya yoksa (veya veriler.txt bossa), silme
       veya arama yaptiginizda program cokmez, kibarca
           "Bulunamadi"
       uyarisi verir.


--------------------------------------------------------------------------------
4. GELISTIRICI BILGILERI
--------------------------------------------------------------------------------

    Ders           : BIL110 - Programlama ve Hesaplama II
    Ders Sorumlusu : Prof. Dr. Serdar Muldur

    Proje Ekibi:
        o Hafsa Bera Pekcan  (250205001)
        o Elif Casun         (250205014)
        o Gulbade Yildiz     (250206003)
        o Nuray Aliyeva      (250206901)


================================================================================
                              SON
================================================================================
