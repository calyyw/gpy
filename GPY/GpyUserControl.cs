using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.IO.MemoryMappedFiles;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Security;
using System.Drawing.Imaging;
using residence_permit_control.me.common;
//using residence_permit_lib.me.pos;

namespace residence_permit_control
{
    [Guid("EBD7BA00-1025-4BC2-BDD0-85ED5794EA0E")]
    [SecuritySafeCritical]

    public partial class GpyUserControl : UserControl, IObjectSafety
    {
        public GpyUserControl()
        {
            InitializeComponent();
            GpySdImpl.LaInit();
            LocalPath = Environment.GetFolderPath(Environment.SpecialFolder.MyPictures);
        }

        #region IObjectSafety 成员

        private const string _IID_IDispatch = "{00020400-0000-0000-C000-000000000046}";
        private const string _IID_IDispatchEx = "{a6ef9860-c720-11d0-9337-00a0c90dcaa9}";
        private const string _IID_IPersistStorage = "{0000010A-0000-0000-C000-000000000046}";
        private const string _IID_IPersistStream = "{00000109-0000-0000-C000-000000000046}";
        private const string _IID_IPersistPropertyBag = "{37D84F60-42CB-11CE-8135-00AA004BB851}";

        private const int INTERFACESAFE_FOR_UNTRUSTED_CALLER = 0x00000001;
        private const int INTERFACESAFE_FOR_UNTRUSTED_DATA = 0x00000002;
        private const int S_OK = 0;
        private const int E_FAIL = unchecked((int)0x80004005);
        private const int E_NOINTERFACE = unchecked((int)0x80004002);

        private bool _fSafeForScripting = true;
        private bool _fSafeForInitializing = true;

        public int GetInterfaceSafetyOptions(ref Guid riid, ref int pdwSupportedOptions, ref int pdwEnabledOptions)
        {
            int Rslt = E_FAIL;
            string strGUID = riid.ToString("B");
            pdwSupportedOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER | INTERFACESAFE_FOR_UNTRUSTED_DATA;
            switch (strGUID)
            {
                case _IID_IDispatch:
                case _IID_IDispatchEx:
                    Rslt = S_OK;
                    pdwEnabledOptions = 0;
                    if (_fSafeForScripting == true)
                        pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_CALLER;
                    break;
                case _IID_IPersistStorage:
                case _IID_IPersistStream:
                case _IID_IPersistPropertyBag:
                    Rslt = S_OK;
                    pdwEnabledOptions = 0;
                    if (_fSafeForInitializing == true)
                        pdwEnabledOptions = INTERFACESAFE_FOR_UNTRUSTED_DATA;
                    break;
                default:
                    Rslt = E_NOINTERFACE;
                    break;
            }
            return Rslt;
        }

        public int SetInterfaceSafetyOptions(ref Guid riid, int dwOptionSetMask, int dwEnabledOptions)
        {
            int Rslt = E_FAIL;
            string strGUID = riid.ToString("B");
            switch (strGUID)
            {
                case _IID_IDispatch:
                case _IID_IDispatchEx:
                    if (((dwEnabledOptions & dwOptionSetMask) == INTERFACESAFE_FOR_UNTRUSTED_CALLER) && (_fSafeForScripting == true))
                        Rslt = S_OK;
                    break;
                case _IID_IPersistStorage:
                case _IID_IPersistStream:
                case _IID_IPersistPropertyBag:
                    if (((dwEnabledOptions & dwOptionSetMask) == INTERFACESAFE_FOR_UNTRUSTED_DATA) && (_fSafeForInitializing == true))
                        Rslt = S_OK;
                    break;
                default:
                    Rslt = E_NOINTERFACE;
                    break;
            }
            return Rslt;
        }

        #endregion

        private String LocalPath;
        private int mainIndex = 0;                  //主头索引
        private int subIndex = 0;                   //副头索引
        private bool bOpenMain = false;             //主头是否已打开
        private bool bOpenSub = false;              //副头是否已打开


