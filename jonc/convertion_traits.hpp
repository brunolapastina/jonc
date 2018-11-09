#pragma once
#include <vector>
#include "jvm.hpp"
#include "jni_error.hpp"

namespace jonc
{

template< class T >
struct convert_to_java
{
   static_assert( std::is_same<T, int>::value && !std::is_same<T, int>::value, "Unknown type conversion to java" );
};


/******************************************************************************
 *                      Conversions from C++ to Java                          *
 ******************************************************************************/

/*
 * Basic types
 */
template<class T>
struct convert_to_java<T&> : convert_to_java<T>
{
   constexpr convert_to_java( jvm& vm, T& val ) : convert_to_java<T>( vm, val ) {}
};

template<class T>
struct convert_to_java<const T&> : convert_to_java<T>
{
   constexpr convert_to_java( jvm& vm, const T& val ) : convert_to_java<T>( vm, val ) {}
};

template<> struct convert_to_java<bool>
{
   constexpr convert_to_java( jvm&, const bool& val ) noexcept : val_( val ) {}
   constexpr jboolean get() const noexcept { return val_; }
private:
   jboolean val_;
};

template<> struct convert_to_java<unsigned char>
{
   constexpr convert_to_java( jvm&, const unsigned char& val ) noexcept : val_( val ) {}
   constexpr jbyte get() const noexcept { return val_; }
private:
   jbyte val_;
};

template<> struct convert_to_java<char>
{
   constexpr convert_to_java( jvm&, const char& val ) noexcept : val_( val ) {}
   constexpr jchar get() const noexcept { return val_; }
private:
   jchar val_;
};

template<> struct convert_to_java<short>
{
   constexpr convert_to_java( jvm&, const short& val ) noexcept : val_( val ) {}
   constexpr jshort get() const noexcept { return val_; }
private:
   jshort val_;
};

template<> struct convert_to_java<int>
{
   constexpr convert_to_java( jvm&, const int& val ) noexcept : val_( val ) {}
   constexpr jint get() const noexcept { return val_; }
private:
   jint val_;
};

template<> struct convert_to_java<long>
{
   constexpr convert_to_java( jvm&, const long& val ) noexcept : val_( val ) {}
   constexpr jlong get() const noexcept { return val_; }
private:
   jlong val_;
};

template<> struct convert_to_java<float>
{
   constexpr convert_to_java( jvm&, const float& val ) noexcept : val_( val ) {}
   constexpr jfloat get() const noexcept { return val_; }
private:
   jfloat val_;
};

template<> struct convert_to_java<double>
{
   constexpr convert_to_java( jvm&, const double& val ) noexcept : val_( val ) {}
   constexpr jdouble get() const noexcept { return val_; }
private:
   jdouble val_;
};



/*
 * Array types
 */
template<class inp_t, size_t N, class inner_t, class array_t >
struct java_converter_array
{
public:
   java_converter_array(
      jvm& vm,
      array_t (JNIEnv_::*creator)(jsize),
      void (JNIEnv_::*filler)(array_t, jsize, jsize, const inner_t*),
      const inp_t inp[N]
   ) :
      vm_( vm )
   {
      val_ = (vm_.get_env().*creator)( N );
      if( val_ != NULL )
      {
         (vm_.get_env().*filler)( val_, 0, N, inp );
      }
   }

   ~java_converter_array()
   {
      vm_.get_env().DeleteLocalRef(val_);
   }

