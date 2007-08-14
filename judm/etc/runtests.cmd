@rem Used in domain-specific packages to run unit tests
@rem Necessary to pick up DLLs from judm dir
@set PATH=%PATH%;..\judm
@java -Djava.library.path=..\judm -jar @DSPACKAGE@-test.jar