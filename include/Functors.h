#pragma once
#include <iostream>

// =============================================================================
// Functors (Function Objects)
// =============================================================================
//
// ? SEE DIAGRAM: images/functor_diagrams.md #1 — why no Functors.cpp?
// ? SEE DIAGRAM: images/functor_diagrams.md #2 — what is a functor?
// ? SEE DIAGRAM: images/functor_diagrams.md #3 — stateless vs stateful
//
// ! DISCUSSION: Functor overview.
//   - a functor is a struct that overloads operator() — callable like a function
//   - unlike a plain function, a functor can carry STATE between calls
//   - everything lives in this .h file — the structs are small and the
//     compiler needs to see operator() to generate template code
//

// ---------------------------------------------------------------------------
// PrintFunctor — prints each value followed by a space
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/functor_diagrams.md #4 — PrintFunctor trace
//
struct PrintFunctor {
    void operator()(int value) {
        std::cout << value << " ";
    }
};

// ---------------------------------------------------------------------------
// SumFunctor — accumulates the sum of all visited values
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/functor_diagrams.md #5 — SumFunctor trace
//
struct SumFunctor {
    int total = 0;
    void operator()(int value) {
        total += value;
    }
};

// ---------------------------------------------------------------------------
// CountFunctor — counts how many times operator() is called
// ---------------------------------------------------------------------------
//
// ? SEE DIAGRAM: images/functor_diagrams.md #6 — CountFunctor trace
//
struct CountFunctor {
    int count = 0;
    void operator()(int value) {
        (void)value;  // unused — we only care about the count
        count++;
    }
};
