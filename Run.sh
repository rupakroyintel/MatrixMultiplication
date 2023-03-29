#!/bin/bash

oneAPI_Ver=2022.0.1

if [ "$1" == "" ]; then
  echo "Usage: compiler [Opt]"
  echo "  where"
  echo "    compiler is gcc or icc or icx"
  exit
fi

OPT=""
if [ "$2" != "" ]; then
  OPT="Opt"
fi

EXE=./MatrixMultiplication${OPT}_$1

if [ "$1" != "gcc" ]; then
  # source /opt/intel/oneapi/setvars.sh
  source /opt/intel/oneapi/compiler/${oneAPI_Ver}/env/vars.sh
fi

echo "$EXE"
$EXE

