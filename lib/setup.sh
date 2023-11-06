if [ -z "$1" ]; then
    echo "Platform is empty"
    exit
fi

git submodule update --init --recursive
sudo apt install libpng-dev -y
sudo apt install fftw3 fftw3-dev -y
sudo apt install mingw-w64 -y
sudo apt install cmake -y
sudo apt install pkg-config -y
sudo apt install zip -y
sudo apt install libtbb-dev -y

cd kissfft
mkdir -p build #create if not exists
rm -r build #remove in any case
mkdir build #create
cd build
if [ "$1" == "win32" ]; then
    cmake -DKISSFFT_DATATYPE=float -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=i686-w64-mingw32-g++ ..
elif [ "$1" == "win64" ]; then
    cmake -DKISSFFT_DATATYPE=float -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ ..
elif [ "$1" == "linux" ]; then
    cmake -DKISSFFT_DATATYPE=float ..
else
    echo "Unknown platform $1"
    exit
fi

make kissfft
cd ..
cd ..
mkdir -p dev #create if not exists
rm -r dev #remove in any case
cp -r kissfft/build dev/
rm -r kissfft/build

source ~/.bashrc
if [ -z `echo $LD_LIBRARY_PATH | grep $PWD/dev` ]; then
    echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/dev" >> ~/.bashrc
fi
source ~/.bashrc
