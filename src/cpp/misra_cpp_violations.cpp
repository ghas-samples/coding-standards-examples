/**
 * @file misra_cpp_violations.cpp
 * @brief Intentional MISRA C++ violations for training purposes.
 *
 * These examples target rules from MISRA C++ 2008 / the C++ rules
 * within the codeql/misra-cpp-coding-standards pack (which includes
 * MISRA C++ guidelines applied to C++14 code via the CodeQL
 * Coding Standards).
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

/* ============================================================
 * MISRA C++ Rule 0-1-1 — A project shall not contain unreachable code
 * ============================================================ */
int misra_cpp_0_1_1(int x) {
    return x;
    int y = 10;  // Unreachable code
    return y;
}

/* ============================================================
 * MISRA C++ Rule 2-10-2 — Identifiers declared in an inner scope
 * shall not hide identifiers from an outer scope.
 * ============================================================ */
int outer_var = 10;

void misra_cpp_2_10_2() {
    int outer_var = 20;  // Shadows global outer_var
    static_cast<void>(outer_var);
}

/* ============================================================
 * MISRA C++ Rule 5-0-3 — A cvalue expression shall not be
 * implicitly converted to a different underlying type.
 * ============================================================ */
void misra_cpp_5_0_3() {
    int i = 100;
    double d = i;  // Implicit widening conversion
    static_cast<void>(d);
}

/* ============================================================
 * MISRA C++ Rule 5-2-4 — C-style casts and functional notation
 * casts shall not be used.
 * ============================================================ */
void misra_cpp_5_2_4() {
    double pi = 3.14;
    int truncated = (int)pi;  // C-style cast
    static_cast<void>(truncated);
}

/* ============================================================
 * MISRA C++ Rule 6-4-2 — All if … else if constructs shall be
 * terminated with an else clause.
 * ============================================================ */
void misra_cpp_6_4_2(int x) {
    if (x == 1) {
        // case 1
    } else if (x == 2) {
        // case 2
    }
    // Missing final else clause
}

/* ============================================================
 * MISRA C++ Rule 6-6-5 — A function shall have a single point of exit
 * at the end of the function.
 * ============================================================ */
int misra_cpp_6_6_5(int x) {
    if (x > 0) {
        return 1;  // Early return #1
    }
    if (x < 0) {
        return -1;  // Early return #2
    }
    return 0;  // Normal return
}

/* ============================================================
 * MISRA C++ Rule 15-3-5 — A class type exception shall always
 * be caught by reference.
 * ============================================================ */
void misra_cpp_15_3_5() {
    try {
        throw 42;
    } catch (int) {  // Catching non-class type
        // ...
    }
}

/* ============================================================
 * MISRA C++ Rule 18-0-1 — The C library shall not be used.
 * (C Standard Library functions)
 * ============================================================ */
void misra_cpp_18_0_1() {
    char src[] = "hello";
    char dst[10];
    std::strcpy(dst, src);  // Using C library function strcpy
    static_cast<void>(dst);
}

/* ============================================================
 * MISRA C++ Rule 18-4-1 — Dynamic heap memory allocation shall
 * not be used.
 * ============================================================ */
void misra_cpp_18_4_1() {
    int *p = new int(42);  // Dynamic allocation prohibited
    delete p;
}

/* ============================================================
 * MISRA C++ Rule 27-0-1 — The stream input/output library
 * <cstdio> shall not be used.
 * ============================================================ */
void misra_cpp_27_0_1() {
    std::printf("Using cstdio is a MISRA violation\n");
}

/* ============================================================
 * Helper: entry point.
 * ============================================================ */
int main() {
    static_cast<void>(misra_cpp_0_1_1(5));
    misra_cpp_2_10_2();
    misra_cpp_5_0_3();
    misra_cpp_5_2_4();
    misra_cpp_6_4_2(1);
    static_cast<void>(misra_cpp_6_6_5(5));
    misra_cpp_15_3_5();
    misra_cpp_18_0_1();
    misra_cpp_18_4_1();
    misra_cpp_27_0_1();
    return 0;
}
