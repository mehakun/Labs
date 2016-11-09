#include "pryam.h"

Pryam::Pryam() : Pryam(0, 0) {}
Pryam::Pryam(const Pryam &obj) {
  side_a = obj.side_a;
  side_b = obj.side_b;
}

Pryam::Pryam(double i, double j) {
  this->side_a = i;
  this->side_b = j;
  std::cout << "Pryamougolnik created: " << this->side_a << ", "
            << this->side_b << std::endl;
}

void Pryam::setParams(std::istream &is) {иxb
  is >> this->side_a;
  is >> this->side_b;
}

double Pryam::Square() {
  return this->side_a * this->side_b;
}

void Pryam::Print() {
  std::cout << "The type of figure is PRYAMOUGOLNIK" << std::endl
            << "a = " << this->side_a << std::endl
            << "b = " << this->side_b << std::endl;
}

Pryam::Pryam(std::istream &is) {
  is >> this->side_a;
  is >> this->side_b;
}