   constexpr array_t get() const noexcept { return val_; }
private:
   jvm& vm_;
   array_t val_;
};


template<size_t N >
struct convert_to_java<bool[N]> : java_converter_array<bool, N, jboolean, jbooleanArray>
{
   convert_to_java( jvm& vm, const bool inp[N] ) : java_converter_array<bool, N, jboolean, jbooleanArray>( vm, &JNIEnv::NewBooleanArray, &JNIEnv::SetBooleanArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<unsigned char[N]> : java_converter_array<unsigned char, N, jbyte, jbyteArray>
{
   convert_to_java( jvm& vm, const unsigned char inp[N] ) : java_converter_array<unsigned char, N, jbyte, jbyteArray>( vm, &JNIEnv::NewByteArray, &JNIEnv::SetByteArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<char[N]> : java_converter_array<char, N, jchar, jcharArray>
{
   convert_to_java( jvm& vm, const char inp[N] ) : java_converter_array<char, N, jchar, jcharArray>( vm, &JNIEnv::NewCharArray, &JNIEnv::SetCharArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<short[N]> : java_converter_array<short, N, jshort, jshortArray>
{
   convert_to_java( jvm& vm, const short inp[N] ) : java_converter_array<short, N, jshort, jshortArray>( vm, &JNIEnv::NewShortArray, &JNIEnv::SetShortArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<int[N]> : java_converter_array<int, N, jint, jintArray>
{
   convert_to_java( jvm& vm, const int inp[N] ) : java_converter_array<int, N, jint, jintArray>( vm, &JNIEnv::NewIntArray, &JNIEnv::SetIntArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<long[N]> : java_converter_array<long, N, jlong, jlongArray>
{
   convert_to_java( jvm& vm, const long inp[N] ) : java_converter_array<long, N, jlong, jlongArray>( vm, &JNIEnv::NewLongArray, &JNIEnv::SetLongArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<float[N]> : java_converter_array<float, N, jfloat, jfloatArray>
{
   convert_to_java( jvm& vm, const float inp[N] ) : java_converter_array<float, N, jfloat, jfloatArray>( vm, &JNIEnv::NewFloatArray, &JNIEnv::SetFloatArrayRegion, inp ) {}
};

template<size_t N >
struct convert_to_java<double[N]> : java_converter_array<double, N, jdouble, jdoubleArray>
{
   convert_to_java( jvm& vm, const double inp[N] ) : java_converter_array<double, N, jdouble, jdoubleArray>( vm, &JNIEnv::NewDoubleArray, &JNIEnv::SetDoubleArrayRegion, inp ) {}
};



/*
 * Other types
 */
template<>
struct convert_to_java<std::string>
{
public:
   convert_to_java( jvm& vm, const std::string& inp ) : vm_( vm )
   {
      val_ = vm_.get_env().NewStringUTF( inp.c_str() );
      if( val_ == NULL )
      {
         throw bad_jni_alloc( "error on NewStringUTF" );
      }
   }
   ~convert_to_java()
   {
      vm_.get_env().DeleteLocalRef(val_);
   }
   jstring get() const noexcept { return val_; }

private:
   jvm& vm_;
   jstring val_;
};


/******************************************************************************
 *                      Conversions from Java to C++                          *
 ******************************************************************************/

template< class T >
struct convert_from_java
{
   static_assert( std::is_same<T, int>::value && !std::is_same<T, int>::value, "Unknown type conversion from java" );
};

template<> struct convert_from_java<bool>
{
   static bool get( jvm& /*vm*/, const jboolean& val ) noexcept { return val; }
};

template<> struct convert_from_java<unsigned char>
{
   static unsigned char get( jvm& /*vm*/, const jbyte& val ) noexcept { return val; }
};

template<> struct convert_from_java<char>
{
   static char get( jvm& /*vm*/, const jchar& val ) noexcept { return val; }
};

template<> struct convert_from_java<short>
{
   static short get( jvm& /*vm*/, const jshort& val ) noexcept { return val; }
};

template<> struct convert_from_java<int>
{
   static int get( jvm& /*vm*/, const jint& val ) noexcept { return val; }
};

template<> struct convert_from_java<long>
{
   static long get( jvm& /*vm*/, const jlong& val ) noexcept { return val; }
};

template<> struct convert_from_java<float>
{
   static float get( jvm& /*vm*/, const jfloat& val ) noexcept { return val; }
};

template<> struct convert_from_java<double>
{
   static double get( jvm& /*vm*/, const jdouble& val ) noexcept { return val; }
};

template<> struct convert_from_java<std::string>
{
   static std::string get( jvm& vm, jobject& val )
   {
      std::string ret;

      jstring obj = reinterpret_cast<jstring>(val);
      if( obj != nullptr )
      {
         const char* msg_str = vm.get_env().GetStringUTFChars(obj, 0);
         ret.assign( msg_str );
         vm.get_env().ReleaseStringUTFChars(obj, msg_str);
      }

      return ret;
   }
};

template<class T>
struct convert_from_java<std::vector<T>>
{
   static std::vector<T> get( jvm& vm, jobject& val )
   {
      jobjectArray obj_array = reinterpret_cast<jobjectArray>(val);
      jsize array_size = vm.get_env().GetArrayLength(obj_array);

      std::vector<T> ret;

      if( (obj_array != nullptr) && (array_size > 0) )
      {
         ret.reserve( array_size );    // Just to gain a bit of performance

         for ( jsize i = 0; i < array_size; ++i )
         {
            jobject element = vm.get_env().GetObjectArrayElement(obj_array, i);
            ret.push_back( jonc::convert_from_java<T>::get( vm, element ) );
            vm.get_env().DeleteLocalRef(element);
         }
      }

      return ret;
   }
};


};
