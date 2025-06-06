#include "DominoClass.h"

Player::Player(Stol&stol,std::string nick):stol_ref(stol), nickname(nick), points(0) {
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
}
void Player::wypisz()const {
	kosc* temp = gracz_glowa;
	int i = 1;
	while (temp != nullptr) {
		std::cout <<i<<". ["<< temp->oczko1 << "|" << temp->oczko2 << "]     ";
		temp = temp->next;
		++i;
	}
	std::cout << std::endl;
}
void Player::licz_punkty_tura() {
	Stol& stol = stol_ref;
	if (stol.dostepne_kosci_glowa != nullptr && stol.dostepne_kosci_ogon != nullptr) {
		int pom = stol.kosci_na_stole_glowa->oczko1 + stol.kosci_na_stole_ogon->oczko2;
		if (pom % 5 == 0) {
			points += pom;
		}
	}
}
void Player::licz_punkty_win(const Player& loser) {
	int suma = licz_oczka(loser.gracz_glowa);
	int punkty = zaokraglij_do_5(suma);
	points += punkty;
}
Player::~Player() {
	//std::cout << "Destruktor Player\n";
	while (gracz_glowa != nullptr) {
		kosc* temp = gracz_glowa->next;
		delete gracz_glowa;
		gracz_glowa = temp;
	}
	gracz_glowa = nullptr;
	gracz_ogon = nullptr;
}