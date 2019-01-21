INC = -I/usr/lib64/jvm/java-1.8.0-openjdk-1.8.0/include \
		-I/usr/lib64/jvm/java-1.8.0-openjdk-1.8.0/include/linux\
		-I../../include
LIB = -L/usr/lib64/jvm/java-1.8.0-openjdk-1.8.0/jre/lib/amd64/server

all:
	javac -cp . -sourcepath . MyTest.java
	$(CXX) -Wall -Wextra -O0 -ggdb3 $(INC) --std=c++11 -pthread main.cpp -o test_jonc $(LIB) -ljvm

clean:
	rm -f *.class *.o test_primitive_types
