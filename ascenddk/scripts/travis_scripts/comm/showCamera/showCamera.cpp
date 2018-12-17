extern "C"
{
#include "driver/peripheral_api.h"
}
#include "hiaiengine/engine.h"
#include "hiaiengine/data_type.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>

using namespace cv;
using namespace hiai;
using namespace std;

//摄像头参数
#define WIDTH	1280
#define HEIGHT	720
int FPS=20;
int allframe=300;

uint32_t m_frameid;

struct yuvfile {
    string file;
    int number;
    int readSize;
    uint8_t* pdata;
};


//map & 锁
map<int, uint8_t*> mapmembuffer;
map<int, string> maptimestamp;
mutex g_lock;

std::shared_ptr<BatchImagePara<uint8_t>> CreateBatchImageParaObj(int channel_ID)
{
    std::shared_ptr < BatchImagePara < uint8_t >> pObj = std::make_shared<BatchImagePara<uint8_t>>();
    pObj->b_info.is_first = (m_frameid == 0);
    pObj->b_info.is_last = false;
    pObj->b_info.batch_size = 1;
    pObj->b_info.max_batch_size = 1;
    pObj->b_info.batch_ID = 0;
    pObj->b_info.channel_ID = channel_ID;
    pObj->b_info.processor_stream_ID = 0;
    pObj->b_info.frame_ID.push_back(m_frameid++);
    pObj->b_info.timestamp.push_back(time(NULL));

    ImageData < uint8_t > imgData;
    imgData.format = YUV420SP;
    imgData.width = WIDTH;
    imgData.height = HEIGHT;

    imgData.size = WIDTH * HEIGHT * 3 / 2;

    uint8_t * image_buffer_ptr1_ = (uint8_t*) (new uint8_t[imgData.size]);
    std::shared_ptr < uint8_t > data(image_buffer_ptr1_);
    imgData.data = data;
    pObj->v_img.push_back(imgData);

    return pObj;

}

static void* writeYUV420sp_thread(void *data)
{
    sleep(1);
    yuvfile *param = (yuvfile *)data;
    map<int, uint8_t*>::iterator it;
    map<int, string>::iterator ittimestamp;
    int number=0;
    while(number<param->number)
    {
        number++;
        it = mapmembuffer.find(number);
        if (it != mapmembuffer.end()){
            param->pdata=it->second;
	        //写入本地YUV文件 
            ittimestamp=maptimestamp.find(number);

            int yuvsize=WIDTH * HEIGHT * 1.5;//1382400;
            char *yuvdata=new char[yuvsize];
            memcpy(yuvdata,param->pdata,WIDTH * HEIGHT * 1.5);
            ofstream fout(ittimestamp->second.c_str());     //创建一个YUV文件
            fout.write(yuvdata,param->readSize);     //将图片写入文件
            fout.close();                  //关闭文件
            //cout<<"write " << ittimestamp->second.c_str() <<" success"<<endl;
            
            
            //OPENCV处理且写本地bmp or jpg文件             
            Mat src(HEIGHT * 1.5, WIDTH, CV_8UC1), dst;      // 如果不是从文件中读取yuv数据，从这里开始看
	        memcpy(src.data, param->pdata, WIDTH * HEIGHT * 1.5);
	        cvtColor(src, dst, CV_YUV420sp2RGB);
            stringstream  Resultfile;
            size_t index=ittimestamp->second.find(".");
	        Resultfile << "Result-" << ittimestamp->second.substr(0,index) << ".jpg";
	        imwrite(Resultfile.str(), dst);
	        cout<<"write " << Resultfile.str() <<" success"<<endl;
            
	        //mapmembuffer中erase
	        g_lock.lock();
            int eraseReturn=mapmembuffer.erase(it->first);
            maptimestamp.erase(it->first);
            g_lock.unlock();

            if(1==eraseReturn)
            {
                cout<<"erase num " << it->first <<" success"<<endl;
            }else{
                cout<<"erase failed,erase num " << it->first <<" not in map"<<endl;
            }       
        }else{
            cout<<"wait 100ms"<<endl;
            usleep(100000);
            number--;
        }
    }
}
pthread_t writeYUV420sp_test_thread_create(int readSize, int number)
{
    yuvfile *param = new yuvfile();
    param->readSize = readSize;
    param->number = number;
    pthread_t thread_id;
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_id, &thread_attr, 
                                &writeYUV420sp_thread, param);

    return thread_id;
}


