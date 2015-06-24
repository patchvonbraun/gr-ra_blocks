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
#include "synch_folder_impl.h"

/*
 * Implements a synchronous "folder", as used in post-detector pulsar processing where you try to
 *   "lay down" pulses, one on top of another, to improve the SNR
 * 
 * The constraint is that the input samples have been re-sampled to a new sample rate
 *   that is (vecsize * pulse_rate)
 * 
 */
namespace gr {
  namespace ra_blocks {

    synch_folder::sptr
    synch_folder::make(int outvecsize, int folding)
    {
      return gnuradio::get_initial_sptr
        (new synch_folder_impl(outvecsize, folding));
    }

    /*
     * The private constructor
     */
    synch_folder_impl::synch_folder_impl(int outvecsize, int folding)
      : gr::sync_decimator("synch_folder",
		      gr::io_signature::make(1, 1, sizeof(float)),
		      gr::io_signature::make(1, 1, sizeof(float)*outvecsize), outvecsize*folding)
    {
		d_fbuf = (float *)malloc (outvecsize * sizeof(float));
		memset (d_fbuf, 0x0, sizeof(float)*outvecsize);
		
		d_folding = folding;
		d_vecsize = outvecsize;
		d_fctr = 0;
	}
	
    /*
     * Our virtual destructor.
     */
    synch_folder_impl::~synch_folder_impl()
    {
		if (d_fbuf != NULL)
		{
			free (d_fbuf);
		}
    }

	void
	synch_folder_impl::set_folding (int folding)
	{
		d_folding = folding;
		memset (d_fbuf, 0x0, sizeof(float)*d_vecsize);
		set_decimation (d_vecsize * folding);
	}
	
    int
    synch_folder_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];
		float a = 1.0 / (double)d_folding;
		int nitems = 0;
		
		/*
		 * For each output item (which will be of size vecsize)
		 */
		for (int i = 0; i < noutput_items; i++)
		{
			for (int j = 0; j < d_vecsize; j++)
			{	
				float x;
				
				d_fbuf[j] += in[j];
			}
			d_fctr++;
			in += d_vecsize;

			/*
			 * Output the folded samples
			 */
			if (d_fctr >= d_folding)
			{
				for (int k = 0; k < d_vecsize; k++)
				{
					d_fbuf[k] /= (float)d_folding;
				}
				d_fctr = 0;
				
				/*
				 * Produce a folded output
				 */
				memcpy (out, d_fbuf, sizeof(float)*d_vecsize);
				
				out += d_vecsize;
				nitems++;
			}
		}
		
		consume_each (noutput_items);
        // Tell runtime system how many output items we produced.
        return nitems;
    }

  } /* namespace ra_blocks */
} /* namespace gr */

