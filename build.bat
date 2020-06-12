cd %~dp0
g++ -static -static-libgcc -static-libstdc++ -O2 -o %~dp0Built\app.exe -I%~dp0v0\ %~dp0v0\*.cpp %~dp0v0\Tokenizer\*.cpp %~dp0v0\Runtime\*.cpp