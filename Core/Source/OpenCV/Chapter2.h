#pragma once
#include <string>

namespace ocv
{
	static std::string SelectFile();
	void ShowImage();
	void ShowVideo();
	void ShowVideoAdvanced();
	void OnTrackbarSlide(int pos, void*);
	void ShowTransformedImage();
	void ShowDownsamplingImage();
	void ShowGrayScaleTransformedImage();
	void CaptureCamera(int cameraNo);
	void WriteAVIFile(std::string filename);

	class VideoControl
	{
	public:
		VideoControl();
		~VideoControl();

		void ShowAdvancedVideoWindow();
	public:
		int SliderPosition;
		int IsRun;
		int SingleStep;
	};
}