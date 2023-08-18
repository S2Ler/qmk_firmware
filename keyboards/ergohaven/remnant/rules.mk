MCU = RP2040
BOARD = GENERIC_RP_RP2040
BOOTLOADER = rp2040
ALLOW_WARNINGS = yes
PICO_INTRINSICS_ENABLED = no

# Build Options
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
WS2812_DRIVER = vendor
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = WS2812
VIALRGB_ENABLE = no
SERIAL_DRIVER = vendor

NKRO_ENABLE = yes           # Enable N-Key Rollover
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
LTO_ENABLE = no
VIA_ENABLE = yes
TAP_DANCE_ENABLE = no
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes
CAPS_WORD_ENABLE = yes
REPEAT_KEY_ENABLE = yes
AUTO_SHIFT_ENABLE = yes