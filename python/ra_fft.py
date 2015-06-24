#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Ra Fft
# Generated: Fri Jun 14 12:35:11 2013
##################################################

from gnuradio import blocks
from gnuradio import fft
from gnuradio import filter
from gnuradio import gr

class ra_fft(gr.hier_block2):

	def __init__(self, fft_size=2048, decim=100):
		gr.hier_block2.__init__(
			self, "RA:FFT",
			gr.io_signature(1, 1, gr.sizeof_gr_complex*1),
			gr.io_signature(1, 1, gr.sizeof_float*fft_size),
		)

		##################################################
		# Parameters
		##################################################
		self.fft_size = fft_size
		self.decim = decim

		##################################################
		# Blocks
		##################################################
		self.single_pole_iir_filter_xx_0 = filter.single_pole_iir_filter_ff(1.0/decim, fft_size)
		self.fft_vxx_0 = fft.fft_vcc(fft_size, True, (window.blackmanharris(1024)), True, 1)
		self.blocks_stream_to_vector_0 = blocks.stream_to_vector(gr.sizeof_gr_complex*1, fft_size)
		self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff(([1.0/fft_size]*fft_size))
		self.blocks_keep_one_in_n_0 = blocks.keep_one_in_n(gr.sizeof_float*fft_size, decim)
		self.blocks_complex_to_mag_squared_0 = blocks.complex_to_mag_squared(fft_size)

		##################################################
		# Connections
		##################################################
		self.connect((self.blocks_multiply_const_vxx_0, 0), (self.single_pole_iir_filter_xx_0, 0))
		self.connect((self.blocks_complex_to_mag_squared_0, 0), (self.blocks_multiply_const_vxx_0, 0))
		self.connect((self.single_pole_iir_filter_xx_0, 0), (self.blocks_keep_one_in_n_0, 0))
		self.connect((self.fft_vxx_0, 0), (self.blocks_complex_to_mag_squared_0, 0))
		self.connect((self.blocks_stream_to_vector_0, 0), (self.fft_vxx_0, 0))
		self.connect((self, 0), (self.blocks_stream_to_vector_0, 0))
		self.connect((self.blocks_keep_one_in_n_0, 0), (self, 0))


	def get_fft_size(self):
		return self.fft_size

	def set_fft_size(self, fft_size):
		self.fft_size = fft_size
		self.blocks_multiply_const_vxx_0.set_k(([1.0/self.fft_size]*self.fft_size))

	def get_decim(self):
		return self.decim

	def set_decim(self, decim):
		self.decim = decim
		self.single_pole_iir_filter_xx_0.set_taps(1.0/self.decim)
		self.blocks_keep_one_in_n_0.set_n(self.decim)


