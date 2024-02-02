#pragma once

#include <string>

#include <llvm/IR/Value.h>

#include "luna/AST/ExprAST.h"


class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}

  Value *codegen() override;
  const std::string &getName() const { return Name; }
};

