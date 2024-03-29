#ifndef LIB_DIALECT_POLY_POLYTRAITS_H_
#define LIB_DIALECT_POLY_POLYTRAITS_H_
#include <mlir/IR/OpDefinition.h>

namespace mlir::toy::poly {
template <typename ConcreteType>
class Has32BitArguments
    : public OpTrait::TraitBase<ConcreteType, Has32BitArguments> {
public:
  static LogicalResult verifyTraits(Operation *op) {
    for (auto type : op->getOperandTypes()) {
      if (!type.isIntOrIndex())
        continue;

      if (!type.isInteger(32)) {
        return op->emitOpError()
               << "requires each numeric operand to be a 32-bit integer";
      }
    }
    return success();
  }
};
} // namespace mlir::toy::poly

#endif // LIB_DIALECT_POLY_POLYTRAITS_H_