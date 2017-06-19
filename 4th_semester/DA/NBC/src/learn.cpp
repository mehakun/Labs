#include "../incl/nbc.h"
#include "../incl/ttag.h"
#include "../incl/util.h"
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <iostream>
#include <cctype>

namespace NNBC {
    namespace NLearnUtil {
        void
        AddToUnique(std::string &word,
                    std::unordered_map<std::string, std::uint32_t> &wordsCounter,
                    std::unordered_set<std::string> &uniqueWords)
        {
            ++wordsCounter[word];
            uniqueWords.emplace(std::move(word));
            word.clear();
        }

        void
        AddWords(const std::string &line,
                 std::unordered_map<std::string, std::uint32_t> &wordsCounter,
                 std::unordered_set<std::string> &uniqueWords,
                 size_t &amountOfWordsInArt)
        {
            std::string tmp{};

            for (size_t i = 0; i < line.size(); ++i) {
                if (std::isalpha(line[i])) {
                    tmp += std::tolower(line[i]);
                } else if (!tmp.empty()) {
                    AddToUnique(tmp, wordsCounter, uniqueWords);
                    ++amountOfWordsInArt;
                } 
            }

            if (!tmp.empty()) {
                AddToUnique(tmp, wordsCounter, uniqueWords);
                ++amountOfWordsInArt;
            } 

        }

        void
        AddTag(const std::unordered_map<std::string, std::uint32_t> &wordsCounter,
               const size_t amountOfWordsInArt, const std::string &tagName,
               std::unordered_map<std::string, TTag> &tags)
        {
            auto iter = tags.try_emplace(tagName, amountOfWordsInArt, 1, wordsCounter); 

            if (iter.second == false) {
                ++iter.first->second.amountOfMentions;
                iter.first->second.amountOfWords += amountOfWordsInArt;
        
                for (const auto &node : wordsCounter) {
                    auto tmp = iter.first->second.wordsCount.try_emplace(node.first, node.second);

                    if (tmp.second == false) {
                        tmp.first->second += node.second;
                    } 
                }
            }
        }

        void
        LearnIn(std::ifstream &input,
                std::unordered_map<std::string, TTag> &tags,
                std::unordered_set<std::string> &uniqueWords)
        {
            size_t amountOfLines;
            input >> amountOfLines;
            input.get();
            std::string line;
            std::unordered_map<std::string, std::uint32_t> wordsCounter;
            size_t amountOfWordsInArt = 0;

            for (size_t currLine = 0; currLine < amountOfLines; ++currLine) {
                std::getline(input, line);
                AddWords(line, wordsCounter, uniqueWords, amountOfWordsInArt);
            }
    
            std::getline(input, line);
            auto tagsVec{NUtil::Split(line, ',')};

            for (const auto &tag : tagsVec) {
                AddTag(wordsCounter, amountOfWordsInArt, tag, tags);
            }

        }

        void
        LearnOut(std::ofstream &output, const size_t amountOfArt,
                 std::unordered_map<std::string, TTag> &tags,
                 const size_t uniqueSize)
        {
            output << amountOfArt << ' ' << uniqueSize << ' ' << tags.size() << '\n';

            for (const auto &tag : tags) {
                output << tag.first << '\n' << tag.second.amountOfMentions << '\n' << tag.second.amountOfWords <<
                    '\n' << tag.second.wordsCount.size() << '\n';

                for (const auto &word : tag.second.wordsCount) {
                    output << word.first << ' ' << word.second << '\n';
                }   
            }
        }        
    } // end of learn utility namespace
    
    void
    Learn(std::ifstream &inStream, std::ofstream &outStream)
    {
        size_t articlesCount = 0;
        std::unordered_map<std::string, TTag> tags;
        std::unordered_set<std::string> uniqueWords;
        
        while (inStream.peek() != EOF) {
            NLearnUtil::LearnIn(inStream, tags, uniqueWords);
            ++articlesCount;
        }

        NLearnUtil::LearnOut(outStream, articlesCount, tags, uniqueWords.size());
    }

} // end of NBC namespace
