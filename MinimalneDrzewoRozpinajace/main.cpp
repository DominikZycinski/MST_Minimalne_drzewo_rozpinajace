//Dominik Zycinski
//MST
//25.04.17

#include <iostream>
#include <string>

using namespace std;



class Object
{
public:
	long key;
	std::string text;

	long bokA;
	long bokB;
	long waga;

	string bok1;
	string bok2;
	Object(long k, std::string s)
	{
		key = k;
		text = s;
	}
	void wyswietl()
	{
		cout << key << " " << text << endl;
	}
	Object()
	{}
	~Object()
	{}
};

class Indeks
{
public:
	std::string nazwa;
	long numer;
	long indeks;
};

class Bok
{
public:
	Object *tabelaB;//tabela z wagami bokow
	Indeks *tabelaW;//tabela z wierzcholkami
	Object *tabela3;//tabela pomocnicza
	long wagamst;


	long rozmiarbok;
	long rozmiarW;



	void size(long x)//rozmiar tabeli z bokami
	{
		rozmiarbok = x;
		tabelaB = new Object[rozmiarbok];
		tabela3 = new Object[rozmiarbok];
		for (int i = 0; i < x; i++)
		{
			tabelaB[i].waga = NULL;
			tabela3[i].bokA = NULL;
			tabela3[i].bokB = NULL;
			tabela3[i].waga = NULL;

		}
	}

	void size2(long x2)//rozmiar tabeli z wierzcholkami
	{
		rozmiarW = x2;
		tabelaW = new Indeks[rozmiarW + 1];
		for (int i = 0; i < x2; i++)
		{
			tabelaW[i].indeks = 'E';
		}

	}

	void add(int a, int b, int c)//dodawanie polaczen bokow, razme z wagami
	{
		for (int i = 0; i < rozmiarbok; i++)
		{
			if (tabelaB[i].waga == NULL)
			{

				tabelaB[i].bokA = a;
				tabelaB[i].bokB = b;
				tabelaB[i].waga = c;
				break;
			}
		}



	}

	void sortowanie()
	{

		//sortowanie babelkowe
		int min, bufor, bufor2, bufor3;
		for (int i = 0; i<rozmiarbok - 1; i++)
		{

			min = i;

			for (int j = i + 1; j<rozmiarbok; j++)
			{
				if (tabelaB[j].waga<tabelaB[min].waga)
					min = j;
			}

			bufor = tabelaB[min].waga;
			tabelaB[min].waga = tabelaB[i].waga;
			tabelaB[i].waga = bufor;

			bufor2 = tabelaB[min].bokA;
			tabelaB[min].bokA = tabelaB[i].bokA;
			tabelaB[i].bokA = bufor2;

			bufor3 = tabelaB[min].bokB;
			tabelaB[min].bokB = tabelaB[i].bokB;
			tabelaB[i].bokB = bufor3;
		}

	}



	void dodawanie(int klu, std::string nam, int it)//dodawanie wierzcholkow
	{
		for (int i = 0; i < rozmiarW; i++)
		{
			if (tabelaW[i].indeks == 'E')
			{

				tabelaW[i].numer = klu;
				tabelaW[i].nazwa = nam;
				tabelaW[i].indeks = it;
				break;
			}
		}


	}
	void drukuj()
	{
		std::string nameB1, nameB2;

		for (int i = 0; i < rozmiarbok; i++)
		{
			if (tabela3[i].waga != 0)
			{
				for (int j = 0; j < rozmiarW; j++)
				{
					if (tabela3[i].bokA == tabelaW[j].numer)//jezeli znajde taki sam bok w tabeli z wierzcholkami to
															//biore jego nazwe i przypisuje do zmiennej 
						nameB1 = tabelaW[j].nazwa;
					if (tabela3[i].bokB == tabelaW[j].numer)
						nameB2 = tabelaW[j].nazwa;
				}

				cout << nameB1 << " " << nameB2 << " " << tabela3[i].waga << endl;
			}
		}
	}

	void mst()
	{
		int a, b;
		int x, y;
		for (int i = 0; i < rozmiarbok; i++)
		{
			a = tabelaB[i].bokA;
			b = tabelaB[i].bokB;
			for (int j = 0; j < rozmiarW; j++)
			{
				//szukam bokow w tabeli z wierzcholkami oraz ich indeksow
				if (tabelaW[j].numer == a)
				{
					x = tabelaW[j].indeks;//przypisuje do zmiennej indeks wierzcholka
				}

				if (tabelaW[j].numer == b)
				{
					y = tabelaW[j].indeks;
				}
			}

			if (x != y)//jezeli indeksy sa rozne
			{
				//tworze drzewo 
				tabela3[i].bokA = tabelaB[i].bokA;
				tabela3[i].bokB = tabelaB[i].bokB;
				tabela3[i].waga = tabelaB[i].waga;


				for (int j = 0; j < rozmiarW; j++)
				{
					//jezeli w tablicy z wierzcholkami wystapi indeks taki jak pierwsza liczba, to zmieniam go 
					if (tabelaW[j].indeks == x)
						tabelaW[j].indeks = y;
				}
			}

		}


	}




};

int main()
{

	Bok b;
	long n;//ilosc wierzcholkow
	long m;//ilosc polaczen bokow
	cin >> n;
	long klucz;
	string text;
	long p;
	b.size2(n);//rozmiar tabeli z wierzcholkami

			   //zapisuje klucz, tekst i indeksy  do tablicy
	for (int i = 0; i < n; i++)
	{

		cin >> klucz;
		cin >> text;

		b.dodawanie(klucz, text, i);


	}

	cin >> m;

	b.size(m);
	int x;
	int y;
	int wart;
	for (int i = 0; i < m; i++)
	{
		cin >> x;
		cin >> y;
		cin >> wart;
		b.add(x, y, wart);

	}
	b.sortowanie();

	b.mst();
	b.drukuj();



	delete[] b.tabela3;
	delete[] b.tabelaB;
	delete[] b.tabelaW;

	return 0;
};
