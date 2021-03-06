#pragma once

#include "Future/Core.h"
#include "Future/Events/Event.h"

namespace Future
{
	class Layer
	{
	public:
		Layer(const std::string name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}
