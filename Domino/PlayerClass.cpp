#include "DominoClass.h"
using namespace std;
//losuje 7 kosci startowych dla gracza
Player::Player(Stol&stol):stol_ref(stol) {
	gracz_glowa = nullptr;
	gracz_ogon = nullptr;
	for (int i = 0; i < 7; ++i) {
		kosc* nowa = stol_ref.losuj_i_usun();

		nowa->prev = gracz_ogon;
		if (gracz_ogon) {
			gracz_ogon->next = nowa;
		}
		else {
			gracz_glowa = nowa;
		}
		gracz_ogon = nowa;
	}
	points = 0;
}
//wypisuje kosci gracza
void Player::wypisz()const {
	kosc* temp = gracz_glowa;
	int i = 1;
	while (temp != nullptr) {
		cout <<i<<". ["<< temp->oczko1 << "|" << temp->oczko2 << "]     ";
		temp = temp->next;
		++i;
	}
	cout << endl;
}
void Player::licz_punkty_tura() {
	Stol& stol = stol_ref;
	int pom = stol.dostepne_kosci_glowa->oczko1 + stol.dostepne_kosci_ogon->oczko2;
	if (pom % 5 == 0) {
		points += pom;
	}
}
//destruktor
Player::~Player() {
	while (gracz_glowa != nullptr) {
		kosc* temp = gracz_glowa->next;
		delete gracz_glowa;
		gracz_glowa = temp;
	}
}
bool tura_Human_AI(Stol& stol, HumanPlayer& human, Player& graczH, AIPlayer& komputer, Player& graczAI) {
	cout << "--------------------------------------------------------" << endl;
	cout << " ruch gracza: " << graczH.getnickname() << endl;
	cout << "kosci: " << endl << endl;
	graczH.wypisz();
	if (human.znajdz_ruch()) {
		kosc* ruch_human = human.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		graczH.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		cout << "brak mozliwych ruchow. gracz pomija ture." << endl;
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Gra zakoñczona remisem.\n";
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (graczH.gracz_glowa == nullptr) {
		cout << endl << "gracz "<<graczH.getnickname()<<" wygral";
		return true;
	}
	cout << "--------------------------------------------------------" << endl;
	cout << "ruch komputera: " << endl;
	if(komputer.znajdz_ruch()){
		kosc* ruch_AI = komputer.wykonaj_ruch();
		stol.doloz_kosc(ruch_AI);
		graczAI.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		cout << "brak mozliwych ruchow. gracz pomija ture." << endl;
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Gra zakonczona remisem.\n";
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (graczAI.gracz_glowa == nullptr) {
		cout << endl << "komputer wygral";
		return true;
	}
	return false;
}