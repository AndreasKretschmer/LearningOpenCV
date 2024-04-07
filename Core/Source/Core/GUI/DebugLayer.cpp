#include "Core/Application.h"

class DebugLayer : public locv::Layer
{
public:
	virtual void OnUIRender() override
	{
		//TODO: implement own logging
		//ImGui::ShowDebugLogWindow(NULL);
	}
};