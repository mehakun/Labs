#ifndef BIGINT_H
#define BIGINT_H
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

static const int R = 4;
static const int BASEOFBASE = 10;
static const int BASE = pow(BASEOFBASE, R);

class TBigInt {
 private:
  inline void FixZero();
  TBigInt Div(const TBigInt& other) const;
  std::vector<int> numbers;
public:
  TBigInt() {};
  TBigInt(const std::string& str);
  TBigInt(const size_t& size);
  TBigInt(std::vector<int>& data);
  TBigInt(int num);
  
  ~TBigInt() {};
  
  TBigInt operator+ (const TBigInt& other) const;
  TBigInt operator- (const TBigInt& other) const;
  TBigInt operator/ (const TBigInt& other) const;
  TBigInt operator* (const TBigInt& other) const;
  TBigInt Karacuba(const TBigInt& other) const;
  TBigInt operator^ (const TBigInt& r) const;
  bool operator< (const TBigInt& other) const;
  bool operator> (const TBigInt& other) const;
  bool operator== (const TBigInt& other) const;
  
  inline size_t Size() const { return numbers.size(); };
  inline int Back() const { return numbers.back(); };
  void AddRadix(const size_t pos, const size_t count);
  void MoveLeft();
  TBigInt Slice(const size_t from, const int to = -1) const;
  int Get(size_t i) const { return (i < numbers.size() ? numbers[i] : 0); };
  void Set(size_t i, int num) { numbers[i] = num;};
  void Print() const;
};

#endif
