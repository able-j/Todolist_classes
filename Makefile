CFLAGS = -c -I/usr/local/include -g
LINK = -I/usr/local/include -L/usr/local/lib -l:libjsoncpp.so -g

default: todolist

todolist: task.o list.o main.o # add list.o, date.o
	c++ $(LINK) -o todolist main.o task.o list.o

main.o: main.cpp
	c++ $(CFLAGS) -o main.o main.cpp

list.o:
	c++ $(CFLAGS) -o list.o list.cpp

task.o:
	c++ $(CFLAGS) -o task.o task.cpp

clean:
	rm -rf todolist *.o
