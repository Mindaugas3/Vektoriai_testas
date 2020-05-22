#include "Studentas.h"
#pragma once
// konstruktoriaus realizacija
Studentas::Studentas(std::istream& is) { 
  // kreipiasi � Studentas::readStudent;

  readStudent(is, *this);  
}

Studentas::Studentas(const Studentas& s){
    try{
        //kopijavimo konstruktorius
        vardas_ = s.vardas();
        pavarde_ = s.pavarde();
        nd_ = s.printND();
        egzaminas_ = s.egzaminas();
    } catch (std::exception& e) {
        e.what();
    }

}

// Studentas::readStudent realizacija
std::istream& Studentas::readStudent(std::istream& I, const Studentas& S) {
  // Member funkcijos realizacija paremta ankstesniojo 2-ojo darbo funkcija: 
  // std::istream& readStudent(std::istream&, Studentas&)
    std::string vardas, pavarde;
  	I >> vardas;
  	I >> pavarde;
  	set_vardas(vardas);
  	set_pavarde(pavarde);
  	float ndbalas;
	std::vector<float> ndzmogui;
	while(I >> ndbalas){
		//namu darbai - vektorius.
		ndzmogui.push_back(ndbalas);			
	}
	int J = (int) ndzmogui.size();
	set_egzaminas(ndzmogui.at(J - 1));
	ndzmogui.pop_back();
	set_nd(ndzmogui);
	//S.egzaminas_ = egzaminas; 
    return I;
}

bool Studentas::gavoSkola() const{
	return (this->vidurkis() < 5);
  // realizacija 
}

//seteriai
void Studentas::set_vardas(const std::string vardas){
	vardas_ = vardas;
}

void Studentas::set_pavarde(const std::string pavarde){
	pavarde_ = pavarde;
}

void Studentas::set_egzaminas(float balas){
	egzaminas_ = balas;
}

void Studentas::set_nd(std::vector<float> nd){
	nd_ = nd;
}

float Studentas::vidurkis() const{
	float tempvid = 0;
	int J = 0;
	if(this->nd_.empty()) return 0;
	
	while(J < this->nd_.size()){
			tempvid += this->nd_.at(J) * 0.4;
			J++;
		}
	tempvid /= J;
	tempvid += this->egzaminas_ * 0.6;
	return tempvid;
}

//operatoriai - priskyrimas
Studentas Studentas::operator = (const Studentas& s){
		Studentas A;
		A.set_vardas(s.vardas());
		A.set_pavarde(s.pavarde());
		A.set_egzaminas(s.egzaminas());
		A.set_nd(s.printND());		
		return A; 
}

//palyginimo operatoriai
bool Studentas::operator > (const Studentas& s) const{
	if(this->vidurkis() == s.vidurkis()) return this->pavarde() > s.pavarde();
	return this->vidurkis() > s.vidurkis();
}

bool Studentas::operator < (const Studentas& s) const{
	if(this->vidurkis() == s.vidurkis()) return this->pavarde() < s.pavarde();
	return this->vidurkis() < s.vidurkis();
}

//destruktorius

Studentas::~Studentas(){
	nd_.clear();
}


/* Realizacija likusi� (member) funkcij�
 .
 .
 .

Studentas::Studentas(std::istream& I) {
    std::string vardas, pavarde;
    I >> vardas;
    I >> pavarde;
    set_vardas(vardas);
    set_pavarde(pavarde);
    float ndbalas;
    std::vector<float> ndzmogui;
    while(I >> ndbalas){
        //namu darbai - vektorius.
        ndzmogui.push_back(ndbalas);
    }
    int J = (int) ndzmogui.size();
    set_egzaminas(ndzmogui.at(J - 1));
    ndzmogui.pop_back();
    set_nd(ndzmogui);
}
*/
