@rem Used in domain-specific packages to run unit tests

@set JUNIT_HOME=%UDM_3RDPARTY_PATH%\junit

@set CLASSPATH=.;%JUNIT_HOME%;%JUNIT_HOME%\junit.jar;%UDM_PATH%\bin\judm.jar;%UDM_PATH%\samples\Java\GeneTF\GeneTF.jar;%UDM_PATH%\samples\Java\GeneTF\GeneTF-test.jar

@java junit.textui.TestRunner edu.vanderbilt.isis.genetf.test.AllTests