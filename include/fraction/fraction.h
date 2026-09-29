#ifndef C_FRACTION_H
#define C_FRACTION_H

// ISO Includes
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

#define c_frac_new(num, den) (struct c_frac){num, den}

struct c_frac {
    long long int num;
    long long int den;
};

const struct c_frac C_FRAC_NAN = {.num=1, .den=0};

extern int c_frac_simp(struct c_frac* frac);

static inline bool c_frac_is_nan(const struct c_frac frac) {
    return frac.den == 0;
} 

static inline struct c_frac c_frac_add(
    const struct c_frac lhs,
    const struct c_frac rhs
) {
    return lhs.den != rhs.den
        ? c_frac_new(
            (lhs.num * rhs.den) + (rhs.num * lhs.den),
                        lhs.den * rhs.den
        )
        : c_frac_new(lhs.num + rhs.num, lhs.den);
}

static inline struct c_frac c_frac_sub(
    const struct c_frac lhs,
    const struct c_frac rhs
) {
    return lhs.den != rhs.den
        ? c_frac_new(
            (lhs.num * rhs.den) - (rhs.num * lhs.den),
                        lhs.den * rhs.den
        )
        : c_frac_new(lhs.num - rhs.num, lhs.den);
}

static inline struct c_frac c_frac_mul(
    const struct c_frac lhs,
    const struct c_frac rhs
) { return c_frac_new(lhs.num * rhs.num, lhs.den * rhs.den); }

static inline struct c_frac c_frac_div(
    const struct c_frac lhs,
    const struct c_frac rhs
) {
    // Use Keep Change Flip
    return c_frac_new(lhs.num * rhs.den, lhs.den * rhs.num);
}

static inline float c_frac_to_float(const struct c_frac frac) {
    return frac.den != 0
        ? (float)frac.num / (float)frac.den
        : NAN;
}

static inline double c_frac_to_double(const struct c_frac frac) {
    return frac.den != 0
        ? (double)frac.num / (double)frac.den
        : NAN;
}

static inline long double c_frac_to_ldouble(const struct c_frac frac) {
    return frac.den != 0
        ? (long double)frac.num / (long double)frac.den
        : NAN;
}

extern char* c_frac_to_str(struct c_frac frac, char* str, size_t len);

extern void c_frac_print(struct c_frac frac);

#ifdef __cplusplus
}
#endif // #ifdef __cplusplus

#endif // #ifndef C_FRACTION_H
