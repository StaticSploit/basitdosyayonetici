#include <stdio.h>
#include <dirent.h>
#include <string.h>

void dosyalisteleme(const char* dizin)
{
    DIR* dir;
    struct dirent* ent;
    
    dir = opendir(dizin);
    if (dir == NULL)
    {
        printf("Dizin bo� veya a��lamad�\n");
        return;
    }
    
    printf("Dosyalar:\n");
    while ((ent = readdir(dir)) != NULL) {
        printf("%s\n", ent->d_name);
    }

    closedir(dir);
}

void dosyaolusturma(const char* dosyadizinveismi)
{
    FILE* dosya = fopen(dosyadizinveismi, "w");
    if (dosya == NULL) 
    {
        printf("Dosya olu�turulamad�\n");
        return;
    }
    fclose(dosya);
    printf("Dosya olu�turuldu: %s\n", dosyadizinveismi);
}

void dosyasilme(const char* dosyavedizinismi)
{
    if (remove(dosyavedizinismi) == 0)
    {
        printf("Dosya ba�ar�yla silindi: %s\n", dosyavedizinismi);
    } 
    else
    {
        printf("Dosya silme hatas�: %s\n", dosyavedizinismi);
    }
}

void dosyakopyalamatasima(const char* kaynak, const char* hedef)
{
    FILE* kaynakdosya = fopen(kaynak, "r");
    FILE* hedefdosya = fopen(hedef, "w");
    
    if (kaynakdosya == NULL) 
    {
        printf("Hata: Kaynak dosya bulunamad�\n");
        return;
    }
    
    int karakter;
    while ((karakter = fgetc(kaynakdosya)) != EOF)
    {
        fputc(karakter, hedefdosya);
    }

    fclose(kaynakdosya);
    fclose(hedefdosya);
    
    printf("Dosya kopyalama/tas�ma i�lemi tamamland�\n");
}

void dosyaara(const char* hedefdizin, const char* aranandosyaismi)
{
    DIR* dir;
    struct dirent* ent;
    
    dir = opendir(hedefdizin);
    if (dir == NULL)
    {
       printf("Dizin a��lamad�\n");
       return;
    }     
    
    printf("Aranan dosyalar:\n");
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, aranandosyaismi) == 0)
        {
            printf("%s\n", ent->d_name);
        }
    }
    
    closedir(dir);
}

int main() 
{
    int cevap;
    printf("Merhaba, dosya y�neticisi uygulamas�na ho� geldiniz\n");
    printf("1 - Belirtilen klas�rdeki dosyalar� listeleme\n");
    printf("2 - Belirtilen klas�rde dosya olu�turma/silme\n");
    printf("3 - Dosya ta��ma ve ba�ka bir dizine kopyalama\n");
    printf("4 - Dosya arama\n");
    printf("Ne yapmak istersiniz: ");
    scanf("%d", &cevap);
    
    switch (cevap)
    {
        case 1:
            {
                char hedefdizin[100];
                printf("L�tfen hedef dizini girin: ");
                scanf("%s", hedefdizin);
                dosyalisteleme(hedefdizin);
            }
            break;
        case 2:
            {
                int secim;
                printf("Dosya olu�turmak m� silmek mi? (1-Olu�turmak, 2-Silmek): ");
                scanf("%d", &secim);
                if (secim == 1)
                {
                    char dosyaismi[100];
                    printf("Dosya ismi ve dizini: ");
                    scanf("%s", dosyaismi);
                    dosyaolusturma(dosyaismi);
                }
                else if (secim == 2)
                {
                    char dosyaismi[100];
                    printf("Dosya ismi ve dizini: ");
                    scanf("%s", dosyaismi);
                    dosyasilme(dosyaismi);
                }
                else
                {
                    printf("Ge�ersiz se�im\n");
                }
            }
            break;
        case 3:
            {
                char kaynak[100];
                char hedef[100];
                printf("Kaynak dosya: ");
                scanf("%s", kaynak);
                printf("Hedef dosya: ");
                scanf("%s", hedef);
                dosyakopyalamatasima(kaynak, hedef);
            }
            break;
        case 4:
            {
                char hedefdizin[100];
                char aranandosya[100];
                printf("Hedef dizin: ");
                scanf("%s", hedefdizin);
                printf("Aranacak dosya: ");
                scanf("%s", aranandosya);
                dosyaara(hedefdizin, aranandosya);
            }
            break;
        default:
            printf("Ge�ersiz i�lem\n");
            break;
    }
    
    return 0;
}
