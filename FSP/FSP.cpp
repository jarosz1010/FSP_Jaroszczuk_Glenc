// FSP.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
using namespace std;


int koszt1; 
int koszt2;
int czas;
int liczba;
int maszyny;
vector<vector<int>> P;
vector<vector<int>> Z;

vector<vector<int>> tab;

/*********************************************************************
Struktura wczytanej tablicy:
lp || czas na 1 maszynie || czas na 2 maszynie
Pamietac o tym ze przez dodanie liczby pozycyjnej indeksy przesuwaja sie o jeden!


**************************************************************************/

void Wczytaj(string Nazwapliku) {
	string linia;
	fstream plik;
	
	plik.open(Nazwapliku, ios::in);
	if (plik.good() == true)
	{
		plik >> liczba;
		plik >> maszyny;
		string pomoc1, pomoc2;
		
		for (int i = 0; i < liczba; i++)
		{
			int tmp;
		
				vector<int> v1;
				v1.push_back(i); // Wrzucamy jaka to kolejnosc
				for (int j = 0; j < maszyny; j++) {
					plik >> pomoc1 >> tmp;
					v1.push_back(tmp);
					
				}
				tab.push_back(v1);
			
		}
		plik.close();
	}
}

int Oblicz(vector<vector<int>> tabela) {
	int koszt = 0;
	for (int i = 0; i < liczba; i++)
	{
		int tmp = tabela[0][1];
		vector<int> v1;
		vector<int> v2;
		for (int j = 0; j < maszyny; j++) {
			// Zeby przsunac indeks przez dodanie liczby pozycyjnej
			int przesuwacz = j + 1;
			// Tam gdzie jest odwolanie do poprzedniego wiersza tablicy P lub Z
			// nie musimy przesuwac bo to jest inna tablica

			if (i > 0) {
				v1.push_back(P[i-1][j]+tabela[i-1][przesuwacz]);
				v2.push_back(Z[i-1][j]+tabela[i][przesuwacz]);
			}
			 else if(i==0 && j==0) {
				v1.push_back(0);
				v2.push_back(tmp);
			}
			else if(i == 0 && j>0) {
				v1.push_back(tabela[i][j]);
				tmp = tmp + tabela[i][przesuwacz];
				v2.push_back(tmp);
			}
		}
		P.push_back(v1);
		Z.push_back(v2);

	}
	koszt = Z[liczba - 1][maszyny - 1];
	return koszt;
}


void BruteForce(vector<vector<int>>& tabela, int poz = 0) {

	if (poz == liczba) {
		czas = Oblicz(tabela);

		koszt2 = min(koszt2, czas);

	}
	else {
		for (int i = poz; i < liczba; i++) {
			for (int j = 0; j < maszyny; j++) {
				swap(tabela[i][j], tabela[poz][j]);
			}
			BruteForce(tabela, poz + 1);
			for (int j = 0; j < maszyny; j++) {
				swap(tabela[i][j], tabela[poz][j]);
			}
		}
	}

}

int main()
{
	Wczytaj("data001.txt");
	koszt1 = Oblicz(tab);
	cout << "Koszt bez zmiany:  " << koszt1 << endl;
	koszt2 = koszt1;
	BruteForce(tab, 0);
	cout << "Koszt po Brute forcie:  " << koszt2 << endl;
}

