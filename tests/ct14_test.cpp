#include <gtest/gtest.h>
#include "BinarySearchTree.h"
#include <sstream>
#include <string>

// =============================================================================
// Helper: capture cout output from a traversal
// =============================================================================
static std::string capture_traversal(BinarySearchTree& bst, char which) {
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    switch (which) {
        case 'i': bst.inorder();   break;
        case 'r': bst.preorder();  break;
        case 'o': bst.postorder(); break;
    }
    std::cout.rdbuf(old);
    return oss.str();
}

// =============================================================================
// Constructor / is_empty / height (empty tree)
// =============================================================================

TEST(BSTConstructor, DefaultIsEmpty) {
    BinarySearchTree bst;
    EXPECT_TRUE(bst.is_empty());
}

TEST(BSTConstructor, DefaultHeightIsNegativeOne) {
    BinarySearchTree bst;
    EXPECT_EQ(bst.height(), -1);
}

TEST(BSTConstructor, SearchOnEmptyReturnsFalse) {
    BinarySearchTree bst;
    EXPECT_FALSE(bst.search(42));
}

// =============================================================================
// Insert — basic
// =============================================================================

TEST(BSTInsert, SingleInsertNotEmpty) {
    BinarySearchTree bst;
    bst.insert(10);
    EXPECT_FALSE(bst.is_empty());
}

TEST(BSTInsert, SingleInsertSearchFindsIt) {
    BinarySearchTree bst;
    bst.insert(10);
    EXPECT_TRUE(bst.search(10));
}

TEST(BSTInsert, SingleInsertHeightZero) {
    BinarySearchTree bst;
    bst.insert(10);
    EXPECT_EQ(bst.height(), 0);
}

TEST(BSTInsert, TwoNodesHeight) {
    BinarySearchTree bst;
    bst.insert(10);
    bst.insert(5);
    EXPECT_EQ(bst.height(), 1);
}

TEST(BSTInsert, DuplicateIgnored) {
    // Inserting the same value twice should not change height or break search
    BinarySearchTree bst;
    bst.insert(10);
    bst.insert(10);
    EXPECT_EQ(bst.height(), 0);
    EXPECT_TRUE(bst.search(10));
}

TEST(BSTInsert, MultipleValues) {
    BinarySearchTree bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    EXPECT_TRUE(bst.search(50));
    EXPECT_TRUE(bst.search(30));
    EXPECT_TRUE(bst.search(70));
    EXPECT_FALSE(bst.search(99));
}

// =============================================================================
// Search
// =============================================================================

TEST(BSTSearch, FoundAndNotFound) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);

    EXPECT_TRUE(bst.search(50));
    EXPECT_TRUE(bst.search(20));
    EXPECT_TRUE(bst.search(80));
    EXPECT_TRUE(bst.search(40));

    EXPECT_FALSE(bst.search(45));
    EXPECT_FALSE(bst.search(10));
    EXPECT_FALSE(bst.search(100));
    EXPECT_FALSE(bst.search(0));
}

TEST(BSTSearch, RootOnly) {
    BinarySearchTree bst;
    bst.insert(42);
    EXPECT_TRUE(bst.search(42));
    EXPECT_FALSE(bst.search(41));
    EXPECT_FALSE(bst.search(43));
}

// =============================================================================
// Height
// =============================================================================

TEST(BSTHeight, SingleNodeZero) {
    BinarySearchTree bst;
    bst.insert(10);
    EXPECT_EQ(bst.height(), 0);
}

TEST(BSTHeight, BalancedSevenNodeTree) {
    // Insert: 50, 30, 70, 20, 40, 60, 80 — perfectly balanced, height = 2
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    EXPECT_EQ(bst.height(), 2);
}

TEST(BSTHeight, DegenerateTreeRightSpine) {
    // Insert 1..5 in order — right spine, height = 4 = n-1
    BinarySearchTree bst;
    for (int v : {1, 2, 3, 4, 5}) bst.insert(v);
    EXPECT_EQ(bst.height(), 4);
}

