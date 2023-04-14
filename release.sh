rm -r release

echo "building for win platform..."
mkdir -p release/win
./setup.sh w > release/win/log 2>&1
x86_64-w64-mingw32-g++ -O3 main.cpp -o release/win/correlator.exe -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> release/win/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` release/win/
if [ -z `ls release/win | grep correlator` ]; then
    echo "error on release for win"
else
    rm release/win/log
    zip -r release/win.zip release/win
fi

echo "building for linux platform..."
mkdir -p release/linux
./setup.sh l > release/linux/log 2>&1
g++ -O3 main.cpp -o release/linux/correlator -std=c++17 -Wall -Ldev -l:`ls dev/ | grep 'libkissfft-.*so$'` >> release/linux/log 2>&1
cp dev/`ls dev/ | grep 'libkissfft-.*so$'` release/linux/
if [ -z `ls release/linux | grep correlator` ]; then
    echo "error on release for linux"
else
    rm release/linux/log
    zip -r release/linux.zip release/linux
fi