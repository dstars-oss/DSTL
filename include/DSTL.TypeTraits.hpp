/*++

Copyright (c) 2024.  D.Stars <d.stars@163.com>
All rights reserved.

Module Name:
    DSTL.TypeTraits.hpp

Abstract:
    Type Traits.

--*/

#ifndef DSTL_TYPETRAITS_H
#define DSTL_TYPETRAITS_H

template<class T, T Val>
struct integral_constant
{
    static constexpr T value = Val;
    using value_type         = T;
    using type               = integral_constant<T, Val>;
    constexpr operator value_type () const noexcept { return value; }
    constexpr value_type operator() () const noexcept { return value; }
};

template<bool Value>
using bool_constant = integral_constant<bool, Value>;

using true_type  = bool_constant<true>;
using false_type = bool_constant<false>;

//
// primary type categories
//

template<class T> struct is_void;
template<class T> struct is_null_pointer;
template<class T> struct is_integral;
template<class T> struct is_floating_point;
template<class T> struct is_array;
template<class T> struct is_pointer;
template<class T> struct is_lvalue_reference;
template<class T> struct is_rvalue_reference;
template<class T> struct is_member_object_pointer;
template<class T> struct is_member_function_pointer;
template<class T> struct is_enum;
template<class T> struct is_union;
template<class T> struct is_class;
template<class T> struct is_function;

//
// composite type categories
//

template<class T> struct is_reference;
template<class T> struct is_arithmetic;
template<class T> struct is_fundamental;
template<class T> struct is_scalar;
template<class T> struct is_object;
template<class T> struct is_compound;
template<class T> struct is_member_pointer;

//
// type properties
//

template<class T> struct is_const;
template<class T> struct is_volatile;
template<class T> struct is_trivial;
template<class T> struct is_trivially_copyable;
template<class T> struct is_standard_layout;
template<class T> struct is_empty;
template<class T> struct is_polymorphic;
template<class T> struct is_abstract;
template<class T> struct is_final;
template<class T> struct is_aggregate;
template<class T> struct is_signed;
template<class T> struct is_unsigned;
template<class T> struct is_bounded_array;
template<class T> struct is_unbounded_array;
template<class T> struct is_scoped_enum;
template<class T, class... Args> struct is_constructible;
template<class T> struct is_default_constructible;
template<class T> struct is_copy_constructible;
template<class T> struct is_move_constructible;
template<class T, class U> struct is_assignable;
template<class T> struct is_copy_assignable;
template<class T> struct is_move_assignable;
template<class T, class U> struct is_swappable_with;
template<class T> struct is_swappable;
template<class T> struct is_destructible;
template<class T, class... Args> struct is_trivially_constructible;
template<class T> struct is_trivially_default_constructible;
template<class T> struct is_trivially_copy_constructible;
template<class T> struct is_trivially_move_constructible;
template<class T, class U> struct is_trivially_assignable;
template<class T> struct is_trivially_copy_assignable;
template<class T> struct is_trivially_move_assignable;
template<class T> struct is_trivially_destructible;
template<class T, class... Args> struct is_nothrow_constructible;
template<class T> struct is_nothrow_default_constructible;
template<class T> struct is_nothrow_copy_constructible;
template<class T> struct is_nothrow_move_constructible;
template<class T, class U> struct is_nothrow_assignable;
template<class T> struct is_nothrow_copy_assignable;
template<class T> struct is_nothrow_move_assignable;
template<class T, class U> struct is_nothrow_swappable_with;
template<class T> struct is_nothrow_swappable;
template<class T> struct is_nothrow_destructible;
template<class T> struct has_virtual_destructor;
template<class T> struct has_unique_object_representations;
template<class T, class U> struct reference_constructs_from_temporary;
template<class T, class U> struct reference_converts_from_temporary;

//
// type property queries
//

template<class T> struct alignment_of;
template<class T> struct rank;
template<class T, unsigned I = 0> struct extent : integral_constant<size_t, 0> {};

