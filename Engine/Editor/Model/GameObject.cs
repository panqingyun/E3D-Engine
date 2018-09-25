using E3DEditor.Common;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using E3DEngine;
using System.Collections.ObjectModel;

namespace E3DEditor.Model
{
    public class GameObjectNode : ItemNodeBase
    {

        [PropertyField(PropType = PropertyType.NormalText, DisplayIndex = 2)]
        public Vector3 Position
        {
            get;set;
        }

        [PropertyField(PropType = PropertyType.NormalText, DisplayIndex = 3)]
        public Vector3 Rotation
        {
            get; set;
        }

        [PropertyField(PropType = PropertyType.NormalText, DisplayIndex = 4)]
        public Vector3 Scale
        {
            get; set;
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
