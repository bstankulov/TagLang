#ifndef __LET_EXPR_H
#define __LET_EXPR_H

#include "abstract_expression.h"

class LetExpr : public AbstractExpr {
    private:
        std::string tag;
        std::string name;
        std::vector<int> nameValue;
        std::vector<AbstractExpr*> children;
    public:
        LetExpr(const std::string& tag, 
                 const std::string& option);

        void addChild(AbstractExpr* expr);

        std::vector<int> calculate();

        void setName();

        std::string getTag();

        std::string getName();

        const std::vector<int>& getChildren() const;

        bool hasChildren() const;

        ~LetExpr();
};

#endif
