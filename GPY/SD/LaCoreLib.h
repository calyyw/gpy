// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LACORELIB_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// extern "C" LACORELIB_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LACORELIB_EXPORTS
#define LACORELIB_API __declspec(dllexport)
#else
#define LACORELIB_API __declspec(dllimport)
#endif


#ifndef _LACORELIB_H
#define _LACORELIB_H

//ˮӡ������Ϣ�ṹ��
typedef struct _WATERMARKPARAM {
	char szText[300];       //����ˮӡ���ַ���
	char szFont[100];        //��������
	int size;                //�����С
	BYTE r;                  //������ɫ��ɫ����
	BYTE g;                  //������ɫ��ɫ����
	BYTE b;                  //������ɫ��ɫ����
	BYTE opcity;             //͸����
	int angle;               //������ת�Ƕ�
	char imagepath[MAX_PATH];                               //ͼƬ�ļ�ȫ·��, ��ˮӡ����ΪͼƬʱ��Ч
	int mode;                //����ˮӡ����ʾ��ʽ, 0---��������, 1---�̶�λ��
	int pos;                 //�̶�λ��ֵ, 0---���Ͻ�, 1---���Ͻ�, 2---���½�, 3---���½�, 4---�м�
	int left;                //������������Ͻ�X����
	int top;                 //������������Ͻ�Y����
	int right;               //������������½�X����
	int bottom;              //������������½�Y����
} WatermarkParam;





//��ʼ��
extern "C" LACORELIB_API int LaInit(void);

//����ʼ��
extern "C" LACORELIB_API int LaUninit();

//��ȡ����ͷ����
extern "C" LACORELIB_API int LaGetCameraCount();

//��ȡ����ͷ����
extern "C" LACORELIB_API LPCSTR LaGetDevName(int iDev);

//������ͷ, iDev����ͷ����, hWndҪ��ʾ��Ƶ�Ĵ��ھ��
extern "C" LACORELIB_API int LaOpenCamera(int iDev, HWND hWnd);

//�ر�ָ����������ͷ
extern "C" LACORELIB_API int LaCloseCamera(int iDev);

//��Ӧ����������
extern "C" LACORELIB_API int LaOnLMousePress(HWND hWnd, int x, int y);

//��Ӧ����������
extern "C" LACORELIB_API int LaOnLMouseRelease(HWND hWnd, int x, int y);

//��Ӧ����Ҽ�����
extern "C" LACORELIB_API int LaOnRMousePress(HWND hWnd, int x, int y);


//��Ӧ����ƶ�
extern "C" LACORELIB_API int LaOnMouseMoving(HWND hWnd, int x, int y);

//��Ӧ������
extern "C" LACORELIB_API int LaOnWheel(HWND hWnd, int zDelta);

//�����Զ���ƫ
extern "C" LACORELIB_API int LaEnableAutoRotate(int iDev, bool bEnable);

//����
extern "C" LACORELIB_API int LaCapture(int iDev, LPCSTR szFilePath);

//��ת90��
extern "C" LACORELIB_API void LaRotateLeft(int iDev);

//��ת90��
extern "C" LACORELIB_API void LaRotateRight(int iDev);

//��Ƶ����
extern "C" LACORELIB_API void LaShowVideoProperty(int iDev);


//ʶ������
extern "C" LACORELIB_API LPCSTR LaReadBarcode(int iDev);

//��ȡ�ֱ��ʸ���
extern "C" LACORELIB_API int LaGetResCount(int iDev);

//��ȡָ���ֱ��ʵĿ��
extern "C" LACORELIB_API int LaGetResWidth(int iDev, int iRes);

//��ȡָ���ֱ��ʵĸ߶�
extern "C" LACORELIB_API int LaGetResHeight(int iDev, int iRes);

//�趨�ֱ���
extern "C" LACORELIB_API int LaSetResolution(int iDev, int iRes);

