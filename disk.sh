MOUNT_DIR="/mnt/Raph_Kernel"
IMAGE="disk.img"
TMPDIR="/tmp/tmpRaphKern"
IMGFILE=$TMPDIR/disk.img

sudo mkdir -p $TMPDIR

umount() {
    sudo umount ${MOUNT_DIR}
    sudo kpartx -d ${IMGFILE}
	[ -f $IMAGE ] && sudo rm $IMAGE
	sudo cp $IMGFILE $IMAGE
    sudo losetup -d /dev/loop[0-9] > /dev/null 2>&1 || return 0
}

loopsetup() {
    set -- $(sudo kpartx -av ${IMGFILE})
    LOOPDEVICE=$8
    MAPPEDDEVICE=/dev/mapper/$3
}

mount() {
	[ -f $IMGFILE ] && sudo rm $IMGFILE
	sudo cp $IMAGE $IMGFILE
    loopsetup
    sudo mkdir ${MOUNT_DIR}
    sudo mount -t ext2 ${MAPPEDDEVICE} ${MOUNT_DIR}
}

if [ $1 = "mount" ]; then
    mount
fi

if [ $1 = "umount" ]; then
    umount
fi

if [ $1 = "grub-install" ]; then
	[ -f $IMGFILE ] || sudo rm $IMGFILE
	sudo cp $IMAGE $IMGFILE
    loopsetup
    sudo mkfs -t ext2 ${MAPPEDDEVICE}
    sudo mkdir -p ${MOUNT_DIR}
    sudo mount -t ext2 ${MAPPEDDEVICE} ${MOUNT_DIR}
    sudo grub-install --no-floppy ${LOOPDEVICE} --root-directory ${MOUNT_DIR}
    umount
fi

if [ $1 = "make-diskimage" ]; then
	[ -f $IMGFILE ] && sudo rm $IMGFILE
	sudo dd if=/dev/zero of=$IMGFILE bs=1M count=20
	sudo parted -s $IMGFILE mklabel msdos -- mkpart primary 2048s -1
	sudo rm $IMAGE
	sudo cp $IMGFILE $IMAGE
fi


