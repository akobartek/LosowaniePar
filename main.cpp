/*
	WIELKI PROJEKT PROGRAMISTOW ZE SPOLKI ZOO "WROBLEWSKI"
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
	fstream plik, plik2, plik3;
	int ileOsob, licznik;
	int os1, os2;
	string wybor, imie, nazwisko, osoba, line;
	string osoba1, osoba2;

	
	cout << "Witaj w programie do losowania Emausow!\n\nCzy chcesz zrobic nowa liste osob? TAK / NIE\n";
	cin >> wybor;
	cout << "\n\n";
	if (wybor == "TAK" || wybor == "tak" || wybor == "Tak")\
	{
		plik.open("czlonkowie.txt", ios::out);
		cout << "Ile osob liczy twoja wspolnota: ";
		cin >> ileOsob;
		plik << ileOsob << endl;
		cout << "Format wpisywania osob:" << endl << "imie nazwisko" << endl << "np. Grzegorz Dudek\n\n";

		for (int numerOsoby = 1; numerOsoby <= ileOsob; numerOsoby++)
		{
			cout << "Podaj imie i nazwisko osoby numer " << numerOsoby << ": ";
			cin >> imie >> nazwisko;
			osoba = imie + " " + nazwisko;
			plik << numerOsoby << " " << osoba << endl;
		}
		plik.close();
	}
		
	plik.open("czlonkowie.txt", ios::in);
	getline(plik, line);
	ileOsob = atoi(line.c_str());
	string * listaOsob = new string[ileOsob];
	list <int> listaLicznikow;

	for (int indeksOsoby = 0; indeksOsoby < ileOsob; indeksOsoby++)
	{
		plik >> licznik >> imie >> nazwisko;
		osoba = imie + " " + nazwisko;
		listaOsob[indeksOsoby] = osoba;
		listaLicznikow.push_back(licznik);
	}

	plik.close();
	plik2.open("pary.txt", ios::in | ios::out | ios::app);
	plik3.open("emausy.txt", ios::out);

	if (ileOsob % 2 == 0)
	{
		for (int liczbaLosowan = 1; liczbaLosowan <= (ileOsob / 2); liczbaLosowan++)
		{
			line = losuj(listaLicznikow, ileOsob);
			plik2 << line << endl;
			stringstream stream(line);
			stream >> os1 >> os2;
			plik3 << listaOsob[os1-1] << " + " << listaOsob[os2-1] << endl;
		}
	}

	else
	{
		for (int liczbaLosowan = 1; liczbaLosowan <= (ileOsob / 2); liczbaLosowan++)
		{
			line = losuj(listaLicznikow, ileOsob);
			plik2 << line << endl;
			stringstream stream(line);
			stream >> os1 >> os2;
			plik3 << listaOsob[os1 - 1] << " + " << listaOsob[os2 - 1] << endl;
		}
		list<int>::iterator it = listaLicznikow.begin();
		os1 = *it;
		plik3 << endl << "Niewylosowano: " << listaOsob[os1 - 1] << "! Dodaj te osobe do ostatniej pary!" << endl;
	}

	plik2.close();
	plik3.close();

	cout << "\n\nEmausy zostaly wylosowane, znajdziesz je w pliku emausy.txt" << endl << "Wcisnij enter aby zakonczyc" << endl;
	
	delete[] listaOsob;
	getchar();
	getchar();
	return 0;
}






bool czy_znaleziono(string para1, string para2) {
	fstream plik3;
	string line;
	plik3.open("pary.txt", ios::in);

	while (!(plik3.eof()))
	{
		getline(plik3, line);
		if ((line.find(para1) != string::npos) || (line.find(para2) != string::npos))
			return true;
	}
	return false;
}

string losuj(list <int> &lista, int iloscOsob)
{
	fstream plik3;
	int osoba1, osoba2;
	string os1, os2, para1, para2, line;
	plik3.open("pary.txt", ios::in | ios::out | ios::app);

	srand(time(NULL));
	bool res = false;
	bool found1, found2;
	
	while(!res)
	{	
		found1 = found2 = false;
		while(found1 == false)
		{
			osoba1 = (rand() % iloscOsob) + 1;
			found1 = (find(lista.begin(), lista.end(), osoba1) != lista.end());
		}
		while (found2 == false)
		{
			osoba2 = (rand() % iloscOsob) + 1;
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