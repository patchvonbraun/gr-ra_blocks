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

#ifndef INCLUDED_RA_BLOCKS_VECTOR_POWER_IMPL_H
#define INCLUDED_RA_BLOCKS_VECTOR_POWER_IMPL_H
#include <vector>
#include <ra_blocks/vector_power.h>

namespace gr {
  namespace ra_blocks {

    class vector_power_impl : public vector_power
    {
     private:
      std::vector<int> d_begins;
      std::vector<int> d_ends;
      int d_vecsize;
      int d_nstream;

     public:
      vector_power_impl(int vecsize, int nstream);
      ~vector_power_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	  
	  void set_positions (const std::vector<int> &begins, const std::vector<int> &ends);
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_VECTOR_POWER_IMPL_H */

