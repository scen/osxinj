CXX = clang++
CXXFLAGS = -pipe -arch i386 -std=c++11 -stdlib=libc++ -W 

all: testapp

testapp:
	$(CXX) $(CXXFLAGS) main.cpp -o testapp

clean:
	rm testapp