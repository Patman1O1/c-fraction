// ISO Includes
#include <errno.h>
#include <stdlib.h>

// Local Includes
#include <fraction/fraction.h>

#ifdef __GNUC__
    #define gnu_likely(expr) __builtin_expect(!!(expr), 1)

    #define gnu_unlikely(expr) __builtin_expect(!!(expr), 0)
#else
    #define gnu_likely(expr)

    #define gnu_unlikely(expr)
#endif // #ifdef __GNUC__

static long long int gcd(long long int a, long long int b) {
    while (b != 0) {
        const long long int tmp = b;
        b = a % b;
        a = tmp;
    }
    return llabs(a);
}

int c_frac_simp(struct c_frac* const frac) {
    if (gnu_unlikely(frac->den == 0)) {
        errno = EINVAL;
        return -1;
    }

    const long long int common_factor = gcd(frac->num, frac->den);
    frac->num /= common_factor;
    frac->den /= common_factor;
    
    // Keep the negative sign in the numerator if the fraction is negative
    if (frac->den < 0) {
        frac->num = -frac->num;
        frac->den = -frac->den;
    }

    return 0;
}

