# dst2root

Conversion program from hipo to root format for dst and skimmed files. This program also reindexes the detector banks and places them into their own banks so it is easier to read the files. See examples for how the files can now be read.

## To build:

    git clone --recurse-submodules https://github.com/tylern4/dst2root.git
    cd dst2root
    make

## To use
    ./dst2root infile.hipo outfile.root

## TODO

-   [ ] Check that all needed banks are present and correctly ported over.
