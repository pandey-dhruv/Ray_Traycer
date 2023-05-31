#ifndef VEC3_H
#define VEC3_H
#include <cmath>
#include <iostream>
#include "rt_weekend.h"
using namespace std;

// defining a class vec3
class vec3
{
public:
    double e[3];
    // all members of a class are private unless defined otherwise
public:
    vec3(); // default constructor
    vec3(double e0, double e1, double e2);
    // functions to return the x,y,z coordinates respectively
    double x() const;
    double y() const;
    double z() const;
    // the const keyword after the x() means that the function is not allowed to change the data members
    // of the class or struct

    vec3 operator-() const;
    double operator[](int i) const;
    double &operator[](int i);
    // this double& return a reference to the actual variable instead of returning a copy of the value

    // function to add a vector to itself
    void operator+=(const vec3 &vector);
    // function to multiply a vector itself by a scalar
    void operator*=(const double t);
    // function to divide a vector itself by a scalar
    void operator/=(const double t);
    // funtion to return the length of the vector
    double length() const;
    double length_squared() const;
    // random functions
    inline static vec3 random()
    {
        return vec3(random_double(), random_double(), random_double());
    }
    inline static vec3 random(double rand_max, double rand_min)
    {
        return vec3(random_double(rand_min, rand_max), random_double(rand_min, rand_max), random_double(rand_min, rand_max));
    }
    bool near_zero() const;
};
using point3 = vec3;
using color = vec3;
/*When the program executes the function call instruction the CPU stores the memory address of the
instruction following the function call, copies the arguments of the function on the stack, and finally
transfers control to the specified function. The CPU then executes the function code, stores the function
return value in a predefined memory location/register, and returns control to the calling function. This can
become overhead if the execution time of the function is less than the switching time from the caller
function to called function (callee).
For functions that are large and/or perform complex tasks, the overhead of the function call is usually
insignificant compared to the amount of time the function takes to run. However, for small, commonly-used
functions, the time needed to make the function call is often a lot more than the time needed to actually
execute the function’s code. This overhead occurs for small functions because the execution time of a small
function is less than the switching time.*/

// inline function is basically a request to the compiler and not a command and can be denied in the following-
/*1. If the function contains a loop, switch or goto statement
  2. If the function is recursive.
  3. If the function is non-void but does not contain a return statement*/

// inline function declarations
inline vec3 operator+(const vec3 &a, const vec3 &b)
{
    return vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}
inline vec3 operator*(const vec3 &a, const double &t)
{
    return vec3(t * a[0], t * a[1], t * a[2]);
}
inline std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2] << "\n";
}
inline vec3 operator-(const vec3 &a, const vec3 &b)
{
    return vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}
inline vec3 operator*(const double &t, const vec3 &a)
{
    return a * t;
}
inline vec3 operator/(const vec3 &a, const double &t)
{
    return vec3(a[0] / t, a[1] / t, a[2] / t);
}
inline vec3 operator/(const double &t, const vec3 &a)
{
    return a / t;
}
inline vec3 cross(const vec3 &u, const vec3 &v)
{
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
inline auto dot(const vec3 &u, const vec3 &v)
{
    return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}
vec3 random_in_unit_sphere();
vec3 random_unit_vector();
inline vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}
// defining a function to simulate refraction
inline vec3 refract(const vec3 &i, const vec3 &normal, const double etai_over_etar)
{
    auto cos_theta = fmin(dot(-i, normal), 1.0);
    // component of the ray perpendicular to the normal to the interface seperating the 2 media
    vec3 ray_perp = etai_over_etar * (i + normal * cos_theta);
    vec3 ray_para = -sqrt(fabs(1 - ray_perp.length_squared())) * normal; // component paralled to the normal to the interface
    // seperating the 2 medium
    return ray_perp + ray_para;
}
vec3 random_in_unit_disk();
#endif