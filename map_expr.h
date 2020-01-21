#ifndef __MAP_EXPR_H
#define __MAP_EXPR_H

#include "abstract_expression.h"

class MapExpr : public AbstractExpr {
    private:
        std::string tag;
        std::string option;
        std::string param;
        std::vector<AbstractExpr*> children;
    public:
        MapExpr(const std::string& tag, 
                const std::string& option, 
                const std::string& param);

        void addChild(AbstractExpr* expr);

        std::vector<int> calculate();

        std::string getTag();

        ~MapExpr();
};

#endif
