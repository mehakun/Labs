#include "trap.h"

Trap::Trap() : Trap(0, 0, 0, 0) {}
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
  std::cout << "Trap created: " << this->side_a << ", " 
            << this->side_b << ", "
            << this->side_c << ", "
            << this->side_d << std::endl;
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

double Trap::Square() {
  double h = std::sqrt(this->side_c * this->side_c - 0.25 *
                        std::pow((this->side_c * this->side_c - this->side_d * this->side_d)
                                  /(this->side_b - this->side_a) + this->side_b - this->side_a
                                    , 2.0));
  return (this->side_a + this->side_b)/2 + h;
}
