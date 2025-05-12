#include "DominoClass.h"
using namespace std;
kosc* PlayerMoveSet::znajdz_ruch() {
	usun_liste_mozliwych();
	Player& gracz = gracz_ref;
	Stol& stol = stol_ref;
	kosc* temp_gracza_g = gracz.gracz_glowa;
	kosc* mozliwe_ruchy = nullptr;
	kosc* mozliwe_glowa = nullptr;
	kosc* mozliwe_ogon = nullptr;
	if (stol.kosci_na_stole_glowa && stol.kosci_na_stole_ogon) {
		kosc* temp_gracza_g = gracz.gracz_glowa;

		while (temp_gracza_g != nullptr) {
			bool pasuje = (stol.kosci_na_stole_glowa->oczko1 == temp_gracza_g->oczko1 ||
				stol.kosci_na_stole_glowa->oczko1 == temp_gracza_g->oczko2 ||
				stol.kosci_na_stole_ogon->oczko2 == temp_gracza_g->oczko1 ||
				stol.kosci_na_stole_ogon->oczko2 == temp_gracza_g->oczko2);

			if (pasuje) {
				kosc* nowy = new kosc{ temp_gracza_g->oczko1, temp_gracza_g->oczko2, nullptr, nullptr };

				if (!mozliwe_glowa) {
					mozliwe_glowa = nowy;
					mozliwe_ogon = nowy;
				}
				else {
					mozliwe_ogon->next = temp_gracza;
					temp_gracza->prev = mozliwe_ogon;
					mozliwe_ogon = temp_gracza;
				}
			}
			temp_gracza_g = temp_gracza_g->next;
		}
	}
	kosc* temp = mozliwe_glowa;
	int i = 1;
	cout << endl << endl << "Mozliwe ruchy do wykonania:" << endl << endl;
	while (temp != nullptr) {
		cout << i << ". [" << temp->oczko1 << "|" << temp->oczko2 << "]     ";
		temp = temp->next;
		++i;
	}
	cout << endl;
	lista_mozliwych = mozliwe_glowa;
	return lista_mozliwych;
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
kosc* HumanPlayer::wykonaj_ruch(){
	Player& gracz = gracz_ref;
	kosc* temp0 = lista_mozliwych;
	int i = 0;
	while (temp0 != nullptr) {
		temp0 = temp0->next;
		++i;
	}
	int wybor = 0;
	cout << "wybierz kosc ktora chcesz wylozyc:" << endl << endl;
	cin >> wybor;
	while (wybor < 1 || wybor>i) {
		cout << "Blad! Masz do wyboru "<<i<<" kosci." << endl;
		cout << "Wybierz kosc ktora chcesz wylozyc:" << endl << endl;
		cin >> wybor;
	}
	
	kosc* wybrana = lista_mozliwych;
	for (int i = 1; i < wybor; ++i) {
		if (wybrana != nullptr)
			wybrana = wybrana->next;
	}

	kosc* temp = gracz.gracz_glowa;
	while (temp != nullptr) {
		bool takie_same =
			(temp->oczko1 == wybrana->oczko1 && temp->oczko2 == wybrana->oczko2) ||
			(temp->oczko1 == wybrana->oczko2 && temp->oczko2 == wybrana->oczko1);

		if (takie_same) {
			break;
		}
		temp = temp->next;
	}
	if (temp != nullptr) {
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
	cout << "blad krytyczny! Nie znaleziono wybranej kosci. Nawet program nie wie jak sie tu znalazles :P." << endl;
	return nullptr;
}
kosc* AIPlayer::wykonaj_ruch() {
	Player& gracz = gracz_ref;
	kosc* wybrana = lista_mozliwych;
	kosc* temp = gracz.gracz_glowa;
	while (temp != nullptr) {
		bool takie_same =
			(temp->oczko1 == wybrana->oczko1 && temp->oczko2 == wybrana->oczko2) ||
			(temp->oczko1 == wybrana->oczko2 && temp->oczko2 == wybrana->oczko1);

		if (takie_same) {
			break;
		}
		temp = temp->next;
	}
	if (temp != nullptr) {
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
	cout << "blad krytyczny! Nie znaleziono wybranej kosci. Nawet program nie wie jak sie tu znalazles :P." << endl;
	return nullptr;
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
	cout << endl << "brak pasujacych kosci. dobierasz nowa kosc." << endl << endl;
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
		kosc* temp = lista_mozliwych->next;
		delete lista_mozliwych;
		lista_mozliwych = temp;
	}
}
PlayerMoveSet::~PlayerMoveSet() {
	while (lista_mozliwych) {
		kosc* temp = lista_mozliwych->next;
		delete lista_mozliwych;
		lista_mozliwych = temp;
	}
}