using E3DEditor.Common;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace E3DEditor.Model
{
    public class FileRecord : ItemNodeBase
    {
        protected ImageSource _icon;
        [PropertyField(PropType = PropertyType.HideInProperty)]
        public ImageSource FileIcon
        {
            get { return _icon; }
            set
            {
                _icon = value;
                IconLoaded = true;
            }
        }
        public System.Drawing.Bitmap bitmMap;
        public bool IconLoaded = false;
        public int FileID { get; set; }

        [PropertyField(PropType = PropertyType.HideInProperty)]
        public string FileName { get; set; }

        public FileRecord()
        {
            _icon = new BitmapImage(new Uri(CONST_STRING.DefaultIcon, UriKind.Relative));
        }

        private ObservableCollection<NodeBase> _subList = new ObservableCollection<NodeBase>();
        public ObservableCollection<NodeBase> SubRecords
        {
            get
            {
                return _subList;
            }
            set
            {
                _subList = value;
            }
        }
    }

    public class DirectoryRecord
    {
        public DirectoryInfo Info { get; set; }

        public IEnumerable<FileInfo> Files
        {
            get
            {
                return Info.GetFiles();
            }
        }

        public IEnumerable<DirectoryRecord> Directories
        {
            get
            {
                return from di in Info.GetDirectories("*", SearchOption.TopDirectoryOnly)
                       select new DirectoryRecord { Info = di };
            }
        }
    }

}