//
// type relations
//

template<class T, class U> struct is_same;
template<class Base, class Derived> struct is_base_of;
template<class Base, class Derived> struct is_virtual_base_of;
template<class From, class To> struct is_convertible;
template<class From, class To> struct is_nothrow_convertible;
template<class T, class U> struct is_layout_compatible;
template<class Base, class Derived> struct is_pointer_interconvertible_base_of;
template<class Fn, class... ArgTypes> struct is_invocable;
template<class R, class Fn, class... ArgTypes> struct is_invocable_r;
template<class Fn, class... ArgTypes> struct is_nothrow_invocable;
template<class R, class Fn, class... ArgTypes> struct is_nothrow_invocable_r;

//
// const-volatile modifications
//

template<class T> struct remove_const;
template<class T> struct remove_volatile;
template<class T> struct remove_cv;
template<class T> struct add_const;
template<class T> struct add_volatile;
template<class T> struct add_cv;

template<class T> using remove_const_t    = typename remove_const<T>::type;
template<class T> using remove_volatile_t = typename remove_volatile<T>::type;
template<class T> using remove_cv_t       = typename remove_cv<T>::type;
template<class T> using add_const_t       = typename add_const<T>::type;
template<class T> using add_volatile_t    = typename add_volatile<T>::type;
template<class T> using add_cv_t          = typename add_cv<T>::type;

//
// reference modifications
//
template<class T> struct remove_reference;
template<class T> struct add_lvalue_reference;
template<class T> struct add_rvalue_reference;

template<class T> using remove_reference_t     = typename remove_reference<T>::type;
template<class T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template<class T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

//
// sign modifications
//

template<class T> struct make_signed;
template<class T> struct make_unsigned;

template<class T> using make_signed_t   = typename make_signed<T>::type;
template<class T> using make_unsigned_t = typename make_unsigned<T>::type;

//
// array modifications
//

template<class T> struct remove_extent;
template<class T> struct remove_all_extents;

template<class T> using remove_extent_t      = typename remove_extent<T>::type;
template<class T> using remove_all_extents_t = typename remove_all_extents<T>::type;

//
// pointer modifications
//

template<class T> struct remove_pointer;
template<class T> struct add_pointer;

template<class T> using remove_pointer_t = typename remove_pointer<T>::type;
template<class T> using add_pointer_t    = typename add_pointer<T>::type;

//
// other transformations
//

template<class T> struct type_identity;
template<class T> struct remove_cvref;
template<class T> struct decay;
template<bool, class T = void> struct enable_if;
template<bool, class T, class F> struct conditional;
template<class... T> struct common_type;
template<class T, class U, template<class> class TQual, template<class> class UQual> struct basic_common_reference {};
template<class... T> struct common_reference;
template<class T> struct underlying_type;
template<class Fn, class... ArgTypes> struct invoke_result;
template<class T> struct unwrap_reference;
template<class T> struct unwrap_ref_decay;

template<class T> using type_identity_t                     = typename type_identity<T>::type;
template<class T> using remove_cvref_t                      = typename remove_cvref<T>::type;
template<class T> using decay_t                             = typename decay<T>::type;
template<bool B, class T = void> using enable_if_t          = typename enable_if<B, T>::type;
template<bool B, class T, class F> using conditional_t      = typename conditional<B, T, F>::type;
template<class... T> using common_type_t                    = typename common_type<T...>::type;
template<class... T> using common_reference_t               = typename common_reference<T...>::type;
template<class T> using underlying_type_t                   = typename underlying_type<T>::type;
template<class Fn, class... ArgTypes> using invoke_result_t = typename invoke_result<Fn, ArgTypes...>::type;
template<class T> using unwrap_reference_t                  = typename unwrap_reference<T>::type;
template<class T> using unwrap_ref_decay_t                  = typename unwrap_ref_decay<T>::type;
template<class...> using void_t                             = void;

//
// logical operator traits
//

