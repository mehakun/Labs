#ifndef _NBC_H
#define _NBC_H
#include <fstream>

namespace NNBC {
    void Classify(std::ifstream&, std::ifstream&, std::ofstream&);
    void Learn(std::ifstream&, std::ofstream&);
}

#endif
