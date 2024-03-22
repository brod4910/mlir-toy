#include "lib/Dialect/Poly/PolyDialect.h"
#include "lib/Transform/AffineTD/Passes.h"
#include "lib/Transform/ArithTD/Passes.h"
#include "mlir/InitAllDialects.h"
#include "mlir/InitAllPasses.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Pass/PassRegistry.h"
#include "mlir/Tools/mlir-opt/MlirOptMain.h"

int main(int argc, char **argv) {
  mlir::DialectRegistry registry;
  registry.insert<mlir::toy::poly::PolyDialect>();
  mlir::registerAllDialects(registry);
  mlir::registerAllPasses();

  mlir::toy::registerAffinePasses();
  mlir::toy::registerArithPasses();

  return mlir::asMainReturnCode(
      mlir::MlirOptMain(argc, argv, "Tutorial Pass Driver", registry));
}