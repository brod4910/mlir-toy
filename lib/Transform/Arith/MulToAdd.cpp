#include "lib/Transform/Arith/MulToAdd.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"

namespace mlir::luna {
// Replace y = C*x with y = C/2*x + C/2*x, when C is a power of 2, otherwise do
// nothing.
struct PowerOfTwoExpand : public OpRewritePattern<arith::MulIOp> {
  PowerOfTwoExpand(mlir::MLIRContext *context)
      : OpRewritePattern<arith::MulIOp>(context, /*benefit=*/2) {}

  LogicalResult matchAndRewrite(arith::MulIOp op,
                                PatternRewriter &rewriter) const override {
    Value lhs = op.getOperand(0);
    Value rhs = op.getOperand(1);
    auto rhsDefiningOp = rhs.getDefiningOp<arith::ConstantIntOp>();

    if (!rhsDefiningOp) {
      return failure();
    }

    int64_t value = rhsDefiningOp.value();
    bool is_power_of_two = (value & (value - 1)) == 0;

    if (!is_power_of_two) {
      return failure();
    }

    arith::ConstantOp newConstant = rewriter.create<arith::ConstantOp>(
        rhsDefiningOp.getLoc(),
        rewriter.getIntegerAttr(rhs.getType(), value / 2));
    arith::MulIOp newMul =
        rewriter.create<arith::MulIOp>(op.getLoc(), lhs, newConstant);
    arith::AddIOp newAdd =
        rewriter.create<arith::AddIOp>(op.getLoc(), newMul, newMul);

    rewriter.replaceOp(op, newAdd);
    rewriter.eraseOp(rhsDefiningOp);

    return success();
  }
};

// Replace y = 9*x with y = 8*x + x
struct PeelFromMul : public OpRewritePattern<arith::MulIOp> {
  PeelFromMul(mlir::MLIRContext *context)
      : OpRewritePattern<arith::MulIOp>(context, /*benefit=*/1) {}

  LogicalResult matchAndRewrite(arith::MulIOp op,
                                PatternRewriter &rewriter) const override {

    return success();
  }
};

void MulToAddPass::runOnOperation() {
  mlir::RewritePatternSet patterns(&getContext());
  patterns.add<PowerOfTwoExpand>(&getContext());
  patterns.add<PeelFromMul>(&getContext());
  (void)applyPatternsAndFoldGreedily(getOperation(), std::move(patterns));
}

} // namespace mlir::luna