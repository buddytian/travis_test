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
        else if (0 == default_attr.compare("DEFAULT_FONT"))
        {
            title=std::string(argv[4]);
            tx = atoi(argv[5]);
            ty = atoi(argv[6]);
            //ftype=atoi(argv[6]);
            fscale=atof(argv[7]);
            fred=atoi(argv[8]);
            fgreen=atoi(argv[9]);
            fblue=atoi(argv[10]);
            fthick=atoi(argv[11]);
            flinetype=atoi(argv[12]);
            text_attr.text=title;
            text_attr.position.x=tx;
            text_attr.position.y=ty;
            //text_attr.fontType=FontType(ftype);
            text_attr.color.red=fred;
            text_attr.color.green=fgreen;
            text_attr.color.blue=fblue;
            text_attr.fontScale=fscale;
            text_attr.thickness=fthick;
            text_attr.lineType=flinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_SCALE"))
        {
            title=std::string(argv[4]);
            tx = atoi(argv[5]);
            ty = atoi(argv[6]);
            ftype=atoi(argv[7]);
            // fscale=atof(argv[7]);
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
            //text_attr.fontScale=fscale;
            text_attr.thickness=fthick;
            text_attr.lineType=flinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_COLOR"))
        {
            title=std::string(argv[4]);
            tx = atoi(argv[5]);
            ty = atoi(argv[6]);
            ftype=atoi(argv[7]);
            fscale=atof(argv[8]);
            //fred=atoi(argv[8]);
            //fgreen=atoi(argv[9]);
            //fblue=atoi(argv[10]);
            fthick=atoi(argv[9]);
            flinetype=atoi(argv[10]);
            text_attr.text=title;
            text_attr.position.x=tx;
            text_attr.position.y=ty;
            text_attr.fontType=FontType(ftype);
            //text_attr.color.red=fred;
            //text_attr.color.green=fgreen;
            //text_attr.color.blue=fblue;
            text_attr.fontScale=fscale;
            text_attr.thickness=fthick;
            text_attr.lineType=flinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_THICK"))
        {
            title=std::string(argv[4]);
            tx = atoi(argv[5]);
            ty = atoi(argv[6]);
            ftype=atoi(argv[7]);
            fscale=atof(argv[8]);
            fred=atoi(argv[9]);
            fgreen=atoi(argv[10]);
            fblue=atoi(argv[11]);
            //fthick=atoi(argv[11]);
            flinetype=atoi(argv[12]);
            text_attr.text=title;
            text_attr.position.x=tx;
            text_attr.position.y=ty;
            text_attr.fontType=FontType(ftype);
            text_attr.color.red=fred;
            text_attr.color.green=fgreen;
            text_attr.color.blue=fblue;
            text_attr.fontScale=fscale;
            //text_attr.thickness=fthick;
            text_attr.lineType=flinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_LINETYPE"))
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
            //flinetype=atoi(argv[12]);
            text_attr.text=title;
            text_attr.position.x=tx;
            text_attr.position.y=ty;
            text_attr.fontType=FontType(ftype);
            text_attr.color.red=fred;
            text_attr.color.green=fgreen;
            text_attr.color.blue=fblue;
            text_attr.fontScale=fscale;
            text_attr.thickness=fthick;
            //text_attr.lineType=flinetype;
        }
        //cv::putText(mat, title, cvPoint(tx, ty), ftype, fscale, CV_RGB(fred, fgreen, fblue), fthick, flinetype, 0);
        if (0 != default_attr.compare("EMPTY_TEXT"))//t00192666
        {
            textAttrs.push_back(text_attr);
        }

        int m_result=PutText(*image_attr,textAttrs,pYuvBuf_dst);
        if (0 == m_result)
        {
            std::cout << "[INFO]PutText successfully" << std::endl;
        }
        else
        {
            isDrawOutJPG=false;
            std::cout << "[ERROR]PutText failed" << std::endl;
            //exit;
        }

    }
    else if (atoi(argv[1]) == 3)
    {
        CircleAttribute cir_attr;
        int cx = atoi(argv[4]);
        int cy = atoi(argv[5]);
        int Radius = atoi(argv[6]);
        int cred = 0;
        int cgreen = 0;
        int cblue = 0;
        int cthickness = 0;
        int clinetype = 0;
        cir_attr.center.x=cx;
        cir_attr.center.y=cy;
        cir_attr.radius=Radius;
        std::vector<CircleAttribute> cirAttrs;
        if (0 == default_attr.compare("ALL"))
        {
            cred=atoi(argv[7]);
            cgreen=atoi(argv[8]);
            cblue=atoi(argv[9]);
            cthickness=atoi(argv[10]);
            clinetype=atoi(argv[11]);
            cir_attr.color.red=cred;
            cir_attr.color.green=cgreen;
            cir_attr.color.blue=cblue;
            cir_attr.thickness=cthickness;
            cir_attr.lineType=clinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_COLOR"))
        {
            cthickness=atoi(argv[7]);
            clinetype=atoi(argv[8]);
            cir_attr.thickness=cthickness;
            cir_attr.lineType=clinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_THICK"))
        {
            cred=atoi(argv[7]);
            cgreen=atoi(argv[8]);
            cblue=atoi(argv[9]);
            clinetype=atoi(argv[10]);
            cir_attr.color.red=cred;
            cir_attr.color.green=cgreen;
            cir_attr.color.blue=cblue;
            cir_attr.lineType=clinetype;
        }
        else if (0 == default_attr.compare("DEFAULT_LINETYPE"))
        {
            cred=atoi(argv[7]);
            cgreen=atoi(argv[8]);
            cblue=atoi(argv[9]);
            cthickness=atoi(argv[10]);
            cir_attr.color.red=cred;
            cir_attr.color.green=cgreen;
            cir_attr.color.blue=cblue;
            cir_attr.thickness=cthickness;
        }
        //cv::circle(mat, cvPoint(cx, cy), Radius, CV_RGB(cred, cgreen, cblue), cthickness, clinetype, 0);
        if (0 != default_attr.compare("EMPTY_CIRCLE"))
        {
            cirAttrs.push_back(cir_attr);
        }
        int m_result = DrawCircle(*image_attr,cirAttrs,pYuvBuf_dst);
        if (0 == m_result)
        {
            std::cout << "[INFO]DrawCircle successfully" << std::endl;
        }
        else
        {
            isDrawOutJPG=false;
            std::cout << "[ERROR]DrawCircle failed" << std::endl;
            //exit;
        }
    }
    else if (atoi(argv[1]) == 4)
    {
        RectangleLabelAttribute reclab_Attr;
        TextAttribute text_attr;          
        std::vector<RectangleAttribute> rectAttrs;     
        std::vector<TextAttribute> textAttrs;  
        std::vector<RectangleLabelAttribute> rectLabelAttrs;                 
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
            
            title=std::string(argv[13]);
            tx = atoi(argv[14]);
            ty = atoi(argv[15]);
            ftype=atoi(argv[16]);
            fscale=atof(argv[17]);
            fred=atoi(argv[18]);
            fgreen=atoi(argv[19]);
            fblue=atoi(argv[20]);
            fthick=atoi(argv[21]);
            flinetype=atoi(argv[22]);
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
            
            reclab_Attr.rectAttr=rec_attr;
            reclab_Attr.textAttr=text_attr;   
            rectLabelAttrs.push_back(reclab_Attr);                              
        }
        else if (0 == default_attr.compare("EMPTY_RECLAB"))
        {
            reclab_Attr.rectAttr=rec_attr;
            reclab_Attr.textAttr=text_attr;              
        }
        else if (0 == default_attr.compare("EMPTY_LAB"))
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

            reclab_Attr.rectAttr=rec_attr;
            rectLabelAttrs.push_back(reclab_Attr);
        }
        else if (0 == default_attr.compare("EMPTY_REC"))
        {
            title=std::string(argv[13]);
            tx = atoi(argv[14]);
            ty = atoi(argv[15]);
            ftype=atoi(argv[16]);
            fscale=atof(argv[17]);
            fred=atoi(argv[18]);
            fgreen=atoi(argv[19]);
            fblue=atoi(argv[20]);
            fthick=atoi(argv[21]);
            flinetype=atoi(argv[22]);
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

            reclab_Attr.textAttr=text_attr;
            rectLabelAttrs.push_back(reclab_Attr);
        }


        int m_result=DrawRectangleAndLabel(*image_attr,rectLabelAttrs,pYuvBuf_dst);
        if (0 == m_result)
        {
            std::cout << "[INFO]DrawRectanglelabel successfully" << std::endl;
        }
        else
        {
            isDrawOutJPG=false;
            std::cout << "[ERROR]DrawRectanglelabel failed" << std::endl;
            //exit;
        }
        
    }
    else
    {
        isDrawOutJPG=false;
        std::cout << "[WARN]Drawtype not supported!" << std::endl;
        //exit;
    }
                                                                                                  
    if (true == isDrawOutJPG)
    {
        cv::Mat yuvImg(HEIGHT * 1.5, WIDTH, CV_8UC1),rgbImg;
        memcpy(yuvImg.data,pYuvBuf_dst.get(),framesize);
        cv::cvtColor(yuvImg, rgbImg, CV_YUV420sp2RGB);
        if (atoi(argv[1]) == 1)
        {cv::imwrite("/root/osd/output_rect.jpg", rgbImg);}
        else if (atoi(argv[1]) == 2)
        {cv::imwrite("/root/osd/output_txt.jpg", rgbImg);}
        else if (atoi(argv[1]) == 3)
        {cv::imwrite("/root/osd/output_cir.jpg", rgbImg);}
        else if (atoi(argv[1]) == 4)
        {cv::imwrite("/root/osd/output_recttxt.jpg", rgbImg);}
        //cv::imwrite("/root/osd/output.jpg", rgbImg);
    }

    fclose(fileIn);
}
