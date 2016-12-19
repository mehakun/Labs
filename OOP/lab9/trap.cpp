#include "trap.h"

Trap::Trap() : Trap(-1.0, -1.0, -1.0, -1.0) {}
Trap::Trap(const Trap &obj) {
  side_a = obj.side_a;
  side_b = obj.side_b;
  side_c = obj.side_c;
  side_d = obj.side_d;
}

Trap::Trap(double i, double j, double k, double l) {
  this->side_a = i;
  this->side_b = j;
  this->side_c = k;
  this->side_d = l;
}

Trap::Trap(std::istream &is) {
  is >> this->side_a;
  is >> this->side_b;
  is >> this->side_c;
  is >> this->side_d;
}

void Trap::setParams(std::istream &is) {
  is >> this->side_a;
  is >> this->side_b;
  is >> this->side_c;
  is >> this->side_d;
}

void Trap::Print() {
  std::cout <<"Type of figure is TRAP"<< std::endl
            << "a = " << this->side_a << std::endl
            << "b = " << this->side_b << std::endl
            << "c = " << this->side_c << std::endl
            << "d = " << this->side_d << std::endl;
}

bool Trap::operator==(const Trap& obj) const {
  return ((this->side_a == obj.side_a) && (this->side_b == obj.side_b)
          && (this->side_c == obj.side_c) && (this->side_d == obj.side_d));
}

Trap Trap::operator=(const Trap& obj) {
    if (this == &obj) return *this;

  side_a = obj.side_a;
  side_b = obj.side_b;
  side_c = obj.side_c;
  side_d = obj.side_d;
  
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Trap& obj) {
  if (obj == Trap())
    return os;
  
  os << "Length of trap is "
     << obj.side_a << " " << obj.side_b
     << " " << obj.side_c << " "
     << obj.side_d << std::endl;
  
  return os;
}


double Trap::getSquare() {
  double h = std::sqrt(this->side_c * this->side_c - 0.25 *
                        std::pow((this->side_c * this->side_c - this->side_d * this->side_d)
                                  /(this->side_b - this->side_a) + this->side_b - this->side_a
                                    , 2.0));
  return (this->side_a + this->side_b)/2 + h;
}
