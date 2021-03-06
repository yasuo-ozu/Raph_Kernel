MOUNT_DIR = /mnt/Raph_Kernel
IMAGE = disk.img
BUILD_DIR = build

.PHONY: clean disk mount

default: image

run:
	make qemurun
	-telnet 127.0.0.1 1234
	make qemuend

qemurun: image
	sudo qemu-system-x86_64 -cpu qemu64,+x2apic -smp 8 -machine q35 -monitor telnet:127.0.0.1:1234,server,nowait -vnc 0.0.0.0:0,password -net nic -net bridge,br=br0 -drive id=disk,file=$(IMAGE),if=virtio &
#	sudo qemu-system-x86_64 -cpu qemu64,+x2apic -smp 8 -machine q35 -monitor telnet:127.0.0.1:1234,server,nowait -vnc 0.0.0.0:0,password -net nic -net bridge,br=br0 -drive id=disk,file=$(IMAGE),if=none -device ahci,id=ahci -device ide-drive,drive=disk,bus=ahci.0 &
#	sudo qemu-system-x86_64 -smp 8 -machine q35 -monitor telnet:127.0.0.1:1234,server,nowait -vnc 0.0.0.0:0,password -net nic -net bridge,br=br0 -drive file=$(IMAGE),if=virtio &
	sleep 0.2s
	echo "set_password vnc a" | netcat 127.0.0.1 1234

qemuend:
	-sudo pkill -KILL qemu

#$(CORE_FILE): $(subst $(MOUNT_DIR)/core,$(BUILD),$@)
#	cp $< $@

bin:
	-mkdir $(BUILD_DIR)
	make -C source

image:
	make mount
	make bin
	sudo cp memtest86+.bin $(MOUNT_DIR)/boot/memtest86+.bin
	sudo cp grub.cfg $(MOUNT_DIR)/boot/grub/grub.cfg 
	-sudo rm -rf $(MOUNT_DIR)/core
	sudo cp -r $(BUILD_DIR) $(MOUNT_DIR)/core
	make umount

$(IMAGE):
	make umount
	sh disk.sh make-diskimage
	sh disk.sh grub-install

cpimg: image
	cp $(IMAGE) /vagrant

hd: image
	@if [ ! -e /dev/sdb ]; then echo "error: insert usb memory!"; exit -1; fi
	sudo dd if=$(IMAGE) of=/dev/sdb

disk:
	make diskclean
	make $(IMAGE)
	make image

mount: $(IMAGE)
	sh disk.sh mount

umount:
	sh disk.sh umount

deldisk: umount
	-rm -f $(IMAGE)

clean: deldisk
	-rm -rf $(BUILD_DIR)
	make -C source clean

diskclean: deldisk clean
