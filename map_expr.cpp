#include "map_expr.h"
#include "command_map.cpp"

MapExpr::MapExpr(const std::string& tag, 
                 const std::string& option, 
                 const std::string& param) {
    this->tag = tag;
    this->option = option;
    this->param = param;
}

void MapExpr::addChild(AbstractExpr* expr) {
    children.push_back(expr);
}

std::vector<int> MapExpr::calculate() {
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

std::string MapExpr::getTag() {
    return tag;
}

MapExpr::~MapExpr() {
    for (AbstractExpr* expr : children) {
        delete expr;
    }
}