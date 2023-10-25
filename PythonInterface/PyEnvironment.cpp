#include "PyEnvironment.h"

static PyTypeObject PyEnvironmentType = {
    //PyVarObject_HEAD_INIT(NULL, 0) //Nach Tutorial funktioniert das???
    .tp_name = "PyEnvironment",
    .tp_basicsize = sizeof(PyTypeObject),
    .tp_itemsize = 0,
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_doc = "PyEnvironments",
    .tp_new = PyType_GenericNew,
};

PyEnvironment::PyEnvironment()
{
    ob_base = *this;
    ob_type = &PyEnvironmentType;
}