//����Ĭ�Ϸֱ���, �ڴ���Ƶ��ʼ¼��֮ǰ����
extern "C" LACORELIB_API int LaSetDefaultResolution(int iDev, int iRes);

//������ɫ: 0--��ɫ, 1--�Ҷ�, 2--�ڰ�
extern "C" LACORELIB_API int LaSetDevColor(int iDev, int iClrIndex);

//���û�ӭ��
extern "C" LACORELIB_API int LaSetWelcome(int iDev, LPCSTR str);

//�������ģʽ, 0--�϶�ͼ��, 1--����
extern "C" LACORELIB_API int LaSetMouseMode(int iDev, int iMode);

//��������ͷ�Ƿ�ɼ�
extern "C" LACORELIB_API int LaSetVisible(int iDev, bool bVisible);

//����JPG�ļ�����, ��ѹ����, iQualΪ1-100֮���ֵ, 
//����1��100, ֵԽ��ͼ������Խ��, ���ļ������ƫ��, ֵԽС����Խ��, �ļ�ԽС
//Ĭ��ֵΪ80
extern "C" LACORELIB_API void LaSetJpgQuality(int iDev, int iQual);


//������ر��Զ�����
extern "C" LACORELIB_API void LaSetAutoCap(int iDev, bool bAutoCap);


//�����Զ����ĵĻص�����
extern "C" LACORELIB_API void LaSetAutoCapCB(int iDev, LPVOID pAutoCap);

//��ʼ¼��
extern "C" LACORELIB_API int LaStartRecord(int iDev, LPCSTR szFilePath, bool bAudio);

//��ͣ¼��
extern "C" LACORELIB_API int LaPauseRecord(int iDev);

//(��ͣ��)��������¼��
extern "C" LACORELIB_API int LaReStartRecord(int iDev);

//ֹͣ¼��
extern "C" LACORELIB_API void LaStopRecord(int iDev);

//������ر�������⹦��
extern "C" LACORELIB_API void LaSetFaceDetect(int iDev, bool bEnable);

//�������л�����ͷ, iDev--���л�����ͷ����, iHost--����������ͷ����, 
//��������봦�ڴ�״̬
extern "C" LACORELIB_API void LaOpenSubCamera(int iDev, int iHost);

//�رջ��л�
extern "C" LACORELIB_API void LaCloseSubCamera(int iDev);

//���û��л���λ��, ����Ϊ���л��豸���������ϽǼ����½��������ϵ��
extern "C" LACORELIB_API void LaSetSubCameraPos(int iDev, float fLeft, float fTop, float fRight, float fBottom);

//��ȡ��Ƶ��
extern "C" LACORELIB_API BYTE* LaGetBuffer(int iDev, int& w, int& h);

//��ȡ¼����Ƶ�豸����
extern "C" LACORELIB_API int LaGetAudioCount();

//��ȡָ��������Ƶ�豸����
extern "C" LACORELIB_API LPCSTR LaGetAudioName(int iDev);

//���õ�ǰ��Ƶ�豸
extern "C" LACORELIB_API void LaSetAudioDev(int iDev);

//����¼��
extern "C" LACORELIB_API int LaStartSoundRecord(int iDev, LPCSTR szFileName);

//��ͣ¼��
extern "C" LACORELIB_API int LaPauseSoundRecord(int iDev);

//(��ͣ��)��������¼��
extern "C" LACORELIB_API int LaReStartSoundRecord(int iDev);

//ֹͣ¼��
extern "C" LACORELIB_API int LaStopSoundRecord(int iDev);

//����DPI
extern "C" LACORELIB_API int LaSetDPI(int iDev, int nDPI);

//ͼƬ�ϳ�, szImagePath---���ͼƬ��ȫ·����Ӣ�ķֺż��, iMode--�ϳ�ģʽΪ0ʱ������col��Ч, 
//Ϊ1ʱ������row��Ч, row--����, col--����, nGap--��϶
extern "C" LACORELIB_API int LaImagesMix(LPCSTR szImagePath, int iMode, int row, int col, int nGap, LPCSTR szSavePath);

