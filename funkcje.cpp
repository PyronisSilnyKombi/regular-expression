#include"header.h"

int menu() {
	int liczba;
	cout << "MENU : " << endl;
	cout << "1 - Temperatury" << endl;
	cout << "2 - Index nasdaq" << endl;
	cout << "3 - Zakoncz program" << endl;
	cout << "Podaj liczbe : "; cin >> liczba;
	system("cls");
	return liczba;
}
int menu2() {
	int liczba;
	cout << "MENU : " << endl;
	cout << "1 - Wczytaj dane z pliku" << endl;
	cout << "2 - Szukaj najwiekszej i najmniejszej wartosci indeksu" << endl;
	cout << "3 - Srednia wartosc indeksu" << endl;
	cout << "4 - Przedzial w ktorym zmiany indeksu byly najwieksze" << endl;
	cout << "5 - Ilosc dni w ktorych indeks osiagnol wynik powyzej podanej wartosci" << endl;
	cout << "6 - Okreslic zakres miesiecy w ktorym bylo prowadzone notowanie" << endl;
	cout << "7 - Cofnij do menu glownego" << endl;
	cout << "Podaj liczbe : "; cin >> liczba;
	system("cls");
	return liczba;
}

string wczytaj(string nazwa_pliku) {
	std::ifstream filestr;
	filestr.open(nazwa_pliku);
	if (filestr.is_open()) {
		stringstream str;
		str << filestr.rdbuf();
		string data = str.str();
		return data;
	}
	else { return "blad odczytu\n"; }
}

vector<temperatura> analizuj(string tekst) {
	vector<temperatura> temperatury;
	temperatura T;
	smatch m;
	regex e("temperature day=\\\"(\\d+\\.\\d+)\\\" min=\\\"(\\d+\\.\\d+)\\\" max=\\\"(\\d+\\.\\d+)\\\" night=\\\"(\\d+\\.\\d+)\\\"");
	while (regex_search(tekst, m, e)) {
		T.temp_d = stof(m[1]);
		T.temp_n = stof(m[4]);
		T.temp_min = stof(m[2]);
		T.temp_max = stof(m[3]);
		temperatury.push_back(T);
		tekst = m.suffix();
	}
	return temperatury;
}

void analizuj2(string tekst, vector<sNotowanie> &dane) {
	sNotowanie N;
	smatch m;
	regex e("\\[\\\"(\\d+)\\-(\\d+)\\-(\\d+)\\\",(\\d+.\\d+),(\\d+.\\d+),(\\d+.\\d+),(\\d+.\\d+),(\\d+.\\d+)\\]");
	cout << "Prosze czekac" << endl;
	while (regex_search(tekst, m, e)) {
		N.year = stoi(m[1]);
		N.month = stoi(m[2]);
		N.day = stoi(m[3]);
		N.index_value = stof(m[4]);
		N.high = stof(m[5]);
		N.low = stof(m[6]);
		N.total_market_value = stof(m[7]);
		N.dividend_market_value = stof(m[8]);
		dane.push_back(N);
		tekst = m.suffix();
	}
}

void sNotowanie::wyswietl() {
	cout << "Date: " << year << "-" << month << "-" << day << endl;
	cout << "high : " << high << endl;
	cout << "low : " << low << endl;
	cout << "total market value : " << total_market_value << endl;
	cout << "dividend market value : " << dividend_market_value << endl;
}

float srednia(const vector<sNotowanie> &dane) {
	float sum = 0;
	int divider = 0;
	for (auto el : dane) {
		sum+=el.index_value;
		divider++;
	}
	return sum / divider;
}

int ilosc_wyzszych_notowan(float liczba, const vector<sNotowanie> &dane) {
	int sum = 0;
	for (auto el : dane) {
		if (liczba < el.index_value) sum++;
	}
	return sum;
}

_Vector_const_iterator<std::_Vector_val<std::_Simple_types<sNotowanie>>> wachania(const vector<sNotowanie> &dane, int okres) {
	float wynik = 0;
	_Vector_const_iterator<std::_Vector_val<std::_Simple_types<sNotowanie>>> miejsce;
	for (auto itr = dane.begin(); itr != dane.end() - okres; itr++) {
		vector<float> wyniki;
		int i = 0;
		for (auto itr2 = itr;i!=okres; itr2++) {
			wyniki.push_back(itr2->index_value);
			i++;
		}
		sort(wyniki.begin(), wyniki.end());
		float roznica = wyniki.back() - wyniki.front();
		if (roznica > wynik) {
			wynik = roznica;
			miejsce = itr;
		}
	}
	

	return miejsce;
}