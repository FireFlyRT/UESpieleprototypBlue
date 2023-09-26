// Fill out your copyright notice in the Description page of Project Settings.
#define PY_SSIZE_T_CLEAN

#include "PythonInterface.h"

extern __declspec(dllimport) int Py_NoSiteFlag;

PythonInterface::PythonInterface()
{
}

PythonInterface::~PythonInterface()
{
}

void PythonInterface::Test()
{
    char* name = "SOMETHING";
    wchar_t* program = new wchar_t(*name);
    Py_SetProgramName(program);  /* optional but recommended */
    Py_NoSiteFlag = 1;
    Py_InitializeEx(0);
    PyRun_SimpleString("from time import time,ctime\n"
        "print('Today is', ctime(time()))\n");
    if (Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
}
