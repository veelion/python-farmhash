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

#define PY_SSIZE_T_CLEAN
#include "Python.h"

static PyObject *py_farmhash_Hash32(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Hash32WithSeed(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Hash64(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Hash64WithSeed(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Hash128(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Hash128WithSeed(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Fingerprint32(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Fingerprint64(PyObject *self, PyObject *args);
static PyObject *py_farmhash_Fingerprint128(PyObject *self, PyObject *args);

PyMODINIT_FUNC initfarmhash(void);

#define HASH32_DOCSTRING      "Hash function for a bytes-like object.  Most useful in 32-bit binaries. \nexample: print farmhash.hash32('abc')\n2521517342"
#define HASH32WITHSEED_DOCSTRING      "Hash function for a bytes-like object.  For convenience, a 32-bit seed is also hashed into the result. \nexample: print farmhash.hash32withseed('abc', 1234)\n2521517342"
#define HASH64_DOCSTRING      "Hash function for a bytes-like object.  Returns an unsigned 64-bit integer. \nexample: print farmhash.hash64('abc')\n2640714258260161385L"
#define HASH64WITHSEED_DOCSTRING      "Hash function for a bytes-like object.  For convenience, a 64-bit seed is also hashed into the result. \nexample: print farmhash.hash64withseed('abc', 12345)\n13914286602242141520L"
#define HASH128_DOCSTRING      "Hash function for a bytes-like object.  Returns a tuple of two unsigned 64-bit integers: (low64, high64). \nexample: print farmhash.hash128('abc')\n(4143508125394299908L, 11566915719555882565L)"
#define HASH128WITHSEED_DOCSTRING      "Hash function for a bytes-like object. For convenience, two 32-bit seeds are also hashed into the result.\nexample: print farmhash.hash128withseed('abc', 1234, 0)\n(13364216625615136468L, 11320522948082609695L)"
#define FINGERPRINT32_DOCSTRING      "Fingerprint (i.e., good, portable, forever-fixed hash) function for a bytes-like object.  Most useful in 32-bit binaries. \nexample: print farmhash.fingerprint32('abc')\n2521517342"
#define FINGERPRINT64_DOCSTRING      "Fingerprint (i.e., good, portable, forever-fixed hash) function for a bytes-like object.  Returns an unsigned 64-bit integer. \nexample: print farmhash.fingerprint64('abc')\n2640714258260161385L"
#define FINGERPRINT128_DOCSTRING      "Fingerprint (i.e., good, portable, forever-fixed hash) function for a bytes-like object.  Returns a tuple of two unsigned 64-bit integers: (low64, high64). \nexample: print farmhash.fingerprint128('abc')\n(13364216625615136468L, 11320522948082609695L)"

#if defined(__SUNPRO_C) || defined(__hpux) || defined(_AIX)
#define inline
#endif

#ifdef __linux
#define inline __inline
#endif
