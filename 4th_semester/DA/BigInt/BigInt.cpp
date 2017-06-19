#include "BigInt.h"

TBigInt::TBigInt(const std::string& str) {
  for (int i = str.size(); i > 0; i -= R) {
    int num = 0;

    for (int j = (i - R > 0 ? i - R : 0); j < i; j++) {
      num = num * BASEOFBASE + str[j] - '0';
    }

    numbers.push_back(num);
  }

  FixZero();
}

TBigInt::TBigInt(const size_t& size) {
  numbers = std::vector<int>(size, 0);
}

TBigInt::TBigInt(int num) {
  if (num == 0) {
    numbers.push_back(num);
  } else {
    while (num != 0) {
      numbers.push_back(num % BASE);
      num /= BASE;
    }
  }
}

TBigInt::TBigInt(std::vector<int>& data) {
  numbers.swap(data);
}

bool TBigInt::operator<(const TBigInt& other) const {
  if (other.Size() > this->Size()) {
    return true;
  } else if (other.Size() < this->Size()) {
    return false;
  }

  for (int i = other.Size() - 1; i >= 0; i--) {
    if (numbers[i] < other.Get(i)) {
      return true;
    } else if (numbers[i] > other.Get(i)) {
      return false;
    }
  }

  return false;
}

bool TBigInt::operator>(const TBigInt& other) const {
  if (other.Size() < this->Size()) {
    return true;
  } else if (other.Size() > this->Size()) {
    return false;
  }

  for (int i = other.Size() - 1; i >= 0; i--) {
    if (numbers[i] > other.Get(i)) {
      return true;
    } else if (numbers[i] < other.Get(i)) {
      return false;
    }
  }

  return false;
}

bool TBigInt::operator==(const TBigInt& other) const {
  if (other.Size() != this->Size()) {
    return false;
  }

  for (int i = other.Size() - 1; i >= 0; i--) {
    if (numbers[i] != other.Get(i)) {
      return false;
    }
  }

  return true;
}

TBigInt TBigInt::operator+(const TBigInt& other) const {
  size_t maxSize = std::max(this->Size(), other.Size()) + 1;
  TBigInt result(maxSize);
  int r, k = 0;
    
  for (size_t i = 0; i < maxSize; i++) {    
    r = Get(i) + other.Get(i) + k;
    result.Set(i, r % BASE);
    k = r / BASE;
  }

  if (r != 0) {
    result.Set(maxSize - 1, r);
  }

  result.FixZero();
  return result;
}

TBigInt TBigInt::operator-(const TBigInt& other) const {
  if ((*this) < other) {
    throw std::runtime_error("Error");
  }
  
  size_t size = Size();
  TBigInt result(size);
  int overload = 0;
  
  for (size_t i = 0; i < size ; i++) {
    int tmp = numbers[i] - other.Get(i) + overload;

    if (tmp < 0) {
      overload = -1;
      result.Set(i, tmp + BASE);
    } else {
      overload = 0;
      result.Set(i, tmp);
    }
  }
  
  result.FixZero();
  
  return result;
}

void TBigInt::FixZero() {
  while (Size() > 1 && numbers.back() == 0) {
    numbers.pop_back();
  }
}

void TBigInt::AddRadix(const size_t pos, const size_t count) {
  auto iter = numbers.begin();
  numbers.insert(iter + pos, count, 0);
}

void TBigInt::MoveLeft() {
  numbers.erase(numbers.begin());
}

TBigInt TBigInt::Karacuba(const TBigInt& other) const{
  if (this->Size() < 4 || other.Size() < 4) {
    return (*this) * other;
  }
  
  TBigInt x0 = this->Slice(0, this->Size() / 2);
  TBigInt x1 = this->Slice(this->Size() / 2);
  TBigInt y0 = other.Slice(0, other.Size() / 2);
  TBigInt y1 = other.Slice(other.Size() / 2);
  TBigInt x0y0 = x0.Karacuba(y0);
  TBigInt x1y1 = x1.Karacuba(y1);
  TBigInt x0x1y0y1 = (x0 + x1).Karacuba(y0 + y1);

  return x1y1 * TBigInt(static_cast<int>(pow(BASE, 2))) + TBigInt(BASE) * x0x1y0y1 + x0y0;
}

