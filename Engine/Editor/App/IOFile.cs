using Microsoft.Win32;
using System.IO;
namespace E3DEditor
{
    public class IOFile
    {
        public static string OpenSlnFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "esln文件(*.esln)|*.esln|所有文件|*.*";
            ofd.ValidateNames = true;
            ofd.CheckPathExists = true;
            ofd.CheckFileExists = true;
            if ((bool)ofd.ShowDialog())
            {
                return ofd.FileName;
            }
            return "";
        }

        public static string SaveScene(string sceneName)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "scene(*.scene)|*.scene|所有文件|*.*";
            sfd.ValidateNames = true;
            sfd.CheckFileExists = false;
            sfd.FileName = sceneName;
            string retFilePath = "";
            if ((bool)sfd.ShowDialog())
            {
                retFilePath = sfd.FileName;
            }
            return retFilePath;
        }

        public static bool SaveFile(string fileName,string fileContent)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "esln文件(*.esln)|*.esln|所有文件|*.*";
            sfd.ValidateNames = true;
            sfd.CheckFileExists = false;
            sfd.FileName = fileName;
            if ((bool)sfd.ShowDialog())
            {
                File.WriteAllText(sfd.FileName, fileContent);
                return true;
            }
            return false;
        }

        public static string OpenFolder()
        {
            System.Windows.Forms.FolderBrowserDialog m_Dialog = new System.Windows.Forms.FolderBrowserDialog();
            System.Windows.Forms.DialogResult result = m_Dialog.ShowDialog();

            if (result == System.Windows.Forms.DialogResult.Cancel)
            {
                return "";
            }
            return m_Dialog.SelectedPath.Trim();
        }
        
        public static void OpenInFolder(string fullPath)
        {
            if (File.Exists(fullPath))
            {
                System.Diagnostics.Process.Start("Explorer", "/select," + fullPath);
            }
        }
    }
}
