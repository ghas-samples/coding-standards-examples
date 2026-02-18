/**
 * @file cert_cpp_violations.cpp
 * @brief Intentional SEI CERT C++ violations for training purposes.
 *
 * Each violation is annotated with the CERT rule it violates.
 * These examples demonstrate what CodeQL's codeql/cert-cpp-coding-standards
 * pack will detect when run against this code.
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

/* ============================================================
 * CERT C++ ERR50-CPP — Do not abruptly terminate the program
 * ============================================================ */
void cert_err50_cpp() {
    std::abort();  // Abrupt termination skips destructors & cleanup
}

/* ============================================================
 * CERT C++ ERR58-CPP — Handle all exceptions thrown before main()
 * begins executing
 * ============================================================ */
std::string global_str = []() -> std::string {
    throw std::runtime_error("init error");  // Thrown during static init
    return "ok";
}();

/* ============================================================
 * CERT C++ DCL50-CPP — Do not define a C-style variadic function
 * ============================================================ */
int cert_dcl50_cpp(int count, ...) {  // C-style variadic — prohibited
    return count;
}

/* ============================================================
 * CERT C++ OOP57-CPP — Prefer special member functions and
 * overloaded operators to C Standard Library functions
 * ============================================================ */
struct SimpleData {
    int x;
    int y;
};

void cert_oop57_cpp() {
    SimpleData a = {1, 2};
    SimpleData b;
    std::memcpy(&b, &a, sizeof(SimpleData));  // Should use copy constructor
    static_cast<void>(b);
}

/* ============================================================
 * CERT C++ EXP55-CPP — Do not access a cv-qualified object
 * through a cv-unqualified type
 * ============================================================ */
void cert_exp55_cpp() {
    const int ci = 42;
    int *ip = const_cast<int *>(&ci);
    *ip = 0;  // Modifying a const object — undefined behavior
    static_cast<void>(*ip);
}

/* ============================================================
 * CERT C++ CTR50-CPP — Guarantee that container indices and
 * iterators are within the valid range
 * ============================================================ */
void cert_ctr50_cpp() {
    std::vector<int> vec = {1, 2, 3};
    int val = vec[5];  // Out-of-bounds access
    static_cast<void>(val);
}

/* ============================================================
 * CERT C++ MEM52-CPP — Detect and handle memory allocation errors
 * ============================================================ */
void cert_mem52_cpp() {
    // nothrow new can return nullptr
    int *p = new (std::nothrow) int[1000000000];
    *p = 42;  // Missing null check — potential nullptr dereference
    delete[] p;
}

/* ============================================================
 * CERT C++ ERR61-CPP — Catch exceptions by lvalue reference
 * ============================================================ */
void cert_err61_cpp() {
    try {
        throw std::runtime_error("error");
    } catch (std::exception e) {  // Caught by value — causes object slicing
        static_cast<void>(e.what());
    }
}

/* ============================================================
 * CERT C++ MSC50-CPP — Do not use std::rand() for generating
 * pseudorandom numbers
 * ============================================================ */
void cert_msc50_cpp() {
    int r = std::rand();  // std::rand() is not cryptographically secure
    static_cast<void>(r);
}

/* ============================================================
 * CERT C++ OOP51-CPP — Do not slice derived objects
 * ============================================================ */
class Base {
public:
    virtual ~Base() = default;
    virtual int value() const { return 0; }
};

class Derived : public Base {
    int extra_ = 42;
public:
    int value() const override { return extra_; }
};

void process_by_value(Base b) {  // Slicing: Derived -> Base
    static_cast<void>(b.value());
}

void cert_oop51_cpp() {
    Derived d;
    process_by_value(d);  // Object slicing occurs here
}

/* ============================================================
 * Helper: entry point.
 * ============================================================ */
int main() {
    // cert_err50_cpp();  // Would terminate — commented for demo
    cert_dcl50_cpp(1, 2, 3);
    cert_oop57_cpp();
    cert_exp55_cpp();
    cert_ctr50_cpp();
    cert_mem52_cpp();
    cert_err61_cpp();
    cert_msc50_cpp();
    cert_oop51_cpp();
    return 0;
}
