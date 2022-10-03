#!/bin/sh

CFILES=$(find . -name '*.c')
CPPFILES=$(find . -name '*.cpp')
HFILES=$(find . -name '*.h')
HPPFILES=$(find . -name '*.hpp')
MAKEFILES=$(find . -name 'makefile')
DOTMKFILES=$(find . -name '*.mk')
SHFILES=$(find . -name '*.sh')
MDFILES=$(find . -name '*.md')

add_files()
{
    git add $CFILES
    git add $CPPFILES
    git add $HFILES
    git add $HPPFILES
    git add $MAKEFILES
    git add $DOTMKFILES
    git add $SHFILES
    git add $MDFILES
}

if [ -z $1 ]
then
    add_files
    git commit
else
    add_files
    git commit -m "$1";
fi
