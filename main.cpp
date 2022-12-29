#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 81

void Add(char* x, char**& tab, unsigned& n);// dodaje dane
void Print(char** tab, unsigned n); // Wszystkich, rozpoczynających się na daną litere;
void Print(char** tab, unsigned n, char litera);
void Remove(unsigned ktory, char**& tab, unsigned& n);// po pozycji, po treśći
void sort(char*& tab, unsigned n);// alfabetycznie, długością znaków

void menu();

int main()
{
    printf("Filip Turczyn\n");
    char** wsk = (char**) calloc(0, sizeof(char*)); // alokuje placeholder rozmiaru zero
    char buf[BUF_SIZE];
    buf[0] = 'n';
    buf[1] = 'i';
    buf[2] = 'g';
    buf[3] = '\0';

    unsigned N = 0;

    Add(buf, wsk, N);
    buf[0] = 'k';
    Add(buf, wsk, N);
    buf[0] = 's';
    Add(buf, wsk, N);

    Print(wsk, N);
    printf("\n %d \n",N);

    Remove(0, wsk, N);

    Print(wsk, N);
    printf("\n");

    for (int i = 0; i < N; ++i)
    {
        free(wsk[i]);
    }
    free(wsk);
    return 0;
}

void Add(char* x, char**& tab, unsigned& n)
{
    char** tmptab = (char**) realloc(tab, (n + 1) * sizeof(char*));
    if (tmptab != NULL) {
        tab = tmptab;
        tab[n] = (char*) malloc(BUF_SIZE * sizeof(char));
        memcpy(tab[n], x, BUF_SIZE);
        n++;
    } else {
        printf("Brak pamięci!\n");
    }
    return;
}

void Print(char** tab, unsigned n)
{
    for (int i = 0; i < n; i++) {
        printf("%d. %s\n", i, tab[i]);
    }

//    for (int i = 0; i < n; i++) {
//        printf("\n%d. ", i);
//        int temp = 0;
//        while (tab[i][temp] != '\0') {
//            printf("%c", tab[i][temp++]);
//        }
//    }
}

void Print(char** tab, unsigned n, char litera)
{
    for (int i = 0; i < n; i++)
    {
        if (tab[i][0] == litera) {
            printf("\n%d.", i);
            int temp = 0;
            while (tab[i][temp] != '\0') {
                printf("%c", tab[i][temp++]);
            }
        }
    }
}
void Remove(unsigned ktory, char**& tab, unsigned& n)
{
    if (ktory < n)
    {
        free(tab[ktory]);
        n--;
//        for (unsigned i = ktory; i < n; i++) {
//            tab[i] = tab[i + 1];
//        }

        memcpy(&tab[ktory], &tab[ktory + 1], (n - ktory) * sizeof(char*));
        tab = (char**) realloc(tab, n * sizeof(char*));

    } else {
        printf("brak danych na pozycji!\n");
    }

    return;
}

void sort(char*& tab, unsigned n)
{
}
