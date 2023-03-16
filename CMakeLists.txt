set(LLVM_LINK_COMPONENTS
  FrontendOpenMP
  Support
  )

add_clang_library(clangTidyVectorizationLocalityModule
  UseIspcCheck.cpp
  VectorizationLocalityModule.cpp
  DataStructuresCheck.cpp

  LINK_LIBS
  clangTidy
  clangTidyUtils

  DEPENDS
  omp_gen
  )

clang_target_link_libraries(clangTidyVectorizationLocalityModule
  PRIVATE
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  )
