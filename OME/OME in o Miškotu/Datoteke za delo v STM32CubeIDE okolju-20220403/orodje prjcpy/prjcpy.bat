@echo off
echo.
echo.

echo ************************
echo A batch script to help with CubeIDE project duplication.
echo Place prjcpy.bat and fart.exe in the CubeIDE workspace.
echo Run prjcpy in the workspace folder in a command line.
echo First parameter: source project folder
echo Second parameter: target project folder
echo Example: prjcpy VAJA_01 VAJA_02
echo Import the target project in the CubeIDE.
echo Clean the project and re-build it.
echo And that is it.
echo.
echo.

echo Copying CubeIDE project
echo Source project: %1
echo Target project: %2

echo.
echo.

rem Save current directory.
set curdir=%cd%


rem Create a target project folder.
mkdir %2

rem Copy all files to target folder.
xcopy %1 %2 /h /i /c /k /e /r /y

echo.
echo.


rem Go to target folder
cd %2 

rem Delete .mxproject (even if hidden) and Debug.launch.
del  /A:H .mxproject
del  %1*.launch

echo.
echo.

rem Rename .ioc files.
ren %1.ioc %2.ioc

echo.
echo.

rem Go to Debug subfolder.
cd Debug

rem Delete old debug files.
del %1.*


rem Return to workspace folder.
cd..
cd..

rem Replace old project name in metafiles.
fart %2\.cproject %1 %2
fart %2\.project %1 %2
fart %2\%2.ioc %1 %2

echo.
echo.

rem Restore current directory
cd %curdir%