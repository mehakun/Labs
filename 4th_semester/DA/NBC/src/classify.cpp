#include "../incl/nbc.h"
#include "../incl/ttag.h"
#include "../incl/util.h"
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cmath>
#include <cctype>
#include <functional>

namespace NNBC {
    namespace NClassUtil {
        static const long double COEFF = 0.93;
        
        std::pair<size_t, size_t>
        ReadStats(std::ifstream &statStream,
                  std::unordered_map<std::string, TTag> &tags)
        {
            size_t amountOfArt, amountOfUniqueWords, amountOfTags;
            statStream >> amountOfArt >> amountOfUniqueWords >> amountOfTags;

            for (size_t i = 0; i < amountOfTags; ++i) {
                std::string tagName;
                std::uint32_t mentions, words;
                size_t amountOfUniWords;
                statStream >> tagName >> mentions >> words >> amountOfUniWords;
                TTag tag(words, mentions);

                for (size_t j = 0; j < amountOfUniWords; ++j) {
                    std::string word;
                    std::uint32_t count;

                    statStream >> word >> count;
                    tag.wordsCount.emplace(std::move(word), std::move(count));
                }

                tags.emplace(std::move(tagName), std::move(tag));
            }

            return std::make_pair(amountOfArt, amountOfUniqueWords);
        }

        void
        AddToCounter(std::string &word,
                     std::unordered_map<std::string, std::uint32_t> &wordsInArticle)
        {
            ++wordsInArticle[std::move(word)];
            word.clear();
        }
    
        void
        AddWords(const std::string &line,
                 std::unordered_map<std::string, std::uint32_t> &wordsInArticle)
        {
            std::string tmp{};
            
            for (size_t i = 0; i < line.size(); ++i) {
                if (std::isalpha(line[i])) {
                    tmp += std::tolower(line[i]);
                } else if (!tmp.empty()){
                    AddToCounter(tmp, wordsInArticle);
                }
            }

            if (!tmp.empty()) {
                AddToCounter(tmp, wordsInArticle);
            }
        }
    
        size_t
        ReadFileToClassify(std::ifstream &classStream,
                           std::unordered_map<std::string, std::uint32_t> &wordsInArticle)
        {
            size_t amountOfLines;
            classStream >> amountOfLines;
            std::string line;
            size_t currLine = 0;
            classStream.get();

            for (; currLine < amountOfLines; ++currLine) {
                std::getline(classStream, line);

                AddWords(line, wordsInArticle);
            }
            
            return currLine;
        }

        std::vector<std::pair<std::string, long double>>
        ValidateTags(std::unordered_map<std::string, TTag> &tags,
                     std::unordered_map<std::string, std::uint32_t> &wordsInArticle,
                     const size_t amountOfArts, const size_t amountOfUniqueWords)
        {
            std::vector<std::pair<std::string, long double>> res;

            for (const auto &tag : tags) {
                long double result = std::log(static_cast<long double>(tag.second.amountOfMentions) / amountOfArts);
                std::uint32_t divisor = amountOfUniqueWords + tag.second.amountOfWords;
                long double valIfNotFound = std::log(1. / divisor);

                for (const auto &word : wordsInArticle) {
                    auto wordInTag = tag.second.wordsCount.find(word.first);
                    
                    if (wordInTag != tag.second.wordsCount.end()) {
                        result += std::log(static_cast<long double>(wordInTag->second + 1) / divisor) * word.second;
                    } else {
                        result += valIfNotFound * word.second;
                    }
                }

                res.emplace_back(tag.first, result);
            }

            std::sort(res.begin(), res.end(), [](const auto& a, const auto& b){
                    return a.second > b.second;
                });
            
            return res;
        }
    } // end of classify utility namespace

    void
    Classify(std::ifstream &stats, std::ifstream &input, std::ofstream &output)
    {
        std::unordered_map<std::string, TTag> tags;
        auto amountOfArtsAndUniq{NClassUtil::ReadStats(stats, tags)};

        while (input.peek() != EOF) {
            std::unordered_map<std::string, std::uint32_t> wordsInArticle;
            NClassUtil::ReadFileToClassify(input, wordsInArticle);
            auto validatedTags = NClassUtil::ValidateTags(tags, wordsInArticle,
                                                          amountOfArtsAndUniq.first,
                                                          amountOfArtsAndUniq.second);
            output << validatedTags[0].first;

            for (size_t i = 1; i < validatedTags.size(); ++i) {
                long double currCoeff = validatedTags[i - 1].second / validatedTags[i].second;
                
                if (currCoeff <= NClassUtil::COEFF || currCoeff == 1) {
                    output << ',' << validatedTags[i].first;
                } else {
                    break;
                }
            }

            output << '\n';
        }
    }
    
} // end of NBC namespace
