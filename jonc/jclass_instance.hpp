#pragma once

#include <type_traits>
#include "signature_traits.hpp"
#include "convertion_traits.hpp"
#include "jvm.hpp"

namespace jonc
{

class jclass_instance
{
public:

   // Specialization for void
   template< class ret_t, typename std::enable_if< std::is_void<ret_t>::value >::type* = nullptr >
   void call_method( const char* method_name )
   {
      constexpr auto signature = sstr::literal("()") + jonc::method_signature<void>::get();

      jvm_.get_env().CallVoidMethod( my_instance_,
                                     get_method_id( method_name, signature ) );

      jvm_.check_for_exceptions();
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_void<ret_t>::value >::type* = nullptr >
   void call_method( const char* method_name, Args&&... args )
   {
      constexpr auto signature = sstr::literal("(") +
                                 jonc::method_signature<Args...>::get() +
                                 sstr::literal(")") +
                                 jonc::method_signature<void>::get();

      jvm_.get_env().CallVoidMethod( my_instance_,
                                     get_method_id( method_name, signature ),
                                     jonc::convert_to_java<Args>(jvm_, std::forward<Args>(args)).get()... );

      jvm_.check_for_exceptions();
   }

   // Specialization for bool
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, bool>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<bool, jboolean>( method_name, &JNIEnv::CallBooleanMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, bool>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<bool, jboolean>( method_name, &JNIEnv::CallBooleanMethod, std::forward<Args>(args)... );
   }

   // Specialization for unsigned char
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, unsigned char>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<unsigned char, jbyte>( method_name, &JNIEnv::CallByteMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, unsigned char>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<unsigned char, jbyte>( method_name, &JNIEnv::CallByteMethod, std::forward<Args>(args)... );
   }

   // Specialization for char
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, char>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<char, jchar>( method_name, &JNIEnv::CallCharMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, char>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<char, jchar>( method_name, &JNIEnv::CallCharMethod, std::forward<Args>(args)... );
   }

   // Specialization for short
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, short>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<short, jshort>( method_name, &JNIEnv::CallShortMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, short>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<short, jshort>( method_name, &JNIEnv::CallShortMethod, std::forward<Args>(args)... );
   }

   // Specialization for int
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, int>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<int, jint>( method_name, &JNIEnv::CallIntMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, int>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<int, jint>( method_name, &JNIEnv::CallIntMethod, std::forward<Args>(args)... );
   }

   // Specialization for long
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, long>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<long, jlong>( method_name, &JNIEnv::CallLongMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, long>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<long, jlong>( method_name, &JNIEnv::CallLongMethod, std::forward<Args>(args)... );
   }

   // Specialization for float
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, float>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<float, jfloat>( method_name, &JNIEnv::CallFloatMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, float>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<float, jfloat>( method_name, &JNIEnv::CallFloatMethod, std::forward<Args>(args)... );
   }

   // Specialization for double
   template< class ret_t, typename std::enable_if< std::is_same<ret_t, double>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      return call_method_internal<double, jdouble>( method_name, &JNIEnv::CallDoubleMethod );
   }

   template< class ret_t, class... Args, typename std::enable_if< std::is_same<ret_t, double>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      return call_method_internal<double, jdouble>( method_name, &JNIEnv::CallDoubleMethod, std::forward<Args>(args)... );
   }

   // Specialization for other kinds of objects
   template< class ret_t, typename std::enable_if< !std::is_void<ret_t>::value &&
                                                   !std::is_same<ret_t, bool>::value &&
                                                   !std::is_same<ret_t, unsigned char>::value &&
                                                   !std::is_same<ret_t, char>::value &&
                                                   !std::is_same<ret_t, short>::value &&
                                                   !std::is_same<ret_t, int>::value &&
                                                   !std::is_same<ret_t, long>::value &&
                                                   !std::is_same<ret_t, float>::value &&
                                                   !std::is_same<ret_t, double>::value >::type* = nullptr >
   ret_t call_method( const char* method_name )
   {
      constexpr auto signature = sstr::literal("()") + method_signature<ret_t>::get();
      //std::cout << "Calling '" << method_name << "' as " << signature << std::endl;

      auto java_ret = jvm_.get_env().CallObjectMethod( my_instance_, get_method_id( method_name, signature ) );

      ret_t ret = jonc::convert_from_java<ret_t>::get( jvm_, java_ret );

      jvm_.get_env().DeleteLocalRef(java_ret);

      return ret;
   }

