#include <iostream>
#include <string>
#include <iomanip>

#include "Vektorius.cpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>

#include "Studentas.h"

using namespace std;
	
//deklaracijos
#define FILEINPUT
#define MAXGEN 20


bool gavoSkola(const Studentas& st);


void rusiuoti(Vektorius<Studentas>& stud, Vektorius<Studentas>& vec1, Vektorius<Studentas>& vec2);

void generuoti(int size, string suffix);


void isvesti(Vektorius<Studentas>& cool, Vektorius<Studentas>& notcool);

void avardas(string* vrd, string* pvrd);
void rastiFailus(string* fpav);


void skaityti(bool input, int num);


int main(int argc, char** argv) {
	srand(time(NULL));

 	setlocale(LC_ALL, "Lithuanian");
	cout << "Ar norite generuoti naujus failus? [T]aip, [N]e " << endl;
	char AA = cin.get();
	if(AA == 'T' || AA == 't'){
		generuoti(1000, to_string(1000));
		generuoti(10000, to_string(10000));
		generuoti(100000, to_string(100000));
		generuoti(1000000, to_string(1000000));
	}
	bool input = false;
	fflush(stdin);
	//atskiros funkcijos
	int suf[] = {1000, 10000, 100000, 1000000};
	for(int I = 0; I < 4; I++){
		cout << "===================================" << endl;
		cout << setw(7) << suf[I] << ": | Skaitymas |" << " Rûðiavimas |" << endl;
		cout << setw(10) << "Vektorius: |";
		skaityti(input, suf[I]); 
	}
	
	system("pause");
	return 0;
}



void skaityti(bool input, int num) {
	
	
	auto start = chrono::high_resolution_clock::now();
	//deklaracija
	Vektorius<Studentas> studentai;
	Vektorius<Studentas> cool;
	Vektorius<Studentas> notcool;
	int counter = 0;
	string vrd; //laikinas skaitliukas vardui
	Studentas S;

	//===============================DARBAS SU FAILAIS==================================

	string fname = "Studentai";
	fname += to_string(num);
	fname +=  + ".txt";
	
	ifstream kursiokai(fname);
	string data; //vardas
	string unused;
	if(!getline(kursiokai, unused)){ //klaidu patikra ir kategoriju praleidimas;
		cout << "Failas nerastas arba tuðèias!" << endl;
	}
	stringstream buferis;
	buferis << kursiokai.rdbuf();
	kursiokai.close();
	//failo ivedimas
	while(getline(buferis, data)){
		
		stringstream eilute(data);
		Studentas SV(eilute);
		studentai.push_back(SV);
	}

	auto end = chrono::high_resolution_clock::now();
		chrono::duration<double> diff = end - start;
		cout << setw(8) << fixed << setprecision(5) << diff.count() << "s. | ";
	
	//apdorojimas
	rusiuoti(studentai, cool, notcool);
	isvesti(cool, notcool);

}

bool gavoSkola(const Studentas& st){
	return st.gavoSkola();
}

bool palyginti(const Studentas& s1, const Studentas& s2){
	return s1 > s2;
}


void rusiuoti(Vektorius<Studentas>& stud, Vektorius<Studentas>& vec1, Vektorius<Studentas>& vec2){
	auto start = chrono::high_resolution_clock::now();
	Vektorius<Studentas>::iterator el = stable_partition(stud.begin(), stud.end(), gavoSkola); //iteratorius - riba
	Vektorius<Studentas> geri(el, stud.end());

	vec1 = geri;
	//matavimas
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> dif = end - start;
	cout <<  fixed << setprecision(6) << dif.count() << "s. |" << endl;
}


void isvesti(Vektorius<Studentas>& cool, Vektorius<Studentas>& notcool){
	auto start = chrono::high_resolution_clock::now();
	ofstream m("Linksmuciai.txt");
	ofstream n("Sadbois.txt");
	//buferis
	stringstream good;
	stringstream bad;
	
	for(auto &B : cool){
		
		good << B.vardas() << " " << B.pavarde() << " ";
		for(int J = 0; J < B.printND().size(); J++){
			good << B.printND().at(J) << " ";
		}
		good << B.egzaminas() << endl;
		//cout << "Linksmuciai " << endl;
	}
	m << good;
	
	for(auto &W : notcool){
		
		bad << W.vardas() << " " << W.pavarde() << " ";
		for(int K = 0; K < W.printND().size(); K++){
			bad << W.printND().at(K) << " ";
		}
		bad << W.egzaminas() << endl;
		//cout << "Sadbois " << endl;
	}
	n << bad;
	m.close();
	n.close();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> dif = end - start;
	//cout << "Sugrupuotu failu sukurimas uztruko: " << dif.count() << " s." << endl;
}

void avardas(string* vrd, string* pvrd){ //atsitiktinai generuojama rodykle i pora eiluciu, vardo ir pavardes
	string vardai[14] = {"Giedrius", "Mantas", "Karolis", "Darius", "Simas", "Simona", "Gabija", "Laura", "Ieva", "Migle", "Justas", "Tadas", "Austeja", "Auguste"};
	string pavardes[14];
	for(int H = 0; H < 14; H++){ 
		if(vardai[H].back() == 's'){
			pavardes[H] = "Pavardenis";// + to_string(H);
		} else {
			pavardes[H] = "Pavardaite";// + to_string(H);
		}
	}

	int rint = rand() % 14;
	*vrd = vardai[rint];
	*pvrd = pavardes[rint];
}

void generuoti(int size, string suffix){
	auto start = chrono::high_resolution_clock::now();
	ofstream h("Studentai" + suffix + ".txt");
	//h << setw(20);
	h << "vardas" << "pavarde" << "Namu darbai " << " Egzaminas" << endl;
			srand(time(NULL));
	for(int I = 0; I < size; I++){
		string vardas, pavarde;
		avardas(&vardas, &pavarde);
		//cout << vardas << " \t " << pavarde << endl;
		h << vardas << " " << pavarde << " ";
		int ndsk = 8;
		for(int I = 0; I < ndsk; I++){
			h << rand()%10+1 << " ";
		}
		h << rand()%7+4 << " " << endl; //egzaminas ir baigia generuoti failo eilute.
	}
	h.close();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end - start;
	//std::cout << size << " elementu generavimas uztruko: " << diff.count() << " s." << endl;
}

