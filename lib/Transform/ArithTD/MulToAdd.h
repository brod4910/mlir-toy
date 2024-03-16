#pragma once
#include "lib/Transform/ArithTD/MulToAdd.h"
#include "mlir/Pass/Pass.h"

namespace mlir::luna {
#define GEN_PASS_DECL_MULTOADD
#include "lib/Transform/ArithTD/Passes.h.inc"
}