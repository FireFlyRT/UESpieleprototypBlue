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

	PyObject* ActionSpace;
	int number;

} PyEnv;

class PyEnvironment
{
public:
	inline static int Cnumargs = 1;

public:
	static void PyEnv_dealloc(PyEnv* self);
	static PyObject* PyEnv_new(PyTypeObject* type, PyObject* args, PyObject* kwds);
	static int PyEnv_init(PyEnv* self, PyObject* args, PyObject* kwds);
	static PyObject* PyEnv_ActionSpace(PyEnv* self, PyObject* Py_UNUSED(ignored));

	// Getter/Setter for Members
	static PyObject* PyEnv_getActionSpace(PyEnv* self, void* closure);
	static int PyEnv_setActionSpace(PyEnv* self, PyObject* value, void* closure);
};
