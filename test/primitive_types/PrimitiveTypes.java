public class PrimitiveTypes {
   public PrimitiveTypes( int i )
   {
      System.out.println("Hello, World in java from PrimitiveTypes ctor " + i);
   }

   public PrimitiveTypes()
   {
      System.out.println("Hello, World in java from PrimitiveTypes ctor void" );
   }

   public void myvoid() {
      System.out.println("Hello, World from void");
   }

   public void mymain( int i ) {
       System.out.println("Hello, World in java from mymain " + i);
   }

   public void mystring( String s ) {
      System.out.println("Hello, World in java from mystring: " + s);
   }

   public boolean mystringcomp( String s )
   {
      return (s.length() == 3);
   }

   public boolean alwaysTrue()
   {
      return true;
   }

   public boolean alwaysFalse()
   {
      return false;
   }
}
