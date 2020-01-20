#ifndef __CONST_EXPR_CPP
#define __CONST_EXPR_CPP

#include "abstract_expression.h"

#include <vector>
#include <string>

class ConstExpr : public AbstractExpr {
    private:
        int value;
        const std::string tag = "Numerical";
    public:
        ConstExpr(int value) {
            this->value = value;
        }

        std::vector<int> calculate() {
            return std::vector<int> {value};
        }

        void addChild(AbstractExpr* expr) {
            return;
        }

        std::string getTag() {
            return tag;
        }
};

#endif