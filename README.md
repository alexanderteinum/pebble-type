# Type ⌚️

A minimalist, typography-driven watchface for Pebble Time and Time Steel.

**Type** is designed to display only the essential data using a balanced, vertical layout. It relies on font weight and size to create visual hierarchy, rather than icons or clutter.

![Screenshot](screenshot.jpg)

## Features

- **Typographic Hierarchy:** Uses `LECO` (42px) for time and `Gothic` (24px) for data to clearly distinguish what matters most.
- **Vertical Balance:** Time is vertically centered, with steps and date perfectly balanced in the remaining space above and below.
- **Health Integration:** Shows today's step count at the top.
- **Silent Battery Monitor:** A discreet **1px red line** appears at the top of the screen only when battery drops to **20% or lower**.

## Installation

You can install this watchface via the Rebble app store (link coming soon) or build it from source.

### Build from source

Ensure you have the Pebble SDK installed.

```bash
# Build the project
pebble build

# Install to your watch
pebble install
```

## License

This project is licensed under the MIT License.
