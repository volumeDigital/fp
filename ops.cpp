#include "ops.h"
#include "fp.h"

namespace ops {
typedef fp::fp32<16> fp_local;

double add(double lhs, double rhs) {
    const auto result = fp_local(lhs) + rhs;
    return result.as_double();
}

double sub(double lhs, double rhs) {
    const auto result = fp_local(lhs) - rhs;
    return result.as_double();
}
double mult(double lhs, double rhs) {
    const auto result = fp_local(lhs) * rhs;
    return result.as_double();
}
double div(double lhs, double rhs) {
    const auto result = fp_local(lhs) / rhs;
    return result.as_double();
}

}

