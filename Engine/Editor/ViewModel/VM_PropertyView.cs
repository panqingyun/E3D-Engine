using E3DEditor.Common;
using E3DEditor.View;
using E3DEngine;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Shapes;

namespace E3DEditor.ViewModel
{
    public delegate void createNewPropertyRowDelegate(PropertyInfo prop, int row, PropertyFieldAttribute attr);
    public class VM_PropertyView
    {
        private Dictionary<PropertyType, createNewPropertyRowDelegate> createNewPropertyMap = new Dictionary<PropertyType, createNewPropertyRowDelegate>();
        private Dictionary<string, UIElement> uiElementMap = new Dictionary<string, UIElement>();
        public PropertiesView _View { set; get; }

        private object _selectedObject;
        private Grid _panelParent;
        private bool _mouseDown = false;
        private double _mousePosX = 0;

        public void SelectObjectChange(object selectObjct, Panel parent)
        {
            if (_selectedObject != selectObjct)
            {
                var obj = _selectedObject as INotifyPropertyChanged;
                if (obj != null)
                    obj.PropertyChanged -= PropertyChanged;
                _panelParent = parent as Grid;
                _selectedObject = selectObjct;
                uiElementMap.Clear();
                Application.Current.Dispatcher.Invoke(() =>
                {
                    try
                    {
                        createPropertyUI();
                    }
                    catch (Exception ex)
                    {
                        MessageBox.Show(ex.ToString());
                    }
                });
                obj = _selectedObject as INotifyPropertyChanged;
                if (obj != null)
                    obj.PropertyChanged += PropertyChanged;
            }
        }

        private void createPropertyUI()
        {
            if (_selectedObject == null)
            {
                _View.ClearGrid();
                return;
            }
            int row = 0;
            Type type = _selectedObject.GetType();

            #region sort list ....
            List<PropertyInfo> properties = new List<PropertyInfo>();
            properties.AddRange(type.GetProperties());

            Comparison<PropertyInfo> sortDele = delegate (PropertyInfo x, PropertyInfo y)
            {
                var attrx = getSelectObjectAttributes(x);
                var attry = getSelectObjectAttributes(y);

                if (attrx.Length != 0 && attry.Length != 0)
                {
                    return (attrx[0] as PropertyFieldAttribute).DisplayIndex - (attry[0] as PropertyFieldAttribute).DisplayIndex;
                }

                return -1;
            };

            properties.Sort(sortDele);
            #endregion

            for (int i = 0; i < properties.Count; i++)
            {
                var attr = getSelectObjectAttributes(properties[i]);
                if (attr.Length != 0 && (attr[0] as PropertyFieldAttribute).PropType != PropertyType.HideInProperty)
                {
                    displayProperty(properties[i], row, attr[0] as PropertyFieldAttribute);
                    row++;
                }
            }
        }

        public VM_PropertyView()
        {
            createNewPropertyMap[PropertyType.Boolean] = createNewNormalBooleanRow;
            createNewPropertyMap[PropertyType.ReadOnlyBoolean] = createNewReadonlyBooleanRow;
            createNewPropertyMap[PropertyType.NormalText] = createNewNormalText;
            createNewPropertyMap[PropertyType.ReadOnlyText] = createNewReadonlyText;
            createNewPropertyMap[PropertyType.IntList] = createNewIntListRow;
            createNewPropertyMap[PropertyType.EnumType] = createNewEnumRow;
            createNewPropertyMap[PropertyType.File] = createNewFileRow;
            createNewPropertyMap[PropertyType.ImageSource] = createNewImageRow;
            createNewPropertyMap[PropertyType.ImagePath] = createImagePathRow;
            createNewPropertyMap[PropertyType.Table] = createTableRow;
            createNewPropertyMap[PropertyType.NumberText] = createNumberBoxRow;
            createNewPropertyMap[PropertyType.Vector3] = createVector3Row;
            createNewPropertyMap[PropertyType.ComponentList] = createComponentRow;
            createNewPropertyMap[PropertyType.Color4] = createColorPanel;
        }

        void PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            Application.Current.Dispatcher.Invoke(() =>
            {
                PropertyInfo property = _selectedObject.GetType().GetProperty(e.PropertyName);
                var attr = getSelectObjectAttributes(property);
                if (attr.Length != 0 && (attr[0] as PropertyFieldAttribute).PropType != PropertyType.HideInProperty)
                {
                    displayProperty(property, 0, attr[0] as PropertyFieldAttribute);
                }
            });
        }

