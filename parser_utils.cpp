#ifndef __PARSER_UTILS_CPP
#define __PARSER_UTILS_CPP

//#include <vector>
//#include <unordered_map>
//#include <functional>
//#include <algorithm>
#include "utils.cpp"
#include "abstract_expression.h"
#include "map_expr.h"
#include "aggr_expr.h"
#include "sort_expr.h"

class ParseUtils {
    private:
        static std::string extractParam(const std::string& expr) {
            std::string param = std::string();
            int index = expr.find("\"");
            if (index == -1)
                return param;
            std::string::const_iterator it = expr.begin() + index + 1;
            while (it != expr.end() && (*it) != '"') {
                param += (*it);
                ++it;  
            }
            return param;
        }           
    public:
        static AbstractExpr* extractCommand(const std::string& expr) {
            std::string command = expr.substr(1, 3);
            std::string option = expr.substr(5, 3); //This is INC in MAP-INC or AVG in AGG-AVG
            if (command == "MAP" &&
                (option == "INC" ||
                 option == "MLT")) {
                std::string param = extractParam(expr);
                bool isNegative = false;
                if (param[0] == '-') {
                    isNegative = true;
                    param = param.substr(1);
                }
                if (!Utils::is_number(param)) {
                    throw new std::invalid_argument("MAP functions only support numerical parameters");
                }
                if (isNegative){
                    param = '-' + param;
                }
                return new MapExpr(command, option, param);
            } else if (command  == "AGG" && 
                        (option == "AVG" || 
                         option == "PRO" ||
                         option == "SUM" ||
                         option == "FST" ||
                         option == "LST")) {
                return new AggrExpr(command, option);
            } else if (command == "SRT" && 
                       (option == "ORD" ||
                        option == "REV" ||
                        option == "SLC" ||
                        option == "DST")) {
                std::string param = extractParam(expr);
                if (option == "ORD" && param != "ASC" && param != "DSC") {
                    throw new std::invalid_argument("SRT-ORD functions only support ASC or DSC as parameters");
                } else if (option == "SLC" && !Utils::is_number(param)) {
                    throw new std::invalid_argument("SRT-SLC functions only support numerical parameters");
                }
                return new SortExpr(command, option, param);
            } else {
                throw new std::invalid_argument("Wrong name/format of the tag");
            }
        }

        static void normalizeCommand(std::string& command) {
            Utils::tokenize(command, ">", "> ");
            Utils::tokenize(command, "<", " <");
            Utils::tokenize(command, " \"", "-\"");
        }
};

#endif