	rm -rf build
	mkdir build
	cd build
	cmake .. -DCOMPILE_EXECUTABLE=ON -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
	cmake --build .
	./app/Executable 

# external lib to using some function
#git submodule add https://github.com/nlohmann/json Lib/json