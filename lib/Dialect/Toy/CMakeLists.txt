set(LLVM_TARGET_DEFINITIONS ToyOps.td)
mlir_tablegen(ToyOps.h.inc -gen-op-decls)
mlir_tablegen(ToyOps.cpp.inc -gen-op-defs)
mlir_tablegen(ToyDialect.h.inc -gen-dialect-decls -dialect=toy)
mlir_tablegen(ToyDialect.cpp.inc -gen-dialect-defs -dialect=toy)
add_public_tablegen_target(MLIRToyOpsIncGen)
add_dependencies(mlir-headers MLIRToyOpsIncGen)

add_mlir_doc(ToyDialect ToyDialect Toy/ -gen-dialect-doc)

add_mlir_dialect_library(MLIRToy
    ToyDialect.cpp
    # ToyOps.cpp

    ADDITIONAL_HEADER_DIRS
    ${PROJECT_SOURCE_DIR}/lib/Dialect/Toy

    LINK_LIBS PUBLIC
    )