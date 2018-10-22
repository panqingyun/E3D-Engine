using System;
using System.Collections.Generic;
using System.Text;
using System.Runtime.InteropServices;
using FreeImageAPI;
using System.Drawing.Imaging;
using System.Drawing;

namespace E3DEditor.Common
{
    public unsafe class FreeImageToBitmap
    {

        [StructLayout(LayoutKind.Sequential)]
        private struct RGBQUAD
        {
            internal byte Blue;
            internal byte Green;
            internal byte Red;
            internal byte Reserved;
        }

        public static Bitmap LoadImageFormFreeImage(string FileName)
        {
            Bitmap Bmp = null;
            FREE_IMAGE_FORMAT fif = FREE_IMAGE_FORMAT.FIF_UNKNOWN; ;
            if (FreeImage.IsAvailable() == true )
            {
                fif = FreeImage.GetFileType(FileName, 0);
                if (fif == FREE_IMAGE_FORMAT.FIF_UNKNOWN)
                {
                    fif =FreeImage.GetFIFFromFilename (FileName);
                }

                if ((fif != FREE_IMAGE_FORMAT.FIF_UNKNOWN) && (FreeImage.FIFSupportsReading(fif) != false))
                {
                    FIBITMAP Dib = FreeImage.Load(fif, FileName, FREE_IMAGE_LOAD_FLAGS.DEFAULT);
                    uint Bpp = FreeImage.GetBPP(Dib);
                    PixelFormat PF;
                    uint Width, Height, Stride;
                    switch (Bpp)
                    {
                        case 1:
                            PF = PixelFormat.Format1bppIndexed; break;
                        case 4:
                            PF = PixelFormat.Format4bppIndexed; break;
                        case 8:
                            PF = PixelFormat.Format8bppIndexed; break;
                        case 16:
                            PF = PixelFormat.Format16bppRgb555; break;
                        case 24:
                            PF = PixelFormat.Format24bppRgb; break;
                        case 32:
                            PF = PixelFormat.Format32bppArgb; break;
                        default:
                            FreeImage.Unload(Dib);
                            return null;
                    }
                    Width = FreeImage.GetWidth(Dib);                        //  图像宽度
                    Height = FreeImage.GetHeight(Dib);                      //  图像高度
                    Stride = FreeImage.GetPitch(Dib);                       //  图像扫描行的大小,必然是4的整数倍

                    IntPtr Bits = FreeImage.GetBits(Dib);
                    Bmp = new Bitmap((int)Width, (int)Height, (int)Stride, PF, Bits);
                    Bmp.RotateFlip(RotateFlipType.RotateNoneFlipY);         // 调用GDI+自己的旋转函数
                    

                    if (Bpp <= 8)
                    {
                        ColorPalette Pal = Bmp.Palette;                     //  设置调色板
                        RGBQUAD* GdiPal = (RGBQUAD*)FreeImage.GetPalette(Dib);
                        int ClrUsed = FreeImage.GetUniqueColors(Dib);
                        for (int I = 0; I < ClrUsed; I++)
                        {
                            Pal.Entries[I] = Color.FromArgb(255, GdiPal[I].Red, GdiPal[I].Green, GdiPal[I].Blue);
                        }
                        Bmp.Palette = Pal;
                    }
                    FreeImage.Unload(Dib);          // 使用方案2则可以立马释放
                    return Bmp;
                }
            }
            return null;
        }
    }
}

