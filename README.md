# CT15 -- Binary Search Trees

## Overview

An in-class code-together activity implementing a **Binary Search Tree (BST)** from scratch using recursive patterns. Students implement `BinarySearchTree.cpp` guided by the instructor, building insert, search, three traversals (in-order, pre-order, post-order), and height. The activity covers the BST property and why in-order traversal produces sorted output.

## Learning Objectives

- Implement **insert** recursively, understanding that new nodes always become leaves and duplicates are ignored
- Implement **search** and explain why it is identical to binary search on a sorted array, achieving O(log n) on a balanced tree
- Implement **in-order traversal** and explain why it produces sorted output given the BST property
- Implement **pre-order** and **post-order** traversals and identify a real use case for each (copy/serialize vs. safe deletion)
- Implement **height** recursively, using -1 as the base case for nullptr so a leaf has height 0

## Project Structure

```
ct15-binary-search-trees/
├── CMakeLists.txt
├── assignment.json
├── README.md
├── include/
│   └── BinarySearchTree.h      # Node struct + class declaration
├── src/
│   ├── BinarySearchTree.cpp    # Implementation (main teaching file)
│   └── main.cpp                # Demo driver showing all operations
├── tests/
│   └── ct15_test.cpp           # Google Test suite
└── images/
    ├── cpp_diagrams.md         # Diagram list for BinarySearchTree.cpp
    └── header_diagrams.md      # Diagram list for BinarySearchTree.h
```

## What You'll Do

Work through `BinarySearchTree.cpp` section by section, implementing each method as the instructor explains the concept. The file is organized into eight numbered sections matching the teaching order below. After each section, uncomment the corresponding block in `main.cpp` to see the results. By the end, you will have a working BST that demonstrates all core operations and prints a degenerate tree whose height equals n-1, setting up the motivation for AVL trees.

## Files

| File | Focus | TODOs |
|---|---|---|
| `BinarySearchTree.cpp` | All BST method implementations | 6 (one per section) |
| `main.cpp` | Demo driver for all operations | 2 sections |

## Teaching Order

### 1. `BinarySearchTree.h` -- Node struct and class declaration

Walk through the header. Discuss the BST property, the Node struct, and the public/private split (public wrappers call private recursive helpers).

### 2. `BinarySearchTree.cpp` -- Implementations (6 sections)

1. **Section 1: Constructor / Destructor** -- initialize root_ to nullptr; destroy_ uses post-order to free children before parent
2. **Section 2: insert / insert_** -- return-the-node pattern; BST property routes each value left or right; new nodes land as leaves
3. **Section 3: search / search_** -- identical logic to binary search; each comparison eliminates one subtree; O(log n) on balanced tree
4. **Section 4a: inorder / inorder_** -- Left-Root-Right; produces ascending sorted output by the BST property
5. **Section 4b: preorder / preorder_** -- Root-Left-Right; root is first; useful for cloning/serializing the tree
6. **Section 4c: postorder / postorder_** -- Left-Right-Root; root is last; same order as safe deletion
7. **Section 5: height / height_** -- base case nullptr = -1; leaf = 0; recursive max + 1

### 3. `main.cpp` -- Demo driver (2 sections)

1. **Section 1: Build and visualize** -- insert 50, 30, 70, 20, 40, 60, 80; print all three traversals and height
2. **Section 2: Search** -- search for values that exist and values that don't; confirm correct true/false

## Diagrams

| File | Description |
|---|---|
| `images/bst_property.png` | BST property diagram: left < parent < right, annotated on example tree |
| `images/insert_path.png` | Step-by-step insert path for value 40 into the 7-node example tree |
| `images/search_path.png` | Search path for a found value and a not-found value, showing elimination |
| `images/traversal_orders.png` | All three traversal orders shown on the same 7-node tree |
| `images/remove_cases.png` | All three remove cases side by side with before/after pointers |
| `images/degenerate_bst.png` | Inserting 1, 2, 3, 4, 5 in order forming a right-spine linked list |

## Grading (25 points)

| Category | Points | What is tested |
|---|---|---|
| Build | 0 | Project must compile (tests won't run otherwise) |
| Insert / Search | 10 | Single insert, multiple inserts, search found, search not-found, duplicates ignored |
| Traversals | 10 | In-order (sorted output), pre-order (root-first), post-order (root-last), single-node case |
| Height | 5 | Empty (-1), single node (0), balanced 7-node (2), degenerate right spine (n-1) |
