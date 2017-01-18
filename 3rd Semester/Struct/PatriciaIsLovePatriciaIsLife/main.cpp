#include <iostream>
#include <iomanip>
#include <string>
#include "patricia.h"

std::string& StringToUpper(std::string& strToConvert) {
  for (auto p = strToConvert.begin(); strToConvert.end() != p; p++)
    *p = toupper(*p);
  return strToConvert;
}

int main(void) {
  unsigned long long tempValue = 0;
  std::string option;
  TPatricia* MyWife = new TPatricia();
  
  while (std::cin >> option) {

    switch(option.front()){
    case '+':
      std::cin >> std::setw(CHAR_LIMIT) >> option;
      std::cin >> tempValue;

      if (option.back() == '0')
        option.pop_back();
      try {
        if (MyWife->Insert(StringToUpper(option), tempValue))
          std::cout << "OK" << std::endl;
        else
          std::cout << "Exist" << std::endl;
      } catch (std::bad_alloc& ba) {
        std::cout << "ERROR: " << ba.what();
      }
        break;
    case '-':
      std::cin >> option;
      if (MyWife->Delete(StringToUpper(option)))
        std::cout << "OK" << std::endl;
      else
        std::cout << "NoSuchWord" << std::endl;
      break;
    case '!':
      std::cin >> option;
      if (option == "Save") {
        std::cin >> option;
        if (option.back() == '0')
          option.pop_back();
        
        if (MyWife->Serialize(option))
          std::cout << "OK" << std::endl;
      }
      if (option == "Load") {
        std::cin >> option;
        if (option.back() == '0')
          option.pop_back();
        try {
          if (MyWife->DeSerialize(option))
            std::cout << "OK" << std::endl;
        } catch (std::bad_alloc& ba) {
          std::cout << "ERROR: " << ba.what();
        }
      }
      break;
    default:
      if (option.empty())
        break;
      if (option.back() == '0')
        option.pop_back();

      auto* herp = MyWife->Search(StringToUpper(option));
      if (herp == nullptr) {
        std::cout << "NoSuchWord" << std::endl;
        break;
      } else {
        std::cout << "OK: " << herp->GetData() << std::endl;
        break;
      }
      
      break;
    }
  }

  delete MyWife; //Sorry
}
