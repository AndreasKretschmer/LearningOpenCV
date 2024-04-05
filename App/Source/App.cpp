#include "Core/Application.h"
#include "Core/Main.h"

locv::Application* locv::CreateApplication(int argc, char** argv)
{
	locv::ApplicationSpecification spec;
	spec.Name = "Learning OpenCV Example";

	locv::Application* app = new locv::Application(spec);
	//app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});
	return app;
}