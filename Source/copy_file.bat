@echo off

set S_PATH=.\config
set D_PATH=..\bin

pushd "%S_PATH%" 2>nul && (
    set "S_PATH=%cd%"
    popd
)


set CONF_PATH=%S_PATH%\config
set RES_PATH=%S_PATH%\resource

for /R "%D_PATH%" %%f in (xpf.exe) do (
    if exist "%%f" (
        echo copy files from "%CONF_PATH%" to "%%~dpf\xpfonfig" ....
        xcopy "%CONF_PATH%" "%%~dpf\xpfconfig" /E /H /C /I /Y
        echo copy complete
    )
)

for /R "%D_PATH%" %%f in (xpf.exe) do (
    if exist "%%f" (
        echo copy files from "%RES_PATH%" to "%%~dpf\xpfresource" ....
        xcopy "%RES_PATH%" "%%~dpf\xpfresource" /E /H /C /I /Y
        echo copy complete
    )
)





