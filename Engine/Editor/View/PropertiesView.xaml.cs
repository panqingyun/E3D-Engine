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
