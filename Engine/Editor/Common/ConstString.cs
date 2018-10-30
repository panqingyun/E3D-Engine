using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace E3DEditor.Common
{
    /// <summary>
    /// 常量字符串定义
    /// </summary>
    public class CONST_STRING
    {
        public const string Name = "Name";
        public const string ID = "ID";
        public const string Type = "Type";
        public const string Config_dialogAtlasFilePath = "dialogAtlasPath";
        public const string Config_resourceFilePath = "resourceFilePath";
        public const string Config_gameWidht = "width";
        public const string Config_renderSystemType = "RenderSystem";
        public const string TAB = "\t";
        public const string Mp3Icon = "/Resources/Pic/Icon/g11.ico";
        public const string EffectIcon = "/Resources/Pic/Icon/g4.ico";
        public const string DictionaryIcon = "/Resources/Pic/Icon/g8.ico";
        public const string TxtIcon = "/Resources/Pic/Icon/g13.ico";
        public const string DefaultIcon = "/Resources/Pic/Icon/g7.ico";
        public const string SoundIcon = "/Resources/Pic/Icon/g11.ico";
        public const string PlistIcon = "/Resources/Pic/Icon/g15.ico";
        public const string ImageIcon = "/Resources/Pic/Icon/g14.ico";
        public const string PlayIcon = "/Resources/Pic/Player Play.ico";
        public const string PauseIcon = "/Resources/Pic/Player Pause.ico";
        public const string SceneIcon = "/Resources/Window.ico";
        public const string WarningIcon = "/Resources/Pic/Symbols Warning.ico";
        public const string ErrorIcon = "/Resources/Pic/Symbols Error.ico";
        public const string InfoIcon = "/Resources/Pic/Symbols Tips.ico";
        public const string DefaultBackImagPath = "/Pic/";

        public static string GetTitleText(Type type, string propertyName)
        {
            string desc = App.Instance[propertyName];
            return desc;
        }
    }

}
