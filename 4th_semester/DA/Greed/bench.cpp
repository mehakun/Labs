#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>

long lrand()
{
  if (sizeof(int) < sizeof(long))
    return (static_cast<long>(rand()) << (sizeof(int) * 8)) |
      rand();

  return rand();
}

int main(void) {
  int rightSide = lrand(), maxRight = 0;
  int leftSide = 0;
  size_t amountOfPairs;

  std::cin >> amountOfPairs;
  std::vector<std::vector<int> > input(amountOfPairs);
  std::vector<std::vector<int> > answer;
  std::vector<bool> used(amountOfPairs);
  
  for (size_t i = 0; i < amountOfPairs; ++i) {
    input[i] = std::vector<int>(3);
    input[i][2] = i;
    
    input[i][0] = lrand();
    input[i][1] = lrand();
  }
  
  clock_t t;
  t = clock();
  
  for (size_t i = 0; i < amountOfPairs && leftSide < rightSide; ++i) {
    int maxIntervalId = -1;
    for (size_t j = 0; j < amountOfPairs; ++j) {
      if (used[j]) continue;
      if (input[j][0] <= leftSide && input[j][1] > leftSide && (input[j][1] >= rightSide || input[j][1] < rightSide)) {
        if (input[j][1] > maxRight) {
          maxIntervalId = j;
          maxRight = input[j][1];
        }
      }
    }
    if (maxIntervalId != -1) {
      used[maxIntervalId] = true;
      leftSide = input[maxIntervalId][1];
      answer.push_back(input[maxIntervalId]);
    }
  }
  
  std::cout << "time for Greed is " << (float)t/CLOCKS_PER_SEC << '\n';

  t = clock();
  std::vector<unsigned long long> lolz(amountOfPairs);
  size_t sizes = lolz.size();
  for (size_t i = 1; i < sizes; i++) {
    lolz[i] = (i + 2 * 3) + lrand();
    lolz[i] += lolz[(size_t)clock() % (i + 3)];
  }

  
  std::cout << "time for naive is " << (float)t/CLOCKS_PER_SEC / amountOfPairs * std::pow(2, amountOfPairs)<< '\n';
  
  return 0;
}


