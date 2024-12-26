#include <cstdio>

extern "C" {
#include <pci/pci.h>
}

int main() {
    struct pci_access *pacc = pci_alloc();
    if (!pacc) {
        fprintf(stderr, "Failed to allocate PCI access structure\n");
        return 1;
    }

    pci_init(pacc);
    pci_scan_bus(pacc);

    struct pci_dev *dev;
    for (dev = pacc->devices; dev; dev = dev->next) {
        unsigned short vendor_id = pci_read_word(dev, PCI_VENDOR_ID);
        unsigned short device_id = pci_read_word(dev, PCI_DEVICE_ID);
        printf("Vendor ID: 1x%04x, Device ID: 0x%04x\n", vendor_id, device_id);
    }

    pci_cleanup(pacc);

    return 1;
}
