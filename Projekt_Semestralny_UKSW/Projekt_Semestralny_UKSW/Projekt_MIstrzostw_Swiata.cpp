#define MOC 50
#define MAX 20

#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string.h>
#include<vector>
#include<Windows.h>

using namespace std;

class Druzyna
{
	int id_druzyny;
	char skrot[4];
	char panstwo[MAX];
	int id_kontynent;
	//int mocObr[MOC];
	int mocAtak;
public:
	int punkty;

public:
	int getId_druzyny()
	{
		return this->id_druzyny;
	}
	int getId_kontynent()
	{
		return this->id_kontynent;
	}
	void setId_druzyny(int id)
	{
		this->id_druzyny = id;
	}
	void setId_kontynent(int id)
	{
		this->id_kontynent = id;
	}
	/*void setMocObr(int i, int j)
	{
	this->mocObr[i] = j;
	}*/
	void setMocAtak(int i, int j)
	{
		this->mocAtak = j;
	}
	void setPanstwo(char ps[MAX])
	{
		strcpy(panstwo, ps);
	}
	void setSkrot(char sk[MAX])
	{
		strcpy(skrot, sk);
	}
	char *getPanstwo()
	{
		return this->panstwo;
	}
	char *getSkrot()
	{
		return this->skrot;
	}
	int getMocATK()
	{
		return mocAtak;//war defaultowa
	}
	//int obliczMocOBR()
	//{
	//	return 0;//war defaultowa
	//}

	Druzyna::Druzyna()
	{
		id_druzyny = 0;
		skrot[0] = '\0';
		panstwo[0] = '\0';
		id_kontynent = 0;
		mocAtak = 0;
	}

	Druzyna::Druzyna(int id, char skrot[3], char panstwo[MAX], int id_kontynent, int mocAtak)
	{
		id_druzyny = id;
		strcpy(this->skrot, skrot);
		strcpy(this->panstwo, panstwo);
		this->id_kontynent = id_kontynent;
		this->mocAtak = mocAtak;
	}

	int strzelajBramki()
	{
		double bramki = rand() % 10000;
		bramki /= 100;
		int mA = mocAtak * 10 - 15;

		if (bramki <= mA)
			return 1;
		mA += mocAtak * 10 / 2;
		if (bramki <= mA + mA / 2)
			return 2;
		mA += mocAtak * 10 / 3;
		if (bramki <= mA + mA / 2)
			return 3;
		mA += mocAtak * 10 / 4;
		if (bramki <= mA + mA / 2)
			return 4;
		else return 0;
	}

	Druzyna(const Druzyna &d)
	{
		id_druzyny = d.id_druzyny;
		strcpy(skrot, d.skrot);
		strcpy(panstwo, d.panstwo);
		id_kontynent = d.id_kontynent;
		mocAtak = d.mocAtak;
	}

};

class Koszyk :public Druzyna
{
protected:
	int bramkiStraconeOgolem;
	int bramkiStrzeloneOgolem;
	int punkty;
	char grupa;
	bool czyAwans;
	friend vector<Druzyna> wyborKont(vector<Druzyna> &v, int size, int wyb);
	friend class Grupa;
public:
	int strzelone;

	char getGrupa()
	{
		return grupa;
	}

	Koszyk()
	{
		strzelone = 0;
		bramkiStraconeOgolem = 0;
		bramkiStrzeloneOgolem = 0;
		punkty = 0;
		grupa = 'A';
		czyAwans = false;
	}

	Koszyk(Druzyna dr, int strzelone, int bramkiStraconeOgolem, int bramkiStrzeloneOgolem, int punkty, char grupa, bool czyAwans)
		:Druzyna(dr)
	{
		this->strzelone = strzelone;
		this->bramkiStraconeOgolem = bramkiStraconeOgolem;
		this->bramkiStrzeloneOgolem = bramkiStrzeloneOgolem;
		this->punkty = punkty;
		this->grupa = grupa;
		this->czyAwans = czyAwans;
	}

	int losuj()
	{
		int los = rand() % 10000;
		return (los /= 100);
	}

	Koszyk rozgrywkiFinalowe(Koszyk druzynaB)
	{
		printf("Mecz miedzy %20s vs %-20s\n", getPanstwo(), druzynaB.getPanstwo());
		this->strzelone = strzelajBramki();
		druzynaB.strzelone = druzynaB.strzelajBramki();
		this->bramkiStrzeloneOgolem += this->strzelone;
		druzynaB.bramkiStraconeOgolem += druzynaB.strzelone;
		printf("Wynik\t%i : %i\n", this->strzelone, druzynaB.strzelone);
		if (this->strzelone == druzynaB.strzelone)
		{
			int bramkiA = 0, bramkiB = 0;
			for (int i = 0; i < 5; i++) {
				int karneA = losuj();
				int karneB = losuj();
				int mA = this->getMocATK() * 10;
				if (karneA < mA)
					bramkiA++;
				int mB = druzynaB.getMocATK() * 10;
				if (karneB < mB)
					bramkiB++;
			}
			while (1) {

				if (bramkiA > bramkiB) {
					printf("Rzuty karne: %i:%i\n", bramkiA, bramkiB);
					printf("Awans dru¿yna:\t%s\n\n", this->getPanstwo());
					this->strzelone = 0;
					druzynaB.strzelone = 0;
					return *this;
					break;
				}
				else if (bramkiA < bramkiB) {
					printf("Rzuty karne: %i:%i\n", bramkiA, bramkiB);
					printf("Awans dru¿yna:\t%s\n\n", druzynaB.getPanstwo());
					this->strzelone = 0;
					druzynaB.strzelone = 0;
					return druzynaB;
					break;
				}
				else {
					do {
						int karneA = losuj();
						int karneB = losuj();
						int mA = this->getMocATK() * 10;
						if (karneA < mA)
							bramkiA++;
						int mB = druzynaB.getMocATK() * 10;
						if (karneB<mB)
							bramkiB++;
					} while (bramkiA == bramkiB);
					continue;
				}

			}
		}
		if (this->strzelone > druzynaB.strzelone) {
			printf("Awans dru¿yna:\t%s\n\n", this->getPanstwo());
			this->strzelone = 0;
			druzynaB.strzelone = 0;
			return *this;
		}
		else {
			printf("Awans dru¿yna:\t%s\n\n", druzynaB.getPanstwo());
			this->strzelone = 0;
			druzynaB.strzelone = 0;
			return druzynaB;
		}
	}

};

class Grupa {

	Koszyk *grupa = new Koszyk[4];
	friend class Koszyk;
public:

	void losowanieGrup(Druzyna vA, Druzyna vB, Druzyna vC, Druzyna vD, char gr)
	{
		Koszyk druzyna = Koszyk(vA, 0, 0, 0, 0, gr, false);
		grupa[0] = druzyna;
		Koszyk druzyna1 = Koszyk(vB, 0, 0, 0, 0, gr, false);
		grupa[1] = druzyna1;
		Koszyk druzyna2 = Koszyk(vC, 0, 0, 0, 0, gr, false);
		grupa[2] = druzyna2;
		Koszyk druzyna3 = Koszyk(vD, 0, 0, 0, 0, gr, false);
		grupa[3] = druzyna3;
	}

	Koszyk getDruzyna(int i)
	{
		return grupa[i];
	}

	Koszyk * rozgrywkiGrupowe()
	{
		cout << "+--------------------------------------+" << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = i + 1; j < 4; j++)
			{
				grupa[i].strzelone = grupa[i].strzelajBramki();
				grupa[j].strzelone = grupa[j].strzelajBramki();
				if (grupa[i].strzelone > grupa[j].strzelone)
				{
					grupa[i].punkty += 3;
					grupa[i].bramkiStrzeloneOgolem += grupa[i].strzelone;
					grupa[j].bramkiStraconeOgolem += grupa[i].strzelone;
					grupa[i].strzelone = 0;
					grupa[j].strzelone = 0;
				}
				else if (grupa[i].strzelone < grupa[j].strzelone)
				{
					grupa[j].punkty += 3;
					grupa[j].bramkiStrzeloneOgolem += grupa[j].strzelone;
					grupa[j].bramkiStraconeOgolem += grupa[j].strzelone;
					grupa[i].strzelone = 0;
					grupa[j].strzelone = 0;
				}
				else
				{
					grupa[j].punkty += 1;
					grupa[i].punkty += 1;
					grupa[i].bramkiStrzeloneOgolem += grupa[i].strzelone;
					grupa[j].bramkiStraconeOgolem += grupa[i].strzelone;
					grupa[j].bramkiStrzeloneOgolem += grupa[j].strzelone;
					grupa[j].bramkiStraconeOgolem += grupa[j].strzelone;
					grupa[i].strzelone = 0;
					grupa[j].strzelone = 0;
				}

			}
		}
		for (int j = 0; j < 4 - 1; j++)
			for (int i = 0; i < 4 - 1; i++)
				if (grupa[i].punkty < grupa[i + 1].punkty) swap(grupa[i], grupa[i + 1]);

		cout << "Tabela grupy " << grupa[1].getGrupa() << endl;
		printf("%20s  %5s  %3i  %3i  %i\n", grupa[0].getPanstwo(), grupa[0].getSkrot(), grupa[0].bramkiStraconeOgolem, grupa[0].bramkiStrzeloneOgolem, grupa[0].punkty);
		printf("%20s  %5s  %3i  %3i  %i\n", grupa[1].getPanstwo(), grupa[1].getSkrot(), grupa[1].bramkiStraconeOgolem, grupa[1].bramkiStrzeloneOgolem, grupa[1].punkty);
		printf("%20s  %5s  %3i  %3i  %i\n", grupa[2].getPanstwo(), grupa[2].getSkrot(), grupa[2].bramkiStraconeOgolem, grupa[2].bramkiStrzeloneOgolem, grupa[2].punkty);
		printf("%20s  %5s  %3i  %3i  %i\n", grupa[3].getPanstwo(), grupa[3].getSkrot(), grupa[3].bramkiStraconeOgolem, grupa[3].bramkiStrzeloneOgolem, grupa[3].punkty);
		return grupa;
	}

	Grupa *losowanieKoszykow(vector<Druzyna> &eur, vector<Druzyna> &azj, vector<Druzyna> &afr, vector<Druzyna> &ampld, vector<Druzyna> &ampln)
	{
		Grupa *gr = new Grupa[8];
		vector<Druzyna> wektor;
		for (int i = 0; i < eur.size(); i++)
		{
			wektor.push_back(eur[i]);
		}
		for (int i = 0; i < azj.size(); i++)
		{
			wektor.push_back(azj[i]);
			wektor.push_back(afr[i]);
		}
		for (int i = 0; i < ampln.size(); i++)
		{
			wektor.push_back(ampln[i]);
		}
		for (int i = 0; i < ampld.size(); i++)
		{
			wektor.push_back(ampld[i]);
		}
		wektor.push_back(Druzyna(0, "RUS", "Rosja", 2, 4));
		wektor.push_back(Druzyna(101, "NEZ", "Nowa Zelandia", 3, 3));
		for (int j = 0; j < wektor.size() - 1; j++)
			for (int i = 0; i < wektor.size() - 1; i++)
				if (wektor[i].getMocATK() < wektor[i + 1].getMocATK()) swap(wektor[i], wektor[i + 1]);
		char czar = 'A';
		for (int i = 0, k = 0; i < 8; i++, k++, czar++)
		{
			gr[i].losowanieGrup(wektor[k], wektor[k + 8], wektor[k + 16], wektor[k + 24], czar);
		}
		return gr;
	}
};

void wypiszTabele(const vector<Koszyk> &vA, const vector<Koszyk> &vB, const vector<Koszyk> &vC, const vector<Koszyk> &vD, const vector<Koszyk> &vE, const vector<Koszyk> &vF, const vector<Koszyk> &vG, const vector<Koszyk> &vH)
{
	cout << "+-----------------------+-----------------------+";
	cout << "+       Grupa A         +       Grupa B         +";
	cout << "+-----------------------+-----------------------+";
	cout << "+       Grupa C         +       Grupa D         +";//12 znaki w kolumnie
	cout << "+-----------------------+-----------------------+";
	cout << "+       Grupa E         +       Grupa F         +";
	cout << "+-----------------------+-----------------------+";
	cout << "+       Grupa G         +       Grupa H         +";
	cout << "+-----------------------+-----------------------+";
}

bool czyBylaWylosowana(int iLiczba, int tab[], int ile)
{
	if (ile <= 0)
		return false;

	int i = 0;
	do {
		if (tab[i] == iLiczba)
			return true;
		i++;
	} while (i < ile);

	return false;
}

void wyswietl(vector<Druzyna> &v, int *tmp, int size, vector<Druzyna> tmpd)
{
	system("cls");
	//vector<Druzyna>tmp;
	int j = 0;
	cout << "                                                      Wybrane dru¿yny" << endl;
	for (int i = 0; i < v.size(); i = i + 2) {
		int ok1 = 1, ok2 = 1;
		cout << "+---+-------------------+---+-------------------+";
		if (j < tmpd.size()) {
			printf("  %15s", tmpd[j].getPanstwo());
			j++;
		}
		putchar('\n');
		printf("|%3i|\t%15s\t|", i + 1, v[i].getPanstwo());
		printf("%3i|\t%15s\t|", i + 2, v[i + 1].getPanstwo());
		if (j < tmpd.size()) {
			printf("  %15s", tmpd[j].getPanstwo());
			j++;
		}
		putchar('\n');
	}
	cout << "+---+-------------------+---+-------------------+" << endl;

}

vector<Druzyna> wyborKont(vector<Druzyna> &v, int size, int wyb)
{

	vector<Druzyna>tmp;
	int * wylosowane = new int[size];
	int wylosowanych = 0;
	if (wyb == 1) {
		do {
			int wybd;
			wyswietl(v, wylosowane, size, tmp);
			cout << "Proszê wybraæ dru¿yny z listy:\n";
			cout << "Twoj wybór:\t";
			cin >> wybd;
			if (czyBylaWylosowana(wybd - 1, wylosowane, wylosowanych) == false)
			{
				tmp.push_back(v[wybd - 1]);//tu bylo v
				wylosowane[wylosowanych] = wybd - 1;
				wylosowanych++;
			}
			else {
				cout << "Dru¿yna ju¿ wybana, proszê wybraæ jeszcze raz" << endl;
				Sleep(1000);
			}
		} while (wylosowanych < size);
		delete[] wylosowane;
	}
	else {
		do {
			int los = rand() % v.size();
			if (czyBylaWylosowana(los, wylosowane, wylosowanych) == false)
			{
				tmp.push_back(v[los]);//tu bylo v
				wylosowane[wylosowanych] = los;
				wylosowanych++;
				cout << "Wczytywanie..." << endl;
				system("cls");
			}
		} while (wylosowanych < size);
		delete[] wylosowane;
	}
	system("cls");
	return tmp;
}

