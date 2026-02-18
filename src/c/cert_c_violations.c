/**
 * @file cert_c_violations.c
 * @brief Intentional SEI CERT C violations for training purposes.
 *
 * Each violation is annotated with the CERT rule it violates.
 * These examples demonstrate what CodeQL's codeql/cert-c-coding-standards
 * pack will detect when run against this code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/* ============================================================
 * CERT C EXP30-C — Do not depend on the order of evaluation of
 * operands or side effects
 * ============================================================ */
void cert_exp30_c(void) {
    int i = 0;
    int arr[5] = {0};
    arr[i] = i++;  /* Undefined behavior: i read and modified in same expression */
    (void)arr;
}

/* ============================================================
 * CERT C EXP33-C — Do not read uninitialized memory
 * ============================================================ */
void cert_exp33_c(void) {
    int x;
    int y = x + 1;  /* Reading uninitialized variable 'x' */
    (void)y;
}

/* ============================================================
 * CERT C ARR30-C — Do not form or use out-of-bounds pointers or
 * array subscripts
 * ============================================================ */
void cert_arr30_c(void) {
    int arr[10];
    int val = arr[10];  /* Out-of-bounds access (valid indices: 0-9) */
    (void)val;
}

/* ============================================================
 * CERT C MEM30-C — Do not access freed memory
 * ============================================================ */
void cert_mem30_c(void) {
    int *p = (int *)malloc(sizeof(int));
    if (p == NULL) return;
    *p = 42;
    free(p);
    int val = *p;  /* Use-after-free */
    (void)val;
}

/* ============================================================
 * CERT C MEM35-C — Allocate sufficient memory for an object
 * ============================================================ */
void cert_mem35_c(void) {
    /* Allocating for int but trying to use as larger struct */
    struct large_struct {
        int data[100];
    };
    struct large_struct *p = (struct large_struct *)malloc(sizeof(int));
    if (p != NULL) {
        p->data[0] = 1;  /* Buffer overflow — not enough memory allocated */
        free(p);
    }
}

/* ============================================================
 * CERT C STR31-C — Guarantee that storage for strings has
 * sufficient space for character data and the null terminator
 * ============================================================ */
void cert_str31_c(void) {
    char buf[10];
    strcpy(buf, "This string is way too long for the buffer");  /* Buffer overflow */
}

/* ============================================================
 * CERT C ERR33-C — Detect and handle standard library errors
 * ============================================================ */
void cert_err33_c(void) {
    FILE *f = fopen("nonexistent.txt", "r");
    /* Missing NULL check — fopen can fail */
    fclose(f);  /* Potential NULL dereference */
}

/* ============================================================
 * CERT C SIG30-C — Call only asynchronous-safe functions within
 * signal handlers
 * ============================================================ */
void bad_signal_handler(int sig) {
    printf("Signal %d caught\n", sig);  /* printf is not async-signal-safe */
}

void cert_sig30_c(void) {
    signal(SIGINT, bad_signal_handler);
}

/* ============================================================
 * CERT C MSC32-C — Properly seed pseudorandom number generators
 * ============================================================ */
void cert_msc32_c(void) {
    int r = rand();  /* Using rand() without calling srand() first */
    (void)r;
}

/* ============================================================
 * CERT C INT31-C — Ensure integer conversions do not result in
 * lost or misinterpreted data
 * ============================================================ */
void cert_int31_c(void) {
    unsigned int u = 4294967295u;  /* UINT_MAX */
    int s = (int)u;               /* Signed overflow / data loss */
    (void)s;
}

/* ============================================================
 * CERT C DCL30-C — Declare objects with appropriate storage
 * durations
 * ============================================================ */
int *cert_dcl30_c(void) {
    int local_var = 42;
    return &local_var;  /* Returning address of local variable */
}

/* ============================================================
 * Helper: entry point to prevent "unused function" warnings.
 * ============================================================ */
int main(void) {
    cert_exp30_c();
    cert_exp33_c();
    cert_arr30_c();
    cert_mem30_c();
    cert_mem35_c();
    cert_str31_c();
    cert_err33_c();
    cert_sig30_c();
    cert_msc32_c();
    cert_int31_c();
    (void)cert_dcl30_c();
    return 0;
}
