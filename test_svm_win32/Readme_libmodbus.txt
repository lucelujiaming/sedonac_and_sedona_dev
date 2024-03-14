可以使用工程test_svm_win32来调试libmodbus_3.1.4_Win32这个DLL。
步骤为：
调试方法：
(1) C++ dll工程：属性-配置属性-调试-把 命令 为 调用该dll的exe工程的bin\Debug\*.exe，
(2) C++ dll工程：属性-配置属性-调试-把 调试器类型 设置为 仅限本机 如图：
(3) C++ dll工程：属性-配置属性-常规-把输出目录设置为 调用该dll的exe工程的bin\Debug目录下
(4) 在dll工程中打好断点，然后重新生成dll工程，为了输出dll到设置的目录下