TBigInt TBigInt::operator*(const TBigInt& other) const {
  size_t thisSize = Size();
  size_t otherSize = other.Size();
  TBigInt result(thisSize + otherSize);
  int remainder;
  
  for (size_t i = 0; i < otherSize; i++) {
    if (other.Get(i) != 0) {
      remainder = 0;

      for (size_t j = 0; j < thisSize; j++) {
        int tmp = numbers[j] * other.Get(i) + result.Get(i + j) + remainder;

        result.Set(i + j, tmp % BASE);
        remainder = tmp / BASE;
      }

      result.Set(i + thisSize, remainder);
    }
  }

  result.FixZero();
  
  return result;
}

TBigInt TBigInt::operator^(const TBigInt& r) const {
  if (Size() == 1 && Get(0) == 0) {
    if (r.Size() == 1 && r.Get(0) == 0) {
      throw std::runtime_error("Error");
    }

    return (*this);
  }
  if (r.Size() == 1 && r.Get(0) == 1) {
    return (*this);
  }
  if (r.Size() == 1 && r.Get(0) == 0 ) {
    return TBigInt(1);
  }
  
  if (r.Get(0) % 2 == 0) {
    TBigInt result = (*this)^(r / 2);
    
    return result * result;
  } else {
    TBigInt result = (*this)^(r - TBigInt(1));
    
    return (*this) * result;
  }
}

TBigInt TBigInt::Div(const TBigInt& other) const {
  TBigInt result(Size());
  int remainder = 0;

  for (int i = Size() - 1; i >= 0; i--) {
    int tmp = numbers[i] + remainder * BASE;
    
    result.Set(i, tmp / other.Get(0));
    remainder = tmp % other.Get(0);
  }
  
  result.FixZero();
  return result;
}

TBigInt TBigInt::operator/(const TBigInt& other) const {
  if (other.Size() == 1) {
    switch (other.Get(0)) {
    case 0:
      throw std::runtime_error("Error");
      break;
    case 1:
      return (*this);
      break;
    default:
      return Div(other);
      break;
    }
  }
  if (other.Size() > Size()) {
    return TBigInt(0);
  }

  size_t n = other.Size();
  size_t m = Size() - n;
  TBigInt d = TBigInt(BASE / (other.Get(n - 1) + 1));
  TBigInt u = (*this) * d;
  TBigInt v = other * d;
  TBigInt factor(m + 1);
  int vLast = v.Get(n -1);
  int vSecLast = v.Get(n - 2);
  v.AddRadix(0, m);
  for (int i = m; i >= 0; i--) {
    size_t del = i + n;
    int pair = u.Get(del) * BASE + u.Get(del - 1);
    int qq = pair / vLast;
    int rr = pair % vLast;
    while (rr < BASE &&
           (qq == BASE ||
            (qq * vSecLast) >
            (BASE * rr + u.Get(del - 2))
            )) {
      qq -= 1;
      rr += vLast;
    }

    factor.Set(i, qq);
    u = u - TBigInt(qq) * v;

    v.MoveLeft();
  }

  factor.FixZero();

  return factor;
}

void TBigInt::Print() const{
  std::cout << numbers[Size() - 1];
  
  for (int i = Size() - 2; i >= 0; i--) {
    std::cout << std::setfill('0') << std::setw(R) << numbers[i];
  }

  std::cout << '\n';
}

TBigInt TBigInt::Slice(const size_t from, const int to) const{
  std::vector<int> tmp(numbers.begin() + from, to == -1 ? numbers.end() : numbers.begin() + to);

  return TBigInt(tmp);
}

