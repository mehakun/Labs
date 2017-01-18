#include <iostream>
#include <cmath>
#include "square.h"
#include "trap.h"
#include "pryam.h"

using namespace std;
void menu(void) {
  cout << "1) Options for Square" << endl;
  cout << "2) Options for Pryamougolnik" << endl;
  cout << "3) Options for Trapecia" << endl;
  cout << "4) Exit" << endl;
  cout << "Enter command:" << endl;
}
void opts(void) {
  cout << "1) Set parameteres for figure" << endl;
  cout << "2) Print figure's parameteres" << endl;
  cout << "3) Show figure's square" << endl;
  cout << "5) Exit" << endl;
}

int main(void)
{
  int opt;
  Trap LilB;
  Squar Kvad;
  Pryam Pram;
  
  do {
    menu();
    cin >> opt;
    
    switch(opt){
    case 1:{
      opts();
      cin >> opt;

      switch(opt){
      case 1:{
        cout << "Enter params:" << endl;
        Kvad.setParams(cin);
        break;
      }
      case 2:
        Kvad.Print();
        break;
      case 3:
        cout << "Square is: " << Kvad.Square() << endl;
        break;
      default:
        break;
      };
    }
      break;
    case 2:{
      opts();
      cin >> opt;
      
      switch(opt){
      case 1:{
        cout << "Enter params:" << endl;
        Pram.setParams(cin);
        break;
      }
      case 2:
        Pram.Print();
        break;
      case 3:
        cout << "Square is: " << Pram.Square() << endl;
        break;
      default:
        break;
      };
    }
      break;      
    case 3:{
      opts();
      cin >> opt;
      
      switch(opt){
      case 1:{
        cout << "Enter params:" << endl;
        LilB.setParams(cin);
        break;
      }
      case 2:
        LilB.Print();
        break;
      case 3:
        cout << "Square is: " << LilB.Square() << endl;
        break;
      default:
        break;
      };
    }
      break;
    default:
      break;
    };
  }
  while (opt != 4);
  cout << "Bye!" << endl;
  
  return 0;
}

