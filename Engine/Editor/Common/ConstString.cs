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
        public const string Config_mutiThreadRender = "MutiThreadRender";
        public const string TAB = "\t";
        public const string Mp3Icon = "/Resources/Pic/Icon/g11.ico";
        public const string EffectIcon = "/Resources/Pic/Icon/particle.ico";
        public const string FrefabIcon = "/Resources/Pic/Icon/prefab.ico";
        public const string ShaderIcon = "/Resources/Pic/Icon/shader.ico";
        public const string MaterialIcon = "/Resources/Pic/Icon/material.ico";
        public const string TxtIcon = "/Resources/Pic/Icon/tex.ico";
        public const string DefaultIcon = "/Resources/Pic/Icon/default.ico";
        public const string ImageIcon = "/Resources/Pic/Icon/g14.ico";
        public const string PlayIcon = "/Resources/Pic/Player Play.ico";
        public const string PauseIcon = "/Resources/Pic/Player Pause.ico";
        public const string SceneIcon = "/Resources/Window.ico";
        public const string CSharpIcon = "/Resources/Pic/Icon/csharp.ico";
        public const string WarningIcon = "/Resources/Pic/Symbols Warning.ico";
        public const string ErrorIcon = "/Resources/Pic/Symbols Error.ico";
        public const string InfoIcon = "/Resources/Pic/Symbols Tips.ico";
        public const string ModelIcon = "/Resources/Pic/Icon/model.ico";
        public const string DefaultBackImagPath = "/Pic/";

        public static string GetTitleText(Type type, string propertyName)
        {
            string desc = App.Instance[propertyName];
            return desc;
        }
    }

}
