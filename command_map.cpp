#ifndef __COMMAND_MAP_CPP
#define __COMMAND_MAP_CPP

#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <string>
#include "utils.cpp"

class CommandMap {
    private:
        inline static std::unordered_map<std::string, 
                                         std::function<void(std::vector<int>&, 
                                                       std::string, std::string)>
                                        > commands;
        inline static bool isInit = false;
    public:
        static bool isInitialized() {
            return isInit;
        }
        static void initCommander() {
            isInit = true;
            commands["MAP"] = Utils::map;
            commands["AGG"] = Utils::aggregate;
            commands["SRT"] = Utils::sort;
        }
        static void execute(std::vector<int>& input, 
                            std::string       command,
                            std::string       option) {
            if (!isInit) {
                std::cout << "Must call initializer of the commander!" << std::endl;
                throw new std::invalid_argument("Please initialize the commander by calling {CommandMap::initCommander()}");
            }
            commands[command](input, option, std::string());
        }
        //const function, also the input reference would be nice if const
        static void execute(std::vector<int>& input, 
                            std::string       command,
                            std::string       option,
                            std::string       params) {
            if (!isInit) {
                std::cout << "Must call initializer of the commander!" << std::endl;
                throw new std::invalid_argument("Please initialize the commander by calling {CommandMap::initCommander()}");
            }
            commands[command](input, option, params);
        }
};

#endif