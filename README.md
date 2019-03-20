# 关于本项目
Windows 下的 v2ray GUI程序, 使用 C++ QT 框架编写.
受[shadowsocks-qt5](https://github.com/shadowsocks/shadowsocks-qt5)启发影响.

# 编译本项目
Visual Studio 2017 是需要的, 因为我目前只在 Visual Studio 2017 上测试过.

QT 环境配置安装与配置, 查考[Qt Documentation>Qt for Windows](https://doc.qt.io/qt-5/windows.html).
首先为Visual Studio 安装 QT 插件, 参考[Qt Documentation > Qt VS Tools Manual](https://doc.qt.io/qtvstools/index.html).
之后在 Visual Studio 上打开这个项目, 或者直接双击`v2ray-qt5.vcxproj`. 待 Visual Studio 加载完毕后点击 `RUN DEBUG`或`RUN RELEASE`, 程序便运行.

使用`windeployqt`打包:
```
windeployqt v2ray-qt5.exe
```

# 程序运行效果:

右下角 windows 图标:
[!systray.png](https://github.com/vibiu/v2ray-qt/blob/master/resourse/systray.png)

菜单栏:
[!menu.png](https://github.com/vibiu/v2ray-qt/blob/master/resourse/menu.png)

其中`Enable Proxy/DisableProxy` 表示启用禁用代理. `Proxy Mode`表示代理模式, 分别有`PAC Mode`和`Global Mode`, 分别代表使用 PAC 文件过滤 URL 和 不过滤 URL, 直接全局使用代理. `Restore`表示重新打开程序主窗口, 目前配置的部分未有实现, 是空的窗口. `Quit`表示推出程序, 会关闭已经启用的代理.

# 项目结构:

`resource`是程序截图.
`src`是项目源码.

# 尝试使用:
从[release](https://github.com/vibiu/v2ray-qt/releases/tag/v0.1.0)中下载试用.
