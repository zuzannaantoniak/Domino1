#include "DominoClass.h"

int wybierz_tryb_gry() {
	std::cout << "wybierz tryb gry:" << std::endl;
	std::cout << "Wpisz 1, aby zagrac z komputerem, lub 2 zeby zagrac z drugim graczem." << std::endl;
	std::string tryb;
	int b;
	while (true) {
		std::cin >> tryb;
		bool valid = true;
		for (size_t i = 0; i < tryb.length(); ++i) {
			if (!std::isdigit(tryb[i])) {
				valid = false;
				break;
			}
		}
		if (valid) {
			b = stoi(tryb);
			if (b == 1 || b == 2) {
				break;
			}
		}
		std::cout << "Nie znam takiego trybu. Wybierz 1 lub 2." << std::endl;
	}
	return b;
}
bool tura_Human_AI(Stol& stol, HumanPlayer& human, Player& graczH, AIPlayer& komputer, Player& graczAI) {
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << " ruch gracza: " << graczH.getnickname() << std::endl;
	std::cout << "kosci: " << std::endl << std::endl;
	graczH.wypisz();
	if (human.znajdz_ruch()) {
		kosc* ruch_human = human.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		graczH.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture." << std::endl;
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		int sumaH = licz_oczka(graczH.gracz_glowa);
		int sumaAI = licz_oczka(graczAI.gracz_glowa);
		if (sumaH > sumaAI) {
			int pom = sumaH - sumaAI;
			int points = zaokraglij_do_5(pom);
			graczAI.dodaj_punkty(points);
			std::cout << "Wygral komputer.\n\n";
		}
		else {
			int pom = sumaAI - sumaH;
			int points = zaokraglij_do_5(pom);
			graczH.dodaj_punkty(points);
			std::cout << "Wygral gracz " << graczH.getnickname() <<"!\n\n";
		}
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (graczH.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Gracz " << graczH.getnickname() << " wylozyl wszystkie kosci!\n\n";
		graczH.licz_punkty_win(graczAI);
		return true;
	}
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "ruch komputera: " << std::endl;
	if (komputer.znajdz_ruch()) {
		kosc* ruch_AI = komputer.wykonaj_ruch();
		stol.doloz_kosc(ruch_AI);
		graczAI.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture." << std::endl;
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		int sumaH = licz_oczka(graczH.gracz_glowa);
		int sumaAI = licz_oczka(graczAI.gracz_glowa);
		if (sumaH > sumaAI) {
			int pom = sumaH - sumaAI;
			int points = zaokraglij_do_5(pom);
			graczAI.dodaj_punkty(points);
			std::cout << "Wygral komputer.\n\n";
		}
		else {
			int pom = sumaAI = sumaH;
			int points = zaokraglij_do_5(pom);
			graczH.dodaj_punkty(points);
			std::cout << "Wygral gracz " << graczH.getnickname() <<"!\n\n";
		}
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (graczAI.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Komputer wylozyl wszystkie kosci.\n\n";
		graczAI.licz_punkty_win(graczH);
		return true;
	}
	return false;
}
bool tura_Human_Human(Stol& stol, HumanPlayer& human1, Player& gracz1, HumanPlayer& human2, Player& gracz2) {
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << " ruch gracza: " << gracz1.getnickname() << std::endl;
	std::cout << "kosci: " << std::endl << std::endl;
	gracz1.wypisz();
	if (human1.znajdz_ruch()) {
		kosc* ruch_human = human1.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		gracz1.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture." << std::endl;
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		int sumaH = licz_oczka(gracz1.gracz_glowa);
		int sumaAI = licz_oczka(gracz2.gracz_glowa);
		if (sumaH > sumaAI) {
			int pom = sumaH - sumaAI;
			int points = zaokraglij_do_5(pom);
			gracz2.dodaj_punkty(points);
			std::cout << "Wygral gracz " << gracz2.getnickname() <<"!\n\n";
		}
		else {
			int pom = sumaAI - sumaH;
			int points = zaokraglij_do_5(pom);
			gracz1.dodaj_punkty(points);
			std::cout << "Wygral gracz " << gracz1.getnickname() <<"!\n\n";
		}
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (gracz1.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Gracz " << gracz1.getnickname() << " wylozyl wszystkie kosci!\n\n";
		gracz1.licz_punkty_win(gracz2);
		return true;
	}
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << " ruch gracza: " << gracz2.getnickname() << std::endl;
	std::cout << "kosci: " << std::endl << std::endl;
	gracz2.wypisz();
	if (human2.znajdz_ruch()) {
		kosc* ruch_human = human2.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		gracz2.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture.\n";
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		int sumaH = licz_oczka(gracz1.gracz_glowa);
		int sumaAI = licz_oczka(gracz2.gracz_glowa);
		if (sumaH > sumaAI) {
			int pom = sumaH - sumaAI;
			int points = zaokraglij_do_5(pom);
			gracz2.dodaj_punkty(points);
			std::cout << "Wygral gracz " << gracz2.getnickname() <<"!\n\n";
		}
		else {
			int pom = sumaAI - sumaH;
			int points = zaokraglij_do_5(pom);
			gracz1.dodaj_punkty(points);
			std::cout << "Wygral gracz " << gracz1.getnickname() <<"!\n\n";
		}
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (gracz2.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Gracz " << gracz2.getnickname() << " wylozyl wszystkie kosci!\n\n";
		gracz2.licz_punkty_win(gracz1);
		return true;
	}
	return false;
}
int licz_oczka(kosc* glowa) {
	kosc* temp = glowa;
	int suma = 0;
	while (temp != nullptr) {
		suma += temp->oczko1 + temp->oczko2;
		temp = temp->next;
	}
	return suma;
}
int zaokraglij_do_5(int liczba) {
	int pom;
	pom = ((liczba + 2) / 5) * 5;
	return pom;
}