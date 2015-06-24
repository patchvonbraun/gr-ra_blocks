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

#ifndef INCLUDED_RA_BLOCKS_SYNCH_CLOCK_IMPL_H
#define INCLUDED_RA_BLOCKS_SYNCH_CLOCK_IMPL_H

#include <ra_blocks/synch_clock.h>

namespace gr {
  namespace ra_blocks {

    class synch_clock_impl : public synch_clock
    {
     private:
      // Nothing to declare in this block.
      int d_clkdiv;
      float d_hval, d_lval;
      int d_state;
      float d_out;
      int d_ctr;

     public:
      synch_clock_impl(int clkdiv, float hval, float lval);
      ~synch_clock_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	  
	  void set_clkdiv (int clkdiv);
	  void set_hval (float hval);
	  void set_lval (float lval);
	  
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_SYNCH_CLOCK_IMPL_H */