template<class... B> struct conjunction;
template<class... B> struct disjunction;
template<class B> struct negation;

//
// primary type categories
//

template<class T> inline constexpr bool is_void_v                    = is_void<T>::value;
template<class T> inline constexpr bool is_null_pointer_v            = is_null_pointer<T>::value;
template<class T> inline constexpr bool is_integral_v                = is_integral<T>::value;
template<class T> inline constexpr bool is_floating_point_v          = is_floating_point<T>::value;
template<class T> inline constexpr bool is_array_v                   = is_array<T>::value;
template<class T> inline constexpr bool is_pointer_v                 = is_pointer<T>::value;
template<class T> inline constexpr bool is_lvalue_reference_v        = is_lvalue_reference<T>::value;
template<class T> inline constexpr bool is_rvalue_reference_v        = is_rvalue_reference<T>::value;
template<class T> inline constexpr bool is_member_object_pointer_v   = is_member_object_pointer<T>::value;
template<class T> inline constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;
template<class T> inline constexpr bool is_enum_v                    = is_enum<T>::value;
template<class T> inline constexpr bool is_union_v                   = is_union<T>::value;
template<class T> inline constexpr bool is_class_v                   = is_class<T>::value;
template<class T> inline constexpr bool is_function_v                = is_function<T>::value;

//
// composite type categories
//

template<class T> inline constexpr bool is_reference_v      = is_reference<T>::value;
template<class T> inline constexpr bool is_arithmetic_v     = is_arithmetic<T>::value;
template<class T> inline constexpr bool is_fundamental_v    = is_fundamental<T>::value;
template<class T> inline constexpr bool is_scalar_v         = is_scalar<T>::value;
template<class T> inline constexpr bool is_object_v         = is_object<T>::value;
template<class T> inline constexpr bool is_compound_v       = is_compound<T>::value;
template<class T> inline constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

//
// type properties
//

