#!/usr/bin/env python
import os
from setuptools import setup, find_packages


def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()


setup(
    name='wiredtiger-ffi',
    version='3.1.0.0',
    author='Amirouche Boubekki',
    author_email='amirouche@hypermove.net',
    url='https://github.com/amirouche/python-wiredtiger-ffi',
    description='cffi bindings for wiredtiger',
    long_description=read('README.rst'),
    packages=find_packages(),
    package_data={'wiredtiger_ffi': ['wiredtiger.h']},
    zip_safe=False,
    license='GPLv2 or GPLv3',
    setup_requires=["cffi>=1.0.0"],
    cffi_modules=["wiredtiger_ffi/wiredtiger_build.py:ffi"],
    install_requires=["cffi>=1.0.0"],
    classifiers=[
        'Intended Audience :: Developers',
        'Topic :: Software Development',
        'Programming Language :: Python :: 3',
    ],
)
