INC = -I/usr/lib64/jvm/java-1.8.0-openjdk-1.8.0/include -I/usr/lib64/jvm/java-1.8.0-openjdk-1.8.0/include/linux
LIB = -L/usr/lib64/jvm/java-1.8.0-openjdk-1.8.0/jre/lib/amd64/server

all:
	$(CXX) -Wall -Wextra -O0 -ggdb3 $(INC) --std=c++11 -pthread main.cpp -o test_jonc $(LIB) -ljvm
