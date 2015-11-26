#!/bin/sh

root_dir=`pwd | xargs basename`

if [ "$root_dir" != "excalibur" ]
then
  echo "Please execute build script under root dir: excalibur/"
  echo "Example:"
  echo "    sh src/script/build_excalibur.sh"
  exit 1
fi

# create output directory
outdir=output
if [ -d $outdir ]
then
  rm -rfv $outdir
fi
pwd
mkdir -p $outdir

# start build binary
cd src
make
mv *.o ../$outdir
cp -v Makefile ../$outdir
cp -v link.ld ../$outdir
cd ../$outdir
make link
cd - > /dev/null

