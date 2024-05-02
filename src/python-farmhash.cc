/*
 * Copyright (c) 2014, Veelion Chong

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

// PY_SSIZE_T_CLEAN macro must be defined for '#' formats.
#define PY_SSIZE_T_CLEAN

#include <iostream>
#include <Python.h>
#include "farmhash.h"
#include "python-farmhash.h"

using namespace NAMESPACE_FOR_HASH_FUNCTIONS;

static PyObject *
py_farmhash_Hash32(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &s, &len))
        return NULL;

    uint32_t h = Hash32(s, len);
    result = Py_BuildValue("I", h);

    return result;
}

static PyObject *
py_farmhash_Hash32WithSeed(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;
    uint32_t seed;

    if (!PyArg_ParseTuple(args, "s#I", &s, &len, &seed))
        return NULL;

    uint32_t h = Hash32WithSeed(s, len, seed);
    result = Py_BuildValue("I", h);

    return result;
}

static PyObject *
py_farmhash_Hash64(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &s, &len))
        return NULL;

    uint64_t h = Hash64(s, len);
# if __WORDSIZE == 64
    const char* int_param = "k";
# else
    const char* int_param = "K";
#endif
    result = Py_BuildValue(int_param, h);

    return result;
}

static PyObject *
py_farmhash_Hash64WithSeed(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;
    uint64_t seed;

    if (!PyArg_ParseTuple(args, "s#K", &s, &len, &seed))
        return NULL;

    uint64_t h = Hash64WithSeed(s, len, seed);
# if __WORDSIZE == 64
    const char* int_param = "k";
# else
    const char* int_param = "K";
#endif
    result = Py_BuildValue(int_param, h);

    return result;
}

static PyObject *
py_farmhash_Hash128(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &s, &len))
        return NULL;

    uint128_t h = Hash128(s, len);
    uint64_t low64 = Uint128Low64(h);
    uint64_t high64 = Uint128High64(h);
    result = Py_BuildValue("(KK)", low64, high64);

    return result;
}

static PyObject *
py_farmhash_Hash128WithSeed(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;
    uint64_t seedlow64;
    uint64_t seedhigh64;

    if (!PyArg_ParseTuple(args, "s#KK", &s, &len, &seedlow64, &seedhigh64))
        return NULL;

    //std::cout << "seed low64:" << seedlow64 << std::endl;
    //std::cout << "seed high64:" << seedhigh64 << std::endl;
    uint128_t seed = Uint128(seedlow64, seedhigh64);
    uint128_t h = Hash128WithSeed(s, len, seed);
    uint64_t low64 = Uint128Low64(h);
    uint64_t high64 = Uint128High64(h);
    result = Py_BuildValue("(KK)", low64, high64);

    return result;
}

static PyObject *
py_farmhash_Fingerprint32(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &s, &len))
        return NULL;

    uint32_t h = Fingerprint32(s, len);
    result = Py_BuildValue("I", h);

    return result;
}

static PyObject *
py_farmhash_Fingerprint64(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &s, &len))
        return NULL;

    uint64_t h = Fingerprint64(s, len);
# if __WORDSIZE == 64
    const char* int_param = "k";
# else
    const char* int_param = "K";
#endif
    result = Py_BuildValue(int_param, h);

    return result;
}

static PyObject *
py_farmhash_Fingerprint128(PyObject *self, PyObject *args)
{
    PyObject *result;
    const char *s;
    Py_ssize_t len;

    if (!PyArg_ParseTuple(args, "s#", &s, &len))
        return NULL;

    uint128_t h = Fingerprint128(s, len);
    uint64_t low64 = Uint128Low64(h);
    uint64_t high64 = Uint128High64(h);
    result = Py_BuildValue("(KK)", low64, high64);

    return result;
}

static PyMethodDef FarmHashMethods[] = {
    {"hash32",  py_farmhash_Hash32, METH_VARARGS, HASH32_DOCSTRING},
    {"hash32withseed",  py_farmhash_Hash32WithSeed, METH_VARARGS, HASH32WITHSEED_DOCSTRING},
    {"hash64",  py_farmhash_Hash64, METH_VARARGS, HASH64_DOCSTRING},
    {"hash64withseed",  py_farmhash_Hash64WithSeed, METH_VARARGS, HASH64WITHSEED_DOCSTRING},
    {"hash128",  py_farmhash_Hash128, METH_VARARGS, HASH128_DOCSTRING},
    {"hash128withseed",  py_farmhash_Hash128WithSeed, METH_VARARGS, HASH128WITHSEED_DOCSTRING},
    {"fingerprint32",  py_farmhash_Fingerprint32, METH_VARARGS, FINGERPRINT32_DOCSTRING},
    {"fingerprint64",  py_farmhash_Fingerprint64, METH_VARARGS, FINGERPRINT64_DOCSTRING},
    {"fingerprint128",  py_farmhash_Fingerprint128, METH_VARARGS, FINGERPRINT128_DOCSTRING},
    {NULL, NULL, 0, NULL}
};

struct module_state {
    PyObject *error;
};

#if PY_MAJOR_VERSION >= 3
#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

#if PY_MAJOR_VERSION >= 3

static int myextension_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int myextension_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}


static struct PyModuleDef moduledef = {
        PyModuleDef_HEAD_INIT,
        "farmhash",
        NULL,
        sizeof(struct module_state),
        FarmHashMethods,
        NULL,
        myextension_traverse,
        myextension_clear,
        NULL
};

#define INITERROR return NULL

extern "C" PyObject *
PyInit_farmhash(void)

#else
#define INITERROR return

void
initfarmhash(void)
#endif
{
#if PY_MAJOR_VERSION >= 3
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("farmhash", FarmHashMethods);
#endif
    struct module_state *st = NULL;

    if (module == NULL)
        INITERROR;
    st = GETSTATE(module);

    st->error = PyErr_NewException("farmhash.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

#if PY_MAJOR_VERSION >= 3
    return module;
#endif
}
