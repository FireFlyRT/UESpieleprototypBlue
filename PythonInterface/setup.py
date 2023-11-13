from setuptools import Extension, setup
ext = Extension("externalTypes", ["PyEnvironment.cpp"])
setup(ext_modules=[ext])