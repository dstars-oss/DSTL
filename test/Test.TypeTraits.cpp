/*++

Copyright (c) 2024.  D.Stars <d.stars@163.com>
All rights reserved.

Module Name:
    Test.TypeTraits.cpp

Abstract:
    Test Traits Type.

--*/

#include "doctest.h"

#include "DSTL.hpp"
using namespace dstl;

union test_union
{
    int i_;
    double f_;
};

class test_class
{
private:
    int val_ = 0;

public:
    int public_val_ = 0;

    void member_func () { ++val_; }
    static void static_member_func (const char *msg) { (void) msg; }
};

void test_global_func (const char *msg) { (void) msg; }

TEST_CASE("checks if a type is void")
{

    CHECK(is_void_v<void>);
    CHECK(is_void_v<const void>);
    CHECK(is_void_v<volatile void>);
    CHECK(!is_void_v<void*>);
    CHECK(!is_void_v<int>);
    CHECK(!is_void_v<decltype(test_global_func)>);
    CHECK(!is_void_v<is_void<void>>);
}

TEST_CASE("checks if a type is nullptr_t")
{
    CHECK(is_null_pointer_v<decltype(nullptr)>);
    CHECK(!is_null_pointer_v<int*>);
}

TEST_CASE("checks if a type is an integral type")
{
    CHECK(is_integral_v<char>);
    CHECK(is_integral_v<wchar_t>);
    CHECK(is_integral_v<short>);
    CHECK(is_integral_v<int>);
    CHECK(is_integral_v<long>);
    CHECK(is_integral_v<long long>);
    CHECK(is_integral_v<unsigned char>);
    CHECK(is_integral_v<unsigned short>);
    CHECK(is_integral_v<unsigned int>);
    CHECK(is_integral_v<unsigned long>);
    CHECK(is_integral_v<unsigned long long>);

    CHECK(!is_integral_v<float>);
    CHECK(!is_integral_v<double>);
    CHECK(!is_integral_v<long double>);
}

TEST_CASE("checks if a type is a floating-point type")
{
    CHECK(!is_floating_point_v<char>);
    CHECK(!is_floating_point_v<wchar_t>);
    CHECK(!is_floating_point_v<short>);
    CHECK(!is_floating_point_v<int>);
    CHECK(!is_floating_point_v<long>);
    CHECK(!is_floating_point_v<long long>);
    CHECK(!is_floating_point_v<unsigned char>);
    CHECK(!is_floating_point_v<unsigned short>);
    CHECK(!is_floating_point_v<unsigned int>);
    CHECK(!is_floating_point_v<unsigned long>);
    CHECK(!is_floating_point_v<unsigned long long>);

    CHECK(is_floating_point_v<float>);
    CHECK(is_floating_point_v<double>);
    CHECK(is_floating_point_v<long double>);
}

TEST_CASE("checks if a type is an array type")
{
    CHECK(!is_array<test_class>::value);
    CHECK(is_array<test_class[]>::value);
    CHECK(is_array<test_class[3]>::value);
    CHECK(!is_array<float>::value);
    CHECK(!is_array<int>::value);
    CHECK(is_array<int[]>::value);
    CHECK(is_array<int[3]>::value);
}

TEST_CASE("checks if a type is a pointer type")
{
    CHECK(!is_pointer<test_class>::value);
    CHECK(!is_pointer_v<test_class>);
    CHECK(!is_pointer<test_class>());
    CHECK(!is_pointer<test_class>{});
    CHECK(!is_pointer<test_class>()());
    CHECK(!is_pointer<test_class>{}());
    CHECK(is_pointer_v<test_class*>);
    CHECK(is_pointer_v<test_class const* volatile>);
    CHECK(!is_pointer_v<test_class&>);
    CHECK(is_pointer_v<void*>);
    CHECK(!is_pointer_v<int>);
    CHECK(is_pointer_v<int*>);
    CHECK(is_pointer_v<int**>);
    CHECK(!is_pointer_v<int[10]>);
    CHECK(!is_pointer_v<decltype(nullptr)>);
    CHECK(is_pointer_v<void (*)()>);
}

