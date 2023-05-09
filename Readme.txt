Sedona开发环境搭建和Sedonac编译过程记录：

1.首先是创建一个新的用户。
创建了一个新用户：sedona_dev。之后还需要把这个用户加入到sudo的配置文件里。
执行su换为root用户，并输入visudo命令进入sudo配置文件。
在配置文件里找到下边的位置，并加入用户权限，保存退出。
# Members of the admin group may gain root privileges
%admin ALL=(ALL) ALL
sedona_dev ALL=(ALL) ALL
后面必须全部使用这个用户操作。

2.首先是安装jdk1.6.0_45。
这里必须是这个1.6.0_45的Java SE 6版本。不能使用Java SE 8版本，否则无法编译。。
文件下载地址为：https://www.oracle.com/java/technologies/javase-java-archive-javase6-downloads.html
下载以后，执行下面的指令：
sedona_dev@ubuntu:~$ chmod 777 jdk-6u45-linux-i586.bin 
sedona_dev@ubuntu:~$ mkdir jdk
sedona_dev@ubuntu:~$ mv jdk-6u45-linux-i586.bin jdk/
sedona_dev@ubuntu:~$ cd jdk/
sedona_dev@ubuntu:~/jdk$ ls
jdk-6u45-linux-i586.bin
sedona_dev@ubuntu:~/jdk$ ./jdk-6u45-linux-i586.bin 
    Unpacking...
    Checksumming...
    Extracting...
    ...
sedona_dev@ubuntu:~/jdk$ sudo mv jdk1.6.0_45 /usr/lib/jdk/
[sudo] password for sedona_dev: 
sedona_dev@ubuntu:~/jdk$ ls /usr/lib/jdk
jdk1.6.0_45  jdk1.8.0_341

3.下面安装jikes编译工具。
   59  tar -xvf jikes_1.22.orig.tar.gz 
   61  cd jikes-1.22.orig/
   62  ./configure 
   63  make
   67  ./src/jikes -version

4.修改环境变量：
在.bachrc中加入下面的设置：
# Add those line for Java HOME by leekwen
export JAVA_HOME="/usr/lib/jdk/jdk1.6.0_45"
export JRE_HOME="$JAVA_HOME/jre"
export CLASSPATH=.:JAVA_HOME/lib/dt.jar:$JAVA_HOME/lib/tools.jar:$JRE_HOME/lib
export SEDONA_HOME="/home/sedona_dev/sedona"
source $SEDONA_HOME/adm/unix/init.sh
export PATH=$JAVA_HOME/bin:$SEDONA_HOME/bin:$PATH
注意：这里必须指定使用1.6.0_45的Java SE 6版本。

5.修改init.sh脚本：
主要是修改jikes的路径：
vi /home/sedona_dev/sedona/adm/unix/init.sh
...
export sedona_home=~/sedonadev
...
# check to make sure that programs we need are in the path
# for p in jikes gcc python
for p in gcc python
do
  if ! which $p > /dev/null
  then
    echo "Sedona Linux Env ERROR: $p is not in the PATH"
  fi
