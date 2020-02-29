#!/bin/bash
script=$(readlink -e $0)
root_dir=$(dirname $script)
export PATH=../../src:../../../src:/opt/panda/bin:$PATH

mkdir -p sail_sim
cd sail_sim
echo "# HLS synthesis, testbench generation and simulation with Verilator"
bambu -v4 $root_dir/module.cpp --compiler=I386_CLANG6 --no-iob --evaluation --clock-period=10 --speculative-sdc-scheduling --print-dot --verbosity=4 --simulate --generate-tb=$root_dir/test.xml --simulator=VERILATOR --pretty-print=a.c --device-name=nangate45 --memory-allocation-policy=ALL_BRAM --experimental-setup=BAMBU-BALANCED
return_value=$?
if test $return_value != 0; then
   exit $return_value
fi