   template< class ret_t, class... Args, typename std::enable_if< !std::is_void<ret_t>::value &&
                                                                  !std::is_same<ret_t, bool>::value &&
                                                                  !std::is_same<ret_t, unsigned char>::value &&
                                                                  !std::is_same<ret_t, char>::value &&
                                                                  !std::is_same<ret_t, short>::value &&
                                                                  !std::is_same<ret_t, int>::value &&
                                                                  !std::is_same<ret_t, long>::value &&
                                                                  !std::is_same<ret_t, float>::value &&
                                                                  !std::is_same<ret_t, double>::value >::type* = nullptr >
   ret_t call_method( const char* method_name, Args&&... args )
   {
      constexpr auto signature = sstr::literal("(") + method_signature<Args...>::get() + sstr::literal(")") + method_signature<ret_t>::get();
      //std::cout << "Calling '" << method_name << "' as " << signature << std::endl;

      auto java_ret = jvm_.get_env().CallObjectMethod( my_instance_,
                                                       get_method_id( method_name, signature ),
                                                       jonc::convert_to_java<Args>(jvm_, std::forward<Args>(args)).get()... );

      ret_t ret = jonc::convert_from_java<ret_t>::get( jvm_, java_ret );

      jvm_.get_env().DeleteLocalRef(java_ret);

      return ret;
   }


   jclass_instance( jonc::jvm& vm, const char* class_name ) :
      jvm_( vm ),
      my_name_( class_name )
   {
      my_class_ = jvm_.get_env().FindClass( class_name );
      if(my_class_ == nullptr)
      {
         jvm_.check_for_exceptions();
         throw jonc::class_not_found( std::string("class '") + class_name + "' not found" );
      }

      constexpr auto ctor_signature = sstr::literal("()") + jonc::method_signature<void>::get();

      jmethodID ctor = get_method_id( "<init>", ctor_signature );

      my_instance_ = jvm_.get_env().NewObject( my_class_, ctor );
   }

   jclass_instance( jonc::jvm& vm, const char* class_name, jobject instance ) :
      jvm_( vm ),
      my_name_( class_name ),
      my_instance_( instance )
   {
      my_class_ = jvm_.get_env().FindClass( class_name );
      if(my_class_ == nullptr)
      {
         jvm_.check_for_exceptions();
         throw jonc::class_not_found( std::string("class '") + class_name + "' not found" );
      }
   }

   template< class... Args >
   jclass_instance( jonc::jvm& vm, const char* class_name, Args&&... args ) :
      jvm_( vm ),
      my_name_( class_name )
   {
      my_class_ = jvm_.get_env().FindClass( class_name );
      if(my_class_ == nullptr)
      {
         jvm_.check_for_exceptions();
         throw jonc::class_not_found( std::string("class '") + class_name + "' not found" );
      }

      constexpr auto ctor_signature = sstr::literal("(") +
                                      jonc::method_signature<Args...>::get() +
                                      sstr::literal(")") +
                                      jonc::method_signature<void>::get();

      jmethodID ctor = get_method_id( "<init>", ctor_signature );

      my_instance_ = jvm_.get_env().NewObject( my_class_, ctor, jonc::convert_to_java<Args>(jvm_, std::forward<Args>(args)).get()... );
   }

   ~jclass_instance()
   {
      jvm_.get_env().DeleteLocalRef(my_instance_);
   }

private:
   jonc::jvm& jvm_;
   const std::string my_name_;
   jclass     my_class_ = nullptr;
   jobject    my_instance_ = nullptr;

   jmethodID get_method_id( const char* method_name, const char* signature )
   {
      jmethodID meth_id = jvm_.get_env().GetMethodID(my_class_, method_name, signature);
      if(meth_id == nullptr)
      {
         jvm_.check_for_exceptions();
         throw jonc::method_not_found( std::string("method '") + method_name + "' in class '" + my_name_ + "' with signture '" + signature + "' not found" );
      }

      return meth_id;
   }

   template< class ret_t, class inner_t >
   ret_t call_method_internal( const char* method_name,
                               inner_t (JNIEnv_::*runner)(jobject, jmethodID, ...) )
   {
      constexpr auto signature = sstr::literal("()") + method_signature<ret_t>::get();
      //std::cout << "Calling '" << method_name << "' as " << signature << std::endl;

      auto java_ret = (jvm_.get_env().*runner)( my_instance_, get_method_id( method_name, signature ) );

      return jonc::convert_from_java<ret_t>::get( jvm_, java_ret );
   }

   template< class ret_t, class inner_t, class... Args >
   ret_t call_method_internal( const char* method_name,
                               inner_t (JNIEnv_::*runner)(jobject, jmethodID, ...),
                               Args&&... args )
   {
      constexpr auto signature = sstr::literal("(") + method_signature<Args...>::get() + sstr::literal(")") + method_signature<ret_t>::get();
      //std::cout << "Calling '" << method_name << "' as " << signature << std::endl;

      auto java_ret = (jvm_.get_env().*runner)( my_instance_,
                                                get_method_id( method_name, signature ),
                                                jonc::convert_to_java<Args>(jvm_, std::forward<Args>(args)).get()... );

      return jonc::convert_from_java<ret_t>::get( jvm_, java_ret );
   }
};

};
