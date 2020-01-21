#include "let_expr.h"
#include "command_map.cpp"

LetExpr::LetExpr(const std::string& tag, 
                 const std::string& name) {
    this->tag = tag;
    this->name = name;
}

void LetExpr::addChild(AbstractExpr* expr) {
    children.push_back(expr);
}

std::vector<int> LetExpr::calculate() {
    std::vector<int> result;
    for (AbstractExpr* child : children) {
        std::vector<int> childResult = child->calculate();
        result.insert(result.end(), 
                      childResult.begin(), 
                      childResult.end());
    }
    return result;
}

// used just for the convinient naming in the code, it basically is
// calculate with the children so far
void LetExpr::setName() {
    CommandMap::initCommander();
    nameValue = this->calculate();
    children.clear(); // clear all current children
}

std::string LetExpr::getTag() {
    return tag;
}

std::string LetExpr::getName() {
    return name;
}

const std::vector<int>& LetExpr::getChildren() const {
    return nameValue;
}

bool LetExpr::hasChildren() const {
    return !(children.empty());
}

LetExpr::~LetExpr() {
    for (AbstractExpr* expr : children) {
        delete expr;
    }
}