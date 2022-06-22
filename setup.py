from distutils.core import setup, Extension

module1 = Extension(
    'vectors_and_matrices',
    sources=['main.c', 'matrix.c', 'vector.c']
)

setup(
    name='vectors_and_matrices',
    version='1.0',
    description='',
    ext_modules=[module1]
)

# python setup.py install