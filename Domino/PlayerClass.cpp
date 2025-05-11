#include "DominoClass.h"
using namespace std;
void Player::setnickname(const string& nick) {
	nickname = nick;
}
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
//destruktor
Player::~Player() {
	while (gracz_glowa != nullptr) {
		kosc* temp = gracz_glowa->next;
		delete gracz_glowa;
		gracz_glowa = temp;
	}
}