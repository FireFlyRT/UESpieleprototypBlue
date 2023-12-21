#pragma once
#include "pylibs/Python.h"

typedef struct 
{
	PyObject_HEAD;

	//int* action_space = new int[1, 128, 128];
	//int observation_space = 8;

	//Env Observation Space =
	//	 SensorData
	//	 Audio
	//	 Inventory
	//	 BrainStorage
	//	 Stats

	PyObject* numargs;
	int nums;

} PyEnv;

class PyEnvironment
{
public:
	inline static int Cnumargs = 1;
	inline static PyTypeObject PyEnvObject =
	{
		.ob_base = PyVarObject_HEAD_INIT(NULL, 0)
		.tp_name = "pyModule.PyEnv",
		.tp_basicsize = sizeof(PyEnv),
		.tp_itemsize = 0,
		.tp_flags = Py_TPFLAGS_DEFAULT,
		.tp_doc = PyDoc_STR("Environment"),
		.tp_new = PyType_GenericNew,
	};
	inline static PyModuleDef PyModule =
	{
		.m_base = PyModuleDef_HEAD_INIT,
		.m_name = "pyModule",
		.m_doc = "Py Module for C++",
		.m_size = -1,
	};

public:
	
	static PyObject* PyInit_PyEnvironment();
	static PyObject* PyEnvironment_nums(PyEnv* self, PyObject* args);
	static PyObject* PyEnvironment_getNumargs(PyEnv* self, void* closure);
	static int PyEnvironment_setNumargs(PyEnv* self, PyObject* value, void* closure);
	static int GetNumargs();
	static void SetNumargs(PyEnv* self);
};
