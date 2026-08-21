# Tungsten-CC
High-Performance SSA-based C Compiler

Tungsten-CC is a robust, bare-metal C compiler built from the ground up for speed, safety, and modern compilation techniques. It features a custom Intermediate Representation (IR), Static Single Assignment (SSA) optimizations, and an advanced Chaitin-Briggs Graph Coloring register allocator targeting AMD64.

## Core Features
1. **Frontend**: Custom robust Lexer and Recursive Descent Parser for a subset of C.
2. **Intermediate Representation**: Three-Address Code (TAC) with explicit Control Flow Graph (CFG) and Phi-nodes.
3. **Optimizations**: SSA-based Constant Folding, Dead Code Elimination.
4. **Register Allocation**: Graph Coloring (Chaitin-Briggs) for AMD64.
5. **Sanitizers**: Address Sanitizer (ASan) and Undefined Behavior Sanitizer (UBSan).
6. **Testing**: Differential testing harness against Clang for correctness verification.
