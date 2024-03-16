#pragma once

#include "lib/Transform/ArithTD/MulToAdd.h"

namespace mlir::luna {
#define GEN_PASS_REGISTRATION
#include "lib/Transform/ArithTD/Passes.h.inc"

}