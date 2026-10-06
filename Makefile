all:
	g++ -Wall -o bk src/mainbk.cpp src/bkmeans.cpp

clean:
	rm -f bk result.txt