//������ֵģʽ, 0--�Զ�������ֵ, 1--�̶���ֵ
extern "C" LACORELIB_API int LaSetThresMode(int iDev, int iMode);

//���ù̶���ֵ��ֵ
extern "C" LACORELIB_API int LaSetThresVal(int iDev, int iThresh);

//������ת�Ƕ�, 0--0��, 1--90��, 2--180��, 3--270��
extern "C" LACORELIB_API int LaSetRotate(int iDev, int index);

//��ȡ�Զ���ߴ����
extern "C" LACORELIB_API int LaGetScanSizeCount(int iDev);

//����Զ����ɨ��ߴ�
//  name���趨һ������
//  left����ߵı���
//  top���ϱߵı���
//  right���ұߵı���
//  bottom���±ߵı���
extern "C" LACORELIB_API bool LaAddCustomScanSize(int iDev, LPCSTR name, float left, float top, float right, float bottom);

//��ȡɨ��ߴ�����, indexָ����ͼƬ�ߴ��Ӧ������ֵ
extern "C" LACORELIB_API LPCSTR LaGetScanSizeName(int iDev, int index);

//��ɨ��ʱ���ɵ�ͼƬ�ߴ�����Ϊָ��ֵ, indexָ����ͼƬ�ߴ��Ӧ������ֵ
extern "C" LACORELIB_API bool LaSetScanSize(int iDev, int index);

//�����Ƿ�ȥ��ɫ
extern "C" LACORELIB_API void LaDelBackColor(int iDev, bool bDel);

//������Ƶ����, ������Ƶ���ż�λ�ƺ�Ļ�ԭ
extern "C" LACORELIB_API void LaResetVideo(int iDev);

//����ˮƽ����
extern "C" LACORELIB_API void LaSetHFlip(int iDev, bool bEnable);

//���ô�ֱ����
extern "C" LACORELIB_API void LaSetVFlip(int iDev, bool bEnable);

//��ȡ���ο�����
extern "C" LACORELIB_API RECT LaGetRect(int iDev);


//��ȡ�������֤��Ϣ, �ڵ��������ȡ����֤��Ϣ֮ǰ�����ȵ��ô˺���
extern "C" LACORELIB_API bool LaReadIDCard();

//��ȡ����֤�е�����
extern "C" LACORELIB_API LPCSTR LaGetIDName();

//��ȡ����֤�е�����
extern "C" LACORELIB_API LPCSTR LaGetIDNation();

//��ȡ����֤�е��Ա�
extern "C" LACORELIB_API LPCSTR LaGetIDSex();

//��ȡ����֤�еĳ������
extern "C" LACORELIB_API LPCSTR LaGetIDBirthYear();

//��ȡ����֤�еĳ�����
extern "C" LACORELIB_API LPCSTR LaGetIDBirthMonth();

//��ȡ����֤�еĳ�����
extern "C" LACORELIB_API LPCSTR LaGetIDBirthDay();

//��ȡ����֤�еĳ���������
extern "C" LACORELIB_API LPCSTR LaGetIDBirthFull();

//��ȡ����֤�ĺ���
extern "C" LACORELIB_API LPCSTR LaGetIDNum();

//��ȡ����֤�е�סַ��Ϣ
extern "C" LACORELIB_API LPCSTR LaGetIDAddress();

//��ȡ����֤�е�ǩ������
extern "C" LACORELIB_API LPCSTR LaGetIDDepart();

//��ȡ����֤�е���Ч����
extern "C" LACORELIB_API LPCSTR LaGetIDTermDay();

//��ȡ����֤ͷ��ͼƬ�ļ�·��
extern "C" LACORELIB_API LPCSTR LaGetIDHeadImagePath();

//��ȡ����֤ͷ��ͼƬ�ļ�Base64�ļ���
extern "C" LACORELIB_API LPCSTR LaGetIDHeadImageBase64();

//�������֤��Ϣ����ͼƬ, ������ͼƬ·��
extern "C" LACORELIB_API LPCSTR LaMakeIDCard();

