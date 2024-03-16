#pragma once
#include "lib/Transform/AffineTD/AffineFullUnroll.h"
#include "lib/Transform/AffineTD/AffineFullUnrollPatternRewrite.h"

namespace mlir::toy {
#define GEN_PASS_REGISTRATION
#include "lib/Transform/AffineTD/Passes.h.inc"

}