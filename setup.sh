#sudo apt update
#sudo apt upgrade -y
#sudo apt autoremove
git submodule update --init --recursive
sudo apt install libpng-dev -y
sudo apt install fftw3 fftw3-dev -y
sudo apt install mingw-w64 -y
sudo apt install cmake -y
sudo apt install pkg-config -y

platform=0
if [ -z "$1" ]; then
    echo "Platform is empty"
    echo "Launch /.setup.sh platform where platform is w for windows or l for linux"
    exit
elif [[ "$1" == "l" ]]; then
    echo "Platform is linux"
    platform=1
elif [[ "$1" == "w" ]]; then
    echo "Platform is windows"
    platform=2
else
    echo "Unknown platform $1. Use w for windows or l for linux"
    exit
fi

cd kissfft
rm -r build
mkdir build
cd build
if [ $platform == 1 ]; then
    cmake -DKISSFFT_DATATYPE=float ..
    make kissfft
elif [ $platform == 2 ]; then
    cmake -DKISSFFT_DATATYPE=float -DCMAKE_C_COMPILER=x86_64-w64-mingw32-gcc -DCMAKE_CXX_COMPILER=x86_64-w64-mingw32-g++ ..
    make kissfft
fi

cd ..
cd ..
rm -r dev
cp -r kissfft/build dev/
rm -r kissfft/build

if [ -z `echo $LD_LIBRARY_PATH | grep $PWD/dev` ]; then
    echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/dev" >> ~/.bashrc
fi