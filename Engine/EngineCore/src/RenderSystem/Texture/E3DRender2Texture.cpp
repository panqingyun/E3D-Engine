#include "E3DRender2Texture.h"

E3DEngine::Render2Texture::Render2Texture()
{
	mBehaviour->SetImage(MonoScriptManager::GetInstance().GetEngineImage());
	NEW_INSTANCE(RenderTexture);
	Object::setBehaviourDefaultValue();
}

E3DEngine::Render2Texture::~Render2Texture()
{
	
}

float E3DEngine::Render2Texture::GetWidth()
{
	return m_nWidth;
}

float E3DEngine::Render2Texture::GetHeight()
{
	return m_nHeight;
}
