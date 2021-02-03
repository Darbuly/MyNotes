@echo off

set JAVA_HOME=D:\Program Files\Java\jdk1.8.0_40
set PATH=%PATH%;%%JAVA_HOME%%\bin;%%JAVA_HOME%%\jre\bin
set CLASSPATH=.;%%JAVA_HOME%%\lib\dt.jar;%%JAVA_HOME%%\lib\tools.jar
 
set RegV=HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
 
reg add "%RegV%" /v "JAVA_HOME" /d "%JAVA_HOME%" /f
reg add "%RegV%" /v "Path" /t REG_EXPAND_SZ /d "%PATH%" /f
reg add "%RegV%" /v "CLASSPATH" /d "%CLASSPATH%" /f
mshta vbscript:msgbox("Java环境已成功注册！",64,"成功")(window.close)
 
#-Dfile.encoding=utf-8
 
exit
