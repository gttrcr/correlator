rm -r build

mkdir -p build/w
./setup.sh w > build/w/log 2>&1
x86_64-w64-mingw32-g++ -g main.cpp -o build/w/correlator.exe -std=c++17 -Wall -Ldev -l:libkissfft-double.so >> build/w/log 2>&1
cp dev/libkissfft-double.so build/w/

mkdir -p build/l
./setup.sh l > build/w/log 2>&1
g++ -g main.cpp -o build/l/correlator -std=c++17 -Wall -Ldev -l:libkissfft-double.so >> build/w/log 2>&1
cp dev/libkissfft-double.so build/l/