/*
	created by Bartek && Denis
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <list>
#include <sstream>
#include <cstdio>

using namespace std;

bool czy_znaleziono(string, string);
string losuj(list<int> &, int);

int main()
{
	setlocale(LC_ALL, "");
	
	fstream plik, plik2, plik3;
	int ile_osob, licznik;
	int os1, os2;
	string wybor, imie, nazwisko, osoba, line;
	string osoba1, osoba2;

	
	cout << "Witaj w programie!\n\nCzy chcesz zrobić nową listę osób? TAK / NIE\n";
	cin >> wybor;
	cout << "\n\n";
	if (wybor == "TAK" || wybor == "tak" || wybor == "Tak")\
	{
		plik.open("Lista.txt", ios::out);
		cout << "Z ilu osób mam losować?: ";
		cin >> ile_osob;
		plik << ile_osob << endl;
		cout << "Format wpisywania osób:" << endl << "imię nazwisko" << endl << "np. Jan Kowalski\n\n";

		for (int numer_osoby = 1; numer_osoby <= ile_osob; numer_osoby++)
		{
			cout << "Podaj imię i nazwisko osoby numer " << numer_osoby << ": ";
			cin >> imie >> nazwisko;
			osoba = imie + " " + nazwisko;
			plik << numer_osoby << " " << osoba << endl;
		}
		plik.close();
		
		plik2.open("Pary.txt", ios::out);
		plik2.close();
	}
		
	plik.open("Lista.txt", ios::in);
	getline(plik, line);
	ileOsob = atoi(line.c_str());
	string * lista_osob = new string[ile_osob];
	list <int> lista_licznikow;

	for (int indeks_osoby = 0; indeks_osoby < ile_osob; indeks_osoby++)
	{
		plik >> licznik >> imie >> nazwisko;
		osoba = imie + " " + nazwisko;
		lista_osob[indeksOsoby] = osoba;
		lista_licznikow.push_back(licznik);
	}

	plik.close();
	plik2.open("Pary.txt", ios::in | ios::out | ios::app);
	plik3.open("Wyniki.txt", ios::out);

	if (ile_osob % 2 == 0)
	{
		for (int liczba_losowan = 1; liczba_losowan <= (ile_osob / 2); liczba_losowan++)
		{
			line = losuj(lista_licznikow, ile_osob);
			plik2 << line << endl;
			stringstream stream(line);
			stream >> os1 >> os2;
			plik3 << lista_osob[os1-1] << " + " << lista_osob[os2-1] << endl;
		}
	}

	else
	{
		for (int liczba_losowan = 1; liczba_losowan <= (ile_osob / 2); liczba_losowan++)
		{
			line = losuj(lista_licznikow, ile_osob);
			plik2 << line << endl;
			stringstream stream(line);
			stream >> os1 >> os2;
			plik3 << lista_osob[os1 - 1] << " + " << lista_osob[os2 - 1] << endl;
		}
		list<int>::iterator it = lista_licznikow.begin();
		os1 = *it;
		plik3 << endl << "Niewylosowano: " << lista_osob[os1 - 1] << "! Dodaj tę osobę do ostatniej pary!" << endl;
	}

	plik2.close();
	plik3.close();

	cout << "\n\nLosowanie zostało zakończone, wyniki znajdziesz w pliku Wyniki.txt" << endl << "Wcisnij enter aby zakończyć" << endl;
	
	delete[] lista_osob;
	getchar();
	getchar();
	return 0;
}




bool czy_znaleziono(string para1, string para2) {
	fstream plik3;
	string line;
	plik3.open("Pary.txt", ios::in);

	while (!(plik3.eof()))
	{
		getline(plik3, line);
		if ((line.find(para1) != string::npos) || (line.find(para2) != string::npos))
			return true;
	}
	return false;
}

string losuj(list <int> &lista, int ilosc_osob)
{
	fstream plik3;
	int osoba1, osoba2;
	string os1, os2, para1, para2, line;
	plik3.open("Pary.txt", ios::in | ios::out | ios::app);

	srand(time(NULL));
	bool res = false;
	bool found1, found2;
	
	while(!res)
	{	
		found1 = found2 = false;
		while(found1 == false)
		{
			osoba1 = (rand() % ilosc_osob) + 1;
			found1 = (find(lista.begin(), lista.end(), osoba1) != lista.end());
		}
		while (found2 == false)
		{
			osoba2 = (rand() % ilosc_osob) + 1;
			found2 = (find(lista.begin(), lista.end(), osoba2) != lista.end());
		}
		
		os1 = to_string(osoba1);
		os2 = to_string(osoba2);
		para1 = os1 + " " + os2;
		para2 = os2 + " " + os1;

		if (osoba1 == osoba2) continue;
		else if (czy_znaleziono(para1, para2)) continue;

		res = true;
		lista.remove(osoba1);
		lista.remove(osoba2);
	}
	
	string wynik = para1 + "        " + para2;
	return wynik;
}
