#include "tinyutil.h"

const char* TinyXmlUtility::get_value(const char* key, TiXmlElement *item)
{
	if(TiXmlElement* subitem = item->FirstChildElement(key))
	{
		return TinyXmlUtility::get_value(subitem);
	}
	else
		return 0;
}

const char* TinyXmlUtility::get_value(TiXmlElement *item)
{
	TiXmlNode *childNode = item->FirstChild();
	if ( childNode == NULL )
		return 0;
	TiXmlText *childText = childNode->ToText();
	if ( childText == NULL )
		return 0;

	return childText->Value();
}

const char* TinyXmlUtility::get_attribute(TiXmlNode* node, const char* key)
{
	TiXmlElement* ele = node->ToElement();
	if(ele)
	{
		return ele->Attribute(key);
	}
	else
		return 0;
}

static unsigned char a16ToByte(const char* str)
{
	if (!str) return 0;

	
	if (!str[0]) return 0;
	if (!str[1]) return 0;

	unsigned char result =  0;
	
	if (str[0] >= '0' && str[0] <= '9')
	{
		result = ((str[0] - '0') << 4) & 0xF0;
	}
	else if (str[0] >= 'A' && str[0] <= 'F')
	{
		result = ((10 + str[0] - 'A') << 4) & 0xF0;
	}
	else if (str[0] >= 'a' && str[0] <= 'f')
	{
		result = ((10 + str[0] - 'a') << 4) & 0xF0;
	}
	else
	{
		return 0;
	}
	
	if (str[1] >= '0' && str[1] <= '9')
	{
		result = result | ((str[1] - '0') & 0x0F);
	}
	else if (str[1] >= 'A' && str[1] <= 'F')
	{
		result = result | ((10 + str[1] - 'A') & 0x0F);
	}
	else if (str[1] >= 'a' && str[1] <= 'f')
	{
		result = result | ((10 + str[1] - 'a') & 0x0F);
	}
	else
	{
		return 0;
	}

	return result;
}

static bool byteToa16(unsigned char c, char* str)
{
	if (!str) return false;

	str[0] = '0';
	str[1] = '0';
	str[2] = 0;

	unsigned char ch = (c >> 4) & 0x0F;
	unsigned char cl = c & 0x0F;
	if (ch >= 0 && ch <= 9)
	{
		str[0] = '0' + ch;
	}
	else if (ch >= 10 && ch <= 15)
	{
		str[0] = 'A' + (ch - 10);
	}

	if (cl >= 0 && cl <= 9)
	{
		str[1] = '0' + cl;
	}
	else if (cl >= 10 && cl <= 15)
	{
		str[1] = 'A' + (cl - 10);
	}
	return true;
}
const char* DataLenAttrName = "Len";
const char* DataNodeName = "Data";
bool TinyXmlUtility::insertBinaryData(TiXmlElement* parent, const char* keyname, int len, const unsigned char* data)
{
	if (!parent) return false;
	if (!keyname) return false;
	if (!data) return false;
	if (len <= 0) return false;
	
	TiXmlElement keynode(keyname);
	keynode.SetAttribute(DataLenAttrName, len);
	
	char tempbuf[256 + 2] = {0};			
	char* tempp = tempbuf;
	int   tempacc = 0;
	
	for (int i = 0; i < len; i++)
	{							
		byteToa16(data[i], tempp);
		tempp += 2;
		tempacc += 2;
		if (tempacc >= 256)
		{				
			tempbuf[tempacc] = '\0';
			tempp = tempbuf;
			tempacc = 0;	

			TiXmlElement datanode(DataNodeName);

			TiXmlText textnode(tempbuf);
			datanode.InsertEndChild(textnode);

			keynode.InsertEndChild(datanode);
		}
	}		
	
	if (tempacc > 0)
	{
		tempbuf[tempacc] = '\0';
		tempp = tempbuf;
		tempacc = 0;

		TiXmlElement datanode(DataNodeName);

		TiXmlText textnode(tempbuf);
		datanode.InsertEndChild(textnode);

		keynode.InsertEndChild(datanode);
	}
	
	parent->InsertEndChild(keynode);

	return true;
}
int TinyXmlUtility::getBinaryDataLen(TiXmlNode* node)
{
	if (!node) return 0;
	TiXmlElement* ele = node->ToElement();
	if(!ele) return 0;

	int result = 0;
	ele->Attribute(DataLenAttrName, &result);
	return result;
}
bool TinyXmlUtility::getBinaryData(TiXmlNode* node, int len, unsigned char* data)
{
	if (!node) return false;
	if (!data) return false;
	if (len <= 0) return false;
	
	int tempacc = 0;
	TiXmlNode* datanode = node->FirstChild(DataNodeName);
	for (; datanode; datanode = datanode->NextSibling(DataNodeName))
	{
		TiXmlElement* ele = datanode->ToElement();
		if (!ele) continue;

		if(const char* v = get_value(ele))
		{
			const char* temp = v;
			
			while (temp[0] && temp[1] && tempacc < len)
			{
				data[tempacc] = a16ToByte(temp);
				tempacc++;
				temp += 2;
			}							
		}						
	}

	return true;
}
