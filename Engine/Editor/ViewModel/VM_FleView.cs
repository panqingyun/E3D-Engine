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
    public class VM_FleView
    {
        public FileView _View
        {
            get;set;
        }

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
            directory.Add(new DirectoryRecord { Info = new DirectoryInfo(Config.GameResourcePath) });
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
                FileRecord rec = new FileRecord();
                if (file.Extension == ".jpg" || file.Extension == ".png")
                {
                    rec.FileIcon = new BitmapImage(new Uri(file.FullName));
                }
                else if (file.Extension == ".mp3")
                {
                    rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.Mp3Icon, UriKind.Relative));
                }
                else if (file.Extension == ".txt")
                {
                    if (!file.Name.Contains("Story"))
                    {
                        continue;
                    }
                    rec.FileIcon = new BitmapImage(new Uri(CONST_STRING.TxtIcon, UriKind.Relative));
                }
                rec.ShowText = file.Name;
                rec.FileFullName = file.FullName.Substring(file.FullName.IndexOf("resources") + 10);
                rec.DragText = rec.FileFullName;
                rec.Description = rec.FileFullName;
                rec.FileName = file.Name;
                viewControl.Items.Add(rec);
                showAtlas(file, rec);
            }
        }

        private void showAtlas(FileInfo file, FileRecord rec)
        {
            if (file.Extension != ".plist")
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
            if (nodeItem is AtlasFrame)
            {
                if (!nodeItem.FileFullName.Contains(Config.DialogAtlasPath))
                {
                    effect = DragDropEffects.None;
                }
            }
            DragDrop.DoDragDrop(dragElement, nodeItem.DragText, effect);
        }
    }
}
