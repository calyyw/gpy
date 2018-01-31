// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LACORELIB_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// extern "C" LACORELIB_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LACORELIB_EXPORTS
#define LACORELIB_API __declspec(dllexport)
#else
#define LACORELIB_API __declspec(dllimport)
#endif


#ifndef _LACORELIB_H
#define _LACORELIB_H

//水印参数信息结构体
typedef struct _WATERMARKPARAM {
	char szText[300];       //文字水印的字符串
	char szFont[100];        //字体名称
	int size;                //字体大小
	BYTE r;                  //字体颜色红色分量
	BYTE g;                  //字体颜色绿色分量
	BYTE b;                  //字体颜色蓝色分量
	BYTE opcity;             //透明度
	int angle;               //文字旋转角度
	char imagepath[MAX_PATH];                               //图片文件全路径, 在水印类型为图片时有效
	int mode;                //文字水印的显示方式, 0---绝对坐标, 1---固定位置
	int pos;                 //固定位置值, 0---左上角, 1---右上角, 2---右下角, 3---左下角, 4---中间
	int left;                //绝对坐标的左上角X坐标
	int top;                 //绝对坐标的左上角Y坐标
	int right;               //绝对坐标的右下角X坐标
	int bottom;              //绝对坐标的右下角Y坐标
} WatermarkParam;





//初始化
extern "C" LACORELIB_API int LaInit(void);

//反初始化
extern "C" LACORELIB_API int LaUninit();

//获取摄像头个数
extern "C" LACORELIB_API int LaGetCameraCount();

//获取摄像头名称
extern "C" LACORELIB_API LPCSTR LaGetDevName(int iDev);

//打开摄像头, iDev摄像头索引, hWnd要显示视频的窗口句柄
extern "C" LACORELIB_API int LaOpenCamera(int iDev, HWND hWnd);

//关闭指定索引摄像头
extern "C" LACORELIB_API int LaCloseCamera(int iDev);

//响应鼠标左键按下
extern "C" LACORELIB_API int LaOnLMousePress(HWND hWnd, int x, int y);

//响应鼠标左键弹起
extern "C" LACORELIB_API int LaOnLMouseRelease(HWND hWnd, int x, int y);

//响应鼠标右键按下
extern "C" LACORELIB_API int LaOnRMousePress(HWND hWnd, int x, int y);


//响应鼠标移动
extern "C" LACORELIB_API int LaOnMouseMoving(HWND hWnd, int x, int y);

//响应鼠标滚轮
extern "C" LACORELIB_API int LaOnWheel(HWND hWnd, int zDelta);

//开启自动纠偏
extern "C" LACORELIB_API int LaEnableAutoRotate(int iDev, bool bEnable);

//拍照
extern "C" LACORELIB_API int LaCapture(int iDev, LPCSTR szFilePath);

//左转90度
extern "C" LACORELIB_API void LaRotateLeft(int iDev);

//右转90度
extern "C" LACORELIB_API void LaRotateRight(int iDev);

//视频属性
extern "C" LACORELIB_API void LaShowVideoProperty(int iDev);


//识别条码
extern "C" LACORELIB_API LPCSTR LaReadBarcode(int iDev);

//获取分辨率个数
extern "C" LACORELIB_API int LaGetResCount(int iDev);

//获取指定分辨率的宽度
extern "C" LACORELIB_API int LaGetResWidth(int iDev, int iRes);

//获取指定分辨率的高度
extern "C" LACORELIB_API int LaGetResHeight(int iDev, int iRes);

//设定分辨率
extern "C" LACORELIB_API int LaSetResolution(int iDev, int iRes);

//设置默认分辨率, 在打开视频或开始录像之前设置
extern "C" LACORELIB_API int LaSetDefaultResolution(int iDev, int iRes);

//设置颜色: 0--彩色, 1--灰度, 2--黑白
extern "C" LACORELIB_API int LaSetDevColor(int iDev, int iClrIndex);

//设置欢迎语
extern "C" LACORELIB_API int LaSetWelcome(int iDev, LPCSTR str);

//设置鼠标模式, 0--拖动图像, 1--画框
extern "C" LACORELIB_API int LaSetMouseMode(int iDev, int iMode);

//设置摄像头是否可见
extern "C" LACORELIB_API int LaSetVisible(int iDev, bool bVisible);

//设置JPG文件质量, 即压缩比, iQual为1-100之间的值, 
//包含1和100, 值越大图像质量越好, 但文件会相对偏大, 值越小质量越差, 文件越小
//默认值为80
extern "C" LACORELIB_API void LaSetJpgQuality(int iDev, int iQual);


