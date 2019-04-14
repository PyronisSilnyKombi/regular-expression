#include"header.h"

//2. Wczytaæ plik temperatura.xml, wyodrêbniaj¹c z niego informacje o minimalnej, maksymalnej temperaturze oraz temperturze œredniej dnia i nocy
//3. Wczytaæ plik w formacie json NDX.json zawieraj¹cy dane indeksu Nasdaq. (zapoznaæ siê z zawartoœci¹ listy
//	"column_names":["Trade Date", "Index Value", "High", "Low", "Total Market Value", "Dividend Market Value"]
//					["2010-02-18",1823.39,		1825.82,	1806.76,	3144711884022.0,	319101328.0]
//	a.Wczytaæ do kontenera informacje dotycz¹ce daty notowania i wartoœci indeksu(kolumna 1 i 2 listy)
//	b.Wyœwietliæ datê gdy wartoœæ indeksu by³a najwiêksza / najmniejsza
//	c.Obliczyæ wartoœæ œredni¹ indeksu
//	e.Okreœliæ liczbê dni w których indeks by³ powy¿ej 4600pkt(wartoœæ ta powinna byæ paramtryzowalna)
//	f.okreœliæ zakres miesiêcy w których prowadzone by³o notowanie


//	d.znaleŸæ przedzia³y 5 dniowe, w których zmiennoœæ indeksu by³a najwiêksza

int main() {
	vector<sNotowanie> dane;
	for (;;)
	{
		int wybor = menu();
		switch (wybor) {
		case 1: {
			string plik_txt = wczytaj("temp.txt");
			vector<temperatura> temp = analizuj(plik_txt);
			for (auto itr = temp.begin(); itr != temp.end(); itr++) {
				cout << "Temperatury: " << endl;
				cout << "dzien: " << itr->temp_d << endl << "noc: " << itr->temp_n << endl << "min: " << itr->temp_min << endl << "max: " << itr->temp_max << endl;
			}

			system("pause");
			system("cls");
			break;
		}
		case 2: {
			int i = 0;
			for (int i=0; i!=1;)
			{
				int wybor = menu2();
				switch (wybor) {
				case 1: {
					cout << "Wczytywanie plikow" << endl;
					string plik_xml = wczytaj("nasdaq.txt");
					analizuj2(plik_xml, dane);
					system("pause");
					system("cls");
					break;
				}
				case 2: {
					cout << "2 - Szukaj najwiekszej i najmniejszej wartosci indeksu" << endl;
					sort(dane.begin(), dane.end(), [](const sNotowanie &a, const sNotowanie &b) {
						if (a.index_value > b.index_value) return true;
						return false;
					});
					sNotowanie max = dane.front();
					sNotowanie min = dane.back();
					cout << "Wartosc minimalna indeksu wynosila " << min.index_value << " w dniu " << min.year << "-" << min.month << "-" << min.day << endl;
					cout << "Wartosc maksymalna indeksu wynosila " << max.index_value << " w dniu " << max.year << "-" << max.month << "-" << max.day << endl;

					system("pause");
					system("cls");
					break;
				}
				case 3: {
					cout << "3 - Srednia wartosc indeksu" << endl;
					cout << "Srednia indeksow wynosi: " << srednia(dane) << endl;
					system("pause");
					system("cls");
					break;
				}
				case 4: {
					cout << "4 - Przedzial w ktorym zmiany indeksu byly najwieksze" << endl;
					sort(dane.begin(), dane.end(), [](const sNotowanie &a, const sNotowanie &b) {
						if (a.year < b.year) return true;
						if (a.year == b.year) {
							if (a.month < b.month) return true;
							if (a.month == b.month)
								return a.day < b.day;
						}
						return false;
					});
					int przedzial;
					cout << "Podaj dlugosc przedzialu/okresu dla ktorego ma byc zbadana zmiennosc indeksu w dniach: ";
					cin >> przedzial;
					_Vector_const_iterator<std::_Vector_val<std::_Simple_types<sNotowanie>>> a = wachania(dane, przedzial);
					vector<float> wyniki;
					int i = 0;
					for (auto itr2 = a; i != przedzial; itr2++) {
						wyniki.push_back(itr2->index_value);
						i++;
					}
					sort(wyniki.begin(), wyniki.end());
					float roznica = wyniki.back() - wyniki.front();
					cout << "Od " << a->year << "-" << a->month << "-" << a->day << " do " << (a + przedzial)->year << "-" << (a + przedzial)->month << "-" << (a + przedzial)->day;
					cout << " wahania byly najwieksze i wynosily " << roznica << endl;

					system("pause");
					system("cls");
					break;
				}
				case 5: {
					cout << "5 - Ilosc dni w ktorych indeks osiagnol wynik powyzej podanej wartosci" << endl;
					int liczba;
					cout << "Podaj liczbe od jakiej ma byc wiekszy indeks: ";
					cin >> liczba;
					cout << "Ilosc notowan z wartoscia indeksu wyzsza od podanej wynosi: " << ilosc_wyzszych_notowan(liczba, dane) << endl;
					system("pause");
					system("cls");
					break;
				}
				case 6: {
					cout << "6 - Okreslanie zakresu w ktorym bylo prowadzone notowanie" << endl;
					sort(dane.begin(), dane.end(), [](const sNotowanie &a, const sNotowanie &b) {
						if (a.year < b.year) return true;
						if (a.year == b.year) {
							if (a.month < b.month) return true;
							if (a.month == b.month)
								return a.day < b.day;
						}
						return false;
					});
					sNotowanie max = dane.front();
					sNotowanie min = dane.back();
					cout << "Notowanie rozpoczolo sie w dniu " << max.year << "-" << max.month << "-" << max.day << endl;
					cout << "Notowanie zakonczylo sie w dniu " << min.year << "-" << min.month << "-" << min.day << endl;

					system("pause");
					system("cls");
					break;
				}
				case 7: {
					i = 1;
					system("cls");
					break;
				}

				default: {
					cout << "PODAJ POPRAWNA LICZBE !!!" << endl;
					cin.ignore();
				}
				}
			}
			system("cls");
			break;
		}
		case 3: {
			return 0;
		}
		default: {
			cout << "PODAJ POPRAWNA LICZBE !!!" << endl;
			cin.ignore();
		}
		}
	}
}