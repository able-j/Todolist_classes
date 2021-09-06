CFLAGS = -c -I/usr/local/include -O2
LINK = -I/usr/local/include -O2
WINCC = i686-w64-mingw32-g++

default: todolist

win: todolist_win

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

todolist_win: task_win.o list_win.o main_win.o jsoncpp_win.o
	$(WINCC) $(LINK) -o todolist.exe main_win.o task_win.o list_win.o jsoncpp_win.o -static

task_win.o:
	$(WINCC) $(CFLAGS) -o task_win.o task.cpp

list_win.o:
	$(WINCC) $(CFLAGS) -o list_win.o list.cpp

main_win.o:
	$(WINCC) $(CFLAGS) -o main_win.o main.cpp

jsoncpp_win.o:
	$(WINCC) $(CFLAGS) -o jsoncpp_win.o jsoncpp.cpp

clean:
	rm -rf todolist todolist.exe *.o
