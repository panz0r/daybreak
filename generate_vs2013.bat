
SETLOCAL

mkdir "build"
cd build
mkdir "win64"
cd win64
set "LOCAL_RELATIVE_PATH=../.."
call %LOCAL_RELATIVE_PATH%/set_env.bat

call "%LOCAL_CMAKE_BIN%" -G "Visual Studio 12 2013 Win64" ../../engine

pause


