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

} PyStat;

class StatData
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
	// Inventory

public:
	//static PyObject* PyInit_PyStatData();
	// ClassCategory
	static PyObject* PyStatData_getClassCategory(PyStat* self, void* closure);
	static int PyStatData_setClassCategory(PyStat* self, PyObject* value, void* closure);
	// TribeID
	static PyObject* PyStatData_getTribeID(PyStat* self, void* closure);
	static int PyStatData_setTribeID(PyStat* self, PyObject* value, void* closure);
	// LivePoints
	static PyObject* PyStatData_getLivePoints(PyStat* self, void* closure);
	static int PyStatData_setLivePoints(PyStat* self, PyObject* value, void* closure);
	// Stamina
	static PyObject* PyStatData_getStamina(PyStat* self, void* closure);
	static int PyStatData_setStamina(PyStat* self, PyObject* value, void* closure);
	// Strength
	static PyObject* PyStatData_getStrength(PyStat* self, void* closure);
	static int PyStatData_setStrength(PyStat* self, PyObject* value, void* closure);
	// Age
	static PyObject* PyStatData_getAge(PyStat* self, void* closure);
	static int PyStatData_setAge(PyStat* self, PyObject* value, void* closure);
	// Height
	static PyObject* PyStatData_getHeight(PyStat* self, void* closure);
	static int PyStatData_setHeight(PyStat* self, PyObject* value, void* closure);
	// Hunger
	static PyObject* PyStatData_getHunger(PyStat* self, void* closure);
	static int PyStatData_setHunger(PyStat* self, PyObject* value, void* closure);
	// Thurst
	static PyObject* PyStatData_getThurst(PyStat* self, void* closure);
	static int PyStatData_setThurst(PyStat* self, PyObject* value, void* closure);
	// PositionX
	static PyObject* PyStatData_getPositionX(PyStat* self, void* closure);
	static int PyStatData_setPositionX(PyStat* self, PyObject* value, void* closure);
	// PositionY
	static PyObject* PyStatData_getPositionY(PyStat* self, void* closure);
	static int PyStatData_setPositionY(PyStat* self, PyObject* value, void* closure);
	// PositionZ
	static PyObject* PyStatData_getPositionZ(PyStat* self, void* closure);
	static int PyStatData_setPositionZ(PyStat* self, PyObject* value, void* closure);
};

