#include "DominoClass.h"
using namespace std;
//tworzy liste WSKAZNIKOW na kosci w liscie gracza
mozliwy_ruch* PlayerMoveSet::znajdz_ruch() {
	usun_liste_mozliwych();

	Player& gracz = gracz_ref;
	Stol& stol = stol_ref;
	kosc* temp = gracz.gracz_glowa;

	mozliwy_ruch* glowa = nullptr;
	mozliwy_ruch* ogon = nullptr;

	if (stol.kosci_na_stole_glowa && stol.kosci_na_stole_ogon) {
		while (temp) {
			bool pasuje =
				stol.kosci_na_stole_glowa->oczko1 == temp->oczko1 ||
				stol.kosci_na_stole_glowa->oczko1 == temp->oczko2 ||
				stol.kosci_na_stole_ogon->oczko2 == temp->oczko1 ||
				stol.kosci_na_stole_ogon->oczko2 == temp->oczko2;

			if (pasuje) {
				mozliwy_ruch* nowy = new mozliwy_ruch{ temp, nullptr };

				if (!glowa) {
					glowa = nowy;
					ogon = nowy;
				}
				else {
					ogon->next = nowy;
					ogon = nowy;
				}
			}

			temp = temp->next;
		}
	}
	if (glowa == nullptr) {
		dobierz_kosc();
		return znajdz_ruch();
	}
	lista_mozliwych = glowa;
	wypisz_mozliwe_ruchy();
	return lista_mozliwych;
}
void HumanPlayer::wypisz_mozliwe_ruchy() {
	mozliwy_ruch* temp = lista_mozliwych;
	int i = 1;
	cout << "Mozliwe ruchy do wykonania:\n\n";
	while (temp) {
		cout << i << ". [" << temp->wskaznik_na_kosc->oczko1
			<< "|" << temp->wskaznik_na_kosc->oczko2 << "]     ";
		temp = temp->next;
		++i;
	}
	cout << "\n\n";
}
void AIPlayer::wypisz_mozliwe_ruchy() {
	cout << endl << endl;
}
kosc* HumanPlayer::pierwszy_ruch(){
	Player& gracz = gracz_ref;
	cout <<endl<<endl<<"Wybierz kosc ktora chcesz wylozyc na poczatek:"<<endl<<endl;
	int wybor = 0;
	cin >> wybor;
	while (wybor < 1 || wybor>7) {
		cout << "Blad! Masz do wyboru 7 kosci." << endl;
		cout << "Wybierz kosc ktora chcesz wylozyc na poczatek:" << endl << endl;
		cin >> wybor;
	}
	kosc* temp = gracz.gracz_glowa;
	for (int i = 0; i < wybor - 1; ++i) {
		temp = temp->next;
	}
	if (temp->prev != nullptr) {
		temp->prev->next = temp->next;
	}
	else {
		gracz.gracz_glowa = temp->next;
	}
	if (temp->next != nullptr) {
		temp->next->prev = temp->prev;
	}
	else {
		gracz.gracz_ogon = temp->prev;
	}
	temp->next = nullptr;
	temp->prev = nullptr;

	return temp;
}
kosc* AIPlayer::pierwszy_ruch() {
	Player& gracz = gracz_ref;
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<> distrib(1, 7);
	int losuj = distrib(gen);
	kosc* temp = gracz.gracz_glowa;
	for (int i = 0; i < losuj - 1; ++i) {
		temp = temp->next;
	}
	if (temp->prev != nullptr) {
		temp->prev->next = temp->next;
	}
	else {
		gracz.gracz_glowa = temp->next;
	}
	if (temp->next == nullptr) {
		temp->next->prev = temp->prev;
	}
	else {
		gracz.gracz_ogon = temp->prev;
	}
	temp->next = nullptr;
	temp->prev = nullptr;

	return temp;
}
kosc* HumanPlayer::wykonaj_ruch() {
	Player& gracz = gracz_ref;
	mozliwy_ruch* temp = lista_mozliwych;

	int i = 0;
	while (temp) {
		++i;
		temp = temp->next;
	}

	cout << "Wybierz kosc : ";
	int wybor = 0;
	cin >> wybor;

	while (wybor < 1 || wybor > i) {
		cout << "Bledny wybor, sprobuj ponownie: ";
		cin >> wybor;
	}

	mozliwy_ruch* wybrany = lista_mozliwych;
	for (int j = 1; j < wybor; ++j) {
		wybrany = wybrany->next;
	}

	kosc* k = wybrany->wskaznik_na_kosc;

	if (k->prev)
		k->prev->next = k->next;
	else
		gracz.gracz_glowa = k->next;

	if (k->next)
		k->next->prev = k->prev;
	else
		gracz.gracz_ogon = k->prev;

	k->next = nullptr;
	k->prev = nullptr;

	return k;
}
kosc* AIPlayer::wykonaj_ruch() {
	Player& gracz = gracz_ref;
	mozliwy_ruch* temp = lista_mozliwych;
	int wybor = 0;

	mozliwy_ruch* wybrany = lista_mozliwych;
	for (int j = 1; j < wybor; ++j) {
		wybrany = wybrany->next;
	}

	kosc* k = wybrany->wskaznik_na_kosc;

	if (k->prev)
		k->prev->next = k->next;
	else
		gracz.gracz_glowa = k->next;

	if (k->next)
		k->next->prev = k->prev;
	else
		gracz.gracz_ogon = k->prev;

	k->next = nullptr;
	k->prev = nullptr;

	return k;
}
bool PlayerMoveSet::czy_dobierz() {
	if (lista_mozliwych == nullptr) {
		return true;
	}
	else return false;
}
void PlayerMoveSet::dobierz_kosc() {
	Player& gracz = gracz_ref;
	Stol& stol = stol_ref;
	kosc* dobierz = stol.losuj_i_usun();
	if (dobierz == nullptr) return;
	cout << endl << "brak pasujacych kosci. gracz dobiera kosc." << endl;
	if (gracz.gracz_glowa == nullptr) {
		gracz.gracz_glowa = dobierz;
		gracz.gracz_ogon = dobierz;
		dobierz->next = nullptr;
		dobierz->prev = nullptr;
	}
	else {
		dobierz->prev = gracz.gracz_ogon;
		gracz.gracz_ogon->next = dobierz;
		gracz.gracz_ogon = dobierz;
		gracz.gracz_ogon->next = nullptr;
	}
}
void PlayerMoveSet::usun_liste_mozliwych() {
	while (lista_mozliwych) {
		mozliwy_ruch* temp = lista_mozliwych->next;
		delete lista_mozliwych;
		lista_mozliwych = temp;
	}
}
PlayerMoveSet::~PlayerMoveSet() {
	while (lista_mozliwych) {
		mozliwy_ruch* temp = lista_mozliwych->next;
		delete lista_mozliwych;
		lista_mozliwych = temp;
	}
}