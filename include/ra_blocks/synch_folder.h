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


#ifndef INCLUDED_RA_BLOCKS_SYNCH_FOLDER_H
#define INCLUDED_RA_BLOCKS_SYNCH_FOLDER_H

#include <ra_blocks/api.h>
#include <gnuradio/sync_decimator.h>

namespace gr {
  namespace ra_blocks {

    /*!
     * \brief <+description of block+>
     * \ingroup ra_blocks
     *
     */
    class RA_BLOCKS_API synch_folder : virtual public gr::sync_decimator
    {
     public:
      typedef boost::shared_ptr<synch_folder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ra_blocks::synch_folder.
       *
       * To avoid accidental use of raw pointers, ra_blocks::synch_folder's
       * constructor is in a private implementation
       * class. ra_blocks::synch_folder::make is the public interface for
       * creating new instances.
       */
      static sptr make(int outvecsize, int folding);
      virtual void set_folding (int folding) = 0;
      
    };

  } // namespace ra_blocks
} // namespace gr

#endif /* INCLUDED_RA_BLOCKS_SYNCH_FOLDER_H */

