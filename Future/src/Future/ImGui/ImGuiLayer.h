#pragma once

#include <Future/Layer.h>
#include "Future/Events/ApplicationEvent.h"

namespace Future
{
	class FUTURE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}



