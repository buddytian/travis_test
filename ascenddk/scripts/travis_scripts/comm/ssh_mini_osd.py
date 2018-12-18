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

    hostname = '192.168.1.2'
    tport = 22
    username = 'root'
    password = 'root'
    execmd = "/root/osd/osdtest 1 0 ALL 100 100 300 300 255 165 0 1 8"
    sshclient_execmd(hostname, tport, username, password, execmd)
    execmd = "/root/osd/osdtest 2 0 ALL FACE:98% 100 100 0 1.5 255 0 0 3 8"
    sshclient_execmd(hostname, tport, username, password, execmd)
    execmd = "/root/osd/osdtest 3 0 ALL 300 300 100 255 0 0 3 8"
    sshclient_execmd(hostname, tport, username, password, execmd)
    execmd = "/root/osd/osdtest 4 0 ALL 100 100 300 300 255 165 0 3 8 FACE:98% 100 100 0 1.5 255 0 0 3 8"
    sshclient_execmd(hostname, tport, username, password, execmd)


if __name__=='__main__':
    main()
