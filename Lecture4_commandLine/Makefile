#using makefile script we can run cmake easy way
prepare:
	rm -rf build
	mkdir build
	cd build
#	cmake -S . -B build
	cmake -S . -B build -DCOMPILE_EXECUTABLE=ON 
#This is only option if you required
	cmake --build build/
	./build/app/Executable 
# clean build and compiler finally run it
# -DCOMPILE_EXECUTABLE=ON D = define and then COMPILE_EXECUTABLE=ON is variable set
 