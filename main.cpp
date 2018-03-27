#include <iostream>
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define ROZMIAR_KOLEJKI 15 // Maksymalna ilosc elementow w kolejce

using namespace std;

/* Zmienne globalne */

int kolejka[ROZMIAR_KOLEJKI][2];
int glowa = 0;
int ogon = 0;
int ilosc_elementow = 0;

/* **************** */

void sortuj_wstaw()
{
    int temp[2];
    int i, j;

    /* Sortowanie */

    for (i = 1; i < ilosc_elementow; ++i)
    {
        temp[0] = kolejka[i][0];
        temp[1] = kolejka[i][1];

        for (j = i-1; j >= 0 && kolejka[j][1] > temp[1]; --j )
        {
            kolejka[j+1][1] = kolejka[j][1];
            kolejka[j+1][0] = kolejka[j][0];
        }

        kolejka[j+1][0] = temp[0];
        kolejka[j+1][1] = temp[1];
    }

    /* Odwracanie elementow */

    for (i = 0; i < ilosc_elementow/2; ++i)
    {
        temp[0] = kolejka[ilosc_elementow-i-1][0];
        temp[1] = kolejka[ilosc_elementow-i-1][1];
        kolejka[ilosc_elementow-i-1][0] = kolejka[i][0];
        kolejka[ilosc_elementow-i-1][1] = kolejka[i][1];
        kolejka[i][0] = temp[0];
        kolejka[i][1] = temp[1];
    }
}

void sortuj_wybor()
{
    int i, j, k;
    int temp[2];

    /* Sortowanie */

    for (i = 0; i < ilosc_elementow; ++i)
    {
        k = i;

        for (j = i+1; j < ilosc_elementow; ++j)
        {
            if ( kolejka[j][1] < kolejka[k][1] )
            {
                k = j;
            }

            swap(kolejka[k][0], kolejka[i][0]);
            swap(kolejka[k][1], kolejka[i][1]);
        }
    }

    /* Odwracanie elementow */

    for (i = 0; i < ilosc_elementow/2; ++i)
    {
        temp[0] = kolejka[ilosc_elementow-i-1][0];
        temp[1] = kolejka[ilosc_elementow-i-1][1];
        kolejka[ilosc_elementow-i-1][0] = kolejka[i][0];
        kolejka[ilosc_elementow-i-1][1] = kolejka[i][1];
        kolejka[i][0] = temp[0];
        kolejka[i][1] = temp[1];
    }
}

void wpisz_recznie()
{
    system ("cls");

    int wartosc;
    int prio;

    if (ilosc_elementow >= ROZMIAR_KOLEJKI)
    {
        cout << "Kolejka pelna!" << endl;
    }
    else
    {
        cout << "Podaj liczbe oraz jej priorytet oddzielajac wartosci spacja." << endl;
        cin >> wartosc;
        cin >> prio;

        kolejka[ogon][0] = wartosc;
        kolejka[ogon][1] = prio;

        ogon = (ogon+1)%ROZMIAR_KOLEJKI;
        ++ilosc_elementow;
    }
}

void usun_wszystko()
{
    for (int i = 0; i < ROZMIAR_KOLEJKI; ++i)
    {
        kolejka[i][0] = 0;
        kolejka[i][1] = 0;
    }

    glowa = 0;
    ogon = 0;
    ilosc_elementow = 0;
}

void generuj_losowo()
{
    /* Generowanie liczb losowo na poczatku czysci wszystkie dane */

    usun_wszystko();

    /* Inicjalizajca generatora liczb losowych */

    srand(time(NULL));

    for (int i = 0; i < ROZMIAR_KOLEJKI; ++i)
    {
        int wartosc = (rand()%100)+1;
        int prio = (rand()%5)+1;

        kolejka[ogon][0] = wartosc;
        kolejka[ogon][1] = prio;

        ogon = (ogon+1)%ROZMIAR_KOLEJKI;
        ++ilosc_elementow;
    }

    /* Sortowanie elementow */

    sortuj_wstaw();
}

void usun()
{
    if (ilosc_elementow == 0)
    {
        cout << "Nie ma czego usuwac!";
    }
    else
    {
        kolejka[0][0] = kolejka[1][0];
        kolejka[0][1] = kolejka[1][1];
        --ilosc_elementow;

        for (int i = 0; i < ilosc_elementow; i++)
        {
            kolejka[i][0] = kolejka[i+1][0];
            kolejka[i][1] = kolejka[i+1][1];
        }

        kolejka[ilosc_elementow][0] = 0;
        kolejka[ilosc_elementow][1] = 0;
    }
}

void wyswietl()
{
        for (int i = 0; i < ROZMIAR_KOLEJKI; ++i)
        {
            cout << "Wartosc: " << kolejka[i][0] << "\tPriorytet: " << kolejka[i][1] << endl;
        }

}

int main()
{
    int wybor = 0;

    while ( wybor != 99 )
    {
        system ("cls");

        cout << "::: MENU GLOWNE PROGRAMU :::" << endl << endl;
        cout << "1. Wpisz wartosci recznie" << endl;
        cout << "2. Wygeneruj wartosci losowo" << endl;
        cout << "3. Usun element z kolejki" << endl;
        cout << "4. Usun wszystko" << endl;
        cout << "5. Sortowanie przez wstawianie" << endl;
        cout << "6. Sortowanie przez wybor" << endl;
        cout << "99. Zakoncz program" << endl << endl;
        cout << "::: KOLEJKA :::" << endl << endl;
        cout << "Glowa: " << kolejka[0][0] << endl;
        cout << "Priorytet glowy: " << kolejka[0][1] << endl;
        cout << "Ogon: " << kolejka[ilosc_elementow-1][0] << endl;
        cout << "Priorytet ogona: " << kolejka[ilosc_elementow-1][1] << endl << endl;

        wyswietl();

        cout << endl << "Twoj wybor: ";
        cin >> wybor;

        if ( wybor == 1 )
            wpisz_recznie();
        else if ( wybor == 2 )
            generuj_losowo();
        else if ( wybor == 3 )
            usun();
        else if ( wybor == 4 )
            usun_wszystko();
        else if ( wybor == 5 )
            sortuj_wstaw();
        else if ( wybor == 6 )
            sortuj_wybor();
        else if ( wybor == 99 )
            return 0;
    }
};
