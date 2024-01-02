
from setuptools import Extension, setup

ext = Extension("pyModule", ["CPyModule.c", "CPyEnvironment.c", "CPyNeuralNetworkData.c", "CPyRewardData.c", "CPySensorData.c", "CPyStatData.c"])
ext.extra_compile_args = ["/std:c17"]
#ext.extra_compile_args = ["/std:c++20"]
setup(ext_modules=[ext])