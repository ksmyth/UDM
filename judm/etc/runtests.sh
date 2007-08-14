#!/bin/bash 
#Used in domain-specific packages to run unit tests
export LD_LIBRARY_PATH=../judm

java -Djava.library.path=../judm -jar @DSPACKAGE@-test.jar
