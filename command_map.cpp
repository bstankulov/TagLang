#ifndef __COMMAND_MAP_CPP
#define __COMMAND_MAP_CPP

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
            if (!isInit) {
                isInit = true;
                commands["MAP"] = Utils::map;
                commands["AGG"] = Utils::aggregate;
                commands["SRT"] = Utils::sort;
            }
        }
        static void execute(std::vector<int>& input, 
                            std::string       command,
                            std::string       option) {
            execute(input, command, option, std::string());
        }
        //const function, also the input reference would be nice if const
        static void execute(std::vector<int>& input, 
                            std::string       command,
                            std::string       option,
                            std::string       params) {
            if (!isInit)
                Logger::Error("Must call initializer of the commander!\nPlease initialize the commander by calling {CommandMap::initCommander()}");
            commands[command](input, option, params);
        }
};

#endif