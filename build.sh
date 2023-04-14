rm -r build

echo "building for win platform..."
mkdir -p build/win
./setup.sh w > build/win/log 2>&1
x86_64-w64-mingw32-g++ -g main.cpp -o build/win/correlator.exe -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> build/win/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` build/win/
if [ -z `ls build/win | grep correlator` ]; then
    echo "error on build for win"
else
    rm build/win/log
    zip -r build/win.zip build/win
fi

echo "building for linux platform..."
mkdir -p build/linux
./setup.sh l > build/linux/log 2>&1
g++ -g main.cpp -o build/linux/correlator -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> build/linux/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` build/linux/
if [ -z `ls build/linux | grep correlator` ]; then
    echo "error on build for linux"
else
    rm build/linux/log
    zip -r build/linux.zip build/linux
fi