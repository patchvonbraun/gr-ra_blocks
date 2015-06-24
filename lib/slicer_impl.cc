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
#include <iostream>
#include <algorithm>    // std::sort
#include <vector>       // std::vector
#include "slicer_impl.h"

/*
 * We implement an algorithm suggested to me by Ken Tapping of the
 *   Dominion Radio Astrophysical Observatory, Penticton, BC, Canada.
 * 
 * When you have a stream of detector values, and the input is being switched
 *   between a the "real" signal, and a reference, and you don't have access to
 *   the switching data (that is, the values you receive aren't tagged in any way
 *   indicating whether they're "real" or "reference"), then you can use a data-slicer
 *   like technique for calculating the delta.
 * 
 * This only works for sample sets that have populations that are "distinct" between
 *   "real" and "reference".
 *
 * 
 * Marcus Leech  mleech@ripnet.com
 */
namespace gr {
  namespace ra_blocks {

    slicer::sptr
    slicer::make(int decim, float thresh, int ratio)
    {
      return gnuradio::get_initial_sptr
        (new slicer_impl(decim, thresh, ratio));
    }

    /*
     * The private constructor
     */
    slicer_impl::slicer_impl(int decim, float thresh, int ratio)
      : gr::sync_decimator ("slicer",
		      gr::io_signature::make(1, 1, sizeof(float)),
		      gr::io_signature::make(1, 1, sizeof(float)), decim)
    {
		d_decim = decim;
		set_decimation (decim);
		d_ctr = 0;
		d_slbuf = (float *)malloc(decim * sizeof(float));
		d_thresh = thresh;
		d_ratio = ratio;
	}

    /*
     * Our virtual destructor.
     */
    slicer_impl::~slicer_impl()
    {
		if (d_slbuf != NULL)
		{
			free (d_slbuf);
		}
    }

	void
	slicer_impl::set_thresh (float thresh)
	{
		d_thresh = thresh;
	}
	
	void
	slicer_impl::set_ratio (int ratio)
	{
		d_ratio = ratio;
	}
	
    int
    slicer_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        float *out = (float *) output_items[0];
        int i, actual;
        actual = 0;
        int x;
        
        /*
         * Record values into d_slbuf
         */
        actual = 0;
        for (i = 0; i < noutput_items*d_decim; i++)
        {
			d_slbuf[d_ctr] = in[i];
			d_ctr++;
			
			/*
			 * When it's time, sort the d_slbuf, and determine inflection point
			 */
			if (d_ctr >= d_decim)
			{
				float low_sum = 0.0f;
				float high_sum = 0.0f;
				int low_count = 0;
				int high_count = 0;
				int q;
				float inflection;
				int k;
				float redbuf[d_decim];
				std::vector<float> vec (d_slbuf, d_slbuf+(d_decim-1));
				d_ctr = 0;
				int titems = 0;
				
				/*
				 * I'd rather just call qsort(), but I can't figure out how to make C++
				 *   happy about that, so I'm calling the std::sort syntax-heavy piece
				 *   of C++ masturbatory nonsense instead, and then unloading the resulting
				 *   vector "object" back into d_slbuf, so I can farking deal with it like
				 *   it's C here.
				 * 
				 * Stay off my godamn lawn.
				 * 
				 */
				std::sort(vec.begin(), vec.end());
				q = 0;
				for (std::vector<float>::iterator it=vec.begin(); it!=vec.end(); ++it)
				{
					d_slbuf[q++] = *it;
				}
				
				/*
				 * Inflection point, because d_slbuf is sorted, will be in the middle
				 *   of the buffer.
				 */
				inflection = d_slbuf[d_decim/2];
				
				/*
				 * So now, we go over the (reduced-by-10%) buffer
				 * And sort into respective "houses".
				 */
				for (k = d_decim/20; k < d_decim-(d_decim/20); k++)
				{
					if (std::isnan(d_slbuf[k]))
					{
						std::cout << "---NAN---- at " << k << "\n";
					}
					/*
					 * Lower or equal to inflection point
					 */
					if (d_slbuf[k] <= inflection)
					{
						low_sum += d_slbuf[k];
						low_count++;
					}
					
					/*
					 * Larger than inflection point
					 */
					else
					{
						high_sum += d_slbuf[k];
						high_count++;
					}
				}
				if (low_count > 1 && high_count > 1)
				{
					/*
					 * If there's less than a d_thresh ratio between high/low, we probably can't
					 *   really make this determination.
					 */
					if (d_ratio == 0 &&
					   ((high_sum/low_sum) < d_thresh))
					{
						out[actual] = (high_sum/(float)high_count);
						out[actual] += (low_sum/(float)low_count);
						out[actual] /= 2.0f;
					}
					/*
					 * Else there's enough difference to make a determination, and return the
					 *   delta between the average of the two "houses".
					 */
					else
					{
						if (d_ratio == 0)
						{
							out[actual] = (high_sum/(float)high_count)-(low_sum/(float)low_count);
						}
						else
						{
							out[actual] = (high_sum/(float)high_count)/(low_sum/(float)low_count);
						}
					}
				}
				else
				{
					out[actual] = 0.0;
					for (int s = 0; s < d_decim; s++)
					{
						out[actual] += d_slbuf[s];
					}
					out[actual] /= d_decim;
				}
				actual++;
			}		
		}
		
        // Tell runtime system how many output items we produced.
        return actual;
    }

  } /* namespace tapping_slicer */
} /* namespace gr *//* -*- c++ -*- */
