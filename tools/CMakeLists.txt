get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

set (LIBS
    ${dialect_libs}
    ${conversion_libs}
    AffineFullUnroll
    # MLIRNoisy
    MLIROptLib
    MLIRPass
    # MLIRPoly
    # MulToAdd
    # NoisyPasses
    # PolyToStandard
    ortools::ortools
)

add_llvm_executable(first-pass first-pass.cpp)

llvm_update_compile_flags(first-pass)
target_link_libraries(first-pass PRIVATE ${LIBS})

mlir_check_all_link_libraries(first-pass)