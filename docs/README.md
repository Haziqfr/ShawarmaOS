

# ShawarmaOS

![License](https://img.shields.io/github/license/your-username/shawarmaos)
![Stars](https://img.shields.io/github/stars/your-username/shawarmaos)
![Forks](https://img.shields.io/github/forks/your-username/shawarmaos)
![Issues](https://img.shields.io/github/issues/your-username/shawarmaos)

---

## About The Project

ShawarmaOS is a from-scratch operating system built entirely from the ground up. It includes a custom bootloader, a monolithic kernel (ShawarmaKernel), and a partially developed C standard library (libc). The project is focused on learning and exploring low-level system design, operating system architecture, and hardware interaction.

---

## Features

- Custom bootloader (from scratch)
- BIOS boot support (x86)
- Very early low-level C runtime experimentation

---

## Planned Features

- First working kernel (ShawarmaKernel)
- x86_64 architecture support
- UEFI boot support
- Full C standard library (libc)
- Memory management (paging, heap, etc.)
- Basic device drivers
- Simple user-space environment

## Status

⚠️ **Early Development Stage**

ShawarmaOS is currently in very early development and only supports BIOS booting with minimal kernel functionality.

---

## Goals

- Learn about the process of making an operating system from scratch
- Learn the basics of systems programming
- Learn how to create an operating system from scratch from booting onwards
- Gain hands-on experience with kernel and runtime environment development

---


## Build & Run

### Requirements
- `gcc` or `clang`
- `nasm`
- `make`
- `qemu`

### Build
```bash
make
```

### Run
```bash
make run
```

### Clean
```bash
make clean
```

---

## Support

If you find this project interesting, consider starring the repository.
