#include "Simplex.h"

void Simplex::napravi_pocetnu_tabelu(const Matrica& matrica_sistema, const Matrica& jedn) {
	// prvih n indeksa kolona su koeficijenti koji odgovaraju promenljivima xi
	// pocevsi od (n+1)-og indeksa kolona su koeficijenti koji odgovaraju slack promenljivima si 


	// x1  x2  ... xn   s1 s2... sm  b
	// a11 a12 ... a1n	1  0 ... 0	 b1		s1
	// a21 a22 ... a2n  0  1 ... 0	 b2		s2
	// ...
	// am1 am2 ... amn	0  0 ... 1	 bm		sm
	// -c1 -c2 ... -cn	0  0 ... 0	 0	<--	z
	// {      n      }  {   m   }   {1} // 

	// broj vrsta tabele je: m + 1
	int br_vrsta = matrica_sistema.dohv_broj_vrsta() + 1;

	// broj kolona tabele je: n + m + 1, matrica sistema ima n + 1 kolonu jer je unutra i kolona slobodnih clanova
	int br_kolona = matrica_sistema.dohv_broj_kolona() + matrica_sistema.dohv_broj_vrsta();
	// inicijalizacija broja promenljivih i broja slack promenljivih
	broj_promenljivih = matrica_sistema.dohv_broj_kolona() - 1;
	broj_slack_promenljivih = matrica_sistema.dohv_broj_vrsta();

	// inicijalizacija niza indeksa koji se trenutno nalaze u bazi
	// u bazi se u pocetnom trenutku nalaze slack promenljive, velicina niza je m
	indeksi_bazicnih_promenljivih = new int[broj_slack_promenljivih];
	for (int i = 0; i < broj_slack_promenljivih; i++) {
		indeksi_bazicnih_promenljivih[i] = broj_promenljivih + i;
	}


	// alokacija memorije tabele
	tabela = new Matrica(br_vrsta, br_kolona);

	// popunjava tabelu koeficijentima aij
	for (int i = 0; i < matrica_sistema.dohv_broj_vrsta(); i++) {
		for (int j = 0; j < matrica_sistema.dohv_broj_kolona() - 1; j++) {
			tabela->dohvati_element_matrice(i, j) = matrica_sistema.dohvati_element_matrice(i, j);
		}
	}

	// popunjava tabelu koeficijentima slack promenjivih
	for (int i = 0; i < br_vrsta - 1; i++) {
		for (int j = matrica_sistema.dohv_broj_kolona() - 1; j < br_kolona - 1; j++) {
			if (i == (j - (matrica_sistema.dohv_broj_kolona() - 1)))
				tabela->dohvati_element_matrice(i, j) = 1;
			else
				tabela->dohvati_element_matrice(i, j) = 0;
		}
	}

	// popunjava tabelu slobodnim clanovima bi
	for (int i = 0; i < matrica_sistema.dohv_broj_vrsta(); i++) {
		tabela->dohvati_element_matrice(i, br_kolona - 1) = matrica_sistema.dohvati_element_matrice(i, matrica_sistema.dohv_broj_kolona() - 1);
	}

	// popunjava poslednju vrstu tabele
	for (int j = 0; j < br_kolona; j++) {
		if (j < jedn.dohv_broj_kolona()) {
			tabela->dohvati_element_matrice(br_vrsta - 1, j) = -jedn.dohvati_element_matrice(0, j);
		}
		else {
			tabela->dohvati_element_matrice(br_vrsta - 1, j) = 0;
		}
	}
	// ispis tabele
	for (int i = 0; i < br_vrsta; i++) {
		for (int j = 0; j < br_kolona; j++)
			std::cout << tabela->dohvati_element_matrice(i, j) << '\t';
		std::cout << std::endl;
	}
}


void Simplex::pivotiranje()
{
	// indeksi ulaznih i izlaznih elemenata su smesteni u nizovima
	// prvi element je vrsta, drugi element je kolona

	int indeks_ulaznog_elementa[2], indeks_izlaznog_elementa[2];

	indeks_ulaznog_elementa[0] = tabela->dohv_broj_vrsta() - 1;
	indeks_ulaznog_elementa[1] = tabela->minimalni_element_vrste();

	indeks_izlaznog_elementa[0] = tabela->podeli_kolonu(indeks_ulaznog_elementa[1]); // Pronalazi indeks vrste izlaznog elementa
	indeks_izlaznog_elementa[1] = indeksi_bazicnih_promenljivih[indeks_izlaznog_elementa[0]]; // indeks vrste ulaznog elementa.

	//
	tabela->podeli_vrstu(indeks_izlaznog_elementa[0], tabela->dohvati_element_matrice(indeks_izlaznog_elementa[0], indeks_ulaznog_elementa[1]));
	//
	tabela->Gausov_algoritam(indeks_izlaznog_elementa[0], indeks_ulaznog_elementa[1]);
	tabela->ispisi_matricu();
	std::cout << std::endl;

	// broj bazicnih promenljivih jednak je broju slack promenljivih
	for (int i = 0; i < broj_slack_promenljivih; i++) {
		if (indeksi_bazicnih_promenljivih[i] == indeks_izlaznog_elementa[1]) {
			indeksi_bazicnih_promenljivih[i] = indeks_ulaznog_elementa[1];
			break;
		}
	}

	/*for (int i = 0; i < broj_slack_promenljivih; i++) {
		std::cout << indeksi_bazicnih_promenljivih[i] << ' ';
	}
	std::cout << std::endl;*/
}

void Simplex::simplex_algoritam()
{
	while (tabela->dohvati_element_matrice(tabela->dohv_broj_vrsta() - 1, tabela->minimalni_element_vrste()) != 0) {
		pivotiranje();
	}

	for (int i = 0; i < broj_slack_promenljivih; i++) {
		tabela->podeli_kolonu(indeksi_bazicnih_promenljivih[i],true); //Sta ovo radi
	}

	// ispis resenja
	for (int i = 0; i < broj_promenljivih + broj_slack_promenljivih; i++) {
		if (i < broj_promenljivih) {
			std::cout << 'x' << i + 1 << " = ";
			bool pomocna = pronadji_bazicnu_promenljivu(i);
			if (pronadji_bazicnu_promenljivu(i)) {
				std::cout << vrednost_bazicne_promenljive(i) << std::endl;
			}
			else {
				std::cout << 0 << std::endl;
			}
		}
	}

	std::cout << "\nz_max = " << tabela->dohvati_element_matrice(tabela->dohv_broj_vrsta() - 1, tabela->dohv_broj_kolona() - 1);
	std::cout << "\n\n";

}

bool Simplex::pronadji_bazicnu_promenljivu(int indeks)
{
	for (int i = 0; i < broj_slack_promenljivih; i++) {
		if (indeks == indeksi_bazicnih_promenljivih[i]) {
			return true;
		}
	}
	return false;
}

double Simplex::vrednost_bazicne_promenljive(int indeks)
{
	for (int i = 0; i < broj_slack_promenljivih; i++) {
		if (indeks == indeksi_bazicnih_promenljivih[i]) {
			return tabela->dohvati_element_matrice(i, tabela->dohv_broj_kolona() - 1);
		}
	}
	return 0.0;
}