TEST_CASE("checks if a type is a lvalue reference")
{
    CHECK(is_lvalue_reference_v<test_class> == false);
    CHECK(is_lvalue_reference_v<test_class&> == true);
    CHECK(is_lvalue_reference_v<test_class&&> == false);

    CHECK(is_lvalue_reference_v<int> == false);
    CHECK(is_lvalue_reference_v<int&> == true);
    CHECK(is_lvalue_reference_v<int&&> == false);
}

TEST_CASE("checks if a type is a rvalue reference")
{
    CHECK(is_rvalue_reference_v<test_class> == false);
    CHECK(is_rvalue_reference_v<test_class&> == false);
    CHECK(is_rvalue_reference_v<test_class&&> != false);
    CHECK(is_rvalue_reference_v<char> == false);
    CHECK(is_rvalue_reference_v<char&> == false);
    CHECK(is_rvalue_reference_v<char&&> != false);

}

TEST_CASE("checks if a type is a pointer to a non-static member object")
{
    CHECK(is_member_object_pointer_v<int(test_class::*)>);
    CHECK(!is_member_object_pointer_v<int(test_class::*)()>);
}

TEST_CASE("	checks if a type is a enumeration/union /class type")
{
    enum e { e_ };
    CHECK(is_enum_v<e>);

    CHECK(is_union_v<test_union>);
    CHECK(is_class_v<test_class>);
}

TEST_CASE("checks if a type is a pointer to a non-static member function")
{
    // fails at compile time if A::member is a data member and not a function
    CHECK(is_member_function_pointer_v<decltype(&test_class::member_func)>);
}

TEST_CASE("checks if a type is an enumeration type")
{
    enum e1 { e1_ };
    enum class e2 { e2_ };

    CHECK(is_enum_v<e1>);
    CHECK(is_enum_v<e2>);
    CHECK(!is_enum_v<test_union>);
    CHECK(!is_enum_v<test_class>);
}

TEST_CASE("checks if a type is a union type")
{
    CHECK(is_union_v<test_union>);
    CHECK(!is_union_v<test_class>);
}

TEST_CASE("checks if a type is a non-union class type")
{
    CHECK(is_class_v<test_class>);
    CHECK(!is_class_v<test_class*>);
    CHECK(!is_class_v<test_class&>);
    CHECK(is_class_v<const test_class>);
}

TEST_CASE("checks if a type is either a lvalue reference or rvalue reference")
{
    CHECK(!is_reference_v<test_class>);
    CHECK(is_reference_v<test_class&>);
    CHECK(is_reference_v<test_class&&>);
    CHECK(!is_reference_v<long>);
    CHECK(is_reference_v<long&>);
    CHECK(is_reference_v<long&&>);
    CHECK(!is_reference_v<double*>);
    CHECK(is_reference_v<double*&>);
    CHECK(is_reference_v<double*&&>);;
}

TEST_CASE("checks if a type is an arithmetic type")
{
    CHECK(is_arithmetic_v<bool> == true);
    CHECK(is_arithmetic_v<char> == true);
    CHECK(is_arithmetic_v<char const> == true);
    CHECK(is_arithmetic_v<int> == true);
    CHECK(is_arithmetic_v<int const> == true);
    CHECK(is_arithmetic_v<float> == true);
    CHECK(is_arithmetic_v<float const> == true);
    CHECK(is_arithmetic_v<size_t> == true);
    CHECK(is_arithmetic_v<char&> == false);
    CHECK(is_arithmetic_v<char*> == false);
    CHECK(is_arithmetic_v<int&> == false);
    CHECK(is_arithmetic_v<int*> == false);
    CHECK(is_arithmetic_v<float&> == false);
    CHECK(is_arithmetic_v<float*> == false);
    CHECK(is_arithmetic_v<test_class> == false);

    enum class e : int { e_ };
    CHECK(is_arithmetic_v<e> == false);
    CHECK(is_arithmetic_v<decltype(e::e_)> == false);
}

