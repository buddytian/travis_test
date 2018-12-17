/*
author:t00192666
version:1.01
Function: OSD common test
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include "OsdDataType.h"
#include "OsdApi.h"
#include "DvppProcess.h"


using namespace Ascend;
using namespace Osd;
using namespace std;


#define WIDTH	1280
#define HEIGHT	720
const int framesize = WIDTH * HEIGHT * 3 / 2;

int main(int argc,char *argv[])
{
    bool isDrawOutJPG=true;//t00192666
    std::shared_ptr<uint8_t> pYuvBuf_dst(new uint8_t[framesize]);
    uint8_t * image_buffer_ptr1 = (uint8_t*) (new uint8_t[framesize]);


    FILE* fileIn = fopen("/root/osd/0000000017.yuv.nv12", "rb+");
    fread(image_buffer_ptr1, framesize*sizeof(uint8_t), 1, fileIn);
    std::shared_ptr<uint8_t> pYuvBuf_src(image_buffer_ptr1);

    ImageAttribute *image_attr=new ImageAttribute;
    //image_attr->imageFormat=YUV420SPNV12;
    image_attr->width=WIDTH;
    image_attr->height=HEIGHT;
    image_attr->size=framesize;
    image_attr->data=pYuvBuf_src;
    string default_attr = std::string(argv[3]);
    if (atoi(argv[2]) == 0)
    {
        image_attr->imageFormat=YUV420SPNV12;
    }
    else
    {
        image_attr->imageFormat=IMAGE_INVALID;
    }
    if (atoi(argv[1]) == 1)
    {
        int ltx=atoi(argv[4]);
        int lty=atoi(argv[5]);
        int rbx=atoi(argv[6]);
        int rby=atoi(argv[7]);
        int rred=0;
        int rgreen=0;
        int rblue=0;
        int thinkness=0;
        int linetype=0;
        RectangleAttribute rec_attr;
        rec_attr.position.lt.x=ltx;
        rec_attr.position.lt.y=lty;
        rec_attr.position.rb.x=rbx;
        rec_attr.position.rb.y=rby;
        std::vector<RectangleAttribute> rectAttrs;//t00192666
	if (0 == default_attr.compare("ALL"))
        {
            rred=atoi(argv[8]);
            rgreen=atoi(argv[9]);
            rblue=atoi(argv[10]);
            thinkness=atoi(argv[11]);
            linetype=atoi(argv[12]); 
            rec_attr.color.red=rred;
            rec_attr.color.green=rgreen;
            rec_attr.color.blue=rblue;
            rec_attr.thickness=thinkness;
            rec_attr.lineType=linetype;
            //t00192666std::cout << "ALL" << std::endl;
        }
        else if (0 == default_attr.compare("DEFAULT_COLOR"))
        {
            thinkness=atoi(argv[8]);
            linetype=atoi(argv[9]);
            rec_attr.thickness=thinkness;
            rec_attr.lineType=linetype;
            //t00192666std::cout << "DEFAULT_COLOR" << std::endl;
        }
        else if (0 == default_attr.compare("DEFAULT_THICK"))
        {
            rred=atoi(argv[8]);
            rgreen=atoi(argv[9]);
            rblue=atoi(argv[10]);
            linetype=atoi(argv[11]);
            rec_attr.color.red=rred;
            rec_attr.color.green=rgreen;
            rec_attr.color.blue=rblue;
            rec_attr.lineType=linetype;
            //t00192666std::cout << "DEFAULT_THICK" << std::endl;
        }
        else if (0 == default_attr.compare("DEFAULT_LINETYPE"))
        {
            rred=atoi(argv[8]);
            rgreen=atoi(argv[9]);
            rblue=atoi(argv[10]);
            thinkness=atoi(argv[11]);
            rec_attr.color.red=rred;
            rec_attr.color.green=rgreen;
            rec_attr.color.blue=rblue;
            rec_attr.thickness=thinkness;
            //t00192666std::cout << "DEFAULT_LINETYPE" << std::endl;
        }
        else
        {}

        // cv::rectangle(mat,cvPoint(ltx,lty),cvPoint(rbx,rby),CV_RGB(red, green, blue), thinkness, linetype, 0); //画矩形框
        //std::vector<RectangleAttribute> rectAttrs;
        if (0 != default_attr.compare("EMPTY_RECT"))//t00192666
        {
            rectAttrs.push_back(rec_attr);
        }
        int m_result=DrawRectangle(*image_attr,rectAttrs,pYuvBuf_dst); 
        if (0 == m_result)
        {
            std::cout << "[INFO]DrawRectangle successfully" << std::endl;
        }
        else
        {
            isDrawOutJPG=false;//t00192666
            std::cout << "[ERROR]DrawRectangle failed" << std::endl;
            //exit;
        }
    }
    else if (atoi(argv[1]) == 2)
    {
        std::string title;
        int tx = 0;
        int ty = 0;        
        int ftype = 0;
        double fscale = 0.0;
        int fred = 0;   
        int fgreen = 0;
        int fblue = 0;
        int fthick = 0;
        int flinetype = 0;
        std::vector<TextAttribute> textAttrs;
        TextAttribute text_attr;
        if (0 == default_attr.compare("ALL"))
        {
            title=std::string(argv[4]);
            tx = atoi(argv[5]);
            ty = atoi(argv[6]);
            ftype=atoi(argv[7]);
            fscale=atof(argv[8]);
            fred=atoi(argv[9]);
            fgreen=atoi(argv[10]);
            fblue=atoi(argv[11]);
            fthick=atoi(argv[12]);
            flinetype=atoi(argv[13]);
            text_attr.text=title;
            text_attr.position.x=tx;
            text_attr.position.y=ty;
            text_attr.fontType=FontType(ftype);
            text_attr.color.red=fred;
            text_attr.color.green=fgreen;
            text_attr.color.blue=fblue;
            text_attr.fontScale=fscale;
            text_attr.thickness=fthick;
            text_attr.lineType=flinetype;
        }
        else if (0 == default_attr.compare("EMPTY_TITLE"))
        {
            title=std::string("");
            tx = atoi(argv[4]);
            ty = atoi(argv[5]);
            ftype=atoi(argv[6]);
            fscale=atof(argv[7]);
            fred=atoi(argv[8]);
            fgreen=atoi(argv[9]);
            fblue=atoi(argv[10]);
            fthick=atoi(argv[11]);
            flinetype=atoi(argv[12]);
            text_attr.text=title;
            text_attr.position.x=tx;
            text_attr.position.y=ty;
            text_attr.fontType=FontType(ftype);
            text_attr.color.red=fred;
            text_attr.color.green=fgreen;
            text_attr.color.blue=fblue;
            text_attr.fontScale=fscale;
            text_attr.thickness=fthick;
            text_attr.lineType=flinetype;
        }
        
