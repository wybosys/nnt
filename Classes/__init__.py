'''nnt, python library'''

INFO = __doc__
VERSION = '1.0'
COPYRIGHT = """ wybosys """
LICENSE = """ BSD """

import os
import sys

python_dir = os.path.dirname(os.path.realpath(__file__)) + "/python"
if (python_dir not in sys.path):
    sys.path.append(python_dir)

from python import *