TEST(BSTHeight, DegenerateTreeLeftSpine) {
    // Insert 5..1 in order — left spine, height = 4
    BinarySearchTree bst;
    for (int v : {5, 4, 3, 2, 1}) bst.insert(v);
    EXPECT_EQ(bst.height(), 4);
}

TEST(BSTHeight, ThreeNodeBalanced) {
    BinarySearchTree bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    EXPECT_EQ(bst.height(), 1);
}

// =============================================================================
// Traversals (capture cout, check string output)
// =============================================================================

TEST(BSTTraversal, InorderProducesSortedOutput) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "20 30 40 50 60 70 80 \n");
}

TEST(BSTTraversal, PreorderRootFirst) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    std::string out = capture_traversal(bst, 'r');
    EXPECT_EQ(out, "50 30 20 40 70 60 80 \n");
}

TEST(BSTTraversal, PostorderRootLast) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);
    std::string out = capture_traversal(bst, 'o');
    EXPECT_EQ(out, "20 40 30 60 80 70 50 \n");
}

TEST(BSTTraversal, SingleNodeInorder) {
    BinarySearchTree bst;
    bst.insert(42);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "42 \n");
}

TEST(BSTTraversal, InorderAfterRandomInsertions) {
    // In-order must be sorted regardless of insertion order
    BinarySearchTree bst;
    for (int v : {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9}) bst.insert(v);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "2 3 4 6 7 9 13 15 17 18 20 \n");
}

// =============================================================================
// is_empty
// =============================================================================

TEST(BSTIsEmpty, NotEmptyAfterInsert) {
    BinarySearchTree bst;
    bst.insert(1);
    EXPECT_FALSE(bst.is_empty());
}

// =============================================================================
// Negative values and mixed
// =============================================================================

TEST(BSTMisc, NegativeValues) {
    BinarySearchTree bst;
    for (int v : {0, -10, 10, -20, -5}) bst.insert(v);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "-20 -10 -5 0 10 \n");
}

TEST(BSTMisc, LargerDatasetSortedOutput) {
    BinarySearchTree bst;
    // Insert in pseudo-random order; in-order must still be sorted
    for (int v : {64, 25, 12, 22, 11, 90, 88, 17, 50, 33}) bst.insert(v);
    std::string out = capture_traversal(bst, 'i');
    EXPECT_EQ(out, "11 12 17 22 25 33 50 64 88 90 \n");
}

// =============================================================================
// Functors
// =============================================================================

TEST(BSTFunctor, PrintFunctorMatchesInorder) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);

    // Capture inorder_apply with PrintFunctor
    std::ostringstream oss;
    std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
    PrintFunctor pf;
    bst.inorder_apply(pf);
    std::cout.rdbuf(old);

    EXPECT_EQ(oss.str(), "20 30 40 50 60 70 80 ");
}

TEST(BSTFunctor, SumFunctorAccumulatesTotal) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);

    SumFunctor sf;
    bst.inorder_apply(sf);
    EXPECT_EQ(sf.total, 350);  // 20+30+40+50+60+70+80
}

TEST(BSTFunctor, CountFunctorCountsNodes) {
    BinarySearchTree bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80}) bst.insert(v);

    CountFunctor cf;
    bst.inorder_apply(cf);
    EXPECT_EQ(cf.count, 7);
}

TEST(BSTFunctor, SumFunctorEmptyTree) {
    BinarySearchTree bst;
    SumFunctor sf;
    bst.inorder_apply(sf);
    EXPECT_EQ(sf.total, 0);
}

TEST(BSTFunctor, CountFunctorSingleNode) {
    BinarySearchTree bst;
    bst.insert(42);
    CountFunctor cf;
    bst.inorder_apply(cf);
    EXPECT_EQ(cf.count, 1);
}