//启动或关闭自动连拍
extern "C" LACORELIB_API void LaSetAutoCap(int iDev, bool bAutoCap);


//设置自动连拍的回调函数
extern "C" LACORELIB_API void LaSetAutoCapCB(int iDev, LPVOID pAutoCap);

//开始录像
extern "C" LACORELIB_API int LaStartRecord(int iDev, LPCSTR szFilePath, bool bAudio);

//暂停录像
extern "C" LACORELIB_API int LaPauseRecord(int iDev);

//(暂停后)重新启动录像
extern "C" LACORELIB_API int LaReStartRecord(int iDev);

//停止录像
extern "C" LACORELIB_API void LaStopRecord(int iDev);

//启动或关闭人脸检测功能
extern "C" LACORELIB_API void LaSetFaceDetect(int iDev, bool bEnable);

//启动画中画摄像头, iDev--画中画摄像头索引, iHost--主画面摄像头索引, 
//主画面必须处于打开状态
extern "C" LACORELIB_API void LaOpenSubCamera(int iDev, int iHost);

//关闭画中画
extern "C" LACORELIB_API void LaCloseSubCamera(int iDev);

//设置画中画的位置, 参数为画中画设备索引和左上角及右下角坐标比例系数
extern "C" LACORELIB_API void LaSetSubCameraPos(int iDev, float fLeft, float fTop, float fRight, float fBottom);

//获取视频流
extern "C" LACORELIB_API BYTE* LaGetBuffer(int iDev, int& w, int& h);

//获取录制音频设备个数
extern "C" LACORELIB_API int LaGetAudioCount();

//获取指定索引音频设备名称
extern "C" LACORELIB_API LPCSTR LaGetAudioName(int iDev);

//设置当前音频设备
extern "C" LACORELIB_API void LaSetAudioDev(int iDev);

//启动录音
extern "C" LACORELIB_API int LaStartSoundRecord(int iDev, LPCSTR szFileName);

//暂停录音
extern "C" LACORELIB_API int LaPauseSoundRecord(int iDev);

//(暂停后)重新启动录音
extern "C" LACORELIB_API int LaReStartSoundRecord(int iDev);

//停止录音
extern "C" LACORELIB_API int LaStopSoundRecord(int iDev);

//设置DPI
extern "C" LACORELIB_API int LaSetDPI(int iDev, int nDPI);

//图片合成, szImagePath---多个图片的全路径以英文分号间隔, iMode--合成模式为0时行优先col有效, 
//为1时列优先row有效, row--行数, col--列数, nGap--间隙
extern "C" LACORELIB_API int LaImagesMix(LPCSTR szImagePath, int iMode, int row, int col, int nGap, LPCSTR szSavePath);

//设置阈值模式, 0--自动计算阈值, 1--固定阈值
extern "C" LACORELIB_API int LaSetThresMode(int iDev, int iMode);

//设置固定阈值的值
extern "C" LACORELIB_API int LaSetThresVal(int iDev, int iThresh);

//设置旋转角度, 0--0度, 1--90度, 2--180度, 3--270度
extern "C" LACORELIB_API int LaSetRotate(int iDev, int index);

//获取自定义尺寸个数
extern "C" LACORELIB_API int LaGetScanSizeCount(int iDev);

//添加自定义的扫描尺寸
//  name：设定一个名称
//  left：左边的比率
//  top：上边的比率
//  right：右边的比率
//  bottom：下边的比率
extern "C" LACORELIB_API bool LaAddCustomScanSize(int iDev, LPCSTR name, float left, float top, float right, float bottom);

//获取扫描尺寸名称, index指定的图片尺寸对应的索引值
extern "C" LACORELIB_API LPCSTR LaGetScanSizeName(int iDev, int index);

//将扫描时生成的图片尺寸设置为指定值, index指定的图片尺寸对应的索引值
extern "C" LACORELIB_API bool LaSetScanSize(int iDev, int index);

//设置是否去底色
extern "C" LACORELIB_API void LaDelBackColor(int iDev, bool bDel);

//重置视频画面, 用于视频缩放及位移后的还原
extern "C" LACORELIB_API void LaResetVideo(int iDev);

//设置水平镜像
extern "C" LACORELIB_API void LaSetHFlip(int iDev, bool bEnable);

//设置垂直镜像
extern "C" LACORELIB_API void LaSetVFlip(int iDev, bool bEnable);

