#include <algorithm>
#include <iostream>
#include <vector>


int main() {
  int rightSide, maxRight = 0;
  int leftSide = 0;
  size_t amountOfPairs;
  std::cin >> amountOfPairs;
  std::vector<std::vector<int> > input(amountOfPairs);
  std::vector<std::vector<int> > answer;
  std::vector<bool> used(amountOfPairs);
  
  for (size_t i = 0; i < amountOfPairs; ++i) {
    input[i] = std::vector<int>(3);
    input[i][2] = i;
    
    std::cin >> input[i][0] >> input[i][1];
  }
  std::cin >> rightSide;
  
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

  if (answer.size() != 0) {
    if (answer[0][0] <= 0 && answer[answer.size() - 1][1] >= rightSide) {
      std::cout << answer.size() << '\n';
      std::sort(answer.begin(), answer.end(),
                [](const std::vector<int>& a, const std::vector<int>& b) {
                  return a[2] < b[2];
                });
      
      for (const auto& pair: answer) {
        std::cout << pair[0] << ' ' << pair[1] << '\n';
      }
    } else {
      std::cout << "0\n";
    }
  } else {
    std::cout << "0\n";
  }

  
  return 0;
}
