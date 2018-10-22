using E3DEditor.Common;
using E3DEditor.Model;
using E3DEditor.View;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media.Imaging;

namespace E3DEditor.ViewModel
{
    enum symbolType
    {
        eNameSpace,
        eClassName,
        eLeft,
        eRight,
    }

    class nameSpaceTree
    {
        public string Name;
        public int leftNumber;
    }

    public class VM_FleView
    {
        public FileView _View
        {
            get;set;
        }

        private Dictionary<string, FileRecord> fileSources = new Dictionary<string, FileRecord>();

        private ObservableCollection<DirectoryRecord> directory = new ObservableCollection<DirectoryRecord>();
        public ObservableCollection<DirectoryRecord> Directory
        {
            get
            {
                return directory;
            }
        }

        public VM_FleView()
        {
            
        }       
        
        public void LoadDirectory()
        {
            directory.Add(new DirectoryRecord { Info = new DirectoryInfo(Config.GamePath) });
            fileSources.Clear();
        }
        
        public void SelectedItemChanged(ItemsControl viewControl, DirectoryRecord SelectedItem)
        {
            DirectoryRecord item = SelectedItem;
            foreach (var file in item.Files)
            {
                if (file.Extension == ".meta")
                {
                    continue;
                }
                FileRecord rec = null;
                if (fileSources.ContainsKey(file.FullName))
                {
                    rec = fileSources[file.FullName];
                }
                else
                {
                    rec = new FileRecord();
                    fileSources[file.FullName] = rec;
                    rec.ShowText = file.Name;
                    rec.FileFullName = file.FullName.Substring(file.FullName.IndexOf("Asset") + 6);
                    rec.DragText = rec.FileFullName;
                    rec.Name = rec.FileFullName;
                    rec.FileName = file.Name;
                    implFileIcon(file, rec);
                }
                viewControl.Items.Add(rec);
                showAtlas(file, rec);
            }
        }

        private void implFileIcon(FileInfo file, FileRecord rec)
        {
            if (rec.IconLoaded)
            {
                return;
            }
            FileType fileType = CommonTools.GetFileType(file.Name);
            if (fileType == FileType.eImage)
            {
                System.Drawing.Bitmap bitmap = FreeImageToBitmap.LoadImageFormFreeImage(file.FullName);
                rec.FileIcon = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(bitmap.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
            }
            else if (fileType == FileType.eAudio)
            {                
                rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.Mp3Icon, UriKind.Relative));
            }
            else if (fileType == FileType.eText)
            {
                rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.TxtIcon, UriKind.Relative));
            }
            else if (fileType == FileType.eScene)
            {
                rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.SceneIcon, UriKind.Relative));
            }
            else if (file.Extension == ".particle")
            {
                rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.EffectIcon, UriKind.Relative));
            }
            else if(fileType == FileType.eScript)
            {
                showScript(file, rec);
            }
        }
        
        private void showScript(FileInfo file, FileRecord rec)
        {
            string text = "";
            FileStream fs = new FileStream(file.FullName, FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs, Encoding.Default);

            int leftNumber = 0;
            List<string> namespaceList = new List<string>();

            while (true)
            {
                text = sr.ReadLine();
                if (text == null)
                {
                    break;
                }
                int posNameSpace = text.IndexOf("namespace");
                int posClass = text.IndexOf("class");
                int leftPos = text.IndexOf("{");
                int rightPos = text.IndexOf("}");
                bool b = false;
                if (posNameSpace != -1)
                {
                    int pos2 = text.IndexOf("{", posNameSpace + 1);
                    string ns = "";
                    if(pos2 != -1)
                    {
                        b = true;
                        ns = text.Substring(posNameSpace + 10, pos2 - posNameSpace - 10).Trim();
                        leftNumber++;
                    }
                    else
                    {
                        ns = text.Substring(posNameSpace + 10).Trim();
                    }
                    namespaceList.Add(ns);
                }
                if(leftPos != -1 && !b)
                {
                    leftNumber++;
                }
                b = false;
                if (posClass != -1)
                {
                    int pos2 = text.IndexOf("{");
                    string className = "";
                    if (pos2 != -1)
                    {
                        b = true;
                        className = text.Substring(posClass + 6, pos2 - posClass - 6).Trim();
                        leftNumber++;
                    }
                    else
                    {
                        className = text.Substring(posClass + 6).Trim();
                    }
                    string nsName = "";
                    for(int i = 0; i < namespaceList.Count;i++)
                    {
                        nsName = nsName + namespaceList[i] + ".";
                    }
                    if (className.IndexOf(":") != -1)
                    {
                        int comPos = className.IndexOf(":");
                        string compStr = className.Substring(comPos + 1);
                        if (compStr.Trim() == "Component")
                        {
                            className = className.Substring(0, comPos);
                            className = nsName + className;
                            ScriptNode r = new ScriptNode();
                            r.ShowText = className.Trim();
                            r.DragText = className.Trim();
                            rec.SubRecords.Add(r);
                        }
                    }
                }
                if(rightPos != -1 && !b)
                {
                    leftNumber--;
                    if(namespaceList.Count > leftNumber)
                    {
                        namespaceList.RemoveAt(leftNumber);
                    }
                }

            }

            sr.Close();
            
        }

        private void showAtlas(FileInfo file, FileRecord rec)
        {
            if (file.Extension != ".atlas")
            {
                return;
            }
            rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.PlistIcon, UriKind.Relative));
            Dictionary<string, AtlasFrame> atlasList = AtlasTools.Instance.GetAtlasFrameList(file.FullName);
            foreach (KeyValuePair<string, AtlasFrame> kv in atlasList)
            {
                AtlasFrame atlas = kv.Value;
                atlas.ShowText = atlas.frameName;
                atlas.DragText = atlas.frameName;
                atlas.FileFullName = file.FullName;
                rec.SubRecords.Add(atlas);
            }
        }

        public void DoDrag(UIElement dragElement, ItemNodeBase nodeItem)
        {
            App.vm_MainWindow.PropertyView.DragItem = nodeItem;
            DragDropEffects effect = DragDropEffects.Link;
            DragDrop.DoDragDrop(dragElement, nodeItem.DragText, effect);
        }
    }
}
