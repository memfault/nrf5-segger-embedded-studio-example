# nRF5 SDK Segger Embedded Studio Memfault Example

This is an example project for Segger Embedded Studio and the nRF5 SDK,
targeting the nRF52480-DK ("pca10056") dev board.

## Building

### Prerequisites

Make sure the `SDK_ROOT` macro is set up in Segger Embedded Studio:

- https://infocenter.nordicsemi.com/topic/com.nordic.infocenter.meshsdk.v3.1.0/md_doc_getting_started_how_to_build.html#how_to_build_segger_setup

### Setup Steps

1. Download and unpack the nRF5 SDK. This example was tested with v15.2.0, which
   can be downloaded
   [here](https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/nRF5_SDK_15.2.0_9412b96.zip).

2. In the nRF5 SDK, disable the nRF5 SDK `app_error.h` file by renaming it:

   ```bash
   mv components/libraries/util/app_error.h{,.overriden}
   ```

3. Clone this repo somewhere:

   ```bash
   git clone --recursive \
      https://github.com/memfault/nrf5-segger-embedded-studio-example.git
   ```

4. Open segger embedded studio and open the solution from
   `examples/peripheral/memfault-example/pca10056/blank/ses/cli_pca10056.emProject`

5. Build and flash to the nRF52480-DK

6. Use the built-in RTT terminal to execute the Memfault Demo CLI commands

## Details on Memfault integration

The overall strategy to integrating Memfault to a Segger Embedded Studio project
is as follows:

1. Add the memfault source files:

   1. Add the memfault sdk as a git submodule (only if the project is already
      using git, otherwise just clone the Memfault SDK instead):

      ```bash
      ❯ git submodule add https://github.com/memfault/memfault-firmware-sdk.git third_party/memfault-firmware-sdk
      ```

   2. Add the source files; for example, as a virtual folder with the following
      exclusions (example below is the content in the `.emProject` file itself;
      can be added from within Segger Embedded Studio or by manually editing the
      file in a text editor):

      ```xml
      <folder
      Name="third_party/memfault-firmware-sdk"
      exclude="cmake;components/http;examples;scripts;tests;atmel;cypress;dialog;emlib;esp8266_sdk;esp_idf;freertos;mynewt;nxp;particle;qp;s32sdk;stm32cube;templates;zephyr;nrf5_coredump_storage.c"
      filter="*.c"
      path="../../../third_party/memfault-firmware-sdk"
      recurse="Yes" />
      ```

2. Add the necessary search paths to the Preprocessor configuration:

   ```plaintext
   ../../../third_party/memfault-firmware-sdk/examples/nrf5/apps/memfault_demo_app/third_party/memfault/sdk_overrides
   ../../../third_party/memfault-firmware-sdk/components/include
   ../../../memfault_port
   ../../../third_party/memfault-firmware-sdk/ports/include
   ```

3. Modify the linker XML (usually the `flash_placement.xml` file) to include the
   following section for the Build ID:

   ```xml
   <ProgramSection alignment="4" load="Yes" name=".text" />
   <!-- placing it right after the .text section -->
    <ProgramSection alignment="4" keep="Yes" load="Yes" name=".note.gnu.build-id" inputsections="*(.note.gnu.build-id)" address_symbol="__start_gnu_build_id_start" end_symbol="__stop_gnu_build_id_stop" />
   ```

4. Add the linker option for build id (project Options -> Code -> Linker ->
   Additional Linker Options, add `--build-id` on its own line). Example here
   for the `.emProject` file:

   ```xml
   <solution Name="MyProject" target="8" version="2">
     <project Name="MyProject">
       <configuration
         ...
         linker_additional_options="--build-id"
   ```

5. Add the necessary memfault port files; in this example, they're added in the
   `memfault_port` folder as a virtual folder, which can be added through the
   UI, or by directly modifying the `.emProject` XML:

   ```xml
   <folder
      Name="memfault_port"
      exclude=""
      filter="*.c"
      path="../../../memfault_port"
      recurse="Yes" />
   ```
