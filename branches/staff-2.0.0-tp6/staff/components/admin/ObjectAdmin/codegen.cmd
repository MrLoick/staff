setlocal
set arch=%1%
if "%arch%" == "" (
  echo.
  echo Error: Arch is not set.
  exit 1
)
SET STAFF_HOME=%cd%\..\..\..\deploy\win_%arch%\staff
set PATH=..\..\..\..\..\rise\deploy\win_%arch%\lib;%STAFF_HOME%\bin;%STAFF_HOME%\lib;%PATH%
cd src
staff_codegen -u -tcomponent ObjectAdmin.h
staff_codegen -u -twsdl ObjectAdmin.h
endlocal
