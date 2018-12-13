# -*- coding:utf-8 -*-
"""
Created on 2018-11-26
@author: t00192666
Func: for ssh ubuntu executing python
"""
import re
import paramiko  
  
def sshclient_execmd(hostname, port, username, password, execmd):  
    paramiko.util.log_to_file("paramiko.log")  
      
    s = paramiko.SSHClient()  
    s.set_missing_host_key_policy(paramiko.AutoAddPolicy())  
      
    s.connect(hostname=hostname, port=port, username=username, password=password)  
    stdin, stdout, stderr = s.exec_command (execmd)  
    stdin.write("Y")  # Generally speaking, the first connection, need a simple interaction.  
      
    print stdout.read()  
      
    s.close()  

def main():  
      
	hostname = '192.168.1.70'  
	tport = 22  
	username = 'administrator'  
	password = 'Ascend310'  
	execmd = "/root/test2/Myssh.py"  
      
	sshclient_execmd(hostname, tport, username, password, execmd)  	

def Matchurl(str0):
    u'''
    verify the ext name of URL
    '''
    str1=re.split("[.]",str0)
    listt = ['php','html','asp','jsp']
    if str1[-1] in listt:
        return "TRUE"
    else:
        return "FAIL"

if __name__=='__main__':
    #str_input='hehe.php'
    #print Matchurl(str_input)
	main()
	
