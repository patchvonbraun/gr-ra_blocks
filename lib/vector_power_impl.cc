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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "vector_power_impl.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>

namespace gr {
  namespace ra_blocks {

    vector_power::sptr
    vector_power::make(int vecsize, int nstream)
    {
      return gnuradio::get_initial_sptr
        (new vector_power_impl(vecsize, nstream));
    }

    /*
     * The private constructor
     */
    vector_power_impl::vector_power_impl(int vecsize, int nstream)
      : gr::sync_block("vector_power",
		      gr::io_signature::make(1, 1, sizeof(float)*vecsize),
		      gr::io_signature::make(nstream, nstream, sizeof(float)))
    {
		d_vecsize = vecsize;
		d_nstream = nstream;
	}

    /*
     * Our virtual destructor.
     */
    vector_power_impl::~vector_power_impl()
    {
    }
	
	void
	vector_power_impl::set_positions (const std::vector<int> &begins, const std::vector<int> &ends)
	{
		if (begins.size() != d_nstream)
		{
			throw std::runtime_error ("Number of channel mappings must match number of streams\n");
		}
		d_begins.resize(begins.size());
		d_ends.resize(ends.size());
		
		for (int j = 0; j < begins.size(); j++)
		{
			if (ends[j] < begins[j])
			{
				char s[128];
				
				sprintf (s, "Position specifier for stream %d has begin > end\n", j);
				throw std::runtime_error (s);
			}
		}
		d_begins = begins;
		d_ends = ends;
	}
	
    int
    vector_power_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
      const float *in = (const float *) input_items[0];
      float **outv = (float **) &output_items[0];
      float sums[d_nstream];
      
	  for (int i = 0; i < noutput_items; i++)
	  {
		  for (int k = 0; k < d_nstream; k++)
		  {
			  sums[k] = 0.0f;
		  }
	      for (int j = 0; j < d_nstream; j++)
	      {
			  if (d_begins.size() == d_nstream)
			  {
				  if (d_ends[j] < d_begins[j])
				  {
					  throw std::runtime_error ("Position specifiers must have end > begin");
				  }
				  for (int k = d_begins[j]; k < d_ends[j]; k++)
				  {
					  if (k < d_vecsize)
					  {
						sums[j] += in[k];
					  }
				  }
			  }
			  memcpy(outv[j], &sums[j], sizeof(float));
			  outv[j]++;
		  }
		  in += d_vecsize;
      }
      return (noutput_items);
    }
  } /* namespace ra_blocks */
} /* namespace gr */

