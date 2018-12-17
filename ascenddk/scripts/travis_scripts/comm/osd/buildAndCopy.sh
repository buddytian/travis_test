#!/bin/bash

ScriptPath=`dirname $0`
ScriptPath=`cd ${ScriptPath};pwd`

destinationIp=$1
userName="root"
passwd="root"

cd $ScriptPath

#cp ~/hava/ascenddk/ascenddk/common/osd/OsdApi.h .
#cp ~/hava/ascenddk/ascenddk/common/osd/OsdDataType.h .
#cp ~/hava/ascenddk/ascenddk/common/utils/ascend_ezdvpp/DvppProcess.h .

make

sshpass -p $passwd ssh -o StrictHostKeyChecking=no $userName@$destinationIp 'mkdir -p /root/osd/'

if [ ! -f "./out/osdtest" ];then
    echo -e  "The file is no exist.please check."
    exit
fi

sshpass -p $passwd scp ./out/osdtest $userName@$destinationIp:/root/osd/
cd ../../../data/input/ascendDKOSD/image_source
sshpass -p $passwd scp ./0000000017.yuv.nv12 $userName@$destinationIp:/root/osd/
