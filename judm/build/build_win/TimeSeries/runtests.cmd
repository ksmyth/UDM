@rem Used in domain-specific packages to run unit tests

@set JUNIT_HOME=%UDM_3RDPARTY_PATH%\junit

@set CLASSPATH=.;%JUNIT_HOME%;%JUNIT_HOME%\junit.jar;%UDM_PATH%\bin\judm.jar;%UDM_PATH%\samples\Java\TimeSeries\TimeSeries.jar;%UDM_PATH%\samples\Java\TimeSeries\TimeSeries-test.jar

@java junit.textui.TestRunner edu.vanderbilt.isis.timeseries.test.AllTests