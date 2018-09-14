using E3DEditor.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace E3DEditor.Common
{
    public class AtlasFrame : ItemNodeBase
    {
        public Int32Rect frame;
        public bool rotated;
        public string frameName;

        [PropertyField(PropType = PropertyType.ImageSource, DisplayIndex = 5)]
        public ImageSource imageSource
        {
            get
            {
                return FileIcon;
            }
            set
            {
                FileIcon = value;
            }
        }

        public AtlasFrame(string _frame,bool _rotated, string _frameName)
        {
            frame = parseIntRect(_frame);
            rotated = _rotated;
            frameName = _frameName;
        }

        private Size parseSize(string _size)
        {
            Size size = new Size();
            _size = _size.Replace("{", "").Replace("}", "");
            string[] sz = _size.Split(',');
            if (sz.Length < 2)
            {
                return size;
            }
            size.Width = Convert.ToInt32(sz[0]);
            size.Height = Convert.ToInt32(sz[1]);
            return size;
        }

        private Point parsePoint(string _point)
        {
            Point point = new Point();
            _point = _point.Replace("{", "").Replace("}", "");
            string[] pi = _point.Split(',');
            if (pi.Length < 2)
            {
                return point;
            }
            point.X = Convert.ToInt32(pi[0]);
            point.Y = Convert.ToInt32(pi[1]);
            return point;
        }

        private Int32Rect parseIntRect(string _frame)
        {
            Int32Rect rect = new Int32Rect();
            _frame = _frame.Replace("{", "").Replace("}", "");
            string[] fr = _frame.Split(',');
            if (fr.Length < 4)
            {
                return rect;
            }
            rect.X = Convert.ToInt32(fr[0]);
            rect.Y = Convert.ToInt32(fr[1]);
            rect.Width = Convert.ToInt32(fr[2]);
            rect.Height = Convert.ToInt32(fr[3]);
            return rect;
        }

        private Rect parseRect(string _frame)
        {
            Rect rect = new Rect();
            _frame = _frame.Replace("{", "").Replace("}", "");
            string[] fr = _frame.Split(',');
            if (fr.Length < 4)
            {
                return rect;
            }
            rect.X = Convert.ToInt32(fr[0]);
            rect.Y = Convert.ToInt32(fr[1]);
            rect.Width = Convert.ToInt32(fr[2]);
            rect.Height = Convert.ToInt32(fr[3]);
            return rect;
        }


    }

    public class AtlasTools
    {
        private Dictionary<string, Dictionary<string, AtlasFrame>> allAtlasMap = new Dictionary<string, Dictionary<string, AtlasFrame>>();
        private Dictionary<string, BitmapFrame> atlasFrameMap = new Dictionary<string, BitmapFrame>();

        private const string str_png = ".png/";
        private const string str_frames = "frame";
        private const string str_textureRect = "textureRect";
        private const string str_rotated = "rotated";
        private const string str_textureRotated = "textureRotated";

        private static AtlasTools _ins = new AtlasTools();
        public static AtlasTools Instance
        {
            get
            {
                return _ins;
            }
        }
        
        public Dictionary<string, AtlasFrame> GetAtlasFrameList(string atlasFullName, bool bRefresh = false)
        {
            if (!bRefresh)
            {
                if (allAtlasMap.ContainsKey(atlasFullName))
                {
                    return allAtlasMap[atlasFullName];
                }
            }
            else if (allAtlasMap.ContainsKey(atlasFullName))
            {
                allAtlasMap.Remove(atlasFullName);
            }

            PList plist = new PList();
            plist.Load(atlasFullName);

            Dictionary<string, AtlasFrame> atlases = new Dictionary<string, AtlasFrame>();

            Dictionary<string, object> frames = plist["frames"] as Dictionary<string, object>;

            string realTextureFileName = plist.GetValue<string>("metadata/realTextureFileName");
            string path = System.IO.Path.GetDirectoryName(atlasFullName);
            foreach (KeyValuePair<string, object> kv in frames)
            {
                string frameName;
                AtlasFrame _atlas = createAtlas(realTextureFileName, path, kv, out frameName);
                atlases.Add(frameName, _atlas);
            }
            allAtlasMap.Add(atlasFullName, atlases);
            return atlases;
        }

        private AtlasFrame createAtlas(string realTextureFileName, string path, KeyValuePair<string, object> kv,
            out string frameName)
        {
            string key = kv.Key;
            Dictionary<string, object> valueMap = kv.Value as Dictionary<string, object>;

            string frameRect = "";
            bool bRotated = false;
            if (valueMap.ContainsKey(str_frames))
            {
                frameRect = valueMap[str_frames].ToString();
                bRotated = (bool)valueMap[str_rotated];
            }
            else if (valueMap.ContainsKey(str_textureRect))
            {
                frameRect = valueMap[str_textureRect].ToString();
                bRotated = (bool)valueMap[str_textureRotated];
            }
            
            BitmapFrame bitmapFrame = null;
            if (atlasFrameMap.ContainsKey(realTextureFileName))
            {
                bitmapFrame = atlasFrameMap[realTextureFileName];
            }
            else
            {
                bitmapFrame = BitmapFrame.Create(new Uri(path + "/" + realTextureFileName, UriKind.Absolute));
                atlasFrameMap[realTextureFileName] = bitmapFrame;
            }
            int pointPos = key.LastIndexOf('.');
            frameName = key;
            if (pointPos != -1)
            {
                frameName = key.Substring(0, pointPos);
            }
            AtlasFrame _atlas = new AtlasFrame(frameRect, bRotated, frameName);
            BitmapSource imgSource = null;
            if (bRotated)
            {
                _atlas.frame.Width = _atlas.frame.Width ^ _atlas.frame.Height;
                _atlas.frame.Height = _atlas.frame.Height ^ _atlas.frame.Width;
                _atlas.frame.Width = _atlas.frame.Width ^ _atlas.frame.Height;
                TransformedBitmap tb = new TransformedBitmap();
                tb.BeginInit();
                imgSource = new CroppedBitmap(bitmapFrame, _atlas.frame);
                tb.Source = imgSource;
                RotateTransform transform = new RotateTransform(-90);
                tb.Transform = transform;
                tb.EndInit();
                _atlas.imageSource = tb;
            }
            else
            {
                _atlas.imageSource = new CroppedBitmap(bitmapFrame, _atlas.frame);
            }
            return _atlas;
        }

        /// <summary>
        /// 获取图集信息
        /// </summary>
        /// <param name="fullReName">图集目录，在resources中的相对目录</param>
        /// <param name="frameName"></param>
        /// <returns></returns>
        public AtlasFrame GetAtlas(string fullReName, string frameName)
        {
            Dictionary<string, AtlasFrame> atlases = GetAtlasFrameList(Config.GameResourcePath + "/" + fullReName);

            if (atlases.ContainsKey(frameName))
            {
                return atlases[frameName];
            }

            return null;
        }
    }
}
