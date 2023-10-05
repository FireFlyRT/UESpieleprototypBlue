#include "PyEnvironment.h"

static PyTypeObject PyEnvironmentType = {
    //PyVarObject_HEAD_INIT(NULL, 0)
    .tp_name = "PyEnvironment",
    .tp_basicsize = sizeof(PyTypeObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "PyEnvironments",
    .tp_new = PyType_GenericNew,
};