#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    NormalBilet=1,
    OgrenciBileti
} BiletTipi;

typedef struct
{
    int SalonTipi;
    int KacinciMatine;
    int KoltukSayisi[50];
} Salon;

void SifreOlustur(FILE *OrjinalDosyaIsaretcisi, FILE *SifrelenmisIsaretci, int Sifre_Anahtar)
{
    char i;
    while((i = fgetc(OrjinalDosyaIsaretcisi)) != EOF)
    {
        fputc(i+Sifre_Anahtar, SifrelenmisIsaretci);
    }
    fclose(OrjinalDosyaIsaretcisi);
    fclose(SifrelenmisIsaretci);
}

void Desifrasyon(int Desifrasyon_Anahtar)
{
    FILE *IkinciDosyaIsaretcisi, *UcuncuDosyaIsaretcisi;

    if((IkinciDosyaIsaretcisi = fopen("SifrelenmisMetinBelgesi.txt", "r")) == NULL)
    {
        printf("Dosya acma hatasi ile karsilasildi.");
        exit(1);
    }

    if((UcuncuDosyaIsaretcisi = fopen("SonOrjinalMetinBelgesi.txt", "w")) == NULL)
    {
        printf("Dosya acma hatasi ile karsilasildi.");
        exit(1);
    }

    char j;

    while((j = fgetc(IkinciDosyaIsaretcisi)) != EOF)
    {
        fputc(j-Desifrasyon_Anahtar, UcuncuDosyaIsaretcisi);
    }

    fclose(IkinciDosyaIsaretcisi);
    fclose(UcuncuDosyaIsaretcisi);

    if((UcuncuDosyaIsaretcisi = fopen("SonOrjinalMetinBelgesi.txt", "r")) == NULL)
    {
        printf("Dosya acma hatasi ile karsilasildi.");
        exit(1);
    }

}

void SifreKontrolSaglama(FILE *SonOrjinalBelgeIsaretcisi)
{
    SonOrjinalBelgeIsaretcisi = fopen("SonOrjinalMetinBelgesi.txt","r");

    char DosyadanAlinanDeger[15], KlavyedenAlinanDeger[15];
    fscanf(SonOrjinalBelgeIsaretcisi, "%s", DosyadanAlinanDeger);

    printf("\n\t\t\t\t\tSINEMA OTOMASYONUNA HOS GELDINIZ\n\n");
    printf("Sifre: ");

    scanf("%s",KlavyedenAlinanDeger);

    if(strcmp(KlavyedenAlinanDeger,DosyadanAlinanDeger))
    {
        printf("\nHatali giris yaptiniz. Otomasyon kapanmistir.\n");
        exit(1);
    }

    fclose(SonOrjinalBelgeIsaretcisi);
}

void BiletIslemleri(BiletTipi biletTipi, Salon salon_sec)
{
    FILE *BiletSecimDosyaIsaretcisi;
    FILE *BiletIslemKontroluDosyaIsaretcisi;
    FILE *HasilatIsaretci;

    BiletSecimDosyaIsaretcisi = fopen("BiletSecimMetinBelgesi.txt", "a+");
    BiletIslemKontroluDosyaIsaretcisi = fopen("BiletSecimMetinBelgesi.txt", "r");
    HasilatIsaretci = fopen("HasilatMetinBelgesi.txt","a+");

    if(BiletSecimDosyaIsaretcisi == NULL)
    {
        printf("Bilet dosyasi acma hatasi ile karsilasildi.\n");
        exit(1);
    }

    printf("\n\nTam bilet icin 1'i, ogrenci bileti icin 2'yi seciniz.\nSeciminiz: ");
    scanf("%d",&biletTipi);

    int *KoltukSayisi_Isaretci, i, KoltukSayisi[50], KullanicininKoltukSecimi;
    int DosyadakiBiletTipi,DosyadakiSalonTipi,DosyadakiMatineBilgisi,DosyadakiSecilenKoltuk;

    if (biletTipi==1)
        printf("\nBilet ucretiniz 30 TL olacaktir.\n");
    else if (biletTipi==2)
        printf("\nBilet ucretiniz 20 TL olacaktir.\n");

    printf("\nSalon seciminizi yapiniz.\nRed icin 1, Green icin 2, Blue icin 3'u seciniz.");

    do
    {
        printf("\nSeciminiz: ");
        scanf("%d",&salon_sec.SalonTipi);
    }
    while(salon_sec.SalonTipi<1 || salon_sec.SalonTipi>3);

    printf("\nMatine seciminizi yapiniz.\n1-2-3-4-5 numarali matinelerden birisini seciniz.");

    do
    {
        printf("\nSeciminiz: ");
        scanf("%d",&salon_sec.KacinciMatine);
    }
    while(salon_sec.KacinciMatine<1 || salon_sec.KacinciMatine>5);

    printf("\n%d. salonun %d. matinesindeki filmi sectiniz.\n\n",salon_sec.SalonTipi,salon_sec.KacinciMatine);

    for(i=0;i<=49;i++)
    {
        KoltukSayisi_Isaretci=KoltukSayisi[i]=i+1;
        if(i!=49)
        printf("%d - ",KoltukSayisi_Isaretci);
    }
    printf("%d",50);

    printf("\n\nBu koltuklar arasindan seciminizi yapiniz.");

    do
    {
        printf("\nTercihiniz: ");
        scanf("%d",&KullanicininKoltukSecimi);
    }
    while(KullanicininKoltukSecimi<1 || KullanicininKoltukSecimi>50);

    while(!feof(BiletIslemKontroluDosyaIsaretcisi))
    {
        fscanf(BiletIslemKontroluDosyaIsaretcisi,"%d %d %d %d",&DosyadakiBiletTipi,&DosyadakiSalonTipi,&DosyadakiMatineBilgisi,&DosyadakiSecilenKoltuk);
        if(salon_sec.SalonTipi==DosyadakiSalonTipi)
        {
            if(salon_sec.KacinciMatine==DosyadakiMatineBilgisi)
            {
                if(KullanicininKoltukSecimi==DosyadakiSecilenKoltuk)
                {
                    printf("\nSecilen koltuk rezerve edilmistir.\n");
                    exit(1);
                }
            }
        }
    }

    printf("\nKoltugunuz rezerve edilmistir.\n");
    fprintf(BiletSecimDosyaIsaretcisi,"%d %d %d %d\n",biletTipi,salon_sec.SalonTipi,salon_sec.KacinciMatine,KullanicininKoltukSecimi);

    fprintf(HasilatIsaretci, "%d", biletTipi);

    fclose(BiletSecimDosyaIsaretcisi);
    fclose(BiletIslemKontroluDosyaIsaretcisi);
    fclose(HasilatIsaretci);
}

