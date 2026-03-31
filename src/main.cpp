// =============================================================================
// CT15: Binary Search Tree — Demo Driver
// =============================================================================
//
// Walks through all BST operations in a structured class demo.
// Each section has DISCUSSION comments for instructor presentation.
//
// Tree used in sections 1–3 (insert order: 50, 30, 70, 20, 40, 60, 80):
//
//              50
//            /    \
//          30      70
//         /  \    /  \
//        20  40  60   80
//

#include "BinarySearchTree.h"
#include <iostream>

int main() {

    // =============================================================================
    // Section 1: Build and Visualize a BST
    // =============================================================================
    //
    // ! DISCUSSION: Insertion order determines tree shape.
    //   - 50 is inserted first — it becomes the root
    //   - 30 < 50: goes left; 70 > 50: goes right
    //   - 20 < 50, 20 < 30: goes left of 30
    //   - 40 < 50, 40 > 30: goes right of 30
    //   - result is a nicely balanced tree with height 2
    //
    std::cout << "=== Section 1: Build a BST ===" << std::endl;

    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    std::cout << "Tree after inserting 50, 30, 70, 20, 40, 60, 80:" << std::endl;

    // ! DISCUSSION: In-order on a BST always produces sorted output.
    //   - this is a quick correctness check: if it's sorted, the BST property holds
    std::cout << "In-order   (sorted):    ";
    bst.inorder();

    // ! DISCUSSION: Pre-order shows the root first, then its subtrees.
    //   - if you insert values in this exact order into a new empty BST,
    //     you rebuild the identical tree structure
    std::cout << "Pre-order  (root-first): ";
    bst.preorder();

    // ! DISCUSSION: Post-order shows the root last — children before parents.
    //   - this is the deletion order; every subtree is cleaned up before
    //     its parent is removed
    std::cout << "Post-order (root-last):  ";
    bst.postorder();

    std::cout << "Height: " << bst.height() << std::endl;  // expected: 2
    std::cout << std::endl;

    // =============================================================================
    // Section 2: Search
    // =============================================================================
    //
    // ! DISCUSSION: Search eliminates one subtree at every step.
    //   - searching for 40: 40 < 50 (go left), 40 > 30 (go right), found!
    //   - only 3 comparisons for a 7-node tree — same as binary search
    //   - searching for 45: 45 < 50 (left), 45 > 30 (right), 45 > 40 (right),
    //     nullptr — not found. 3 comparisons, definitive answer.
    //
    std::cout << "=== Section 2: Search ===" << std::endl;

    int targets_found[]     = {50, 30, 70, 20, 40, 60, 80};
    int targets_not_found[] = {45, 10, 100, 35};

    std::cout << "Values that ARE in the tree:" << std::endl;
    for (int v : targets_found) {
        std::cout << "  search(" << v << ") = "
                  << (bst.search(v) ? "true" : "false") << std::endl;
    }

    std::cout << "Values that are NOT in the tree:" << std::endl;
    for (int v : targets_not_found) {
        std::cout << "  search(" << v << ") = "
                  << (bst.search(v) ? "true" : "false") << std::endl;
    }
    std::cout << std::endl;

    // =============================================================================
    // Section 3: Functors — Flexible Traversal
    // =============================================================================
    //
    // ! DISCUSSION: The problem with hardcoded traversals.
    //   - inorder() above can ONLY print — it has std::cout baked in
    //   - what if we want to sum all values? count nodes? collect into a vector?
    //   - we'd have to write a separate traversal for each — lots of duplication
    //
    // ! DISCUSSION: Functors solve this by separating "how to traverse" from "what to do".
    //   - a functor is a struct with operator() — it looks like a function call
    //   - we pass it to inorder_apply, which calls func(value) at each node
    //   - the traversal logic is written ONCE; the functor controls the action
    //
    std::cout << "=== Section 3: Functors ===" << std::endl;

    // --- PrintFunctor: stateless, same output as inorder() ---
    //
    // ! DISCUSSION: PrintFunctor is the simplest functor.
    //   - operator()(int value) just prints the value
    //   - no state — every call is independent
    //   - proves that inorder_apply produces the same output as inorder()
    //
    PrintFunctor printer;
    std::cout << "inorder_apply(PrintFunctor): ";
    bst.inorder_apply(printer);
    std::cout << std::endl;

    // --- SumFunctor: stateful, accumulates a running total ---
    //
    // ! DISCUSSION: This is where functors shine over plain functions.
    //   - SumFunctor has a `total` member that persists between calls
    //   - passed by reference: inorder_apply modifies the SAME functor object
    //   - after traversal, sf.total holds the sum of every node in the tree
    //   - a function pointer can't do this without a global variable
    //
    SumFunctor summer;
    bst.inorder_apply(summer);
    std::cout << "Sum of all values: " << summer.total << std::endl;
    // expected: 20 + 30 + 40 + 50 + 60 + 70 + 80 = 350

    // --- CountFunctor: stateful, counts nodes ---
    //
    // ! DISCUSSION: Another stateful example.
    //   - ignores the value entirely, just increments a counter
    //   - after traversal, cf.count == number of nodes in the tree
    //
    CountFunctor counter;
    bst.inorder_apply(counter);
    std::cout << "Number of nodes: " << counter.count << std::endl;
    // expected: 7

    std::cout << std::endl;

    return 0;
}