template<class T> inline constexpr bool is_const_v                                     = is_const<T>::value;
template<class T> inline constexpr bool is_volatile_v                                  = is_volatile<T>::value;
template<class T> inline constexpr bool is_trivial_v                                   = is_trivial<T>::value;
template<class T> inline constexpr bool is_trivially_copyable_v                        = is_trivially_copyable<T>::value;
template<class T> inline constexpr bool is_standard_layout_v                           = is_standard_layout<T>::value;
template<class T> inline constexpr bool is_empty_v                                     = is_empty<T>::value;
template<class T> inline constexpr bool is_polymorphic_v                               = is_polymorphic<T>::value;
template<class T> inline constexpr bool is_abstract_v                                  = is_abstract<T>::value;
template<class T> inline constexpr bool is_final_v                                     = is_final<T>::value;
template<class T> inline constexpr bool is_aggregate_v                                 = is_aggregate<T>::value;
template<class T> inline constexpr bool is_signed_v                                    = is_signed<T>::value;
template<class T> inline constexpr bool is_unsigned_v                                  = is_unsigned<T>::value;
template<class T> inline constexpr bool is_bounded_array_v                             = is_bounded_array<T>::value;
template<class T> inline constexpr bool is_unbounded_array_v                           = is_unbounded_array<T>::value;
template<class T> inline constexpr bool is_scoped_enum_v                               = is_scoped_enum<T>::value;
template<class T, class... Args> inline constexpr bool is_constructible_v              = is_constructible<T, Args...>::value;
template<class T> inline constexpr bool is_default_constructible_v                     = is_default_constructible<T>::value;
template<class T> inline constexpr bool is_copy_constructible_v                        = is_copy_constructible<T>::value;
template<class T> inline constexpr bool is_move_constructible_v                        = is_move_constructible<T>::value;
template<class T, class U> inline constexpr bool is_assignable_v                       = is_assignable<T, U>::value;
template<class T> inline constexpr bool is_copy_assignable_v                           = is_copy_assignable<T>::value;
template<class T> inline constexpr bool is_move_assignable_v                           = is_move_assignable<T>::value;
template<class T, class U> inline constexpr bool is_swappable_with_v                   = is_swappable_with<T, U>::value;
template<class T> inline constexpr bool is_swappable_v                                 = is_swappable<T>::value;
template<class T> inline constexpr bool is_destructible_v                              = is_destructible<T>::value;
template<class T, class... Args> inline constexpr bool is_trivially_constructible_v    = is_trivially_constructible<T, Args...>::value;
template<class T> inline constexpr bool is_trivially_default_constructible_v           = is_trivially_default_constructible<T>::value;
template<class T> inline constexpr bool is_trivially_copy_constructible_v              = is_trivially_copy_constructible<T>::value;
template<class T> inline constexpr bool is_trivially_move_constructible_v              = is_trivially_move_constructible<T>::value;
template<class T, class U> inline constexpr bool is_trivially_assignable_v             = is_trivially_assignable<T, U>::value;
template<class T> inline constexpr bool is_trivially_copy_assignable_v                 = is_trivially_copy_assignable<T>::value;
template<class T> inline constexpr bool is_trivially_move_assignable_v                 = is_trivially_move_assignable<T>::value;
template<class T> inline constexpr bool is_trivially_destructible_v                    = is_trivially_destructible<T>::value;
template<class T, class... Args> inline constexpr bool is_nothrow_constructible_v      = is_nothrow_constructible<T, Args...>::value;
template<class T> inline constexpr bool is_nothrow_default_constructible_v             = is_nothrow_default_constructible<T>::value;
template<class T> inline constexpr bool is_nothrow_copy_constructible_v                = is_nothrow_copy_constructible<T>::value;
template<class T> inline constexpr bool is_nothrow_move_constructible_v                = is_nothrow_move_constructible<T>::value;
template<class T, class U> inline constexpr bool is_nothrow_assignable_v               = is_nothrow_assignable<T, U>::value;
template<class T> inline constexpr bool is_nothrow_copy_assignable_v                   = is_nothrow_copy_assignable<T>::value;
template<class T> inline constexpr bool is_nothrow_move_assignable_v                   = is_nothrow_move_assignable<T>::value;
template<class T, class U> inline constexpr bool is_nothrow_swappable_with_v           = is_nothrow_swappable_with<T, U>::value;
template<class T> inline constexpr bool is_nothrow_swappable_v                         = is_nothrow_swappable<T>::value;
template<class T> inline constexpr bool is_nothrow_destructible_v                      = is_nothrow_destructible<T>::value;
template<class T> inline constexpr bool has_virtual_destructor_v                       = has_virtual_destructor<T>::value;
template<class T> inline constexpr bool has_unique_object_representations_v            = has_unique_object_representations<T>::value;
template<class T, class U> inline constexpr bool reference_constructs_from_temporary_v = reference_constructs_from_temporary<T, U>::value;
template<class T, class U> inline constexpr bool reference_converts_from_temporary_v   = reference_converts_from_temporary<T, U>::value;

//
// type property queries
//

template<class T> inline constexpr size_t alignment_of_v           = alignment_of<T>::value;
template<class T> inline constexpr size_t rank_v                   = rank<T>::value;
template<class T, unsigned I = 0> inline constexpr size_t extent_v = extent<T, I>::value;

//
// type relations
//

template<class T, class U> inline constexpr bool is_same_v                                      = is_same<T, U>::value;
template<class Base, class Derived> inline constexpr bool is_base_of_v                          = is_base_of<Base, Derived>::value;
template<class Base, class Derived> inline constexpr bool is_virtual_base_of_v                  = is_virtual_base_of<Base, Derived>::value;
template<class From, class To> inline constexpr bool is_convertible_v                           = is_convertible<From, To>::value;
template<class From, class To> inline constexpr bool is_nothrow_convertible_v                   = is_nothrow_convertible<From, To>::value;
template<class T, class U> inline constexpr bool is_layout_compatible_v                         = is_layout_compatible<T, U>::value;
template<class Base, class Derived> inline constexpr bool is_pointer_interconvertible_base_of_v = is_pointer_interconvertible_base_of<Base, Derived>::value;
template<class Fn, class... ArgTypes> inline constexpr bool is_invocable_v                      = is_invocable<Fn, ArgTypes...>::value;
template<class R, class Fn, class... ArgTypes> inline constexpr bool is_invocable_r_v           = is_invocable_r<R, Fn, ArgTypes...>::value;
template<class Fn, class... ArgTypes> inline constexpr bool is_nothrow_invocable_v              = is_nothrow_invocable<Fn, ArgTypes...>::value;
template<class R, class Fn, class... ArgTypes> inline constexpr bool is_nothrow_invocable_r_v   = is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;

