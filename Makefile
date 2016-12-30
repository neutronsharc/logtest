exe = hcdlogtest spdlogtest easylogtest

objs = hcdlog.o

all : $(exe)

hcdlogtest : hcdlogtest.o $(objs)
	g++ -std=c++11 -g $^ -o $@ -lpthread

spdlogtest : spdlogtest.o
	g++ -std=c++11 -g $^ -o $@ -lpthread

easylogtest : easylogtest.o
	g++ -std=c++11 -g $^ -o $@ -lpthread

%.o : %.cpp
	g++ -std=c++11 -g -c $< -o $@

clean:
	rm -f *.o $(exe)
