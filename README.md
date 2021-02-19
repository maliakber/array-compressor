# byte-array-compression
To compress an array of bytes to save memory and recover the data without loss of information

# How to run (using cmake)?
	1. Install cmake (https://cmake.org/install/)
	2. Go to the project folder and open terminal
	3. Run the following commands:
		mkdir build
		cd build
		cmake -DCMAKE_BUILD_TYPE=Release ..
		make
	4. Now run the program:
		./src/compressor
    5. To run the unit-test:
		./src/compressor-test

# How to run (manually using g++)?
    1. Go to the src folder inside the project folder
    2. Open terminal in that directory
	1. Compile the program:
		g++ -Wall -O3 -std=c++17 main.cpp utils/system.cpp -o compressor
			-Wall: with all warnings
			-O3: compiler optimization
			-std: using c++ standard 17
			-o: output binary name 
	2. Run the program:
        ./compressor
