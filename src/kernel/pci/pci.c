#include <pci/pci.h>
#include <pci/config.h>
#include <pci/ids.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include <arch/i386/stdint.h>

void pci_init(void)
{
	kprintf("[PCI] Scanning...\n");

	pci_scan(0);

	kprintf("[PCI] Scan complete\n");
}

static const char *pci_vendor_name(uint16_t id)
{
	for (size_t i = 0; i < sizeof(pci_vendors) / sizeof(pci_vendors[0]);
	     i++) {
		if (pci_vendors[i].id == id)
			return pci_vendors[i].name;
	}

	return "Unknown";
}

static bool pci_bus_scanned[256];

void pci_scan(uint8_t bus)
{
	if (pci_bus_scanned[bus])
		return;

	pci_bus_scanned[bus] = true;

	for (uint8_t dev = 0; dev < 32; dev++) {
		if ((uint16_t)(pci_config_read32(bus, dev, 0, 0x00) & 0xFFFF) ==
		    0xFFFF)
			continue;

		uint32_t header0 = pci_config_read32(bus, dev, 0, 0x0C);
		uint8_t max_func = (header0 & 0x800000) ? 8 : 1;

		for (uint8_t func = 0; func < max_func; func++) {
			uint32_t pci_id =
				pci_config_read32(bus, dev, func, 0x00);
			uint16_t vendor_id = pci_id & 0xFFFF;
			uint16_t device_id = pci_id >> 16;

			if (vendor_id == 0xFFFF)
				continue;

			uint32_t header =
				pci_config_read32(bus, dev, func, 0x0C);
			uint8_t header_type = (header >> 16) & 0x7F;

			if (header_type != 0x1 && header_type != 0x2) {
				kprintf("[PCI] %x:%x.%x vendor=%#x (%s) device=%#x\n",
					bus, dev, func, vendor_id,
					pci_vendor_name(vendor_id), device_id);

				continue;
			}

			uint8_t sec_bus =
				(pci_config_read32(bus, dev, func, 0x18) >> 8) &
				0xFF;

			kprintf("[PCI] %x:%x.%x vendor=%#x (%s) device=%#x -> bus=%d\n",
				bus, dev, func, vendor_id,
				pci_vendor_name(vendor_id), device_id, sec_bus);

			if (sec_bus == 0 || sec_bus == bus)
				continue;
			pci_scan(sec_bus);
		}
	}
}
