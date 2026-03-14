# Type

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Build](https://github.com/alexanderteinum/pebble-type/actions/workflows/build.yml/badge.svg)](https://github.com/alexanderteinum/pebble-type/actions/workflows/build.yml)

Type is an opinionated, minimalist watchface for Pebble. It prioritizes instant legibility and native performance.

![Screenshot](screenshot.png)

## Design Philosophy & Features

- **High Contrast:** Designed specifically for the reflective Memory LCD. Black text on a white background offers superior contrast in all lighting conditions.
- **Zero Latency:** Relies exclusively on on-device data (Time & Health API). No web APIs, no loading times, and zero impact on phone battery.
- **Typographic Hierarchy:** A vertically balanced stack using native system fonts (Bitham and Gothic) for crisp, artifact-free rendering.
- **Calm Tech:** The interface remains distraction-free. A red line appears along the edge of the screen when the battery drops to 20% or lower.

## Build From Source

Ensure you have the Pebble SDK installed.

```bash
# Build the project
pebble build

# Install to watch
pebble install --cloudpebble
```

## License

Distributed under the MIT License. See [LICENSE](LICENSE) for more information.
