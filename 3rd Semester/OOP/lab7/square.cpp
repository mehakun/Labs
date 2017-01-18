#include "square.h"

Square::Square() : Square(-1.0){}
Square::Square(const Square &obj) {
  side_a = obj.side_a;
}

Square::Square(double i) {
  this->side_a = i;
}

Square::Square(std::istream &is) {
  is >> this->side_a;
}

double Square::getSquare() {
  return this->side_a * this->side_a;
}

void Square::setParams(std::istream &is) {
  is >> this->side_a;
}

void Square::Print() {
  std::cout << "Type of figure is square" << std::endl
            << "a = " << this->side_a << std::endl;
}

Square Square::operator++() {
  this->side_a++;
}

Square Square::operator+(const Square& obj) const{
  Square res;
  res.side_a = side_a + obj.side_a;
  return res;
}

std::ostream& operator<<(std::ostream& os, const Square& obj) {
  if (obj == Square())
    return os;
  
  os << "Length of square is "
     << obj.side_a << std::endl;
  return os;
}

std::istream& operator>>(std::istream& is, Square& obj) {
  is >> obj.side_a;
  return is;
}

bool Square::operator==(const Square& obj) const{
  return side_a == obj.side_a;
}

Square Square::operator=(const Square& obj) {
  if (this == &obj) return *this;

  side_a = obj.side_a;
  return *this;
}
