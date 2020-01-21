#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <sstream>
#include <stack>
#include <string>
#include "logger.h"
#include "utils.cpp"
#include "parser_utils.cpp"
#include "command_map.cpp"
#include "abstract_expression.h"
#include "aggr_expr.h"
#include "map_expr.h"
#include "sort_expr.h"
#include "let_expr.h"
#include "const_expr.cpp"
#define OUTPUT_FILE "output.txt"

void evaluateInputLine(AbstractExpr*& rootNode);
AbstractExpr* buildAbstractSyntaxTree(const std::string& command);
std::vector<std::string> getCommand();
void printProgramOutput(const std::vector<int>& lineResult);

int main() {    
    std::vector<std::string> IMLProgram = getCommand();// Getting the IML tag lines
    for (std::string line : IMLProgram) {
        AbstractExpr* rootNode = buildAbstractSyntaxTree(line); // Parsing it and creating the Abstract Syntax Tree (AST) 
        evaluateInputLine(rootNode); // Evaluating the AST
    } 
    Logger::Log(std::cout, "Program finished successfully. Closing...");
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
    Logger::Log(std::cout, "Written successfully in the output file.");
}

void evaluateInputLine(AbstractExpr*& rootNode) {
    CommandMap::initCommander();
    std::vector<int> result = rootNode->calculate();
    printProgramOutput(result);
}

AbstractExpr* buildAbstractSyntaxTree(const std::string& command) {
    std::istringstream parser(command);
    std::string word;
    std::stack <AbstractExpr*> functionalExpressionStack;
    AbstractExpr* rootNode;
    std::stack <LetExpr*> latestLetTags;
    while (parser >> word) {
        AbstractExpr* expression = nullptr;
        if (word[0] == '<') {
            //Check if the tag is closing
            if (word[word.size() - 1] == '>' && word[1] == '/') {
                //Check if the closing tag is the opening one, so parsing can finish
                if (functionalExpressionStack.top()->getTag() == "LET")
                    latestLetTags.pop();
                if (functionalExpressionStack.size() == 1) {
                    rootNode = functionalExpressionStack.top();
                    functionalExpressionStack.pop();
                    Logger::Log(std::cout, "Parsed successfully, calculating...");
                    break;
                }
            functionalExpressionStack.pop();
            } else if (word == "<BODY/>") {
                LetExpr* let = dynamic_cast<LetExpr*> (functionalExpressionStack.top());
                if ( !let )
                    Logger::Error("The body tag should enclose the first part of the LET tag definition");

                if( !(let->hasChildren()) )
                    Logger::Error("Duplicating BODY tag or empty definition of LET first part. The BODY tag should only be used to close the first part of LET tag.");

                let->setName(); // Should set the commander
            } else {
                //In this else sits the logic, that handles the opening tag
                expression = ParseUtils::extractCommand(word);
                if (expression->getTag() == "LET")
                    latestLetTags.push(dynamic_cast<LetExpr*>(expression));
                if (functionalExpressionStack.size() > 0)
                    functionalExpressionStack.top()->addChild(expression);
                //std::cout << "Adding " << expression->getTag() << " to the stack" << std::endl;
                functionalExpressionStack.push(expression);
            }
        } else if (Utils::is_number(word)){
            expression = new ConstExpr(std::stoi(word));
            functionalExpressionStack.top()->addChild(expression);
        } else if (latestLetTags.top()->getName() == word) {
            //Handling the LET Name parsing
            AbstractExpr* currentTopExpression = functionalExpressionStack.top();
            for  (int el : latestLetTags.top()->getChildren()) {
                currentTopExpression->addChild(new ConstExpr(el));
            }
        } else {
            Logger::Error("Invalid command format: Could be only an opening/closing tag; numerical value or let tag name");
        }
    }
    return rootNode;
}