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

TEST_SUITE_BEGIN("TypeTraits");

struct test_empty_struct {};

struct test_struct
{
    int i_;
    double f_;
};

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

class test_standard_layout_class
{
private:
    int private_val_ = 0;

public:
    void member_func () { ++private_val_; }
    static void static_member_func (const char *msg) { (void) msg; }
};

class test_base_class
{
protected:
    int val_ = 0;

public:
    virtual ~test_base_class () = default;
    virtual void member_func () { ++val_; }

    [[nodiscard]] int get_val () const { return val_; }
};

class test_derived_class final : public test_base_class
{
public:
    void member_func () override
    {
        val_ += 10;
    }
};

class test_base_interface
{
protected:
    int val_ = 0;

public:
    virtual ~test_base_interface () = default;
    virtual void member_func () = 0;
};

class test_derived_interface final : public test_base_interface
{
public:
    void member_func () override
    {
        val_ += 10;
    }
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

TEST_CASE("checks if a type is a integral type")
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

TEST_CASE("checks if a type is a array type")
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

TEST_CASE("checks if a type is a enumeration/union /class type")
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

TEST_CASE("checks if a type is a enumeration type")
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

TEST_CASE("checks if a type is a arithmetic type")
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

TEST_CASE("checks if a type is a object type")
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

TEST_CASE("checks if a type is trivial")
{
    CHECK(is_trivial_v<test_union>);
    CHECK(is_trivial_v<test_struct>);
    CHECK(!is_trivial_v<test_class>);
    CHECK(!is_trivial_v<test_base_class>);
    CHECK(!is_trivial_v<test_derived_class>);
}

TEST_CASE("checks if a type is trivially copyable")
{
    CHECK(is_trivially_copyable_v<test_union>);
    CHECK(is_trivially_copyable_v<test_struct>);
    CHECK(is_trivially_copyable_v<test_class>);
    CHECK(!is_trivially_copyable_v<test_base_class>);
    CHECK(!is_trivially_copyable_v<test_derived_class>);
}

TEST_CASE("checks if a type is a standard-layout type")
{
    CHECK(is_standard_layout_v<test_union>);
    CHECK(is_standard_layout_v<test_struct>);

    CHECK(!is_standard_layout_v<test_class>);
    CHECK(is_standard_layout_v<test_standard_layout_class>);

    CHECK(!is_standard_layout_v<test_base_class>);
    CHECK(!is_standard_layout_v<test_derived_class>);
}

TEST_CASE("checks if a type is a class (but not union) type and has no non-static data members")
{
    CHECK(!is_empty_v<test_struct>);
    CHECK(!is_empty_v<test_union>);

    CHECK(is_empty_v<test_empty_struct>);
}

TEST_CASE("checks if a type is a polymorphic class type")
{
    CHECK(!is_polymorphic_v<test_struct>);
    CHECK(!is_polymorphic_v<test_union>);
    CHECK(is_polymorphic_v<test_base_class>);

    CHECK(is_polymorphic_v<test_derived_class>);
}

TEST_CASE("checks if a type is a abstract class type")
{
    CHECK(!is_abstract_v<test_struct>);
    CHECK(!is_abstract_v<test_union>);
    CHECK(!is_abstract_v<test_base_class>);
    CHECK(!is_abstract_v<test_derived_class>);

    CHECK(is_abstract_v<test_base_interface>);
    CHECK(!is_abstract_v<test_derived_interface>);
}

TEST_CASE("checks if a type is a final class type")
{
    CHECK(!is_final_v<test_struct>);
    CHECK(!is_final_v<test_union>);
    CHECK(is_final_v<test_derived_class>);
    CHECK(is_final_v<test_derived_interface>);
}

TEST_CASE("checks if a type is a aggregate type")
{
    CHECK(is_aggregate_v<test_struct>);
    CHECK(is_aggregate_v<test_union>);
    CHECK(!is_aggregate_v<test_class>);
    CHECK(!is_aggregate_v<test_derived_class>);
}

TEST_CASE("obtains the number of dimensions of a array type")
{
    CHECK(rank<int>{} == 0);
    CHECK(rank<int[5]>{} == 1);
    CHECK(rank<int[5][5]>{} == 2);
    CHECK(rank<int[][5][5]>{} == 3);
}

TEST_CASE("obtains the size of a array type along a specified dimension")
{
    CHECK(extent_v<int[3]> == 3);
    CHECK(extent_v<int[3], 0> == 3);
    CHECK(extent_v<int[3][4], 0> == 3);
    CHECK(extent_v<int[3][4], 1> == 4);
    CHECK(extent_v<int[3][4], 2> == 0);
    CHECK(extent_v<int[]> == 0);
}

TEST_CASE("checks if two types are the same")
{
    CHECK(is_same_v<int, int>);
    CHECK(!is_same_v<int, double>);
}

TEST_CASE("removes const and/or volatile specifiers from the given type")
{
    CHECK(is_same_v<remove_cv_t<int>, int>);
    CHECK(is_same_v<remove_cv_t<const int>, int>);
    CHECK(is_same_v<remove_cv_t<volatile int>, int>);
    CHECK(is_same_v<remove_cv_t<const volatile int>, int>);
    CHECK(!is_same_v<remove_cv_t<const volatile int*>, int*>);
    CHECK(is_same_v<remove_cv_t<const volatile int*>, const volatile int*>);
    CHECK(is_same_v<remove_cv_t<const int* volatile>, const int*>);
    CHECK(is_same_v<remove_cv_t<int* const volatile>, int*>);
}

TEST_CASE("checks if a type is a base of the other type")
{
    CHECK(is_base_of_v<test_base_class, test_derived_class>);
    CHECK(is_base_of_v<test_base_interface, test_derived_interface>);
    CHECK(!is_base_of_v<test_base_class, test_derived_interface>);
}

TEST_CASE("adds const and/or volatile specifiers to the given type")
{
    CHECK(is_same_v<add_const_t<int>, const int>);
    CHECK(is_same_v<add_volatile_t<int>, volatile int>);
    CHECK(is_same_v<add_cv_t<int>, const volatile int>);
}

TEST_CASE("adds a lvalue or rvalue reference to the given type")
{
    using non_ref = int;
    CHECK(is_lvalue_reference_v<non_ref> == false);

    using l_ref = add_lvalue_reference_t<non_ref>;
    CHECK(is_lvalue_reference_v<l_ref> == true);

    using r_ref = add_rvalue_reference_t<non_ref>;
    CHECK(is_rvalue_reference_v<r_ref> == true);

    using void_ref = add_lvalue_reference_t<void>;
    CHECK(is_reference_v<void_ref> == false);
}

TEST_CASE("removes extent from the given array type")
{
    float a0;
    float a1[1][2][3];
    float *a3;

    CHECK(is_same_v<remove_extent_t<decltype(a0)>, float>);
    CHECK(is_same_v<remove_extent_t<decltype(a1)>, float[2][3]>);
    CHECK(is_same_v<remove_all_extents_t<decltype(a1)>, float>);

    CHECK(is_same_v<remove_extent_t<decltype(a3)>, float*>);
    CHECK(is_same_v<remove_all_extents_t<decltype(a3)>, float*>);
}

TEST_CASE("removes a pointer from the given type")
{
    CHECK(is_same_v<int, remove_pointer_t<int>> == true);
    CHECK(is_same_v<int, remove_pointer_t<int*>> == true);
    CHECK(is_same_v<int, remove_pointer_t<int**>> == false);
    CHECK(is_same_v<int, remove_pointer_t<int* const>> == true);
    CHECK(is_same_v<int, remove_pointer_t<int* volatile>> == true);
    CHECK(is_same_v<int, remove_pointer_t<int* const volatile>> == true);
}

TEST_CASE("adds a pointer to the given type")
{
    CHECK(is_same_v<int*, add_pointer_t<int>> == true);
    CHECK(is_same_v<int**, add_pointer_t<int*>> == true);
}

template<class T>
T test_type_identity (T a, type_identity_t<T> b) { return a + b; }

TEST_CASE("returns the type argument unchanged")
{
    CHECK(test_type_identity(4.2, 1) == 5.2);
}

TEST_CASE("combines remove_cv and remove_reference")
{
    CHECK(is_same_v<remove_cvref_t<int>, int>);
    CHECK(is_same_v<remove_cvref_t<int&>, int>);
    CHECK(is_same_v<remove_cvref_t<int&&>, int>);
    CHECK(is_same_v<remove_cvref_t<const int&>, int>);
    CHECK(is_same_v<remove_cvref_t<const int[2]>, int[2]>);
    CHECK(is_same_v<remove_cvref_t<const int(&)[2]>, int[2]>);
    CHECK(is_same_v<remove_cvref_t<int(int)>, int(int)>);
}

TEST_CASE("applies type transformations as when passing a function argument by value")
{
    CHECK(is_same_v<decay_t<int>, int>);
    CHECK(!is_same_v<decay_t<int>, float>);
    CHECK(is_same_v<decay_t<int&>, int>);
    CHECK(is_same_v<decay_t<int&&>, int>);
    CHECK(is_same_v<decay_t<const int&>, int>);
    CHECK(is_same_v<decay_t<int[2]>, int*>);
    CHECK(!is_same_v<decay_t<int[4][2]>, int*>);
    CHECK(!is_same_v<decay_t<int[4][2]>, int**>);
    CHECK(is_same_v<decay_t<int[4][2]>, int(*)[2]>);
    CHECK(is_same_v<decay_t<int(int)>, int(*)(int)>);
}

template<class T, enable_if_t<!is_same_v<T, int>>* = nullptr>
bool test_enable_if ()
{
    return false;
}

template<class T, enable_if_t<is_same_v<T, int>>* = nullptr>
bool test_enable_if ()
{
    return true;
}

TEST_CASE("conditionally removes a function overload or template specialization from overload resolution")
{
    CHECK(test_enable_if<int>());
    CHECK(!test_enable_if<double>());
}

TEST_CASE("chooses one type or another based on compile-time boolean")
{
    CHECK(is_same_v<conditional_t<true, int, double>, int>);
    CHECK(is_same_v<conditional_t<false, int, double>, double>);
}

TEST_CASE("variadic logical AND/OR/NOT metafunction")
{
    CHECK(conjunction_v<true_type, true_type, true_type>);
    CHECK(!conjunction_v<true_type, false_type, true_type>);

    CHECK(disjunction_v<true_type, false_type, false_type>);
    CHECK(!disjunction_v<false_type, false_type>);

    CHECK(!negation_v<true_type>);
    CHECK(negation_v<false_type>);
}

TEST_CASE("checks if a type is trivial")
{
    CHECK(is_trivial_v<test_struct>);
    CHECK(!is_trivial_v<test_class>);
}

TEST_SUITE_END  ();
