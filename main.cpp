#include "fp.h"
#include "test_run.h"
#include "ops.h"

typedef fp::fp32<16> fph;

int main()
{
    test_run tr;

    fph a = 2;
    fph b = 4;
    fph c(2);
    fph d(4);
    fph e(2.0);
    fph f(4.0);

    tr.test(a != b);
    tr.test(a == c);
    tr.test(b != c);
    tr.test(b == d);
    tr.test(a == e);
    tr.test(b == f);

    tr.test(+a == 2);
    tr.test(-a == -2);

    tr.test(a + c == b);
    tr.test(b - c == a);
    tr.test(a * c == b);
    tr.test(b / c == a);

    tr.test(a < b);
    tr.test(a <= b);
    tr.test(b > a);
    tr.test(b >= a);

    // assignment ops
    a += 3;
    tr.test(a == 5);
    b -= 1;
    tr.test(b == 3);
    c *= 3;
    tr.test(c == 6);
    d /= 2;
    tr.test(d == 2);

    // pre/post increment
    tr.test(++e == 3);
    tr.test(e++ == 3);
    tr.test(e == 4);
    tr.test(--f == 3);
    tr.test(f-- == 3);
    tr.test(f == 2);

    // modulo
    tr.test(fph(5) % 2 == 1);
    tr.test(fph(2.75) % 0.5 == 0.25);

    tr.test(fph(5) * fph(10) == fph(50));
    tr.test(fph(5) * 10 == 50);
    tr.test(fph(2) == 2);
    tr.test(fph(4).fma(3,4) == 16);

    tr.test(fph(4).sqrt() == 2);
    tr.test(sqrt(fph(4)) == 2);

    tr.test(2 == fph(2));
    tr.test(2 != fph(3));
    tr.test(3 > fph(2));
    tr.test(3 >= fph(2));
    tr.test(2 < fph(3));
    tr.test(2 <= fph(3));
    tr.test(2 + fph(3) == 5);
    tr.test(2 - fph(3) == -1);
    tr.test(2 * fph(3) == 6);
    tr.test(6 / fph(3) == 2);
    tr.test(5 % fph(3) == 2);

    tr.test(fph(2.1) == 2.1);

    tr.test(ops::add(3,2) == 5);
    tr.test(ops::sub(3,2) == 1);
    tr.test(ops::mult(3,2) == 6);
    tr.test(ops::div(3,2) == 1.5);

    tr.test(fph(2.5).as_int() == 2);
    tr.test(fph(2.5).as_float() == 2.5f);
    tr.test(fph(2.5).as_double() == 2.5);
    const auto nd = fph(2.5).as_num_denom();
    tr.test((double)nd.first / nd.second == 2.5);

    tr.print();

    return 0;
}


