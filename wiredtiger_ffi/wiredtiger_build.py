import os
from cffi import FFI


ffi = FFI()
ffi.set_source(
    "wiredtiger_ffi._wiredtiger",
    "#include <wiredtiger.h>",
    libraries=['wiredtiger']
)

with open(os.path.join(os.path.dirname(__file__), 'wiredtiger.h')) as f:
    ffi.cdef(f.read())


if __name__ == '__main__':
    ffi.compile(verbose=True)
