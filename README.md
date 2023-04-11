# correlator

## setup
sudo apt update 
sudo apt upgrade -y
sudo apt autoremove
git submodule update --init --recursive
sudo apt install libpng-dev -y
sudo apt install fftw3 fftw3-dev -y
cd kissfft
mkdir build
cd build
cmake -DKISSFFT_DATATYPE=double ..
make all
sudo make install
sudo ldconfig
cd ..
rm -rf build
