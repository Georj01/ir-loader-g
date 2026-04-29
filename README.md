# ir-loader-g

A minimalist VST3 Impulse Response (IR) loader plugin built with the JUCE framework. It provides a simple, zero-bureaucracy solution for loading `.wav` impulse responses for convolution reverb or cabinet simulation.

## Stack
- C++ 20
- JUCE Framework
- CMake

## Installation
Ensure you have CMake and a C++ compiler (like MSVC, Clang, or GCC) installed.

1. Clone the repository:
   ```bash
   git clone https://github.com/Georj01/ir-loader-g.git
   cd ir-loader-g
   ```

2. Configure and build via CMake:
   ```bash
   cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
   cmake --build build --config Release
   ```
   *Note: If JUCE is not found locally, CMake will automatically fetch it.*

3. The compiled `.vst3` file will be located in the `build/ir-loader-g_artefacts/Release/VST3/` directory.

## Usage
1. Place the generated `.vst3` plugin in your DAW's VST3 plugins folder.
2. Load `IR Loader` onto an audio track.
3. Click the interface to select and load your desired `.wav` impulse response file.
4. The plugin will immediately apply the convolution processing to the audio signal.
