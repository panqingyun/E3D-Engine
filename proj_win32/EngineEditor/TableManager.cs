using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.Linq;

namespace Service
{
    public enum Condition
    {
        EqualTo,            // 等于
        NotEqual,           // 不等于
        GreaterThan,        // 大于
        LessThan,           // 小于
    }

    public class TableQuery
    {
        private Dictionary<int,Dictionary<string, string>> table;
        private static TableQuery query;
        private static string selectKey = string.Empty;
        private static bool isSelectRow = true;

        private TableQuery()
        {
 
        }
        public static TableQuery Select()
        {
            isSelectRow = true;
            TableQuery _query = new TableQuery();
            query = _query;
            return query;
        }

        public static TableQuery Select(string key)
        {
            isSelectRow = false;
            TableQuery _query = new TableQuery();
            query = _query;
            selectKey = key;
            return query;
        }

        public TableQuery From(Dictionary<int,Dictionary<string, string>> table)
        {
            query.table = table;
            return query;
        }

        public Dictionary<string,string> Where(string key,int value, Condition condition)
        {
            Dictionary<string, string> newDicList = null;
            switch (condition)
            {
                case Condition.EqualTo:
                    {
                        newDicList = selectDicionary(key, value);
                    }
                    break;
                default: 
                    break;
            }
            return newDicList;
        }

