#ifndef TINYXML_UTIL
#define TINYXML_UTIL

#include "tinyxml.h"


class TinyXmlUtility
{
public:
	
	static const char* get_value(const char* key, TiXmlElement *item);
	
	static const char* get_value(TiXmlElement *item);
	
	static const char* get_attribute(TiXmlNode* node, const char* key);
	
	static bool insertBinaryData(TiXmlElement* parent, const char* keyname, int len, const unsigned char* data);
	
	static int getBinaryDataLen(TiXmlNode* node);
	
	static bool getBinaryData(TiXmlNode* node, int len, unsigned char* data);
};


#endif // TINYXML_UTIL

