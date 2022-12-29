#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define BUF_SIZE 81

void Add(char* x, char**& tab, unsigned& n); // dodaje dane
void Print(char** tab, unsigned n); // wszystkich, rozpoczynających się na daną litere;
void Print(char** tab, unsigned n, char letter);
void Remove(unsigned position, char**& tab, unsigned& n); // po pozycji, po treśći
void RemoveByName(char* data,char**& tab, unsigned& n); // po pozycji, po treśći
void sort(char**& tab, unsigned n); // alfabetycznie, długością znaków
void sortSize(char**& tab, unsigned n);
void wypiszMenu(bool wrongInput);
void pobierzZnaki(char* output);

int main()
{
    printf("Filip Turczyn\n");
    char** wsk = (char**) calloc(0, sizeof(char*)); // alokuje placeholder rozmiaru zero
    char buf[BUF_SIZE];
    unsigned N = 0;
    {
        bool running = true;
        bool wrongInput = false;
        int temp;
        while (running)
        {
            system("clear");
            wypiszMenu(wrongInput);
            wrongInput = false;

            scanf("%d", &temp);
            printf("\n");
            getchar();

            switch (temp)
            {
                case 1: { //Podaj Dane
                    printf("Podaj Dane: ");
                    pobierzZnaki(buf);
                    Add(buf, wsk, N);
                    break;
                }
                case 2: { //Wypisz Dane
                    system("clear");
                    Print(wsk, N);
                    printf("\n\nPress any key..");
                    getchar();
                    break;
                }
                case 3: { //Wypisz Dane na litere
                    char letter;
                    printf("Podaj litere: ");
                    scanf("%c", &letter);
                    system("clear");
                    Print(wsk, N, letter);
                    printf("\n\nPress any key..");
                    getchar();
                    break;
                }
                case 4: { //Usun Dane z pozycji
                    int position;
                    printf("Podaj Pozycje: ");
                    scanf("%d", &position);
                    Remove(position, wsk, N);
                    break;
                }
                case 5: { //Usun Dane po nazwie
                    pobierzZnaki(buf);
                    RemoveByName(buf, wsk, N);
                    break;
                }
                case 6: { //Posortuj alfabetycznie
                    sort(wsk, N);
                    break;
                }
                case 7: { //Posortuj po wielkości
                    sortSize(wsk, N);
                    break;
                }
                case 8: { //END
                    running = false;
                    break;
                }
                default: {
                    getchar();
                    wrongInput = true;
                    break;
                }
            }
        }
    }

    for (unsigned i = 0; i < N; ++i)
    {
        free(wsk[i]);
    }

    free(wsk);
    return 0;
}

void Add(char* x, char**& tab, unsigned& n)
{
    char** tmptab = (char**)realloc(tab, (n + 1) * sizeof(char*));
    if (tmptab != NULL) {
        tab = tmptab;
        tab[n] = (char*)malloc(BUF_SIZE * sizeof(char));
        strcpy(tab[n], x);
        n++;
    } else {
        printf("Brak pamięci!\n");
    }
    return;
}

void Print(char** tab, unsigned n)
{
    if (n != 0) {
        for (unsigned i = 0; i < n; i++) {
            printf("%d. %s\n", i, tab[i]);
        }
    } else {
        printf("Pusta tablica....");
    }
    return;
}

void Print(char** tab, unsigned n, char letter)
{
    bool doesntExist = true;
    if (n != 0) {
        for (unsigned i = 0; i < n; i++) {
            if (tab[i][0] == letter) {
                printf("%d. %s\n", i, tab[i]);
                doesntExist = false;
            }
        }
        if (doesntExist) {
			printf("Nie ma danych na taką litere...");
		}
    } else {
        printf("Pusta tablica....");
    }
}

void Remove(unsigned position, char**& tab, unsigned& n)
{
    if (position < n) {
        free(tab[position]);
        n--;
        memcpy(&tab[position], &tab[position + 1], (n - position) * sizeof(char*));
        tab = (char**) realloc(tab, n * sizeof(char*));
    } else {
        printf("brak danych na pozycji!\n");
    }
    return;
}

void RemoveByName(char* data, char**& tab, unsigned& n)
{
    for (unsigned i = 0; i < n; i++) {
        if (*tab[i] == *data) {
            Remove(i, tab, n);
        }
    }
}

void sort(char**& tab, unsigned n) {
    int* sizes = (int*) calloc(n, sizeof(int));
    for (unsigned i = 0; i < n; i++) {
        if (tab[i][0] <= 'z' && 'a' <= tab[i][0]) {
            sizes[i] = int(tab[i][0]);
        } else if (tab[i][0] <= 'Z' && 'A' <= tab[i][0]) {
            sizes[i] = int(tab[i][0]) - ('A' - 'a');
        } else {
            sizes[i] = CHAR_MAX;
        }
    }

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned o = 0; o < n - 1; o++)
        {
            if (sizes[o] > sizes[o + 1]) {
                int tempINT = sizes[o];
                char* tempPTR = tab[o];
                sizes[o] = sizes[o + 1];
                tab[o] = tab[o + 1];
                sizes[o + 1] = tempINT;
                tab[o + 1] = tempPTR;
            }
        }
    }

    free(sizes);
    return;
}

void sortSize(char**& tab, unsigned n) {
    int* sizes = (int*)malloc(n * sizeof(int));
    for (unsigned i = 0; i < n; i++)
    {
        int temp = 0;
        while (tab[i][temp] != NULL)
            temp++;
        sizes[i] = temp;
    }

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned o = 0; o < n-1; o++)
        {
            if (sizes[o] > sizes[o + 1]) {
                int tempINT = sizes[o];
                char* tempPTR = tab[o];
                sizes[o] = sizes[o + 1];
                tab[o] = tab[o + 1];
                sizes[o + 1] = tempINT;
                tab[o + 1] = tempPTR;
            }
        }
    }
    free (sizes);
    return;
}

void wypiszMenu(bool wrongInput)
{
    printf("[#===={}====#|Menu|#===={}====#]\n");
    printf("|                              |\n");
    printf("| 1.  Dodaj dane               |\n");
    printf("|                              |\n");
    printf("| 2.  Wypisz wszystko          |\n");
    printf("| 3.  Wypisz dane na litere    |\n");
    printf("|                              |\n");
    printf("| 4.  Usun z pozycji           |\n");
    printf("| 5.  Usun dane wartosci       |\n");
    printf("|                              |\n");
    printf("| 6.  Posortuj alfabetycznie   |\n");
    printf("| 7.  Posortuj po dlugości     |\n");
    printf("|                              |\n");
    printf("| 8.  End Program              |\n");
    printf("|                              |\n");
    printf("[#===={}====#|Menu|#===={}====#]\n\n");
    if (wrongInput) {
        printf("Wrong Input");
    }
    printf("\nWybor: ");
    return;
}

void pobierzZnaki(char *output)
{
    char temp;
    for (int i = 0; i < BUF_SIZE - 1; i++ )
    {
        scanf("%c", &temp);
        if (temp != 10) {
            output[i] = temp;
            output[i+1] = '\0';
        } else {
            break;
        }
    }
    return;
}
