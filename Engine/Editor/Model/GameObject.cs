using E3DEditor.Common;
using E3DEngine;
using System.Collections.ObjectModel;

namespace E3DEditor.Model
{
    public class GameObjectNode : ItemNodeBase
    {
        public GameObjectRef mGameObject;

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
