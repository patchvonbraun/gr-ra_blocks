/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_RA_BLOCKS_SLICER_IMPL_H
#define INCLUDED_RA_BLOCKS_SLICER_IMPL_H

#include <ra_blocks/slicer.h>

namespace gr {
  namespace ra_blocks {

    class slicer_impl : public slicer
    {
     private:
      float *d_slbuf;
      float d_thresh;
      int d_decim;
      int d_ratio;
      int d_ctr;

     public:
      slicer_impl(int decim, float thresh, int ratio);
      ~slicer_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	  
	  void set_thresh (float thresh);
	  void set_ratio (int ratio);
	  
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_SLICER_IMPL_H */

