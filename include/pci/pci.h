#ifndef PCI_PCI_H
#define PCI_PCI_H

#include <arch/i386/stdint.h>

void pci_init(void);
void pci_scan(uint8_t bus);

#endif // PCI_PCI_H
