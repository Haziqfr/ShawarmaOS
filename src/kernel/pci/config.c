#include <pci/config.h>
#include <arch/i386/stdint.h>
#include <arch/i386/io.h>

uint32_t pci_config_read32(uint8_t bus, uint8_t device, uint8_t function,
			   uint8_t offset)
{
	uint32_t address = 0x80000000 | ((uint32_t)bus << 16) |
			   ((uint32_t)device << 11) |
			   ((uint32_t)function << 8) | (offset & 0xFC);

	outl(PCI_CONFIG_CMD_PORT, address);
	return inl(PCI_CONFIG_DATA_PORT);
}

void pci_config_write32(uint8_t bus, uint8_t device, uint8_t function,
			uint8_t offset, uint32_t value)
{
	uint32_t address = 0x80000000 | ((uint32_t)bus << 16) |
			   ((uint32_t)device << 11) |
			   ((uint32_t)function << 8) | (offset & 0xFC);

	outl(PCI_CONFIG_CMD_PORT, address);
	outl(PCI_CONFIG_DATA_PORT, value);
}
