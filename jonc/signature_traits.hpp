#pragma once

#include <string>
#include <vector>
#include "utils/static_string.hpp"

namespace sstr = ak_toolkit::static_str;

namespace jonc
{

template< class T >
struct type_signature
{
   static_assert( std::is_same<T, int>::value && !std::is_same<T, int>::value, "Unknow type signature" );
   static constexpr auto value = sstr::literal("");
};

template<class T, size_t N>
struct type_signature<T[N]> { static constexpr auto value = sstr::literal("[") + type_signature<T>::value; };

template<class T>
struct type_signature<std::vector<T>> { static constexpr auto value = sstr::literal("[") + type_signature<T>::value; };

template<class T> struct type_signature<T&> : type_signature<typename std::remove_cv<T>::type> {};

template<> struct type_signature<void>          { static constexpr auto value = sstr::literal("V"); };
template<> struct type_signature<bool>          { static constexpr auto value = sstr::literal("Z"); };
template<> struct type_signature<unsigned char> { static constexpr auto value = sstr::literal("B"); };
template<> struct type_signature<char>          { static constexpr auto value = sstr::literal("C"); };
template<> struct type_signature<short>         { static constexpr auto value = sstr::literal("S"); };
template<> struct type_signature<int>           { static constexpr auto value = sstr::literal("I"); };
template<> struct type_signature<long>          { static constexpr auto value = sstr::literal("J"); };
template<> struct type_signature<float>         { static constexpr auto value = sstr::literal("F"); };
template<> struct type_signature<double>        { static constexpr auto value = sstr::literal("D"); };
template<> struct type_signature<std::string>   { static constexpr auto value = sstr::literal("Ljava/lang/String;"); };


template <class... Args>
struct method_signature;

template <class First, class... Args>
struct method_signature<First, Args...>
{
   static constexpr auto get()
      -> decltype( type_signature<First>::value + method_signature<Args...>::get() )
   {
      return type_signature<First>::value + method_signature<Args...>::get();
   };
};

template <class First>
struct method_signature<First>
{
   static constexpr auto get()
      -> decltype(type_signature<First>::value)
   {
      return type_signature<First>::value;
   };
};

};