done
...
function scodegen
{
  rt=$java_home/jre/lib/rt.jar
  # jikes +E -classpath $rt $sedona_home/adm/SCodeGen.java
  ~/jikes/jikes-1.22.orig/src/jikes +E -classpath $rt $sedona_home/adm/SCodeGen.java
  ...
 rm -rf $sedona_home/adm/*.class
}

值得注意的是，这个文件还指定了sedona_home，这就是为什么整个编译过程发生在/home/sedona_dev/sedonadev/下，而不是在/home/sedona_dev/sedona_dev/里面，编译结果也需要从/home/sedona_dev/sedonadev/中获取的原因。

6.使设置生效：
sedona_dev@ubuntu:~$ source ~/.bashrc
sedona_dev@ubuntu:~$ 


7.复制Sedona代码包在sedona_dev目录中。
sedona_dev@ubuntu:~$ mkdir sedona_dev
sedona_dev@ubuntu:~/sedona$ cd sedona_dev/
sedona_dev@ubuntu:~/sedona_dev$ cp -r ../sedona/* .
sedona_dev@ubuntu:~/sedona_dev$ ls
adm  apps  bin  doc  kits  lib  manifests  platforms  scode  source  src  XG_AUTO
把adm里面的python编译脚本复制到sedona_dev目录中。
sedona_dev@ubuntu:~/sedona_dev$ cp adm/*.py .
sedona_dev@ubuntu:~/sedona_dev$ ls
adm   compilejar.py   compilewin.py  fileutil.py  makedev.py   makelauncher.py    
makesedona.py   makewinvm.py    platformdb.py  runsvm.py  src
apps  compilekit.py   doc            kits         makedist.py  makesedonacert.py  
makeunixdev.py  manifests       platforms      scode      XG_AUTO
bin   compileunix.py  env.py         lib          makedocs.py  makesedonac.py     
makeunixvm.py   platArchive.py  props.py       source
[2023/5/6 15:18:20] sedona_dev@ubuntu:~/sedona_dev$ ls src/sedonac
[2023/5/6 15:18:20] build.xml  src

这个目录可以自己指定，我指定为sedona_dev。

8.开始编译：
编译脚本使用的是Python 2.7.3。如果使用Python3，需要手工调整所有的py脚本的语法。
sedona_dev@ubuntu:~/sedona_dev$ python makesedona.py
Compile [sedona.jar]
  Javac [src/sedona/src]
  Jar [lib/sedona.jar]
sedona_dev@ubuntu:~/sedona_dev$ python makesedonac.py
Compile [sedonac.jar]
  Javac [src/sedonac/src]
  Jar [lib/sedonac.jar]
sedona_dev@ubuntu:~/sedona_dev$ ls
adm            compilejar.pyc  doc          fileutil.pyc  makedist.py        
makesedonac.py  makewinvm.py    platforms  scode
apps           compilekit.py   env.py       kits          makedocs.py        
makesedona.py   manifests       props.py   source
bin            compileunix.py  env.pyc      lib           makelauncher.py    
makeunixdev.py  platArchive.py  props.pyc  src
compilejar.py  compilewin.py   fileutil.py  makedev.py    makesedonacert.py  
makeunixvm.py   platformdb.py   runsvm.py  XG_AUTO

可以看到编译通过。


注意：这个目录中有很多脚本。分别用于不同模块的编译。
在执行这些python脚本的时候，会出现一些错误。类似于这样的错误信息：
sedona_dev@ubuntu:~$ python ./sedona/adm/unix/makeunixdev.py 
Traceback (most recent call last):
  File "./sedona/adm/unix/makeunixdev.py", line 15, in <module>
    import env
ImportError: No module named env
如果出现这样的错误。这个不是因为你没有安装env的原因，也不需要执行pip install env这种命令。
这些所谓的import env其实指的是~/sedona/adm里面的env.py文件。
 

9.修改代码查看编译效果：
如果遇到，编译soxcert报错。
修改env.py文件：
sedona_dev@ubuntu:~/sedona_dev$ vi /home/sedona_dev/sedona_dev/env.py
加入temp属性。
# lujiaming Add at 05/06/23
temp         = os.path.join(home, "temp")

如果编译soxcert再次报错。
Compile [soxcert]
/home/sedona_dev/sedona_dev/src/soxcert/kit.xml:20: Missing kit dependency 'sys 1.2+'
*** FAILED with 1 error(s) and 0 warning(s) ***

执行grep -Rns "1.2" . | grep "kit.xml"。把所有的<depend on="sys 1.2+"  />改成<depend on="sys  0.1+" />。
类似的在kit.xml中类似的地方也要修改。。
还需要修改platforms里面的文件。
platforms/src/generic/unix/kit.xml
platforms/src/generic/unix/generic-unix.xml
platforms/src/generic/win32/kit.xml

还有就是我在Component中加入了define Log log。因此上其他的代码中需要注释掉这句话。
// define Log log

10.编译vm再次报错：
编译vm再次报错。
/home/sedona_dev/sedonadev/temp/generic-unix/runtime.c:10:18: fatal error: list.h: No such file or directory
执行：
cp ./source/list.h /home/sedona_dev/sedonadev/src/vm/
这个地方好像是写死的。必须是~/sedonadev/目录。

解决方法，注释掉makeunixdev.py中的makeunixvm.main([])部分，因为我们不需要在unix下执行svm程序。

11.如果想查看编译脚本，可以修改这里：
  compilejar.py
      在类似于status = os.system(cmd) 的语句后面。加入打印语句：
  print "Compile Javac os.system(" + cmd + ")"
注意Javac和Jar 都要加。
结果如下：
sedona_dev@ubuntu:~/sedona_dev$ python makesedona.py
Compile [sedona.jar]
  Javac [/home/sedona_dev/sedonadev/src/sedona/src]
Compile Javac os.system(
~/jikes/jikes-1.22.orig/src/jikes +E +Pno-shadow -d /home/sedona_dev/sedonadev/tempJar \
-classpath /usr/lib/jdk/jdk1.6.0_45/jre/lib/rt.jar:/home/sedona_dev/sedonadev/src/sedona/src \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/kit/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/manifest/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/platform/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/offline/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/dasp/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/sox/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/util/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/util/sedonadev/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/web/*.java \
 /home/sedona_dev/sedonadev/src/sedona/src/sedona/xml/*.java
)
Compile Javac os.system(
/usr/lib/jdk/jdk1.6.0_45/bin/jar \
cf /home/sedona_dev/sedonadev/lib/sedona.jar -C /home/sedona_dev/sedonadev/tempJar .
)
  Jar [/home/sedona_dev/sedonadev/lib/sedona.jar]


sedona_dev@ubuntu:~/sedona_dev$ python makesedonac.py
Compile [sedonac.jar]
  Javac [/home/sedona_dev/sedonadev/src/sedonac/src]
Compile Javac os.system(
    ~/jikes/jikes-1.22.orig/src/jikes +E +Pno-shadow -d /home/sedona_dev/sedonadev/tempJar \
    -classpath /usr/lib/jdk/jdk1.6.0_45/jre/lib/rt.jar:\
    /home/sedona_dev/sedonadev/src/sedonac/src:/home/sedona_dev/sedonadev/lib/sedona.jar \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/analysis/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/asm/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/ast/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/gen/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/ir/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/namespace/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/parser/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/platform/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/scode/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/steps/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/test/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/translate/*.java \
    /home/sedona_dev/sedonadev/src/sedonac/src/sedonac/util/*.java 
)
Compile Javac os.system(
    /usr/lib/jdk/jdk1.6.0_45/bin/jar cf /home/sedona_dev/sedonadev/lib/sedonac.jar \
-C /home/sedona_dev/sedonadev/tempJar .
)
  Jar [/home/sedona_dev/sedonadev/lib/sedonac.jar]

12.下面查看最终的编译输出：
sedona_dev@ubuntu:~/sedona_dev$ python makeunixdev.py 
Compile [sedona.jar]
  Javac [/home/sedona_dev/sedonadev/src/sedona/src]
  Jar [/home/sedona_dev/sedonadev/lib/sedona.jar]
Compile [sedonac.jar]
  Javac [/home/sedona_dev/sedonadev/src/sedonac/src]
  Jar [/home/sedona_dev/sedonadev/lib/sedonac.jar]
Compile [sedonacert.jar]
  Javac [/home/sedona_dev/sedonadev/src/sedonacert/src]
  Jar [/home/sedona_dev/sedonadev/lib/sedonacert.jar]
-------------------------------------------------------------------
/home/sedona_dev/sedonadev
/home/sedona_dev/sedonadev/src
-------------------------------------------------------------------
Compile [sys] Parse [50 files] WriteKit [/home/sedona_dev/sedonadev/kits/sys/sys-82791acf-0.1.0.kit] 
WriteManifest [/home/sedona_dev/sedonadev/manifests/sys/sys-82791acf.xml] 
...
-------------------------------------------------------------------
Compile [sys]
  Parse [50 files]
  WriteKit [/home/sedona_dev/sedonadev/kits/sys/sys-82791acf-0.1.0.kit]
  WriteManifest [/home/sedona_dev/sedonadev/manifests/sys/sys-82791acf.xml]
...

*** Success! ***
sedona_dev@ubuntu:~/sedona_dev$ 

可以看到不知道为什么整个编译过程发生在/home/sedona_dev/sedonadev/下，而不是在/home/sedona_dev/sedona_dev/里面。
因此上，我们所有的改动都需要在/home/sedona_dev/sedonadev/里面进行，编译结果也需要从/home/sedona_dev/sedonadev/中获取。

至此编译过程完成。。


13.下面修改代码，查看最终的编译效果：
下面以修改Component名字长度为例，演示修改效果。
sedona_dev@ubuntu:~/sedonadev$ grep -Rns "nameTooLong" .
./src/sys/Err.sedona:53:  define int nameTooLong          = 61
./src/sys/Component.sedona:419:    if (!in.readStr(name, 8)) return Err.nameTooLong
./src/sedona/src/sedona/Component.java:295:    if (name.length() > 7) return "nameTooLong";
sedona_dev@ubuntu:~/sedonadev$ 

这个时候执行sedonac.exe显示如下错误：
D:\SeconaDownload>C:\Sedona\SedonaWorkbench-1.2.28\sedona\bin\sedonac.exe  app.sax
  ConvertAppFile [D:\SeconaDownload\app.sax -> D:\SeconaDownload\app.sab]
app.sax:133: Invalid name "BB77BB77BB77BB77BB77" (nameTooLong)
*** FAILED with 1 error(s) and 0 warning(s) ***

D:\SeconaDownload>
下面修改代码：
sedona_dev@ubuntu:~/sedonadev$ vi ./src/sedona/src/sedona/Component.java 
sedona_dev@ubuntu:~/sedonadev$ grep -Rns "nameTooLong" .
./src/sys/Err.sedona:53:  define int nameTooLong          = 61
./src/sys/Component.sedona:419:    if (!in.readStr(name, 8)) return Err.nameTooLong
./src/sedona/src/sedona/Component.java:295:    if (name.length() > 15) return "nameTooLong with 15";
sedona_dev@ubuntu:~/sedonadev$ 
可以看到我们把Component名字长度改成了15。并且修改了提示信息。
之后把生成的jar包复制到Windows电脑中：
sedona_dev@ubuntu:~/sedonadev$ cp -r ../sedonadev /mnt/hgfs/Sedona/lujiaming_exchange/
sedona_dev@ubuntu:~/sedonadev$ 

把编译出来的jar包复制到电脑的C:\Sedona\SedonaWorkbench-1.2.28\sedona\lib目录中。
再次执行sedonac.exe显示如下错误：
D:\SeconaDownload>C:\Sedona\SedonaWorkbench-1.2.28\sedona\bin\sedonac.exe  app.sax
  ConvertAppFile [D:\SeconaDownload\app.sax -> D:\SeconaDownload\app.sab]
app.sax:133: Invalid name "BB77BB77BB77BB77BB77" (nameTooLong with 15)
*** FAILED with 1 error(s) and 0 warning(s) ***

可以看到提示信息已经生效。接着把名字改为15个字符以内。再次执行sedonac.exe程序。
D:\SeconaDownload>C:\Sedona\SedonaWorkbench-1.2.28\sedona\bin\sedonac.exe  app.sax
  ConvertAppFile [D:\SeconaDownload\app.sax -> D:\SeconaDownload\app.sab]
  +----------------------------------
  |  RAM:     29.7kb (30452 bytes)
  |  FLASH:    1.1kb (1143 bytes)
  +----------------------------------
*** Success! ***
可以看到生成成功。

D:\SeconaDownload>

