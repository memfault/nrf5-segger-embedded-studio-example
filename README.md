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

## Details on Memfault integration

The overall strategy to integrating Memfault to a Segger Embedded Studio project
is as follows:

1. add the memfault source files:

   1. add the memfault sdk as a git submodule:

      ```bash
      ❯ git submodule add https://github.com/memfault/memfault-firmware-sdk.git third_party/memfault-firmware-sdk
      ```

   2. add the source files; for example, as a virtual folder with the following
      exclusions:

      ```xml
      <folder
      Name="third_party/memfault-firmware-sdk"
      exclude="cmake;components/http;examples;scripts;tests;atmel;cypress;dialog;emlib;esp8266_sdk;esp_idf;freertos;mynewt;nxp;particle;qp;s32sdk;stm32cube;templates;zephyr;nrf5_coredump_storage.c"
      filter="*.c"
      path="../../../third_party/memfault-firmware-sdk"
      recurse="Yes" />
      ```

2. add the necessary search paths to the Preprocessor configuration:

   ```plaintext
   ../../../third_party/memfault-firmware-sdk/examples/nrf5/apps/memfault_demo_app/third_party/memfault/sdk_overrides
   ../../../third_party/memfault-firmware-sdk/components/include
   ../../../memfault_port
   ../../../third_party/memfault-firmware-sdk/ports/include
   ```

3. modify the linker to include the following section for the Build ID:

   ```xml
   <ProgramSection alignment="4" load="Yes" name=".text" />
   <!-- placing it right after the .text section -->
    <ProgramSection alignment="4" keep="Yes" load="Yes" name=".note.gnu.build-id" inputsections="*(.note.gnu.build-id)" address_symbol="__start_gnu_build_id_start" end_symbol="__stop_gnu_build_id_stop" />
   ```

4. add the linker option for build id:

   ```xml
   linker_additional_options="--build-id"
   ```

5. add the necessary memfault port files; in this example, they're added in the
   `memfault_port` folder as a virtual folder:

   ```xml
   <folder
      Name="memfault_port"
      exclude=""
      filter="*.c"
      path="../../../memfault_port"
      recurse="Yes" />
   ```
