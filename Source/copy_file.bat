@echo off

set S_PATH=.
set D_PATH=..\bin

rem 获取当前脚本所在的目录
set "current_dir=%~dp0"

rem 将相对路径转换为绝对路径
for %%I in ("%current_dir%%S_PATH%") do set "S_PATH=%%~fI"
for %%I in ("%current_dir%%D_PATH%") do set "D_PATH=%%~fI"

echo "copy files to %D_PATH% from %S_PATH%"

set CONF_PATH=%S_PATH%\config
set RES_PATH=%S_PATH%\resource

for /R "%D_PATH%" %%f in (xpf.exe xpfd.exe) do (
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