        /// <summary>
        /// 获取摄像头数量
        /// </summary>
        /// <returns></returns>
        public int btnGetCameraCount_Click(String pDeviceID)
        {
            if (!"01".Equals(pDeviceID))
            {
                return -1;
            }
            int num = GpySdImpl.LaGetCameraCount();
            return num;
        }

        /// <summary>
        /// 打开主摄像头
        /// </summary>    
        public void btnOpenMain_Click(String pDeviceID)
        {

            mainIndex = GpySdImpl.LaGetCameraIndex("1bc3", "1100");
            if (GpySdImpl.LaOpenCamera(mainIndex, pictureBox1.Handle) == 0)
            {
                bOpenMain = true;
            }            
        }

        /// <summary>
        /// 关闭主摄像头
        /// </summary>
        public void btnCloseMain_Click()
        {
            if (bOpenMain)
            {
                GpySdImpl.LaCloseCamera(mainIndex);
                bOpenMain = false;
            }
        }

        /// <summary>
        /// 主摄像头拍照
        /// </summary>
        /// <param name="file"></param>        
        public void btnCaptureMain_Click(String file)
        {
            if (bOpenMain)
            {
                file = LocalPath + "\\" + file;
                //如果没有目录，则创建目录
                String dir = Path.GetDirectoryName(file);
                if (!Directory.Exists(dir))
                {
                    Directory.CreateDirectory(dir);
                }
                //GpySdImpl.LaSetJpgQuality(mainIndex, 50);
                GpySdImpl.LaSetDPI(mainIndex, 350);
                GpySdImpl.LaCapture(mainIndex, file);
                //GpySdImpl.AddImageItem(file);//显示
            }
        }

        /// <summary>
        /// 主摄像头拍照返回Base64位
        /// </summary>
        /// <param name="file">路径</param>
        /// <returns></returns>
        public String btnCaptureMainBase64_Click(String file)
        {
            if (bOpenMain)
            {
                file = LocalPath + "\\" + file;
                //如果没有目录，则创建目录
                String dir = Path.GetDirectoryName(file);
                if (!Directory.Exists(dir))
                {
                    Directory.CreateDirectory(dir);
                }

                //SD.LaSetJpgQuality(mainIndex, 50);
                GpySdImpl.LaSetDPI(mainIndex, 350);

                //Im.Dispose();
                //Bm.Dispose();
                //File.Delete(file);

                //String base64= SD.LaCaptureBase64(mainIndex);

                if (File.Exists(file))
                {
                    File.Delete(file);
                }

                //String file = ("C:\\bcd.jpg");

                GpySdImpl.LaCapture(mainIndex, file);

                //int i = file.LastIndexOf(".");
                //string extension = file.Substring(i + 1);

                //Image Im = Image.FromFile(file);

                ////Bitmap Bm = new Bitmap(file);
                //Bitmap Bm = new Bitmap(Im);

                //MemoryStream m = new MemoryStream();


                ////Image img = this.pictureBox.Image;
                //BinaryFormatter binFormatter = new BinaryFormatter();
                //MemoryStream memStream = new MemoryStream();
                //binFormatter.Serialize(m, Im);
                ////byte[] bytes = memStream.GetBuffer();
                ////string base64 = Convert.ToBase64String(bytes);

                //if (extension == "tif")
                //{
                //    //Bm.Save(m, ImageFormat.Tiff);
                //    Im.Save(m, ImageFormat.Tiff);

                //    Bm.Save("C:\\bcd.jpg", ImageFormat.Tiff);

                //}
                //else if (extension == "jpg")
                //{
                //    //Bm.Save(m, ImageFormat.Jpeg);
                //    Im.Save(m, ImageFormat.Jpeg);

                //    Bm.Save("C:\\bcd.jpg", ImageFormat.Jpeg);
                //}


                //String base64 = SD.LaCaptureBase64(mainIndex);

                //String base64 = Convert.ToBase64String(m.GetBuffer());
                //String base64 = Convert.ToBase64String(m.ToArray());

                //byte[] bytes = null;
                //using (FileStream fs = new FileStream(file, FileMode.Open, FileAccess.Read))
                //{
                //    using (BinaryReader br = new BinaryReader(fs))
                //    {
                //        bytes = br.ReadBytes((int)fs.Length);
                //    }
                //}
                //String base64 = Convert.ToBase64String(bytes);


                //String base64 = SD.LaConvert2Base64(file);

                String base64 = btnConvertBase64_Click(file);

                //SD.AddImageItem(file);//显示

                //Im.Dispose();
                //Bm.Dispose();

                return base64;
            }
            else
                return null;
        }

