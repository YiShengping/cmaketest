#include <stdio.h>
#include <stdlib.h>
#include "../pciutils-3.13.0/lib/pci.h"
#include <windows.h>

int main(void) {
    struct pci_access *pacc;
    struct pci_dev *dev;
    char namebuf[1024];

    // 初始化PCI库
    pacc = pci_alloc();
    pci_init(pacc);
    pci_scan_bus(pacc);

    // 遍历所有PCI设备
    for (dev = pacc->devices; dev; dev = dev->next) {
        // 读取设备的配置空间
        pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_CLASS);
        
        // 获取设备名称
        pci_lookup_name(pacc, namebuf, sizeof(namebuf),
            PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE,
            dev->vendor_id, dev->device_id);

        // 打印设备信息
        printf("Bus %02x Device %02x Function %02x:\n",
            dev->bus, dev->dev, dev->func);
        printf("  Vendor ID: %04x  Device ID: %04x\n",
            dev->vendor_id, dev->device_id);
        printf("  Device Name: %s\n", namebuf);
        printf("  Device Class: %04x\n", dev->device_class);
        printf("\n");
    }

    // 清理
    pci_cleanup(pacc);
    return 0;
}
