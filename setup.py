#!/usr/bin/env python


from setuptools import setup, find_packages, Extension

VERSION = (0, 1, 5)

setup(
    name='pyfarmhash',
    version=".".join([str(x) for x in VERSION]),
    description="Google FarmHash Bindings for Python",
    long_description=open('README.md', 'r').read(),
    data_files=[
        'README.md',
    ],
    author='Veelion Chong',
    author_email='veelion@gmail.com',
    url='https://github.com/veelion/python-farmhash',
    packages=find_packages('src'),
    package_dir={'': 'src'},
    ext_modules=[
        Extension('farmhash', [
            'src/farmhash.cc',
            'src/python-farmhash.cc'
        ], extra_compile_args=["-O4"]
        )
    ],
    classifiers=[
        'Development Status :: 5 - Production/Stable',
        'License :: OSI Approved :: MIT License',
        'Intended Audience :: Developers',
        'Programming Language :: C',
        'Programming Language :: Python',
        'Programming Language :: Python :: 2.6',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.3',
    ],
)
