options="-static-libgcc -static-libstdc++ -std=c++17 -Wall -Wpedantic -Ldev -O3 -l:libkissfft-float.so"

mkdir -p release #create if not exists
rm -r release #remove in any case

execute ()
{
    echo "building for $PLATFORM platform..."
    mkdir -p release/$PLATFORM
    ./setup.sh $PLATFORM > release/$PLATFORM/log 2>&1

    if [ "$PLATFORM" == "win32" ]; then
        i686-w64-mingw32-g++ main.cpp -o release/$PLATFORM/correlator.exe -static $options >> release/$PLATFORM/log 2>&1
    elif [ "$PLATFORM" == "win64" ]; then
        x86_64-w64-mingw32-g++ main.cpp -m64 -DBITS=64 -o release/$PLATFORM/correlator.exe -static $options >> release/$PLATFORM/log 2>&1
    elif [ "$PLATFORM" == "linux" ]; then
        g++ main.cpp -o release/$PLATFORM/correlator $options >> release/$PLATFORM/log 2>&1
    else
        echo "Unknown platform $PLATFORM"
        exit
    fi

    cp dev/libkissfft-float.so release/$PLATFORM/
    
    if [[ "$PLATFORM" == *"win"* ]]; then
        mv release/$PLATFORM/libkissfft-float.so release/$PLATFORM/libkissfft-float.so.131.1.0
    fi
    
    if [ -z `ls release/$PLATFORM | grep correlator` ]; then
        echo "Error on release for $PLATFORM"
        exit
    else
        rm release/$PLATFORM/log
        cp -a ../test_csv/. release/$PLATFORM
        cd release
        zip -r $PLATFORM.zip $PLATFORM/
        cd ..
    fi
}

PLATFORM="win32"
execute

PLATFORM="win64"
execute

PLATFORM="linux"
execute

echo "Relese completed for every supported platform"
echo "Press ENTER to create a relese on public repo"
read -s -n 1 key
if [[ $key = "" ]]; then 
    echo "Enter TAG name for the RELEASE (TAG and RELEASE will have the same name)"
    read tagname
    git clone git@github.com:gttrcr/correlator.git
    cd correlator
    cp ../../README.md .
    git add .
    git commit -m 'update README.md for release $tagname'
    git push
    gh release create v$tagname --generate-notes ../release/linux.zip ../release/win64.zip ../release/win32.zip
    cd ..
    rm -rf correlator
else
    echo "You pressed '$key'. Bye bye!"
fi