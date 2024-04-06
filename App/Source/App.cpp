#include "Core/Application.h"
#include "Core/Main.h"
#include "OpenCV/ocv_show_image.h"

class ExampleLayer : public locv::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGuiWindowFlags window_flags = 0;
		window_flags |= ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoCollapse;
		//window_flags |= ImGuiWindowFlags_NoDocking;
		//window_flags |= ImGuiWindowFlags_NoResize;

		ImGui::Begin("OpenCV Chapters", NULL, window_flags);
		if (ImGui::TreeNode("Chapters"))
		{
			if (ImGui::TreeNode("Chapter 2"))
			{
				static int selected = -1;

				if (ImGui::Selectable("My First OpenCV Program", selected == 1))
				{
					selected = 1;
					ocv::ShowImage();
				}
				if (ImGui::Selectable("My Second OpenCV Program", selected == 2))
					selected = 2;
				if (ImGui::Selectable("My Third OpenCV Program", selected == 3))
					selected = 3;
				if (ImGui::Selectable("My Fourth OpenCV Program", selected == 4))
					selected = 4;
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

locv::Application* locv::CreateApplication(int argc, char** argv)
{
	locv::ApplicationSpecification spec;
	spec.Name = "Learning OpenCV Example";

	locv::Application* app = new locv::Application(spec);
	app->PushLayer<ExampleLayer>();
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