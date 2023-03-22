#include "Matrica.h"
#include "Simplex.h"

#include <fstream>
#include <string>
#include <sstream>
#include <exception>


void ispisUlaznePoruke();
void ispisGlavnogMenija();
void pokreniUcitavanjeMatrice();
void pokreniUcitavanjeFunkcije();
void pokreniSimpleksAlgoritam();

Matrica* matrica_s = nullptr;
Matrica* funkcija_za_maksimizaciju = nullptr;


int main() {

	ispisUlaznePoruke();

	int izbor = 1;

	while (izbor != 0) {
		std::cout << "Odaberite neku od sledecih opcija\n";
		ispisGlavnogMenija();
		std::cin >> izbor;
		std::cout << '\n';

		switch (izbor) {
		case 1:
			pokreniUcitavanjeMatrice();
			break;
		case 2:
			pokreniUcitavanjeFunkcije();
			break;
		case 3:
			pokreniSimpleksAlgoritam();
			break;
		case 0:
			break;
		default:
			std::cout << "GRESKA: Nepravilan unos, molimo pokusajte ponovo\n\n";
			break;
		}
	}

	std::cout << "Izlazak iz programa. Dovidjenja!\n";

}


void pokreniUcitavanjeIzFajla();
void pokreniUcitavanjeIzKonzole();


void ispisUlaznePoruke() {
	std::cout << "Slozenost algoritama i odabrane metode optimizacije, semestralni rad 2020/2021\n";
	std::cout << "Program za resavanje problema linearnog programiranja uz pomoc simpleks metode\n\n";
}


void ispisGlavnogMenija() {
	std::cout << "1: Ucitaj matricu sistema\n";
	std::cout << "2: Unesi funkciju za maksimizaciju\n";
	std::cout << "3: Pokreni simpleks algoritam\n";
	std::cout << "0: Izlazak iz programa\n\n";
}

void pokreniUcitavanjeMatrice() {

	if (matrica_s != nullptr) {
		std::cout << "UPOZORENJE: U sistemu je vec ucitana jedna matrica. ";
		std::cout << "Ucitavanjem nove matrice brisu se podaci o staroj\n";
		std::cout << "Da li zelite da nastavite?\n";
		std::cout << "1: Ucitaj novu matricu\n";
		std::cout << "0: Povratak na glavni meni\n\n";
		int izbor;
		std::cin >> izbor;
		switch (izbor) {
		case 1:
			delete matrica_s;
			delete funkcija_za_maksimizaciju;
			funkcija_za_maksimizaciju = nullptr;
			break;
		case 0:
			std::cout << "Povratak na glavni meni\n\n";
			return;
		default:
			std::cout << "GRESKA: Pogresan unos, povratak na glavni meni\n\n";
			return;
		}
	}
	
	std::cout << "Matricu mozete uneti rucno u konzoli ili se moze ucitati iz fajla\n";
	std::cout << "Odaberite opciju:\n";
	std::cout << "1: Unos kroz konzolu\n";
	std::cout << "2: Ucitavanje matrice iz fajla\n\n";
	int izbor;
	std::cin >> izbor; std::cout << '\n';
	switch (izbor) {
	case 1:
		pokreniUcitavanjeIzKonzole();
		break;
	case 2:
		pokreniUcitavanjeIzFajla();
		break;
	default:
		std::cout << "GRESKA: Pogresan unos, povratak na glavni meni\n\n";
		return;
	}
	std::cout << "Matrica sistema uspesno ucitana, povratak na glavni meni\n\n";
	matrica_s->ispisi_matricu();
	std::cout << std::endl;
}

void pokreniUcitavanjeIzFajla() {
	std::cout << "Unesite matricu sistema u formatu:\n";
	std::cout << "m n\n";
	std::cout << "a_11 a_12 ... a_1n b_1\n";
	std::cout << "a_21 a_22 ... a_2n b_2\n";
	std::cout << " .    .        .    .\n";
	std::cout << " .    .        .    .\n";
	std::cout << " .    .        .    .\n";
	std::cout << "a_m1 a_m2 ... a_mn b_n\n\n";

	std::cout << "Gde je m broj nejednacina u sistemu,n brojpromenljivih u sistemu,";
	std::cout << " a a_ij i b_i koeficijenti sistema nejednacina:\n";

	std::cout << "a_11*x_1 a_12*x_2 ... a_1n*x_n <= b_1\n";
	std::cout << "a_21*x_1 a_22*x_2 ... a_2n*x_n <= b_1\n";
	std::cout << "   .        .                  .  \n";
	std::cout << "   .        .                  .  \n";
	std::cout << "   .        .                  .  \n";
	std::cout << "a_m1*x_1 a_m2*x_2 ... a_mn*x_n <= b_m\n\n";


	std::cout << "Unesite naziv/putanju do fajla u kome se nalaze podaci u odgovarajucem formatu: ";
	std::string naziv_fajla;
	std::cin >> naziv_fajla;
	std::cout << '\n';

	std::ifstream ulazni_fajl(naziv_fajla);
	if (!ulazni_fajl.is_open()) {
		std::cout << "GRESKA: Neuspesno otvaranje fajla\n\n";
		exit(0);
	}
	int m, n;

	ulazni_fajl >> m >> n;

	if (n < 2 || m < 2) {
		std::cout << "Nepravilan unos\n\n";
		exit(0);
	}

	matrica_s = new Matrica(m, n + 1);

	matrica_s->ucitaj_iz_ulaznog_toka(ulazni_fajl);

	ulazni_fajl.close();

	return;
}

