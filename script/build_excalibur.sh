#!/bin/sh

base=$(pwd)
root_dir=$(pwd | xargs basename)
src_dir="$base/src";

if [ "$root_dir" != "excalibur" ]
then
    echo "Please execute build script under root dir: excalibur/"
    echo "Example:"
    echo "    sh src/script/build_excalibur.sh"
    exit 1
fi

## create output directory ##
outdir=output
if [ -d $outdir ]
then
    rm -rfv $outdir
fi
mkdir -p $outdir

## Generate C function declaration header file ##
perl script/generate_declaration.pl $src_dir

## Generate sub-module Makefile ##
# echo "== Generate Compile Makefile for Sub-Module =="
perl script/produce_compile_makefile.pl $src_dir

## Iterate sub-module and build objective file ##
module_list=$(find src/ -type d | grep -v inc)

for var in ${module_list[@]}
do
    cd $var > /dev/null
    make
    mv -v *.o $base/$outdir
    cd - > /dev/null
done

## Generate kernel link Makefile and prepare link script ##
# echo "== Generate Link Makefile for Kernel binary =="
cp -v script/link.ld $outdir
perl script/produce_link_makefile.pl

## Start linking and export finial kernel binary ##
cd $outdir > /dev/null
make
cd - > /dev/null

elf=$base/$outdir/kernel

file $elf
echo "Kernel Binary Build Sucess at <$elf>."

