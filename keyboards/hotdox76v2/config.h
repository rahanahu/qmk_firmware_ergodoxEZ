// Copyright 2021 JasonRen(biu)
// Copyright 2022 Drashna Jael're (@Drashna Jael're)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disabletion features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define EE_HANDS
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#define TAPPING_TERM_PER_KEY
#define SPLIT_TRANSACTION_IDS_KB KEYBOARD_CURRENT_ALPA_SYNC
