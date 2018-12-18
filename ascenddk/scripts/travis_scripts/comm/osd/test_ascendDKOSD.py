# -*- coding: utf-8 -*
'''
Created on 2018-11-12

@author: t00192666
'''
import os
import sys
curPath = os.path.abspath(os.path.dirname(__file__))
rootPath=os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(curPath))))
sys.path.append(rootPath)
reload(sys)
sys.setdefaultencoding('utf-8')
import time
from publicModule import SSHConnection,ExcelUnit
from serviceModule import checkOSD
from config import env_config
from var_ascendDKOSD import *
import logging
import unittest
import ddt
from publicModule import ExcelUnit
import operator as op

excel1=ExcelUnit().readExcel(ddtFileName, sheetName1,2)
excel2=ExcelUnit().readExcel(ddtFileName, sheetName2,2)
excel3=ExcelUnit().readExcel(ddtFileName, sheetName3,2)
excel4=ExcelUnit().readExcel(ddtFileName, sheetName4,2)

@ddt.ddt
class Test(unittest.TestCase):
    
    def __init__(self,methodName='runTest'):
        self._UIHost=None
        self._mini=None
        self._glbLocalRun=False
        self.conn=None
        super(Test,self).__init__(methodName)
        
    def setUp(self):
        logging.basicConfig(level=env_config.glbLogLevel,
                    format='%(asctime)s - %(filename)s[line:%(lineno)d] - %(levelname)s: %(message)s')
        logging.info("[Step1] Load Global Variable")
        self._UIHost=env_config.glbUIHost
        self._mini=env_config.glbMini
        self._glbLocalRun=env_config.glbLocalRun
        logging.debug("Env of MINI:")
        logging.debug(self._mini)
    

    @ddt.data(*excel1)
    def testDrawRectangle(self,data):
        logging.info("[Step2] Execute Test Case")
        now = time.strftime("%Y%m%d%H%M%S",time.localtime(time.time()))
        srcfilename="output.jpg"
        filename=data['TestCaseName']+"_"+data['drawtype']+"_"+data['imgformat']+"_"+data['defaultattr']+"_output.jpg"
        command="rm -rf "+imageOutputFilepath+filename
        self.conn=SSHConnection(env_config.glbUIHost)
        self.conn.exec_command(command)    
        command=data['Command']+" "+data['drawtype']+" "+data['imgformat']+" "+data['defaultattr']+" "+data['ltx']+" "+data['lty']+" "+data['rbx']+" "+data['rby']+" "+data['rred']+" "+data['rgreen']+" "+data['rblue']+" "+data['thinkness']+" "+data['linetype']
        logging.info("DrawRectangle command is: "+str(command))
        self.conn=SSHConnection(self._mini)
        acutualResult=self.conn.exec_command(varAscendDKOSDPath+command)
        stdAcutualResult="".join(acutualResult.split())
        stdExpectedResult="".join(data['Expected Result'].split())
        logging.info("AcutualResult is: "+str(stdAcutualResult))         
        logging.info("ExpectedResult is: "+str(stdExpectedResult))          
        #assert actual and expected
        self.assertTrue(stdExpectedResult in (stdAcutualResult))
 
        if data['Error']=="No" or data['Error']==None or data['Error']=="":
            self.assertNotIn("ERROR", stdAcutualResult)
            #download output jpg
            self.conn.download(varAscendDKOSDPath+srcfilename, imageOutputFilepath+filename)
            #compare input and output pics
            osdcmp=checkOSD.checkOSD()
            outputPic=osdcmp.getImgHash(imageOutputFilepath+filename)
            inputPic=osdcmp.getImgHash(imageinputFilepath+filename)
            compareResult=osdcmp.getMH(inputPic,outputPic)
            logging.info("compareResult is: "+str(compareResult))
            self.assertTrue("100.0" == str(compareResult))            
        else:
            self.assertTrue("".join(data['Error'].split()) in (stdAcutualResult))
        
        if data['Warn']=="No" or data['Warn']==None or data['Warn']=="":
            self.assertNotIn("WARNING", stdAcutualResult)
        else:
            self.assertTrue("".join(data['Warn'].split()) in (stdAcutualResult))
        logging.info("Complete execution command:"+command)
        logging.info("The Test Case Name is:"+data['TestCaseName']+" in Sheet1")

    @ddt.data(*excel2)
    def testPutText(self,data):
        logging.info("[Step2] Execute Test Case")
        now = time.strftime("%Y%m%d%H%M%S",time.localtime(time.time()))
        srcfilename="output.jpg"
        filename=data['TestCaseName']+"_"+data['drawtype']+"_"+data['imgformat']+"_"+data['defaultattr']+"_output.jpg"
        command="rm -rf "+imageOutputFilepath+filename
        self.conn=SSHConnection(env_config.glbUIHost)
        self.conn.exec_command(command)    
        command=data['Command']+" "+data['drawtype']+" "+data['imgformat']+" "+data['defaultattr']+" "+data['title']+" "+data['tx']+" "+data['ty']+" "+data['ftype']+" "+data['fscale']+" "+data['fred']+" "+data['fgreen']+" "+data['fblue']+" "+data['fthick']+" "+data['flinetype']
        logging.info("PutText command is: "+str(command))
        self.conn=SSHConnection(self._mini)
        acutualResult=self.conn.exec_command(varAscendDKOSDPath+command)
        stdAcutualResult="".join(acutualResult.split())
        stdExpectedResult="".join(data['Expected Result'].split())
        logging.info("AcutualResult is: "+str(stdAcutualResult))         
        logging.info("ExpectedResult is: "+str(stdExpectedResult))          
        #assert actual and expected
        self.assertTrue(stdExpectedResult in (stdAcutualResult))
 
        if data['Error']=="No" or data['Error']==None or data['Error']=="":
            self.assertNotIn("ERROR", stdAcutualResult)
            #download output jpg
            self.conn.download(varAscendDKOSDPath+srcfilename, imageOutputFilepath+filename)
            #compare input and output pics
            osdcmp=checkOSD.checkOSD()
            outputPic=osdcmp.getImgHash(imageOutputFilepath+filename)
            inputPic=osdcmp.getImgHash(imageinputFilepath+filename)
            compareResult=osdcmp.getMH(inputPic,outputPic)
            logging.info("compareResult is: "+str(compareResult))
            self.assertTrue("100.0" == str(compareResult))            
        else:
            self.assertTrue("".join(data['Error'].split()) in (stdAcutualResult))
        
        if data['Warn']=="No" or data['Warn']==None or data['Warn']=="":
            self.assertNotIn("WARNING", stdAcutualResult)
        else:
            self.assertTrue("".join(data['Warn'].split()) in (stdAcutualResult))
        logging.info("Complete execution command:"+command)
        logging.info("The Test Case Name is:"+data['TestCaseName']+" in Sheet2")

    @ddt.data(*excel3)
    def testDrawCircle(self,data):
        logging.info("[Step2] Execute Test Case")
        now = time.strftime("%Y%m%d%H%M%S",time.localtime(time.time()))
        srcfilename="output.jpg"
        filename=data['TestCaseName']+"_"+data['drawtype']+"_"+data['imgformat']+"_"+data['defaultattr']+"_output.jpg"
        command="rm -rf "+imageOutputFilepath+filename
        self.conn=SSHConnection(env_config.glbUIHost)
        self.conn.exec_command(command)    
        command=data['Command']+" "+data['drawtype']+" "+data['imgformat']+" "+data['defaultattr']+" "+data['cx']+" "+data['cy']+" "+data['Radius']+" "+data['cred']+" "+data['cgreen']+" "+data['cblue']+" "+data['cthickness']+" "+data['clinetype']
        logging.info("DrawCircle command is: "+str(command))
        self.conn=SSHConnection(self._mini)
        acutualResult=self.conn.exec_command(varAscendDKOSDPath+command)
        stdAcutualResult="".join(acutualResult.split())
        stdExpectedResult="".join(data['Expected Result'].split())
        logging.info("AcutualResult is: "+str(stdAcutualResult))         
        logging.info("ExpectedResult is: "+str(stdExpectedResult))  
        #assert actual and expected
        self.assertTrue(stdExpectedResult in (stdAcutualResult))

        if data['Error']=="No" or data['Error']==None or data['Error']=="":
            self.assertNotIn("ERROR", stdAcutualResult)
            #download output jpg
            self.conn.download(varAscendDKOSDPath+srcfilename, imageOutputFilepath+filename)
            #compare input and output pics
            osdcmp=checkOSD.checkOSD()
            outputPic=osdcmp.getImgHash(imageOutputFilepath+filename)
            inputPic=osdcmp.getImgHash(imageinputFilepath+filename)
            compareResult=osdcmp.getMH(inputPic,outputPic)
            logging.info("compareResult is: "+str(compareResult))
            self.assertTrue("100.0" == str(compareResult))
        else:
            self.assertTrue("".join(data['Error'].split()) in (stdAcutualResult))
        
        if data['Warn']=="No" or data['Warn']==None or data['Warn']=="":
            self.assertNotIn("WARNING", stdAcutualResult)
        else:
            self.assertTrue("".join(data['Warn'].split()) in (stdAcutualResult))
        logging.info("Complete execution command:"+command)
        logging.info("The Test Case Name is:"+data['TestCaseName']+" in Sheet3")       
   
    @ddt.data(*excel4)
    def testDrawRectangleAndLabel(self,data):
        logging.info("[Step2] Execute Test Case")
        now = time.strftime("%Y%m%d%H%M%S",time.localtime(time.time()))
        srcfilename="output.jpg"
        filename=data['TestCaseName']+"_"+data['drawtype']+"_"+data['imgformat']+"_"+data['defaultattr']+"_output.jpg"
        command="rm -rf "+imageOutputFilepath+filename
        self.conn=SSHConnection(env_config.glbUIHost)
        self.conn.exec_command(command)    
        commandrec=data['Command']+" "+data['drawtype']+" "+data['imgformat']+" "+data['defaultattr']+" "+data['ltx']+" "+data['lty']+" "+data['rbx']+" "+data['rby']+" "+data['rred']+" "+data['rgreen']+" "+data['rblue']+" "+data['thinkness']+" "+data['linetype']
        command=commandrec+" "+data['title']+" "+data['tx']+" "+data['ty']+" "+data['ftype']+" "+data['fscale']+" "+data['fred']+" "+data['fgreen']+" "+data['fblue']+" "+data['fthick']+" "+data['flinetype']
        logging.info("DrawRectangleAndLabel command is: "+str(command))
        self.conn=SSHConnection(self._mini)
        acutualResult=self.conn.exec_command(varAscendDKOSDPath+command)
        stdAcutualResult="".join(acutualResult.split())      
        stdExpectedResult="".join(data['Expected Result'].split())
        logging.info("AcutualResult is: "+str(stdAcutualResult))         
        logging.info("ExpectedResult is: "+str(stdExpectedResult))          
        #assert actual and expected
        self.assertTrue(stdExpectedResult in (stdAcutualResult))
 
        if data['Error']=="No" or data['Error']==None or data['Error']=="":
            self.assertNotIn("ERROR", stdAcutualResult)
            #download output jpg
            self.conn.download(varAscendDKOSDPath+srcfilename, imageOutputFilepath+filename)
            #compare input and output pics
            osdcmp=checkOSD.checkOSD()
            outputPic=osdcmp.getImgHash(imageOutputFilepath+filename)
            inputPic=osdcmp.getImgHash(imageinputFilepath+filename)
            compareResult=osdcmp.getMH(inputPic,outputPic)
            logging.info("compareResult is: "+str(compareResult))
            self.assertTrue(op.lt(float("99.99989"),float(compareResult)))
        else:
            self.assertTrue("".join(data['Error'].split()) in (stdAcutualResult))
        
        if data['Warn']=="No" or data['Warn']==None or data['Warn']=="":
            self.assertNotIn("WARNING", stdAcutualResult)
        else:
            self.assertTrue("".join(data['Warn'].split()) in (stdAcutualResult))
        logging.info("Complete execution command:"+command)
        logging.info("The Test Case Name is:"+data['TestCaseName']+" in Sheet4")            
    
    def tearDown(self):
        if self.conn:
            logging.info("[Step3] Post Process,Close SSH Connection")
            self.conn.close()

if __name__ == "__main__":
    unittest.main()     
