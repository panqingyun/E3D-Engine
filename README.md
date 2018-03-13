# E3DEngine
![](https://github.com/panqingyun/E3D/engine.png)  
3D引擎 目前完成
- [x] 场景
- [x] 摄像机
- [x] 粒子系统
- [x] 天空盒
- [x] 文理序列帧
- [x] 材质
- [x] RenderToTexture
- [x] 多FBO
- [x] 渲染合批
- [x] 模型读取和显示
- [x] Mono和Bullet已接入。

#### 渲染系统使用的OpenGL ES，Windows上使用AMD的ES模拟器。实时阴影、骨骼动画、UI尚未完成。

## 环境部署

### Win32环境配置

- 将``proj_win32/RenderSystem/gles_renderSystem/GLES/dll`` 中的两个dll文件拷贝到``proj_win32/bin``中。 

## 从C#编辑器启动 调试C++代码方法：
- 在``EngineCore``项目上右键打开属性窗口，选择调试选项页，修改调试类型为混合
- 在``EngineEditor``上右键打开属性窗口，选择调试，勾选“启用本机代码调试”
- 完成

## Mono C#代码调试方法
下载并安装 ``Xamarin Studio``，在系统环境变量中添加 ``MONODEVELOP_SDB_TEST`` 值为 1，
打开``MonoScriptManager.cpp`` 修改``_DEBUG_CSHARP`` 为 1，启动程序，这时候程序会进入等待状态，不会显示出来， 
接下来在``Xamarin Studio``中打开``GameClient.CSharp\GameClient.CSharp.csproj``，在``Solution``面板中右键项目从打开菜单中选择 “RunWith -> CustomConfiguration”，
窗口最下方``RunAction``处选择``Debug-Custom Command Mono Soft Debugger``,然后单击最右下方的``Debug``按钮，
打开新的窗口后，在IP一栏填入``127.0.0.1`` Port一栏填入 ``10000`` 点击``Connect``按钮。之前处于等待的程序会出现了，接下来就可以在Xamarin Studio中调试Mono C#代码了。
