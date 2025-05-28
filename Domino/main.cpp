#include <iostream>
#include <string>
#include "DominoClass.h"

int licznik_passow = 0;
int main() {
	std::cout << "Witaj w grze Domino!\n\n";
	int tryb = wybierz_tryb_gry();
	const int MAX_PUNKTY = 55;
	if (tryb == 2) {
		std::cout << "podaj nick pierwszego gracza: ";
		std::string nick1;
		std::cin >> nick1;
		std::cout << "podaj nick drugiego gracza: ";
		std::string nick2;
		std::cin >> nick2;
		int punkty_gracza1 = 0;
		int punkty_gracza2 = 0;
		int nr_tury = 1;
		while (punkty_gracza1 < MAX_PUNKTY && punkty_gracza2 < MAX_PUNKTY) {
			std::cout << "\n\n\n\n\t\tTURA " << nr_tury << "\n\n";
			Stol game;
			Player gracz1(game);
			Player gracz2(game);
			HumanPlayer human1(gracz1, game);
			HumanPlayer human2(gracz2, game);
			gracz1.setnickname(nick1);
			gracz2.setnickname(nick2);
			std::cout << "--------------------------------------------------------" << std::endl;
			std::cout << " ruch gracza: " << gracz2.getnickname() << std::endl;
			kosc* ruch0 = human2.pierwszy_ruch();
			game.doloz_kosc(ruch0);
			game.wypisz_kosci_na_stole();
			while (true) {
				if (tura_Human_Human(game, human1, gracz1, human2, gracz2)) {
					break;
				}
			}
			std::cout << "punkty gracza " << gracz1.getnickname() << ": " << gracz1.getpoints()+punkty_gracza1 << std::endl;
			std::cout << "punkty gracza " << gracz2.getnickname() << ": " << gracz2.getpoints()+punkty_gracza2 << std::endl;
			punkty_gracza1 += gracz1.getpoints();
			punkty_gracza2 += gracz2.getpoints();
			nr_tury++;
		}
		std::cout << "\n\n\nKoniec gry! Wygral: "<< (punkty_gracza1 >= MAX_PUNKTY ? nick1 : nick2) << std::endl;
	}
	else {
		std::cout << "podaj nick gracza: ";
		std::string nick1;
		std::cin >> nick1;
		int punkty_gracza1 = 0;
		int punkty_komputera = 0;
		int nr_tury = 1;
		while (punkty_gracza1 < MAX_PUNKTY && punkty_komputera < MAX_PUNKTY) {
			std::cout << "\n\n\n\n\t\tTURA " << nr_tury << "\n\n";
			Stol game;
			Player gracz1(game);
			Player AI(game);
			HumanPlayer human1(gracz1, game);
			AIPlayer komputer(AI, game);
			gracz1.setnickname(nick1);
			std::cout << "--------------------------------------------------------" << std::endl;
			std::cout << " ruch komputera.\n\n";
			kosc* ruch0 = komputer.pierwszy_ruch();
			game.doloz_kosc(ruch0);
			game.wypisz_kosci_na_stole();
			while (true) {
				if (tura_Human_AI(game, human1, gracz1, komputer, AI)) {
					break;
				}
			}
			std::cout << "punkty gracza " << gracz1.getnickname() << ": " << gracz1.getpoints() + punkty_gracza1 << std::endl;
			std::cout << "punkty komputera "  << ": " << AI.getpoints() + punkty_komputera << std::endl;
			punkty_gracza1 += gracz1.getpoints();
			punkty_komputera += AI.getpoints();
			nr_tury++;
		}
		std::cout << "\n\n\nKoniec gry! Wygral: " << (punkty_gracza1 >= MAX_PUNKTY&&punkty_gracza1>punkty_komputera ? nick1 : "komputer") << std::endl;
	}
	return 0;
}