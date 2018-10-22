using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.ComponentModel;
using System.Reflection;
using E3DEditor.Common;
using System.Windows.Media.Imaging;
using E3DEditor.Model;
using System.Collections.ObjectModel;
using E3DEditor.ViewModel;
using E3DEngine;

namespace E3DEditor.View
{
	/// <summary>
	/// Interaction logic for PropertiesView.xaml
	/// </summary>
	public partial class PropertiesView : UserControl
	{
        public ItemNodeBase DragItem
        {
            set;get;
        }

        private VM_PropertyView viewModel = new VM_PropertyView();

		private object _selectedObject;
		public object SelectedObject
		{
			get { return _selectedObject; }
			set
            {
                if (_selectedObject != value)
                {
                    _selectedObject = value;
                    if (_selectedObject is GameObjectNode)
                    {
                        AllowDrop = true;
                    }
                    else
                    {
                        AllowDrop = false;
                    }
                    ClearGrid();
                    viewModel.SelectObjectChange(_selectedObject, _grid);
                    if (_grid.RowDefinitions.Count != 0)
                    {
                        Grid.SetRowSpan(_splitter, _grid.RowDefinitions.Count);
                    }
                }
			}
		}
        
        public PropertiesView()
		{
			InitializeComponent();
            viewModel._View = this;

            PreviewDragOver += PropertiesView_PreviewDragOver;
            PreviewDrop += PropertiesView_PreviewDrop;
            PreviewDragLeave += PropertiesView_PreviewDragLeave;
            BorderThickness = new Thickness(3);
        }

        private void PropertiesView_PreviewDragLeave(object sender, DragEventArgs e)
        {
            BorderBrush = Brushes.Transparent;
        }

        private void PropertiesView_PreviewDrop(object sender, DragEventArgs e)
        {
            GameObjectNode gameObjNode = _selectedObject as GameObjectNode;
            GameObjectRef gameObj = gameObjNode.mGameObject;
            gameObj.AddComponent(DragItem.DragText);
            BorderBrush = Brushes.Transparent;
            SelectedObject = null;
            SelectedObject = gameObjNode;
        }

        private void PropertiesView_PreviewDragOver(object sender, DragEventArgs e)
        {
            GameObjectNode gameObjNode = _selectedObject as GameObjectNode;
            GameObjectRef gameObj = gameObjNode.mGameObject;
            if (DragItem is ScriptNode && !gameObj.GetHasComponent(DragItem.DragText))
            {
                e.Handled = true;
                BorderBrush = Brushes.LightGreen;
            }
            else
            {
                e.Effects = DragDropEffects.None;
                BorderBrush = Brushes.Red;
            }
        }

        public void ClearGrid()
        {
            _grid.RowDefinitions.Clear();
			for (int i = _grid.Children.Count - 1; i >= 0; i--)
			{
				if ( _grid.Children[i] != _splitter)
					_grid.Children.RemoveAt(i);
			}
		}
        
	}
}
