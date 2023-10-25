#pragma once

//! @file
//!
//! Copyright (c) Memfault, Inc.
//! See License.txt for details
//!
//! Platform overrides for the default configuration settings in the memfault-firmware-sdk.
//! Default configuration settings can be found in "memfault/config.h"

// Use GNU Build ID
#define MEMFAULT_USE_GNU_BUILD_ID 1

// Use the platform-specific 'memfault_platform_log_config.h' implementation
#define MEMFAULT_PLATFORM_HAS_LOG_CONFIG 1

// Optionally, use Memfault compact logs
//#define MEMFAULT_COMPACT_LOG_ENABLE 1

// Enable capture of entire ISR state at time of crash
#define MEMFAULT_NVIC_INTERRUPTS_TO_COLLECT 64

// Select the correct output region name for the Memfault RAM-Backed coredump
// storage buffer to be placed in the NRF5 SDK's non_init section
#define MEMFAULT_PLATFORM_COREDUMP_NOINIT_SECTION_NAME ".non_init.mflt_coredump"

