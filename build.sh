rm -r build

echo "building for win platform..."
mkdir -p build/w
./setup.sh w > build/w/log 2>&1
x86_64-w64-mingw32-g++ -g main.cpp -o build/w/correlator.exe -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> build/w/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` build/w/

echo "building for linux platform..."
mkdir -p build/l
./setup.sh l > build/l/log 2>&1
g++ -g main.cpp -o build/l/correlator -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> build/l/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` build/l/