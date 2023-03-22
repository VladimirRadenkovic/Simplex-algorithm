#ifndef _MATRICA_H_
#define _MATRICA_H_

#include <iostream>
#include <iomanip>


class Matrica {
	int broj_vrsta=0, broj_kolona=0;
	float** matrica = nullptr;

public:
	// podrazumevani konstruktor pravi matricu sa elementima sa standardnog ulaza
	Matrica();
	// konstruktor koji samo alocira memoriju za matricu
	Matrica(const int& i, const int& j);
	Matrica(const Matrica&) = delete;
	Matrica(Matrica&&) = delete;

	~Matrica();
	// ucitavanje
	void ucitaj_iz_ulaznog_toka(std::istream& ulazni_tok);

	// dohvataci
	int dohv_broj_vrsta() const {
		return broj_vrsta;
	}
	int dohv_broj_kolona() const {
		return broj_kolona;
	}
	float dohvati_element_matrice(int i, int j) const {
		return matrica[i][j];
	}

	// dohvata element po referenci
	float& dohvati_element_matrice(int i, int j) {
		return matrica[i][j];
	}



	// metoda koja vraca indeks minimalnog elementa poslednje vrste matrice
	int minimalni_element_vrste() const;

	// metoda koja skalira zadatu vrstu zadatim brojem i vraca je kao niz
	float* skaliraj_vrstu(int indeks_vrste, float vrednost);
	// metoda deli vrstu zadatim brojem
	void podeli_vrstu(int indeks_vrste, float vrednost);

	/* metoda koja deli skalarno poslednju kolonu kolonom zadatog indeksa i vraca minimalnu indeks vrste minimalne
	nenegativne vrednosti nakon skalarnog deljenja poslednje kolone */
	int podeli_kolonu(int indeks_kolone);
	void podeli_kolonu(int indeks_kolone, bool x);
	// metoda sabira vrstu i niz elementa vrste
	void saberi_vrste(int indeks_vrste_1, float* vrsta);

	// Gausova algoritam - pravi nule iznad i ispod zadatog elementa u matrici
	void Gausov_algoritam(int indeks_vrste, int indeks_kolone);



	void ispisi_matricu() const;



};
#endif // !_MATRICA_H_
