@rem Used in domain-specific packages to run unit tests

@set JUNIT_HOME=%UDM_3RDPARTY_PATH%\junit

@set CLASSPATH=.;%JUNIT_HOME%;%JUNIT_HOME%\junit.jar;%UDM_PATH%\bin\judm.jar;%UDM_PATH%\samples\Java\GeneTRE\GeneTRE.jar;%UDM_PATH%\samples\Java\GeneTRE\GeneTRE-test.jar

@java junit.textui.TestRunner edu.vanderbilt.isis.genetre.test.AllTests