//获取矩形框坐标
extern "C" LACORELIB_API RECT LaGetRect(int iDev);


//读取二代身份证信息, 在调用下面获取二代证信息之前必须先调用此函数
extern "C" LACORELIB_API bool LaReadIDCard();

//获取二代证中的姓名
extern "C" LACORELIB_API LPCSTR LaGetIDName();

//获取二代证中的民族
extern "C" LACORELIB_API LPCSTR LaGetIDNation();

//获取二代证中的性别
extern "C" LACORELIB_API LPCSTR LaGetIDSex();

//获取二代证中的出生年份
extern "C" LACORELIB_API LPCSTR LaGetIDBirthYear();

//获取二代证中的出生月
extern "C" LACORELIB_API LPCSTR LaGetIDBirthMonth();

//获取二代证中的出生日
extern "C" LACORELIB_API LPCSTR LaGetIDBirthDay();

//获取二代证中的出生年月日
extern "C" LACORELIB_API LPCSTR LaGetIDBirthFull();

//获取二代证的号码
extern "C" LACORELIB_API LPCSTR LaGetIDNum();

//获取二代证中的住址信息
extern "C" LACORELIB_API LPCSTR LaGetIDAddress();

//获取二代证中的签发机关
extern "C" LACORELIB_API LPCSTR LaGetIDDepart();

//获取二代证中的有效期限
extern "C" LACORELIB_API LPCSTR LaGetIDTermDay();

//获取二代证头像图片文件路径
extern "C" LACORELIB_API LPCSTR LaGetIDHeadImagePath();

//获取二代证头像图片文件Base64文件流
extern "C" LACORELIB_API LPCSTR LaGetIDHeadImageBase64();

//重组二代证信息生成图片, 并返回图片路径
extern "C" LACORELIB_API LPCSTR LaMakeIDCard();

//重组二代证信息生成图片, 并返回图片Base64编码流
extern "C" LACORELIB_API LPCSTR LaMakeIDCardBase64();

//根据PID和VID获取摄像头索引
extern "C" LACORELIB_API int LaGetCameraIndex(LPCSTR szPID, LPCSTR szVID);

//根据索引获取摄像的PID
extern "C" LACORELIB_API LPCSTR LaGetCameraPID(int iDev);

//根据索引获取摄像头的VID
extern "C" LACORELIB_API LPCSTR LaGetCameraVID(int iDev);

//设置拍照模式, 0---正常拍照, 1---合成拍照
extern "C" LACORELIB_API void LaSetCaptureMode(int iDev, int iMode);

//拍照到Http服务器
extern "C" LACORELIB_API LPCSTR LaCapture2HttpServer(int iDev, LPCSTR szUrl);

//上传文件到Http服务器, 要求必须连接光阵高拍仪
extern "C" LACORELIB_API LPCSTR LaUpload2HttpServer(LPCSTR szFilePath, LPCSTR szUrl);

//拍照到FTP服务器
extern "C" LACORELIB_API bool LaCapture2FTPServer(int iDev, LPCSTR szFTPServer, LPCSTR szUser, LPCSTR szPwd, int nPort);

//上传文件到FTP服务器, 要求必须连接光阵高拍仪
extern "C" LACORELIB_API bool LaUpload2FTPServer(LPCSTR szFilePath, LPCSTR szFTPServer, LPCSTR szUser, LPCSTR szPwd, int nPort);

//添加水印, iType---水印类型, 0--自动日期水印, 1--自动编号水印, 2--文字水印, 3--图片水印, 4--二维码
extern "C" LACORELIB_API int LaAddWaterMark(int iDev, int iType, WatermarkParam* pWatermarkParam);

//返回水印个数
extern "C" LACORELIB_API int LaGetWatermarkCount(int iDev);

//获取水印信息
extern "C" LACORELIB_API WatermarkParam* LaGetWatermarkInfo(int iDev, int idx);

//设置水印信息, idx---水印索引, iType---水印类型
extern "C" LACORELIB_API void LaSetWatermark(int iDev, int idx, WatermarkParam* pWatermarkParam);

//删除指定索引水印
extern "C" LACORELIB_API int LaDeleteWatermarkItem(int iDev, int index);

//清除所有水印
extern "C" LACORELIB_API int LaClearWatermark(int iDev);

//复印当前图像
extern "C" LACORELIB_API int LaPrint(int iDev);

//拍照返回Base64码流
extern "C" LACORELIB_API LPCSTR LaCaptureBase64(int iDev);

//设置视频出图回调函数
extern "C" LACORELIB_API void LaSetArrivalCB(int iDev, void* pArrival);

