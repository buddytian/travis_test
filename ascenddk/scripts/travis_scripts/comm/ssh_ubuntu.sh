#!/bin/bash

destinationIp="192.168.1.70"
userName="administrator"
passwd="Ascend310"


sshpass -p $passwd ssh -o StrictHostKeyChecking=no $userName@$destinationIp 'python ssh_test.py'
