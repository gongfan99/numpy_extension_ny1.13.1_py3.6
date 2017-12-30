#define NPY_NO_DEPRECATED_API  NPY_1_7_API_VERSION

#include "Python.h"
#include "numpy/arrayobject.h"

static PyObject* example (PyObject *self, PyObject *args, PyObject *keywds)
{
    PyObject *arg1 = NULL;
    int mul;
    static char *kwlist[] = {"input_arr", "multiplier", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "Oi", kwlist, &arg1, &mul))
        return NULL;

    PyObject *arr1 = PyArray_FROM_OTF(arg1, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY);
    if (arr1 == NULL){
        return NULL;
    }

    int ndim = PyArray_NDIM((PyArrayObject *)arr1);
    npy_intp *dims = PyArray_DIMS((PyArrayObject *)arr1);
    npy_intp size = PyArray_SIZE((PyArrayObject *)arr1);
    npy_double *dptr = (npy_double *)PyArray_DATA((PyArrayObject *)arr1);

    PyObject *arr2 = PyArray_ZEROS(ndim, dims, NPY_DOUBLE, NPY_CORDER);
    if (arr2 == NULL){
        Py_DECREF(arr1);
        return NULL;
    }
    npy_double *dptr2 = (npy_double *)PyArray_DATA((PyArrayObject *)arr2);

    while(size--) {
      *dptr2 = mul * (*dptr);
      dptr++;
      dptr2++;
    }

    Py_DECREF(arr1);

    return arr2;
}

static struct PyMethodDef MylibMethods[] = {
    {"example", (PyCFunction)example, METH_VARARGS | METH_KEYWORDS, "descript of example"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef mylibmodule = {
    PyModuleDef_HEAD_INIT,
    "mylib",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,       /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    MylibMethods
};

#ifdef __cplusplus
extern "C" {
#endif

PyMODINIT_FUNC
PyInit_mylib(void)
{
    import_array();
    return PyModule_Create(&mylibmodule);
}

#ifdef __cplusplus
}
#endif