// check if T is in Types
template<class T, class... Types> constexpr bool is_any_of_v = (is_same_v<T, Types> || ...);

//
// logical operator traits
//

template<class... B> inline constexpr bool conjunction_v = conjunction<B...>::value;
template<class... B> inline constexpr bool disjunction_v = disjunction<B...>::value;
template<class B> inline constexpr bool negation_v       = negation<B>::value;

//
// traits_type implement.
//

// checks if a type is void
template<class T>
struct is_void : is_same<void, remove_cv_t<T>> {};

// checks if a type is nullptr_t
template<class T>
struct is_null_pointer : is_same<decltype(nullptr), remove_cv_t<T>> {};

// checks if a type is an integral type
template<class T>
struct is_integral : bool_constant<
            is_any_of_v<remove_cv_t<T>, bool, char, signed char, unsigned char, wchar_t,
#ifdef __cpp_char8_t
                        char8_t,
#endif
                        char16_t, char32_t, short, unsigned short,
                        int, unsigned int, long, unsigned long, long long, unsigned long long>> {};

// checks if a type is a floating-point type
template<class T>
struct is_floating_point : bool_constant<
            is_any_of_v<remove_cv_t<T>, float, double, long double>> {};

// checks if a type is an array type
template<class T>
struct is_array : false_type {};
template<class T>
struct is_array<T[]> : true_type {};
template<class T, size_t N>
struct is_array<T[N]> : true_type {};

// checks if a type is a pointer type
template<class T>
struct is_pointer : false_type {};
template<class T>
struct is_pointer<T *> : true_type {};
template<class T>
struct is_pointer<T * const> : true_type {};
template<class T>
struct is_pointer<T * volatile> : true_type {};
template<class T>
struct is_pointer<T * const volatile> : true_type {};

// checks if a type is a lvalue reference
template<class T> struct is_lvalue_reference : false_type {};
template<class T> struct is_lvalue_reference<T &> : true_type {};

// checks if a type is a rvalue reference
template<class T> struct is_rvalue_reference : false_type {};
template<class T> struct is_rvalue_reference<T &&> : true_type {};

// checks if a type is a pointer to a non-static member object
template<class T>
struct is_member_object_pointer : integral_constant<bool,
                                                    is_member_pointer_v<T> &&
                                                    !is_member_function_pointer_v<T>> {};

// checks if a type is an enumeration type
template<class T>
struct is_enum : bool_constant<__is_enum(T)> {};

// checks if a type is a union type
template<class T>
struct is_union : bool_constant<__is_union(T)> {};

// checks if a type is a non-union class type
template<class T>
struct is_class : bool_constant<__is_class(T)> {};

// checks if a type is a function type
template<class T>
struct is_function :
#pragma warning(push)
#pragma warning(disable : 4180)
        bool_constant<!is_const_v<const T> && !is_reference_v<T>> {};
#pragma warning(pop)

// checks if a type is a pointer to a non-static member function
namespace detail
{
    template<class T>
    struct is_member_function_pointer_helper : false_type {};
    template<class T, class U>
    struct is_member_function_pointer_helper<T U::*> : is_function<T> {};
}

template<class T>
struct is_member_function_pointer : detail::is_member_function_pointer_helper<typename remove_cv<T>::type> {};

