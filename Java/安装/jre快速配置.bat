set JAVA_HOME=D:\Program Files\Java
set PATH=%PATH%;%%JAVA_HOME%%\jre\bin
set CLASSPATH=.;%%JAVA_HOME%%\jre\lib
 
set RegV=HKLM\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
 
reg add "%RegV%" /v "JAVA_HOME" /d "%JAVA_HOME%" /f
reg add "%RegV%" /v "Path" /t REG_EXPAND_SZ /d "%PATH%" /f
reg add "%RegV%" /v "CLASSPATH" /d "%CLASSPATH%" /f
mshta vbscript:msgbox("Java�����ѳɹ�ע�ᣡ",64,"�ɹ�")(window.close)
 
exit
