#include <iostream>
#include <string>
#include "DominoClass.h"
using namespace std;

int main() {
	Stol game;
	Player gracz1(game);
	Player gracz2(game);
	AIPlayer komputer(gracz1,game);
	HumanPlayer human2(gracz2,game);
	cout << "kosci gracza 1: " << endl;
	gracz1.wypisz();
	kosc* ruch0 = komputer.pierwszy_ruch();
	game.doloz_kosc(ruch0);
	game.wypisz_kosci_na_stole();
	cout << "kosci gracza 2: " << endl;
	gracz2.wypisz();
	kosc* mozliwe_ruchy = human2.znajdz_ruch();
	kosc* ruch1 = human2.wykonaj_ruch();
	game.doloz_kosc(ruch1);
	game.wypisz_kosci_na_stole();
	HumanPlayer human1(gracz1, game);
	cout << "kosci gracza 1: " << endl;
	gracz1.wypisz();
	mozliwe_ruchy = human1.znajdz_ruch();
	ruch1 = human1.wykonaj_ruch();
	game.doloz_kosc(ruch1);
	game.wypisz_kosci_na_stole();
	gracz1.wypisz();
	return 0;
}