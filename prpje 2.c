#include <stdio.h>
#include <stdlib.h>


struct Urun {
    int id;
    char ad[50];
    int adet;
    double fiyat;
};


void depoGoruntule(FILE *dosya) {
    struct Urun urun;

    printf("%-5s %-20s %-10s %-10s\n", "ID", "Ad", "Adet", "Fiyat");

    rewind(dosya);


    while (fscanf(dosya, "%d %s %d %lf", &urun.id, urun.ad, &urun.adet, &urun.fiyat) == 4) {
        printf("%-5d %-20s %-10d %-10.2f\n", urun.id, urun.ad, urun.adet, urun.fiyat);
    }
}


double depotoplamDeger(FILE *dosya) {
    struct Urun urun;
    double toplamDeger = 0.0;

    rewind(dosya);


    while (fscanf(dosya, "%d %s %d %lf", &urun.id, urun.ad, &urun.adet, &urun.fiyat) == 4) {
        toplamDeger += urun.adet * urun.fiyat;
    }

    return toplamDeger;
}


void urunEkle(FILE *dosya) {
    struct Urun urun;

    printf("Yeni urun bilgilerini girin:\n");
    printf("ID: ");
    scanf("%d", &urun.id);

    printf("Ad: ");
    scanf("%s", urun.ad);

    printf("Adet: ");
    scanf("%d", &urun.adet);

    printf("Fiyat: ");
    scanf("%lf", &urun.fiyat);


    fprintf(dosya, "%d %s %d %.2f\n", urun.id, urun.ad, urun.adet, urun.fiyat);
    printf("Urunu basariyla eklendiniz!\n");
}


void urunSil(FILE *dosya, int hedefId) {
    FILE *geciciDosya = fopen("gecici.txt", "w");
    if (geciciDosya == NULL) {
        printf("Gecici dosya olusturulamadi.\n");
        exit(4);
    }

    struct Urun urun;

    rewind(dosya);


    while (fscanf(dosya, "%d %s %d %lf", &urun.id, urun.ad, &urun.adet, &urun.fiyat) == 4) {
        if (urun.id != hedefId) {
            fprintf(geciciDosya, "%d %s %d %.2f\n", urun.id, urun.ad, urun.adet, urun.fiyat);
        }
    }

    fclose(dosya);
    fclose(geciciDosya);

    remove("depo.txt");
    rename("gecici.txt", "depo.txt");

    printf("ID %d'li urunu basariyla silindi!\n", hedefId);
}

int main() {
    FILE *dosya = fopen("depo.txt", "a+");
    if (dosya == NULL) {
        printf("Dosya acilamadi.\n");
        exit(4);
    }

    int secim, hedefId;

    do {

        printf("\nDepo Takip Sistemi\n");
        printf("1. Depo Goruntule\n");
        printf("2. Urun Ekle\n");
        printf("3. Urun Sil\n");
        printf("4. Depo Toplam Deger Hesapla\n");
        printf("5. Cikis\n");
        printf("Seciminizi girin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                depoGoruntule(dosya);
                break;
            case 2:
                urunEkle(dosya);
                break;
            case 3:
                printf("Silinecek urunun ID'sini girin: ");
                scanf("%d", &hedefId);
                urunSil(dosya, hedefId);
                break;
            case 4:
                printf("Depo Toplam Degeri: %.2f\n", depotoplamDeger(dosya));
                break;
            case 5:
                printf("Programdan cikiliyor. Hosca kal!\n");
                break;
            default:
                printf("Gecersiz secim. Lutfen gecerli bir secenek girin.\n");
        }
    } while (secim != 5);

    fclose(dosya);

    return 0;
}
