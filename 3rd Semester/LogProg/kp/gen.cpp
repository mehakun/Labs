#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>

struct person {
  std::string name;
  std::string surn;
  std::string id;
};

int main() {
  std::map<std::string, std::string> map;
  person foo;
  std::map<std::string, std::string>::iterator iter;
  std::string tmp1;
  std::string tmp2;
  std::string husb;
  std::string wife;
  std::string child;
  std::vector<std::string> male;

  while(std::cin >> tmp2) {
    if(tmp2 == "INDI") {
      foo.id = tmp1;
    } else if(tmp1 == "GIVN") {
      foo.name = tmp2;
    } else if(tmp1 == "SURN") {
      foo.surn = tmp2;
    } else if(tmp1 == "_MARNM") {
      foo.surn = tmp2;
    } else if(tmp1 == "SEX") {
      if(tmp2 == "M") {
        male.emplace_back(std::string(foo.surn + " " + foo.name));
      }
    } else if(tmp2 == "_UID") {
      auto str = std::string(foo.surn + " " + foo.name);
      map.insert(std::make_pair(foo.id, str));
    } else if(tmp2 == "FAM") {
      while(tmp2 != "_UID") {
        if(tmp1 == "HUSB") {
          iter = map.find(tmp2);
          husb = iter->second;
        } else if(tmp1 == "WIFE") {
          iter = map.find(tmp2);
          wife = iter->second;
        } else if(tmp1 == "CHIL") {
          iter = map.find(tmp2);
          child = iter->second;
          std::cout << "parent('" << husb << "', '" << child << "')." << std::endl
                    << "parent('" << wife << "', '" << child << "')." << std::endl;
        }
        tmp1 = tmp2;
        std::cin >> tmp2;
      }
    }
    tmp1 = tmp2;
  }
  
  std::cout << std::endl;
  
  for(auto i : male) {
    std::cout << "sex('" << i << "', m" << ")." << std::endl;
  }

  return 0;
}
