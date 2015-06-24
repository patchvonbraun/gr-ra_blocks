#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Synch Folder2
# Generated: Tue Jun 18 19:43:17 2013
##################################################

from gnuradio import blocks
from gnuradio import filter
from gnuradio import gr

class ra_synch_folder2(gr.hier_block2):

	def __init__(self, samp_rate=1000, vecsize=500, folding=5, pulse_rate=0.7477):
		gr.hier_block2.__init__(
			self, "Synch Folder2",
			gr.io_signature(1, 1, gr.sizeof_float*1),
			gr.io_signature(1, 1, gr.sizeof_float*vecsize),
		)

		##################################################
		# Parameters
		##################################################
		self.samp_rate = samp_rate
		self.vecsize = vecsize
		self.folding = folding
		self.pulse_rate = pulse_rate

		##################################################
		# Blocks
		##################################################
		self.single_pole_iir_filter_xx_0 = filter.single_pole_iir_filter_ff(1.0/folding, vecsize)
		self.fractional_resampler_xx_0 = filter.fractional_resampler_ff(0, float(samp_rate)/(float(pulse_rate)*float(vecsize)))
		self.blocks_stream_to_vector_0 = blocks.stream_to_vector(gr.sizeof_float*1, vecsize)

		##################################################
		# Connections
		##################################################
		self.connect((self.blocks_stream_to_vector_0, 0), (self.single_pole_iir_filter_xx_0, 0))
		self.connect((self.fractional_resampler_xx_0, 0), (self.blocks_stream_to_vector_0, 0))
		self.connect((self, 0), (self.fractional_resampler_xx_0, 0))
		self.connect((self.single_pole_iir_filter_xx_0, 0), (self, 0))


	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.fractional_resampler_xx_0.set_resamp_ratio(float(self.samp_rate)/(float(self.pulse_rate)*float(self.vecsize)))

	def get_vecsize(self):
		return self.vecsize

	def set_vecsize(self, vecsize):
		self.vecsize = vecsize
		self.fractional_resampler_xx_0.set_resamp_ratio(float(self.samp_rate)/(float(self.pulse_rate)*float(self.vecsize)))

	def get_folding(self):
		return self.folding

	def set_folding(self, folding):
		self.folding = folding
		self.single_pole_iir_filter_xx_0.set_taps(1.0/self.folding)

	def get_pulse_rate(self):
		return self.pulse_rate

	def set_pulse_rate(self, pulse_rate):
		self.pulse_rate = pulse_rate
		self.fractional_resampler_xx_0.set_resamp_ratio(float(self.samp_rate)/(float(self.pulse_rate)*float(self.vecsize)))


