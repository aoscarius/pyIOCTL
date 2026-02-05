# IOCTL Test Utilities

Small toolkit to convert C IOCTL headers to JSON format definitions and to call it with a Python ad hoc script.

## Files
- [ioctl](ioctl) - IOCTL caller script for low level device testing purpose
- [h2json](h2json) - C header → JSON converter
- [examples/*](examples) - Some C → JSON conversion and usage examples 

## Requirements
- Python 3
- Permissions to open the target device: `sudo chmod 666 /dev/target` or run the script with sudo

## Usage

1. Convert a header to JSON:
```bash
python3 h2json examples/tty.h examples/tty.json
```

2. Call a defined IOCTL from JSON:
```bash
python3 ioctl /dev/ttyS0 --config examples/tty.json call TIOCGWINSZ
```

3. Provide struct params (packed as defined in JSON):
```bash
python3 ioctl /dev/custom --config examples/custom.json call IOCTL_SET_FORMAT "mode0" 1920 1080
```

4. Raw IOCTL call:
```bash
python3 ioctl /dev/mydev raw 0x80045467 8
```

## Advanced Features
* _Array Handling_: Automatically detects type name[size] in C headers. In the executor, these are grouped and displayed as a single field with an ASCII preview if they contain bytes.

* _Zero Padding_: If you call a command with an array but provide fewer arguments, the suite automatically pads the buffer with zeros to prevent memory corruption.

* _Hex Dumping_: Every call prints the raw buffer hex-dump before and after the kernel execution, allowing you to debug memory alignment issues.

* _Non-Blocking I/O_: The executor opens devices in O_NONBLOCK mode to prevent the script from hanging on misconfigured hardware.

## Troubleshooting
* _Size Mismatch_: If the kernel returns an error (Inval), check if your header uses __attribute__((packed)). If so, you may need to manually adjust the format in the JSON to match.

* _Unknown Types_: If the parser encounters a custom typedef not in the [`TYPE_MAP`](h2json), it defaults to a 32-bit integer (I). You can add custom types to the [`TYPE_MAP`](h2json) dictionary in [h2json](h2json).

## Notes
- Be cautious with device access and struct layouts; mismatched formats may crash kernels or drivers.
