using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    public enum FileType
    {
        eUnKnown,
        eImage,
        eTga,
        eText,
        eScript,
        ePrefab,
        eScene,
        eAudio,
        eVideo,
    }
    
    public enum PropertyType
    {
        HideInProperty,
        NormalText,
        ReadOnlyText,
        Boolean,
        ReadOnlyBoolean,
        IntList,
        StringList,
        EnumType,
        File,
        ImageSource,
        ImagePath,
        Position,
        NumberText,
        Table,
        Vector3,
        ComponentList,
        Color4,
    }

    public enum LogLevel
    {
        Info,
        Error,
        Warning,
    }
  
    public class NumberParamEventArgs : EventArgs
    {
        public int InputNumber;
    }
}
