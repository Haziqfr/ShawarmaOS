# ShawarmaOS

![GitHub License](https://img.shields.io/github/license/Haziqfr/Shawarma-OS?style=flat)
![Stars](https://img.shields.io/github/stars/Haziqfr/Shawarma-OS?style=flat)
![Forks](https://img.shields.io/github/forks/Haziqfr/Shawarma-OS)
![Issues](https://img.shields.io/github/issues/Haziqfr/Shawarma-OS)



---

## About The Project

ShawarmaOS is a from-scratch operating system built entirely from the ground up. It includes a custom bootloader, a monolithic kernel (ShawarmaKernel), and a partially developed C standard library (libc). The project is focused on learning and exploring low-level system design, operating system architecture, and how software interacts with hardware at a fundamental level.

---

## License

This project is licensed under the [GNU General Public License v2.0.](https://www.gnu.org/licenses/old-licenses/gpl-2.0.html#SEC1)

See the `LICENSE` file in this repository for full details.

---

## Features

- Custom bootloader (written from scratch)
- BIOS boot support (x86)
- Early low-level C runtime experimentation

---

## Planned Features

- First working kernel (ShawarmaKernel)
- x86_64 architecture support
- UEFI boot support
- Full C standard library (libc)
- Memory management (paging, heap, etc.)
- Basic device drivers
- Simple user-space environment

---

## Status

⚠️ **Early Development Stage**

ShawarmaOS is currently in very early development. At this stage, it only supports BIOS booting and contains minimal system functionality.

---

## Goals

- Understand how an operating system is built from the ground up  
- Learn the fundamentals of low-level systems programming  
- Gain hands-on experience with the full boot-to-kernel development process  
- Build a practical understanding of operating system internals and runtime systems  

---

## Build & Run

### Requirements
- GCC or Clang  
- NASM  
- Make  
- QEMU  

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
