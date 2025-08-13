#!/bin/bash
TARGET=DEBUG
FILESYSTEM=vfat
BS=1MiB
COUNT=128
#RELEASE SIZE=82MiB
#DEBUG SIZE=84MiB
IMAGEDIR=/mnt/edk2
IMAGE=${IMAGEDIR}/UEFI-STUB_${TARGET}.img
WEBROOT=/var/www/html/edk2-build
BUILDDEPS=0
BUILDPKGS=0
PICKDEPS=1
PICKPKGS=1
SECURE_BOOT=ENABLE

if [ $BUILDDEPS -eq 1 ];then
    PICKDEPS=1
fi

if [ $BUILDPKGS -eq 1 ];then
    PICKPKGS=1
fi


BuildDeps()
{
    build -p MdeModulePkg/MdeModulePkg.dsc -b ${TARGET}
    build -p CryptoPkg/CryptoPkg.dsc -b ${TARGET}
    build -p NetworkPkg/NetworkPkg.dsc -b ${TARGET}
    build -p ShellPkg/ShellPkg.dsc -b ${TARGET}
    
    if [ "x${TARGET}" == "xDEBUG"];then
        build -p OvmfPkg/OvmfPkgX64.dsc -b ${TARGET} -D DEBUG_ON_SERIAL_PORT -D SECURE_BOOT_${SECURE_BOOT}
    else
        build -p OvmfPkg/OvmfPkgX64.dsc -b ${TARGET} -D SECURE_BOOT_${SECURE_BOOT}
    fi
}

PickUpEFI()
{
    echo -n "Picking Up EFIs $1 ... "
    sudo mkdir -p ${IMAGEDIR}/img/$1
    CPRESULT=$(sudo cp -r Build/$1/${TARGET}_GCC/X64/*.efi ${IMAGEDIR}/img/$1 2>&1)
    if [ "x$CPRESULT" ==  "x" ];then
        echo OK
    else
        echo FAIL
    fi
}

PickUpFV()
{
    echo -n "Picking Up FVs $1 ... "
    sudo mkdir -p ${IMAGEDIR}/img/$1
    CPRESULT=$(sudo cp -r Build/$1/${TARGET}_GCC/FV/*.fd ${IMAGEDIR}/img/$1 2>&1)
    if [ "x$CPRESULT" ==  "x" ];then
        echo OK
    else
        echo FAIL
    fi

    if ! [ "x$WEBROOT" == x ];then
        echo -n "Publishing FVs $1 ... "
        if ! [ -d $WEBROOT/OVMF-$TARGET ];then
            sudo mkdir -p $WEBROOT/OVMF-$TARGET
        fi

        PUBLISHRESULT=$(sudo cp -r Build/$1/${TARGET}_GCC/FV/*.fd $WEBROOT/OVMF-$TARGET 2>&1)
        if [ "x$PUBLISHRESULT" ==  "x" ];then
            echo OK
        else
            echo FAIL
        fi
    fi
}

PickUp()
{
    if ! [ -d ${IMAGEDIR} ];then
        sudo mkdir -p ${IMAGEDIR}
    fi

    if [ -f $IMAGE ];then
        sudo rm $IMAGE
    fi

    if ! [ -f $IMAGE ];then        
        sudo dd if=/dev/zero of=$IMAGE bs=$BS count=$COUNT
        sudo mkfs.$FILESYSTEM $IMAGE
        sudo mkdir -p ${IMAGEDIR}/img
        sudo mount $IMAGE ${IMAGEDIR}/img
    fi

    if [ $PICKDEPS -eq 1 ];then
        PickUpEFI CryptoPkg/All
        PickUpEFI MdeModule
        PickUpEFI NetworkPkg
        PickUpEFI Shell
        PickUpEFI OvmfX64
        PickUpFV OvmfX64
    fi

    if [ $BUILDPKGS -eq 1 ];then       
        TARGET=$TARGET ./YukiPkg/YukiPkg.Makefile
    fi     

    if [ $PICKPKGS -eq 1 ];then       
        PickUpEFI YukiPkg
    fi
    
    DISKUSED=$(sudo df -kh ${IMAGEDIR}/img --output=used| tr -s ' ' | sed -ne 2p )
    DISKAVAIL=$(sudo df -kh ${IMAGEDIR}/img --output=avail| tr -s ' ' | sed -ne 2p )
    DISKSIZE=$(sudo df -kh ${IMAGEDIR}/img --output=size| tr -s ' ' | sed -ne 2p )

    echo IMAGE INFO: 
    echo Total: ${DISKSIZE} Used:${DISKUSED} Available:${DISKAVAIL}

    sudo umount ${IMAGEDIR}/img
    sudo rm -rf ${IMAGEDIR}/img
}

PublishEFI()
{
    if ! [ "x$WEBROOT" == x ];then
        echo -n "Publishing EFI Disk Image $1 ... "
        PUBLISHRESULT=$(sudo cp -r $IMAGE $WEBROOT 2>&1)
        if [ "x$PUBLISHRESULT" ==  "x" ];then
            echo OK
        else
            echo FAIL
        fi
    fi
}

clear

if [ $BUILDDEPS -eq 1 ];then
    BuildDeps
fi

if [ $BUILDPKGS -eq 1 ];then
    ./YukiPkg/YukiPkg.Makefile
fi

PickUp
PublishEFI

