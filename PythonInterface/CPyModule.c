#define PY_SSIZE_T_CLEAN

#include "pylibs/Python.h"
#include "CPyEnvironment.c"
#include "CPyNeuralNetworkData.c"
#include "CPyRewardData.c"
#include "CPySensorData.c"
#include "CPyStatData.c"

static PyModuleDef PyModule =
{
	.m_base = PyModuleDef_HEAD_INIT,
	.m_name = "pyModule",
	.m_doc = "Py Module for C++",
	.m_size = -1,
};

PyMODINIT_FUNC PyInit_pyModule()
{
	PyObject* obj;
	if (PyType_Ready(&PyEnvObject) < 0)
		return NULL;
	if (PyType_Ready(&PyNNDataObject) < 0)
		return NULL; 
	if (PyType_Ready(&PyRewObject) < 0)
		return NULL;
	if (PyType_Ready(&PySensDataObject) < 0)
		return NULL;
	if (PyType_Ready(&PyStatDataObject) < 0)
		return NULL;

	obj = PyModule_Create(&PyModule);
	if (obj == NULL)
		return NULL;

	Py_INCREF(&PyEnvObject);
	if (PyModule_AddObject(obj, "CPyEnv", (PyObject*)&PyEnvObject) < 0)
	{
		Py_DECREF(&PyEnvObject);
		Py_DECREF(obj);
		return NULL;
	}
	if (PyModule_AddObject(obj, "CPyNNData", (PyObject*)&PyNNDataObject) < 0)
	{
		Py_DECREF(&PyNNDataObject);
		Py_DECREF(obj);
		return NULL;
	}
	if (PyModule_AddObject(obj, "CPyRew", (PyObject*)&PyRewObject) < 0)
	{
		Py_DECREF(&PyRewObject);
		Py_DECREF(obj);
		return NULL;
	}
	if (PyModule_AddObject(obj, "CPySensData", (PyObject*)&PySensDataObject) < 0)
	{
		Py_DECREF(&PySensDataObject);
		Py_DECREF(obj);
		return NULL;
	}
	if (PyModule_AddObject(obj, "CPyStatData", (PyObject*)&PyStatDataObject) < 0)
	{
		Py_DECREF(&PyStatDataObject);
		Py_DECREF(obj);
		return NULL;
	}

	return obj;
}