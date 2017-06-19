#include <iostream>
#include <fstream> 
#include <cstring>
#include "incl/nbc.h"

static const char * const args[] = {
    "learn", "--input",
    "--output", "classify", "--stats"
};
static const int LEARN_ARGS_COUNT = 6;
static const int CLASFY_ARGS_COUNT = 8;

    
void Helper();
bool ParseArgv(char *argv[], const int, char*[]);

int
main(int argc, char *argv[])
{   
    char *filePaths[] = {nullptr, nullptr, nullptr};
    
    if (ParseArgv(argv, argc, filePaths) == false) {
        Helper();
        return 0;
    }

    std::ifstream input(filePaths[0]);
    std::ofstream output(filePaths[1]);
    
    if (filePaths[2] != nullptr) {
        std::ifstream stats(filePaths[2]);
        NNBC::Classify(stats, input, output);
        
        return 0;
    }
        
    NNBC::Learn(input, output);
    
    return 0;
}

void
Helper()
{
    std::cout << "usage:\n" <<
        "./prog learn --input <input file> --output <stats file>\n" <<
        "./prog classify --stats <stats file> --input <input file> --output <output file>" <<
        std::endl;
}

bool
ParseArgv(char *argv[], const int argCount, char *res[])
{
    std::uint8_t validArgs = 0;
    
    if (strcmp(argv[1], args[0]) == 0) {
        for (size_t i = 1; i < LEARN_ARGS_COUNT; ++i) {
            if (strcmp(argv[i], args[1]) == 0) {
                res[0] = argv[i + 1];
                ++i;
                ++validArgs;
                
            } else if (strcmp(argv[i], args[2]) == 0) {
                res[1] = argv[i + 1];
                ++i;
                ++validArgs;
            } 
        }

        return validArgs == 2 && argCount == LEARN_ARGS_COUNT;
    } else if (strcmp(argv[1], args[3]) == 0) {
        for (size_t i = 1; i < CLASFY_ARGS_COUNT; ++i) {
            if (strcmp(argv[i], args[1]) == 0) {
                res[0] = argv[i + 1];
                ++i;
                ++validArgs;
            } else if (strcmp(argv[i], args[2]) == 0) {
                res[1] = argv[i + 1];
                ++i;
                ++validArgs;
            } else if (strcmp(argv[i], args[4]) == 0) {
                res[2] = argv[i + 1];
                ++i;
                ++validArgs;                
            }
        }

        return validArgs == 3 && argCount == CLASFY_ARGS_COUNT;
    }

    return false;
}