TEST_CASE("checks if a type is a fundamental type")
{
    CHECK(is_fundamental_v<int> == true);
    CHECK(is_fundamental_v<int&> == false);
    CHECK(is_fundamental_v<int*> == false);
    CHECK(is_fundamental_v<void> == true);
    CHECK(is_fundamental_v<void*> == false);
    CHECK(is_fundamental_v<float> == true);
    CHECK(is_fundamental_v<float&> == false);
    CHECK(is_fundamental_v<float*> == false);
    CHECK(is_fundamental_v<decltype(nullptr)> == true);
    CHECK(is_fundamental_v<is_fundamental<int>> == false);
    CHECK(is_fundamental_v<test_class> == false);
    CHECK(is_fundamental_v<is_fundamental<test_class>::value_type>);
}

TEST_CASE("checks if a type is a scalar type")
{
    CHECK(is_scalar_v<int> == true);
    CHECK(is_scalar_v<float> == true);
    CHECK(is_scalar_v<double> == true);
    CHECK(is_scalar_v<const char*> == true);
    CHECK(is_scalar_v<decltype(test_class::public_val_)> == true);
    CHECK(is_scalar_v<decltype(&test_class::public_val_)> == true);
    CHECK(is_scalar_v<decltype(nullptr)> == true);
    CHECK(is_scalar_v<test_class> == false);
}

TEST_CASE("checks if a type is an object type")
{
    CHECK(!is_object_v<void>);
    CHECK(is_object_v<int>);
    CHECK(!is_object_v<int&>);
    CHECK(is_object_v<int*>);
    CHECK(!is_object_v<int*&>);
    CHECK(is_object_v<test_class>);
    CHECK(!is_object_v<test_class&>);
    CHECK(is_object_v<test_class*>);
    CHECK(!is_object_v<int()>);
    CHECK(is_object_v<int(*)()>);
    CHECK(!is_object_v<int(&)()>);
}

TEST_CASE("checks if a type is a compound type")
{
    CHECK(!is_compound_v<int>);
    CHECK(is_compound_v<int*>);
    CHECK(is_compound_v<int&>);
    CHECK(is_compound_v<decltype(test_global_func)>);
    CHECK(is_compound_v<decltype(&test_global_func)>);
    CHECK(is_compound_v<char[100]>);
    CHECK(is_compound_v<test_class>);
    CHECK(is_compound_v<test_union>);
 
    enum struct E { e };
    CHECK(is_compound_v<E>);
    CHECK(is_compound_v<decltype(E::e)>);
    
    CHECK(!is_compound_v<decltype(test_class::public_val_)>);
    CHECK(is_compound_v<decltype(&test_class::public_val_)>);
    CHECK(is_compound_v<decltype(&test_class::member_func)>);
}

TEST_CASE("checks if a type is a pointer to a non-static member function or object")
{
    CHECK(!is_member_pointer_v<int*>);

    using mem_int_ptr_t = int test_class::*;
    using mem_fun_ptr_t = void (test_class::*) () ;
    CHECK(is_member_pointer_v<mem_int_ptr_t>);
    CHECK(is_member_pointer_v<mem_fun_ptr_t>);

    CHECK(!is_member_pointer_v<decltype(test_class::static_member_func)>);
}

TEST_CASE("checks if a type is const-qualified")
{
    CHECK(!is_const_v<int>);
    CHECK(is_const_v<const int>);
    CHECK(!is_const_v<int*>);
    CHECK(is_const_v<int* const>);
    CHECK(!is_const_v<const int*>);
    CHECK(!is_const_v<const int&>);
}

TEST_CASE("checks if a type is volatile-qualified")
{
    CHECK(!is_volatile_v<int>);
    CHECK(is_volatile_v<volatile int>);
    CHECK(is_volatile_v<volatile const int>);
}
