# correlator

## Versions, tags and releases
| Latest stable |   Policy    |  Tag  |    Win32    |       Win64        |       Linux        |                                   Link                                    |
| :-----------: | :---------: | :---: | :---------: | :----------------: | :----------------: | :-----------------------------------------------------------------------: |
|        *       |   Release   |  0.3  | :x: |    :heavy_check_mark:     | :heavy_check_mark: |  [releases/tag/0.3](https://github.com/gttrcr/correlator/releases/tag/0.3)     |                                                                
|              |   Release   |  0.2  |     :x:     | :heavy_check_mark: | :heavy_check_mark: | [releases/tag/0.2](https://github.com/gttrcr/correlator/releases/tag/0.2) |
|               | Pre release |  0.1  |     :x:     | :heavy_check_mark: | :heavy_check_mark: | [releases/tag/0.1](https://github.com/gttrcr/correlator/releases/tag/0.1) |

Each release folder also contains some example datasets [test_csv](https://github.com/gttrcr/correlator/tree/main/test_csv) so you can immediately test the correct functioning of the program on real data: in case of errors, any [issue](https://github.com/gttrcr/correlator/issues) is welcome :wink:.

## Introduction and motivation
Many datasets are composed of real scalar functions (scalar function for short) or are amenable to scalar functions. In the most general case, a scalar function is a function $f\colon\mathbb{R}^n\to\mathbb{R}$. Therefore an input csv file with $n+1$ columns is interpreted as a function $f\colon\mathbb{R}^n\to\mathbb{R}$.

Just add the csv files you want to analyze inside the executable folder and the program will start processing. Every execution of ```correlator``` do the following:
1. Look for every csv file in the execution folder.
2. Compute the best polynomial fit for every pair of input (on the y axis) and for every file (x with respect to y).
3. Compute fft for every input file.
4. Compute peaks in every fft.
5. Compute the best polynomial fit for the migration of peaks at point 4.

The results are placed inside the ```out_correlator``` default folder (or the output folder you decide from cli). The folder contains many files (sometimes hundreds :wink:). But the filename structure is pretty straightforward. Consider the following tree.
```
.
├── a_6_28.csv  (this is an example file)
├── b_9_42.csv  (this is an example file)
├── c_14_13.csv (this is an example file)
├── correlator  (this is the program)
├── d_21_20.csv (this is an example file)
├── libkissfft-float.so (libkissfft library)
└── out_correlator (default output folder)
    ├── fft (subdirectory with all fft computations)
    │   ├── a_6_28.csv  (computation of fft of the corresponding input file)
    │   ├── b_9_42.csv  (computation of fft of the corresponding input file)
    │   ├── c_14_13.csv (computation of fft of the corresponding input file)
    │   └── d_21_20.csv (computation of fft of the corresponding input file)
    ├── peaks (subdirectory with peaks coming from fft computation)
    │   ├── a_6_28.csv  (computation of peaks of fft of the corresponding input file)
    │   ├── b_9_42.csv  (computation of peaks of fft of the corresponding input file)
    │   ├── c_14_13.csv (computation of peaks of fft of the corresponding input file)
    │   └── d_21_20.csv (computation of peaks of fft of the corresponding input file)
    └── polyfit (subdirectory of all polynomials fit)
        ├── cross.csv
        └── single.csv

4 directories, 16 files
```

In the case of the ```polyfit``` I decided to merge all the files so as to avoid having a large amount of generated files to check. polyfit files are sorted by decreasing $r^2$ and increasing degree.

## Features
Consider the following table where :heavy_check_mark: means _done_, :hourglass: means _it will come_, :thinking: means _I am thinking how to do it_.
|                        Feature                         |       Status       |
| :----------------------------------------------------: | :----------------: |
|                   Support csv files                    | :heavy_check_mark: |
|            Support csv files separated by ;            | :heavy_check_mark: |
|            Support multi columns csv files             | :heavy_check_mark: |
|                          Fft                           | :heavy_check_mark: |
|                       Fft peaks                        | :heavy_check_mark: |
|                        Polyfit                         | :heavy_check_mark: |
|                 Basic peaks migration                  | :heavy_check_mark: |
|              Complete fft peaks migration              |    :hourglass:     |
|               Multidimensional analysis                |    :hourglass:     |
|         polyfix for the distribution of peaks          |     :thinking:     |
| listen to data coming from socket, pipe, stream or api |     :thinking:     |
|                  Realtime statistics                   |     :thinking:     |

## CLI
Conside the following table for the cli.
|             Option name              | Option command |      Default value      |       Accepted type        |       Status       |
| :----------------------------------: | :------------: | :---------------------: | :------------------------: | :----------------: |
|         Input file or folder         |       -i       |            .            | string interpreted as path | :heavy_check_mark: |
|   Output folder for -i input files   |       -o       |    ./out_correlator     | string interpreted as path | :heavy_check_mark: |
|    Number of fft peaks to compute    |       -e       |            5            |        unsigned int        | :heavy_check_mark: |
|        Codomain column index         |       -c       |            1            |        unsigned int        | :heavy_check_mark: |
|             Domain size              |       -d       |            1            |        unsigned int        | :heavy_check_mark: |
|    Port for the socket connection    |       -p       |          39785          |        unsigned int        |    :hourglass:     |
| Output folder for socket correlation |       -s       | ./socket_out_correlator | string interpreted as path |    :hourglass:     |

## Dev section (linux only)
Since it's easier to compile for windows on linux than to compile on windows for linux I unquestionably established that all development will take place on linux so the scripts placed here and there in the repo are all ```.sh``` (that's not true: if you have proposals to implement a development process directly for windows leave feedback via [issue](https://github.com/gttrcr/correlator/issues) :face_in_clouds:).

There are two ```.sh``` scripts.
* ```./setup.sh platform``` sets up the system, update and init all submodules, configure the platform and the compiler. ```platform``` is:
  * ```win32``` for windows 32 bits
  * ```win64``` for windows 64 bits
  * ```linux```for linux
* ```./release.sh``` releases every supported platform and produces the zip files that will be distributed.

### main.cpp steps
```
main
    get_arguments
       get_csv_files
           correlate_from_files
               get_functions
                   read_csv
                       get_function
                           all_methods
```