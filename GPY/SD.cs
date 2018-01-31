using System;
using System.Runtime.InteropServices;

namespace residence_permit_control
{
    public static class GpySdImpl
    {
        const string DLLPath1 = @"SD\LaCoreLib.dll";
        const string DLLPath2 = @"SD\LaThumbnail.dll"; 


        [DllImport(DLLPath1, EntryPoint = "LaInit", ExactSpelling = false, CallingConvention = CallingConvention.StdCall)]
        public static extern int LaInit();

        [DllImport(DLLPath1, EntryPoint = "LaUninit", ExactSpelling = false, CallingConvention = CallingConvention.StdCall)]
        public static extern int LaUninit();

        [DllImport(DLLPath1, EntryPoint = "LaGetCameraCount", ExactSpelling = false, CallingConvention = CallingConvention.StdCall)]
        public static extern int LaGetCameraCount();

        [DllImport(DLLPath1, EntryPoint = "LaOpenCamera", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaOpenCamera(int idx, IntPtr handle);

        [DllImport(DLLPath1, EntryPoint = "LaCloseCamera", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaCloseCamera(int idx);

        [DllImport(DLLPath1, EntryPoint = "LaCapture", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaCapture(int idx, string str);

        [DllImport(DLLPath1, EntryPoint = "LaStartRecord", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaStartRecord(int idx, string str, bool bAudio);

        [DllImport(DLLPath1, EntryPoint = "LaStopRecord", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaStopRecord(int idx);

        [DllImport(DLLPath1, EntryPoint = "LaStartSoundRecord", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaStartSoundRecord(int idx, string str);

        [DllImport(DLLPath1, EntryPoint = "LaStopSoundRecord", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaStopSoundRecord(int idx);

        [DllImport(DLLPath1, EntryPoint = "LaGetCameraIndex", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaGetCameraIndex(string sPID, string sVID);

        [DllImport(DLLPath1, EntryPoint = "LaRotateLeft", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaRotateLeft(int idx);

        [DllImport(DLLPath1, EntryPoint = "LaRotateRight", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaRotateRight(int idx);

        [DllImport(DLLPath1, EntryPoint = "LaShowMask", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaShowMask(int idx, bool bShow);

        [DllImport(DLLPath1, EntryPoint = "LaOnLMousePress", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaOnLMousePress(IntPtr handle, int x, int y);

        [DllImport(DLLPath1, EntryPoint = "LaOnLMouseRelease", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaOnLMouseRelease(IntPtr handle, int x, int y);

        [DllImport(DLLPath1, EntryPoint = "LaOnMouseMoving", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaOnMouseMoving(IntPtr handle, int x, int y);

        [DllImport(DLLPath1, EntryPoint = "LaOnWheel", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaOnWheel(IntPtr handle, int zDelta);

        [DllImport(DLLPath1, EntryPoint = "LaSetMouseMode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaSetMouseMode(int iDev, int iMode);

        [DllImport(DLLPath1, EntryPoint = "LaSetExposure", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaSetExposure(int iDev, bool bAuto, int nVal);

        [DllImport(DLLPath1, EntryPoint = "LaSetCaptureMode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaSetCaptureMode(int iDev, int iMode);

        [DllImport(DLLPath1, EntryPoint = "LaEnableAutoRotate", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaEnableAutoRotate(int iDev, bool bEnable);

        [DllImport(DLLPath1, EntryPoint = "LaSetJpgQuality", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaSetJpgQuality(int iDev, int iQual);

        [DllImport(DLLPath1, EntryPoint = "LaSetDPI", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaSetDPI(int iDev, int nDPI);

        [DllImport(DLLPath1, EntryPoint = "LaCaptureBase64", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public  static extern string LaCaptureBase64(int iDev);

        [DllImport(DLLPath1, EntryPoint = "LaSetDefaultResolution", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaSetDefaultResolution(int iDev, int iRes);

        [DllImport(DLLPath1, EntryPoint = "LaSetResolution", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaSetResolution(int iDev, int iRes);

        [DllImport(DLLPath1, EntryPoint = "LaSetDevColor", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaSetDevColor(int iDev, int iClrIndex);

        [DllImport(DLLPath1, EntryPoint = "LaEnableDelBack", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int LaEnableDelBack(int iDev, bool bEnable);

        [DllImport(DLLPath1, EntryPoint = "LaDelBackColor", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaDelBackColor(int iDev, bool bEnable);

        [DllImport(DLLPath1, EntryPoint = "LaSetDelBackMode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaSetDelBackMode(int iDev, int iMode);

        [DllImport(DLLPath1, EntryPoint = "LaSetPhotoReCap", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void LaSetPhotoReCap(int iDev, bool bEnable);

        [DllImport(DLLPath1, EntryPoint = "LaConvert2Base64", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern string LaConvert2Base64(string szFilePath);


        [DllImport(DLLPath2, EntryPoint = "AddImageItem", ExactSpelling = false, CallingConvention = CallingConvention.StdCall)]
        public static extern int AddImageItem(string szFilePath);

        [DllImport(DLLPath2, EntryPoint = "InitLib", ExactSpelling = false, CallingConvention = CallingConvention.StdCall)]
        public static extern int InitLib(IntPtr handle);
    }
}
