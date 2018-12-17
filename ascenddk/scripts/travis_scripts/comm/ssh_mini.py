#!/usr/bin/env python

import sys
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

    hostname = '192.168.4.11'
    tport = 22
    username = 'root'
    password = 'root'
    execmd = "/temp/showCamera -c 0"

    sshclient_execmd(hostname, tport, username, password, execmd)

def myrectangle(deviceip,deviceport,deviceusrname,devicepasswd,ltx,lty,rbx,rby,red,green,blue,thinkness,linetype):
    u'''
    draw rectangle
    '''

    script="/temp/drawdemo"
    execmd=script+" "+ltx+" "+lty+" "+rbx+" "+rby+" "+red+" "+green+" "+blue+" "+thinkness+" "+linetype
    #execmd=script+" "+str(list_rec[0][0][0])+" "+str(list_rec[0][0][1])+" "+str(list_rec[0][1][0])+" "+str(list_rec[0][1][1])+" "+str(list_rec[1][0])+" "+str(list_rec[1][1])+" "+str(list_rec[1][2])+" "+str(list_rec[2])+" "+str(list_rec[3])
    print execmd
    mport=int(deviceport)
    sshclient_execmd(deviceip,mport,deviceusrname,devicepasswd,execmd)
    
def mylabel(deviceip,deviceport,deviceusrname,devicepasswd,title,x,y,lfonttype,lfontscale,lred,lgreen,lblue,lthinkness,llinetype):
    u'''
    draw label
    '''

    script="/temp/drawdemo"
    execmd=script+" "+title+" "+x+" "+y+" "+lfonttype+" "+lfontscale+" "+lred+" "+lgreen+" "+lblue+" "+lthinkness+" "+llinetype
    #execmd=script+" "+str(list_rec[0][0][0])+" "+str(list_rec[0][0][1])+" "+str(list_rec[0][1][0])+" "+str(list_rec[0][1][1])+" "+str(list_rec[1][0])+" "+str(list_rec[1][1])+" "+str(list_rec[1][2])+" "+str(list_rec[2])+" "+str(list_rec[3])
    print execmd
    mport=int(deviceport)
    sshclient_execmd(deviceip,mport,deviceusrname,devicepasswd,execmd)

def mycircle(deviceip,deviceport,deviceusrname,devicepasswd,cx,cy,Radius,cred,cgreen,cblue,cthinkness,clinetype):
    u'''
    draw label
    '''

    script="/temp/drawdemo"
    execmd=script+" "+cx+" "+cy+" "+Radius+" "+cred+" "+cgreen+" "+cblue+" "+cthinkness+" "+clinetype
    #execmd=script+" "+str(list_rec[0][0][0])+" "+str(list_rec[0][0][1])+" "+str(list_rec[0][1][0])+" "+str(list_rec[0][1][1])+" "+str(list_rec[1][0])+" "+str(list_rec[1][1])+" "+str(list_rec[1][2])+" "+str(list_rec[2])+" "+str(list_rec[3])
    print execmd
    mport=int(deviceport)
    sshclient_execmd(deviceip,mport,deviceusrname,devicepasswd,execmd)

def myreclabel(deviceip,deviceport,deviceusrname,devicepasswd,ltx,lty,rbx,rby,red,green,blue,thinkness,linetype,title,x,y,lfonttype,lfontscale,lred,lgreen,lblue,lthinkness,llinetype):
    u'''
    draw rectangle
    '''

    script="/temp/drawdemo"
    execmd=script+" "+ltx+" "+lty+" "+rbx+" "+rby+" "+red+" "+green+" "+blue+" "+thinkness+" "+linetype+" "+title+" "+x+" "+y+" "+lfonttype+" "+lfontscale+" "+lred+" "+lgreen+" "+lblue+" "+lthinkness+" "+llinetype
    print execmd
    mport=int(deviceport)
    sshclient_execmd(deviceip,mport,deviceusrname,devicepasswd,execmd)     

if __name__=='__main__':
    #main()
    #pycrypto-2.6.1.tar.gz--1
    #paramiko-1.12.1.tar.gz--2
    if len(sys.argv) == 14:
        myrectangle(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7],sys.argv[8],sys.argv[9],sys.argv[10],sys.argv[11],sys.argv[12],sys.argv[13])
    if len(sys.argv) == 15:
        mylabel(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7],sys.argv[8],sys.argv[9],sys.argv[10],sys.argv[11],sys.argv[12],sys.argv[13],sys.argv[14])
    if len(sys.argv) == 13:
        mycircle(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7],sys.argv[8],sys.argv[9],sys.argv[10],sys.argv[11],sys.argv[12])
    if len(sys.argv) == 24:
        myreclabel(sys.argv[1],sys.argv[2],sys.argv[3],sys.argv[4],sys.argv[5],sys.argv[6],sys.argv[7],sys.argv[8],sys.argv[9],sys.argv[10],sys.argv[11],sys.argv[12],sys.argv[13],sys.argv[14],sys.argv[15],sys.argv[16],sys.argv[17],sys.argv[18],sys.argv[19],sys.argv[20],sys.argv[21],sys.argv[22],sys.argv[23])
