add_mlir_library(AffineFullUnroll
    AffineFullUnroll.cpp

    ${PROJECT_SOURCE_DIR}/lib/Transform/Affine/
    ADDITIONAL_HEADER_DIRS

    LINK_LIBS PUBLIC
)