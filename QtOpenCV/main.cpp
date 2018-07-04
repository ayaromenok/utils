#include <iostream>
#include <opencv/cv.hpp>

using namespace std;

int main(int argc, char ** argv)
{
    cout << "Qt/OpenCV" << endl;
    cv::VideoCapture cap;

    if(argc==1){
        cap.open(0);
    } else
    {
        cap.open(argv[1]);
        cout << "add video as command-line argument\n";
    }
    if (!cap.isOpened()){
        cerr << "Couldn't open capture" << endl;
        return -1;
    }
    cv::namedWindow("VideoFromCamera", cv::WINDOW_AUTOSIZE);
    cv::Mat frame;

    for(;;) {
        cap >> frame;
        if (frame.empty())
            break;
        cv::imshow("VideoFromCamera", frame);
        if (cv::waitKey(33) >= 0) //ESC key
            break;
    }

    cv::destroyWindow("VideoFromCamera");
    return 0;
}
