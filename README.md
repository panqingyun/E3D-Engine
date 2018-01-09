# E3DEngine
3D引擎
目前完成基本渲染，摄像机，粒子系统，文理序列帧，材质，RenderToTexture，多FBO，渲染合批等，Mono和Bullet已接入，功能尚未完善。

渲染系统使用的OpenGL ES，Windows上使用AMD的ES模拟器。

光照尚未完成

模型文件读取已完成，但是模型的材质尚未完成，骨骼动画也未完成

模型部分的结构设计也存在问题

Android 和 IOS接入也有待解决。

## 环境部署

### Win32环境配置

1.项目根目录下有mono文件夹，需将此文件夹拷贝到proj_win32/bin/Library 中，同时需要拷贝到proj_win32/bin中的还有根目录中的Resource文件夹。 

2.将proj_win32/EngineCore/GLES/dll 中的两个dll文件拷贝到proj_win32/bin中。 

3.完成环境配置


## 从C#编辑器启动 调试C++代码方法：

在EngineCore项目上右键打开属性窗口，选择调试选项页，修改调试类型为混合

在EngineEditor上右键打开属性窗口，选择调试，勾选“启用本机代码调试”

完成

## Mono C#代码调试方法
下载并安装 Xamarin Studio，在系统环境变量中添加 MONODEVELOP_SDB_TEST 值为 1，
打开MonoScriptManager.cpp 修改_DEBUG_CSHARP 为 1，启动程序，这时候程序会进入等待状态，不会显示出来， 
接下来在Xamarin Studio中打开GameClient.CSharp\GameClient.CSharp.csproj，在Solution面板中右键项目从打开菜单中选择 “RunWith -> CustomConfiguration”，
窗口最下方“RunAction”处选择“Debug-Custom Command Mono Soft Debugger”,然后单击最右下方的Debug按钮，
打开新的窗口后，在IP一栏填入127.0.0.1 Port一栏填入 10000 点击Connect按钮。之前处于等待的程序会出现了，接下来就可以在Xamarin Studio中调试Mono C#代码了。
