#include "PyEnvironment.h"

PyEnvironment::PyEnvironment()
{
	ob_base = *(PyObject*)this;
	tp_name = "PyEnvironment";
}
