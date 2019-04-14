#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<regex>
#include<string>
#include<vector>
using namespace std;

struct temperatura {
	float temp_d;
	float temp_n;
	float temp_min;
	float temp_max;
};

struct sNotowanie {
	int year, month, day;
	float index_value, high, low, total_market_value, dividend_market_value;

	void wyswietl();
};

string wczytaj(string nazwa_pliku);
vector<temperatura> analizuj(string tekst);
void analizuj2 (string plik_txt, vector<sNotowanie> &dane);
float srednia(const vector<sNotowanie> &dane);
int ilosc_wyzszych_notowan(float liczba, const vector<sNotowanie> &dane);
_Vector_const_iterator<std::_Vector_val<std::_Simple_types<sNotowanie>>> wachania(const vector<sNotowanie> &dane, int okres);

int menu();
int menu2();