#ifndef DOMINOCLASS_H
#define DOMINOCLASS_H

#include <iostream>
#include <string>
#include <random>
using namespace std;

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
public:
	void setnickname(const string& nick);
	Player(Stol& stol);
	~Player();
private:
	Stol& stol_ref;
public:
	struct kosc* gracz_glowa;
	struct kosc* gracz_ogon;
	void wypisz()const;
private:
	int punkty = 0;
};


// ruchy gracza: szukanie mozliwych ruchow, wykonywanie ruchu, wykladanie kosci
class PlayerMoveSet {
protected:
	Player& gracz_ref;
	Stol& stol_ref;

	mozliwy_ruch* lista_mozliwych = nullptr;
private:
	void usun_liste_mozliwych();
public:
	PlayerMoveSet(Player& gracz, Stol& stol)
		: gracz_ref(gracz), stol_ref(stol) {}

	virtual kosc* pierwszy_ruch() = 0;
	mozliwy_ruch* znajdz_ruch();//zwroci liste mozliwych ruchow do wykonania
	virtual kosc* wykonaj_ruch() = 0; // gracz wybiera ruch z mozliwych
	// zwraca wzkaznik na kosc do wylozenia i usuwa go z listy gracza
	bool czy_dobierz();
	void dobierz_kosc();
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

#endif