// checks if a type is either a lvalue reference or rvalue reference
template<class T> struct is_reference : false_type {};
template<class T> struct is_reference<T &> : true_type {};
template<class T> struct is_reference<T &&> : true_type {};

// checks if a type is an arithmetic type
template<class T>
struct is_arithmetic : integral_constant<bool,
                                         is_integral_v<T> ||
                                         is_floating_point_v<T>> {};

// checks if a type is a fundamental type
template<class T>
struct is_fundamental : integral_constant<bool,
                                          is_arithmetic_v<T> ||
                                          is_void_v<T> ||
                                          is_same<decltype(nullptr), remove_cv_t<T>>::value> {};

// checks if a type is a scalar type
template<class T>
struct is_scalar : integral_constant<bool, is_arithmetic<T>::value
                                           || is_enum<T>::value
                                           || is_pointer<T>::value
                                           || is_member_pointer<T>::value
                                           || is_null_pointer<T>::value> {};

// checks if a type is an object type
template<class T>
struct is_object : integral_constant<bool,
                                     is_scalar<T>::value ||
                                     is_array<T>::value ||
                                     is_union<T>::value ||
                                     is_class<T>::value> {};

// checks if a type is a compound type
template<class T>
struct is_compound : integral_constant<bool, !is_fundamental<T>::value> {};

// checks if a type is a pointer to a non-static member function or object
namespace detail
{
    template<class T>
    struct is_member_pointer_helper : false_type {};
    template<class T, class U>
    struct is_member_pointer_helper<T U::*> : true_type {};
}

template<class T> struct is_member_pointer : detail::is_member_pointer_helper<remove_cv_t<T>> {};

// checks if a type is const-qualified
template<class T> struct is_const : false_type {};
template<class T> struct is_const<const T> : true_type {};

// checks if a type is volatile-qualified
template<class T> struct is_volatile : false_type {};
template<class T> struct is_volatile<volatile T> : true_type {};

// obtains the number of dimensions of an array type
template<class T>
struct rank : public integral_constant<size_t, 0> {};
template<class T>
struct rank<T[]> : public integral_constant<size_t, rank<T>::value + 1> {};
template<class T, size_t N>
struct rank<T[N]> : public integral_constant<size_t, rank<T>::value + 1> {};

// obtains the size of an array type along a specified dimension

template<class T>
struct extent<T[], 0> : integral_constant<size_t, 0> {};
template<class T, unsigned N>
struct extent<T[], N> : extent<T, N - 1> {};
template<class T, size_t I>
struct extent<T[I], 0> : integral_constant<size_t, I> {};
template<class T, size_t I, unsigned N>
struct extent<T[I], N> : extent<T, N - 1> {};

// checks if two types are the same
template<class T, class U>
struct is_same : false_type {};
template<class T>
struct is_same<T, T> : true_type {};

// removes const specifiers from the given type
template<class T>
struct remove_const
{
    using type = T;
};
template<class T>
struct remove_const<const T>
{
    using type = T;
};

// removes volatile specifiers from the given type
template<class T>
struct remove_volatile
{
    using type = T;
};
template<class T>
struct remove_volatile<volatile T>
{
    using type = T;
};

// removes const and volatile specifiers from the given type
template<class T>
struct remove_cv
{
    using type = T;
};
template<class T>
struct remove_cv<const T>
{
    using type = T;
};
template<class T>
struct remove_cv<volatile T>
{
    using type = T;
};
template<class T>
struct remove_cv<const volatile T>
{
    using type = T;
};

// adds const specifiers to the given type
template<class T>
struct add_const
{
    using type = const T;
};

// adds volatile specifiers to the given type
template<class T>
struct add_volatile
{
    using type = volatile T;
};

// adds const and volatile specifiers to the given type
template<class T>
struct add_cv
{
    using type = const volatile T;
};

// removes a reference from the given type
template<class T> struct remove_reference
{
    typedef T type;
};
template<class T> struct remove_reference<T &>
{
    typedef T type;
};
template<class T> struct remove_reference<T &&>
{
    typedef T type;
};

