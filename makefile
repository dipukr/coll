CXX = g++ -c -O3 -std=c++17

main: error.o hash.o chars.o
	ar -rcs libcoll.a error.o hash.o chars.o

error.o: error.h error.cxx
	$(CXX) error.cxx

hash.o: hash.h hash.cxx
	$(CXX) hash.cxx	

chars.o: chars.h chars.cxx
	$(CXX) chars.cxx

clean:
	rm *.o

install:
	cp error.h chars.h array.h list.h stack.h queue.h /usr/include/coll/
	mv libcoll.a /usr/lib64/
	mv collib /usr/include/