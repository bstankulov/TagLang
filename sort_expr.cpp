#include <iostream>
#include "sort_expr.h"
#include "command_map.cpp"

SortExpr::SortExpr(const std::string& tag, 
                const std::string& option, 
                const std::string& param) {
    this->tag = tag;
    this->option = option;
    this->param = param;
}

void SortExpr::addChild(AbstractExpr* expr) {
    children.push_back(expr);
}

std::vector<int> SortExpr::calculate() {
    std::vector<int> result;
    for (AbstractExpr* child : children) {
        std::vector<int> childResult = child->calculate();
        result.insert(result.end(), 
                      childResult.begin(), 
                      childResult.end());
    }
    CommandMap::execute(result, tag, option, param);
    return result;
}

std::string SortExpr::getTag() {
    return tag;
}

SortExpr::~SortExpr() {
    for (AbstractExpr* expr : children) {
        delete expr;
    }
}