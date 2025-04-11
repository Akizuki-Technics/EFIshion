<span style="color:red">These Functions are UNDER CONSTRUCTION. Everything Below is WIP, can be change at any moment.</span>

# EFIshion

**EFIshion** is a modern, sleek UEFI boot manager designed for flexibility, speed, and ease of configuration. Bringing a fresh approach to system booting, it makes managing multiple systems both fast and user-friendly.

## Features

- **Modern Interface**: A clean, easy-to-use interface designed for simplicity and style.
- **Fast Booting**: Optimized to ensure a quick and efficient boot process.
- **Easy Configuration**: No more complex setups. Configure your system effortlessly.
- **Cross-Platform Support**: Compatible with multiple operating systems and boot setups.

## Installation

### Prerequisites
- A UEFI-compatible system.
- A bootable USB or disk.

### Steps
1. Download the latest release from [here](#).
2. Copy the files to your bootable USB or disk.
3. Reboot your system and enter the UEFI settings.
4. Set the USB or disk as the primary boot device.
5. Restart, and EFIshion will manage your boot process!

## Configuration

You can easily configure EFIshion by editing the `config.ini` file located in the main directory. The settings are straightforward, and no complex syntax is required.

Example configuration:

```ini
[General]
default_boot = "Ubuntu"
timeout = 5

[Operating Systems]
"Ubuntu" = "/dev/sda1"
"Windows" = "/dev/sda2"
