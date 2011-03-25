# Script to generate .exe file for gme.py
# /c/Program\ Files/Python26/python UdmCliGen-setup.py py2exe && mv dist/UdmCliGen.exe UdmCliGen.exe

from distutils.core import setup
import py2exe
import time
import sys
import os

import UdmCliGen # for Cheetah in sys.path

templates = ['Interface', 'Implementation', 'Initialize']
if __name__ == '__main__':
    from Cheetah.CheetahWrapper import CheetahWrapper
    for template in templates:
        CheetahWrapper().main([sys.argv[0], 'compile', template + '.tmpl'])

class Target:
    def __init__(self, **kw):
        self.__dict__.update(kw)
        # versioninfo resources
        self.version = time.strftime("%Y.%m.%d.%H%M%S", time.gmtime())
        self.company_name = "Vanderbilt University"
        self.name = "UdmCliGen"


setup(console=[Target(script = "UdmCliGen.py")], zipfile=None,
options={"py2exe":{
                        "dll_excludes": ['w9xpopen.exe'],
                        #"bundle_files": 1,
                        "includes": ["Cheetah.DummyTransaction"] + templates,
                }
        },
)
