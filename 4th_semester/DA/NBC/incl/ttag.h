#ifndef _TTAG_H
#define _TTAG_H
#include <string>
#include <unordered_map>

struct TTag {
TTag(const std::uint32_t amount,
     const std::uint32_t mentions,
     const std::unordered_map<std::string, std::uint32_t> &dict):
    amountOfWords(amount), amountOfMentions(mentions), wordsCount(dict) {}
    
TTag(const std::uint32_t amount,
     const std::uint32_t mentions):
    amountOfWords(amount), amountOfMentions(mentions) {};

    TTag(TTag &&other) = default;
    
    std::uint32_t amountOfWords;
    std::uint32_t amountOfMentions;
    std::unordered_map<std::string, std::uint32_t> wordsCount;
};

#endif
