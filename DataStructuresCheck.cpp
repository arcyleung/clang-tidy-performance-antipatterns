//===--- SIMDIntrinsicsCheck.cpp - clang-tidy------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DataStructuresCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/Decl.h"
#include "clang/AST/DeclTemplate.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/TypeLoc.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/TargetInfo.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Regex.h"
#include <iostream>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace vectorization_locality {

void DataStructuresCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
        varDecl(
          has(
            cxxConstructExpr()
          ),
          hasType(
            classTemplateSpecializationDecl().bind("sp_dcl")
          )
      ).bind("var_dcl"),
  this);
}

void DataStructuresCheck::check(const MatchFinder::MatchResult &Result) {
  using CTSD = ClassTemplateSpecializationDecl;
  const auto *spec_decl = Result.Nodes.getNodeAs<CTSD>("sp_dcl");
  const auto *var_decl = Result.Nodes.getNodeAs<VarDecl>("var_dcl");

  auto templateArgs = spec_decl->getTemplateArgs().asArray();

  for (auto a: templateArgs) {
    if (a.getAsType()->isBooleanType()) {

      auto typeLoc = var_decl->getTypeSourceInfo()->getTypeLoc();
      auto specTypeLoc = typeLoc.getAs<clang::TemplateSpecializationTypeLoc>();
      
      diag(
        // Put the carat at the spec type location
        specTypeLoc.getArgLoc(0).getLocation(),

        // Show the message to the developer
        "std::vector<bool> is not contiguous for efficient vectorization, prefer std::vector<char>")

        // Implement a replacement action
        << FixItHint::CreateReplacement(specTypeLoc.getArgLoc(0).getSourceRange(), "char");

    }
  }
}

} // namespace vectorization_locality
} // namespace tidy
} // namespace clang
