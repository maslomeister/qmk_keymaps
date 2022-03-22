/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "rev1.h"

#ifdef RGB_MATRIX_ENABLE

  // Logical Layout
  // Columns
  // Left
  // 0  1  2  3  4  5
  //                   ROWS
  // 25 24 19 18 11 10   0
  //    03    02    01
  // 26 23 20 17 12 09   1
  //    04    05    06
  // 27 22 21 16 13 08   2
  //
  //          15 14 07   3
  //
  // Right
  // 0  1  2  3  4  5
  //                    ROWS
  // 25 24 19 18 11 10   4
  //    03    02    01
  // 26 23 20 17 12 09   5
  //    04    05    06
  // 27 22 21 16 13 08   6
  //
  //          15 14 07   7
  //
  // Physical Layout
  // Columns
  // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
  //                                           ROWS
  // 25 24 19 18 11 10       10 11 18 19 24 25  0
  //    03    02    01       01    02    03
  // 26 23 20 17 12 09       09 12 17 20 23 26  1
  //    04                               04
  // 27 22 21 16 13 08       08 13 16 21 22 27  2
  //          05    06       06    05
  //           15 14 07     07 14 15              3

led_config_t g_led_config = { {
    {  24,  23,  18,  17,  10,   9 },
    {  25,  22,  19,  16,  11,   8 },
    {  26,  21,  20,  15,  12,   7 },
    {  27,  NO_LED, NO_LED,  14,  13,   6 },
    {  51,  50,  45,  44,  37,  36 },
    {  52,  49,  46,  43,  38,  35 },
    {  53,  48,  47,  42,  39,  34 },
    {  54,  NO_LED, NO_LED,  41,  40,  33 }
}, {
    {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, { 105,  63 },
    {  90,  39 }, {  90,  21 }, {  90,   4 }, {  75,   2 }, {  75,  19 }, {  75,  37 }, {  90,  58 },
    {  75,  55 }, {  60,  35 }, {  60,  13 }, {  60,   0 }, {  45,   3 }, {  45,  20 }, {  45,  37 },
    {  30,  42 }, {  30,  24 }, {  30,   7 }, {  15,   7 }, {  15,  24 }, {  15,  41 }, {   0,  24 },
    { 139,  16 }, { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 }, { 119,  63 },
    { 134,  39 }, { 134,  21 }, { 134,   4 }, { 149,   2 }, { 149,  19 }, { 149,  37 }, { 134,  58 },
    { 149,  55 }, { 164,  35 }, { 164,  13 }, { 164,   0 }, { 179,   3 }, { 179,  20 }, { 179,  37 },
    { 194,  42 }, { 194,  24 }, { 194,   7 }, { 209,   7 }, { 209,  24 }, { 209,  41 }, { 224,  24 }
}, {
    2, 2, 2, 2, 2, 2, 1,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 1,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1, 1, 1
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif
