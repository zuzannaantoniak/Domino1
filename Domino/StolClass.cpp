#include "DominoClass.h"
using namespace std;
//losuje jedna kosc z dostepnych i usuwa ja z tej listy
kosc* Stol::losuj_i_usun() {
	random_device rand;
	mt19937 gen(rand());
	int dlugosc = 0;
	kosc* pom = dostepne_kosci_glowa;
	while (pom!=nullptr) {
		++dlugosc;
		pom = pom->next;
	}
	if (dlugosc == 0) return nullptr;
	uniform_int_distribution<> distrib(0, dlugosc - 1);
	int losuj = distrib(gen);
	if (!dostepne_kosci_glowa) return nullptr;

	kosc* usun = dostepne_kosci_glowa;
	for (int j = 0; j < losuj; ++j) {
		if (losuj == 0) {
			usun = dostepne_kosci_glowa;
		}
		usun = usun->next;
	}

	if (!usun) return nullptr;

	if (usun->prev!= nullptr) usun->prev->next = usun->next;
	else dostepne_kosci_glowa = usun->next;

	if (usun->next!=nullptr) usun->next->prev = usun->prev;
	else dostepne_kosci_ogon = usun->prev;

	usun->prev = nullptr;
	usun->next = nullptr;

	return usun;
}
void Stol::wypisz_kosci_na_stole() {
	kosc* glowa = kosci_na_stole_glowa;
	cout << "Kosci na stole:" << endl << endl;
	int counter = 0;
	const int MAX_KOSCI = 28;
	while (glowa != nullptr&&counter<MAX_KOSCI) {
		cout <<"[" << glowa->oczko1 << "|" << glowa->oczko2 <<"] ";
		glowa = glowa->next;
		++counter;
	}
	cout << endl << endl;
}
void Stol::doloz_kosc(kosc* nowa) {
	nowa->next = nullptr;
	nowa->prev = nullptr;
	if (kosci_na_stole_glowa == nullptr) {
		kosci_na_stole_glowa = nowa;
		kosci_na_stole_ogon = nowa;
		nowa->next = nullptr;
		nowa->prev = nullptr;
		return;
	}
	int wartosc_na_glowie = kosci_na_stole_glowa->oczko1;
	if (nowa->oczko1 == wartosc_na_glowie) {
		swap(nowa->oczko1, nowa->oczko2);
	}
	if (nowa->oczko2 == wartosc_na_glowie) {

		nowa->next = kosci_na_stole_glowa;
		nowa->prev = nullptr;
		kosci_na_stole_glowa->prev = nowa;
		kosci_na_stole_glowa = nowa;
		return;
	}


	int wartosc_na_ogonie = kosci_na_stole_ogon->oczko2;
	if (nowa->oczko2 == wartosc_na_ogonie) {

		swap(nowa->oczko1, nowa->oczko2);
	}
	if (nowa->oczko1 == wartosc_na_ogonie) {
		nowa->prev = kosci_na_stole_ogon;
		nowa->next = nullptr;
		kosci_na_stole_ogon->next = nowa;
		kosci_na_stole_ogon = nowa;
		return;
	}
	cout << "Blad: Kosc [" << nowa->oczko1 << "|" << nowa->oczko2 << "] nie pasuje do glowy ["
		<< kosci_na_stole_glowa->oczko1 << "] ani ogona ["
		<< kosci_na_stole_ogon->oczko2 << "]." << endl;
}
//tworzy liste kosci do gry
Stol::Stol() {
	dostepne_kosci_glowa = nullptr;
	dostepne_kosci_ogon = nullptr;
	for (int i = 0; i <= 6; ++i) {
		for (int j = i; j <= 6; ++j) {
			kosc* nowy = new kosc{ i,j,nullptr,dostepne_kosci_ogon };
			if (dostepne_kosci_ogon != nullptr) {
				dostepne_kosci_ogon->next = nowy;
			}
			else {
				dostepne_kosci_glowa = nowy;
			}
			dostepne_kosci_ogon = nowy;
		}
	}
	dostepne_kosci_ogon->next = nullptr;
}
//destruktor
Stol::~Stol() {
	cout << "Destruktor Stol\n";
	while (dostepne_kosci_glowa != nullptr) {
		kosc* temp = dostepne_kosci_glowa->next;
		delete dostepne_kosci_glowa;
		dostepne_kosci_glowa = temp;
	}
	dostepne_kosci_glowa = nullptr;
	dostepne_kosci_ogon = nullptr;
	while (kosci_na_stole_glowa != nullptr) {
		kosc* temp = kosci_na_stole_glowa->next;
		delete kosci_na_stole_glowa;
		kosci_na_stole_glowa = temp;
	}
	kosci_na_stole_glowa = nullptr;
	kosci_na_stole_ogon = nullptr;
}