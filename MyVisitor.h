#pragma once
#include "CParserBaseVisitor.h"
using namespace antlrcpptest;

class MyVisitor : public antlrcpptest::CParserBaseVisitor
{
public:
    MyVisitor() {}
    virtual ~MyVisitor() {}

    std::any visitProg(CParser::ProgContext *ctx) override {
        return visit(ctx->expr());
    }

    std::any visitFactor(CParser::FactorContext *ctx) override {
        int left = std::any_cast<int>(visit( ctx->expr()[0] ));
        int right = std::any_cast<int>(visit( ctx->expr()[1] ));
        if(ctx->Star()){
            return left * right;
        }else{
            return left / right;
        }
    }

    std::any visitTerm(CParser::TermContext *ctx) override {
        std::any ret;
        int left = std::any_cast<int>(visit( ctx->expr()[0] ));
        int right = std::any_cast<int>(visit( ctx->expr()[1] ));
        if(ctx->Plus()){
            ret = left + right;
        }else{
            ret = left - right;
        }
        return ret;
    }

    virtual std::any visitParen(CParser::ParenContext *ctx) override {
        return visit(ctx->expr());
    }

    virtual std::any visitNum(CParser::NumContext *ctx) override {
        std::any ret = atoi(ctx->getText().c_str());
        return ret;
    }

private:
    int result;

};
