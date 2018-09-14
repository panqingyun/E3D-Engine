using System.IO;
using System.Windows.Forms;

namespace E3DEditor
{
    public class IOFile
    {
        public static string OpenFile()
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.Filter = "json文件(*.json)|*.json|所有文件|*.*";
            ofd.ValidateNames = true;
            ofd.CheckPathExists = true;
            ofd.CheckFileExists = true;
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                return ofd.FileName;
            }
            return "";
        }

        public static bool SaveFile(string fileName,string fileContent)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.Filter = "json文件(*.json)|*.json|所有文件|*.*";
            sfd.ValidateNames = true;
            sfd.CheckFileExists = false;
            sfd.FileName = fileName;
            if (sfd.ShowDialog() == DialogResult.OK)
            {
                File.WriteAllText(sfd.FileName, fileContent);
                return true;
            }
            return false;
        }

        public static string OpenFolder()
        {
            FolderBrowserDialog m_Dialog = new FolderBrowserDialog();
            DialogResult result = m_Dialog.ShowDialog();

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
