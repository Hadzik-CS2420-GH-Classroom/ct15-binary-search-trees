# CT15 -- Functor Diagrams

Conceptual diagrams referenced from `Functors.h`.

---

## 1. Why No Functors.cpp?
*`Functors.h` -- why these structs are defined entirely in the header with no .cpp file*

![Why No Functors.cpp?](svgs/functor_no_cpp.svg)

---

## 2. What Is a Functor?
*`Functors.h` -- a struct with operator() that can be called like a function but carries state*

![What Is a Functor?](svgs/functor_what_is.svg)

---

## 3. Stateless vs Stateful Functors
*`Functors.h` -- PrintFunctor (no state, just prints) vs SumFunctor (accumulates a total across calls)*

![Stateless vs Stateful](svgs/functor_stateless_vs_stateful.svg)

---

## 4. PrintFunctor
*`Functors.h::PrintFunctor` -- stateless, prints each value, same behavior as inorder()*

![PrintFunctor](svgs/functor_print.svg)

---

## 5. SumFunctor
*`Functors.h::SumFunctor` -- stateful, accumulates a running total across every call*

![SumFunctor](svgs/functor_sum.svg)

---

## 6. CountFunctor
*`Functors.h::CountFunctor` -- stateful, counts nodes visited, ignores the actual values*

![CountFunctor](svgs/functor_count.svg)
