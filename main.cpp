#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>

using namespace std;

int portfel, x;
bool wygrana;
typedef vector<bool> Talia;
typedef vector<int> Karty;

Talia stworzTalie(int t)
{
    Talia T(t, false);
    return T;
}

string odczytajKarte(int k)
{
    string karta = "";

    if(k%13 == 0 )
        karta += "As";
    else if (k%13 < 9)
        karta += char('0' + k%13 + 1);
    else if(k%13 == 9)
        karta += "10";
    else if (k%13 == 10)
        karta += "Walet";
    else if (k%13 == 11)
        karta += "Dama";
    else
        karta += "Krol";

    if(k < 13)
        karta += " Kier ";
    else if (k < 26)
        karta += " Pik";
    else if (k < 39)
        karta += " Trefl";
    else
        karta += " Karo";

    return karta;
}

int wyberzLosowaLiczbe(int minimum, int maximum)
{
    return rand() % (maximum - minimum + 1) + minimum;
}

void stanPortfela(int &portfel)
{
    cout << "Stan Twojego portfela: " << portfel << "$" << endl;
}

int wybierzKarte(Talia &T)
{
    bool b = false;
    int r;
    while (!b)
    {
        r = wyberzLosowaLiczbe(0, T.size()-1);
        if(!T[r])
            b = true;
    }
    T[r] = true;
    return r;
}

int wplacKwote(int &portfel)
{
    int kwota;
    cout << "Wpisz kwote jaka chcesz postawic: " << endl;
    cin >> kwota;

    if(kwota > portfel)
    {
        cout << "Nie mozesz postawic wiecej niz masz!" << endl;
        wplacKwote(portfel);
    }
    portfel -= kwota;
    return kwota;
}

int punktyBlackJack (int k)
{
    if (k%13 == 0)
    {
        int wybor;
        do{

        cout << "Wpisz 1 lub 11: ";
        cin >> wybor;
        if( wybor == 1)
            return 1;
        else if (wybor == 11)
            return 11;
        else
            cout << "Wpisales zla liczbe...";
        }while(wybor != 1 || wybor != 11);
    }

        if(k%13 < 9)
            return (k%13 + 1);

        return 10;

}


void blackJack(int &portfel)
{
    cout << " Gra BlackJack" << endl;
    stanPortfela(portfel);
    int kwota = wplacKwote(portfel);
    Talia T = stworzTalie(52);
    int punkty = 0;
    int punktyKomputera = 0;
    bool koniec = false;



    int karta = wybierzKarte(T);
    cout << "Twoja pierwsza karta to " << odczytajKarte(karta)  << endl;
    punkty += punktyBlackJack(karta);
    karta = wybierzKarte(T);
    cout << "Twoja druga karta to " << odczytajKarte(karta)  << endl;
    punkty += punktyBlackJack(karta);


    karta = wybierzKarte(T);
    cout << "Karta komputera to " << odczytajKarte(karta) << endl;
    if (karta%13 == 0) {
        if (punktyKomputera > 10)
            punktyKomputera += 1;
        else
            punktyKomputera += 11;
    }
    else punktyKomputera += punktyBlackJack(karta);

    int ukrytaKarta = wybierzKarte(T);
    if (ukrytaKarta%13 == 0) {
        if (punktyKomputera > 10)
            punktyKomputera += 1;
        else
            punktyKomputera += 11;
    }
    else punktyKomputera += punktyBlackJack(ukrytaKarta);


    while (punkty < 21 && punktyKomputera < 21 && koniec == false )
    {
        int wybor;
        cout << "Wpisz 1 aby grac dalej; 2 aby spasowac" << endl;
        cin >> wybor;

        switch (wybor) {

            case 1: {
                karta = wybierzKarte(T);
                cout << "Twoja karta to " << odczytajKarte(karta) << endl;
                punkty += punktyBlackJack(karta);

                if(punkty == 21)
                {
                    koniec = true;
                    break;
                }
                else if(punkty < 21)
                {
                    if(punktyKomputera < 16)
                    {
                        karta = wybierzKarte(T);
                        if (karta%13 == 0) {
                            if (punktyKomputera > 10)
                                punktyKomputera += 1;
                            else
                                punktyKomputera += 11;
                        }
                        else punktyKomputera += punktyBlackJack(karta);
                        if (punktyKomputera == 21) koniec = true;
                        break;
                    }
                    else cout << "Komputer pasuje" << endl;
                }
                break;
            }

            case 2: {
                cout << "Ukryta karta komputera to " << odczytajKarte(ukrytaKarta) << endl;
                koniec = true;
                break;
            }

        }

    }
    if(punkty == 21) {
        cout << "BlackJack! Wygrales, gratulacje! " << endl;
        wygrana = true;
    }
    else if (punktyKomputera == 21)
    {
        cout << "BlackJack komputera!" << endl;
        wygrana = false;
    }
    if (punkty > 21){
        wygrana = false;
    }
    else if (punktyKomputera > 21)
    {
        wygrana = true;
    }
    else if(punkty > punktyKomputera)
        wygrana = true;
    else if(punkty < punktyKomputera)
        wygrana = false;


    if(wygrana)
    {
        if (punkty != 21)
            cout << "Wygrales! :)" << endl;
        portfel += kwota*2;
    }
    else{
        cout << "Przegrales :(" << endl;
    }

    cout << "Twoje punkty: " << punkty << endl;
    cout << "Punkty przeciwnika: " << punktyKomputera << endl;
    stanPortfela(portfel);
}

