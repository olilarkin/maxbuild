ARCHIVED - use https://github.com/Cycling74/min-devkit instead

maxbuild v-0-3
================

Oli Larkin, 2009-2016
York, UK


a folder structure and IDE projects for building cross platform Max MSP externals. It includes a python script for 
rapidly cloning a project, doing a find and replace on strings in filenames and inside the source code itself

IDE projects are for MSVS2010 and Xcode7

It includes submodules for the Max SDK and for Graham Wakefield's MaxCPP, so when you check out the project, you may want to do it like this in order to checkout the submodules at the same time.

git clone --recursive https://github.com/olilarkin/maxbuild.git

after cloning the repository you can cd to /examples

run ./duplicate.py mbmaxcpp mynewmaxexternal to duplicate (on windows you may need to invoke python.exe)