//设置欢迎画面背景颜色
extern "C" LACORELIB_API void LaSetWelcomeBK(int iDev, BYTE r, BYTE g, BYTE b);

//设置制式(颜色空间) 0---YUY2, 1---MJPG
extern "C" LACORELIB_API void LaSetColorSpace(int iDev, int idx);

//获取麦克风索引, 如果不存在则返回-1
extern "C" LACORELIB_API int LaGetAudioIndex(LPCSTR szAudioName);

//放大图像
extern "C" LACORELIB_API void LaZoomIn(int iDev);

//缩小图像
extern "C" LACORELIB_API void LaZoomOut(int iDev);

//获取最小缩放比率
extern "C" LACORELIB_API float LaGetMinZoomRatio(int iDev);

//获取最大缩放比率
extern "C" LACORELIB_API float LaGetMaxZoomRatio(int iDev);

//按设定缩放比例进行缩放
extern "C" LACORELIB_API void LaZoom(int iDev, float fRate);

//设置缩放比率更新回调函数
extern "C" LACORELIB_API void LaSetZoomCB(int iDev, void* pZoomUpdate);

//获取缩放比率
extern "C" LACORELIB_API float LaGetZoomRate(int iDev);

//设置是否显示缩放百分比
extern "C" LACORELIB_API void LaSetShowZoomRate(int iDev, bool bShow);


//设置曝光度, iDev--摄像头索引, bAuto--是否自动曝光, nVal--手动曝光值
extern "C" LACORELIB_API void LaSetExposure(int iDev, bool bAuto, int nVal);


//设置曝光度
extern "C" LACORELIB_API void LaSetExposure(int iDev, bool bAuto, int nVal);


//获取曝光度相关信息
extern "C" LACORELIB_API void LaGetExposure(int iDev, bool& bAuto, int& nMax, int& nMin, int& nVal);


//刷新视频显示
extern "C" LACORELIB_API void LaUpdateVideo(int iDev);

//硬件触碰拍照
extern "C" LACORELIB_API void LaStillCapture(int iDev, LPCSTR szFilePath);

//身份证自动扶正开关
extern "C" LACORELIB_API void LaEnableIDCardCorrect(int iDev, bool bEnable);

//A4自动扶正模式, 0--不扶正, 1--向左旋转, 2--向右旋转
extern "C" LACORELIB_API void LaSetA4CorrectMode(int iDev, int iMode);

//显示子画面, iDev--摄像头索引, x-子画面左上角X坐标, y--子画面左上角Y坐标, w--子画面宽度, h--子画面高度
extern "C" LACORELIB_API bool LaDisplaySubImage(int iDev, int x, int y, int w, int h);

//取消Mask功能
extern "C" LACORELIB_API void LaDisableMask(int iDev);

//设置并激活Mask数据
extern "C" LACORELIB_API void LaSetupMask(int iDev, int x, int y, int w, int h);

//采集指定大小的图像数据
extern "C" LACORELIB_API BOOL LaGrabImage(int iDev, unsigned char *pBuffer, int w, int h);

//合成主副画面
extern "C" LACORELIB_API int LaCombineMainSub(LPCSTR szMain, LPCSTR szSub, LPCSTR szSave);

//设置拍照生成PDF的模式, 0--多页图片一个PDF文件, 1--一页图片一个PDF文件, 默认为0
extern "C" LACORELIB_API int LaSetPDFMode(int iDev, int iMode);

//为实达定制图像缩放功能
extern "C" LACORELIB_API void LaResample(LPCSTR szFilePath);

//获取鼠标模式
extern "C" LACORELIB_API int LaGetMouseMode(int iDev);

//设置子画面显示窗口句柄
extern "C" LACORELIB_API void LaSetSubHwnd(int iDev, HWND hWnd);

//对图像进行缩放
extern "C" LACORELIB_API void LaResampleImage(LPCSTR szFilePath, int w, int h);

//设置实达北控三兴导出宽度和高度
extern "C" LACORELIB_API void LaSetExportWH(int iDev, int w, int h);

//设置是否显示蒙板
extern "C" LACORELIB_API void LaShowMask(int iDev, bool bShow);


//设置去底色模式, iMode：0--不去底色, 1--去蓝色, 2--去红色, 3--去绿色
extern "C" LACORELIB_API void LaSetDelBackMode(int iDev, int iMode);

//开启/关闭照片翻拍模式
extern "C" LACORELIB_API void LaSetPhotoReCap(int iDev, bool bEnable);
#endif