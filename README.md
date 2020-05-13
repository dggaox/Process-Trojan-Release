# Process-Trojan-Release
## 网络攻防之第二次作业 基于进程扫描的防木马软件最终发布版
## 软件简要说明：
该软件可以查看进程，查杀指定进程，以及扫描局域网内指定的地址段的所有主机的程序
首先进行端口扫描，扫描的范围从文件到注册表。网络扫描和进程扫描
进程扫描可以扫描出进程的ID，进程名称以及父进程等
当扫描发现异常进行时，异常进程会显示红色，这时候我们可以查杀进程，把恶意程序或者疑似木马终止进程
### 注：该软件采用C++进行编写，利用MFC模式，遇到恶意程序通过调用Knernel32内核级进行进程终止 具体截图已经上传到移动教学平台 这里不再赘述
## 源代码文档如下：
## NeighborInfo.dsp
此文件(项目文件)包含项目级别的信息
用于构建单个项目或子项目。
其他用户可以共享
项目(.dsp)文件，但他们应该导出makefile本地。
## NeighborInfo.h
这是应用程序的主头文件。
它包括其他
项目特定的标头(包括Resource.h)并声明
CNeighborInfoApp应用程序类。
## NeighborInfo.cpp
这是包含应用程序的主应用程序源文件
类CNeighborInfoApp。
## NeighborInfo.rc
这是所有Microsoft Windows资源的列表程序使用。它包括存储的图标、位图和游标在RES子目录中。这个文件可以在微软直接编辑Visual c++。
## NeighborInfo.clw
此文件包含ClassWizard用于编辑现有信息的信息类或添加新类。ClassWizard也使用这个文件来存储创建和编辑消息映射和对话框数据所需的信息映射和创建原型成员函数。
## res \ NeighborInfo.ico
这是一个图标文件，用作应用程序的图标。这图标包含在主资源文件NeighborInfo.rc中。
## res \ NeighborInfo.rc2
此文件包含微软未编辑的资源Visual c++。您应该放置所有不可编辑的资源此文件中的资源编辑器。
## /////////////////////////////////////////////////////////////////////////////
## AppWizard创建一个对话类:
## NeighborInfoDlg.h, NeighborInfoDlg.cpp
-对话框这些文件包含您的CNeighborInfoDlg类。这个类定义应用程序的主对话框的行为。对话框的模板在NeighborInfo中。可以在微软编辑Visual c++。
## /////////////////////////////////////////////////////////////////////////////
# 其他标准文件:
# #StdAfx.h, StdAfx.cpp
这些文件用于构建预编译头文件(PCH)NeighborInfo命名。pch和一个名为StdAfx.obj的预编译类型文件。
## Resource.h
这是标准头文件，定义了新的资源id。
Microsoft Visual c++读取并更新此文件。
## /////////////////////////////////////////////////////////////////////////////
