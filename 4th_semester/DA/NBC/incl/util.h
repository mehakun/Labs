#include <string>
#include <vector>
#include "nbc.h"

namespace NNBC {
    namespace NUtil {    
        inline std::vector<std::string>
            Split(const std::string &line, const char delim)
        {
            std::vector<std::string> vec;
            size_t start = 0;
            auto end = line.find(delim);
            
            while (end != std::string::npos) {
                vec.emplace_back(line.substr(start, end - start));
                start = end + 1;
                end = line.find(delim, start);
            }

            vec.emplace_back(line.substr(start, end - start));
            
            return vec;
        }

    }
}
