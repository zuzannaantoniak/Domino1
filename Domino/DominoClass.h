#ifndef DOMINOCLASS_H
#define DOMINOCLASS_H

#include <iostream>
#include <string>
#include <random>
#include <ctype.h>
using namespace std;
extern int licznik_passow;
struct kosc {
	int oczko1;
	int oczko2;
	kosc* next;
	kosc* prev;
};
struct mozliwy_ruch {
	kosc* wskaznik_na_kosc;
	mozliwy_ruch* next;
};

//stol - stan gry, kosci "na stole", kosci do dobrania, dokladanie kosci
class Stol {
public:
	Stol();
	~Stol();
	kosc* dostepne_kosci_glowa;
	kosc* dostepne_kosci_ogon;
	kosc* kosci_na_stole_glowa = nullptr;
	kosc* kosci_na_stole_ogon = nullptr;
	kosc* losuj_i_usun();
	void doloz_kosc(kosc* nowa);
	void wypisz_kosci_na_stole();
};


// kosci gracza, wypisywanie kosci gracza, dobieranie kosci, punkty(maybe moze dodam inna klase)
class Player {
protected:
	string nickname;
	int points;
public:
	void setnickname(const string& nick) { nickname = nick; };
	string getnickname() { return nickname; }
	int getpoints() { return points; }
	void licz_punkty_tura();
	void licz_punkty_win(const Player& loser);
	void dodaj_punkty(int p) { points += p; }
	Player(Stol& stol);
	~Player();
private:
	Stol& stol_ref;
public:
	struct kosc* gracz_glowa;
	struct kosc* gracz_ogon;
	void wypisz()const;
private:
};


// ruchy gracza: szukanie mozliwych ruchow, wykonywanie ruchu, wykladanie kosci
class PlayerMoveSet {
protected:
	Player& gracz_ref;
	Stol& stol_ref;

	mozliwy_ruch* lista_mozliwych = nullptr;
	void usun_liste_mozliwych();
public:
	PlayerMoveSet(Player& gracz, Stol& stol)
		: gracz_ref(gracz), stol_ref(stol) {}

	virtual kosc* pierwszy_ruch() = 0;
	bool znajdz_ruch();//zwroci liste mozliwych ruchow do wykonania
	virtual kosc* wykonaj_ruch() = 0; // gracz wybiera ruch z mozliwych
	// zwraca wzkaznik na kosc do wylozenia i usuwa go z listy gracza
	bool czy_dobierz();
	bool dobierz_kosc();
	virtual ~PlayerMoveSet();
	virtual void wypisz_mozliwe_ruchy() = 0;
};


class HumanPlayer :public PlayerMoveSet {
public:
	HumanPlayer(Player& gracz, Stol& stol)
		: PlayerMoveSet(gracz, stol) {}
	kosc* pierwszy_ruch() override;
	kosc* wykonaj_ruch() override;
	void wypisz_mozliwe_ruchy() override;
};


class AIPlayer : public PlayerMoveSet {
public:
	AIPlayer(Player& gracz, Stol& stol)
		: PlayerMoveSet(gracz, stol) {}
	kosc* pierwszy_ruch() override;
	kosc* wykonaj_ruch() override;
	void wypisz_mozliwe_ruchy() override;
};

// funkcja obslugujaca jedna runde: ruch gracza 1,liczenie punktow, ruch gracza 2, liczenie punktow
void tura_Human_Human(Stol& stol, HumanPlayer& gracz1, AIPlayer& gracz2);

bool tura_Human_AI(Stol& stol, HumanPlayer& human, Player& graczH, AIPlayer& komputer, Player& graczAI);
int licz_oczka(kosc* glowa);
int zaokraglij_do_5(int liczba);

#endif;
