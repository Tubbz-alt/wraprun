# The MIT License (MIT)
#
# Copyright (c) 2016 M. Belhorn
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

"""
Wraprun - A task bundling wrapper for ALPS/Aprun.

Wraprun is a wrapper utility for ALPS/Aprun that bundles tasks into single
aprun calls. It permits launching multiple independent instances of an
application on singular nodes or even multiple unique applications on several
nodes in a single aprun call. Bundling tasks reduces aprun overhead and allows
more tasks to be started per batch job. Wraprun works with both MPI-aware and
serial executables.
"""

import sys
from .api import Wraprun


__all__ = ["Wraprun"]


def _cli_main():
    """Main commandline interface entrypoint."""
    bundle = Wraprun(argv=sys.argv)
    bundle.launch()

if __name__ == '__main__':
    _cli_main()