        /// <summary>
        /// 图片转Base64位
        /// </summary>
        /// <param name="file"></param>
        /// <returns></returns>
        private String btnConvertBase64_Click(String file)
        {
            byte[] bytes = null;
            using (FileStream fs = new FileStream(file, FileMode.Open, FileAccess.Read))
            {
                using (BinaryReader br = new BinaryReader(fs))
                {
                    bytes = br.ReadBytes((int)fs.Length);
                }
            }

            String base64 = Convert.ToBase64String(bytes);

            //String base64 = SD.LaConvert2Base64(file);

            return base64;
        }


        /// <summary>
        /// 左转
        /// </summary>        
        public void btnRotateLeftMain_Click()
        {
            if (bOpenMain)
            {
                GpySdImpl.LaRotateLeft(mainIndex);
            }
        }

        /// <summary>
        /// 右转
        /// </summary>       
        public void btnRotateRightMain_Click()
        {
            if (bOpenMain)
            {
                GpySdImpl.LaRotateRight(mainIndex);
            }
        }

        /// <summary>
        /// 设置颜色：0--彩色, 1--灰度, 2--黑白 
        /// </summary>
        /// <param name="iClrIndex"></param>
        public void btnSetDevColor_Click(int iClrIndex)
        {
            GpySdImpl.LaSetDevColor(mainIndex, iClrIndex);
        }

        /// <summary>
        /// 设置主摄像头压缩比
        /// </summary>
        /// <param name="iQual"></param>
        public void btnSetJpgQualityMain_Click(int iQual)
        {
            GpySdImpl.LaSetJpgQuality(mainIndex, iQual);
        }

        /// <summary>
        /// 设置副摄像头压缩比
        /// </summary>
        /// <param name="iQual"></param>
        public void btnSetJpgQualitySub_Click(int iQual)
        {
            GpySdImpl.LaSetJpgQuality(subIndex, iQual);
        }

        /// <summary>
        /// 设置默认分辨率
        /// </summary>
        /// <param name="iRes"></param>
        public void btnSetDefaultResolution_Click(int iRes)
        {
            GpySdImpl.LaSetDefaultResolution(mainIndex, iRes);
        }

        /// <summary>
        /// 设置分辨率
        /// </summary>
        /// <param name="iRes"></param>
        public void btnSetResolution_Click(int iRes)
        {
            GpySdImpl.LaSetResolution(mainIndex, iRes);
        }

        /// <summary>
        /// 主摄像头合成拍照
        /// </summary>
        /// <param name="file"></param>
        public void btnComposeMain_Click(String file)
        {

            if (bOpenMain)
            {
                file = LocalPath + "\\" + file;
                //如果没有目录，则创建目录
                String dir = Path.GetDirectoryName(file);
                if (!Directory.Exists(dir))
                {
                    Directory.CreateDirectory(dir);
                }

                GpySdImpl.LaSetCaptureMode(mainIndex, 1);                       //设置拍照模式为合成拍照模式
                GpySdImpl.LaEnableAutoRotate(mainIndex, true);                  //开启自动纠偏
                //GpySdImpl.LaSetJpgQuality(mainIndex, 50);                       //设置压缩比, 第二个参数取值1-100
                GpySdImpl.LaSetDPI(mainIndex, 350);
                GpySdImpl.LaCapture(mainIndex, file);
                //GpySdImpl.AddImageItem(file);//显示
                GpySdImpl.LaSetCaptureMode(mainIndex, 0);                       //设置拍照模式为正常拍照
                GpySdImpl.LaEnableAutoRotate(mainIndex, false);                 //关闭自动纠偏
            }

        }

