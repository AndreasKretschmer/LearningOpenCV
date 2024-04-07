#include "Core/Application.h"
#include "OpenCV/LearningOpenCVChapters.h"

class MenuLayer : public locv::Layer
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

				if (ImGui::Selectable("Show simple Image", selected == 1))
				{
					selected = 1;
					ocv::ShowImage();
				}
				if (ImGui::Selectable("Show Video", selected == 2))
				{
					selected = 2;
					ocv::ShowVideo();
				}
				if (ImGui::Selectable("Show Video Advanced", selected == 3))
				{
					selected = 3;
					ocv::ShowVideoAdvanced();
				}
				if (ImGui::Selectable("A simple Transformation", selected == 4))
				{
					selected = 4;
					ocv::ShowTransformedImage();
				}
				if (ImGui::Selectable("A downsampling Transformation", selected == 5))
				{
					selected = 5;
					ocv::ShowDownsamplingImage();
				}
				if (ImGui::Selectable("A grayscale Transformation", selected == 6))
				{
					selected = 6;
					ocv::ShowGrayScaleTransformedImage();
				}
				if (ImGui::Selectable("Camera Example", selected == 7))
				{
					selected = 7;
					ocv::CaptureCamera(1);
				}
				if (ImGui::Selectable("Writing to an AVI File", selected == 8))
				{
					selected = 8;
					ocv::WriteAVIFile("Test.mp4");
				}
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::End();
	}
};