int main()
{
	setlocale(LC_ALL, "");
	cout << "\tWitam w symulatorze mistrzostw œwiata w pi³ce no¿nej!!!" << endl;
	cout << "\n\n";
	cout << "\t\t\t Autor: Adam Kossakowski" << endl;
	cout << "\n\n";
	cout << "\t\t     Wciœnij enter aby przejœæ dalej" << endl;
	char czar;
	scanf("%c", &czar);
	fstream plik;
	Druzyna d;
	vector <Druzyna> AMPlN8;
	vector <Druzyna> AMPLD1;
	vector <Druzyna> EUR2;
	vector <Druzyna> AFR6;
	vector <Druzyna> AZJ5;
	vector <Druzyna> OCE3;
	srand(time(NULL));
	FILE *f;
	if ((f = fopen("input.txt", "r")) == NULL)
		cout << "Blad otwarcia pliku\n";
	else
		cout << "Plik zostal otwarty\n";

	do {
		int id, kont, moc;
		char nap1[MAX], nap2[MAX];
		fscanf(f, "%d" "%s" "%s" "%d" "%d\n", &id, nap1, nap2, &kont, &moc);
		switch (kont)
		{
		case 1:
			AMPLD1.push_back(Druzyna(id, nap1, nap2, kont, moc));
			printf("%d %s %s %i %i\n", id, nap1, nap2, kont, moc);
			break;
		case 2:
			EUR2.push_back(Druzyna(id, nap1, nap2, kont, moc));
			printf("%d %s %s %i %i\n", id, nap1, nap2, kont, moc);
			break;
		case 3:
			OCE3.push_back(Druzyna(id, nap1, nap2, kont, moc));
			printf("%d %s %s %i %i\n", id, nap1, nap2, kont, moc);
			break;
		case 5:
			AZJ5.push_back(Druzyna(id, nap1, nap2, kont, moc));
			printf("%d %s %s %i %i\n", id, nap1, nap2, kont, moc);
			break;
		case 6:
			AFR6.push_back(Druzyna(id, nap1, nap2, kont, moc));
			printf("%d %s %s %i %i\n", id, nap1, nap2, kont, moc);
			break;
		case 8:
			AMPlN8.push_back(Druzyna(id, nap1, nap2, kont, moc));
			printf("%d %s %s %i %i\n", id, nap1, nap2, kont, moc);
			break;
		}
	} while (feof(f) == 0);

	fclose(f);

	vector <Druzyna> AMPlN;
	vector <Druzyna> AMPLD;
	vector <Druzyna> EUR;
	vector <Druzyna> AFR;
	vector <Druzyna> AZJ;
	vector <Druzyna> OCE;
	Grupa *grupa = new Grupa[8];
	Grupa gr;
	Koszyk *rozFin = new Koszyk[8];
	if (czar == '\n')
	{
		system("cls");
		cout << "\t\t\tMenu:" << endl;
		cout << "+----------------------------------------------------+" << endl;
		cout << "+          1       | Samodzielny wybór dru¿yn        +" << endl;
		cout << "+----------------------------------------------------+" << endl;
		cout << "+          2       | Losowy wybór dru¿yn             +" << endl;
		cout << "+----------------------------------------------------+" << endl;
		int wybor = 0;
		do {
			cout << "Podaj czynnoœæ:\t";
			cin >> wybor;
			//dodac funkcje sprawdzaj¹c¹ wprowadzone dane
		} while (wybor != 1 && wybor != 2);

		switch (wybor) {

		case 1:
		{
			EUR = wyborKont(EUR2, 13, 1);
			AMPLD = wyborKont(AMPLD1, 4, 1);
			AMPlN = wyborKont(AMPlN8, 3, 1);
			AFR = wyborKont(AFR6, 5, 1);
			AZJ = wyborKont(AZJ5, 5, 1);
			//czyszczenie
			AMPLD1.clear();
			AMPlN8.clear();
			EUR2.clear();
			AZJ5.clear();
			AFR6.clear();
			//losowanie grup
			grupa = gr.losowanieKoszykow(EUR, AZJ, AFR, AMPLD, AMPlN);
			//czyszczenie
			EUR.clear();
			AMPLD.clear();
			AMPlN.clear();
			AZJ.clear();
			AFR.clear();
			break;
		}
		case 2:
		{
			EUR = wyborKont(EUR2, 13, 2);
			AMPLD = wyborKont(AMPLD1, 4, 2);
			AMPlN = wyborKont(AMPlN8, 3, 2);
			AFR = wyborKont(AFR6, 5, 2);
			AZJ = wyborKont(AZJ5, 5, 2);
			///
			AMPLD1.clear();
			AMPlN8.clear();
			EUR2.clear();
			AZJ5.clear();
			AFR6.clear();
			///losowanie do grup
			grupa = gr.losowanieKoszykow(EUR, AZJ, AFR, AMPLD, AMPlN);
			////czyszczenie
			EUR.clear();
			AMPLD.clear();
			AMPlN.clear();
			AZJ.clear();
			AFR.clear();
			////
			//wypiszTabele(GrA, GrB, GrC, GrD, GrE, GrF, GrG, GrH);
			break;
		}
		}
	}
	////rozgrywki dru¿ynowe
	for (int i = 0; i < 8; i++)
		grupa[i].rozgrywkiGrupowe();
	cout << "+--------------------------------------+" << endl;
	cout << "Rozgrywki 1/8" << endl;
	cout << "+--------------------------------------+" << endl;
	putchar('\n');
	for (int i = 0; i < 8; i = i + 2) {
		rozFin[i] = grupa[i].getDruzyna(0).rozgrywkiFinalowe(grupa[i + 1].getDruzyna(1));
		rozFin[i + 1] = grupa[i].getDruzyna(1).rozgrywkiFinalowe(grupa[i + 1].getDruzyna(0));
	}
	cout << "+--------------------------------------+" << endl;
	cout << "Rozgrywki 1/4" << endl;
	cout << "+--------------------------------------+" << endl;
	putchar('\n');
	for (int i = 0, j = 0; i < 8; i = i + 2)
	{
		rozFin[j] = rozFin[i].rozgrywkiFinalowe(rozFin[i + 1]);
		j++;
	}
	cout << "+--------------------------------------+" << endl;
	cout << "Rozgrywki 1/2" << endl;
	cout << "+--------------------------------------+" << endl;
	putchar('\n');
	for (int j = 0, i = 0; i < 4; i = i + 2, j++) {
		rozFin[j] = rozFin[i].rozgrywkiFinalowe(rozFin[i + 1]);
	}
	cout << "+--------------------------------------+" << endl;
	cout << "Fina³" << endl;
	cout << "+--------------------------------------+" << endl;
	putchar('\n');
	rozFin[0] = rozFin[0].rozgrywkiFinalowe(rozFin[1]);
	cout << "+--------------------------------------+" << endl;
	cout << "Mistrzostwa Œwiata w Pi³ce No¿nej wygra³a dru¿yna " << rozFin[0].getPanstwo() << endl;
	cout << "Gratulacje!!!!!" << endl;
}

