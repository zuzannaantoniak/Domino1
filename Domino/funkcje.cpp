#define _CRT_SECURE_NO_WARNINGS
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
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	std::cout << " ruch gracza: " << graczH.getnickname() << std::endl<<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "kosci: " << std::endl << std::endl;
	graczH.wypisz();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (human.znajdz_ruch()) {
		kosc* ruch_human = human.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		graczH.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (graczH.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Gracz " << graczH.getnickname() << " wylozyl wszystkie kosci!\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		graczH.licz_punkty_win(graczAI);
		return true;
	}
	std::cout << "----------------------------------------------------------------------------" << std::endl;
	std::cout << "ruch komputera: " << std::endl << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (komputer.znajdz_ruch()) {
		kosc* ruch_AI = komputer.wykonaj_ruch();
		stol.doloz_kosc(ruch_AI);
		graczAI.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (graczAI.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Komputer wylozyl wszystkie kosci.\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		graczAI.licz_punkty_win(graczH);
		return true;
	}
	return false;
}
bool tura_Human_Human(Stol& stol, HumanPlayer& human1, Player& gracz1, HumanPlayer& human2, Player& gracz2) {
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << " ruch gracza: " << gracz1.getnickname() << std::endl << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "kosci: " << std::endl << std::endl;
	gracz1.wypisz();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (human1.znajdz_ruch()) {
		kosc* ruch_human = human1.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		gracz1.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture." << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (gracz1.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Gracz " << gracz1.getnickname() << " wylozyl wszystkie kosci!\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		gracz1.licz_punkty_win(gracz2);
		return true;
	}
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << " ruch gracza: " << gracz2.getnickname() << std::endl << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "kosci: " << std::endl << std::endl;
	gracz2.wypisz();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (human2.znajdz_ruch()) {
		kosc* ruch_human = human2.wykonaj_ruch();
		stol.doloz_kosc(ruch_human);
		gracz2.licz_punkty_tura();
		licznik_passow = 0;
	}
	else {
		std::cout << "brak mozliwych ruchow. gracz pomija ture.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
		licznik_passow++;
	}
	if (licznik_passow >= 2) {
		std::cout << "Koniec gry. Brak mozliwych ruchow.\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
	std::this_thread::sleep_for(std::chrono::seconds(1));
	if (gracz2.gracz_glowa == nullptr) {
		std::cout << std::endl << "Koniec gry. Gracz " << gracz2.getnickname() << " wylozyl wszystkie kosci!\n\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
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
void wczytaj_do_pliku(std::string nick1,std::string nick2, int punkty1,int punkty2,int max) {
	time_t log_time;
	time(&log_time);
	struct tm* time = localtime(& log_time);
	std::string log_gracz = "historia_gier_" + nick1;
	std::ofstream log(log_gracz, std::ios::app);
	if (!log) {
		std::cerr << "Blad przy otwarciu pliku! Dane z tej rozgrywki nie zostana zapisane :(\n";
		return;
	}
	if (punkty1 >= max && punkty1 > punkty2) {
		log << "Gracz " << nick1 << " wygral z graczem " << nick2 << " wynikiem " << punkty1 << " do " << punkty2 << ".\n";
	}
	else {
		log<< "Gracz "<<nick1<<" przegral z graczem "<<nick2<< " wynikiem " <<punkty1 << " do " <<punkty2 <<".\n";
	}
	log << "Rozgrywka zakonczona o: " << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << " " << time->tm_mday<< "/" << time->tm_mon + 1 << "/" << time->tm_year + 1900 << "\n\n\n";
	log.close();
}
int odczytaj_pliki_wybor() {
	std::cout << "Wpisz 1, jesli chcesz zobaczyc historie gier graczy, lub 2 jesli chcesz zakonczyc program:" << std::endl;
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
		std::cout << "Nie znam polecenia. Wybierz 1 lub 2." << std::endl;
	}
	return b;
}
void odczytaj_plik(std::string nick) {
	std::string gracz = "historia_gier_" + nick;
	std::ifstream file(gracz);
	if (!file) {
		std::cerr << "Blad przy otwarciu pliku!\n";
		return;
	}
	std::cout << "Historia gracza " << nick << ":\n\n";
	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
	}
	file.close();
}