        //主摄像头合成拍照返回base64位
        public String btnComposeMainBase64_Click(String file)
        {
            if (bOpenMain)
            {
                file = LocalPath + "\\" + file;
                //如果没有目录，则创建目录
                String dir = Path.GetDirectoryName(file);
                if (!Directory.Exists(dir))
                {
                    Directory.CreateDirectory(dir);
                }

                GpySdImpl.LaSetCaptureMode(mainIndex, 1);                       //设置拍照模式为合成拍照模式
                GpySdImpl.LaEnableAutoRotate(mainIndex, true);                  //开启自动纠偏
                //SD.LaSetJpgQuality(mainIndex, 50);                       //设置压缩比, 第二个参数取值1-100
                GpySdImpl.LaSetDPI(mainIndex, 350);

                if (File.Exists(file))
                {
                    File.Delete(file);
                }

                //String file = ("C:\\cde.jpg");
                GpySdImpl.LaCapture(mainIndex, file);


                //Image Im = Image.FromFile(file);
                //Bitmap Bm = new Bitmap(Im);

                //MemoryStream m = new MemoryStream();
                //Bm.Save(m, ImageFormat.Jpeg);
                ////String base64 = Convert.ToBase64String(m.GetBuffer());
                ////String base64 = Convert.ToBase64String(m.ToArray());
                //Im.Dispose();
                //Bm.Dispose();


                //String base64 = SD.LaCaptureBase64(mainIndex);                
                //SD.AddImageItem(file);//显示
                GpySdImpl.LaSetCaptureMode(mainIndex, 0);                       //设置拍照模式为正常拍照
                GpySdImpl.LaEnableAutoRotate(mainIndex, false);                 //关闭自动纠偏

                String base64 = btnConvertBase64_Click(file);

                return base64;

            }
            else
                return null;

        }

        /// <summary>
        /// 副摄像头打开
        /// </summary>        
        public void btnOpenSub_Click(String pDeviceID)
        {
            subIndex = GpySdImpl.LaGetCameraIndex("1bc3", "1101");
            if (GpySdImpl.LaOpenCamera(subIndex, pictureBox1.Handle) == 0)
            {
                bOpenSub = true;
                GpySdImpl.LaShowMask(subIndex, true);
                GpySdImpl.LaSetMouseMode(subIndex, 3);
            }
        }


        /// <summary>
        /// 副摄像头关闭
        /// </summary>
        public void btnCloseSub_Click()
        {
            if (bOpenSub)
            {
                GpySdImpl.LaCloseCamera(subIndex);
            }
        }

        /// <summary>
        /// 开关自动去背景，默认打开为true，关闭为false
        /// </summary>
        /// <param name="bEnable"></param>
        public void btnEnableDelBack_Click(bool bEnable)
        {
            GpySdImpl.LaEnableDelBack(subIndex, bEnable);
        }

        /// <summary>
        /// 副摄像头拍照
        /// </summary>
        /// <param name="file"></param>
        public void btnCaptureSub_Click(String file)
        {
            if (bOpenSub)
            {
                file = LocalPath + "\\" + file;
                //如果没有目录，则创建目录
                String dir = Path.GetDirectoryName(file);
                if (!Directory.Exists(dir))
                {
                    Directory.CreateDirectory(dir);
                }

                //GpySdImpl.LaSetJpgQuality(subIndex, 50);
                GpySdImpl.LaSetDPI(subIndex, 350);
                GpySdImpl.LaCapture(subIndex, file);
                //GpySdImpl.AddImageItem(file);//显示
            }
        }

