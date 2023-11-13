#define PY_SSIZE_T_CLEAN

#include "pylibs/Python.h"

typedef struct
{
    PyObject_HEAD

    int* action_space;
    int observation_space;
} PyEnvironment;

static PyTypeObject PyEnvironmentType = {
    .ob_base = PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "externalTypes.PyEnvironment",
    .tp_basicsize = sizeof(PyEnvironment),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = PyDoc_STR("PyEnvironments"),
    .tp_new = PyType_GenericNew,
};

static PyModuleDef externalTypes = {
    .m_base = PyModuleDef_HEAD_INIT,
    .m_name = "externalTypes",
    .m_doc = "All external Types from C++",
    .m_size = -1,
};

PyMODINIT_FUNC
PyInit_externalTypes(void)
{
    PyObject* m;
    if (PyType_Ready(&PyEnvironmentType) < 0)
        return NULL;

    m = PyModule_Create(&externalTypes);
    if (m == NULL)
        return NULL;

    Py_INCREF(&PyEnvironmentType);
    if (PyModule_AddObject(m, "PyEnvironment", (PyObject*)&PyEnvironmentType) < 0)
    {
        Py_DECREF(&PyEnvironmentType);
        Py_DECREF(m);
        return NULL;
    }

    return m;
}