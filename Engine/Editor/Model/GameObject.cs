using E3DEditor.Common;
using E3DEngine;
using System.Collections.ObjectModel;
using System;

namespace E3DEditor.Model
{
    public class GameObjectNode : ItemNodeBase
    {
        public bool IsSelected = false;

        private GameObjectRef gameObject;
        public GameObjectRef mGameObject
        {
            set
            {
                gameObject = value;
                gameObject.TransformChangeHandle = objectTransChange;
            }
            get
            {
                return gameObject;
            }
        }

        private void objectTransChange(object sender, EventArgs e)
        {
            if (IsSelected)
            {
                Position = mGameObject.GetTransform().Position;
                Rotation = mGameObject.GetTransform().Rotation;
                Scale = mGameObject.GetTransform().Scale;
            }
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
                if (mGameObject.GetTransform().Position != value)
                {
                    mGameObject.GetTransform().Position = value;
                }
                OnPropertyChanged("Position");
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
                if (mGameObject.GetTransform().Rotation != value)
                {
                    mGameObject.GetTransform().Rotation = value;
                }
                OnPropertyChanged("Rotation");
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
                if (mGameObject.GetTransform().Scale != value)
                {
                    mGameObject.GetTransform().Scale = value;
                }
                OnPropertyChanged("Scale");
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
