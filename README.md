python-farmhash
==========


Overview
========
This package provides bindings for the [Google's FarmHash](http://code.google.com/p/farmhash/).  

Code specific to this project is covered by [The MIT License](http://opensource.org/licenses/MIT)

Forked on 2015.04.06 to add bindings for fingerprint functions.  Pull request submitted.
Install
=======
Currently, clone the repo and:

pip:
> $ sudo pip install pyfarmhash  

Linux:
> $ cd python-farmhash  
> $ sudo python setup.py Install  

Windows: 
(Sheer hackery.  I'm sure there's a way to do this with the new VS but this is working and 
I don't have hours to work on it.  Feel free to submit a pull request)

> Install Microsoft Visual C++ Compiler for Python 2.7
http://www.microsoft.com/en-us/download/details.aspx?id=44266
> Install msinttypes https://code.google.com/p/msinttypes/
> Copy stdint.h to the src directory, and modify the farmhash.cc line 47 reference to use double quotes instead of angle brackets
> Add "if defined(_MSC_VER) ||" to line 76 of farmhash.cc
> $ cd python-farmhash
> $ sudo python setup.py install

Usage
=====
The library is pretty simple to use:

> import farmhash  
> print farmhash.hash64('abc')  
> 2640714258260161385  

For more details, use ipython:
> In [1]: import farmhash 
> 
> In [2]: farmhash.hash64withseed?  
> Type:       builtin_function_or_method  
> String Form:<built-in function hash64withseed>  
> Docstring:  
> Hash function for a string.  For convenience, a 64-bit seed is also hashed into the result.  
> example: print farmhash.hash64withseed('abc', 12345)  
> 13914286602242141520L  



