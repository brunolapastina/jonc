INC = -I$(JAVA_HOME)/include \
		-I$(JAVA_HOME)/include/linux \
		-I../../include
LIB = -L$(JAVA_HOME)/jre/lib/amd64/server

all:
	javac -cp . -sourcepath . PrimitiveTypes.java
	$(CXX) -Wall -Wextra -O0 -ggdb3 $(INC) --std=c++11 -pthread main.cpp -o test_primitive_types $(LIB) -ljvm

clean:
	rm -f *.class *.o test_primitive_types
