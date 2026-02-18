/**
 * @file misra_violations.c
 * @brief Intentional MISRA C 2012 violations for training purposes.
 *
 * Each violation is annotated with the MISRA rule it violates.
 * These examples demonstrate what CodeQL's codeql/misra-c-coding-standards
 * pack will detect when run against this code.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ============================================================
 * MISRA C 2012 Rule 2.2 — No dead code
 * There shall be no dead code.
 * ============================================================ */
void misra_rule_2_2(void) {
    int x = 10;
    x = 20;   /* First assignment is dead — never read before overwrite */
    (void)x;
}

/* ============================================================
 * MISRA C 2012 Rule 8.4 — Compatible declaration before definition
 * A compatible declaration shall be visible when a function with
 * external linkage is defined.
 * ============================================================ */
/* No prior declaration — violates Rule 8.4 */
int misra_rule_8_4_func(int a) {
    return a + 1;
}

/* ============================================================
 * MISRA C 2012 Rule 10.1 — Operands of inappropriate essential type
 * Operands shall not be of an inappropriate essential type category.
 * ============================================================ */
void misra_rule_10_1(void) {
    char c = 'A';
    int result = c << 2;  /* Shift of essentially character type */
    (void)result;
}

/* ============================================================
 * MISRA C 2012 Rule 10.3 — Narrow assignment
 * The value of an expression shall not be assigned to an object of a
 * narrower essential type or of a different essential type category.
 * ============================================================ */
void misra_rule_10_3(void) {
    int i = 42;
    short s = i;  /* Implicit narrowing from int to short */
    (void)s;
}

/* ============================================================
 * MISRA C 2012 Rule 11.3 — Cast between pointer to object and pointer
 * to different object type
 * ============================================================ */
void misra_rule_11_3(void) {
    int i = 0x12345678;
    char *cp = (char *)&i;  /* Cast between incompatible pointer types */
    (void)cp;
}

/* ============================================================
 * MISRA C 2012 Rule 12.1 — Precedence of operators
 * The precedence of operators within expressions should be made explicit.
 * ============================================================ */
void misra_rule_12_1(void) {
    int a = 1, b = 2, c = 3;
    int result = a + b << c;  /* Ambiguous precedence without parentheses */
    (void)result;
}

/* ============================================================
 * MISRA C 2012 Rule 14.4 — Controlling expression of if/while is boolean
 * The controlling expression of an if statement and iteration statements
 * shall have essentially Boolean type.
 * ============================================================ */
void misra_rule_14_4(void) {
    int x = 1;
    if (x) {  /* x is not essentially Boolean */
        x = 0;
    }
}

/* ============================================================
 * MISRA C 2012 Rule 15.6 — Compound statement required for loops/if
 * The body of an iteration-statement or a selection-statement shall be
 * a compound statement.
 * ============================================================ */
void misra_rule_15_6(void) {
    int i;
    for (i = 0; i < 10; i++)
        i++;  /* Loop body is not a compound statement (no braces) */
}

/* ============================================================
 * MISRA C 2012 Rule 17.7 — Return value of non-void function used
 * The value returned by a function having non-void return type shall
 * be used.
 * ============================================================ */
void misra_rule_17_7(void) {
    char buf[64];
    memset(buf, 0, sizeof(buf));
    strlen(buf);  /* Return value of strlen is discarded */
}

/* ============================================================
 * MISRA C 2012 Rule 21.3 — Memory allocation/deallocation not used
 * The memory allocation and deallocation functions of <stdlib.h> shall
 * not be used.
 * ============================================================ */
void misra_rule_21_3(void) {
    int *p = (int *)malloc(sizeof(int) * 10);  /* Dynamic allocation prohibited */
    if (p != NULL) {
        free(p);  /* free also prohibited */
    }
}

/* ============================================================
 * MISRA C 2012 Rule 21.6 — Standard I/O not used
 * The Standard Library input/output functions shall not be used.
 * ============================================================ */
void misra_rule_21_6(void) {
    printf("This should not be used in safety-critical code\n");
}

/* ============================================================
 * MISRA C 2012 Dir 4.6 — Use typedefs for basic numerical types
 * typedefs that indicate size and signedness should be used in place
 * of the basic numerical types.
 * ============================================================ */
void misra_dir_4_6(void) {
    int x = 42;            /* Should use int32_t or similar */
    unsigned long y = 100u; /* Should use uint32_t / uint64_t */
    (void)x;
    (void)y;
}

/* ============================================================
 * MISRA C 2012 Rule 8.7 — Object/function scope
 * Functions and objects should not be defined with external linkage
 * if they are referenced in only one translation unit.
 * ============================================================ */
int misra_rule_8_7_global = 42;  /* External linkage but only used here */

/* ============================================================
 * Helper: entry point to prevent "unused function" warnings.
 * ============================================================ */
int main(void) {
    misra_rule_2_2();
    (void)misra_rule_8_4_func(1);
    misra_rule_10_1();
    misra_rule_10_3();
    misra_rule_11_3();
    misra_rule_12_1();
    misra_rule_14_4();
    misra_rule_15_6();
    misra_rule_17_7();
    misra_rule_21_3();
    misra_rule_21_6();
    misra_dir_4_6();
    return 0;
}
