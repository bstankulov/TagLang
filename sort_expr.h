#ifndef __SORT_EXPR_H
#define __SORT_EXPR_H

#include "abstract_expression.h"
#include <iostream>

class SortExpr : public AbstractExpr {
    private:
        std::string tag;
        std::string option;
        std::string param;
        std::vector<AbstractExpr*> children;
    public:
        SortExpr(const std::string& tag, 
                 const std::string& option, 
                 const std::string& param);

        void addChild(AbstractExpr* expr);

        std::vector<int> calculate();

        std::string getTag();

        ~SortExpr();
};

#endif
