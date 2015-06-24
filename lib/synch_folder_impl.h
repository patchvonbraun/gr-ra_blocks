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

#ifndef INCLUDED_RA_BLOCKS_SYNCH_FOLDER_IMPL_H
#define INCLUDED_RA_BLOCKS_SYNCH_FOLDER_IMPL_H

#include <ra_blocks/synch_folder.h>

namespace gr {
  namespace ra_blocks {

    class synch_folder_impl : public synch_folder
    {
     private:
      // Nothing to declare in this block.
      int d_folding;
      float *d_fbuf;
      int d_vecsize;
      int d_fctr;

     public:
      synch_folder_impl(int outvecsize, int folding);
      ~synch_folder_impl();

      // Where all the action really happens
      int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
	       
	  void set_folding (int folding);
	  
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_SYNCH_FOLDER_IMPL_H */

