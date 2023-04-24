options="-static-libgcc -static-libstdc++ -std=c++17 -Wall -Ldev -l:libkissfft-float.so"

rm -r release

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