////
////  DynamicRectangle.hpp
////
////  Created by 潘庆云 on 2017/7/25.
////
//
//#ifndef DynamicRectangle_hpp
//#define DynamicRectangle_hpp
//
//#include "E3DRenderObject.hpp"
//#include "../ParticleSystem/E3DParticle.h"
//#include "../Source/EngineDelegate.h"
//#include "../Source/E3DDelegate.h"
//
//#define LONG_TIME 9999999
//
//namespace E3DEngine
//{
//	class DynamicRectangle : public GameObject
//	{
//	private:
//		DynamicRectangle()
//		{
//			NodeType = eT_MagicWord;
//		}
//	public:
//		static DynamicRectangle * CreateInstance(Object * parent);
//		virtual ~DynamicRectangle() override;
//		void Init();
//		void Create(float perWidth, float perHeight, vec3f centerPosition, vec2f uv, vec2f wh);
//        void CreateTextShadow(float perWidth, float perHeight, vec3f centerPosition, vec2f uv, vec2f wh);
//		void CreateComplete();
//		void SetMaterial(Material * material);
//		std::vector<Particle*> *GetElements();
//        std::vector<Particle*> *GetShadowElements();
//		void Move(vec3f newPos);
//		void Scale(vec3f scale);
//		void Rotate(vec3f rotate);
//		void SetUV(vec2f uv);
//		virtual void AfterUpdate(float deltaTime) override;
//		virtual void SetActive(bool isActive) override;
//	public:
//		void Pause(bool bPause);        
//        void Enable(bool bEnable);
//		virtual void SetDontDestory(bool dontDestory) override;
//
//		event EventDelegates PauseEffectDelegate;
//		event EventDelegates EnableEffectDelegate;
//	private:
//		std::vector<Particle*>	  m_vecWords;
//        std::vector<Particle*>	  m_vecWordShadows;
//		Renderer			*	  m_pRender;
//		uint					  m_nMaterialID;
//		uint					  vertexStartIndex;
//		int ivertexTotal;
//		int iindexTotal;
//        
//	};
//}
//
//#endif /* DynamicRectangle_hpp */
