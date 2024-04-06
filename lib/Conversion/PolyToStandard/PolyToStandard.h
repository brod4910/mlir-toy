#ifndef LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_H_
#define LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_H_
#include "mlir/Pass/Pass.h"

#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/Tensor/IR/Tensor.h"

namespace mlir::toy::poly {
#define GEN_PASS_DECL
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

#define GEN_PASS_REGISTRATION
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"
} // namespace mlir::toy::poly

#endif // LIB_CONVERSION_POLYTOSTANDARD_POLYTOSTANDARD_H_