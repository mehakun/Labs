#include <iostream>
#include <vector>

int main(void) {
  unsigned long long number;
  std::cin >> number;
  std::vector<unsigned long long> answer(number + 1);
  std::vector<short> decision(number + 1);

  for(size_t i = 2; i <= number; i++) {
    answer[i] = answer[i - 1];
    decision[i] = 1;
    
    if (i % 3 == 0 && answer[i] > answer[i / 3]) {
      decision[i] = 3;
      answer[i] = answer[i / 3];
    }
    if (i % 2 == 0 && answer[i] > answer[i / 2]) {
      decision[i] = 2;
      answer[i] = answer[i / 2];
    }

    answer[i] += i;
  }

  std::cout << answer[number] << '\n';
  
    if (decision[number] == 1) {
      std::cout << "-1";
      number--;
    } else if (decision[number] == 2) {
      std::cout << "/2";
      number /= 2;      
    } else {
      std::cout << "/3";
      number /= 3;      
    }

  for (size_t i = number; i != 1;) {
    if (decision[i] == 1) {
      std::cout << (i == 2 ? "/2" :" -1");
      i--;
    } else if (decision[i] == 2) {
      std::cout << " /2";
      i /= 2;      
    } else {
      std::cout << " /3";
      i /= 3;      
    }
  }

  std::cout << '\n';
  
  return 0;
}
