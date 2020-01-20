#include "aggr_expr.h"
#include "command_map.cpp"

AggrExpr::AggrExpr(const std::string& tag, 
                   const std::string& option) {
    this->tag = tag;
    this->option = option;
}

void AggrExpr::addChild(AbstractExpr* expr) {
    children.push_back(expr);
}

std::vector<int> AggrExpr::calculate() {
    std::vector<int> result;
    for (AbstractExpr* child : children) {
        std::vector<int> childResult = child->calculate();
        result.insert(result.end(), 
                      childResult.begin(), 
                      childResult.end());
    }
    CommandMap::execute(result, tag, option);
    return result;
}

std::string AggrExpr::getTag() {
    return tag;
}

AggrExpr::~AggrExpr() {
    for (AbstractExpr* expr : children) {
        delete expr;
    }
}