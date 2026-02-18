/**
 * @file autosar_violations.cpp
 * @brief Intentional AUTOSAR C++14 guideline violations for training purposes.
 *
 * Each violation is annotated with the AUTOSAR rule it violates.
 * These examples demonstrate what CodeQL's codeql/autosar-cpp-coding-standards
 * pack will detect when run against this code.
 */

#include <cstdlib>
#include <cstdio>
#include <memory>
#include <stdexcept>
#include <vector>

/* ============================================================
 * AUTOSAR A0-1-1 — A project shall not contain instances of
 * non-volatile variables given values that are not subsequently used.
 * ============================================================ */
void autosar_a0_1_1() {
    int x = 10;
    x = 20;  // First assignment (10) is never read — unused value
    static_cast<void>(x);
}

/* ============================================================
 * AUTOSAR A0-1-2 — The value returned by a function having a
 * non-void return type that is not an overloaded operator
 * shall be used.
 * ============================================================ */
int helper_returns_value() { return 42; }

void autosar_a0_1_2() {
    helper_returns_value();  // Return value discarded
}

/* ============================================================
 * AUTOSAR A2-10-1 — An identifier declared in an inner scope
 * shall not hide an identifier declared in an outer scope.
 * ============================================================ */
int shadow_var = 10;  // NOLINT — outer scope

void autosar_a2_10_1() {
    int shadow_var = 20;  // Shadows the global 'shadow_var'
    static_cast<void>(shadow_var);
}

/* ============================================================
 * AUTOSAR A5-1-1 — Literal values shall not be used apart from
 * type initialization, otherwise symbolic names shall be used.
 * (Magic numbers)
 * ============================================================ */
int autosar_a5_1_1(int input) {
    return input * 3600;  // Magic number 3600 (seconds in an hour)
}

/* ============================================================
 * AUTOSAR A7-1-5 — The auto specifier shall not be used apart
 * from … (limited contexts)
 * ============================================================ */
void autosar_a7_1_5() {
    auto x = 42;  // 'auto' hides the type — violation
    static_cast<void>(x);
}

/* ============================================================
 * AUTOSAR A11-0-2 — A type defined as struct shall only provide
 * public data members.
 * ============================================================ */
struct autosar_a11_0_2_struct {
private:
    int secret;  // Private member in a struct — violates A11-0-2
public:
    int visible;
    void set_secret(int v) { secret = v; }
};

/* ============================================================
 * AUTOSAR A15-1-2 — An exception object shall not be a pointer.
 * ============================================================ */
void autosar_a15_1_2() {
    try {
        throw new std::runtime_error("oops");  // Throwing a pointer — violates A15-1-2
    } catch (std::runtime_error *e) {
        delete e;
    }
}

/* ============================================================
 * AUTOSAR A18-1-1 — C-style arrays shall not be used.
 * ============================================================ */
void autosar_a18_1_1() {
    int arr[10] = {0};  // C-style array — should use std::array
    static_cast<void>(arr);
}

/* ============================================================
 * AUTOSAR A18-5-1 — Functions malloc, calloc, realloc and free
 * shall not be used.
 * ============================================================ */
void autosar_a18_5_1() {
    int *p = static_cast<int *>(std::malloc(sizeof(int) * 10));
    if (p != nullptr) {
        std::free(p);
    }
}

/* ============================================================
 * AUTOSAR M5-0-3 — A cvalue expression shall not be implicitly
 * converted to a different underlying type.
 * ============================================================ */
void autosar_m5_0_3() {
    int i = 42;
    double d = i;  // Implicit int -> double conversion
    static_cast<void>(d);
}

/* ============================================================
 * AUTOSAR A5-2-2 — Traditional C-style casts shall not be used.
 * ============================================================ */
void autosar_a5_2_2() {
    double pi = 3.14159;
    int truncated = (int)pi;  // C-style cast — should use static_cast
    static_cast<void>(truncated);
}

/* ============================================================
 * AUTOSAR A3-9-1 — Fixed width integer types from <cstdint>
 * shall be used instead of basic numerical types.
 * ============================================================ */
void autosar_a3_9_1() {
    int x = 42;            // Should use std::int32_t
    unsigned long y = 100; // Should use std::uint64_t
    static_cast<void>(x);
    static_cast<void>(y);
}

/* ============================================================
 * AUTOSAR M6-4-1 — An if-else-if construct shall be terminated
 * with an else clause.
 * ============================================================ */
void autosar_m6_4_1(int val) {
    if (val == 1) {
        // Handle 1
    } else if (val == 2) {
        // Handle 2
    }
    // Missing final 'else' clause
}

/* ============================================================
 * AUTOSAR A8-4-7 — "in" parameters for "cheap to copy" types
 * shall be passed by value. "in" parameters for "not cheap to
 * copy" types shall be passed by reference to const.
 * ============================================================ */
void autosar_a8_4_7(std::vector<int> data) {  // Large type by value — should be const&
    static_cast<void>(data.size());
}

/* ============================================================
 * Helper: entry point to call all violation functions.
 * ============================================================ */
int main() {
    autosar_a0_1_1();
    autosar_a0_1_2();
    autosar_a2_10_1();
    static_cast<void>(autosar_a5_1_1(10));
    autosar_a7_1_5();

    autosar_a11_0_2_struct s;
    s.visible = 1;
    s.set_secret(2);

    autosar_a18_1_1();
    autosar_a18_5_1();
    autosar_m5_0_3();
    autosar_a5_2_2();
    autosar_a3_9_1();
    autosar_m6_4_1(1);

    std::vector<int> v = {1, 2, 3};
    autosar_a8_4_7(v);

    return 0;
}
