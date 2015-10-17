#!/bin/bash

if [[ $# -lt 2 ]]
then
	echo "usage:	$0 name_project | dir"
else
	mkdir $2
	touch -a {$2/README,$2/makefile,$2/$1.c}
	echo "$2" > $2/README
	echo "/* This file generated by mkprj.sh */" > $2/$1.c
	cat template/template1.c >> $2/$1.c
	echo "TARGET = $1" > $2/makefile
	cat template/makefile >> $2/makefile
fi
exit 0