        /// <summary>
        /// 副摄像头拍照,返回base64
        /// </summary>
        /// <returns></returns>
        public String btnCaptureSubBase64_Click(String file)
        {
            if (bOpenSub)
            {
                file = LocalPath + "\\" + file;
                //SD.LaSetJpgQuality(subIndex, 50);
                GpySdImpl.LaSetDPI(subIndex, 350);

                if (File.Exists(file))
                {
                    File.Delete(file);
                }
                //String file = ("c:\\abc.jpg");

                //如果没有目录，则创建目录
                String dir = Path.GetDirectoryName(file);
                if (!Directory.Exists(dir))
                {
                    Directory.CreateDirectory(dir);
                }

                GpySdImpl.LaCapture(subIndex, file);

                //Image Im = Image.FromFile(file);
                //Bitmap Bm = new Bitmap(Im);
                //MemoryStream m = new MemoryStream();
                //Bm.Save(m, ImageFormat.Jpeg);
                ////String base64 = Convert.ToBase64String(m.GetBuffer());
                //String base64 = Convert.ToBase64String(m.ToArray());
                //Im.Dispose();
                //Bm.Dispose();

                //File.Delete(file);
                //SD.AddImageItem(file);//显示

                //Write(base64, "d:\\人图像base64数据.txt");

                String base64 = btnConvertBase64_Click(file);

                return base64;
            }
            else
                return null;
        }

        /// <summary>
        /// 低光
        /// </summary>
        public void btnLowLight_Click()
        {
            if (bOpenSub)
            {
                GpySdImpl.LaSetExposure(subIndex, false, -4);
            }
        }

        /// <summary>
        /// 高光
        /// </summary>
        public void btnHightLight_Click()
        {
            if (bOpenSub)
            {
                GpySdImpl.LaSetExposure(subIndex, false, -2);
            }
        }

        /// <summary>
        /// 自动
        /// </summary>
        public void btnAuto_Click()
        {
            if (bOpenSub)
            {
                GpySdImpl.LaSetExposure(subIndex, true, -2);
            }
        }

        /// <summary>
        /// 按下鼠标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            GpySdImpl.LaOnLMousePress(pictureBox1.Handle, e.X, e.Y);
        }

        /// <summary>
        /// 移动鼠标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>   
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            GpySdImpl.LaOnMouseMoving(pictureBox1.Handle, e.X, e.Y);
        }


        /// <summary>
        /// 抬起鼠标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            GpySdImpl.LaOnLMouseRelease(pictureBox1.Handle, e.X, e.Y);
        }

        /// <summary>
        /// 滑动鼠标
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pictureBox1_MouseWheel(object sender, MouseEventArgs e)
        {
            GpySdImpl.LaOnWheel(pictureBox1.Handle, e.Delta);
        }


        /// <summary>
        /// 开启翻拍照片功能
        /// </summary>
        /// <param name="iMode">0不去底色，1去蓝色，2去红色，3去绿色，4去白底</param>
        public void btnOpenPhotoRecopy(int iMode)
        {
            GpySdImpl.LaSetMouseMode(mainIndex, 1);
            GpySdImpl.LaSetDelBackMode(mainIndex, iMode);
            GpySdImpl.LaSetPhotoReCap(mainIndex, true);
        }

        /// <summary>
        /// 关闭翻拍照片功能
        /// </summary>
        /// <param name="iMode"></param>
        public void btnClosePhotoRecopy(int iMode)
        {
            GpySdImpl.LaSetPhotoReCap(mainIndex, false);
            GpySdImpl.LaSetDelBackMode(mainIndex, 0);
            GpySdImpl.LaSetMouseMode(mainIndex, 0);
        }

        /// <summary>
        /// 得到版本号
        /// </summary>
        /// <returns></returns>
        public String GetVersion()
        {
            return Config.Version;
        }

    }
}
