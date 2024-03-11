Sedona开发环境搭建和Sedonac编译过程记录（Win10）：
写在前面：
该文档基于《Sedona开发环境搭建和Sedonac编译过程记录》的基础上生成。
不是从原始软件包生成的。

1.首先是创建一个虚拟机。
因为整个编译过程使用的是jdk1.6.0_45。而不是Java SE 8版本。

2.首先是安装jdk1.6.0_45。
这里必须是这个1.6.0_45的Java SE 6版本。不能使用Java SE 8版本，否则无法编译。。
文件下载地址为：https://www.oracle.com/java/technologies/javase-java-archive-javase6-downloads.html
注意这里安装的是x86版本。不能安装x64版本。
也就是安装jdk-6u45-windows-i586.exe。不能安装jdk-6u45-windows-x64.exe。否则会报这个错误。
        Failed to load the JNI shared library \Java\jre6\bin\client\jvm.dll

3.下面安装Visual Studio编译工具。否则会报这个错误。
   Exception: FATAL: Visual Studio environment not setup [VCINSTALLDIR]
还需要配置下面两个环境变量：
export VCINSTALLDIR="C:\Program Files\Microsoft Visual Studio\2022\Community"
export win_sdk="C:\Program Files (x86)\Windows Kits\10"
修改PATH，添加下面两个路径：
export PATH=$PATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.38.33130\bin\Hostx86\x86"
export PATH=$PATH:"C:\Program Files (x86)\Java\jdk1.6.0_45\bin"

4.修改环境变量：
在环境变量中加入下面的设置：
# Add those line for Java HOME by leekwen
export JAVA_HOME="C:\Program Files (x86)\Java\jdk1.6.0_45"
export JRE_HOME="C:\Program Files (x86)\Java\jdk1.6.0_45\jre"
# export CLASSPATH=.:JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:$JRE_HOME/lib
注意：这里必须指定使用1.6.0_45的Java SE 6版本。


5.根据遇到的错误，修改编译脚本：
修改compilewin.py文件，加入Include文件路径。
...
  # cmd += " /I\"" + os.path.join(winSdk, "Include") + "\""
  cmd += " /I\"" + os.path.join(winSdk, "Include\\10.0.22000.0\\ucrt") + "\""
  cmd += " /I\"" + os.path.join(vcInstallDir, "VC\\Tools\\MSVC\\14.38.33130\\include") + "\""
...
修改makewinvm.py文件，注释掉编译svm文件的部分。因为这个部分，使用其他工程生成。
...
	# I will compile svm.exe by other project
    # compilewin.compile(exeFile, srcFiles, includes, libs, cdefs)
...
修改platArchive.py文件，这里调用platformdb.py的地方写错了。
...
  # cmd = os.path.join(env.adm, "platformdb.py")
  cmd = "python " + os.path.join(env.adm, "platformdb.py")
...


6.在Windows上的编译生成manifests文件和kits文件的方法如下：
   首先需要安装JDK。之后步骤如下：
   1. 把整个目录拷贝到c盘。文件目录为“C:\sedona_dev\sedona_dev”。
   2. 进入目录C:\sedona_dev\sedona_dev中：
   3. 执行下面的命令就会生成kit文件和xml文件：
        C:\sedona_dev\sedona_dev>java -Dsedona.home="C:\sedona_dev\sedona_dev" -cp "C:\sedona_dev\sedona_dev\lib\*"  sedonac/Main src\sys
          Parse [50 files]
          WriteKit [C:\sedona_dev\sedona_dev\kits\sys\sys-82791acf-0.1.0.kit]
          WriteManifest [C:\sedona_dev\sedona_dev\manifests\sys\sys-82791acf.xml]
        *** Success! ***
    
   生成app.scode也是可以的。
        C:\sedona_dev\sedona_dev\source>java -Dsedona.home="C:\sedona_dev\sedona_dev" -cp "C:\sedona_dev\sedona_dev\lib\*"  sedonac/Main app.xml
          ReadKits [16 kits]
          WriteImage [C:\sedona_dev\sedona_dev\source\app.scode] (101500 bytes)
          +----------------------------------
          |  Data:      6.9kb (7044 bytes)
          |  Code:     99.1kb (101500 bytes)
          |  Total:     106kb (108544 bytes)
          +----------------------------------
        *** Success! ***
        C:\sedona_dev\sedona_dev>
    
    也可以写一个脚本来实现上面的步骤：
        C:\sedona_dev\sedona_dev>type bin\sedonac.bat
        @echo off
        set "CURRENT_DIR=%cd%"
        java -Dsedona.home="%CURRENT_DIR%" -cp "%CURRENT_DIR%\lib\*"  sedonac/Main %1

    之后执行下面的命令就会生成kit文件和xml文件。并完成所有的编译工作。
        bin\sedonac.bat src\Arith\
        bin\sedonac.bat src\sys\
        bin\sedonac.bat platforms\src\XunGaoAuto\unix\
        bin\sedonac.bat src\inet\
        bin\sedonac.bat src\sox\
        bin\sedonac.bat src\Variable\
        bin\sedonac.bat src\FieldBus\
        bin\sedonac.bat src\PID\
        bin\sedonac.bat src\Timer\
        bin\sedonac.bat src\Math\
        bin\sedonac.bat src\BitLogic\
        bin\sedonac.bat src\Compare\
        bin\sedonac.bat src\Convert\
        bin\sedonac.bat src\WordOpr\
        bin\sedonac.bat src\Other\
        bin\sedonac.bat src\Schedule\
        bin\sedonac.bat source\app.xml


