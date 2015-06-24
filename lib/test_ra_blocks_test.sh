#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/mleech/gr-ra_blocks/trunk/lib
export PATH=/home/mleech/gr-ra_blocks/trunk/lib:$PATH
export LD_LIBRARY_PATH=/home/mleech/gr-ra_blocks/trunk/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-ra_blocks 
