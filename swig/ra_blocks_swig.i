/* -*- c++ -*- */

#define RA_BLOCKS_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ra_blocks_swig_doc.i"

%{
#include "ra_blocks/slicer.h"
#include "ra_blocks/vector_power.h"
#include "ra_blocks/synch_folder.h"
#include "ra_blocks/synch_detect.h"
#include "ra_blocks/synch_clock.h"
%}


%include "ra_blocks/slicer.h"
GR_SWIG_BLOCK_MAGIC2(ra_blocks, slicer);
%include "ra_blocks/vector_power.h"
GR_SWIG_BLOCK_MAGIC2(ra_blocks, vector_power);
%include "ra_blocks/synch_folder.h"
GR_SWIG_BLOCK_MAGIC2(ra_blocks, synch_folder);
%include "ra_blocks/synch_detect.h"
GR_SWIG_BLOCK_MAGIC2(ra_blocks, synch_detect);
%include "ra_blocks/synch_clock.h"
GR_SWIG_BLOCK_MAGIC2(ra_blocks, synch_clock);
