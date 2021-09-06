CFLAGS = -c -I/usr/local/include -O2
LINK = -I/usr/local/include -O2

default: todolist

todolist: task.o list.o main.o jsoncpp.o
	c++ $(LINK) -o todolist main.o task.o list.o jsoncpp.o

main.o: main.cpp
	c++ $(CFLAGS) -o main.o main.cpp

list.o:
	c++ $(CFLAGS) -o list.o list.cpp

task.o:
	c++ $(CFLAGS) -o task.o task.cpp

jsoncpp.o:
	g++ $(CFLAGS) -o jsoncpp.o jsoncpp.cpp

clean:
	rm -rf todolist *.o
