all:
	g++ -o main ./src/*.cpp -I ./include/ -L ./lib -lsqlite3