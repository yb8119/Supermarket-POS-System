# Supermarket-POS-System
面向对象程序设计（C++）期末大作业

开发环境： Xcode 8.2.1 + FLTK 1.3.4 （macOS Sierra 10.12.2）
详细的内容说明（其实只是简单地写了写）在PDF文档中，其实大部分代码都很重复，类的结构也比较简单（没有继承关系）。

传上来留给学弟学妹们（主要是学妹），附上作业报告，希望能够给那些不想打飞机（😷）的人一些灵感。


# 关于在Xcode中配置FLTK库

其实这才是比较重要的一点。在MacBook上使用过Visual Studio，按照老师主页上的配置确实可以使用FLTK库。但奈何自己的MacBook跑一会Windows就变铁板烧，所以还是想用Xcode，但无奈网上并没有很直接的教程，因此打算自己在这里记录一下。
这里使用的是Xcode 8.2.1 + FLTK 1.3.4，下载FLTK 1.3.4解压之后，打开./ide/Xcode4/FLTK.xcodeproj ，Xcode选择Automatically Create Schemes.注意这张**图中的FL文件夹**，我们待会需要用到。

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/IDE_DIR.png)

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/xcode1.png)

对于FLTK开发不是很熟悉的同学（比如我），上图中左侧的Tests文件夹下全是例程，可以参考，看几个例程（input,output,line_style）之后，基本上FLTK的套路能学个大概。

如果想要运行例程，在下图中点击browser（因为我这里选的是browser...）然后在下拉菜单里选择你想要执行的Scheme，编译运行即可。Scheme对应的源码可以在上述Tests下同名文件夹中找到。

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/Example.png)

打开这个FLTK.xcodeproj目的主要是为了编译出FLTK的库，我也是自己胡乱摸索出来的，可能有更好的办法，下面讲一下具体过程。

给出的例子是绘制红白相间的棋盘，我已经将源代码上传到tutorial文件夹下。

1.首先，在打开的FLTK.xcodeproj中任选一个Scheme，在Xcode顶部标签Product下选择Archive（图中所示为"hello"这个scheme生成的），编译完毕后会显示如下窗口：

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/Archive.png)

然后选择Export，弹窗中选择

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/select.png)

点击Next，然后在你保存库的地方，就会出现一个文件夹，点进去之后，右键hello（"hello"这个scheme生成的），选择”显示包内容“，进入Content/Frameworks就可以看到FLTK的库了，**请务必记得将这个fltk.framework文件拷贝出来**。

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/lib.png)

接下来我们就要将这个库和自己的Project关联起来，首先创建一个Command line tool 的 Project（FLTK_Tutorial），导入红白棋盘的源文件，在project的选项中选择Build Phase，在 Link Binary with Libraries中，选择"+"。

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/FLTK_NOT_YET.png)

在Add Another...中选择刚刚拷贝出来的fltk.framework

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/adding.png)

如果此时编译会，提示找不到头文件，因此，接下来要做的是将FLTK的头文件包含到Project中，考虑到未来可能还要使用FLTK库，这里是将FLTK添加到系统的framekwork中。

首先将fltk.framework文件拷贝到 /Library/Frameworks文件夹下，可以看到这个文件夹下有很多framework文件夹，注意此步骤需要管理员权限

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/copy1.png)

比较蛋疼的是，这个fltk.framework中虽然已经包含了头文件，但是并不全（142个），差一个abi-version.h文件，因此，我们回到最初的FLTK解压文件夹，在/FL文件夹中找到abi-version.h文件，然后再回到/Library/Frameworks下，打开刚刚拷贝进来的fltk.framework，在/Version/A/Headers/FL/ 下，将abi-version.h拷贝进来。

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/copy2.png)

集齐了头文件之后，我们需要在Xcode中设定头文件搜寻路径。还是在Project的选项中，这次选择Build Setting，在Search Paths中按照下图进行设置。

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/setSearch.png)

设置完毕后理论上编译就可以执行了。效果如图：

![imag](https://github.com/yb8119/Supermarket-POS-System/blob/master/pictures/ChessBoard.png)
