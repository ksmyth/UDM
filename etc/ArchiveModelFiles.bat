:: Archives the model files created during Windows build
::
cd %UDM_PATH%
zip -r model-files.zip . -i *_udm.xml -i *_udm.udm -x judm/build/* -x samples/Java/*
