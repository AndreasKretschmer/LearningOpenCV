#pragma once

#ifdef WINDOWS_PLATFORM

extern locv::Application* locv::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace locv {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			locv::Application* app = locv::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

int main(int argc, char** argv)
{
	return locv::Main(argc, argv);
}

#endif // WINDOWS_PLATFORM