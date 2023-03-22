#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_

#include "Matrica.h"

class Simplex {
	Matrica* tabela = nullptr;
	int broj_promenljivih = 0, broj_slack_promenljivih = 0;
	int* indeksi_bazicnih_promenljivih = nullptr; // niz indeksa koji se trenutno nalaze u bazi 


public:
	void napravi_pocetnu_tabelu(const Matrica& matrica_sistema, const Matrica& jedn);
	void pivotiranje();
	void simplex_algoritam();
	bool pronadji_bazicnu_promenljivu(int indeks);
	double vrednost_bazicne_promenljive(int indeks);





};
#endif // !_SIMPLEX_H_
