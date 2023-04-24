# correlator

## Release and tag
|Latest|Release|Tag|Win32|Win64|Linux|Link|
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|*|Pre|0.1|:x:|:heavy_check_mark:|:heavy_check_mark:|[https://github.com/gttrcr/correlator/releases/tag/0.1](https://github.com/gttrcr/correlator/releases/tag/0.1)|
||||||

## Introduction and motivation
Many datasets are composed of real scalar functions (scalar function for short) or are amenable to scalar functions. In the most general case, a scalar function is a function $f\colon\mathbb{R}^n\to\mathbb{R}$. Therefore an input csv file with $n+1$ columns is interpreted as a function $f\colon\mathbb{R}^n\to\mathbb{R}$.

Just add the csv files you want to analyze inside the executable folder and the program will start processing. Every execution of ```correlator``` do the following:
1. Look for every csv file in the execution folder.
2. Compute the best polynomial fit for every pair of input (on the y axis) and for every file (x with respect to y).
3. Compute fft for every input file.
4. Compute peaks in every fft.
5. Compute the best polynomial fit for the migration of peaks at point 4.

The results are placed inside the ```output``` folder. The folder contains many files (sometimes hundreds :wink:). But the filename structure is pretty straightforward. Let $n$ be the number of input datasets, then consider the following table.
|File name|File type|Category|Content|
|:-:|:-:|:-:|:-:|
|polyfit_```filename```|csv|polyfit|Coefficients of the polynomial that best fits the data contained within ```filename``` up to the ```polyfit_max_degree```-th degree|
|polyfit|csv|polyfit|Coefficients of the polynomials that best fits the $y$-values (codomain) of every dataset up to the ```polyfit_max_degree```-th degree|
|fft_```filename```|csv|FFT|FFT of ```filename```|
|fft_peaks_```filename```|csv|FFT|First ```fft_peaks_number``` peaks of FFT of ```filename```|
|peak_migration_$i$|csv|FFT and polyfit|Coefficients of the polynomial that best first the migration of the $i$-th peak. $i\in\left[1, n\right]$|

## upcoming features
1. fft of peaks at point 4.
2. multidimensional fft
3. Compute the best polynomial fit for the distribution of peaks at point 4.
4. ```correlator``` will listen to new data (by socket, by pipe, by stream, by api, ...) and compute real time statistics.

## Dev section
### setup
Launch ```./setup.sh platform``` where ```platform``` is:
* ```win32``` for windows 32 bits
* ```win64``` for windows 64 bits
* ```linux```for linux

It sets up the system, update and init all submodules, configure the platform and the compiler.

### release
Launch ```./release.sh```. It releases every supported platform