void HasilatIslemi(FILE *HasilatDosyaIsaretcisi)
{
    HasilatDosyaIsaretcisi = fopen("HasilatMetinBelgesi.txt","r");

    BiletTipi HasilatIcinBiletTayini;
    int TamBiletSayaci=0, OgrenciBiletiSayaci=0;
    int ToplamBiletAlanKisiSayisi=0, HasilatDegeri=0;

    while(!feof(HasilatDosyaIsaretcisi))
    {
        HasilatIcinBiletTayini=fgetc(HasilatDosyaIsaretcisi);
        if(HasilatIcinBiletTayini=='1')
        {
            TamBiletSayaci++;
            ToplamBiletAlanKisiSayisi++;
        }
        else if(HasilatIcinBiletTayini=='2')
        {
            OgrenciBiletiSayaci++;
            ToplamBiletAlanKisiSayisi++;
        }
    }

    HasilatDegeri = ((TamBiletSayaci*20)+(OgrenciBiletiSayaci*30));
    printf("\nSistemde bilet alan %d kisi mevcuttur.\n\nHasilat degeri: %d TL\n",ToplamBiletAlanKisiSayisi,HasilatDegeri);

    fclose(HasilatDosyaIsaretcisi);
}

void MatinelerinDolulukOranlari(FILE *BiletDosyaIsaretcisi)
{
    BiletDosyaIsaretcisi = fopen("BiletSecimMetinBelgesi.txt", "r");

    int Dosya_BiletTipi, Dosya_SalonTipi, Dosya_MatineBilgisi, Dosya_SecilenKoltuk;

    int S1M1=0, S1M2=0, S1M3=0, S1M4=0, S1M5=0;
    int S2M1=0, S2M2=0, S2M3=0, S2M4=0, S2M5=0;
    int S3M1=0, S3M2=0, S3M3=0, S3M4=0, S3M5=0;

    while(!feof(BiletDosyaIsaretcisi))
    {
        fscanf(BiletDosyaIsaretcisi, "%d%d%d%d", &Dosya_BiletTipi, &Dosya_SalonTipi, &Dosya_MatineBilgisi, &Dosya_SecilenKoltuk);
        if(Dosya_SalonTipi==1)
        {
            if(Dosya_MatineBilgisi==1)
            {
                S1M1++;
            }
            if(Dosya_MatineBilgisi==2)
            {
                S1M2++;
            }
            if(Dosya_MatineBilgisi==3)
            {
                S1M3++;
            }
            if(Dosya_MatineBilgisi==4)
            {
                S1M4++;
            }
            if(Dosya_MatineBilgisi==5)
            {
                S1M5++;
            }
        }
        if(Dosya_SalonTipi==2)
        {
            if(Dosya_MatineBilgisi==1)
            {
                S2M1++;
            }
            if(Dosya_MatineBilgisi==2)
            {
                S2M2++;
            }
            if(Dosya_MatineBilgisi==3)
            {
                S2M3++;
            }
            if(Dosya_MatineBilgisi==4)
            {
                S2M4++;
            }
            if(Dosya_MatineBilgisi==5)
            {
                S2M5++;
            }
        }
        if(Dosya_SalonTipi==3)
        {
            if(Dosya_MatineBilgisi==1)
            {
                S3M1++;
            }
            if(Dosya_MatineBilgisi==2)
            {
                S3M2++;
            }
            if(Dosya_MatineBilgisi==3)
            {
                S3M3++;
            }
            if(Dosya_MatineBilgisi==4)
            {
                S3M4++;
            }
            if(Dosya_MatineBilgisi==5)
            {
                S3M5++;
            }
        }
    }

    printf("\n1. Salon ve 1. Matine - %d kisi bilet satin almistir.",S1M1);
    printf("\n1. Salon ve 2. Matine - %d kisi bilet satin almistir.",S1M2);
    printf("\n1. Salon ve 3. Matine - %d kisi bilet satin almistir.",S1M3);
    printf("\n1. Salon ve 4. Matine - %d kisi bilet satin almistir.",S1M4);
    printf("\n1. Salon ve 5. Matine - %d kisi bilet satin almistir.",S1M5);
    printf("\n\n2. Salon ve 1. Matine - %d kisi bilet satin almistir.",S2M1);
    printf("\n2. Salon ve 2. Matine - %d kisi bilet satin almistir.",S2M2);
    printf("\n2. Salon ve 3. Matine - %d kisi bilet satin almistir.",S2M3);
    printf("\n2. Salon ve 4. Matine - %d kisi bilet satin almistir.",S2M4);
    printf("\n2. Salon ve 5. Matine - %d kisi bilet satin almistir.",S2M5);
    printf("\n\n3. Salon ve 1. Matine - %d kisi bilet satin almistir.",S3M1);
    printf("\n3. Salon ve 2. Matine - %d kisi bilet satin almistir.",S3M2);
    printf("\n3. Salon ve 3. Matine - %d kisi bilet satin almistir.",S3M3);
    printf("\n3. Salon ve 4. Matine - %d kisi bilet satin almistir.",S3M4);
    printf("\n3. Salon ve 5. Matine - %d kisi bilet satin almistir.\n",S3M5);

    fclose(BiletDosyaIsaretcisi);
}

