.PHONY: test

all:
	g++ -g -std=c++11 generacsv.cpp -o test

clean:
	rm ./test
	
test:
	./test < peorcaso.txt > peorcaso.csv
	./test < mejorcaso.txt > mejorcaso.csv
