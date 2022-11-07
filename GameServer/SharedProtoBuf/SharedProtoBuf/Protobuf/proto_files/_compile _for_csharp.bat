protoc.exe --proto_path=./ --csharp_out=../csharp/ *.proto
IF ERRORLEVEL 1 PAUSE