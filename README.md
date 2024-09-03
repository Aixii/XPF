# XPF

X Plugins Framework

## 1 使用方法

XPFCore 是框架的核心  
Bin/XPFConfig/XPF.xml 是插件核心启动加载的配置项，包括是否支持同源多启动，多屏幕等配置  
Bin/XPFConfig/XPFPlugins.xml 是配置加载哪些插件的配置文件  

XPFUi 是通过配置文件生成界面的插件，建议最后加载  
Bin/XPFConfig/XPF.xml WidgetBody 和 WidgetHeader 的内容最终会交由 XPFUi 通过配置文件名进行生成  
Bin/XPFConfig/XPFUi 中存放 XPFUi 待生成界面的配置文件  

### 新建插件

复制 XPFUi 修改其下的 XPFUiPlugin.pro XPFUiPlugin.cpp XPFUiPlugin.h 的名字为自己将要新建插件的名字  
修改这三个文件中相应的生成目标的名称及类的名称。  
IXPFPluginHelper 这个类提供了框架的一些功能，提供了插件之间的通信，采用订阅及发布模式。  

后续我会提供一个工具自动生成插件  

## 2 待开发的功能或待完成的工作

* 换肤功能
* 服务机制
* 同源软件之间的通信
* 日志插件
* 项目生成工具的开发
* 国际化处理
* 远程通信插件
* 多平台适配（目前只考虑 Windows 和 Linux, Qt 本身具备跨平台特性）
