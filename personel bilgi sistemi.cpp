#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <locale.h> 



#define MAX_PATH        80
#define INVALID         0




struct PERSON{
	char isim[100];
	long int TCKimlikNo;
	long int telefon;
	char eposta[100];
	char adres[100];
 };


int  Menu(void);
void Ekle(void);
void Listele(void);
void IsimAra(void);
void TCAra(void);
void Sil(void);
void Duzenle(void);


FILE *f;
char fname[MAX_PATH];


void Ekle(void)
{
    PERSON per;
    fflush(stdin);
    printf("Adi soyadi....: ");		gets(per.isim); fflush(stdin);
    printf("TC No.........: ");		scanf("%lu", &per.TCKimlikNo); fflush(stdin);
    printf("Telefon.......: ");		scanf("%lu", &per.telefon); fflush(stdin);
    printf("E-Posta.......: ");		gets(per.eposta); fflush(stdin);//daha düzgün veri girilmesi için
    printf("Adres.........: ");		gets(per.adres); fflush(stdin);
    
    fseek(f, 0, SEEK_END);
    fwrite(&per, sizeof(PERSON), 1, f);
}

void IsimAra(void)
{
    PERSON per;
    char isim[30];
    
    printf("lütfen kayit ismini giriniz :");
    fflush(stdin);
    gets(isim);
    fseek(f, 0, SEEK_SET);
    while (fread(&per, sizeof(PERSON), 1, f) > 0) {
    	//ayný mý diye kontrolü
        if (!stricmp(per.isim, isim)) {
            	printf("Adi soyadi....: %s\nTC No.........: %lu\nTelefon.......: %lu\nE-Posta.......: %s\nAdres.........: %s",per.isim,per.TCKimlikNo, per.telefon,per.eposta,per.adres);
            	printf("\n\n");
			return;
        }
    }    
    printf("Kayit bulunamadi...");
}

void TCAra(void)
{
    PERSON per;
    long int tc;
    
    printf("lütfen kayit TC sini giriniz :");
    fflush(stdin);
    scanf("%lu",&tc);
    fseek(f, 0, SEEK_SET);
    while (fread(&per, sizeof(PERSON), 1, f) > 0) {
        
        if (per.TCKimlikNo == tc) {
            	printf("Adi soyadi....: %s\nTC No.........: %ld\nTelefon.......: %ld\nE-Posta.......: %s\nAdres.........: %s",per.isim,per.TCKimlikNo, per.telefon,per.eposta,per.adres);
              	printf("\n\n");
			return;
        }
    }
  
    printf("Kayit bulunamadi...");
}

void Listele(void)
{
	printf("\n\n");
    PERSON per;
    fseek(f, 0L, SEEK_SET);//baþtan baþla aramaya
    while (fread(&per, sizeof(PERSON), 1, f) > 0) {
	    printf("Adi soyadi....: %s\nTC No.........: %lu\nTelefon.......: %lu\nE-Posta.......: %s\nAdres.........: %s",per.isim,per.TCKimlikNo, per.telefon,per.eposta,per.adres);
    }
    printf("\n\n");
}

void Sil(void)
{
    char isim[30];
    PERSON per;

    printf("Silinecek kayitin adi ve soyadi : ");
    fflush(stdin);
    gets(isim);
    fseek(f, 0, SEEK_SET);
    while (fread(&per, sizeof(PERSON), 1, f) > 0) {
        if (!stricmp(per.isim, isim)) {
            fseek(f, -(long)sizeof(PERSON), 1);
            fwrite(&per, sizeof(PERSON), 1, f);
            printf("Kayit silindi!..\n");
            return;
        }
    }
    printf("Silinecek kayit bulunamadi");
}

void Duzenle(void)
{
    char isim[30];
    PERSON per;

    printf("Degistirilecek kayitin adi ve soyadi : ");
    fflush(stdin);
    gets(isim);
    fseek(f, 0, SEEK_SET);
    while (fread(&per, sizeof(PERSON), 1, f) > 0) {
        if (!stricmp(per.isim, isim)) {
   			printf("Adi soyadi....: ");		gets(per.isim);fflush(stdin);
    		printf("TC No.........: ");		scanf("%lu", &per.TCKimlikNo);fflush(stdin);
		    printf("Telefon.......: ");		scanf("%lu", &per.telefon);fflush(stdin);
		    printf("E-Posta.......: ");		gets(per.eposta);fflush(stdin);
		    printf("Adres.........: ");		gets(per.adres);fflush(stdin);
		    fseek(f, -(long)sizeof(PERSON), 1);
            fwrite(&per, sizeof(PERSON), 1, f);
            return;
        }
    }
    printf("Degistirilecek kayit bulunamadi.");
}

int Menu(void)
{
    int option;

    printf("1) Kayit Ekle\n");
    printf("2) Personel Listele\n");
    printf("3) Kaydi Duzenle\n");
    printf("4) TC Kimlik No ile Kayit Bul\n");
    printf("5) Isim ile Kayit Bul\n");
    printf("6) Kayit Sil\n");
    printf("0) Cikis\n");
    printf("\nSeciminiz :");
    scanf("%d", &option);
    if (option < -1 || option >6)
        return INVALID;
    return option;
}




int main()
{
//	setlocale(LC_ALL, "Turkish");
    int menu;
    if ((f = fopen("personel.txt", "r+b")) == NULL){
        if ((f = fopen("personel.txt", "w+b")) == NULL) {
            exit(EXIT_FAILURE);
        }
    }
    strcpy(fname,"personel.txt");
    for (;;) {
        menu = Menu();
    	switch (menu) {
            case 1  : Ekle(); break;
            case 2  : Listele(); break;
            case 3  : Duzenle(); break;
        	case 4  : TCAra(); break;
			case 5  : IsimAra(); break;
            case 6  : Sil(); break;
            case 0  : exit(0); break; 
            default : printf("Geçersiz Seçenek!..\n"); break;
        }
    }
    exit(0);
    fclose(f);
    return 0;
}

