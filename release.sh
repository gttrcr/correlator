rm -r release

echo "building for win platform..."
mkdir -p release/w
./setup.sh w > release/w/log 2>&1
x86_64-w64-mingw32-g++ -O3 main.cpp -o release/w/correlator.exe -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> release/w/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` release/w/

echo "building for linux platform..."
mkdir -p release/l
./setup.sh l > release/l/log 2>&1
g++ -O3 main.cpp -o release/l/correlator -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> release/l/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` release/l/