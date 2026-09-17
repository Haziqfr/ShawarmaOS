#ifndef PCI_IDS_H
#define PCI_IDS_H

#include <arch/i386/stdint.h>

#define PCI_VENDOR_COUNT (sizeof(pci_vendors) / sizeof(pci_vendors[0]))

typedef struct {
	uint16_t id;
	const char *name;
} pci_vendor_t;

static const pci_vendor_t pci_vendors[] = {
	{ 0x1000, "Broadcom / LSI" },
	{ 0x1011, "Digital Equipment Corporation" },
	{ 0x1022, "Advanced Micro Devices, Inc. [AMD]" },
	{ 0x1033, "NEC Corporation" },
	{ 0x1042, "Micron" },
	{ 0x1043, "ASUSTeK Computer Inc." },
	{ 0x106B, "Apple Inc." },
	{ 0x1099, "Samsung Electronics Co., Ltd" },
	{ 0x10DE, "NVIDIA Corporation" },
	{ 0x10EC, "Realtek Semiconductor Co., Ltd." },
	{ 0x1274, "Ensoniq" },
	{ 0x1462, "Micro-Star International Co., Lts. [MSI]" },
	{ 0x15AD, "VMware" },
	{ 0x168C, "Qualcomm Atheros" },
	{ 0x17CB, "Qualcomm Technologies, Inc." },
	{ 0x1969, "Qualcomm Atheros" },
	{ 0x1AF4, "Red Hat, Inc." },
	{ 0x1B36, "Red Hat, Int." },
	{ 0x8086, "Intel Corporation" },

};

#endif // PCI_IDS_H