int main()
{
    int Anahtar;
    FILE *BirinciIsaretci, *IkinciIsaretci, *AnahtarIsaretci;

    BirinciIsaretci = fopen("OrjinalMetinBelgesi.txt", "r");
    AnahtarIsaretci = fopen("AnahtarMetinBelgesi.txt", "r");
    IkinciIsaretci = fopen("SifrelenmisMetinBelgesi.txt", "w");

    if (BirinciIsaretci == NULL)
    {
        printf("Ilk adimda dosya acma hatasiyla karsilasildi.");
        exit(1);
    }

    if (AnahtarIsaretci == NULL)
    {
        printf("Ikinci adimda dosya acma hatasiyla karsilasildi.");
        exit(1);
    }

    Anahtar = fgetc(AnahtarIsaretci);
    if (IkinciIsaretci == NULL)
    {
        printf("Ucuncu adimda dosya acma hatasiyla karsilasildi.");
        exit(1);
    }

    SifreOlustur(BirinciIsaretci, IkinciIsaretci, Anahtar);
    Desifrasyon(Anahtar);

    FILE *SonDosyaIsaretcisi;
    SonDosyaIsaretcisi = fopen("SonOrjinalMetinBelgesi.txt","r");

    SifreKontrolSaglama(SonDosyaIsaretcisi);

    printf("\n\n1. Salon Tipi: Red\t\t\t2. Salon Tipi: Green\t\t\t3. Salon Tipi: Blue\n");
    printf("\n1. Matine - Annemin Yarasi\t\t1. Matine - Buz Devri 5\t\t\t1. Matine - Azem 3: Cin Tohumu\n");
    printf("2. Matine - Azazil 2: Buyu\t\t2. Matine - Dehset Odasi\t\t2. Matine - Bir Dilim Ask\n");
    printf("3. Matine - Bir Baba Hindu\t\t3. Matine - Intihar Timi\t\t3. Matine - Deliormanli\n");
    printf("4. Matine - Kizkaciran\t\t\t4. Matine - Kucuk Esnaf\t\t\t4. Matine - Leblebi Tozu\n");
    printf("5. Matine - Olaylar Olaylar\t\t5. Matine - Turk Lokumu\t\t\t5. Matine - Heidi\n\n");

    BiletTipi bilet_tipi;
    Salon salon;

    BiletIslemleri(bilet_tipi, salon);

    FILE *HasilatIsaretcisi;
    HasilatIsaretcisi = fopen("HasilatMetinBelgesi.txt", "r");

    HasilatIslemi(HasilatIsaretcisi);

    FILE *BiletIsaretcisi;
    BiletIsaretcisi = fopen("BiletSecimMetinBelgesi.txt", "r");

    MatinelerinDolulukOranlari(BiletIsaretcisi);

    fclose(BirinciIsaretci);
    fclose(IkinciIsaretci);
    fclose(AnahtarIsaretci);
    fclose(SonDosyaIsaretcisi);
    fclose(HasilatIsaretcisi);
    fclose(BiletIsaretcisi);
    return 0;
}

