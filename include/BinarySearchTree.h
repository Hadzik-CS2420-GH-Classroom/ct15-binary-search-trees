#pragma once
#include <iostream>
#include <algorithm>  // std::max
#include "Functors.h" // PrintFunctor, SumFunctor, CountFunctor

// =============================================================================
// CT15: Binary Search Trees — Day 1
// =============================================================================
//
// A Binary Search Tree (BST) is a linked structure where every node obeys
// the BST property:
//   - all values in the LEFT subtree are LESS than the node's value
//   - all values in the RIGHT subtree are GREATER than the node's value
//
// This property holds recursively for every node in the tree, which gives
// us O(log n) search and insert on a balanced tree.
//
// ? SEE DIAGRAM: images/header_diagrams.md #1 — BST property: left < parent < right
//

// -----------------------------------------------------------------------------
// Node — the building block of the BST
// -----------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/header_diagrams.md #2 — Node structure: data, left, right
//
// Each node holds an integer value and two child pointers.
// Nodes are heap-allocated; the BinarySearchTree class owns them all.
//
struct Node {
    int   data;   // the stored value
    Node* left;   // pointer to left child  (smaller values)
    Node* right;  // pointer to right child (larger values)

    // Constructor: set data, null out children
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// -----------------------------------------------------------------------------
// BinarySearchTree — manages a tree of Node objects
// -----------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/public_private_pattern.svg — why public + private helpers
//
// ! DISCUSSION: The public/private helper pattern.
//   - public methods provide a clean interface: insert(50), inorder(), etc.
//   - private helpers add a Node* parameter so they can recurse through the tree
//   - the public method starts recursion at root_; the private helper does the work
//   - users never see root_ or Node* — encapsulation
//   - naming convention: trailing underscore (insert_ , search_) signals "private helper"
//
class BinarySearchTree {
public:
    // -------------------------------------------------------------------------
    // Constructor / Destructor
    // -------------------------------------------------------------------------

    /// Constructs an empty BST (root_ = nullptr).
    BinarySearchTree();

    /// Destroys the entire tree, freeing all heap-allocated nodes.
    /// Uses post-order traversal so children are freed before parents.
    ~BinarySearchTree();

    // -------------------------------------------------------------------------
    // Modifiers
    // -------------------------------------------------------------------------

    // ? SEE DIAGRAM: images/header_diagrams.md #3 — insert path for value 40
    //
    // ! DISCUSSION: How BST insert works.
    //   - compare the new value to the current node
    //   - less than: go left.  Greater than: go right.
    //   - repeat until we reach a nullptr slot — that's where the new node goes
    //   - new nodes are ALWAYS leaves — we never rearrange existing links
    //
    // ! DISCUSSION: Duplicates are ignored.
    //   - if value == node->data, we simply return without inserting
    //   - every value in the tree is unique
    //
    // - Time: O(log n) balanced | O(n) degenerate
    // - The recursive helper returns a Node* so the parent can reattach its child
    //
    void insert(int value);

    // -------------------------------------------------------------------------
    // Queries
    // -------------------------------------------------------------------------

    // ? SEE DIAGRAM: images/header_diagrams.md #4 — search path showing halving at each node
    //
    // ! DISCUSSION: BST search is binary search on a linked structure.
    //   - at each node, one comparison eliminates an entire subtree
    //   - if value < node: the value cannot be in the right subtree — go left
    //   - if value > node: the value cannot be in the left subtree — go right
    //   - if value == node: found it — return true
    //   - if we reach nullptr: the value is not in the tree — return false
    //
    // ! DISCUSSION: Time complexity depends on tree shape.
    //   - balanced tree (height ≈ log n): O(log n) — same as binary search on an array
    //   - degenerate tree (height = n − 1): O(n) — same as scanning a linked list
    //   - this is why balance matters — and why AVL trees exist
    //
    bool search(int value) const;

