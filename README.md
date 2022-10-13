# nRF5 SDK Segger Embedded Studio Memfault Example

This is an example project for Segger Embedded Studio and the nRF5 SDK,
targeting the nRF52480-DK ("pca10056") dev board.

## Building

1. download and unpack the nRF5 SDK. tested with v15.2.0, which can be
   downloaded
   [here](https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/nRF5_SDK_15.2.0_9412b96.zip).
2. clone this repo into the nRF5 SDK directory tree:

   ```bash
   # assuming current working directory is the root of the unpacked nRF5 SDK
   git clone --recursive \
      https://github.com/memfault/nrf5-segger-embedded-studio-example.git \
      examples/peripheral/memfault-example
   ```

3. disable the nRF5 SDK `app_error.h` file by renaming it:

   ```bash
   mv components/libraries/util/app_error.h{,.overriden}
   ```

4. open segger embedded studio and open the solution from
   `examples/peripheral/memfault-example/pca10056/blank/ses/cli_pca10056.emProject`
5. build and flash to the nRF52480-DK
6. use the built-in RTT terminal to execute the Memfault Demo CLI commands
