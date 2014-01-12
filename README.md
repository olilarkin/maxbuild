maxbuild v-0-2
Oli Larkin, 2009-2014
York, UK
================

a folder structure and IDE projects for building cross platform Max MSP externals. It includes a python script for 
rapidly cloning a project, doing a find and replace on strings in filenames and inside the source code itself

IDE projects are for MSVS2010 and Xcode3 (hopefully it will work in more recent versions too)

it includes submodules for the max sdk and for Graham Wakefields MaxCPP, so when you check out the project, you may
want to do it like this in order to checkout the submodules at the same time.

git clone --recursive https://github.com/olilarkin/maxbuild.git

after cloning the repository you can cd to /examples

run ./duplicate.py mbmaxcpp mynewmaxexternal to duplicate (on windows you may need to invoke python.exe)
