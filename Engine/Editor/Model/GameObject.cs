using E3DEditor.Common;
using E3DEngine;
using System.Collections.ObjectModel;
using System;
using System.Collections.Generic;

namespace E3DEditor.Model
{
    public class GameObjectNode : ItemNodeBase
    {
        public int SceneInnerID = 0;
        int iupdateTimes = 0;
        int iupdateNeedNumber = 60;

        private bool isSelect = false;
        public bool IsSelected
        {
            get { return isSelect; }
            set
            {
                isSelect = value;
                OnPropertyChanged("IsSelected");
            }
        }        

        private GameObjectRef gameObject;
        public GameObjectRef mGameObject
        {
            set
            {
                gameObject = value;
                value.TransformChangeHandle = objectTransChange;
                value.GameObjectSelected = objectSelected;
            }
            get
            {
                return gameObject;
            }
        }

        private void objectSelected(object sender, EventArgs e)
        {
            IsSelected = true;
            App.vm_MainWindow.SelectObject(this);
        }

        private void objectTransChange(object sender, EventArgs e)
        {
            if (IsSelected)
            {
                if (App.vm_MainWindow.IsRun)
                {
                    iupdateTimes++;
                    if (iupdateTimes < iupdateNeedNumber)
                    {
                        return;
                    }
                    iupdateTimes = 0;
                }
                OnPropertyChanged("Position");
                OnPropertyChanged("Rotation");
                OnPropertyChanged("Scale");
            }
        }

        public void RefreshComponent()
        {
            OnPropertyChanged("Component");
        }

        [PropertyField(PropType = PropertyType.Boolean, DisplayIndex = 1)]
        public bool Active
        {
            get
            {
                return mGameObject.GetActive();
            }
            set
            {
                mGameObject.SetActive(value);
            }
        }

        [PropertyField(PropType = PropertyType.Vector3, DisplayIndex = 2)]
        public Vector3 Position
        {
            get
            {
                return mGameObject.GetTransform().Position;
            }
            set
            {
                mGameObject.GetTransform().Position = value;
            }
        }
        
        [PropertyField(PropType = PropertyType.Vector3, DisplayIndex = 3)]
        public Vector3 Rotation
        {
            get
            {
                return mGameObject.GetTransform().Rotation;
            }
            set
            {
                mGameObject.GetTransform().Rotation = value;
            }
        }

        [PropertyField(PropType = PropertyType.Vector3, DisplayIndex = 4)]
        public Vector3 Scale
        {
            get
            {
                return mGameObject.GetTransform().Scale;
            }
            set
            {
                mGameObject.GetTransform().Scale = value;
            }
        }

        [PropertyField(PropType = PropertyType.Color4, DisplayIndex = 5)]
        public Vector4 Color
        {
            get
            {
                return mGameObject.GetColor();
            }
            set
            {
                mGameObject.SetColor(value);
            }
        }

        [PropertyField(PropType = PropertyType.ComponentList, DisplayIndex = 6)]
        public List<ComponentRef> Component
        {
            get
            {
                return mGameObject.GetComponents();
            }
        }

        private ObservableCollection<GameObjectNode> _subList = new ObservableCollection<GameObjectNode>();
        public ObservableCollection<GameObjectNode> Childs
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
}