//�������֤��Ϣ����ͼƬ, ������ͼƬBase64������
extern "C" LACORELIB_API LPCSTR LaMakeIDCardBase64();

//����PID��VID��ȡ����ͷ����
extern "C" LACORELIB_API int LaGetCameraIndex(LPCSTR szPID, LPCSTR szVID);

//����������ȡ�����PID
extern "C" LACORELIB_API LPCSTR LaGetCameraPID(int iDev);

//����������ȡ����ͷ��VID
extern "C" LACORELIB_API LPCSTR LaGetCameraVID(int iDev);

//��������ģʽ, 0---��������, 1---�ϳ�����
extern "C" LACORELIB_API void LaSetCaptureMode(int iDev, int iMode);

//���յ�Http������
extern "C" LACORELIB_API LPCSTR LaCapture2HttpServer(int iDev, LPCSTR szUrl);

//�ϴ��ļ���Http������, Ҫ��������ӹ��������
extern "C" LACORELIB_API LPCSTR LaUpload2HttpServer(LPCSTR szFilePath, LPCSTR szUrl);

//���յ�FTP������
extern "C" LACORELIB_API bool LaCapture2FTPServer(int iDev, LPCSTR szFTPServer, LPCSTR szUser, LPCSTR szPwd, int nPort);

//�ϴ��ļ���FTP������, Ҫ��������ӹ��������
extern "C" LACORELIB_API bool LaUpload2FTPServer(LPCSTR szFilePath, LPCSTR szFTPServer, LPCSTR szUser, LPCSTR szPwd, int nPort);

//���ˮӡ, iType---ˮӡ����, 0--�Զ�����ˮӡ, 1--�Զ����ˮӡ, 2--����ˮӡ, 3--ͼƬˮӡ, 4--��ά��
extern "C" LACORELIB_API int LaAddWaterMark(int iDev, int iType, WatermarkParam* pWatermarkParam);

//����ˮӡ����
extern "C" LACORELIB_API int LaGetWatermarkCount(int iDev);

//��ȡˮӡ��Ϣ
extern "C" LACORELIB_API WatermarkParam* LaGetWatermarkInfo(int iDev, int idx);

//����ˮӡ��Ϣ, idx---ˮӡ����, iType---ˮӡ����
extern "C" LACORELIB_API void LaSetWatermark(int iDev, int idx, WatermarkParam* pWatermarkParam);

//ɾ��ָ������ˮӡ
extern "C" LACORELIB_API int LaDeleteWatermarkItem(int iDev, int index);

//�������ˮӡ
extern "C" LACORELIB_API int LaClearWatermark(int iDev);

//��ӡ��ǰͼ��
extern "C" LACORELIB_API int LaPrint(int iDev);

//���շ���Base64����
extern "C" LACORELIB_API LPCSTR LaCaptureBase64(int iDev);

//������Ƶ��ͼ�ص�����
extern "C" LACORELIB_API void LaSetArrivalCB(int iDev, void* pArrival);

//���û�ӭ���汳����ɫ
extern "C" LACORELIB_API void LaSetWelcomeBK(int iDev, BYTE r, BYTE g, BYTE b);

//������ʽ(��ɫ�ռ�) 0---YUY2, 1---MJPG
extern "C" LACORELIB_API void LaSetColorSpace(int iDev, int idx);

//��ȡ��˷�����, ����������򷵻�-1
extern "C" LACORELIB_API int LaGetAudioIndex(LPCSTR szAudioName);

//�Ŵ�ͼ��
extern "C" LACORELIB_API void LaZoomIn(int iDev);

//��Сͼ��
extern "C" LACORELIB_API void LaZoomOut(int iDev);

//��ȡ��С���ű���
extern "C" LACORELIB_API float LaGetMinZoomRatio(int iDev);

//��ȡ������ű���
extern "C" LACORELIB_API float LaGetMaxZoomRatio(int iDev);

