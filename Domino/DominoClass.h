#ifndef DOMINOCLASS_H
#define DOMINOCLASS_H

#include <iostream>
#include <string>
#include <random>
#include <ctype.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <time.h>
//licznik passow w turze, potrzebny do sprawdzenia konca rundy
extern int licznik_passow;
//struktura do przechowywania kosci w formie listy dwukierunkowej
struct kosc {
	int oczko1;
	int oczko2;
	kosc* next;
	kosc* prev;
};
//struktura pomocnicza do przechowywania mozliwych ruchow gracza
struct mozliwy_ruch {
	kosc* wskaznik_na_kosc;
	mozliwy_ruch* next;
};

//stol - stan gry, kosci "na stole", kosci do dobrania, dokladanie kosci
class Stol {
public:
	Stol();// konstruktor, tworzy 28 kosci i dodaje do listy dostepnych kosci
	~Stol();//destruktor, usuwa kosci z dostepnych i na stole
	kosc* dostepne_kosci_glowa;
	kosc* dostepne_kosci_ogon;
	kosc* kosci_na_stole_glowa = nullptr;
	kosc* kosci_na_stole_ogon = nullptr;
	kosc* losuj_i_usun();//wylosuje jedna kosc z dostepnych i ususnie ja z listy
	void doloz_kosc(kosc* nowa);//doklada kosc do stolu
	void wypisz_kosci_na_stole();//wypisuje kosci na stole
};


//player - trzyma kosci gracza, nick i punkty, wypisywanie kosci gracza, dobieranie kosci
class Player {
protected:
	std::string nickname;
	int points;
public:
	void setnickname(const std::string& nick) { nickname = nick; };//seter nickname
	std::string getnickname() { return nickname; }//geter nickname
	int getpoints() { return points; }//geter points
	void licz_punkty_tura();// sprawdza po kazdej turze czy gracz ma dostac punkty i je dodaje
	void licz_punkty_win(const Player& loser);//dodaje punkty po wygranej
	void dodaj_punkty(int p) { points += p; }//dodaje punkty
	Player(Stol& stol, std::string nick);//konstruktor, dobiera 7 startowych kosci
	~Player();//destruktor, usuwa kosci z listy gracza
private:
	Stol& stol_ref;
public:
	struct kosc* gracz_glowa;
	struct kosc* gracz_ogon;
	void wypisz()const;//wypisuje kosci gracza
private:
};


// ruchy gracza: szukanie mozliwych ruchow, wykonywanie ruchu, wykladanie kosci
class PlayerMoveSet {
protected:
	Player& gracz_ref;
	Stol& stol_ref;

	mozliwy_ruch* lista_mozliwych = nullptr;
	void usun_liste_mozliwych();//czysci liste mozliwych ruchow
public:
	PlayerMoveSet(Player& gracz, Stol& stol)
		: gracz_ref(gracz), stol_ref(stol) {}

	virtual kosc* pierwszy_ruch() = 0;//wykonuje pierwszy ruch, kiedy gracz moze wylozyc dowolna kosc
	bool znajdz_ruch();//zwroci liste mozliwych ruchow do wykonania
	virtual kosc* wykonaj_ruch() = 0; // gracz wybiera ruch z mozliwych
	// zwraca wzkaznik na kosc do wylozenia i usuwa go z listy gracza
	bool dobierz_kosc();// dobiera kosc z dostepnych kosci na stole
	virtual ~PlayerMoveSet();//destruktor, czysci liste mozliwych ruchow
	virtual void wypisz_mozliwe_ruchy() = 0;//wypisuje liste mozliwych ruchow gracza
};


class HumanPlayer :public PlayerMoveSet {
public:
	HumanPlayer(Player& gracz, Stol& stol)
		: PlayerMoveSet(gracz, stol) {}
	kosc* pierwszy_ruch() override;//gracz wybiera dowolna kosc
	kosc* wykonaj_ruch() override;//gracz wybiera kosc z mozliwych ruchow
	void wypisz_mozliwe_ruchy() override;//wypisuje liste mozliwych ruchow gracza
};


class AIPlayer : public PlayerMoveSet {
public:
	AIPlayer(Player& gracz, Stol& stol)
		: PlayerMoveSet(gracz, stol) {}
	kosc* pierwszy_ruch() override;//komputer wyklada pierwsza kosc na liscie
	kosc* wykonaj_ruch() override;//komputer wybiera pierwsza kosc z mozliwych ruchow
	void wypisz_mozliwe_ruchy() override;// nic nie wypisuje
};

// funkcja obslugujaca jedna ture: ruch gracza 1,liczenie punktow, ruch gracza 2, liczenie punktow, sprawdza wszystkie warunki konczace runde
bool tura_Human_Human(Stol& stol, HumanPlayer& human1, Player& gracz1,HumanPlayer& human2, Player& gracz2);
// funkcja obslugujaca jedna ture: ruch gracza, liczenie punktow, ruch kompitera, liczenie punktow, sprawdza wszystkie warunki konczace runde
bool tura_Human_AI(Stol& stol, HumanPlayer& human, Player& graczH, AIPlayer& komputer, Player& graczAI);
//liczy oczka na kosciach gracza
int licz_oczka(kosc* glowa);
//pomocnicza, zaokragla do najblizszej wielokrotnosci piatki
int zaokraglij_do_5(int liczba);
//pomocnicza, do wyboru trybu gry
int wybierz_tryb_gry();
//wczytuje wynik meczu do pliku, kazdy nick ma swoj oddzielny plik
void wczytaj_do_pliku(std::string nick1, std::string nick2, int punkty1, int punkty2, int max);
#endif;
