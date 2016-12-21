# Supermarket-POS-System
面向对象程序设计（C++）期末大作业

开发环境： Xcode 8.2.1 + FLTK 1.3.4
详细的内容说明（其实只是简单地写了写）在PDF文档中，其实大部分代码都很重复，类的结构也比较简单（没有继承关系）。

传上来留给学弟学妹们（主要是学妹），希望能够给那些不想打飞机（😷）的人一些灵感。


# 关于在Xcode中配置FLTK库

在MacBook上使用过Visual Studio，按照老师主页上的配置确实可以使用FLTK库。但奈何自己的MacBook跑一会Windows就变铁板烧，所以还是想用Xcode。
这里使用的是Xcode 8.2.1 + FLTK 1.3.4，下载FLTK 1.3.4解压之后，打开./ide/Xcode4/FLTK.xcodeproj ，选择Automatically Create Schemes.

![image](https://github.com/yb8119/Supermarket-POS-System/blob/Edit-Readme/pictures/Xcode1.png)

对于FLTK开发不是很熟悉的同学（比如我），上图中左侧的Tests文件夹下全是例程，可以参考，看几个例程（input,output,line_style）之后，基本上FLTK的套路能学个大概。

![image](https://github.com/yb8119/Supermarket-POS-System/blob/Edit-Readme/pictures/Example.png)

想要运行例程，在上图中点击browser（因为我这里选的是browser...）然后在下拉菜单里选择你想要执行的Scheme，编译运行即可。Scheme对应的源码可以在上述Test下同名文件夹中找到。

打开这个FLTK.xcodeproj目的主要是为了编译出FLTK的库，我也是自己胡乱摸索出来的，可能有更好的办法，下面讲一下怎么生成库。


1.首先，任选一个Scheme，在Xcode顶部标签Product下选择Archive（图中所示为"hello"这个scheme生成的）

pict

然后选择Export，弹窗中选择

puct

点击Next，然后在你保存库的地方，就会出现一个文件夹，点进去之后，右键hello（"hello"这个scheme生成的），选择”显示包内容“，进入Content/Frameworks就可以看到FLTK的库了，记得将这个库拷贝出来。
pict
接下来我们就要将这个库和自己的Project关联起来，首先创建一个Command line tool 的 Project，例如FLTK_Tutorial，在其选项卡中选择Build Phase，在 Link Binary with Libraries中，选择"+"。
pict

在Add Another...中选择刚刚生成的fltk.frameworks