        private object[] getSelectObjectAttributes(PropertyInfo prop)
        {
            if (SpecialGetAttributeClassMap.GetIsSpecial(_selectedObject.GetType()))
            {
                return (_selectedObject as INode).GetCustomAttributies(prop.Name);
            }
            return prop.GetCustomAttributes(typeof(PropertyFieldAttribute), false);
        }

        #region 创建新的属性显示 。。。

        private void createNewNormalText(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            gridAddRowDef();
            createNewTextRow(prop, row, false);
            gridAddEnd();
        }

        private void createNewReadonlyText(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            gridAddRowDef();
            createNewTextRow(prop, row, true);
            gridAddEnd();
        }

        private void createNewNormalBooleanRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            gridAddRowDef();
            createNewBooleanRow(prop, row, false);
            gridAddEnd();
        }

        private void createNewReadonlyBooleanRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            gridAddRowDef();
            createNewBooleanRow(prop, row, true);
            gridAddEnd();
        }

        TextBlock gridAddTitle(float left, string title)
        {
            TextBlock tb = null;
            if (uiElementMap.ContainsKey(title))
            {
                tb = uiElementMap[title] as TextBlock;
            }
            else
            {
                tb = new TextBlock() { Text = title };
                uiElementMap[title] = tb;
                tb.Foreground = new SolidColorBrush(Colors.White);
                tb.Margin = new Thickness(left + 4, 4, 4, 4);

                Grid.SetColumn(tb, 0);
                Grid.SetRow(tb, _panelParent.RowDefinitions.Count - 1);
                _panelParent.Children.Add(tb);
            }
            return tb;

        }

        private CheckBox createCheckBox()
        {
            CheckBox cb = new CheckBox();
            cb.Margin = new Thickness(4, 0, 0, 0);
            cb.HorizontalAlignment = HorizontalAlignment.Left;
            cb.VerticalAlignment = VerticalAlignment.Center;
            Grid.SetColumn(cb, 0);
            Grid.SetRow(cb, _panelParent.RowDefinitions.Count - 1);
            _panelParent.Children.Add(cb);

            return cb;
        }

        private void Check_Unchecked(object sender, RoutedEventArgs e)
        {
            CheckBox check = sender as CheckBox;
            ComponentRef com = check.Tag as ComponentRef;
            com.SetActive(false);
        }

        private void Check_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox check = sender as CheckBox;
            ComponentRef com = check.Tag as ComponentRef;
            com.SetActive(true);
        }

        private void createColorPanel(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            gridAddRowDef();
            gridAddTitle(prop);
            Rectangle back = new Rectangle();
            back.Margin = new Thickness(0, 2, 2, 0);
            Rectangle rect = new Rectangle();
            Vector4 color = (Vector4)prop.GetValue(_selectedObject);
            back.Fill = _View.Resources["CheckerBoard"] as Brush;
            rect.Fill = new SolidColorBrush(Color.FromArgb((byte)(color.w * 255), 
                (byte)(color.x * 255), (byte)(color.y * 255), (byte)(color.z * 255)));
            rect.Tag = prop;

            rect.Margin = new Thickness(0, 2, 2, 0);
            Grid.SetColumn(rect, 1);
            Grid.SetRow(rect, _panelParent.RowDefinitions.Count - 1);
            Grid.SetColumn(back, 1);
            Grid.SetRow(back, _panelParent.RowDefinitions.Count - 1);
            var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
            Validation.SetErrorTemplate(rect, template);
            _panelParent.Children.Add(back);
            _panelParent.Children.Add(rect);
            rect.PreviewMouseLeftButtonUp += Rect_PreviewMouseLeftButtonUp;
            gridAddEnd();
        }

        private void Rect_PreviewMouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            Rectangle rect = sender as Rectangle;
            PropertyInfo prop = rect.Tag as PropertyInfo;
            Vector4 color = (Vector4)prop.GetValue(_selectedObject);

            ColorDialog colorDlg = new ColorDialog();
            colorDlg.InitialColor = Color.FromArgb((byte)(color.w * 255),
                (byte)(color.x * 255), (byte)(color.y * 255), (byte)(color.z * 255));
            colorDlg.Show();
            Vector4 vec = new Vector4(1, 1, 1, 1);
            colorDlg.SelectedColorChanged += new EventHandler<ColorPicker.EventArgs<Color>>((object _sender, ColorPicker.EventArgs<Color> _e) =>
            {
                rect.Fill = new SolidColorBrush( _e.Value);
                vec.SetValue(_e.Value.R / 255.0f, _e.Value.G / 255.0f, _e.Value.B / 255.0f, _e.Value.A / 255.0f);
                prop.SetValue(_selectedObject, vec);
            });
        }

        private void createComponentRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            IList<ComponentRef> componentList = prop.GetValue(_selectedObject) as IList<ComponentRef>;
            Type comType = typeof(ComponentRef);
            for (int i = 0; i < componentList.Count; i++)
            {
                gridAddRowDef();
                CheckBox check = createCheckBox();
                check.IsChecked = componentList[i].GetIsActive();
                check.Tag = componentList[i];
                check.Checked += Check_Checked;
                check.Unchecked += Check_Unchecked;
                gridAddTitle(15, componentList[i].GetName());
                gridAddEnd();
                ComponentRef com = componentList[i];
                List<ComponentField> fieldList = com.GetFields();
                for (int j = 0; j < fieldList.Count; j++)
                {
                    gridAddRowDef();
                    TextBlock title = gridAddTitle(30, fieldList[j].Name);
                    if ((fieldList[j].Type & ComponentFieldType.FT_FLOAT) == ComponentFieldType.FT_FLOAT ||
                        (fieldList[j].Type & ComponentFieldType.FT_INT) == ComponentFieldType.FT_INT)
                    {
                        NumberTextBox tb = createNumberTextBox();
                        tb.Text = fieldList[j].Value;
                        tb.Tag = fieldList[j];
                        tb._KeyUp += comNumTb__KeyUp;
                        title.Tag = fieldList[j];
                        float value = Convert.ToSingle(fieldList[j].Value);
                        title.MouseLeftButtonDown += new MouseButtonEventHandler((object sender, MouseButtonEventArgs e) =>
                        {
                            _mouseDown = true;
                            _mousePosX = e.GetPosition(null).X;
                            title.CaptureMouse();
                        });
                        title.MouseMove += new MouseEventHandler((object sender, MouseEventArgs e) =>
                        {
                            if(_mouseDown)
                            {
                                double xPos = e.GetPosition(null).X;
                                ComponentField f = (sender as TextBlock).Tag as ComponentField;
                                if((f.Type & ComponentFieldType.FT_READONLY) == ComponentFieldType.FT_READONLY)
                                {
                                    return;
                                }
                                if ((f.Type & ComponentFieldType.FT_FLOAT) == ComponentFieldType.FT_FLOAT)
                                {
                                    if(xPos > _mousePosX)
                                    {
                                        value += 0.01f;
                                    }
                                    else if(xPos < _mousePosX)
                                    {
                                        value -= 0.01f;
                                    }
                                }
                                else if((f.Type & ComponentFieldType.FT_INT) == ComponentFieldType.FT_INT)
                                {
                                    if (xPos > _mousePosX)
                                    {
                                        value += 1;
                                    }
                                    else if(xPos < _mousePosX)
                                    {
                                        value -= 1;
                                    }
                                }
                                tb.Text = value.ToString();
                                f.SetValue(tb.Text);
                                _mousePosX = xPos;
                            }
                        });
                        title.MouseLeftButtonUp += new MouseButtonEventHandler((object sender, MouseButtonEventArgs e) => 
                        {
                            _mouseDown = false;
                            _mousePosX = 0;
                            title.ReleaseMouseCapture();
                        });
                    }
                    else if (fieldList[j].Type == ComponentFieldType.FT_OBJECT)
                    {
                        TextBox tb = createTextBox(true);
                        tb.Tag = fieldList[j];
                        tb.KeyUp += comTb_KeyUp;
                        tb.Text = fieldList[j].Value;
                    }
                    else if (fieldList[j].Type == ComponentFieldType.FT_BOOLEAN)
                    {
                        ComboBox cb = createBoolControl();
                        cb.Tag = fieldList[j];
                        cb.SelectionChanged += comCb_SelectionChanged;
                        cb.SelectedIndex = fieldList[j].Value == "true" ? 0 : 1;
                    }
                    else if (fieldList[j].Type == ComponentFieldType.FT_VECTOR3)
                    {
                        var vecElement = new Vector3Control();
                        string[] vStr = fieldList[j].Value.Split(',');
                        Vector3 vec = new Vector3(Convert.ToSingle(vStr[0]), Convert.ToSingle(vStr[1]), Convert.ToSingle(vStr[2]));
                        vecElement.ValueObject = vec;
                        vecElement.Margin = new Thickness(0, 2, 2, 0);
                        vecElement.BorderThickness = new Thickness(0);
                        vecElement.Tag = fieldList[j];
                        Grid.SetColumn(vecElement, 1);
                        Grid.SetRow(vecElement, _panelParent.RowDefinitions.Count - 1);
                        var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
                        Validation.SetErrorTemplate(vecElement, template);
                        vecElement.EnterKeyDown += VecElement_EnterKeyDown;
                        _panelParent.Children.Add(vecElement);
                    }
                    else
                    {
                        TextBox tb = createTextBox(false);
                        tb.Tag = fieldList[j];
                        tb.KeyUp += comTb_KeyUp;
                        tb.Text = fieldList[j].Value;
                    }
                    gridAddEnd();

                }
            }
        }

        private void VecElement_EnterKeyDown(object sender, KeyEventArgs e)
        {
            Vector3Control vc = sender as Vector3Control;
            ComponentField cf = vc.Tag as ComponentField;
            cf.SetValue(vc.X + "," + vc.Y + "," + vc.Z);
        }

        private void comCb_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            ComboBox cb = sender as ComboBox;
            ComponentField cf = cb.Tag as ComponentField;
            cf.SetValue(cb.SelectedIndex == 0 ? "true" : "false");
        }

        private void comTb_KeyUp(object sender, KeyEventArgs e)
        {
            if(e.Key != Key.Enter)
            {
                return;
            }
            TextBox tb = sender as TextBox;
            ComponentField cf = tb.Tag as ComponentField;
            cf.SetValue(tb.Text);
        }

        private void comNumTb__KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key != Key.Enter)
            {
                return;
            }
            NumberTextBox tb = sender as NumberTextBox;
            ComponentField cf = tb.Tag as ComponentField;
            cf.SetValue(tb.Text);
        }

        private NumberTextBox createNumberTextBox()
        {
            var numBox = new NumberTextBox();
            numBox.Margin = new Thickness(0, 2, 2, 0);
            numBox.BorderThickness = new Thickness(0);
            Grid.SetColumn(numBox, 1);
            Grid.SetRow(numBox, _panelParent.RowDefinitions.Count - 1);
            var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
            Validation.SetErrorTemplate(numBox, template);

            _panelParent.Children.Add(numBox);

            return numBox;
        }

        private void createVector3Row(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            Vector3Control vecElement = null;
            if (uiElementMap.ContainsKey(prop.Name))
            {
                vecElement = uiElementMap[prop.Name] as Vector3Control;
                vecElement.ValueObject = (E3DEngine.Vector3)prop.GetValue(_selectedObject);
            }
            else
            {
                gridAddRowDef();
                gridAddTitle(prop);
                gridAddEnd();
                gridAddRowDef();
                vecElement = new Vector3Control();
                vecElement.ValueObject = (E3DEngine.Vector3)prop.GetValue(_selectedObject);
                vecElement.SelectObject = _selectedObject;
                vecElement.ValueProperty = prop;
                vecElement.Margin = new Thickness(0, 2, 2, 0);
                vecElement.BorderThickness = new Thickness(0);
                Grid.SetColumn(vecElement, 0);
                Grid.SetColumnSpan(vecElement, 2);
                Grid.SetRow(vecElement, _panelParent.RowDefinitions.Count - 1);
                var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
                Validation.SetErrorTemplate(vecElement, template);
                uiElementMap[prop.Name] = vecElement;
                _panelParent.Children.Add(vecElement);
                gridAddEnd();
            }
        }

        private void createNumberBoxRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            if (!uiElementMap.ContainsKey(prop.Name))
            {
                gridAddRowDef();
                gridAddTitle(prop);
                var numBox = createNumberTextBox();
                numBox.Tag = prop;
                var binding = new Binding(prop.Name);
                binding.Source = _selectedObject;
                binding.ValidatesOnExceptions = true;
                binding.Mode = BindingMode.OneWay;

                numBox.tbx.SetBinding(TextBox.TextProperty, binding);
                uiElementMap[prop.Name] = numBox;
                numBox.KeyUp += NumBox_KeyUp;
                gridAddEnd();
            }
        }

        private void NumBox_KeyUp(object sender, KeyEventArgs e)
        {
            if (Key.Enter == e.Key)
            {
                NumberTextBox numBox = (sender as NumberTextBox);
                PropertyInfo prop = numBox.Tag as PropertyInfo;
                int number = numBox.Number;
                prop.SetValue(_selectedObject, number);
            }

        }
        private ComboBox createBoolControl()
        {
            ComboBox cb = new ComboBox();
            cb.Items.Add("是");
            cb.Items.Add("否");
            cb.Margin = new Thickness(0, 2, 2, 0);
            cb.BorderThickness = new Thickness(0);
            Grid.SetColumn(cb, 1);
            Grid.SetRow(cb, _panelParent.RowDefinitions.Count - 1);
            var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
            Validation.SetErrorTemplate(cb, template);

            _panelParent.Children.Add(cb);
            return cb;
        }

        private TextBox createTextBox(bool isReadOnly)
        {
            var ed = new TextBox();
            ed.Margin = new Thickness(0, 2, 2, 0);
            ed.BorderThickness = new Thickness(0);
            ed.IsReadOnly = isReadOnly;
            Grid.SetColumn(ed, 1);
            Grid.SetRow(ed, _panelParent.RowDefinitions.Count - 1);
            var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
            Validation.SetErrorTemplate(ed, template);

            _panelParent.Children.Add(ed);

            return ed;
        }

        private RowDefinition gridAddRowDef()
        {
            var rowDef = new RowDefinition();
            rowDef.Height = new GridLength(25);
            _panelParent.RowDefinitions.Add(rowDef);
            return rowDef;
        }

        private void gridAddTitle(PropertyInfo prop)
        {
            TextBlock tb = null;
            if (uiElementMap.ContainsKey(prop.Name))
            {
                tb = uiElementMap[prop.Name] as TextBlock;
                tb.Text = CONST_STRING.GetTitleText(prop.ReflectedType, prop.Name);
            }
            else
            {
                tb = new TextBlock() { Text = CONST_STRING.GetTitleText(prop.ReflectedType, prop.Name) };
                tb.Foreground = new SolidColorBrush(Colors.White);
                tb.Margin = new Thickness(4);
                Grid.SetColumn(tb, 0);
                Grid.SetRow(tb, _panelParent.RowDefinitions.Count - 1);
                _panelParent.Children.Add(tb);
                uiElementMap[prop.Name] = tb;
            }

        }

        private void gridAddEnd()
        {
            var line = new Line();
            line.Style = (Style)_View.Resources["gridHorizontalLineStyle"];
            Grid.SetRow(line, _panelParent.RowDefinitions.Count - 1);
            _panelParent.Children.Add(line);
        }

        private void createNewTextRow(PropertyInfo prop, int row, bool isReadOnly)
        {
            TextBox ed = null;
            if (uiElementMap.ContainsKey(prop.Name))
            {
                //ed = uiElementMap[prop.Name] as TextBox; 
            }
            else
            {
                gridAddTitle(prop);
                ed = createTextBox(isReadOnly);
                ed.AllowDrop = false;
                ed.Tag = prop;

                var binding = new Binding(prop.Name);
                binding.Source = _selectedObject;
                binding.ValidatesOnExceptions = true;
                binding.Mode = BindingMode.OneWay;

                ed.SetBinding(TextBox.TextProperty, binding);
                ed.KeyUp += textBox_KeyUp;
                uiElementMap[prop.Name] = ed;
            }
        }

        private void textBox_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                TextBox tb = sender as TextBox;
                PropertyInfo pri = tb.Tag as PropertyInfo;
                pri.SetValue(_selectedObject, Convert.ChangeType(tb.Text, pri.PropertyType));
                tb.Focus();
            }
        }

        private void createNewBooleanRow(PropertyInfo prop, int row, bool isReadonly)
        {
            ComboBox cb = null;
            if (uiElementMap.ContainsKey(prop.Name))
            {
                cb = uiElementMap[prop.Name] as ComboBox;

                bool propValue = false;
                if (prop.PropertyType == typeof(int))
                    propValue = (int)prop.GetValue(_selectedObject) == 1;
                else
                    propValue = (bool)prop.GetValue(_selectedObject);

                if (propValue)
                    cb.SelectedIndex = 0;
                else
                    cb.SelectedIndex = 1;
            }
            else
            {
                gridAddTitle(prop);
                cb = createBoolControl();
                cb.Tag = prop;              

                bool propValue = false;
                if (prop.PropertyType == typeof(int))
                    propValue = (int)prop.GetValue(_selectedObject) == 1;
                else
                    propValue = (bool)prop.GetValue(_selectedObject);

                if (propValue)
                    cb.SelectedIndex = 0;
                else
                    cb.SelectedIndex = 1;

                cb.SelectionChanged += boolComb_SelectionChanged;
                uiElementMap[prop.Name] = cb;
            }

        }

        private void boolComb_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            var comboBox = sender as ComboBox;
            PropertyInfo pri = comboBox.Tag as PropertyInfo;

            if (comboBox.SelectedIndex == 0)
            {
                pri.SetValue(_selectedObject, true);
            }
            else
            {
                pri.SetValue(_selectedObject, false);
            }
        }

        private void createNewIntListRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            if (!uiElementMap.ContainsKey(prop.Name))
            {
                gridAddRowDef();
                MultTextBox mutb = new MultTextBox();
                mutb.Margin = new Thickness(0, 2, 2, 0);
                mutb.BorderThickness = new Thickness(0);
                mutb.VerticalAlignment = VerticalAlignment.Stretch;
                mutb.titleName.Text = CONST_STRING.GetTitleText(prop.ReflectedType, prop.Name);
                Grid.SetColumn(mutb, 0);
                Grid.SetColumnSpan(mutb, 2);
                mutb.HorizontalAlignment = HorizontalAlignment.Stretch;
                Grid.SetRow(mutb, _panelParent.RowDefinitions.Count - 1);
                mutb.SelectObject = _selectedObject;
                mutb.inputPropertyInfo = prop;
                _panelParent.Children.Add(mutb);

                _panelParent.RowDefinitions[_panelParent.RowDefinitions.Count - 1].Height = new GridLength(mutb.TotalHeight);

                mutb.EnterComplete += Mutb_EnterComplete;
                uiElementMap[prop.Name] = mutb;
                gridAddEnd();
            }
        }

        private void createImgeProperty(ImageSource src, int row, string propName)
        {
            if (!uiElementMap.ContainsKey(propName))
            {
                var img = new System.Windows.Controls.Image();
                img.Source = src;
                Grid.SetColumn(img, 0);
                Grid.SetColumnSpan(img, 2);
                Grid.SetRow(img, _panelParent.RowDefinitions.Count - 1);
                _panelParent.Children.Add(img);
                img.HorizontalAlignment = HorizontalAlignment.Stretch;
                img.VerticalAlignment = VerticalAlignment.Stretch;

                img.Width = src.Width > _panelParent.ActualWidth ? _panelParent.ActualWidth : src.Width;
                _panelParent.RowDefinitions[_panelParent.RowDefinitions.Count - 1].Height = new GridLength(500);
                uiElementMap[propName] = img;
            }
        }

        private void createNewImageRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            gridAddRowDef();
            createImgeProperty(prop.GetValue(_selectedObject) as ImageSource, row, prop.Name);
            gridAddEnd();
        }

        private void createImagePathRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            if (!uiElementMap.ContainsKey(prop.Name))
            {
                gridAddRowDef();
                gridAddTitle(prop);

                var ed = createTextBox(false);

                ed.Tag = prop;

                var binding = new Binding(prop.Name);
                binding.Source = _selectedObject;
                binding.ValidatesOnExceptions = true;
                binding.Mode = BindingMode.OneWay;

                ed.SetBinding(TextBox.TextProperty, binding);

                uiElementMap[prop.Name] = ed;

                gridAddEnd();
            }
        }
        
        private DropDownBox createDropDownBox(int row)
        {
            DropDownBox box = new DropDownBox();

            box.Margin = new Thickness(0, 2, 2, 0);
            box.BorderThickness = new Thickness(0);
            Grid.SetColumn(box, 0);
            Grid.SetColumnSpan(box, 2);
            Grid.SetRow(box, _panelParent.RowDefinitions.Count - 1);
            var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
            Validation.SetErrorTemplate(box, template);
            Panel.SetZIndex(box, 20);
            _panelParent.Children.Add(box);

            return box;
        }

        private void createTableRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            if (!uiElementMap.ContainsKey(prop.Name))
            {
                gridAddRowDef();
                var ed = createDropDownBox(row);
                ed.Title = CONST_STRING.GetTitleText(prop.ReflectedType, prop.Name);
                ed.AllowDrop = true;
                ed.Tag = prop;
                ed.SelectText = prop.GetValue(_selectedObject).ToString();
                ed.PreviewKeyUp += dropDown_PreviewKeyUp;
                //ed.ItemSource = TableManager.GetNodeList(attr.Param.ToString());
                ed.DorpDownEvent += dropDown_DorpDownEvent;
                ed.DropDownSelected += dropDown_DropDownSelected;
                ed.PreviewDragOver += new DragEventHandler((object sender, DragEventArgs e) =>
                {
                    table_dragOver(attr, sender, e);
                });
                ed.PreviewDragLeave += control_PreviewDragLeave;
                ed.PreviewDrop += new DragEventHandler((object sender, DragEventArgs e) =>
                {
                    table_PreviewDrop(sender, e.Data.GetData(typeof(string)).ToString(), attr.Param.ToString());
                });
                uiElementMap[prop.Name] = ed;
                gridAddEnd();
            }
        }

        private void dropDown_DropDownSelected(object sender, string selectText)
        {
            DropDownBox ddb = sender as DropDownBox;
            string num = selectText;
            (ddb.Tag as PropertyInfo).SetValue(_selectedObject, Convert.ToInt32(num));
            int row = Grid.GetRow(ddb);
            _panelParent.RowDefinitions[row].Height = new GridLength(ddb.Height);
        }

        private void control_PreviewDragLeave(object sender, DragEventArgs e)
        {
            (sender as Control).Background = Brushes.White;
        }

        private void dropDown_PreviewKeyUp(object sender, KeyEventArgs e)
        {
            DropDownBox ddb = sender as DropDownBox;
            if (e.Key == Key.Enter)
            {
                string num = ddb.SelectText;
                (ddb.Tag as PropertyInfo).SetValue(_selectedObject, Convert.ToInt32(num));
            }
        }

        private void dropDown_DorpDownEvent(object sender, bool isDown)
        {
            DropDownBox box = sender as DropDownBox;
            int row = Grid.GetRow(box);
            _panelParent.RowDefinitions[row].Height = new GridLength(box.Height);
        }

        private void table_dragOver(PropertyFieldAttribute attr, object sender, DragEventArgs e)
        {
            string text = e.Data.GetData(typeof(string)).ToString();
            if (checkDragTextIsCanUse(attr.Param, text))
            {
                e.Handled = true;
                (sender as DropDownBox).Background = Brushes.LightGreen;
            }
            else
            {
                e.Effects = DragDropEffects.None;
                (sender as DropDownBox).Background = Brushes.Red;
            }
        }

        private bool checkDragTextIsCanUse(object tableName, string text)
        {
            if (tableName != null)
            {
                if (_View.DragItem.TableName == tableName.ToString())
                {
                    return true;
                }
                else if ("" == tableName.ToString())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            return false;
        }

        private void table_PreviewDrop(object sender, string text, string tableName)
        {
            DropDownBox tb = sender as DropDownBox;

            tb.SelectText = "";
            string param = "";
            PropertyInfo prop = tb.Tag as PropertyInfo;
            //NodeBase node = null;
            if (tableName != "" && _View.DragItem.TableName == tableName)
            {
                string id = text;
                prop.SetValue(_selectedObject, Convert.ChangeType(id, prop.PropertyType));
            }
            else if (text.LastIndexOf(".") != -1)
            {
                string extention = System.IO.Path.GetExtension(text);
                param = text.Replace(extention, "");

            }
            else
            {
                param = text;
            }

            //if (tableName == StoryImageJson.TAB_NAME)
            //{
            //    node = TableManager.CreateNode(tableName, param) as StoryImage;
            //    ((StoryImage)node).Path = param;
            //}
            //prop.SetValue(_selectedObject, Convert.ChangeType(node.ID, prop.PropertyType));
            //tb.ReplaceNewTextBox(node.ID.ToString());

            (sender as DropDownBox).Background = Brushes.White;
        }

        private void createNewFileRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            if (!uiElementMap.ContainsKey(prop.Name))
            {
                gridAddRowDef();
                string text = prop.GetValue(_selectedObject) as string;
                if (text == "")
                    return;
                FileType fileType = CommonTools.GetFileType(text);

                if (fileType == FileType.eImage)
                {
                    System.Drawing.Bitmap bitmap = FreeImageToBitmap.LoadImageFormFreeImage(Config.GamePath + "\\" + text);
                    System.Windows.Media.Imaging.BitmapSource bs = Imaging.CreateBitmapSourceFromHBitmap(bitmap.GetHbitmap(), 
                        IntPtr.Zero, Int32Rect.Empty, System.Windows.Media.Imaging.BitmapSizeOptions.FromEmptyOptions());
                 
                    createImgeProperty(bs, _panelParent.RowDefinitions.Count - 1, prop.Name);
                }
                else if (fileType == FileType.eText || fileType == FileType.eScript)
                {
                    showTxt(text, prop.Name);
                }
                else if (fileType == FileType.eVideo || fileType == FileType.eAudio)
                {
                    showMusic(text, prop.Name);
                }
                else
                {
                    _panelParent.RowDefinitions.RemoveAt(_panelParent.RowDefinitions.Count - 1);
                    return;
                }
                gridAddEnd();
            }
        }

        private void showMusic(string fName, string propName)
        {
            RowDefinition _row = _panelParent.RowDefinitions[_panelParent.RowDefinitions.Count - 1];
            _row.Height = new GridLength(820);

            MediaControl md = new MediaControl();
            Grid.SetColumn(md, 0);
            Grid.SetColumnSpan(md, 2);
            md.Margin = new Thickness(0, 2, 0, 0);
            Grid.SetRow(md, _panelParent.RowDefinitions.Count - 1);
            var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
            Validation.SetErrorTemplate(md, template);
            md.VerticalAlignment = VerticalAlignment.Bottom;
            md.HorizontalAlignment = HorizontalAlignment.Stretch;
            md.Foreground = Brushes.White;
            md.MediaSource =  new Uri(Config.GamePath + "\\" + fName, UriKind.Absolute);
            uiElementMap[propName] = md;

            _panelParent.Children.Add(md);
        }

        private void showTxt(string fName, string propName)
        {
            RowDefinition _row = _panelParent.RowDefinitions[_panelParent.RowDefinitions.Count - 1];
            _row.Height = new GridLength(820);

            TextBox _tb = createTextBox(true);
            _tb.FontFamily = new FontFamily("Consolas");
            Grid.SetColumn(_tb, 0);
            Grid.SetColumnSpan(_tb, 2);
            _tb.Margin = new Thickness(0, 2, 0, 0);
            _tb.Background = Brushes.Black;
            _tb.Foreground = Brushes.White;
            _tb.VerticalScrollBarVisibility = ScrollBarVisibility.Auto;
            _tb.HorizontalScrollBarVisibility = ScrollBarVisibility.Auto;
            _tb.Text = System.IO.File.ReadAllText(Config.GamePath + "\\" + fName);
            uiElementMap[propName] = _tb;
        }

        private void Mutb_EnterComplete(object sender, EventArgs e)
        {
            MultTextBox mtb = sender as MultTextBox;
            NumberParamEventArgs _e = e as NumberParamEventArgs;
            int row = Grid.GetRow(mtb);
            _panelParent.RowDefinitions[row].Height = new GridLength(mtb.TotalHeight);
        }

        private bool addValueInComboBox(ComboBox cb, Type type)
        {
            List<string> source = EnumTools.GetEnumListByType(type);
            if (source == null)
            {
                return false;
            }

            for (int i = 0; i < source.Count; i++)
            {
                cb.Items.Add(source[i]);
            }

            return true;
        }

        private void createNewEnumRow(PropertyInfo prop, int row, PropertyFieldAttribute attr)
        {
            if (!uiElementMap.ContainsKey(prop.Name))
            {
                gridAddRowDef();
                gridAddTitle(prop);
                var cb = new ComboBox();
                Type type = prop.PropertyType;
                if (attr.EnumType != null) type = attr.EnumType;
                if (!addValueInComboBox(cb, type))
                    return;
                cb.Margin = new Thickness(0, 2, 2, 0);
                cb.BorderThickness = new Thickness(0);

                Grid.SetColumn(cb, 1);
                Grid.SetRow(cb, _panelParent.RowDefinitions.Count - 1);
                cb.Tag = prop;
                int propValue = (int)prop.GetValue(_selectedObject);
                string text = EnumTools.GetTextByValue(propValue, type);
                cb.SelectedItem = text;

                cb.SelectionChanged += new SelectionChangedEventHandler((object sender, SelectionChangedEventArgs e) =>
                {
                    int enumValue = EnumTools.GetEnumValue(cb.SelectedValue.ToString(), type);
                    prop.SetValue(_selectedObject, EnumTools.Int2Enum(enumValue, type));
                });
                var template = (ControlTemplate)_View.Resources["validationErrorTemplate"];
                Validation.SetErrorTemplate(cb, template);
                uiElementMap[prop.Name] = cb;
                _panelParent.Children.Add(cb);
                gridAddEnd();
            }
        }

        #endregion

        private void displayProperty(PropertyInfo prop, int row, PropertyFieldAttribute prf)
        {
            if (!createNewPropertyMap.ContainsKey(prf.PropType))
            {
                return;
            }
            createNewPropertyMap[prf.PropType](prop, row, prf);
        }

    }
}
