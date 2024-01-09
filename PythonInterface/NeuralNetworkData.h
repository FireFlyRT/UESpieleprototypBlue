#pragma once
#include "include/Python.h"

typedef struct
{
	PyObject_HEAD;
	PyObject* Action;
	PyObject* MovementX;
	PyObject* MovementY;
	PyObject* RotationX;
	PyObject* RotationY;

} PyNN;

class NeuralNetworkData
{
public:
	int Action;
	float MovementX;
	float MovementY;
	float RotationX;
	float RotationY;

public:
	//static PyObject* PyInit_PyNeuralNetworkData();
	// Action
	static PyObject* PyNeuralNetworkData_getAction(PyNN* self, void* closure);
	static int PyNeuralNetworkData_setAction(PyNN* self, PyObject* value, void* closure);
	// MovementX
	static PyObject* PyNeuralNetworkData_getMovementX(PyNN* self, void* closure);
	static int PyNeuralNetworkData_setMovementX(PyNN* self, PyObject* value, void* closure);
	// MovementY
	static PyObject* PyNeuralNetworkData_getMovementY(PyNN* self, void* closure);
	static int PyNeuralNetworkData_setMovementY(PyNN* self, PyObject* value, void* closure);
	// RotationX
	static PyObject* PyNeuralNetworkData_getRotationX(PyNN* self, void* closure);
	static int PyNeuralNetworkData_setRotationX(PyNN* self, PyObject* value, void* closure);
	// RotationY
	static PyObject* PyNeuralNetworkData_getRotationY(PyNN* self, void* closure);
	static int PyNeuralNetworkData_setRotationY(PyNN* self, PyObject* value, void* closure);

};

