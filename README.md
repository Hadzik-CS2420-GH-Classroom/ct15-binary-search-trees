# CT15 -- Binary Search Trees

## Overview

An in-class code-together activity implementing a **Binary Search Tree (BST)** from scratch using recursive patterns. Students implement `BinarySearchTree.cpp` guided by the instructor, building insert, search, three traversals (in-order, pre-order, post-order), and height. The activity closes with a **functor demo**: three pre-built functor structs (PrintFunctor, SumFunctor, CountFunctor) show how separating traversal logic from per-node actions makes the same traversal reusable for printing, summing, and counting.

## Learning Objectives

- Implement **insert** recursively, understanding that new nodes always become leaves and duplicates are ignored
- Implement **search** and explain why it is identical to binary search on a sorted array, achieving O(log n) on a balanced tree
- Implement **in-order traversal** and explain why it produces sorted output given the BST property
- Implement **pre-order** and **post-order** traversals and identify a real use case for each (copy/serialize vs. safe deletion)
- Implement **height** recursively, using -1 as the base case for nullptr so a leaf has height 0
- Explain what a **functor** is and why it is more flexible than a hardcoded print traversal — a struct with operator() can carry state (running sum, count) that a plain function cannot

## Project Structure

```
ct15-binary-search-trees/
├── CMakeLists.txt
├── assignment.json
├── README.md
├── include/
│   ├── BinarySearchTree.h      # Node struct + class declaration
│   └── Functors.h              # PrintFunctor, SumFunctor, CountFunctor (provided)
├── src/
│   ├── BinarySearchTree.cpp    # Implementation (main teaching file)
│   └── main.cpp                # Demo driver showing all operations
├── tests/
│   └── ct15_test.cpp           # Google Test suite
└── images/
    ├── cpp_diagrams.md         # Diagram list for BinarySearchTree.cpp
    ├── functor_diagrams.md     # Diagram list for Functors.h and inorder_apply
    └── header_diagrams.md      # Diagram list for BinarySearchTree.h
```

## What You'll Do

Work through `BinarySearchTree.cpp` section by section, implementing each method as the instructor explains the concept. Sections 1–5 are TODOs (constructor through height); Section 7 is a provided functor demo with discussion. After each section, run `main.cpp` to verify output. The session closes with Section 3 of main: three pre-built functors (PrintFunctor, SumFunctor, CountFunctor) applied via `inorder_apply` to show how the same traversal can print, sum, or count without rewriting traversal logic.

## Files

| File | Focus | TODOs |
|---|---|---|
| `BinarySearchTree.h` | Node struct, class interface, inorder_apply template | 0 (provided) |
| `Functors.h` | PrintFunctor, SumFunctor, CountFunctor | 0 (provided) |
| `BinarySearchTree.cpp` | BST method implementations + functor discussion | 6 (sections 1–5) |
| `main.cpp` | Demo driver: build, search, functor demo | 0 (run as-is per section) |

## Teaching Order

### 1. `BinarySearchTree.h` -- Node struct and class declaration

Walk through the header. Discuss the BST property, the Node struct, the public/private split, and `inorder_apply` — the template method that accepts any functor (introduced here so students see it before the functor demo at the end).

### 2. `Functors.h` -- Functor definitions (provided)

Walk through all three functors before any implementation. Students should understand `operator()` and the stateless vs. stateful distinction before they see functors used in `main.cpp`.

1. **PrintFunctor** -- stateless; operator()(int) prints value + space; callable like a function
2. **SumFunctor** -- stateful; accumulates `total`; persists state between calls via struct member
3. **CountFunctor** -- stateful; increments `count` regardless of value; ignores the argument entirely

### 3. `BinarySearchTree.cpp` -- Implementations (6 TODOs + functor discussion)

1. **Section 1: Constructor / Destructor** -- initialize root_ to nullptr; destroy_ uses post-order to free children before parent
2. **Section 2: insert / insert_** -- return-the-node pattern; BST property routes each value left or right; new nodes land as leaves
3. **Section 3: search / search_** -- identical logic to binary search; each comparison eliminates one subtree; O(log n) on balanced tree
4. **Section 4a: inorder / inorder_** -- Left-Root-Right; produces ascending sorted output by the BST property
5. **Section 4b: preorder / preorder_** -- Root-Left-Right; root is first; useful for cloning/serializing the tree
6. **Section 4c: postorder / postorder_** -- Left-Right-Root; root is last; same order as safe deletion
7. **Section 5: height / height_** -- base case nullptr = -1; leaf = 0; recursive max + 1
8. **Section 7: Functors (provided, discussion only)** -- no TODO; discuss why inorder_apply is a template, how the compiler generates one version per functor type, and why functors beat function pointers for stateful operations

### 4. `main.cpp` -- Demo driver (3 sections)

1. **Section 1: Build and visualize** -- insert 50, 30, 70, 20, 40, 60, 80; print all three traversals and height
2. **Section 2: Search** -- search for values that exist and values that don't; confirm correct true/false
3. **Section 3: Functors** -- apply PrintFunctor (same output as inorder), SumFunctor (total = 350), CountFunctor (count = 7); compare to hardcoded print and discuss why functors win

## Diagrams

Diagrams are SVGs in `images/svgs/` and referenced from the source code via `images/cpp_diagrams.md`, `images/header_diagrams.md`, and `images/functor_diagrams.md`.

| Diagram | Shows |
|---|---|
| `bst_property` | BST property: left < parent < right, annotated on 7-node example tree |
| `node_structure` | Three-cell node: left pointer, data, right pointer |
| `insert_path` | Step-by-step insert path for value 40 with code and tree trace |
| `search_path` | Search path: found (40) vs not found (45), showing subtree elimination |
| `traversal_orders` | All three traversal orders with numbered visit sequence on same tree |
| `height_convention` | Height at each level: nullptr=-1, leaf=0, with 1+max calculation |
| `functor_what_is` | What a functor is: struct + operator() compared to a plain function |
| `functor_stateless_vs_stateful` | PrintFunctor (stateless) vs SumFunctor/CountFunctor (stateful with member) |
| `functor_inorder_apply` | inorder_apply template: one traversal, pluggable action at each node |
| `functor_apply_print` | Trace of inorder_apply with PrintFunctor on 7-node tree |
| `functor_apply_sum` | Trace of inorder_apply with SumFunctor: running total at each step |
| `functor_apply_count` | Trace of inorder_apply with CountFunctor: counter increments at each node |

## Grading (30 points)

| Category | Points | What is tested |
|---|---|---|
| Build | 0 | Project must compile (tests won't run otherwise) |
| Insert | 6 | Single insert, multiple inserts, duplicates ignored, height after insert |
| Search | 6 | Found, not found, root only, empty tree, negative values, large dataset |
| Traversals | 12 | In-order (sorted output, 4 pts), pre-order (root first, 4 pts), post-order (root last, 4 pts) |
| Height | 6 | Empty (-1), single node (0), balanced 7-node (2), degenerate right/left spine (n-1) |
| Functors | 0 | Provided infrastructure — tests verify integration works once BST is correct |
