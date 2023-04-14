# correlator

## setup
Launch ```./setup.sh platform``` where ```platform``` is:
* ```w``` for windows
* ```l```for linux

It sets up the system, update and init all submodules, configure the platform and the compiler.

## build
Launch  ```./build.sh```. It builds for every supported platform

## release
Launch ```./release.sh```. It releases every supported platform

## features
Every execution of ```correlator``` do the following:
1. Look for every ```*.csv``` file in the execution folder.
2. Compute the best polynomial fit for every pair of input (on the y axis) and for every file (x with respect to y).
3. Compute fft for every input file.
4. Compute peaks in every fft.
5. Compute the best polynomial fit for the migration of peaks at point 4.

## upcoming features
1. fft of peaks at point 4.
2. multidimensional fft
3. Compute the best polynomial fit for the distribution of peaks at point 4.
4. ```correlator``` will listen to new data (by socket, by pipe, by stream, by api, ...) and compute real time statistics.