/* ----------------------------------------------------------------------------
* ergoDOX layout : QWERTY (modified from the Kinesis layout)
* -----------------------------------------------------------------------------
* Copyright (c) 2012 Ben Blazak <benblazak.dev@gmail.com>
* Released under The MIT License (MIT) (see "license.md")
* Project located at <https://github.com/benblazak/ergodox-firmware>
* -------------------------------------------------------------------------- */
#include <stdint.h>
#include <stddef.h>
#include <avr/pgmspace.h>
#include "../../../lib/data-types/misc.h"
#include "../../../lib/usb/usage-page/keyboard--short-names.h"
#include "../../../lib/key-functions/public.h"
#include "../matrix.h"
#include "../layout.h"
// FUNCTIONS ------------------------------------------------------------------
void kbfun_layer_pop_all(void) {
  kbfun_layer_pop_1();
  kbfun_layer_pop_2();
  kbfun_layer_pop_3();
  kbfun_layer_pop_4();
  kbfun_layer_pop_5();
  kbfun_layer_pop_6();
  kbfun_layer_pop_7();
  kbfun_layer_pop_8();
  kbfun_layer_pop_9();
  kbfun_layer_pop_10();
}

// DEFINITIONS ----------------------------------------------------------------
#define  kprrel   &kbfun_press_release
#define  ktog     &kbfun_toggle
#define  ktrans   &kbfun_transparent
#define  lpush1   &kbfun_layer_push_1
#define  lpush2   &kbfun_layer_push_2
#define  lpush3   &kbfun_layer_push_3
#define  lpush4   &kbfun_layer_push_4
#define  lpush5   &kbfun_layer_push_5
#define  lpush6   &kbfun_layer_push_6
#define  lpush7   &kbfun_layer_push_7
#define  lpush8   &kbfun_layer_push_8
#define  lpush9   &kbfun_layer_push_9
#define  lpush10  &kbfun_layer_push_10
#define  lpop     &kbfun_layer_pop_all
#define  lpop1    &kbfun_layer_pop_1
#define  lpop2    &kbfun_layer_pop_2
#define  lpop3    &kbfun_layer_pop_3
#define  lpop4    &kbfun_layer_pop_4
#define  lpop5    &kbfun_layer_pop_5
#define  lpop6    &kbfun_layer_pop_6
#define  lpop7    &kbfun_layer_pop_7
#define  lpop8    &kbfun_layer_pop_8
#define  lpop9    &kbfun_layer_pop_9
#define  lpop10   &kbfun_layer_pop_10
#define  dbtldr   &kbfun_jump_to_bootloader
#define  sshprre  &kbfun_shift_press_release
#define  s2kcap   &kbfun_2_keys_capslock_press_release
#define  slpunum  &kbfun_layer_push_numpad
#define  slponum  &kbfun_layer_pop_numpad
// ----------------------------------------------------------------------------

// LAYOUT ---------------------------------------------------------------------
const uint8_t PROGMEM _kb_layout[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER( // main layer
    // unused
    0,
    // left hand
    _esc,       _1,         _2,         _3,         _4,         _5,         1,
    _grave,     _Q,         _W,         _F,         _P,         _G,         _bracketL,
    _tab,       _A,         _R,         _S,         _T,         _D,
    _shiftL,    _Z,         _X,         _C,         _V,         _B,         _dash,
    _guiL,      _capsLock,  _print,     _scrollLock,_pause,
                                                                _ctrlL,     _altL,
                                                    0,          0,          _home,
                                                    _bs,        _del,       _end,
    // right hand
    1,          _6,         _7,         _8,         _9,         _0,         _insert,
    _bracketR,  _J,         _L,         _U,         _Y,         _semicolon, _quote,
                _H,         _N,         _E,         _I,         _O,         _backslash,
    _equal,     _K,         _M,         _comma,     _period,    _slash,     _shiftR,
                            _arrowL,    _arrowD,    _arrowU,    _arrowR,    _guiR, 
    _altR,      _ctrlR,
    _pageU,     0,          0,
    _pageD,     _enter,     _space
),
// LAYER 1
KB_MATRIX_LAYER( // function keys, and bootloader
    // unused
    0,
    // left hand
    _F1,        _F2,        _F3,        _F4,        _F5,        _F6,        1,
    0,          0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,
                                                                0,          0,
                                                    0,          0,          0,
                                                    0,          0,          0,
    // right hand
    // was 4 for +4
    1,          _F7,        _F8,        _F9,        _F10,       _F11,       _F12,
    0,          0,          0,          0,          0,          0,          0,
                0,          0,          0,          0,          0,          0,
    0,          0,          0,          0,          0,          0,          0,
                            0,          0,          0,          0,          0,
    0,          0,
    0,          0,          0,
    0,          0,          0
),
};
// ----------------------------------------------------------------------------

// PRESS ----------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_press[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
    // unused
    NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpush1,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                                                                kprrel,     kprrel,
                                                    NULL,       NULL,       kprrel,
                                                    kprrel,     kprrel,     kprrel,
    // right hand
    lpush1,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                            kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,
    kprrel,     NULL,       NULL,
    kprrel,     kprrel,     kprrel
),
// LAYER 1
KB_MATRIX_LAYER(
    // unused
    NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     lpop1,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       dbtldr,
    NULL,       NULL,       NULL,       NULL,       NULL,
                                                                NULL,       NULL,
                                                    NULL,       NULL,       NULL,
                                                    NULL,       NULL,       NULL,
    // right hand
    lpop1,      kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
                NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    dbtldr,     NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
                            NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,
    NULL,       NULL,       NULL,
    NULL,       NULL,       NULL
),
};
// ----------------------------------------------------------------------------

// RELEASE --------------------------------------------------------------------
const void_funptr_t PROGMEM _kb_layout_release[KB_LAYERS][KB_ROWS][KB_COLUMNS] = {
// LAYER 0
KB_MATRIX_LAYER(
    // unused
    NULL,
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                                                                kprrel,     kprrel,
                                                    NULL,       NULL,       kprrel,
                                                    kprrel,     kprrel,     kprrel,
    // right hand
    NULL,       kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
                            kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    kprrel,     kprrel,
    kprrel,     NULL,       NULL,
    kprrel,     kprrel,     kprrel
),
// LAYER 1
    KB_MATRIX_LAYER(
    // unused
    NULL,	
    // left hand
    kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,
                                                                NULL,       NULL,
                                                    NULL,       NULL,       NULL,
                                                    NULL,       NULL,       NULL,
    // right hand
    NULL,      kprrel,     kprrel,     kprrel,     kprrel,     kprrel,     kprrel,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
                NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,       NULL,       NULL,       NULL,       NULL,       NULL,
                            NULL,       NULL,       NULL,       NULL,       NULL,
    NULL,       NULL,
    NULL,       NULL,       NULL,
    NULL,       NULL,       NULL
),
};
// ----------------------------------------------------------------------------
