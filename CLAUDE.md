# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

gorge_core is the **C++ implementation** of the runtime and framework for the **gorge programming language**, designed specifically for the **Gorge music game engine**.

**Migration Context**: The original tooling is in C# at `/Users/daxingyi/RiderProjects/gorgecompilertool`. This C++ version represents a gradual migration from C# to C++ for performance and native integration. The **type system is independently designed** (not migrated from C#).

The project provides:
- **Type system** for the gorge language, with rich type metadata independently designed for C++
- **Annotation system** for runtime metadata storage and retrieval
- **External Function Interface (FFI)** for C# interop during migration phase
- **C# bindings** as transitional layer to interface with existing C# codebase

This is the runtime component - the compiler is a separate project. The C++ implementation provides native performance while maintaining compatibility with the existing C# ecosystem.

## Build System

This project uses **xmake** as the build system. Key build targets:

- `gorge_core_cpp`: Shared library (DLL/so) containing the core type system
- `gorge_core`: Executable binary for testing

### Common Build Commands

```bash
# Build both targets (library and executable)
xmake

# Build specific target
xmake build gorge_core_cpp
xmake build gorge_core

# Run the executable
xmake run gorge_core

# Configure for debug mode
xmake f -m debug

# Configure for release mode
xmake f -m release

# On Windows: switch to LLVM toolchain (required for C++ modules)
xmake f --toolchain=llvm -c

# Generate compile_commands.json for IDE support
xmake project -k compile_commands
```

### Platform-Specific Notes

- **Windows**: Must use LLVM toolchain (`xmake f --toolchain=llvm -c`) due to C++ modules support
- **macOS/Linux**: Uses LLVM toolchain by default
- **C++ Modules**: Enabled via `set_policy("build.c++.modules", true)` in xmake.lua

## Architecture

### Runtime Design

This is the **gorge language runtime**, which provides:
1. **Type representation** - For the gorge language's type system (similar to C#'s System.Type)
2. **Reflection capabilities** - Runtime type inspection and metadata access
3. **Interop layer** - Communication between gorge language code and the Gorge game engine
4. **Annotation system** - Custom metadata attributes for runtime use

### Core Type System (`src/objective/`)

The gorge language's type system is implemented using C++23 modules:

1. **`basic_type.cppm`** - Defines `BasicType` enum (Int, Float, Bool, Enum, String, Object, Interface, Delegate)
2. **`gorge_type.cppm`** - Main `GorgeType` class representing type metadata with:
   - Basic type classification
   - Class name and namespace
   - Generic type support (`is_generics`)
   - Subtype hierarchy for arrays, injectors, and generic parameters
3. **`annotation.cppm`** - Annotation system (`Annotation` and `Metadata` classes) for runtime metadata storage

### Module Structure

C++ modules follow this pattern:
```cpp
module;
// Include headers before module declaration
#include "../lib.h"
#include <fmt/core.h>
export module gorge_type;

import std;
import basic_type;
// Module implementation...
```

### FFI Layer (`src/ffi/`)

Provides C-compatible API specifically for C# P/Invoke calls from the Gorge game engine:
- **`ffi.cppm`** - C++ module interface for FFI
- **`ffi_objective.cpp`** - C-compatible API functions for creating and manipulating gorge language types
- Exports factory functions for creating type and annotation objects
- Designed for C# interop via P/Invoke, allowing the C#-based Gorge game engine to create and use gorge language types

### Public API (`src/lib.h`)

Defines platform-specific export macros:
- `GORGE_API` for C++ class exports
- `__export` for C function exports
- Handles Windows DLL export/import semantics

## Dependencies

Managed by xmake package system:
- **Boost** - For hash calculations and utilities
- **fmt** (v10.2.1) - Modern formatting library
- C++23 standard library with modules support

## Development Notes

### IDE Support

- **CLion**: May show errors until compile_commands.json is generated
- Use `xmake project -k compile_commands` to generate IDE configuration
- On Windows, ensure LLVM toolchain is configured to avoid C++ modules errors

### Code Style

- Uses `.clang-format` and `.clang-tidy` for code formatting and linting
- Follows modern C++ practices with smart pointers and RAII
- Type system is designed to be immutable (const fields where possible)

### Testing

The `gorge_core` executable serves as the test runner. Current implementation is minimal (`src/main.cpp`), but can be extended for unit testing.

### Cross-Platform Considerations

- Platform-specific code uses `#ifdef` checks in `src/lib.h`
- Windows requires `GORGE_CORE_CPP_EXPORTS` define when building the DLL
- Linux/macOS use `-fvisibility=default` for symbol visibility