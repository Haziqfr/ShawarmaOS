#ifndef PCI_CONFIG_H
#define PCI_CONFIG_H

#include <arch/i386/stdint.h>

#define PCI_CONFIG_CMD_PORT 0xCF8
#define PCI_CONFIG_DATA_PORT 0xCFC

uint32_t pci_config_read32(uint8_t bus, uint8_t device, uint8_t function,
			   uint8_t offset);

void pci_config_write32(uint8_t bus, uint8_t device, uint8_t function,
			uint8_t offset, uint32_t value);

#endif // PCI_CONFIG_H
