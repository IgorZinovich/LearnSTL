.PHONY: all clean

STD_FLAG = -std=c++20
TBB_FLAG = -ltbb
TARGET = algoritm

all: ${TARGET}

main.o: main.cpp
	g++ -c ${STD_FLAG} -o main.o main.cpp 

${TARGET} : main.o
	g++ -o ${TARGET} main.o ${TBB_FLAG}

clean:
	rm ${TARGET}
