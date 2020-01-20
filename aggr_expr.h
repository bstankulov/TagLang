#ifndef __AGGR_EXPR_H
#define __AGGR_EXPR_H

#include "abstract_expression.h"

class AggrExpr : public AbstractExpr {
    private:
        std::string tag;
        std::string option;
        std::vector<AbstractExpr*> children;
    public:
        AggrExpr(const std::string& tag, 
                 const std::string& option);

        void addChild(AbstractExpr* expr);

        std::vector<int> calculate();

        std::string getTag();

        ~AggrExpr();
};

#endif
