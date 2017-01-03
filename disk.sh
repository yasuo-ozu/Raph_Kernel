MOUNT_DIR="/mnt/Raph_Kernel"
IMAGE="disk.img"
TMPDIR="/tmp/tmpRaphKern"

sudo mkdir -p $TMPDIR

umount() {
    sudo umount ${MOUNT_DIR}
    sudo kpartx -d ${$TMPDIR/$IMAGE}
    [ -f $IMAGE ] && sudo rm $IMAGE
    sudo cp $TMPDIR/$IMAGE $IMAGE
    sudo losetup -d /dev/loop[0-9] > /dev/null 2>&1 || return 0
}

loopsetup() {
    set -- $(sudo kpartx -av ${$TMPDIR/$IMAGE})
    LOOPDEVICE=$8
    MAPPEDDEVICE=/dev/mapper/$3
}

mount() {
    [ -f $TMPDIR/$IMAGE ] && sudo rm $TMPDIR/$IMAGE
    sudo cp $IMAGE $TMPDIR/$IMAGE
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
    [ -f $TMPDIR/$IMAGE ] || sudo rm $TMPDIR/$IMAGE
    sudo cp $IMAGE $TMPDIR/$IMAGE
    loopsetup
    sudo mkfs -t ext2 ${MAPPEDDEVICE}
    sudo mkdir -p ${MOUNT_DIR}
    sudo mount -t ext2 ${MAPPEDDEVICE} ${MOUNT_DIR}
    sudo grub-install --no-floppy ${LOOPDEVICE} --root-directory ${MOUNT_DIR}
    umount
fi

if [ $1 = "make-diskimage" ]; then
    [ -f $TMPDIR/$IMAGE ] && sudo rm $TMPDIR/$IMAGE
    sudo dd if=/dev/zero of=$TMPDIR/$IMAGE bs=1M count=20
    sudo parted -s $TMPDIR/$IMAGE mklabel msdos -- mkpart primary 2048s -1
    sudo rm $IMAGE
    sudo cp $TMPDIR/$IMAGE $IMAGE
fi