    // ? SEE DIAGRAM: images/header_diagrams.md #5 — height convention: nullptr=-1, leaf=0
    //
    // ! DISCUSSION: Height determines the cost of every operation.
    //   - search, insert, and remove each take O(height) time
    //   - height is the number of edges on the longest root-to-leaf path
    //   - balanced tree: height ≈ log₂(n) — all operations are O(log n)
    //   - degenerate tree: height = n − 1 — all operations degrade to O(n)
    //
    // ! DISCUSSION: The base case — nullptr has height −1.
    //   - a leaf has two nullptr children (height −1 each)
    //   - leaf height = 1 + max(−1, −1) = 0 — correct
    //   - using −1 (not 0) for nullptr avoids an off-by-one in every calculation
    //
    int height() const;

    /// Returns true if the tree contains no nodes.
    bool is_empty() const;

    // -------------------------------------------------------------------------
    // Traversals
    // -------------------------------------------------------------------------
    //
    // ? SEE DIAGRAM: images/header_diagrams.md #6 — all three traversal orders on same tree
    //
    // Each traversal prints all values to std::cout separated by spaces,
    // followed by std::endl.  The order of visiting nodes differs:

    /// In-order traversal: Left → Root → Right.
    /// Visits nodes in ascending (sorted) order — a key BST property.
    void inorder() const;

    /// Pre-order traversal: Root → Left → Right.
    /// Visits the root before its subtrees — useful for copying or serializing a tree.
    void preorder() const;

    /// Post-order traversal: Left → Right → Root.
    /// Visits children before parent — the same order used for safe deletion.
    void postorder() const;

    // -------------------------------------------------------------------------
    // Functor-based Traversal
    // -------------------------------------------------------------------------
    //
    // ! DISCUSSION: What is a functor?
    //   - a functor (function object) is a struct/class that overloads operator()
    //   - it can be "called" like a function: functor(arg)
    //   - unlike a function pointer, a functor can carry STATE between calls
    //     (e.g., a running sum, a count, a collected list)
    //
    // ! DISCUSSION: Why use a functor instead of hardcoding print?
    //   - the traversals above hardcode std::cout — they can ONLY print
    //   - with a functor, the same traversal logic can: sum values, count nodes,
    //     find min/max, collect into a vector, check a condition, etc.
    //   - we write the traversal ONCE; the functor controls what happens at each node
    //

    /// Applies a functor to every node in in-order sequence.
    /// The functor must provide operator()(int value).
    /// Template allows any functor type — no inheritance needed.
    template <typename Functor>
    void inorder_apply(Functor& func) const {
        inorder_apply_(root_, func);
    }

private:
    Node* root_;   // pointer to the root node (nullptr when tree is empty)

    // -------------------------------------------------------------------------
    // Private recursive helpers
    // -------------------------------------------------------------------------

    /// Recursively inserts value into the subtree rooted at node.
    /// Returns the (possibly new) root of that subtree.
    Node* insert_(Node* node, int value);

    /// Recursively searches for value in the subtree rooted at node.
    bool search_(Node* node, int value) const;

    /// Recursive in-order helper: prints left subtree, then node, then right.
    void inorder_(Node* node) const;

    /// Recursive pre-order helper: prints node, then left subtree, then right.
    void preorder_(Node* node) const;

    /// Recursive post-order helper: prints left subtree, then right, then node.
    void postorder_(Node* node) const;

    /// Returns the height of the subtree rooted at node.
    /// Base case: nullptr has height -1.
    int height_(Node* node) const;

    /// Recursively deletes all nodes in the subtree rooted at node (post-order).
    void destroy_(Node* node);

    /// Recursive helper for inorder_apply — applies functor at each node.
    /// Template must be in the header because the compiler needs to see
    /// the full definition to generate code for each functor type.
    template <typename Functor>
    void inorder_apply_(Node* node, Functor& func) const {
        if (!node) return;
        inorder_apply_(node->left, func);
        func(node->data);          // call the functor's operator()
        inorder_apply_(node->right, func);
    }
};
