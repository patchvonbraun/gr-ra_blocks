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
#include "synch_detect_impl.h"
#include <math.h>

namespace gr {
  namespace ra_blocks {

    synch_detect::sptr
    synch_detect::make(int decim, float hval, float lval)
    {
      return gnuradio::get_initial_sptr
        (new synch_detect_impl(decim, hval, lval));
    }

    /*
     * The private constructor
     */
    synch_detect_impl::synch_detect_impl(int decim, float hval, float lval)
      : gr::sync_decimator("synch_detect",
		      gr::io_signature::make(2, 2, sizeof(float)),
		      gr::io_signature::make(1, 1, sizeof(float)), decim)
    {
		d_decim = decim;
		set_decimation (decim);
		d_dbuf = (float *)malloc (d_decim * sizeof(float));
		d_rbuf = (float *)malloc (d_decim * sizeof(float));
		d_rctr = 0;
		d_dctr = 0;
		d_totctr = 0;
		d_hval = hval;
		d_lval = lval;
	}
	
    /*
     * Our virtual destructor.
     */
    synch_detect_impl::~synch_detect_impl()
    {
		if (d_dbuf != NULL)
		{
			free (d_dbuf);
			free (d_rbuf);
		}
    }

	void
	synch_detect_impl::set_decim (int decim)
	{
		d_decim = decim;
		if (d_dbuf != NULL)
		{
			d_dbuf = (float *)realloc (d_dbuf, decim * sizeof(float));
		}
		if (d_rbuf != NULL)
		{
			d_rbuf = (float *)realloc (d_rbuf, decim * sizeof(float));
		}
		set_decimation (decim);
	}
	
	void
	synch_detect_impl::set_hval (float hval)
	{
		d_hval = hval;
	}
	
	void
	synch_detect_impl::set_lval (float lval)
	{
		d_lval = lval;
	}
	
    int
    synch_detect_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *d_in = (const float *) input_items[0];
        const float *r_in = (const float *)input_items[1];
        float *out = (float *) output_items[0];
        int nitems = 0;
        float midpoint = d_hval - d_lval;

		for (int i = 0; i < noutput_items*d_decim; i++)
		{
			if (r_in[i] < midpoint)
			{
				d_dbuf[d_dctr] = d_in[i];
				d_dctr++;
			}
			else
			{
				d_rbuf[d_rctr] = d_in[i];
				d_rctr++;
			}
			d_totctr++;
			if (d_totctr >= d_decim)
			{
				float davg, ravg;
				
				ravg = davg = 0;
				
				for (int k = 0; k < d_dctr; k++)
				{
					davg += d_dbuf[k];
				}
				if (d_dctr)
				{
					davg /= d_dctr;
				}
				for (int k = 0; k < d_rctr; k++)
				{
					ravg += d_rbuf[k];
				}
				if (d_rctr)
				{
					ravg /= d_rctr;
				}
				
				*out = davg - ravg;
				out++;
				d_dctr = d_rctr = 0;
				d_totctr = 0;
				nitems++;
			}
		}

        // Tell runtime system how many output items we produced.
        return nitems;
    }

  } /* namespace ra_blocks */
} /* namespace gr */

