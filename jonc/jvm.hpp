#pragma once
#include <memory>
#include <jni.h>
#include "jni_error.hpp"

namespace jonc
{

class jclass_instance;

class jvm
{
public:
   jvm()
   {
      JavaVMOption options;
      options.optionString = const_cast<char*>(default_options_);
      create_jvm( &options, 1 );
   }

   jvm( std::string extra_options )
   {
      JavaVMOption options[2];
      options[0].optionString = const_cast<char*>(default_options_);
      options[1].optionString = const_cast<char*>(extra_options.c_str());
      create_jvm( options, 2 );
   }

   ~jvm()
   {
      jvm_->DestroyJavaVM();
   }

   int version() noexcept { return env_->GetVersion(); }

   JNIEnv& get_env() noexcept { return *env_; }

   void check_for_exceptions()
   {
      /*if( env_->ExceptionCheck() == JNI_TRUE )
      {
         //jthrowable except = env_->ExceptionOccurred();
         std::cout << "EXCEPTION Happened" << std::endl;
         env_->ExceptionDescribe();
         env_->ExceptionClear();
      }*/
   }

private:
   const char* default_options_ = "-Djava.class.path=./java";
   JavaVM* jvm_ = nullptr;
   JNIEnv* env_ = nullptr;

   void create_jvm( JavaVMOption* opts, const size_t num_opts )
   {
      JavaVMInitArgs vm_args;
      vm_args.version = JNI_VERSION_1_8;        // minimum Java version
      vm_args.nOptions = num_opts;
      vm_args.options = opts;
      vm_args.ignoreUnrecognized = JNI_FALSE;   // invalid options make the JVM init fail

      //=============== load and initialize Java VM and JNI interface =============
      jint rc = JNI_CreateJavaVM( &jvm_, reinterpret_cast<void**>(&env_), &vm_args );
      if (rc != JNI_OK)
      {
         throw std::system_error( rc, jni_error_category(), "[jvm::jvm] JNI_CreateJavaVM error" );
      }
   }
};

};
