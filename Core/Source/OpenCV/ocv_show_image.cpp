#include "ocv_show_image.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <windows.h>
#include <commdlg.h>
#include <iostream>

namespace ocv
{
    static std::string SelectFile()
    {
        char filename[MAX_PATH] = { 0 };

        OPENFILENAMEA ofn;
        ZeroMemory(&filename, sizeof(filename));
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter = "Supported Image files\0*.bmp;*.png;*.jpg\0All Files\0*\0\0";;
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Select a File, yo!";
        ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;

        if (GetOpenFileNameA(&ofn))
        {
            return(filename);
        }
        else
        {
            return("");
        }
    }

    void ShowImage()
    {
        std::string filename = SelectFile();
        cv::Mat img = cv::imread(filename);

        if (img.empty())
        {
            std::cout << "Could not open or find the image" << std::endl;
            std::cin.get(); //wait for any key press
            return;
        }

        cv::namedWindow("First OpenCV Application");
        cv::imshow("First OpenCV Application", img);
        cv::moveWindow("First OpenCV Application", 0, 45);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }
}