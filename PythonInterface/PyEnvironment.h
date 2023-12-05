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
private:
	inline static int Cnumargs = 1;

public:
	static PyObject* PyInit_PyEnvironment();
	static PyObject* PyEnvironment_nums(PyEnv* self, PyObject* args);
	static PyObject* PyEnvironment_getNumargs(PyEnv* self, void* closure);
	static int PyEnvironment_setNumargs(PyEnv* self, PyObject* value, void* closure);
	static int GetNumargs();
	static void SetNumargs(PyEnv* self);
};
