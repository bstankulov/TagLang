#ifndef __ABSTRACT_EXPRESSION_H
#define __ABSTRACT_EXPRESSION_H

#include <vector>
#include <string>

class AbstractExpr {
public:
    virtual ~AbstractExpr() { }
    virtual std::vector<int> calculate() = 0;
    virtual void addChild(AbstractExpr* expr) = 0;
    virtual std::string getTag() = 0;
};

#endif