#!/usr/bin/python

# Python shell script for Duplicating Max External Projects

from __future__ import generators

import fileinput, glob, string, sys, os, re, uuid
from shutil import copy, copytree, ignore_patterns, rmtree
from os.path import join

VERSION = "0.1.0"

# binary files that we don't want to do find and replace inside
FILTERED_FILE_EXTENSIONS = [".mxo", ".mxe",".ico",".icns", ".pdf", ".png", ".zip", ".exe", ".wav", ".aif"]

def checkdirname(name, searchproject):
  "check if directory name matches with the given pattern"
  print ""
  if name == searchproject:
# if name == searchproject + ".xcodeproj":
    return True
  else:
    return False

def replacestrs(filename, s, r):
  files = glob.glob(filename)
  
  for line in fileinput.input(files,inplace=1):
    string.find(line, s)
    line = line.replace(s, r)
    sys.stdout.write(line)
    
def replacestrsChop(filename, s, r):
  files = glob.glob(filename)
  
  for line in fileinput.input(files,inplace=1):
    if(line.startswith(s)): 
      line = r + "\n"
    sys.stdout.write(line)

def dirwalk(dir, searchproject, replaceproject):
  for f in os.listdir(dir):
    fullpath = os.path.join(dir, f)
    
    if os.path.isdir(fullpath) and not os.path.islink(fullpath):
      if checkdirname(f, searchproject + ".xcodeproj"):
        os.rename(fullpath, os.path.join(dir, replaceproject + ".xcodeproj"))
        fullpath = os.path.join(dir, replaceproject + ".xcodeproj")
        
        print 'recursing in main xcode project directory: '
        for x in dirwalk(fullpath, searchproject, replaceproject):
          yield x
      elif (f ==  "bin"):
        print 'recursing in bin directory: '
        for x in dirwalk(fullpath, searchproject, replaceproject):
          yield x
      
    if os.path.isfile(fullpath):
      tabstring = ""
      #for tab in range(0,tabs):
      # tabstring += "\t"
      
      filename = os.path.basename(fullpath)
      newfilename = filename.replace(searchproject, replaceproject)
      base, extension = os.path.splitext(filename)
      
      if (not(extension in FILTERED_FILE_EXTENSIONS)):
        print tabstring + 'Replacing project name strings in file', filename
        replacestrs(fullpath, searchproject, replaceproject)
        
        print tabstring + 'Replacing captitalized project name strings in file', filename
        replacestrs(fullpath, searchproject.upper(), replaceproject.upper())
      else:
        print tabstring + 'NOT replacing name strings in file', filename
      
      if filename != newfilename:
        print tabstring + 'Renaming file ' + filename + ' to ' + newfilename
        os.rename(fullpath, os.path.join(dir, newfilename))
  
      yield f, fullpath 
    else:
      yield f, fullpath

def main():
  global VERSION
  print "\nMax Project Duplicator v" + VERSION + " by Oli Larkin ------------------------------\n"
  
  if len(sys.argv) != 3:
    print "Usage: duplicate.py inputprojectname outputprojectname",
    sys.exit(1)
  else:
    input=sys.argv[1]
    output=sys.argv[2]

    if ' ' in input:
      print "error: input project name has spaces",
      sys.exit(1)
      
    if ' ' in output:
      print "error: output project name has spaces",
      sys.exit(1)
    
    # remove a trailing slash if it exists
    if input[-1:] == "/":
      input = input[0:-1]
    
    if output[-1:] == "/":
      output = output[0:-1]
      
    #check that the folders are OK
    if os.path.isdir(input) == False:
      print "error: input project not found",
      sys.exit(1)
        
    if os.path.isdir(output):
      print "error: output folder allready exists",
      sys.exit(1)
        
    print "copying " + input + " folder to " + output
    copytree(input, output, ignore=ignore_patterns('*.mxo', '*.mxe', '*.exe', '*.dmg', '*.pkg', '*.mpkg', '*.svn', '*.ncb', '*.suo', '*sdf', 'ipch', 'build-*', '*.layout', '*.depend', '.DS_Store', 'xcuserdata*' ))
    cpath = os.path.join(os.getcwd(), output)

    #replace manufacturer name strings
    for dir in dirwalk(cpath, input, output):
      pass
    
    print "\ncopying gitignore template into project folder"

    copy('gitignore_template', output + "/.gitignore")
    
if __name__ == '__main__':
  main()