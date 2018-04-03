#ifndef __UI_SYSTEM_H__
#define __UI_SYSTEM_H__

#include "../Source/Interface.h"

namespace E3DEngine
{
	namespace UI
	{
		class UISystem : public ISystem
		{
		public:
			UISystem();
			~UISystem();

		public:
			//virtual void Update(float deltaTime) override;
			virtual void Initilize() override;
			virtual void Destory() override;
			virtual std::string  GetName() override;

		private:

		};
	}
}

#endif
