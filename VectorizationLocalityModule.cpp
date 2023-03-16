//===--- PortabilityTidyModule.cpp - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "DataStructuresCheck.h"
#include "UseIspcCheck.h"

namespace clang {
namespace tidy {
namespace vectorization_locality {

class VectorizationLocalityModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<DataStructuresCheck>(
        "vectorization-locality-datastructures");
  }
};

// Register the PortabilityModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<VectorizationLocalityModule>
    X("vectorization-locality-module", "Adds vectorization-locality-related checks.");

} // namespace vectorization_locality

// This anchor is used to force the linker to link in the generated object file
// and thus register the PortabilityModule.
volatile int VectorizationLocalityModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang
