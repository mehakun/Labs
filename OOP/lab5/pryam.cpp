#include "pryam.h"

Pryam::Pryam() : Pryam(-1.0, -1.0) {}
Pryam::Pryam(const Pryam &obj) {
  side_a = obj.side_a;
  side_b = obj.side_b;
}

Pryam::Pryam(double i, double j) {
  this->side_a = i;
  this->side_b = j;
}

void Pryam::setParams(std::istream &is) {
  is >> this->side_a;
  is >> this->side_b;
}

double Pryam::getSquare() {
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

bool Pryam::operator==(const Pryam& obj) const {
  return ((this->side_a == obj.side_a) && (this->side_b == obj.side_b));
}

Pryam Pryam::operator=(const Pryam& obj) {
  side_a = obj.side_a;
  side_b = obj.side_b;

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Pryam& obj) {
  if (obj == Pryam())
    return os;

  os << "The length of Pryam is " << obj.side_a
     << " " << obj.side_b << std::endl;

  return os;
}
