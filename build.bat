rm build
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER:FILEPATH=C:\Users\manbi\MinGW\bin\gcc.exe -DCMAKE_CXX_COMPILER:FILEPATH=C:\Users\manbi\MinGW\bin\g++.exe
cmake --build .
