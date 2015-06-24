#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Vector Normalize
# Generated: Mon Jul  1 15:55:00 2013
##################################################

from gnuradio import blocks
from gnuradio import gr

class ra_vector_normalize(gr.hier_block2):

	def __init__(self, vecsize=1024):
		gr.hier_block2.__init__(
			self, "Vector Normalize",
			gr.io_signature(1, 1, gr.sizeof_float*1024),
			gr.io_signature(1, 1, gr.sizeof_float*1024),
		)

		##################################################
		# Parameters
		##################################################
		self.vecsize = vecsize

		##################################################
		# Blocks
		##################################################
		self.blocks_stream_to_vector_0 = blocks.stream_to_vector(gr.sizeof_float*1, vecsize)
		self.blocks_repeat_0 = blocks.repeat(gr.sizeof_float*1, vecsize)
		self.blocks_max_xx_0 = blocks.max_ff(vecsize)
		self.blocks_divide_xx_0 = blocks.divide_ff(vecsize)

		##################################################
		# Connections
		##################################################
		self.connect((self.blocks_divide_xx_0, 0), (self, 0))
		self.connect((self.blocks_stream_to_vector_0, 0), (self.blocks_divide_xx_0, 1))
		self.connect((self, 0), (self.blocks_max_xx_0, 0))
		self.connect((self.blocks_repeat_0, 0), (self.blocks_stream_to_vector_0, 0))
		self.connect((self.blocks_max_xx_0, 0), (self.blocks_repeat_0, 0))
		self.connect((self, 0), (self.blocks_divide_xx_0, 0))


	def get_vecsize(self):
		return self.vecsize

	def set_vecsize(self, vecsize):
		self.vecsize = vecsize


