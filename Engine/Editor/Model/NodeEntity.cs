using E3DEditor.Common;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace E3DEditor.Model
{
    public delegate void PathChangeDelegate(object sender, string path);
    [Serializable]
    public class NodeBase : INode, INotifyPropertyChanged
    {
        public UIElement UIElement;

        public NodeBase()
        {
            
        }

        private int _id;
        public int ID
        {
            get { return _id; }
            set
            {
                _id = value;
                OnPropertyChanged(CONST_STRING.ID);
            }
        }


        private string _name;
        [PropertyField(PropType = PropertyType.NormalText, DisplayIndex = 0)]
        public string Name
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
                OnPropertyChanged(CONST_STRING.Name);
            }
        }

        #region INotifyPropertyChanged Members

        public event PropertyChangedEventHandler PropertyChanged;

        public virtual void ChangeSelect()
        {
            
        }

        public virtual object[] GetCustomAttributies(string name)
        {
            return null;
        }

        protected void OnPropertyChanged(string name)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(name));
        }

        #endregion
    }

    public class ItemNodeBase : NodeBase
    {
        public PathChangeDelegate ImagePathChange;
        public string TableName;

        [PropertyField(PropType = PropertyType.HideInProperty)]
        public string FileFullName
        {
            get; set;
        }

        private string _showText;
        [PropertyField(PropType = PropertyType.HideInProperty)]
        public string ShowText
        {
            get
            {
                return _showText;
            }
            set
            {
                _showText = value;
                OnPropertyChanged("ShowText");
            }
        }

        private string _dragText = "";
        [PropertyField(PropType = PropertyType.File, DisplayIndex = 20)]
        public string DragText
        {
            get
            {
                return _dragText;
            }
            set
            {
                _dragText = value;
                OnPropertyChanged("DragText");
            }
        }

        protected ImageSource _icon;
        [PropertyField(PropType = PropertyType.HideInProperty)]
        public ImageSource FileIcon
        {
            get { return _icon; }
            set
            {
                _icon = value;
            }
        }

    }

    public class FileRecord : ItemNodeBase
    {
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
