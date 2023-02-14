	rm -rf build
	mkdir build
	cd build
	cmake .. -DCOMPILE_EXECUTABLE=ON -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
	cmake --build .
	./app/Executable 