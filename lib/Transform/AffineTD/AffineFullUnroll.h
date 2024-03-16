#pragma once

#include "mlir/Pass/Pass.h"

namespace mlir::toy {
#define GEN_PASS_DECL_AFFINEFULLUNROLL
#include "lib/Transform/AffineTD/Passes.h.inc"
} // namespace mlir::toy