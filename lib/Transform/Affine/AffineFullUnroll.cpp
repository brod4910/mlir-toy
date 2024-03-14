#include "lib/Transform/Affine/AffineFullUnroll.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Pass/Pass.h"

namespace mlir::luna {
void AffineFullUnrollPass::runOnOperation() {
  getOperation().walk([&](mlir::affine::AffineForOp op) {
    if (failed(mlir::affine::loopUnrollFull(op))) {
      op.emitError("unrolling failed");
      signalPassFailure();
    }
  });
}
} // namespace mlir::luna