# CT15 -- Implementation Diagrams

Code-block diagrams referenced from `BinarySearchTree.cpp`.

---

## 1. Constructor / Destructor: Post-Order Deletion
*`BinarySearchTree.cpp::destroy_()` -- children freed before parent to avoid losing pointers*

![Post-Order Deletion](svgs/destroy_postorder.svg)

---

## 2. destroy_() Recursion Trace
*`BinarySearchTree.cpp::destroy_()` -- step-by-step trace showing every recursive call, base case, and deletion*

![Recursion Trace](svgs/destroy_recursion_trace.svg)

---

## 3. Insert Path
*`BinarySearchTree.cpp::insert_()` -- each comparison routes left or right; new node lands as a leaf*

![Insert Path](svgs/insert_path.svg)

---

## 4. insert_() Recursion Trace
*`BinarySearchTree.cpp::insert_()` -- step-by-step call stack inserting 40, showing the unwind that reattaches child pointers*

![Insert Recursion Trace](svgs/insert_recursion_trace.svg)

---

## 5. Search Path
*`BinarySearchTree.cpp::search_()` -- each comparison eliminates one subtree; O(log n) on balanced tree*

![Search Path](svgs/search_path.svg)

---

## 6. search_() Recursion Trace
*`BinarySearchTree.cpp::search_()` -- side-by-side traces: found (40) vs not found (45), showing how true/false bubbles up*

![Search Recursion Trace](svgs/search_recursion_trace.svg)

---

## 7. In-Order Traversal: Code + Trace
*`BinarySearchTree.cpp::inorder_()` -- Left, Print, Right on 5-node tree showing sorted output*

![In-Order Trace](svgs/inorder_trace.svg)

---

## 8. Pre-Order Traversal: Code + Trace
*`BinarySearchTree.cpp::preorder_()` -- Print, Left, Right on 5-node tree showing root-first output*

![Pre-Order Trace](svgs/preorder_trace.svg)

---

## 9. Post-Order Traversal: Code + Trace
*`BinarySearchTree.cpp::postorder_()` -- Left, Right, Print on 5-node tree showing leaves-first output*

![Post-Order Trace](svgs/postorder_trace.svg)

---

## 10. Height: Recursive Calculation
*`BinarySearchTree.cpp::height_()` -- base case nullptr=-1, each node adds 1+max(left, right)*

![Height Recursive](svgs/height_recursive.svg)

---

## 11. height_() Recursion Trace
*`BinarySearchTree.cpp::height_()` -- step-by-step bottom-up trace showing how -1 bubbles up through leaves to root*

![Height Recursion Trace](svgs/height_recursion_trace.svg)

---

## 12. Functor-Based Traversal
*`BinarySearchTree.h::inorder_apply_()` -- same traversal logic, functor controls what happens at each node*

![Functor Inorder Apply](svgs/functor_inorder_apply.svg)

---

## 13. inorder_apply with PrintFunctor
*`BinarySearchTree.cpp` -- PrintFunctor running on the tree: stateless, prints each value in order*

![PrintFunctor Apply](svgs/functor_apply_print.svg)

---

## 14. inorder_apply with SumFunctor
*`BinarySearchTree.cpp` -- SumFunctor running on the tree: stateful, total accumulates at each node*

![SumFunctor Apply](svgs/functor_apply_sum.svg)

---

## 15. inorder_apply with CountFunctor
*`BinarySearchTree.cpp` -- CountFunctor running on the tree: stateful, counts nodes, ignores values*

![CountFunctor Apply](svgs/functor_apply_count.svg)
