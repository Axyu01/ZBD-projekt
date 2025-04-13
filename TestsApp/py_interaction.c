#include <Python.h>
#include <stdio.h>
#include <stdlib.h>
#include "py_interaction.h"  // Include the header file

PyObject** generate_multiple_by_types(const char* inputs[], int count, int num_arrays, int* out_size) {
    Py_Initialize();
    PyRun_SimpleString("import sys; sys.path.append('.')");

    PyObject *pModule = PyImport_ImportModule("c_interaction");
    if (!pModule) {
        PyErr_Print();
        fprintf(stderr, "Failed to import myscript.py\n");
        Py_Finalize();
        return NULL;
    }

    PyObject *pFunc = PyObject_GetAttrString(pModule, "generate_multiple_by_types");
    if (!pFunc || !PyCallable_Check(pFunc)) {
        PyErr_Print();
        fprintf(stderr, "Function generate_multiple_by_types not found or not callable\n");
        Py_DECREF(pModule);
        Py_Finalize();
        return NULL;
    }

    // Prepare input list
    PyObject *pyList = PyList_New(count);
    for (int i = 0; i < count; ++i) {
        PyObject *pyStr = PyUnicode_FromString(inputs[i]);
        PyList_SetItem(pyList, i, pyStr);
    }

    PyObject *pArgs = PyTuple_Pack(2, pyList, PyLong_FromLong(num_arrays));
    PyObject *pReturn = PyObject_CallObject(pFunc, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(pFunc);
    Py_DECREF(pModule);

    if (!pReturn || !PyList_Check(pReturn)) {
        PyErr_Print();
        fprintf(stderr, "Returned object is not a list\n");
        Py_Finalize();
        return NULL;
    }

    *out_size = (int)PyList_Size(pReturn);
    PyObject** result_array = malloc(sizeof(PyObject*) * (*out_size));

    for (int i = 0; i < *out_size; ++i) {
        result_array[i] = PyList_GetItem(pReturn, i);
        Py_INCREF(result_array[i]);
    }

    Py_DECREF(pReturn);
    return result_array;
}
