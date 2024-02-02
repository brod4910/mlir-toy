#pragma once

#include <memory>
#include <string>

#include <llvm/IR/Value.h>

#include "luna/AST/ExprAST.h"


/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}

  llvm::Value *codegen() override;
};