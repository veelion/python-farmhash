python-farmhash
==========


Overview
========
This package provides bindings for the [Google's FarmHash](http://code.google.com/p/farmhash/).  

Code specific to this project is covered by [The MIT License](http://opensource.org/licenses/MIT)

Install
=======
Currently, clone the repo and:
> $ cd python-farmhash  
> $ sudo python setup.py Install  


The package was hosted on [PyPI](http://pypi.python.org/pypi/pyfarmhash)

> $ pip install pyfarmhash  
> $ easy_install pyfarmhash  

Usage
=====
The library is pretty simple to use:

> import pyfarmhash as farmhash
> print farmhash.hash64('abc')  
> 2640714258260161385  

For more details, use ipython:
> In [1]: import pyfarmhash as farmhash 
> 
> In [2]: farmhash.hash64withseed?  
> Type:       builtin_function_or_method  
> String Form:<built-in function hash64withseed>  
> Docstring:  
> Hash function for a string.  For convenience, a 64-bit seed is also hashed into the result.  
> example: print farmhash.hash64withseed('abc', 12345)  
> 13914286602242141520L  