void jednorekiBandyta(int &portfel)
{
    int kredyt, stawka;
    char koniec = ' ';
    int nr[3];
    cout << "Slot machine" << endl;
    kredyt = wplacKwote(portfel);
    cout << "Wplacono: " << kredyt <<  endl;

    do{
    cout << "Podaj stawke: " << endl;
    cin >> stawka;
    for (int i = 0; i <3; i++)
        nr[i] =wyberzLosowaLiczbe(1,7);

    cout << "----------------" << endl;
    for (int i = 0; i < 3;i++){
        printf("%5d", nr[i]-1);
        printf("%5d", nr[i]);
        printf("%5d \n", nr[i]+1);


    }
    cout << "----------------" << endl;

    if((nr[1]== nr[2]) && (nr[2] == nr[3])){
        cout << "Wygrales: " << stawka*100 << endl;
        kredyt += stawka*100;
    }
    else{
        cout << "Nie tym razem :-( \n Sprobuj ponownie!" << endl;
        kredyt -= stawka;
    }
    cout << "Stan konta: " << kredyt << endl;
    cout << "Aby wyplacic gotowke i wyjsc z Slot machine wpisz q" << endl;
    cin >> koniec;
    }while(koniec!= 'q' || koniec!= 'Q');
}

void ruletka(int &portfel)
{
    int rodzaj, obstaw, wynik;

    cout << " Ruletka" << endl;
    stanPortfela(portfel);
    int kwota = wplacKwote(portfel);
    cout << " Wybierz 1 aby obstawiac numery \n Wybierz 2 aby obstawic kolor" << endl;
    cin >> rodzaj;
    wynik = wyberzLosowaLiczbe(0,36);
    switch (rodzaj) {

        case 1: {
            cout << "Wybierz liczbe od 0 do 36: " << endl;
            cin >> obstaw;
            cout << "Wygrywa numer " << wynik << endl;
            if(obstaw == wynik){
                cout << "Wygrales!" << endl;
                portfel += 36*kwota;
            }
            else
                cout << "Przegrales" << endl;
            break;
        }

        case 2: {
            cout << "Wybierz 1 aby obstawic czarne \n Wybierz 2 aby obstawic czerwone" << endl;
            cin >> obstaw;
            cout << "Wygrywa numer " << wynik << endl;
            if(obstaw%2 == wynik%2)
            {
                cout << "Wygrales!" << endl;
                portfel += 2*kwota;
            }
            else cout <<  "Przegrales" << endl;
            break;
        }
    }
    stanPortfela(portfel);
}
int main()
{
    portfel = rand() % 1000 + 500;
    cout << "Witaj w kasynie!" << endl;
    stanPortfela(portfel);
    cout << " 1. BlackJack \n  2. Jednoreki bandyta \n   3. Ruletka \n (Wybierz 1-3): ";
    cin >> x;

    switch(x) {

        case 1: {blackJack(portfel); break;}
        case 2: {jednorekiBandyta(portfel); break;}
        case 3: {ruletka(portfel); break;}
    }

    return 0;
}
