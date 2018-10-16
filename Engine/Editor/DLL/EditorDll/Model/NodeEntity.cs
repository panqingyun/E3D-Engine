using E3DEditor.Common;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.IO;
using System.Linq;

namespace E3DEditor.Model
{
    public delegate void PathChangeDelegate(object sender, string path);
    [Serializable]
    public class NodeBase : INode, INotifyPropertyChanged
    {
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
                OnPropertyChanged("ID");
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
                OnPropertyChanged("Name");
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
        [PropertyField(PropType = PropertyType.HideInProperty, DisplayIndex = 20)]
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
    }
}
