import os
from cffi import FFI


ffi = FFI()
ffi.set_source("_wiredtiger", None)
with open(os.path.join(os.path.dirname(__file__), 'wiredtiger.h')) as f:
    ffi.cdef(f.read())

if __name__ == '__main__':
    ffi.compile()
