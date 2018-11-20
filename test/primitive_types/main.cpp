#include <iostream>
#include "jonc/jonc.hpp"

int main()
{
   try
   {
      jonc::jvm vm;

      const auto ver = vm.version();
      std::cout << "JVM load succeeded: Version " << ((ver>>16)&0x0f) << "."<<(ver&0x0f) << std::endl;

      jonc::jclass_instance  inst( vm, "MyTest" );

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
