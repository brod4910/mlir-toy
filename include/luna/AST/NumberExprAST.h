/// NumberExprAST - Expression class for numeric literals like "1.0".
#pragma once

#include <llvm/IR/Value.h>

#include "luna/AST/ExprAST.h"


class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}

  llvm::Value *codegen() override;
};