// adds a lvalue or rvalue reference to the given type
namespace detail
{
    template<class T, class = void>
    struct add_reference_helper
    {
        using _Lvalue = T;
        using _Rvalue = T;
    };

    template<class T>
    struct add_reference_helper<T, void_t<T &>>
    {
        using _Lvalue = T &;
        using _Rvalue = T &&;
    };
}

template<class T>
struct add_lvalue_reference
{
    using type = typename detail::add_reference_helper<T>::_Lvalue;
};
template<class T>
struct add_rvalue_reference
{
    using type = typename detail::add_reference_helper<T>::_Rvalue;
};

// removes one extent from the given array type
template<class T>
struct remove_extent
{
    using type = T;
};
template<class T>
struct remove_extent<T[]>
{
    using type = T;
};
template<class T, size_t N>
struct remove_extent<T[N]>
{
    using type = T;
};

// removes all extents from the given array type
template<class T>
struct remove_all_extents
{
    using type = T;
};
template<class T>
struct remove_all_extents<T[]>
{
    using type = typename remove_all_extents<T>::type;
};
template<class T, size_t N>
struct remove_all_extents<T[N]>
{
    using type = typename remove_all_extents<T>::type;
};

// 	removes a pointer from the given type
template<class T>
struct remove_pointer
{
    using type = T;
};
template<class T>
struct remove_pointer<T *>
{
    using type = T;
};
template<class T>
struct remove_pointer<T * const>
{
    using type = T;
};
template<class T>
struct remove_pointer<T * volatile>
{
    using type = T;
};
template<class T>
struct remove_pointer<T * const volatile>
{
    using type = T;
};

// adds a pointer to the given type
namespace detail
{
    template<class _Ty, class = void>
    struct add_pointer_helper
    {
        using type = _Ty;
    };

    template<class _Ty>
    struct add_pointer_helper<_Ty, void_t<remove_reference_t<_Ty> *>>
    {
        using type = remove_reference_t<_Ty> *;
    };
}

template<class _Ty>
struct add_pointer
{
    using type = typename detail::add_pointer_helper<_Ty>::type;
};

// returns the type argument unchanged
template<class T>
struct type_identity
{
    using type = T;
};

// combines remove_cv and remove_reference
template<class T>
struct remove_cvref
{
    using type = remove_cv_t<remove_reference_t<T>>;
};

// applies type transformations as when passing a function argument by value
template<class T>
struct decay
{
private:
    using U = typename remove_reference<T>::type;

public:
    using type = conditional_t<is_array_v<U>,
                               add_pointer_t<remove_extent_t<U>>,
                               conditional_t<is_function_v<U>,
                                             add_pointer_t<U>,
                                             remove_cv_t<U>>>;
};

// conditionally removes a function overload or template specialization from overload resolution
template<class T> struct enable_if<true, T>
{
    typedef T type;
};

// chooses one type or another based on compile-time boolean
template<bool B, class T, class F>
struct conditional
{
    using type = T;
};
template<class T, class F>
struct conditional<false, T, F>
{
    using type = F;
};

// variadic logical AND metafunction
template<class...>
struct conjunction : true_type {};
template<class B1>
struct conjunction<B1> : B1 {};
template<class B1, class... Bn>
struct conjunction<B1, Bn...>
        : conditional_t<static_cast<bool>(B1::value), conjunction<Bn...>, B1> {};

// variadic logical OR metafunction
template<class...>
struct disjunction : false_type {};
template<class B1>
struct disjunction<B1> : B1 {};
template<class B1, class... Bn>
struct disjunction<B1, Bn...>
        : conditional_t<static_cast<bool>(B1::value), B1, disjunction<Bn...>> {};

// logical NOT metafunction
template<class B>
struct negation : bool_constant<!static_cast<bool>(B::value)> {};

#endif //DSTL_TYPETRAITS_H
