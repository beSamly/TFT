protoc.exe --proto_path=./ --cpp_out=../ *.proto

protoc.exe --proto_path=./ --cs_out=../csharp *.proto
IF ERRORLEVEL 1 PAUSE