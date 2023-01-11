#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct DateAutoturism
{
    char nr_de_inmatriculare[15];
    char marca[20];
    char culoare[10];
    int nr_de_locuri;
    char tip_de_combustibil[30];
    float capacitate_cilindrica_motor;
    char serie_sasiu[30];
    int vechime;
    float nr_de_km;
} autoturism;

void modificare_date_autoturism(char *nume_fisier)
{
    char numar_inmatriculare[15] = {0};
    int pozitie = 0, numar_set_date = 0;

    FILE *f;
    f = fopen(nume_fisier, "rb+");
    if (f == NULL)
    {
        printf("A aparut o eroare! Incearca din nou\n");
        exit(1);
    }

    printf("\nIntroduceti numar de inmatriculare al autoturismului pentru care vreti sa modificati numarul de km parcursi si vechimea acestuia, sau introduceti '-1' pentru a termina acest proces: ");
    scanf("%s", &numar_inmatriculare);

    while (strcmp(numar_inmatriculare, "-1") != 0)
    {
        do
        {
            numar_set_date = fread(&autoturism, sizeof(autoturism), 1, f);

            if (strcmp(autoturism.nr_de_inmatriculare, numar_inmatriculare) == 0)
            {
                pozitie = ftell(f) - sizeof(autoturism);
                break;
            }
        } while (strcmp(autoturism.nr_de_inmatriculare, numar_inmatriculare) != 0 && numar_set_date == 1);

        if (numar_set_date < 1)
        {
            printf("\nAcest autoturism nu exista in lista.\n");
            break;
        }

        printf("\nIntroduceti noua vechime a autoturismului: ");
        scanf("%d", &autoturism.vechime);

        printf("Introduceti noua valoare pentru numarul de km parcursi ai autoturismului: ");
        scanf("%f", &autoturism.nr_de_km);

        fseek(f, pozitie, 0);
        fwrite(&autoturism, sizeof(autoturism), 1, f);

        printf("\nIntroduceti numar de inmatriculare al autoturismului pentru care vreti sa modificati numarul de km parcursi si vechimea acestuia, sau introduceti '-1' pentru a termina acest proces: ");
        scanf("%s", &numar_inmatriculare);
    }

    fclose(f);
}

void adaugare_autoturism_nou(char *nume_fisier)
{
    FILE *f;
    f = fopen(nume_fisier, "ab");
    if (f == NULL)
    {
        printf("A aparut o eroare! Incearca din nou\n");
        exit(1);
    }

    citire_nr_inmatriculare();

    while (strcmp(autoturism.nr_de_inmatriculare, "-1") != 0)
    {
        citire_date_autoturism();
        fwrite(&autoturism, sizeof(autoturism), 1, f);
        citire_nr_inmatriculare();
    }

    fclose(f);
}

void afisare_continut_fisier(char *nume_fisier)
{
    FILE *f;
    f = fopen(nume_fisier, "rb");
    if (f == NULL)
    {
        printf("A aparut o eroare! Incearca din nou\n");
        exit(1);
    }

    printf("\nLista autoturismelor este:");

    int nr_set_date;
    nr_set_date = fread(&autoturism, sizeof(autoturism), 1, f);

    while (nr_set_date == 1)
    {
        printf("\n*------------*");
        printf("\n-Nr. de inmatriculare: %s", autoturism.nr_de_inmatriculare);
        printf("\n-Marca: %s", autoturism.marca);
        printf("\n-Culoare: %s", autoturism.culoare);
        printf("\n-Nr. de locuri: %d", autoturism.nr_de_locuri);
        printf("\n-Tip de combustibil: %s", autoturism.tip_de_combustibil);
        printf("\n-Capacitate cilindrica motor: %f", autoturism.capacitate_cilindrica_motor);
        printf("\n-Serie sasiu: %s", autoturism.serie_sasiu);
        printf("\n-Vechime: %d", autoturism.vechime);
        printf("\n-Nr. de km parcursi: %f", autoturism.nr_de_km);
        printf("\n*------------*\n");

        nr_set_date = fread(&autoturism, sizeof(autoturism), 1, f);
    }

    fclose(f);
}

void creare_fisier(char *nume_fisier)
{
    FILE *f = fopen(nume_fisier, "wb");

    if (f == NULL)
    {
        printf("Crearea fisierului a esuat! Incearca din nou\n");
        exit(1);
    }

    // pentru a vedea cand se termina citirea datelor desore autoturisme
    citire_nr_inmatriculare();

    while (strcmp(autoturism.nr_de_inmatriculare, "-1") != 0)
    {
        citire_date_autoturism();
        fwrite(&autoturism, sizeof(autoturism), 1, f);
        citire_nr_inmatriculare();
    }

    fclose(f);
}

void citire_date_autoturism()
{
    printf("\nIntroduceti marca autoturismului: ");
    scanf("%s", &autoturism.marca);

    printf("\nIntroduceti culoarea autoturismului: ");
    scanf("%s", &autoturism.culoare);

    printf("\nIntroduceti numarul de locuri al autoturismului: ");
    scanf("%d", &autoturism.nr_de_locuri);

    printf("\nIntroduceti tipul de combustibil al autoturismului: ");
    scanf("%s", &autoturism.tip_de_combustibil);

    printf("\nIntroduceti capacitatea cilindrica a motorului autoturismului: ");
    scanf("%f", &autoturism.capacitate_cilindrica_motor);

    printf("\nIntroduceti seria sasiului autoturismului: ");
    scanf("%s", &autoturism.serie_sasiu);

    printf("\nIntroduceti vechimea autoturismului: ");
    scanf("%d", &autoturism.vechime);

    printf("\nIntroduceti numarul de km parcursi ai autoturismului: ");
    scanf("%f", &autoturism.nr_de_km);
    printf("\n");
}

void citire_nr_inmatriculare()
{
    printf("\nIntroduceti numarul de inmatriculare al autoturismului dorit sau '-1' pentru a termina citirea datelor despre autoturisme: ");
    scanf("%s", &autoturism.nr_de_inmatriculare);
}

int main()
{
    char nume_fisier[50];

    printf("\nIntroduceti numele fisierului care va contine datele despre autoturisme: ");
    scanf("%s", nume_fisier);

    creare_fisier(nume_fisier);
    afisare_continut_fisier(nume_fisier);

    printf("\n*---------------*\n");
    printf("Adaugare de noi autoturisme:\n");
    adaugare_autoturism_nou(nume_fisier);
    afisare_continut_fisier(nume_fisier);

    printf("\n*---------------*\n");
    printf("Modificare date autoturisme:\n");
    modificare_date_autoturism(nume_fisier);
    afisare_continut_fisier(nume_fisier);

    return 0;
}