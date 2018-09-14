using System;
using System.Collections.Generic;
using System.Reflection;

namespace E3DEditor.Common
{
    public sealed class PropertyFieldAttribute : Attribute
    {
        private PropertyType _mPropType;
        public PropertyType PropType
        {
            get
            {
                return _mPropType;
            }
            set
            {
                _mPropType = value;
            }
        }

        private int _mIndex = 0;
        public int DisplayIndex
        {
            get
            {
                return _mIndex;
            }
            set
            {
                _mIndex = value;
            }
        }

        private object _param = "";
        public object Param
        {
            get { return _param; }
            set { _param = value; }
        }

        private Type _enumType;
        public Type EnumType
        {
            get { return _enumType; }
            set { _enumType = value; }
        }
    }

}
