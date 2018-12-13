#!/bin/bash

destinationIp="119.3.83.87"
userName="administrator"
passwd="Ascend310"


sshpass -p $passwd ssh -o StrictHostKeyChecking=no $userName@$destinationIp 'python ssh_test.py'
