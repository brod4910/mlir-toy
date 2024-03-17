get_property(dialect_libs GLOBAL PROPERTY MLIR_DIALECT_LIBS)
get_property(conversion_libs GLOBAL PROPERTY MLIR_CONVERSION_LIBS)

set (LIBS
    ${dialect_libs}
    ${conversion_libs}
    AffineFullUnroll
    # MLIRNoisy
    MLIROptLib
    MLIRPass
    MLIRPoly
    MulToAdd
    # NoisyPasses
    # PolyToStandard
)

add_llvm_executable(toy toy.cpp)

llvm_update_compile_flags(toy)
target_link_libraries(toy PRIVATE ${LIBS})

mlir_check_all_link_libraries(toy)