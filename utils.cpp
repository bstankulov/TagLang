#ifndef __UTILS_CPP
#define __UTILS_CPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

enum string_code {
    SUM,
    PRO,
    AVG,
    FIRST,
    LAST,
    UNK
};

class Utils
{
    private:
        static string_code hashit (std::string const& inString) {
            if (inString == "SUM") return SUM;
            if (inString == "PRO") return PRO;
            if (inString == "AVG") return AVG;
            if (inString == "FST") return FIRST;
            if (inString == "LST") return LAST;
            return UNK;
        }           
    public:
        static void tokenize(std::string& command, 
                             std::string oldString, 
                             std::string replacementString) {
            size_t index = 1,
            oldLength = oldString.size(),
            newLength = replacementString.size();
            while (true) {
                index = command.find(oldString, index);
                if (index == std::string::npos) break;
                command.replace(index, oldLength, replacementString);
                index += newLength;
            }
        }
        
        static bool is_number(const std::string& word) {
            std::string::const_iterator it = word.begin();
            while (it != word.end() && std::isdigit(*it))
                ++it;
            return it == word.end();
        }

        static void map(std::vector<int>& input, 
                        std::string       option, 
                        std::string       params) { 
            int inc = std::stoi(params);
            if (option == "MLT") {
                for (int& value : input) {
                    value *= inc;
                }
            } else if (option == "INC") {
                for (int& value : input) {
                    value += inc;
                }
            }
            
        }

        static void distinct(std::vector<int>& input) {
            std::unordered_map<int, int> counts;
            for (int el : input) ++counts[el];
            for (int i = input.size() - 1; i >= 0; --i) {
                int num = input[i]; // if i use counts[input[i]] hell goes loose ????
                if (counts[num] != 1) {
                    input.erase(input.begin() + i);
                    --counts[num];
                }
            }
        }

        static void aggregate(std::vector<int>& input, 
                              std::string       typeOfAggregation, 
                              std::string       params = std::string()) { 
            //The switch is written in such manner in order to use the switch - case syntax for strings
            switch(hashit(typeOfAggregation)) {
                case SUM:
                {
                    int sum = 0;
                    for (int value : input) {
                        sum += value;
                    }
                    input[0] = sum;
                    break;
                }        
                case PRO:
                {
                    int product = 1;
                    for (int value : input) {
                        product *= value;
                    }
                    input[0] = product;
                    break;
                }         
                case AVG:
                {
                    int sum = 0;
                    int count = 0;
                    for (int value : input) {
                        sum += value;
                        ++count;
                    }
                    input[0] = sum / count;
                    break;
                } 
                case FIRST:
                {
                    break;
                }
                case LAST:
                {
                    input[0] = input.back();
                    break;
                }
                default:
                    throw new std::invalid_argument("Invalid Aggregation function in hashtag");
            }
            input.erase(input.begin() + 1, input.end());
        }

        static void sort(std::vector<int>& input, 
                         std::string       option, 
                         std::string       params = std::string()) {
            if (option == "REV") {
                if (params != "") {
                    throw new std::invalid_argument("There shouldn't be parameter of any type if you want to just reverse the list");
                }
                std::reverse(input.begin(), input.end());
            } else if (option == "ORD") {
                if (params == "ASC") {
                    std::sort(input.begin(), input.end());
                } else if (params == "DSC") {
                    std::sort(input.rbegin(), input.rend());
                } else {
                    throw new std::invalid_argument("There shouldn't be parameter of any type if you want to just reverse the list");
                }
            } else if (option == "DST") {
                if (params != "") {
                    throw new std::invalid_argument("There shouldn't be parameter of any type if you want to just reverse the list");
                }
                //Removing duplicates:
                distinct(input);
            } else if (option == "SLC") {
                if (!Utils::is_number(params)) {
                    throw new std::invalid_argument("Parameter should be a number");
                }
                int slice = std::stoi(params) % input.size();
                input.erase(input.begin(), input.begin() + slice);
            } else {
                throw new std::invalid_argument("Sorting option can only be two values: REV or ORD");
            }
        }
};

#endif