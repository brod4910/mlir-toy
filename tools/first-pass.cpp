#include "lib/Transform/Affine/AffineFullUnroll.h"
#include "lib/Transform/Arith/MulToAdd.h"
#include "mlir/InitAllDialects.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  mlir::registerAllDialects(registry);

  mlir::PassRegistration<mlir::luna::AffineFullUnrollPass>();
  mlir::PassRegistration<mlir::luna::AffineFullUnrollPassAsPatternRewrite>();
  mlir::PassRegistration<mlir::luna::MulToAddPass>();

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Tutorial Pass Driver", registry));
}