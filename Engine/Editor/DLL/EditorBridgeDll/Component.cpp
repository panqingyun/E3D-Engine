#include "Component.h"

#pragma managed

#include <msclr\marshal_cppstd.h>
using namespace msclr::interop;
namespace E3DEngine
{

	ComponentRef::ComponentRef(Component *component)
	{
		mComponentFieldMap = gcnew System::Collections::Generic::List<ComponentField ^>();
		SetValue(component);
	}

	void ComponentRef::SetValue(Component *component)
	{
		mComponent = component;
		mName = gcnew System::String(component->mName.c_str());
		mFullName = gcnew System::String(component->mTypeName.c_str());
		mComponentFieldMap->Clear();
		for (auto &field : component->m_propertyTypeMap)
		{
			ComponentField ^comField = gcnew ComponentField();
			comField->Name = gcnew System::String(field.first.c_str());
			comField->Type = field.second;
			comField->Value = gcnew System::String(component->GetFieldValueStr(field.first).c_str());
			comField->Component = this;
			mComponentFieldMap->Add(comField);
		}
	}

	System::Collections::Generic::List<ComponentField^>^ ComponentRef::GetFields()
	{
		return mComponentFieldMap;
	}

	System::String^ ComponentRef::GetName()
	{
		return mName;
	}

	System::String^ ComponentRef::GetFullName()
	{
		return mFullName;
	}

	E3DEngine::Component * ComponentRef::GetComponentPtr()
	{
		return mComponent;
	}

	void ComponentRef::SetFielValue(System::String ^name, System::String ^value)
	{
		mComponent->SetFieldValue(marshal_as<std::string>(name), marshal_as<std::string>(value));
	}

	bool ComponentRef::GetIsActive()
	{
		return mComponent->IsActive;
	}

	void ComponentRef::SetActive(bool active)
	{
		mComponent->SetActive(active);
	}

	void ComponentField::SetValue(System::String ^value)
	{
		Value = value;
		Component->SetFielValue(Name, value);
	}

}

#pragma unmanaged