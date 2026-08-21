# Tungsten-CC 🚀
**High-Performance SSA-based C Compiler Targeting AMD64**

Tungsten-CC is a robust, bare-metal C compiler built from the ground up to explore advanced modern compilation techniques. It features a custom Intermediate Representation (IR), rigorous Static Single Assignment (SSA) optimizations, and an advanced Chaitin-Briggs Graph Coloring register allocator targeting the AMD64 architecture.

---

## 🧠 Compiler Architecture

Tungsten-CC follows a strict multi-pass architecture, ensuring separation of concerns between frontend parsing, middle-end optimizations, and backend code generation.

### 1. Frontend: Lexical Analysis & Parsing
The frontend is responsible for transforming raw C source code into a mathematically rigid Abstract Syntax Tree (AST).
* **Lexer**: A highly optimized deterministic finite automaton (DFA) state machine capable of precise column/line tracking for diagnostic error reporting.
* **Parser**: A top-down recursive descent parser that constructs arena-allocated AST nodes. It implements Pratt Parsing (top-down operator precedence) to correctly handle the notoriously complex C expression precedence and associativity rules.

### 2. Middle-End: Intermediate Representation (IR) & SSA
This is the heart of Tungsten-CC's optimization capabilities. The AST is lowered into a linear sequence of atomic instructions forming a custom Three-Address Code (TAC).
* **Control Flow Graph (CFG)**: The TAC is organized into Basic Blocks, explicitly modeling branching via Jump and Conditional Jump instructions.
* **Static Single Assignment (SSA) Form**:
  * **Dominator Trees**: The compiler calculates immediate dominators (IDOM) using iterative dataflow analysis to construct a strict Dominator Tree.
  * **Dominance Frontiers**: Calculates exact insertion points for $\Phi$ (Phi) nodes.
  * **Variable Renaming**: Enforces strict SSA invariants by versioning virtual registers during a pre-order traversal of the Dominator Tree.
* **SSA-Based Optimizations**:
  * *Constant Folding*: Aggressively evaluates constant expressions at compile-time to reduce runtime overhead.
  * *Dead Code Elimination (DCE)*: Prunes instructions whose outputs are mathematically provable to be unused.

### 3. Backend: Register Allocation
Mapping infinite virtual registers to the highly constrained finite set of 14 usable general-purpose physical registers on AMD64.
* **Liveness Analysis**: Computes `IN` and `OUT` liveness sets for every basic block via backward dataflow equations to determine exactly when a variable's lifespan ends.
* **Interference Graph**: Builds a symmetric graph where nodes represent virtual registers and edges represent overlapping lifespans.
* **Chaitin-Briggs Graph Coloring Allocator**:
  * **Simplify**: Iteratively removes nodes with a degree less than 14, pushing them onto a stack.
  * **Spill**: Fallback heuristic to gracefully spill high-degree variables to the stack frame when register pressure is too high.
  * **Select**: Pops nodes from the stack and colors them (assigns physical registers), strictly ensuring that no connected nodes share a color.

### 4. Code Generation & Sanitizers
Hardening the executable and outputting native machine code.
* **AMD64 Codegen**: Translates colored TAC IR directly to Intel-syntax AMD64 assembly, respecting System V ABI calling conventions (prologues, epilogues, stack alignment).
* **Address Sanitizer (ASan)**: Optionally injects runtime shadow memory checks immediately preceding every IR `LOAD` and `STORE` instruction to trap out-of-bounds access.
* **Undefined Behavior Sanitizer (UBSan)**: Injects division-by-zero checks before `DIV` and `MOD` operations.

---

## 🛡️ Differential Testing Framework

Compiler correctness is non-negotiable. Tungsten-CC includes a custom Python-based fuzzing harness designed to brutally stress-test the pipeline against industry standards.

* **Fuzzer (`test/fuzzer.py`)**: Generates infinitely deep, randomized AST trees of complex mathematical C expressions, branching logic, and edge-case syntax.
* **Harness (`test/harness.py`)**: Automatically pipes the fuzzed code through both Tungsten-CC and `clang -O0`. It captures standard output, standard error, and exit codes of both generated binaries, strictly asserting that Tungsten-CC produces mathematically identical runtime behaviors as Clang.

---

## 🛠️ Development & Building

The compiler is written purely in C. No external dependencies like LLVM or Bison/Flex were used—this is a 100% bespoke pipeline.

To run the automated differential fuzzer:
```bash
cd test
python3 harness.py
```
