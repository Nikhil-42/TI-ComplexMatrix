#include <ti/real>

using namespace ti::literals;

bool operator==(const real_t& lhs, const real_t& rhs) {
    return os_RealCompare(&lhs, &rhs) == 0;
};

bool operator!=(const real_t& lhs, const real_t& rhs) {
    return os_RealCompare(&lhs, &rhs) != 0;
}

bool operator<(const real_t& lhs, const real_t& rhs) {
    return os_RealCompare(&lhs, &rhs) < 0;
};

bool operator<=(const real_t& lhs, const real_t& rhs) {
    return os_RealCompare(&lhs, &rhs) <= 0;
};

bool operator>(const real_t& lhs, const real_t& rhs) {
    return os_RealCompare(&lhs, &rhs) > 0;
};

bool operator>=(const real_t& lhs, const real_t& rhs) {
    return os_RealCompare(&lhs, &rhs) >= 0;
};

real_t operator+(const real_t& lhs, const real_t& rhs)
{
    return os_RealAdd(&lhs, &rhs);
};

real_t operator-(const real_t& lhs, const real_t& rhs) {
    return os_RealSub(&lhs, &rhs);
};

real_t operator*(const real_t& lhs, const real_t& rhs) {
    return os_RealMul(&lhs, &rhs);
};

real_t operator/(const real_t& lhs, const real_t& rhs) {
    return os_RealDiv(&lhs, &rhs);
};

real_t operator-(const real_t& unary) {
    return os_RealNeg(&unary);
};

real_t& operator+=(real_t& lhs, const real_t& rhs) {
    lhs = lhs + rhs;
    return lhs;
};

real_t& operator-=(real_t& lhs, const real_t& rhs) {
    lhs = lhs - rhs;
    return lhs;
};

real_t& operator*=(real_t& lhs, const real_t& rhs) {
    lhs = lhs * rhs;
    return lhs;
};

real_t& operator/=(real_t& lhs, const real_t& rhs) {
    lhs = lhs / rhs;
    return lhs;
};

cplx_t operator+(const cplx_t& lhs, const cplx_t& rhs)
{
    return cplx_t{lhs.real + rhs.real, lhs.imag + rhs.imag};
};

cplx_t operator-(const cplx_t& lhs, const cplx_t& rhs)
{
    return cplx_t{lhs.real - rhs.real, lhs.imag - rhs.imag};
};

cplx_t operator*(const cplx_t& lhs, const cplx_t& rhs) {
    return cplx_t{lhs.real * rhs.real - lhs.imag * rhs.imag, lhs.real * rhs.imag + lhs.imag * rhs.real};
};

cplx_t operator/(const cplx_t& lhs, const real_t& rhs) {
    return cplx_t{lhs.real / rhs, lhs.imag / rhs};
};

cplx_t operator/(const cplx_t& lhs, const cplx_t& rhs) {
    return lhs * cplx_t{rhs.real, -rhs.imag} / (rhs.real * rhs.real + rhs.imag * rhs.imag);
};

cplx_t operator-(const cplx_t& unary) {
    return cplx_t{-unary.real, -unary.imag};
};

cplx_t operator+=(cplx_t& lhs, const cplx_t& rhs) {
    lhs = lhs + rhs;
    return lhs;
};

cplx_t operator-=(cplx_t& lhs, const cplx_t& rhs) {
    lhs = lhs - rhs;
    return lhs;
};

cplx_t operator*=(cplx_t& lhs, const cplx_t& rhs) {
    lhs = lhs * rhs;
    return lhs;
};

cplx_t operator/= (cplx_t& lhs, const real_t& rhs) {
    lhs = lhs / rhs;
    return lhs;
};

cplx_t operator/=(cplx_t& lhs, const cplx_t& rhs) {
    lhs = lhs / rhs;
    return lhs;
};
