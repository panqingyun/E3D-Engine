//
//  E3DMaterialManager.cpp
//
//  Created by 潘庆云 on 2017/7/17.
//

#include "E3DGLESMaterialManager.hpp"
#include "src/Source/Helpers.h"
#include "E3DGLESMaterial.hpp"

namespace E3DEngine
{
	GLES_MaterialManager::GLES_MaterialManager()
	{
		m_BlendFactorMap[ZERO] = GL_ZERO;
		m_BlendFactorMap[ONE] = GL_ONE;
		m_BlendFactorMap[SRC_COLOR] = GL_SRC_COLOR;
		m_BlendFactorMap[ONE_MINUS_SRC_COLOR] = GL_ONE_MINUS_SRC_COLOR;
		m_BlendFactorMap[SRC_ALPHA] = GL_SRC_ALPHA;
		m_BlendFactorMap[ONE_MINUS_SRC_ALPHA] = GL_ONE_MINUS_SRC_ALPHA;
		m_BlendFactorMap[DST_ALPHA] = GL_DST_ALPHA;
		m_BlendFactorMap[ONE_MINUS_DST_ALPHA] = GL_ONE_MINUS_DST_ALPHA;
		m_BlendFactorMap[DST_COLOR] = GL_DST_COLOR;
		m_BlendFactorMap[ONE_MINUS_DST_COLOR] = GL_ONE_MINUS_DST_COLOR;
	}


	E3DEngine::Material * GLES_MaterialManager::createMatrerial()
	{
		return new GLES_Material();
	}
}
