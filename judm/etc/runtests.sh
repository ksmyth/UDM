#!/bin/bash 
#Used in domain-specific packages to run unit tests

java -Djava.library.path=../judm -jar @DSPACKAGE@-test.jar
