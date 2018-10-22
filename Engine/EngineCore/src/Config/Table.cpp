//
//  Table.cpp

//  Created by 潘庆云 on 2017/2/7.
//

#include "Table.h"
namespace E3DEngine
{
	DECLARE_CLASS_NAME(BallEmitterConfig)
	DECLARE_CLASS_NAME(PointEmitterConfig)
	DECLARE_CLASS_NAME(AreaEmitterConfig)
	DECLARE_CLASS_NAME(LinnerForceAffectorConfig)
	DECLARE_CLASS_NAME(RandomForceAffectorConfig)
    DECLARE_CLASS_NAME(MoveToFiringPointForceAffectorConfig)
    DECLARE_CLASS_NAME(RotationForceAffectorConfig)
	DECLARE_CLASS_NAME(MaterialConfig)
	DECLARE_CLASS_NAME(TextureUVConfig)
	DECLARE_CLASS_NAME(LinnerColorAffectorConfig)
	DECLARE_CLASS_NAME(ParticleConfig)
	DECLARE_CLASS_NAME(RotationAffectorConfig)
	DECLARE_CLASS_NAME(SelfScalAffectorConfig)
	DECLARE_CLASS_NAME(SelfRotateAffectorConfig)
	DECLARE_CLASS_NAME(MeshConfig)
	DECLARE_CLASS_NAME(LayerConfig)
	DECLARE_CLASS_NAME(ShaderConfig)
	DECLARE_CLASS_NAME(TextureAtlas)
	DECLARE_CLASS_NAME(SkyBoxConfig)
	DECLARE_CLASS_NAME(RenderTextureConfig)
	
    void RegisterTableCreateInstance()
    {
        REGIST_CLASS(BallEmitterConfig);
        REGIST_CLASS(PointEmitterConfig);
        REGIST_CLASS(AreaEmitterConfig);
        REGIST_CLASS(LinnerForceAffectorConfig);
        REGIST_CLASS(RandomForceAffectorConfig);
        REGIST_CLASS(MoveToFiringPointForceAffectorConfig);
        REGIST_CLASS(RotationForceAffectorConfig);
        REGIST_CLASS(MaterialConfig);
        REGIST_CLASS(TextureUVConfig);
        REGIST_CLASS(LinnerColorAffectorConfig);
        REGIST_CLASS(ParticleConfig);
        REGIST_CLASS(RotationAffectorConfig);
        REGIST_CLASS(SelfScalAffectorConfig);
		REGIST_CLASS(SelfRotateAffectorConfig);
		REGIST_CLASS(MeshConfig);
		REGIST_CLASS(LayerConfig);
		REGIST_CLASS(ShaderConfig);
		REGIST_CLASS(TextureAtlas);
		REGIST_CLASS(SkyBoxConfig);
		REGIST_CLASS(RenderTextureConfig);
    }
}
