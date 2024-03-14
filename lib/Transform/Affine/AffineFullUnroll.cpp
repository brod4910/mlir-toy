#include "lib/Transform/Affine/AffineFullUnroll.h"

#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::luna {
void AffineFullUnrollPass::runOnOperation() {
  getOperation().walk([&](mlir::affine::AffineForOp op) {
    if (failed(mlir::affine::loopUnrollFull(op))) {
      op.emitError("unrolling failed");
      signalPassFailure();
    }
  });
}

// A pattern that matches on AffineForOp and unrolls it.
struct AffineFullUnrollPattern : public OpRewritePattern<affine::AffineForOp> {
  AffineFullUnrollPattern(mlir::MLIRContext *context)
      : OpRewritePattern<affine::AffineForOp>(context, /*benefit=*/1) {}

  LogicalResult matchAndRewrite(affine::AffineForOp op,
                                PatternRewriter &rewriter) const override {
    // This is technically not allowed, since in a RewritePattern all
    // modifications to the IR are supposed to go through the `rewriter` arg,
    // but it works for our limited test cases.
    return loopUnrollFull(op);
  }
};

// A pass that invokes the pattern rewrite engine.
void AffineFullUnrollPassAsPatternRewrite::runOnOperation() {
  mlir::RewritePatternSet patterns(&getContext());
  patterns.add<AffineFullUnrollPattern>(&getContext());
  // One could use GreedyRewriteConfig here to slightly tweak the behavior of
  // the pattern application.
  (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
}
} // namespace mlir::luna