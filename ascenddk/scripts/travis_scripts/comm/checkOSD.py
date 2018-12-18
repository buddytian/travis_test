# -*- coding:utf-8 -*-
'''
Created on 2018-11-26

@author: x00184840
'''
import logging
import os
import sys
curPath = os.path.abspath(os.path.dirname(__file__))
rootPath = os.path.split(curPath)[0]
sys.path.append(rootPath)
reload(sys)
sys.setdefaultencoding('utf-8')
sys.dont_write_bytecode = True
from PIL import Image,ImageEnhance,ImageFilter
from config import env_config
import cv2


class checkOSD(object):
    '''
    classdocs
    '''


    def __init__(self):
        '''
        Constructor
        '''
    
    def getGray(self,image_file):
        tmpls=[]
        for h in range(0,  image_file.size[1]):#h
            for w in range(0, image_file.size[0]):#w
                tmpls.append( image_file.getpixel((w,h)))
        return tmpls
    
    def getAvg(self,ls):#获取平均灰度值
        return sum(ls)/len(ls)
    
    def getMH(self,a,b):#比较字符里有几个相同的
        dist = 0;
        for i in range(0,len(a)):
            if a[i]==b[i]:
                dist=dist+1
        return float(dist)*100/len(a)
    
    def getImgHash(self,fne):
        image_file = Image.open(fne) # 打开
        #image_file=image_file.resize((12, 12))#重置图片大小
        image_file=image_file.convert("L")#转256灰度图
        Grayls=self.getGray(image_file)#灰度集合
        avg=self.getAvg(Grayls)#灰度平均值
        bitls=''#接收获取0或1
        #除去变宽1px遍历像素
        for h in range(1,  image_file.size[1]-1):#h
            for w in range(1, image_file.size[0]-1):#w
                if image_file.getpixel((w,h))>=avg:#像素的值比较平均值 大于记为1 小于记为0
                    bitls=bitls+'1'
                else:
                    bitls=bitls+'0'
        return bitls
    
    def drawRectangle(self,srcpath,destpath,color,lt,rb):
        img = cv2.imread(srcpath)
        cv2.rectangle(img, lt, rb, color, 5)
        cv2.imwrite(destpath, img)

    #wzz
    def drawCircle(self,srcpath,destpath,coordinate,radius,color):
        img = cv2.imread(srcpath)
        cv2.circle(img,coordinate,radius,color,3)
        cv2.imwrite(destpath,img)

#===============================================================================
# OSDPath=env_config.glbOutputDataPath+"OSD/"
# check=checkOSD()    
# srcPath=env_config.glbInputDataPath+"OSD/src.jpg"
# print('srcPath: ',srcPath)#wzz
# destPath=OSDPath+"output.jpg"
# print('destPath: ',destPath)#wzz
# color=(0,0,255)
# lt=(50,50)
# rb=(100,100)
# coordinate=(100,100)#wzz
# radius=10#wzz
# #check.drawRectangle(srcPath,destPath,color, lt, rb)
# check.drawCircle(srcPath, destPath, coordinate, radius, color)#wzz
# srcPath=env_config.glbInputDataPath+"OSD/output.jpg"
# a=check.getImgHash(srcPath)
# b=check.getImgHash(destPath)
# compare=check.getMH(a,b)
# print 'similarity:',str(compare)+"%"
#===============================================================================
        
        
