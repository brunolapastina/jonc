/**
 * JONC primitive type conversion test
 *
 * This test will load the JVM, instanciate a Java class and call some methods to test the automatic value conversion
 *
 */

#include <iostream>
#include "jonc/jonc.hpp"

int main()
{
   try
   {
      // Load the JVM without any parameters (default constructed)
      jonc::jvm vm;

      // Create an instance of the PrimitiveTypes class
      jonc::jclass_instance  inst( vm, "PrimitiveTypes" );

      inst.call_method<void>( "myvoid" );
      inst.call_method<void>( "mymain", 10 );
      inst.call_method<void>( "mystring", std::string("ola") );

      std::cout << "mystringcomp = " << inst.call_method<bool>( "mystringcomp", std::string("olaa") ) << std::endl;
      std::cout << "mystringcomp = " << inst.call_method<bool>( "mystringcomp", std::string("ola") ) << std::endl;

      std::cout << "alwaysTrue  = " << inst.call_method<bool>( "alwaysTrue" )  << std::endl;
      std::cout << "alwaysFalse = " << inst.call_method<bool>( "alwaysFalse" ) << std::endl;
   }
   catch( std::exception& e )
   {
      std::cout << e.what() << std::endl;
   }

   return 0;
}
