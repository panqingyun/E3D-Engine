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

       static  Dictionary<string, System.Windows.Media.ImageSource> imageSources = new Dictionary<string, System.Windows.Media.ImageSource>();

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
            imageSources.Clear();
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
                implFileIcon(file, rec);
                rec.ShowText = file.Name;
                rec.FileFullName = file.FullName.Substring(file.FullName.IndexOf("Asset") + 6);
                rec.DragText = rec.FileFullName;
                rec.Name = rec.FileFullName;
                rec.FileName = file.Name;
                viewControl.Items.Add(rec);
                showAtlas(file, rec);
            }
        }

        private void implFileIcon(FileInfo file, FileRecord rec)
        {
            FileType fileType = CommonTools.GetFileType(file.Name);
            if (fileType == FileType.eImage)
            {
                if (imageSources.ContainsKey(file.FullName))
                {
                    rec.FileIcon = imageSources[file.FullName];
                }
                else
                {
                    System.Drawing.Bitmap bitmap = FreeImageToBitmap.LoadImageFormFreeImage(file.FullName);
                    rec.FileIcon = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(bitmap.GetHbitmap(), IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
                    imageSources[file.FullName] = rec.FileIcon;
                }
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
            DragDrop.DoDragDrop(dragElement, nodeItem.DragText, effect);
        }
    }
}
