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
#include "synch_clock_impl.h"

namespace gr {
  namespace ra_blocks {

    synch_clock::sptr
    synch_clock::make(int clkdiv, float hval, float lval)
    {
      return gnuradio::get_initial_sptr
        (new synch_clock_impl(clkdiv, hval, lval));
    }

    /*
     * The private constructor
     */
    synch_clock_impl::synch_clock_impl(int clkdiv, float hval, float lval)
      : gr::sync_block("synch_clock",
		      gr::io_signature::make(1, 1, sizeof(float)),
		      gr::io_signature::make(1, 1, sizeof(float)))
    {
		d_state = 1;
		d_out = hval;
		d_hval = hval;
		d_lval = lval;
		d_clkdiv = clkdiv;
		d_ctr = 0;
	}
	
	void
	synch_clock_impl::set_clkdiv (int clkdiv)
	{
		d_clkdiv = clkdiv;
	}
	
	void
	synch_clock_impl::set_hval (float hval)
	{
		d_hval = hval;
	}
	
	void
	synch_clock_impl::set_lval (float lval)
	{
		d_lval = lval;
	}
	
	

    /*
     * Our virtual destructor.
     */
    synch_clock_impl::~synch_clock_impl()
    {
    }

    int
    synch_clock_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];
        float vals[] = {d_lval, d_hval};
        int next[] = {1, 0};

        for (int i = 0; i < noutput_items; i++)
        {
			d_ctr++;
			if (d_ctr >= d_clkdiv)
			{
				d_state = next[d_state];
				d_ctr = 0;
				d_out = vals[d_state];
			}
			*out = d_out;
			out++;
		}

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ra_blocks */
} /* namespace gr */

