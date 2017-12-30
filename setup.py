#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# from distutils.core import setup, Extension
# import numpy as np

# ext_modules = [ Extension('mylib', sources = ['mylib.c']) ]

# setup(
        # name = 'mylib',
        # version = '1.0',
        # include_dirs = [np.get_include()], #Add Include path of numpy
        # ext_modules = ext_modules
      # )
      
from setuptools import setup, Extension, find_packages
import numpy as np

ext_modules = [ Extension('mylib',
include_dirs = [np.get_include()],
libraries=[],
library_dirs = [],
sources = ['mylib.cc']
) ]

setup(
    name = 'mylib',
    version = '1.0',
    zip_safe = True,
    ext_modules = ext_modules
)