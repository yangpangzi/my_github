#########################################################################
# File Name: start.sh
# Author: yangle
# mail: yangle4695@gmail.com
# Created Time: 2016年08月16日 星期二 07时26分31秒
#########################################################################
#!/bin/bash
ROOT_PATH=$(pwd)

export LD_LIBRARY_PATH=$ROOT_PATH/lib/lib;
./httpd 127.0.0.1 8888