void pokreniUcitavanjeIzKonzole() {
	int m, n;

	std::cout << "Unesite broj promenljivih u sistemu: ";
	std::cin >> n;

	std::cout << "Unesite broj nejednacina u sistemu: ";
	std::cin >> m;

	std::cout << '\n';

	if (n < 2 || m < 2 || n > 9 || m > 9) {
		std::cout << "GRESKA: Nepravilan unos";
		exit(0);
	}
	std::cout << "Unesite matricu sistema u formatu:\n";
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			std::cout << "a_" << i + 1 << j + 1 << ' ';
		std::cout << "b_" << i + 1 << '\n';
	}
	std::cout << '\n';
	std::cout << "Gde su ovo koeficijenti sistema nejednacina:\n";
	for (int i = 0; i < m; i++) {
		std::stringstream linija;
		for (int j = 0; j < n; j++) {
			linija << "a_" << i + 1 << j + 1 << "*x_" << j + 1 << " + ";
		}
		std::string l = linija.str();
		l.pop_back(); l.pop_back();
		std::cout << l << "<= b_" << i + 1 << '\n';
	}
	std::cout << '\n';
	matrica_s = new Matrica(m, n + 1);
	
	std::cout << "Molim vas unesite matricu sistema u trazenom formatu:\n";
	matrica_s->ucitaj_iz_ulaznog_toka(std::cin);
	std::cout << '\n';

}


void pokreniUcitavanjeFunkcije() {
	if (matrica_s == nullptr) {
		std::cout << "GRESKA: Mora najpre biti ucitana matrica sistema, povratak na glavni meni\n\n";
		return;
	}
	if (funkcija_za_maksimizaciju != nullptr) {
		std::cout << "UPOZORENJE: U sistemu je vec ucitana jedna funkcija za maksimizaciju. ";
		std::cout << "Ucitavanjem nove funkcije brisu se podaci o staroj\n";
		std::cout << "Da li zelite da nastavite?\n";
		std::cout << "1: Ucitaj novu funkciju za maksimizaciju\n";
		std::cout << "0: Povratak na glavni meni\n\n";
		int izbor;
		std::cin >> izbor; std::cout << '\n';
		switch (izbor) {
		case 1:
			delete funkcija_za_maksimizaciju;
			break;
		case 0:
			std::cout << "Povratak na glavni meni\n\n";
			return;
		default:
			std::cout << "GRESKA: Pogresan unos, povratak na glavni meni\n\n";
			return;
		}
	}
	std::cout << "Unesite funkciju za maksimizaciju u formatu:\n";
	for (int i = 0; i < matrica_s->dohv_broj_kolona() - 1; i++) {
		std::cout << "c" << i + 1 << ' ';
	}
	std::cout << "\n\n";
	std::cout << "Gde su ovo koeficijenti jednacine:\n";
	std::stringstream linija;
	for (int i = 0; i < matrica_s->dohv_broj_kolona() - 1; i++) {
		linija << "c" << i + 1 << "*x_" << i + 1 << " + ";
	}
	std::string l = linija.str();
	l.pop_back(); l.pop_back();
	std::cout << l << "= F (F se maksimizuje)\n\n";

	funkcija_za_maksimizaciju = new Matrica(1, matrica_s->dohv_broj_kolona() - 1);

	std::cout << "Molim vas unesite trazene koeficijente:\n";
	funkcija_za_maksimizaciju->ucitaj_iz_ulaznog_toka(std::cin);
	std::cout << '\n';

	return;
}

void pokreniSimpleksAlgoritam() {
	if (matrica_s == nullptr) {
		std::cout << "GRESKA: Mora najpre biti ucitana matrica sistema, povratak na glavni meni\n\n";
		return;
	}
	if (funkcija_za_maksimizaciju == nullptr) {
		std::cout << "GRESKA: Nije ucitana funkcija za maksimizaciju, povratak na glavni meni\n\n";
		return;
	}
	Simplex s;
	s.napravi_pocetnu_tabelu(*matrica_s, *funkcija_za_maksimizaciju);
	std::cout << std::endl;
	s.simplex_algoritam();

	return;
}
