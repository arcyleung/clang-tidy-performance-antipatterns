# Vectorization & Locality Checks

## Install

1. Clone the llvm clang repo
2. Move the subdirectory into clang/clang-tools-extra/clang-tidy/
3. Add the following to CMakeLists.txt under the existing clang-tidy/ directory
```cmake
add_subdirectory(vectorization_locality)

...

set(
    ...
    clangTidyVectorizationLocalityModule
    ...
)
```
4. Run `make clang-tidy` (optionally, `make install` so clangd is available system-wide for vscode to use on startup)
5. In your project `.clang-tidy` file, add to enabled checks line
```
Checks: '...,vectorization-locality-datastructures'
```

## About
C/C++ is widely used in a diverse set of industry/ academic domains, best practices may already be solidified but the arrival of new hardwares and architectures signals a time to rethink some programming models for high performance computing. Abstraction libraries and frameworks and such as Kokkos and compilers such as ISPC exist, we also wish to provide tools to detect potential performance issues alongside programming errors at design time.

This set of clang checks look for inefficient patterns when it comes to program speed. The compiler may fail to autovectorize these due to reasons not apparent to the programmer, so we suggest alternative replacements which are vectorization and cache-friendly.

A cost model is in the works for the user to select a compromise level between memory (space) usage and performance (time), where depending on the underlying architecture/ hardware at runtime, the end user can have fine grained control over these tradeoffs. 

Since this approach of matching the AST is considered static analysis, there will be limitations, compared to post-link and runtime optimizatons. The goal is to guide Software Engineers at design time to consciously make tradeoffs, as opposed to the hands-off automated approach to transform or tune a program executable. This is one step before manually writing intrinsics SIMD code or assembly, which is less readable and portable, also more difficult to debug. 

## Contributing
See CONTRIBUTING.md

## License
See LICENSE.md