int main(int argc, char* argv[])
{
    if (argc < 3)    //Usage:./hello -c [channel_ID]
    {
       printf("run command error!!!!!!!\n");
       printf("Usage:./hello -c [channel_ID]\n");
       exit(-1);
    }
    else if(argc > 3)
    {
       printf("Unknow command ,%s!!!!!!!\n",argv[3]);
       printf("Usage:./hello -c [channel_ID]\n");
       exit(-1);
    }
    
    if(*argv[1] != 45 || *(argv[1]+1) != 99 || *(argv[1]+2) != 0)    // -c/0
    {
        printf("run command error!!!!!!!,%s\n",argv[1]);
        printf("Usage:./hello -c [channel_ID]\n");
        exit(0);
    }
    
    if(*argv[2] != 0x30  &&  *argv[2] != 0x31 || *(argv[2]+1) != 0x0)    //channel_ID=[0,1]
    {
        printf("channel_ID error!!!!!!!,%d,%d\n",*argv[2],*(argv[2]+1));
        printf("channel_ID=[0,1]\n");
        exit(0);
    }
    
    int channel_ID=atoi(argv[2]);
    
    int ret, para;
    struct CameraResolution resolution;
    resolution.height = HEIGHT;
	resolution.width = WIDTH;

    MediaLibInit();

    ret = IsChipAlive(NULL);
    printf("IsChipAlive ret %d\r\n", ret);
    if(ret==0) 
    {
        printf("Camera(%d) is not alive\n",channel_ID);
        exit(0);
    }
    ret=OpenCamera(channel_ID);
    printf("OpenCamera(%d) ret %d\r\n", channel_ID,ret);
    if(ret==0) 
    {
        printf("Camera(%d) can not open\n",channel_ID);
        exit(0);
    }   

    //设置摄像头参数
    //fps
    para = FPS;   
    SetCameraProperty(channel_ID, CAMERA_PROP_FPS, &para);
       
    //YUV420SP
    para = CAMERA_IMAGE_YUV420_SP;    
    SetCameraProperty(channel_ID, CAMERA_PROP_IMAGE_FORMAT, &para);
    
    //1280*720
    SetCameraProperty(channel_ID, CAMERA_PROP_RESOLUTION, &resolution);
    
    //主动模式
    para = CAMERA_CAP_ACTIVE;
    SetCameraProperty(channel_ID, CAMERA_PROP_CAP_MODE, &para);
    printf("SetCameraProperty(%d) OK\r\n",channel_ID);
    
    //从摄像头获取图片    
    int readSize = 0;
    std::shared_ptr < BatchImagePara < uint8_t >> pObj = CreateBatchImageParaObj(channel_ID);
    ImageData < uint8_t > *pImgData = &pObj->v_img[0];
    uint8_t* pdata = pImgData->data.get();
    readSize = (int) pImgData->size;
    
    
    //起一个处理缓存mapmembuffer的线程
    writeYUV420sp_test_thread_create(readSize,allframe);  
    
    int index=0;
    while(index<allframe)   //循环从摄像头读取200张YUV图片 1秒20帧 那么就是取10s的图片
    {
        index++;
        //从摄像头读一张图片
        suseconds_t timediffA;
        struct timeval beginA, endA;
        gettimeofday(&beginA, NULL);

        int readRet = ReadFrameFromCamera(channel_ID, (void*) pdata, &readSize); 
        
        gettimeofday(&endA, NULL);
        timediffA = endA.tv_usec - beginA.tv_usec + (endA.tv_sec - beginA.tv_sec) * 1000000;
        printf("ReadFrameFromCamera %d wastes %d us total\n",index,(int)timediffA);   
        
        //时间戳写入一个maptimestamp 
        time_t timep;
        time (&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y%m%d%H%M%S",localtime(&timep) );
        string cur_time=tmp;
        stringstream  tmpfile;
	    tmpfile <<cur_time.c_str()<< "-" << index << ".YUV420SP";
	    
	    //拷贝一份
        uint8_t* dpdata = (uint8_t*)malloc(readSize);
        memcpy(dpdata,pdata,readSize);
        
        //insert map 写入内存缓存mapmembuffer
        g_lock.lock();
        mapmembuffer.insert({index,dpdata});
        maptimestamp.insert({index,tmpfile.str()});
        g_lock.unlock();     
    }
    
    //循环暂停1s,等待所有的处理线程处理完毕,才能退出程序
    while(mapmembuffer.size()!=0)
    {
        cout<<"mapmembuffer size :" << mapmembuffer.size()<<endl;
        sleep(1);
    }
    
    //关闭摄像头
    printf("CloseCamera(%d) ret %d\r\n", channel_ID,CloseCamera(channel_ID));   
    printf("Camera(%d)-result is Result1.jpg-Result%d.jpg\r\n",channel_ID,allframe);      
    return 0;
}

