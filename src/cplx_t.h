#include <ti/real>

using namespace ti::literals;

bool operator==(const real_t& lhs, const real_t& rhs);
bool operator!=(const real_t& lhs, const real_t& rhs);
bool operator<(const real_t& lhs, const real_t& rhs);
bool operator<=(const real_t& lhs, const real_t& rhs);
bool operator>(const real_t& lhs, const real_t& rhs);
bool operator>=(const real_t& lhs, const real_t& rhs);

real_t operator+(const real_t& lhs, const real_t& rhs);
real_t operator-(const real_t& lhs, const real_t& rhs);
real_t operator*(const real_t& lhs, const real_t& rhs);
real_t operator/(const real_t& lhs, const real_t& rhs);
real_t operator-(const real_t& unary);

real_t operator+=(real_t& lhs, const real_t& rhs);
real_t operator-=(real_t& lhs, const real_t& rhs);
real_t operator*=(real_t& lhs, const real_t& rhs);
real_t operator/=(real_t& lhs, const real_t& rhs);

bool operator==(const cplx_t& lhs, const cplx_t& rhs);
bool operator!=(const cplx_t& lhs, const cplx_t& rhs);

cplx_t operator+(const cplx_t& lhs, const cplx_t& rhs);
cplx_t operator-(const cplx_t& lhs, const cplx_t& rhs);
cplx_t operator*(const cplx_t& lhs, const cplx_t& rhs);
cplx_t operator/(const cplx_t& lhs, const real_t& rhs);
cplx_t operator/(const cplx_t& lhs, const cplx_t& rhs);
cplx_t operator-(const cplx_t& unary);

cplx_t operator+=(cplx_t& lhs, const cplx_t& rhs);
cplx_t operator-=(cplx_t& lhs, const cplx_t& rhs);
cplx_t operator*=(cplx_t& lhs, const cplx_t& rhs);
cplx_t operator/=(cplx_t& lhs, const real_t& rhs);
cplx_t operator/=(cplx_t& lhs, const cplx_t& rhs);