#pragma once
#include "Chapter2.h"
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <windows.h>
#include <commdlg.h>

cv::VideoCapture Cap;

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
        ofn.lpstrFilter = "Supported Image files\0*.bmp;*.png;*.jpg\0All Files\0*\0\0";
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Select a File.";
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
            //TODO: implement Logging
            return;
        }

        cv::namedWindow("Show Image", cv::WINDOW_AUTOSIZE);
        cv::imshow("Show Image", img);
        cv::moveWindow("Show Image", 500, 500);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    void ShowVideo()
    {
        std::string filename = SelectFile();
        cv::VideoCapture cap;
        cap.open(filename);
        cv::Mat frame;
        cv::namedWindow("Show Image", cv::WINDOW_AUTOSIZE);
        for (;;)
        {
            cap >> frame;
            if (frame.empty())
                break;

            cv::imshow("Show Image", frame);

            if (cv::waitKey(30) >= 0) 
                break;
        }
        cv::destroyAllWindows();
    }

    void OnTrackbarSlide(int pos, void* p_vc)
    {
        VideoControl* vc = static_cast<VideoControl*>(p_vc);

        Cap.set(cv::CAP_PROP_POS_FRAMES, vc->SliderPosition);
     
        if (!vc->SingleStep)
        {
            vc->IsRun = 1;
        }
        vc->SingleStep = 0;
    }

    void ShowTransformedImage()
    {
        //Import Image from selected Path
        std::string filename = SelectFile();
        cv::Mat img = cv::imread(filename);

        if (img.empty())
        {
            //TODO: implement Logging
            return;
        }


        //Create 2 new Windows representing the Image before and after Transformation
        cv::namedWindow("Show Image In", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Show Image Out", cv::WINDOW_AUTOSIZE);

        //show image before transformation
        cv::imshow("Show Image In", img);
        cv::moveWindow("Show Image In", 500, 500);

        //create variable to store image after transformation
        cv::Mat img_transformed;

        //Transform image 
        //do smoothing as example. possible functions -> blur(), GaussianBlur(), medianBlur(), bilateralFilter()
        cv::GaussianBlur(img, img_transformed, cv::Size(5,5), 3, 3);
        cv::GaussianBlur(img_transformed, img_transformed, cv::Size(5, 5), 3, 3); 
        //second Blur is there to demonstrate automatic memory allocation by OpenCV
        //NOTE: Kernel Size of the GaussianBlud should be odd -> GaussianKernel is calculated based on the center pixel in this area

        //show image after transformation
        cv::imshow("Show Image Out", img_transformed);
        cv::moveWindow("Show Image Out", 500, 500);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    void ShowDownsamplingImage()
    {
        //Import Image from selected Path
        std::string filename = SelectFile();
        cv::Mat img = cv::imread(filename);

        if (img.empty())
        {
            //TODO: implement Logging
            return;
        }

        //Create 2 new Windows representing the Image before and after Transformation
        cv::namedWindow("Show Downsampling Image In", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Show Downsampling Image Out", cv::WINDOW_AUTOSIZE);

        //show image before transformation
        cv::imshow("Show Downsampling Image In", img);
        cv::moveWindow("Show Downsampling Image In", 500, 500);

        //downsample image
        cv::Mat img_downsampled;
        cv::pyrDown(img, img_downsampled);

        //show image after transformation
        cv::imshow("Show Downsampling Image Out", img_downsampled);
        cv::moveWindow("Show Downsampling Image Out", 700, 500);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    void ShowGrayScaleTransformedImage()
    {
        //Import Image from selected Path
        std::string filename = SelectFile();
        cv::Mat img_rgb = cv::imread(filename);
        cv::Mat img_gray, img_cny, img_pyr, img_pyr2;

        if (img_rgb.empty())
        {
            //TODO: implement Logging
            return;
        }

        cv::namedWindow("Example Gray", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Example Canny", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Example Downsampling Canny", cv::WINDOW_AUTOSIZE);

        cv::cvtColor(img_rgb, img_gray, cv::COLOR_BGR2GRAY);
        cv::imshow("Example Gray", img_gray);
        cv::moveWindow("Example Gray", 500, 500);
        
        cv::Canny(img_gray, img_cny, 10, 100, 3, true);
        cv::imshow("Example Canny", img_cny);
        cv::moveWindow("Example Canny", 700, 500);

        cv::pyrDown(img_gray, img_pyr);
        cv::pyrDown(img_pyr, img_pyr2);
        cv::Canny(img_pyr2, img_cny, 10, 100, 3, true);
        cv::imshow("Example Downsampling Canny", img_cny);
        cv::moveWindow("Example Downsampling Canny", 900, 800);

        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    void CaptureCamera(int cameraNo = 1)
    {
        cv::VideoCapture vc;

        if (cameraNo == 1)
        {
            vc.open(0); //open first camera
        }
        else
        { //if no camera is selected open video file
            std::string filename = SelectFile();
            vc.open(filename);
        }

        if (!vc.isOpened()) //check if video from camera or file is opened
        {
            return;
        }
        cv::Mat frame;
        cv::namedWindow("Show Camera", cv::WINDOW_AUTOSIZE);
        for (;;)
        {
            vc >> frame;
            if (frame.empty())
                break;

            cv::imshow("Show Camera", frame);

            if (cv::waitKey(1) >= 0)
                break;
        }
        cv::destroyAllWindows();
    }

    void WriteAVIFile(std::string filename)
    {
        cv::namedWindow("Write AVI File", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Log_Polar", cv::WINDOW_AUTOSIZE);
        cv::VideoCapture vc(SelectFile());

        double fps = vc.get(cv::CAP_PROP_FPS);
        cv::Size size(
            (int)vc.get(cv::CAP_PROP_FRAME_WIDTH),
            (int)vc.get(cv::CAP_PROP_FRAME_HEIGHT)
        );

        cv::VideoWriter vw;
        vw.open(filename, cv::VideoWriter::fourcc('M', 'P', '4', 'V'), fps, size);
        cv::Mat logpolar_frame, bgr_frame;
        for (;;)
        {
            vc >> bgr_frame;
            if (bgr_frame.empty())
                break;

            cv::imshow("Write AVI File", bgr_frame);

            cv::logPolar(
                bgr_frame,                                          //Input color frame
                logpolar_frame,                                     //Output frame logpolar
                cv::Point2f(bgr_frame.cols/ 2, bgr_frame.rows/ 2),    //Centerpoint for log polar Transformation (x,y)
                40,                                                 //Magnitude (scale parameter)
                cv::WARP_FILL_OUTLIERS                              //Fill outliers with zero
            );

            cv::imshow("Log_Polar", logpolar_frame);
            vw << logpolar_frame;

            char c = (char)cv::waitKey(33);
            if (c == 27)
                break;
        }

        vc.release();
        cv::destroyAllWindows();
    }

    void ShowVideoAdvanced()
    {
        VideoControl vc = VideoControl();
        vc.ShowAdvancedVideoWindow();
    }

    VideoControl::VideoControl()
    {
        SliderPosition = 0;
        IsRun = 1;
        SingleStep = 0;
    }

    VideoControl::~VideoControl()
    {
        cv::destroyAllWindows();
    }


    void VideoControl::ShowAdvancedVideoWindow()
    {
        std::string filename = SelectFile();
        Cap.open(filename);
        int frames = (int)Cap.get(cv::CAP_PROP_FRAME_COUNT);
        int tmpw = (int)Cap.get(cv::CAP_PROP_FRAME_WIDTH);
        int tmph = (int)Cap.get(cv::CAP_PROP_FRAME_HEIGHT);

        cv::namedWindow("Show Video Advanced", cv::WINDOW_AUTOSIZE);
        cv::createTrackbar("Position", "Show Video Advanced", &SliderPosition, frames, OnTrackbarSlide, this);
        cv::Mat frame;

        for (;;)
        {
            if (IsRun != 0)
            {
                Cap >> frame;
                if (frame.empty())
                    break;
                int CurrPos = (int)Cap.get(cv::CAP_PROP_POS_FRAMES);
                SingleStep = 1;

                cv::setTrackbarPos("Position", "Show Video Advanced", CurrPos);
                cv::imshow("Show Video Advanced", frame);

                IsRun -= 1;
            }

            char c = cv::waitKey(10);
            if (c == 's') //single step
            {
                IsRun = 1; 
            }
            if (c == 'r') //single step
            {
                IsRun = -1;
            }
            if (c == 27) //single step
            {
                break;
            }
        }
    }
}