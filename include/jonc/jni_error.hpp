#pragma once

#include <system_error>

namespace jonc
{

class jni_error_category : public std::error_category
{
   const char* name() const noexcept { return "jni_error_category"; }
   std::string message( int condition ) const
   {
      switch(condition)
      {
         case JNI_OK:         return "(0) Success";
         case JNI_ERR:        return "(-1) Unknown error";
         case JNI_EDETACHED:  return "(-2) Thread detached from the VM";
         case JNI_EVERSION:   return "(-3) JNI version error";
         case JNI_ENOMEM:     return "(-4) Not enough memory";
         case JNI_EEXIST:     return "(-5) VM already created";
         case JNI_EINVAL:     return "(-6) Invalid arguments";
         default:             return "Unknown code=" + std::to_string(condition);
      }
   }
};

class bad_jni_alloc : public std::runtime_error
{
public:
   explicit bad_jni_alloc( const char* what_arg ) : std::runtime_error( what_arg ) {}
   explicit bad_jni_alloc( const std::string& what_arg ) : std::runtime_error( what_arg ) {}
};

class class_not_found : public std::runtime_error
{
public:
   explicit class_not_found( const char* what_arg ) : std::runtime_error( what_arg ) {}
   explicit class_not_found( const std::string& what_arg ) : std::runtime_error( what_arg ) {}
};

class method_not_found : public std::runtime_error
{
public:
   explicit method_not_found( const char* what_arg ) : std::runtime_error( what_arg ) {}
   explicit method_not_found( const std::string& what_arg ) : std::runtime_error( what_arg ) {}
};

};
