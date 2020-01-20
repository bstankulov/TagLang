#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <sstream>
#include <stack>
#include "utils.cpp"
#include "parser_utils.cpp"
#include "command_map.cpp"
#include "abstract_expression.h"
#include "aggr_expr.h"
#include "map_expr.h"
#include "sort_expr.h"
#include "const_expr.cpp"
#define OUTPUT_FILE "output.txt"

void evaluateInputLine(AbstractExpr*& rootNode);
AbstractExpr* parseCommand(const std::string& command);
std::vector<std::string> getCommand();
void printProgramOutput(const std::vector<int>& lineResult);

int main() {    
    std::vector<std::string> IMLProgram = getCommand();// Getting the IML tag lines
    for (std::string line : IMLProgram) {
        AbstractExpr* rootNode = parseCommand(line); // Parsing it and creating the Abstract Syntax Tree (AST) 
        evaluateInputLine(rootNode); // Evaluating the AST
    } 
    std::cout << "Program finished successfully. Closing...\n";
}

std::vector<std::string> getCommand() {
    std::ifstream reader;
    std::string   file;

    std::cout << "Please enter input file: "; std::cin >> file;
    reader.open(file);

    std::string              command;
    std::vector<std::string> lines;

    while (getline(reader, command)) {
        ParseUtils::normalizeCommand(command);
        lines.push_back(command);
    }

    reader.close();
    return lines;
}

void printProgramOutput(const std::vector<int>& lineResult) {
    std::ofstream outputFile;
    /*
    std::string   out_file;
    std::cout << "Please enter output file: "; std::cin >> out_file;
    outputFile.open(out_file, std::ios_base::app);
    */
    outputFile.open(OUTPUT_FILE, std::ios_base::app);
    for (int value : lineResult) {
        outputFile << value << " ";
    }
    outputFile << '\n';
    outputFile.close();
    std::cout << "Written successfully in the output file.\n";
}

void evaluateInputLine(AbstractExpr*& rootNode) {
    CommandMap::initCommander();
    std::vector<int> result = rootNode->calculate();
    printProgramOutput(result);
}

AbstractExpr* parseCommand(const std::string& command) {
    std::istringstream parser(command);
    std::string word;
    std::stack <AbstractExpr*> functionalExpressionStack;
    AbstractExpr* rootNode;
    while (parser >> word) {
        AbstractExpr* expression = nullptr;
        if (word[0] == '<') {
            //Check if the tag is closing
            if (word[word.size() - 1] == '>' && word[1] == '/') {
                //Check if the closing tag is the opening one, so parsing can finish
                if (functionalExpressionStack.size() == 1) {
                    rootNode = functionalExpressionStack.top();
                    functionalExpressionStack.pop();
                    //std::cout << "Removed the opening tag "<< rootNode->getTag() << "\nParsed successfully, calculating..." << std::endl;
                    break;
                }
            //std::cout << "Removing from the stack: " << functionalExpressionStack.top()->getTag() << std::endl;
            functionalExpressionStack.pop();
            } else {
                //In this else sits the logic, that handles the opening tag
                expression = ParseUtils::extractCommand(word);
                if (functionalExpressionStack.size() > 0) {
                    functionalExpressionStack.top()->addChild(expression);
                }
                //std::cout << "Adding " << expression->getTag() << " to the stack" << std::endl;
                functionalExpressionStack.push(expression);
            }
        } else if (Utils::is_number(word)){
            expression = new ConstExpr(std::stoi(word));
            functionalExpressionStack.top()->addChild(expression);
        } else {
            throw new std::invalid_argument("Invalid command format");
        }
    }
    return rootNode;
}