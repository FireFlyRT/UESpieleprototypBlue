from setuptools import Extension, setup
ext = Extension("externalTypes", ["PyEnvironment.cpp"])
ext.extra_compile_args = ["/std:c++20"]
setup(ext_modules=[ext])