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


#ifndef INCLUDED_RA_BLOCKS_VECTOR_POWER_H
#define INCLUDED_RA_BLOCKS_VECTOR_POWER_H

#include <ra_blocks/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ra_blocks {

    /*!
     * \brief <+description of block+>
     * \ingroup ra_blocks
     *
     */
    class RA_BLOCKS_API vector_power : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<vector_power> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ra_blocks::vector_power.
       *
       * To avoid accidental use of raw pointers, ra_blocks::vector_power's
       * constructor is in a private implementation
       * class. ra_blocks::vector_power::make is the public interface for
       * creating new instances.
       */
      static sptr make(int vecsize, int nstream);
      
      virtual void set_positions (const std::vector <int> &begins, const std::vector <int> &ends) = 0;
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_VECTOR_POWER_H */

