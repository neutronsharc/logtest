exe = spdlogtest easylogtest

all : $(exe)

spdlogtest : spdlogtest.cpp
	g++ -std=c++11 -g $^ -o $@ -lpthread

easylogtest : easylogtest.cpp
	g++ -std=c++11 -g $^ -o $@ -lpthread

clean:
	rm -f *.o $(exe)
