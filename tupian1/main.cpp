#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>
#include<algorithm>
using namespace std;
using namespace cv;
//剩余按键事件
Mat frame;
Mat number_five;
Mat number_nine;
Mat number_nine_fire;
Mat mask_five;
Mat mask_nine;
Mat mask_nine_fire;
Mat five_frame_roi;
Mat nine_frame_roi;
Mat nine_frame_roi_fire;
Mat frame_red;
int flag=0;
int nine_number_flag;
//__________两边红蓝方块显示_________________//
void rect_red(Mat frame)//red
{
    for(int i=0;i<5;i++)
    {
        rectangle(frame,Rect(50,260+i*150,100,30),Scalar(0,0,255),-1,0,0);
        rectangle(frame,Rect(1210,260+i*150,100,30),Scalar(0,0,255),-1,0,0);
    }
}

void rect_blue(Mat frame)//blue
{
    for(int i=0;i<5;i++)
    {
        rectangle(frame,Rect(50,260+i*150,100,30),Scalar(255,0,0),-1,0,0);
        rectangle(frame,Rect(1210,260+i*150,100,30),Scalar(255,0,0),-1,0,0);
    }
}

//__________显示晶体管数字随机显示_______________//
void _number_five(Mat frame)
{
    char Filename[100];
    int number_radom[5];
    char Windowname[100];
    for (int i = 1; i <= 5; i++)
    {
        number_radom[i]=i;
    }
    for (int i = 5; i >= 1; i--)//没法显示在正中间（算法问题
    {
        swap(number_radom[i],number_radom[rand()%i+1]);
        sprintf(Filename, "/home/joyce/下载/rune_simulation/%d.png", number_radom[i]);
        sprintf(Windowname, "Img%d", number_radom[i]);
        number_five = imread(Filename);
//        frame_roi=frame(Rect((frame.cols-5*number.cols/2)+i*number.cols,30,number.cols,number.rows));
        five_frame_roi=frame(Rect(300+i*100,30,number_five.cols,number_five.rows));

        mask_five=imread(Filename,0);
        number_five.copyTo(five_frame_roi,mask_five);
     }
}

//___________九宫格手写数字随机显示____________//
void _number_nine(Mat frame)
{
    char Filename1[100];
    int nine_radom[96];
    int nine_what_number[9];
    for (int i = 1; i <= 9; i++)
    {
        nine_what_number[i]=i;
    }

    for (int i = 9; i >= 1; i--)//九宫格(贴图//非火焰数字
    {
        swap(nine_what_number[i],nine_what_number[rand()%i+1]);
        nine_radom[i]=rand()%95+1;
        sprintf(Filename1, "/home/joyce/下载/rune_simulation/rm_pics/newsudoku/%d/%d.png",nine_what_number[i],nine_radom[i]);
        number_nine = imread(Filename1);
        resize(number_nine,number_nine,Size(frame.rows/6,frame.cols/7));//把图片裁减一下
        if(i>=7)
        {
            nine_frame_roi=frame(Rect(i*300-1820,260,number_nine.cols,number_nine.rows));//i*x=两张图的图距
        }
        else if (i<7&&i>3)
        {
            nine_frame_roi=frame(Rect((i+3)*300-1820,500,number_nine.cols,number_nine.rows));
        }
        else
        {
            nine_frame_roi=frame(Rect((i+6)*300-1820,740,number_nine.cols,number_nine.rows));
        }
        mask_nine=imread(Filename1,0);
        resize(mask_nine,mask_nine,Size(frame.rows/6,frame.cols/7));

        number_nine.copyTo(nine_frame_roi,mask_nine);
    }

}

int main()
{
    //1920x1080//1380x1440
    frame=Mat(1020,1340,CV_8UC3,Scalar(0,0,0));
    srand(time(NULL));
    int red_blue_output=rand()%2;//一开始随机出现的颜色,0为red，1为blue
    _number_five(frame);
    _number_nine(frame);

//    int key1=waitKey(0);

    if(red_blue_output==0)//程序开始时两侧随机显示方块颜色
    {
        rect_red(frame);
    }
    else if(red_blue_output==1)
    {
        rect_blue(frame);
    }

//    int flag1;
//    cin>>flag1;
//    int key;
//    for(int i=0;i<30;i++)
//    {
////        cin>>flag1;
//        key=waitKey(0);
//        if(key==27)
//        {
//            rect_red(frame);
//            imshow("frame",frame);
////            waitKey(0);

//        }
//        else
//        {
//            rect_blue(frame);
//            imshow("frame",frame);
////            waitKey(0);
//        }

//    }
//    _number_five(frame);

//    nine_number_out(frame);

//    char key=waitKey(0);
//    do
    /*while(1)
    {
//        if(red_blue_output==0)//程序开始时两侧随机显示方块颜色
//        {
//            rect_red(frame);
//            imshow("frame",frame);
//        }
//        else
//        {
//            rect_blue(frame);
//            imshow("frame",frame);

//        }
//        imshow("frame",frame);
//        waitKey(0);
        if(key==27)//按‘3’切换两侧方块颜色
        {
            rect_blue(frame);
            imshow("frame",frame);

//            break;
        }
        else
        {
             rect_red(frame);
             imshow("frame",frame);
//             break;
        }
        waitKey(1000);
//        switch (key)
//        {
//            case 51:
//                number_five(frame);
//                  rect_blue(frame);
//                  imshow("frame",frame);
//                  waitKey(0);
//            break;
//            default:
//            if(key==27)
//            {
//                break;
//            }
//                imshow("frame",frame);

//                break;
//        }
//        cin>>flag;
    }*/
//    while (key==27);


//    number=imread("/home/joyce/下载/rune_simulation/1.png");

    imshow("frame",frame);
    waitKey(0);

//    if(char(waitKey(0))=='1')
//    {
//        rect_red(frame);
        return 0;
//    }

}

