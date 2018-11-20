#pragma once

#include <string>
#include <jni.h>
#include "jvm.hpp"
#include "jclass_instance.hpp"

namespace jonc
{

struct stack_trace_element
{
   stack_trace_element( jvm& vm, jobject& val )
   {
      jclass_instance stack_trace_obj( vm, "java/lang/StackTraceElement", val );

      class_name_ = stack_trace_obj.call_method<std::string>( "getClassName" );
      file_name_ = stack_trace_obj.call_method<std::string>( "getFileName" );
      line_number_ = stack_trace_obj.call_method<int>( "getLineNumber" );
      method_name_ = stack_trace_obj.call_method<std::string>( "getMethodName" );
      hash_code_ = stack_trace_obj.call_method<int>( "hashCode" );
      is_native_method_ = stack_trace_obj.call_method<bool>( "isNativeMethod" );
   }

   std::string toString() const
   {
      return class_name_ + '.' + method_name_ +
             '(' + file_name_ + ':' + std::to_string(line_number_) + ')' +
             ((is_native_method_) ? "[N]" : "");
      }

   std::string class_name_;
   std::string file_name_;
   int line_number_;
   std::string method_name_;
   int hash_code_;
   bool is_native_method_;
};

template<> struct type_signature<stack_trace_element>
{
   static constexpr auto value = sstr::literal("Ljava/lang/StackTraceElement;");
};

template<> struct convert_from_java<stack_trace_element>
{
   static stack_trace_element get( jvm& vm, jobject& val )
   {
      return stack_trace_element( vm, val );
   }
};

class java_exception
{
public:
   java_exception( jvm& vm, jthrowable exception )
   {
      jclass_instance exc_obj( vm, "java/lang/Throwable", reinterpret_cast<jobject>(exception) );
      message_ = exc_obj.call_method<std::string>( "getMessage" );
      stack_trace_ = exc_obj.call_method<std::vector<stack_trace_element>>( "getStackTrace" );
      desc_ = exc_obj.call_method<std::string>( "toString" );
   }

   const std::string& getMessage() const            { return message_; }
   const std::string& getLocalizedMessage() const   { return message_; }
   const std::vector<stack_trace_element>& getStackTrace() const { return stack_trace_; }
   void printStackTrace()
   {
      std::cout << desc_; // << ": " << message_;
      for( auto& it : stack_trace_ )
      {
         std::cout << "\n\t" << "at " << it.toString();
      }
      std::cout << std::endl;
   }

private:
   std::string message_;
   std::vector<stack_trace_element> stack_trace_;
   std::string desc_;
};

};
