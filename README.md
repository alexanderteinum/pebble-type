# Type

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build](https://github.com/alexanderteinum/pebble-type/actions/workflows/build.yml/badge.svg)](https://github.com/alexanderteinum/pebble-type/actions/workflows/build.yml)

Type is a minimalist watchface for Pebble, built for legibility and clean aesthetics.

![Screenshot](screenshot.png)

## Features

- **Inter Typography:** Uses the Inter typeface for a modern, refined look.
- **High Contrast:** Black text on a white background for superior visibility on the Memory LCD.
- **Calm Tech:** No distractions. A subtle red line appears only when the battery drops below 20%.
- **Purely Local:** Uses on-device data only (Time & Health API). No Bluetooth required, no impact on phone battery.

## Build From Source

Ensure you have the Pebble SDK installed.

```bash
# Build the project
pebble build

# Install to watch
pebble install --cloudpebble
```

## Credits

- **Inter Font:** Designed by Rasmus Andersson. Licensed under the [SIL Open Font License, Version 1.1](https://scripts.sil.org/OFL).

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.
