#include <iostream>
#include <string>
#include "DominoClass.h"
using namespace std;

int main() {
	Stol game;
	Player gracz1(game);
	Player gracz2(game);
	AIPlayer human1(gracz1, game);
	HumanPlayer human2(gracz2,game);
	cout << "--------------------------------------------------------" << endl;
	cout << "kosci gracza 1: " << endl;
	gracz1.wypisz();
	kosc* ruch0 = human1.pierwszy_ruch();
	game.doloz_kosc(ruch0);
	game.wypisz_kosci_na_stole();
	for (int i = 0; i < 8; ++i) {
		cout << "--------------------------------------------------------" << endl;
		cout << "kosci gracza 2: " << endl;
		gracz2.wypisz();
		mozliwy_ruch* mozliwe_ruchy = human2.znajdz_ruch();
		kosc* ruch1 = human2.wykonaj_ruch();
		game.doloz_kosc(ruch1);
		game.wypisz_kosci_na_stole();
		if (gracz2.gracz_glowa == nullptr) {
			cout << endl << "gracz 2 wygral";
			return 0;
		}
		cout << "--------------------------------------------------------" << endl;
		cout << "kosci gracza 1: " << endl;
		gracz1.wypisz();
		mozliwy_ruch* mozliwe_ruchy1 = human1.znajdz_ruch();
		kosc* ruch2 = human1.wykonaj_ruch();
		game.doloz_kosc(ruch2);
		game.wypisz_kosci_na_stole();
		if (gracz1.gracz_glowa == nullptr) {
			cout << endl << "gracz 1 wygral";
			return 0;
		}
	}

	return 0;
}