//���趨���ű�����������
extern "C" LACORELIB_API void LaZoom(int iDev, float fRate);

//�������ű��ʸ��»ص�����
extern "C" LACORELIB_API void LaSetZoomCB(int iDev, void* pZoomUpdate);

//��ȡ���ű���
extern "C" LACORELIB_API float LaGetZoomRate(int iDev);

//�����Ƿ���ʾ���Űٷֱ�
extern "C" LACORELIB_API void LaSetShowZoomRate(int iDev, bool bShow);


//�����ع��, iDev--����ͷ����, bAuto--�Ƿ��Զ��ع�, nVal--�ֶ��ع�ֵ
extern "C" LACORELIB_API void LaSetExposure(int iDev, bool bAuto, int nVal);


//�����ع��
extern "C" LACORELIB_API void LaSetExposure(int iDev, bool bAuto, int nVal);


//��ȡ�ع�������Ϣ
extern "C" LACORELIB_API void LaGetExposure(int iDev, bool& bAuto, int& nMax, int& nMin, int& nVal);


//ˢ����Ƶ��ʾ
extern "C" LACORELIB_API void LaUpdateVideo(int iDev);

//Ӳ����������
extern "C" LACORELIB_API void LaStillCapture(int iDev, LPCSTR szFilePath);

//���֤�Զ���������
extern "C" LACORELIB_API void LaEnableIDCardCorrect(int iDev, bool bEnable);

//A4�Զ�����ģʽ, 0--������, 1--������ת, 2--������ת
extern "C" LACORELIB_API void LaSetA4CorrectMode(int iDev, int iMode);

//��ʾ�ӻ���, iDev--����ͷ����, x-�ӻ������Ͻ�X����, y--�ӻ������Ͻ�Y����, w--�ӻ�����, h--�ӻ���߶�
extern "C" LACORELIB_API bool LaDisplaySubImage(int iDev, int x, int y, int w, int h);

//ȡ��Mask����
extern "C" LACORELIB_API void LaDisableMask(int iDev);

//���ò�����Mask����
extern "C" LACORELIB_API void LaSetupMask(int iDev, int x, int y, int w, int h);

//�ɼ�ָ����С��ͼ������
extern "C" LACORELIB_API BOOL LaGrabImage(int iDev, unsigned char *pBuffer, int w, int h);

//�ϳ���������
extern "C" LACORELIB_API int LaCombineMainSub(LPCSTR szMain, LPCSTR szSub, LPCSTR szSave);

//������������PDF��ģʽ, 0--��ҳͼƬһ��PDF�ļ�, 1--һҳͼƬһ��PDF�ļ�, Ĭ��Ϊ0
extern "C" LACORELIB_API int LaSetPDFMode(int iDev, int iMode);

//Ϊʵ�ﶨ��ͼ�����Ź���
extern "C" LACORELIB_API void LaResample(LPCSTR szFilePath);

//��ȡ���ģʽ
extern "C" LACORELIB_API int LaGetMouseMode(int iDev);

//�����ӻ�����ʾ���ھ��
extern "C" LACORELIB_API void LaSetSubHwnd(int iDev, HWND hWnd);

//��ͼ���������
extern "C" LACORELIB_API void LaResampleImage(LPCSTR szFilePath, int w, int h);

//����ʵ�ﱱ�����˵�����Ⱥ͸߶�
extern "C" LACORELIB_API void LaSetExportWH(int iDev, int w, int h);

//�����Ƿ���ʾ�ɰ�
extern "C" LACORELIB_API void LaShowMask(int iDev, bool bShow);


//����ȥ��ɫģʽ, iMode��0--��ȥ��ɫ, 1--ȥ��ɫ, 2--ȥ��ɫ, 3--ȥ��ɫ
extern "C" LACORELIB_API void LaSetDelBackMode(int iDev, int iMode);

//����/�ر���Ƭ����ģʽ
extern "C" LACORELIB_API void LaSetPhotoReCap(int iDev, bool bEnable);
#endif