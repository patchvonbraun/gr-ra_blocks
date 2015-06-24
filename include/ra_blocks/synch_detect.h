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


#ifndef INCLUDED_RA_BLOCKS_SYNCH_DETECT_H
#define INCLUDED_RA_BLOCKS_SYNCH_DETECT_H

#include <ra_blocks/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace ra_blocks {

    /*!
     * \brief <+description of block+>
     * \ingroup ra_blocks
     *
     */
    class RA_BLOCKS_API synch_detect : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<synch_detect> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ra_blocks::synch_detect.
       *
       * To avoid accidental use of raw pointers, ra_blocks::synch_detect's
       * constructor is in a private implementation
       * class. ra_blocks::synch_detect::make is the public interface for
       * creating new instances.
       */
      static sptr make(int decim, float hval, float lval);
      virtual void set_decim (int decim) = 0;
      virtual void set_hval (float hval) = 0;
      virtual void set_lval (float lval) = 0;
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_SYNCH_DETECT_H */

