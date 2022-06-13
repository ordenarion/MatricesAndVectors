from distutils.core import setup, Extension

module1 = Extension(
    'vectors_and_matrices',  # module name in interpreter
    sources=[]
)

setup(
    name='data_table',
    version='1.2',
    description='',
    ext_modules=[module1]
)

# python setup.py install