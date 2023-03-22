#include"Matrica.h"

Matrica::Matrica()
{
	// ucitavanje dimenzija matrice sa standardnog ulaza
	std::cout << "Unesite broj vrsta i broj kolona:\n";
	std::cin >> broj_vrsta >> broj_kolona;

	// alokacija memorije
	matrica = new float*[broj_vrsta];
	for (int i = 0; i < broj_vrsta; i++) {
		matrica[i] = new float[broj_kolona];
	}

	// inicijalizacija matrice
	std::cout << "\nUnesite elemente matrice:\n";
	for (int i = 0; i < broj_vrsta; i++) {
		for (int j = 0; j < broj_kolona; j++) {
			std::cin >> matrica[i][j];
		}
	}



}

Matrica::Matrica(const int& i, const int& j)
{
	broj_vrsta = i;
	broj_kolona = j;
	matrica = new float* [broj_vrsta];
	for (int i = 0; i < broj_vrsta; i++) {
		matrica[i] = new float[broj_kolona];
	}
}

Matrica::~Matrica()
{
	for (int i = 0; i < broj_vrsta; i++) {
		delete [] matrica[i];
	}
}

void Matrica::ucitaj_iz_ulaznog_toka(std::istream& ulazni_tok)
{
	if (this->broj_vrsta <= 0 || this->broj_kolona <= 0) return;

	for (int i = 0; i < broj_vrsta; i++) {
		for (int j = 0; j < broj_kolona; j++) {
			ulazni_tok >> matrica[i][j];
		}
	}
}

// radi
int Matrica::minimalni_element_vrste() const
{
	float min = matrica[broj_vrsta - 1][0];
	int indeks = 0;
	for (int i = 0; i < broj_kolona-1; i++) {
		if (matrica[broj_vrsta - 1][i] < min) {
			min = matrica[broj_vrsta-1][i];
			indeks = i;
		}
	}
	return indeks;
}

// radi skaliranje vrste matrice
float* Matrica::skaliraj_vrstu(int indeks_vrste, float vrednost)
{
	float* skalirana_vrsta = new float[broj_kolona];
	if (vrednost != 0) {
		for (int i = 0; i < broj_kolona; i++) {
			skalirana_vrsta[i] = matrica[indeks_vrste][i] * vrednost;
		}
	}
	else
		std::cout << "Skaliranje nulom!!!!!" << std::endl;

	return skalirana_vrsta;
}

void Matrica::podeli_vrstu(int indeks_vrste, float vrednost)
{
	for (int j = 0; j < broj_kolona; j++) {
		matrica[indeks_vrste][j] /= vrednost;
	}
}

// trebalo bi da radi istestirano je na dva primera
int Matrica::podeli_kolonu(int indeks_kolone)
{
	float* pomocni_niz = new float[broj_vrsta*4]; 
	for (int i = 0; i < broj_kolona; i++)
		pomocni_niz[i] = 0;

	// stavlja sve nenegativne kolicnike u pomocni niz
	for (int i = 0; i < broj_vrsta; i++) {
		if (matrica[i][indeks_kolone] != 0) {
			float pomocna_promenljiva = matrica[i][broj_kolona - 1] / matrica[i][indeks_kolone];
			if (pomocna_promenljiva > 0)
				pomocni_niz[i] = pomocna_promenljiva;
		}
	}

	int indeks = 0;
	double min = 0;

	// pronalazi minimum niza i njegov indeks, ide do n-1 jer je poslednji element matrice z
	for (int i = 0; i < broj_vrsta-1; i++) {
		if (pomocni_niz[i] != 0) {
			min = pomocni_niz[i];
			indeks = i;
			break;
		}
	}

	for (int i = 0; i < broj_vrsta-1; i++) {
		if (min > pomocni_niz[i] && pomocni_niz[i] != 0) {
			min = pomocni_niz[i];
			indeks = i;
		}
	}
	delete [] pomocni_niz;
	return indeks;
}

void Matrica::podeli_kolonu(int indeks_kolone, bool x)
{
	if (x) {
		for (int i = 0; i < broj_vrsta; i++) {
			if (matrica[i][indeks_kolone] != 0) {
				matrica[i][broj_kolona - 1] /= matrica[i][indeks_kolone];
			}
		}
	}
}

void Matrica::saberi_vrste(int indeks_vrste_1, float* skalirana_vrsta)
{
	for (int j = 0; j < broj_kolona; j++) {
		matrica[indeks_vrste_1][j] += skalirana_vrsta[j];
	}
	delete[] skalirana_vrsta;
}

// radi Gausov algoritam
void Matrica::Gausov_algoritam(int indeks_vrste, int indeks_kolone)
{
	for (int i = 0; i < broj_vrsta; i++) {
		if (i != indeks_vrste) {
			float s = matrica[i][indeks_kolone] / matrica[indeks_vrste][indeks_kolone];
			s = -s;
			if (s != 0) {
				float* skalirana_vrsta = skaliraj_vrstu(indeks_vrste, s);
				saberi_vrste(i, skalirana_vrsta);
			}
		}
	}
}




void Matrica::ispisi_matricu() const
{
	for (int i = 0; i < broj_vrsta; i++) {
		for (int j = 0; j < broj_kolona; j++) {
			std::cout << std::fixed << std::setprecision(2) << matrica[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}
