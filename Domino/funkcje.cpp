#include "DominoClass.h"
using namespace std;
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
		cout << "Koniec gry. Brak mozliwych ruchow.\n";
		int sumaH = licz_oczka(graczH.gracz_glowa);
		int sumaAI = licz_oczka(graczAI.gracz_glowa);
		if (sumaH > sumaAI) {
			int pom = sumaH - sumaAI;
			int points = zaokraglij_do_5(pom);
			graczAI.dodaj_punkty(points);
			cout << "Wygral komputer." << endl;
		}
		else {
			int pom = sumaAI - sumaH;
			int points = zaokraglij_do_5(pom);
			graczH.dodaj_punkty(points);
			cout << "Wygral gracz " << graczH.getnickname() << endl;
		}
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (graczH.gracz_glowa == nullptr) {
		cout << endl << "Koniec gry. Gracz " << graczH.getnickname() << " wygral"<<endl;
		graczH.licz_punkty_win(graczAI);
		return true;
	}
	cout << "--------------------------------------------------------" << endl;
	cout << "ruch komputera: " << endl;
	if (komputer.znajdz_ruch()) {
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
		cout << "Koniec gry. Brak mozliwych ruchow.\n";
		int sumaH = licz_oczka(graczH.gracz_glowa);
		int sumaAI = licz_oczka(graczAI.gracz_glowa);
		if (sumaH > sumaAI) {
			int pom = sumaH - sumaAI;
			int points = zaokraglij_do_5(pom);
			graczAI.dodaj_punkty(points);
			cout << "Wygral komputer." << endl;
		}
		else {
			int pom = sumaAI = sumaH;
			int points = zaokraglij_do_5(pom);
			graczH.dodaj_punkty(points);
			cout << "Wygral gracz " << graczH.getnickname() << endl;
		}
		return true;
	}
	stol.wypisz_kosci_na_stole();
	if (graczAI.gracz_glowa == nullptr) {
		cout << endl << "Koniec gry. Komputer wygral"<<endl;
		graczAI.licz_punkty_win(graczH);
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