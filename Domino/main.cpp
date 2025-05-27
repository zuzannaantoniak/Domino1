#include <iostream>
#include <string>
#include "DominoClass.h"
using namespace std;
int licznik_passow = 0;
int main() {
	Stol game;
	Player gracz1(game);
	Player gracz2(game);
	AIPlayer komputer(gracz1, game);
	HumanPlayer human2(gracz2,game);
	
	cout << "--------------------------------------------------------" << endl;
	cout << "ruch komputera: " << endl<<endl;
	kosc* ruch0 = komputer.pierwszy_ruch();
	game.doloz_kosc(ruch0);
	game.wypisz_kosci_na_stole();
	while (true) {
		if (tura_Human_AI(game, human2, gracz2, komputer, gracz1)) {
			break;
		}
	}
	cout << "punkty gracza 1: " << gracz1.getpoints() << endl;
	cout << "punkty gracza 2: " << gracz2.getpoints() << endl;
	return 0;
}