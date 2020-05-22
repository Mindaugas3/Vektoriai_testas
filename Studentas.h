#include <iostream>
#include <string>
#include <vector>


#pragma once
class Studentas {
// realizacija
private:
  std::string vardas_ = "";
  std::string pavarde_ = "";
  float egzaminas_;
  std::vector<float> nd_;
// interfeisas
public:
  //konstruktoriai
  Studentas() : egzaminas_(0) { }  // default konstruktorius
  Studentas(std::istream& is);
  Studentas(const Studentas& s);
  //geteriai
  std::string vardas() const { return vardas_; }    // get'eriai, inline
  std::string pavarde() const { return pavarde_; }  // get'eriai, inline
  std::vector<float> printND() const { return nd_;}
  float vidurkis() const;
  bool gavoSkola() const;
  float egzaminas() const { return egzaminas_;}
  //seteriai
  void set_vardas(std::string vardas);
  void set_pavarde(std::string pavarde);
  void set_egzaminas(float balas);
  void set_nd(std::vector<float> nd);

  std::istream& readStudent(std::istream& I, const Studentas& s);  // set'eriai
  Studentas operator= (const Studentas& s);
  bool operator> (const Studentas& s) const;
  bool operator< (const Studentas& s) const;
  ~Studentas();
};
