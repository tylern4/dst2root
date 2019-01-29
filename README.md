# dst2root
[![Build Status](https://travis-ci.org/tylern4/dst2root.svg?branch=master)](https://travis-ci.org/tylern4/dst2root)

Conversion program from hipo to root format for dst and skimmed files. This program also reindexes the detector banks and places them into their own banks so it is easier to read the files. See examples for how the files can now be read.

## To build:

    git clone --recurse-submodules https://github.com/tylern4/dst2root.git
    cd dst2root
    make

## To use
    ./dst2root infile.hipo outfile.root

## Running with Docker
When in the same directory as the input file:

```
docker run -v $PWD:/tmp tylern4/dst2root infile.hipo outfile.root
```

## Help
```
SYNOPSIS
    ./dst2root [-h] [-mc] [-b] [-r] [-e] [-c] <inputFile.hipo> [<outputFile.root>]

OPTIONS
    -h, --help  print help
    -mc, --MC   Convert dst and mc banks
    -b, --batch Don't show progress and statistics
    -r, --rec   Only save events where number of partilces in the event > 0
    -e, --elec  Only save events with good electron as first particle
    -c, --cov   Save Covariant Matrix for kinematic fitting
```

## Performance

Taking a skimmed dst file and converting it on Ubuntu 17.10, Intel(R) i7-3770 CPU @ 3.40GHz, reading and writing to an ssd.

| hipo   	| root    |
|:------:	|:------: |
| 14G 	  | 11G     |


| Conversion time   	| Events/Sec    |
|:-----------------:	|:------------: |
| 2349 seconds 	      | 3050 Hz       |
