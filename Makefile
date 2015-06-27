all:
	g++ -std=c++11 main.cpp src/vklib.cpp src/jsoncpp/jsoncpp.o -l curl -o vkapp
clean:
	rm -rf *.o vkapp