        public Dictionary<string, string> Where(string key1, int value1, string key2, int value2, Condition condition)
        {
            Dictionary<string, string> newDicList = new Dictionary<string, string>();
            switch (condition)
            {
                case Condition.EqualTo:
                    {
                        int keyhash = value1 * 10000 + value2;
                        if (table.ContainsKey(keyhash) && table[keyhash].ContainsKey(key1))
                        {
                            if (table[keyhash].ContainsKey(key2) && int.Parse(table[keyhash][key2]) == value2)
                            {
                                newDicList = table[keyhash];
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
            return newDicList;
        }

        private Dictionary<string, string> selectDicionary(string key, int value)
        {
            Dictionary<string, string> newDicList = new Dictionary<string,string>();
            if (table.ContainsKey(value) == true && table[value].ContainsKey(key))
            {
                if (int.Parse(table[value][key]) == value)
                {
                    newDicList = table[value];
                }
            }
            return newDicList;
        }

        private object selectFirstValue(string key ,int value)
        {
            if (table.ContainsKey(value) == true && table[value].ContainsKey(key))
            {
                if (int.Parse(table[value][key]) == value && table[value].ContainsKey(selectKey))
                {
                    return table[value][selectKey];
                }
            }
            return null;
        }

        public static void Sort(List<Dictionary<string, string>> sortList,string sortKey)
        {
            
        }
    }

    public class TableBase
    {
        //public string ID;
        public string TableName;
        public string SourcePath;//路径字段只在开发阶段本地加载的时候用了，当使用Bundle的时候不用这个值 2016/09/23 @Onezz

        public string SourceData { get; set; }
        public event EventHandler TableLoaded;


        private Dictionary<int, Dictionary<string, string>> tableDictionary = new Dictionary<int, Dictionary<string, string>>();
        private Dictionary<int, TableBase> allTableInstanceDic = new Dictionary<int, TableBase>();
        public void Loaded()
        {            
            //本地加载需要在这里根据读取的路径额外加载一份
            string text = File.ReadAllText(SourcePath);
            loadFileContent(text);
            
        }

        private void analysisXml(XmlDocument xml_doc)
        {
            if (xml_doc == null)
            {
                return;
            }
    //        Profiler.BeginSample("TableRegister a----------");
            XmlElement rootElem = xml_doc.DocumentElement;
            XmlNodeList ConfigItemList = rootElem.GetElementsByTagName("ConfigItem");
    //        Profiler.EndSample();
			int k = 0;
            try
            {
     //           Profiler.BeginSample("TableRegister----------");
                foreach (XmlNode item_node in ConfigItemList)
                {
                    Dictionary<string, string> node_dic = new Dictionary<string, string>();
                    foreach (XmlNode node in item_node.Attributes)
                    {
                        node_dic.Add(node.Name, node.Value);
                    }
                    int key = int.Parse(node_dic[GetKey1()]);
					k = key;
                    if (GetKey1() != GetKey2())
                    {
                        key = int.Parse(node_dic[GetKey1()]) * 10000 + int.Parse(node_dic[GetKey2()]);
                    }
                    tableDictionary.Add(key, node_dic);
                    Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集 
                    TableBase tbl = (TableBase)(TableBase)assembly.CreateInstance(TableName);
                    processSelectResult(ref tbl, node_dic);
                    allTableInstanceDic.Add(key, tbl);
                }
            //    Profiler.EndSample();
            }
            catch (Exception ex)
            {
                 Console.WriteLine(TableName + " | Key1 | " + GetKey1() + " | Key2 | " + GetKey2() + " Key = " + k + " { " + ex.ToString() + " }");
            }
        }

        private void loadFileContent(string fileContent)
        {
            XmlDocument xml_doc = new XmlDocument();
//            Profiler.BeginSample("TableRegister LoadXml----------");
            xml_doc.LoadXml(fileContent);
//            Profiler.EndSample();
            analysisXml(xml_doc);

            if (TableLoaded != null)
            {
                TableManager.TableRegistCount += 1;
                TableLoaded(this, null);
            }
        }

        public virtual void Release() { }
        public virtual void Destory() { }
        public virtual string GetKey1() { return "ID"; }
        public virtual string GetKey2() { return "ID"; }
       
        public T Select<T>(int key) where T : TableBase
        {
            if (allTableInstanceDic.ContainsKey(key) == false)
                return null;
            return allTableInstanceDic[key] as T;
        }

        public TableBase Select(Type T,int key)
        {
            if (allTableInstanceDic.ContainsKey(key) == false)
                return null;
            return allTableInstanceDic[key];
        }

        private void processSelectResult<T>(Dictionary<string,string> ConfigItemVar) where T : TableBase
        {
            if (TableManager.GetTableInstance<T>() == null)
            {
                return;
            }
            
            foreach (PropertyInfo property in TableManager.GetTableInstance<T>().GetType().GetProperties())
            {
                if (ConfigItemVar.ContainsKey(property.Name) == false)
                {
                    continue;
                }
                if (TableManager.SpecialType.ContainsKey(property.PropertyType.Name) && TableManager.SpecialType[property.PropertyType.Name] == true)
                {
                    property.SetValue(TableManager.GetTableInstance<T>(), System.Activator.CreateInstance(property.PropertyType,ConfigItemVar[property.Name]), null);
                }
                else
                {
                    property.SetValue(TableManager.GetTableInstance<T>(), Convert.ChangeType(ConfigItemVar[property.Name], property.PropertyType), null);
                }
            }
        }

        private void processSelectResult(ref TableBase T, Dictionary<string, string> ConfigItemVar)
        {
            if (T == null)
            {
                return;
            }

            foreach (PropertyInfo property in T.GetType().GetProperties())
            {
                if (ConfigItemVar.ContainsKey(property.Name) == false)
                {
                    continue;
                } try
                {
                    if (TableManager.SpecialType.ContainsKey(property.PropertyType.Name) && TableManager.SpecialType[property.PropertyType.Name] == true)
                    {
                        property.SetValue(T, System.Activator.CreateInstance(property.PropertyType, ConfigItemVar[property.Name]), null);
                    }
                    else
                    {
                        property.SetValue(T, Convert.ChangeType(ConfigItemVar[property.Name], property.PropertyType), null);
                    }
                }
                catch (Exception ex)
                {
                    Console.WriteLine(TableName + " |属性名| " + property.Name + " |属性值| " + ConfigItemVar[property.Name] + " |异常| " + ex.ToString());
                }
            }
        }

        public T Select<T>(int key1, int key2) where T : TableBase
        {
            int key = key1 * 10000 + key2;
            if (allTableInstanceDic.ContainsKey(key) == false)
                return null;
            return allTableInstanceDic[key] as T;
        }

        public TableBase Select(Type T, int key1, int key2)
        {
            int key = key1 * 10000 + key2;
            if (allTableInstanceDic.ContainsKey(key) == false)
                return null;
            return allTableInstanceDic[key];
        }

        public Dictionary<string, string> GetTableDictionary(Type T, int key1, int key2)
        {
            return TableQuery.Select().From(tableDictionary).Where(GetKey1(), key1, GetKey2(), key2, Condition.EqualTo);
        }

        public Dictionary<string, string> GetTableDictionary(Type T, int key)
        {
            return TableQuery.Select().From(tableDictionary).Where(GetKey1(), key, Condition.EqualTo);
        }

        /// <summary>
        /// 获取配置表所有内容
        /// </summary>
        /// <typeparam name="T">类型</typeparam>
        /// <returns></returns>
        public List<T> GetTable<T>() where T : TableBase
        {
            List<T> list = new List<T>();

            //var ConfigItemVar = tableDictionary;
            foreach (KeyValuePair<int,TableBase> tb in allTableInstanceDic)
            {                
                list.Add(tb.Value as T);
            }

            return list;
        }

        /// <summary>
        /// 获取配置表所有内容
        /// </summary>
        /// <typeparam name="T">类型</typeparam>
        /// <returns></returns>
        public List<TableBase> GetTable(Type T)
        {
            List<TableBase> list = new List<TableBase>();
           
            //var ConfigItemVar = tableDictionary;
            foreach (KeyValuePair<int,TableBase> tb in allTableInstanceDic)
            {                
                list.Add(tb.Value);
            }            
            return list;
        }

        /// <summary>
        /// 深拷贝构造函数
        /// </summary>
        /// <param name="other"></param>
        public TableBase(TableBase other)
        {
            if (other == null)
            {
                Console.WriteLine("深拷贝表 " + this.GetType().FullName + "出错 other 是 null");
                return;
            }
            PropertyInfo[] property = this.GetType().GetProperties();
            foreach (PropertyInfo p in property)
            {
                p.SetValue(this, p.GetValue(other, null), null);
            }
        }
        public TableBase() { }
    }

    public class TableManager
    {
        public static event EventHandler AllTableLoaded;
        public static int TableRegistCount = 0;
        private static TableManager instance = null;
        public Dictionary<string, TableBase> dicConfigData = new Dictionary<string, TableBase>();
        public Dictionary<string, int[]> dicSceneBlockData = new Dictionary<string, int[]>();

        /// <summary>
        /// special type 类的构造方法参数必须是string类型
        /// </summary>
        public static Dictionary<string, bool> SpecialType = new Dictionary<string, bool>();

        public static TableManager Instance
        {
            get
            {
                if (instance == null)
                {
                    instance = new TableManager();
                }
                return instance;
            }
        }
        private TableManager() 
        {
           
        }

        public static T GetTableInstance<T>() where T : TableBase
        {
            Type t = typeof(T);
            if (Instance.dicConfigData.ContainsKey(t.ToString()))
            {
                return Instance.dicConfigData[t.ToString()] as T;
            }
            return null;
        }

        public static TableBase GetTableInstance(Type tp)
        {
            if (Instance.dicConfigData.ContainsKey(tp.ToString()))
            {
                return Instance.dicConfigData[tp.ToString()];
            }
            return null;
        }

        /// <summary>
        /// 登记游戏数据表
        /// </summary>
        /// <param name="config_obj"></param>
        /// <param name="sourceData">Editor下是表路径，其他情况下是直接从AssetBundle里读出来的数据</param>
        /// <param name="className"></param>
        public void RegisterTable(TableBase config_obj, string sourceData, string className)
        {
            //Editor下是表路径
            config_obj.SourcePath = sourceData;

            config_obj.TableName = className;
            config_obj.TableLoaded += config_obj_TableLoaded;
            config_obj.Loaded();
            string key = config_obj.GetType().FullName;
            if (!dicConfigData.ContainsKey(key))
            {
                dicConfigData.Add(key, config_obj);
            }

        }

        void config_obj_TableLoaded(object sender, EventArgs e)
        {
            if (AllTableLoaded != null)
            {
                AllTableLoaded(this, null);
            }
        }

        /// <summary>
        /// 按一个主键查询 
        /// </summary>
        /// <typeparam name="T">Table 类</typeparam>
        /// <param name="key">主键值</param>
        /// <returns></returns>
        public static T Select<T>(int key) where T : TableBase
        {
            string typeName = typeof(T).FullName;
            if (Instance.dicConfigData.ContainsKey(typeName))
            {
                return Instance.dicConfigData[typeName].Select<T>(key);
            }
            return null;
        }

        /// <summary>
        /// 按一个主键查询 
        /// </summary>
        /// <typeparam name="tableType">Table 类 Type</typeparam>
        /// <param name="key">主键值</param>
        /// <returns></returns>
        public static TableBase Select(Type tableType, int key)
        {
            string typeName = tableType.FullName;
            if (Instance.dicConfigData.ContainsKey(typeName))
            {
                return Instance.dicConfigData[typeName].Select(tableType, key);
            }
            return null;
        }

        /// <summary>
        /// 按两个主键查询
        /// </summary>
        /// <typeparam name="T">Table 类</typeparam>
        /// <param name="key1">主键1</param>
        /// <param name="key2">主键2</param>
        /// <returns></returns>
        public static T Select<T>(int key1, int key2) where T : TableBase
        {
            string typeName = typeof(T).FullName;
            if (Instance.dicConfigData.ContainsKey(typeName))
            {
                return Instance.dicConfigData[typeName].Select<T>(key1, key2);
            }
            return null;
        }

        /// <summary>
        /// 按两个主键查询
        /// </summary>
        /// <typeparam name="T">Table 类</typeparam>
        /// <param name="key1">主键1</param>
        /// <param name="key2">主键2</param>
        /// <returns></returns>
        public static TableBase Select(Type T, int key1, int key2)
        {
            string typeName = T.FullName;
            if (Instance.dicConfigData.ContainsKey(typeName))
            {
                return Instance.dicConfigData[typeName].Select(T, key1, key2);
            }
            return null;
        }

        public static TableBase Select(string tableName, int key)
        {
            if (Instance.dicConfigData.ContainsKey(tableName))
            {
                Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集 
                Type T = assembly.GetType(tableName);
                return Instance.dicConfigData[tableName].Select(T, key);
            }
            return null;
        }

        public static TableBase Select(string tableName, int key1, int key2)
        {
            if (Instance.dicConfigData.ContainsKey(tableName))
            {
                Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集 
                Type T = assembly.GetType(tableName);
                return Instance.dicConfigData[tableName].Select(T, key1, key2);
            }
            return null;
        }

        /// <summary>
        /// 获取表中的所有内容
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static List<T> GetTable<T>() where T : TableBase
        {
            string typeName = typeof(T).FullName;
            if (Instance.dicConfigData.ContainsKey(typeName))
            {
                return Instance.dicConfigData[typeName].GetTable<T>();
            }
            return null;
        }

        /// <summary>
        /// 获取表中的所有内容
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static List<TableBase> GetTable(Type T)
        {
            string typeName = T.FullName;
            if (Instance.dicConfigData.ContainsKey(typeName))
            {
                return Instance.dicConfigData[typeName].GetTable(T);
            }
            return null;
        }

        /// <summary>
        /// 获取表中的所有内容
        /// </summary>
        /// <returns></returns>
        public static List<TableBase> GetTable(string tableName)
        {
            if (Instance.dicConfigData.ContainsKey(tableName))
            {
                Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集 
                Type T = assembly.GetType(tableName);
                return Instance.dicConfigData[tableName].GetTable(T);
            }
            return null;
        }

        public static Dictionary<string, string> GetTableDictionary(string tableName, int key)
        {
            if (Instance.dicConfigData.ContainsKey(tableName))
            {
                Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集 
                Type T = assembly.GetType(tableName);
                return Instance.dicConfigData[tableName].GetTableDictionary(T, key);
            }
            return null;
        }

        public static Dictionary<string, string> GetTableDictionary(string tableName, int key1, int key2)
        {
            if (Instance.dicConfigData.ContainsKey(tableName))
            {
                Assembly assembly = Assembly.GetExecutingAssembly(); // 获取当前程序集 
                Type T = assembly.GetType(tableName);
                return Instance.dicConfigData[tableName].GetTableDictionary(T, key1, key2);
            }
            return null;
        }

    }
}