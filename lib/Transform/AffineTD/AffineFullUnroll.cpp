#include "lib/Transform/AffineTD/AffineFullUnroll.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/Pass/Pass.h"

namespace mlir::luna {
#define GEN_PASS_DEF_AFFINEFULLUNROLL
#include "lib/Transform/AffineTD/Passes.h.inc"

using mlir::affine::AffineForOp;
using mlir::affine::loopUnrollFull;

// A pass that manually walks the IR
struct AffineFullUnroll : impl::AffineFullUnrollBase<AffineFullUnroll> {
  using AffineFullUnrollBase::AffineFullUnrollBase;

  void runOnOperation() {
    getOperation()->walk([&](AffineForOp op) {
      if (failed(loopUnrollFull(op))) {
        op.emitError("unrolling failed");
        signalPassFailure();
      }
    });
  }
};
} // namespace mlir::luna