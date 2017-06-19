#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

int main(void) {
  unsigned long long number;
  std::cin >> number;
  std::vector<unsigned long long> answer(number + 1);
  clock_t t;
  t = clock();
  
  for(size_t i = 2; i <= number; i++) {
    
    if (i % 3 == 0 && answer[i] > answer[i / 3]) {
      answer[i] = answer[i / 3];
    }
    if (i % 2 == 0 && answer[i] > answer[i / 2]) {
      answer[i] = answer[i / 2];
    }

    answer[i] += i;
  }
  
  std::cout << "time for DP is " << (float)t/CLOCKS_PER_SEC << '\n';

  t = clock();
  std::vector<unsigned long long> lolz(number);
  size_t sizes = lolz.size();
  for (size_t i = 1; i < sizes; i++) {
    lolz[i] = (i + 2 * 3) + 2;
    lolz[i] += lolz[(size_t)clock() % (i + 3)];
  }

  
  std::cout << "time for naive is " << (float)t/CLOCKS_PER_SEC / number * std::pow(2, number)<< '\n';
  
  return 0;
}


