#! /bin/bash

if [ "x$TARGET" == "x" ];then
    TARGET=DEBUG
fi

# cat YukiPkg/Application/HelloWorld/HelloWorld.inf.inc > YukiPkg/Application/HelloWorld/HelloWorld.inf
# cat YukiPkg/Include/lvgl.inf.inc >> YukiPkg/Application/HelloWorld/HelloWorld.inf
# cp -Rv YukiPkg/Application/HelloWorld/stdc/*.h YukiPkg/Application/HelloWorld


cat YukiPkg/Application/YukiLoader/YukiLoader.inf.inc > YukiPkg/Application/YukiLoader/YukiLoader.inf
cat YukiPkg/Include/lvgl.inf.inc >> YukiPkg/Application/YukiLoader/YukiLoader.inf
cat YukiPkg/Include/lv_sprintf.h > YukiPkg/Libs/lvgl/src/stdlib/lv_sprintf.h
cat YukiPkg/Include/jdmaster.c > YukiPkg/Libs/libjpeg-turbo/src/jdmaster.c
cat YukiPkg/Include/jpegint.h > YukiPkg/Libs/libjpeg-turbo/src/jpegint.h
cat YukiPkg/Include/jmorecfg.h > YukiPkg/Libs/libjpeg-turbo/src/jmorecfg.h
cat YukiPkg/Include/pnglibconf.h > YukiPkg/Libs/libpng/pnglibconf.h

build -p YukiPkg/YukiUEFI.dsc -b ${TARGET}
