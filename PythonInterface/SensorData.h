#pragma once
#include "include/Python.h"

typedef struct
{
	PyObject_HEAD;
	PyObject* ClassCategory;
	PyObject* TribeID;
	PyObject* LivePoints;
	PyObject* Stamina;
	PyObject* Strength;
	PyObject* Age;
	PyObject* Height;
	PyObject* Hunger;
	PyObject* Thurst;
	PyObject* PositionX;
	PyObject* PositionY;
	PyObject* PositionZ;
	PyObject* Distance;

} PySensor;

class SensorData
{
public:
	int ClassCategory;
	int TribeID;
	int LivePoints;
	int Stamina;
	int Strength;
	int Age;
	int Height;
	int Hunger;
	int Thurst;
	int PositionX;
	int PositionY;
	int PositionZ;
	int Distance;
	// Inventory Array

public:
	//static PyObject* PyInit_PySensorData();
	// ClassCategory
	static PyObject* PySensorData_getClassCategory(PySensor* self, void* closure);
	static int PySensorData_setClassCategory(PySensor* self, PyObject* value, void* closure);
	// TribeID
	static PyObject* PySensorData_getTribeID(PySensor* self, void* closure);
	static int PySensorData_setTribeID(PySensor* self, PyObject* value, void* closure);
	// LivePoints
	static PyObject* PySensorData_getLivePoints(PySensor* self, void* closure);
	static int PySensorData_setLivePoints(PySensor* self, PyObject* value, void* closure);
	// Stamina
	static PyObject* PySensorData_getStamina(PySensor* self, void* closure);
	static int PySensorData_setStamina(PySensor* self, PyObject* value, void* closure);
	// Strength
	static PyObject* PySensorData_getStrength(PySensor* self, void* closure);
	static int PySensorData_setStrength(PySensor* self, PyObject* value, void* closure);
	// Age
	static PyObject* PySensorData_getAge(PySensor* self, void* closure);
	static int PySensorData_setAge(PySensor* self, PyObject* value, void* closure);
	// Height
	static PyObject* PySensorData_getHeight(PySensor* self, void* closure);
	static int PySensorData_setHeight(PySensor* self, PyObject* value, void* closure);
	// Hunger
	static PyObject* PySensorData_getHunger(PySensor* self, void* closure);
	static int PySensorData_setHunger(PySensor* self, PyObject* value, void* closure);
	// Thurst
	static PyObject* PySensorData_getThurst(PySensor* self, void* closure);
	static int PySensorData_setThurst(PySensor* self, PyObject* value, void* closure);
	// PositionX
	static PyObject* PySensorData_getPositionX(PySensor* self, void* closure);
	static int PySensorData_setPositionX(PySensor* self, PyObject* value, void* closure);
	// PositionY
	static PyObject* PySensorData_getPositionY(PySensor* self, void* closure);
	static int PySensorData_setPositionY(PySensor* self, PyObject* value, void* closure);
	// PositionZ
	static PyObject* PySensorData_getPositionZ(PySensor* self, void* closure);
	static int PySensorData_setPositionZ(PySensor* self, PyObject* value, void* closure);
	// Distance
	static PyObject* PySensorData_getDistance(PySensor* self, void* closure);
	static int PySensorData_setDistance(PySensor* self, PyObject* value, void* closure);

};

