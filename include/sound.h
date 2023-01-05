#ifndef SOUND_H
#define SOUND_H


int PlaySoundEffect(int soundEffectID, int ptrToMoby, int playbackMode, char *param_4);

enum SoundEffectIDS
{
SOUND_EFFECT_SPYRO_WALKING_1 = 0x0,
SOUND_EFFECT_SPYRO_WALKING_2 = 0x1,
SOUND_EFFECT_SPYRO_WALKING_3 = 0x2,
SOUND_EFFECT_SPYRO_PIVOT = 0x3,
SOUND_EFFECT_SPYRO_STOP = 0x3,
SOUND_EFFECT_SPYRO_JUMP = 0x4,
SOUND_EFFECT_SPYRO_LAND = 0x5,
SOUND_EFFECT_SPYRO_LAND_FLOP = 0x6,
SOUND_EFFECT_SPYRO_FLAME = 0x7,
SOUND_EFFECT_SPYRO_ROLL = 0x8,
SOUND_EFFECT_SPYRO_BONK = 0x9,
SOUND_EFFECT_UNK_SWIPE = 0xA,
SOUND_EFFECT_UNK_WOOD = 0xB,
SOUND_EFFECT_UNK_LIQUID = 0xC,
SOUND_EFFECT_UNK_LIQUID_2 = 0xD,
SOUND_EFFECT_UNK_LIQUID_3 = 0xE,
SOUND_EFFECT_UNK_HIT = 0xF,
SOUND_EFFECT_UNK_HIT_2 = 0x10,
SOUND_EFFECT_GEM_COLLECTED_DING = 0x11,
SOUND_EFFECT_DRAGON_PEDISTOOL_DING = 0x11,
SOUND_EFFECT_GEM_HIT_FLOOR = 0x12,
SOUND_EFFECT_SPARX_GRAB_GEM = 0x12,
SOUND_EFFECT_CHARGING = 0x13,
SOUND_EFFECT_FLAME_TOUCH_SURFACE = 0x14,
SOUND_EFFECT_SPYRO_DIZZY = 0x15,
SOUND_EFFECT_ENEMY_DISAPEAR = 0x16,
SOUND_EFFECT_PORTAL_SHIMMER = 0x17,
SOUND_EFFECT_UNK_GRASS = 0x18,
SOUND_EFFECT_GOOP = 0x19,
SOUND_EFFECT_OPEN_PAUSE_MENU_DING = 0x1A,
SOUND_EFFECT_OPEN_INVENTORY_MENU = 0x1A,
SOUND_EFFECT_PAUSE_MENU_CHANGE_SELECTION_DING = 0x1B,
SOUND_EFFECT_PAUSE_MENU_CHANGE_MENU_DING = 0x1C,
SOUND_EFFECT_PAUSE_MENU_EXIT_DING = 0x1C,
SOUND_EFFECT_DRAGON_FREE = 0x1D,
SOUND_EFFECT_DRAGON_BREAK_OPEN = 0x1E,
SOUND_EFFECT_DRAGON_RUMBLE = 0x1F,
SOUND_EFFECT_DRAGON_DISAPEAR = 0x20,
SOUND_EFFECT_DRAGON_BEGIN_DISAPEAR = 0x21,
SOUND_EFFECT_DRAGON_UNK = 0x22,
SOUND_EFFECT_TITLE_SCREEN_MEMORY_CARD_SELECTION = 0x23,
SOUND_EFFECT_SPYRO_HIT = 0x24,
SOUND_EFFECT_UNK_DING = 0x25,
SOUND_EFFECT_DEEP_WIND = 0x26,
SOUND_EFFECT_SUNNY_FLIGHT_WALL_LOWERS = 0x26,
SOUND_EFFECT_WATERFALL = 0x27,
SOUND_EFFECT_BIRD_1 = 0x28,
SOUND_EFFECT_BIRD_2 = 0x29,
SOUND_EFFECT_BIRD_3 = 0x2A,
SOUND_EFFECT_BIRD_4 = 0x2B,
SOUND_EFFECT_BIRD_5 = 0x2C,
SOUND_EFFECT_BIRD_6 = 0x2D,
SOUND_EFFECT_HAWK_1 = 0x2E,
SOUND_EFFECT_HAWK_2 = 0x2F,
SOUND_EFFECT_SEAGULL_1 = 0x30,
SOUND_EFFECT_SEAGULL_2 = 0x31,
SOUND_EFFECT_WHIRLWIND = 0x32,
SOUND_EFFECT_MONEYBAG_GNORC_BELTCH = 0x33,
SOUND_EFFECT_UNK_GRASS_2 = 0x34,
SOUND_EFFECT_UNK_GRASS_3 = 0x35,
SOUND_EFFECT_MONEYBAG_GNORC_HIT = 0x36,
SOUND_EFFECT_MONEYBAG_GNORC_GEMS_SHAKE_1 = 0x37,
SOUND_EFFECT_MONEYBAG_GNORC_GEMS_SHAKE_2 = 0x38,
SOUND_EFFECT_MONEYBAG_GNORC_DEATH_GROAN_1 = 0x39,
SOUND_EFFECT_MONEYBAG_GNORC_DEATH_GRAON_2 = 0x3A,
SOUND_EFFECT_ARTISANS_GNORC_SCARED = 0x3B,
SOUND_EFFECT_ARTISANS_GNORC_SHIVERING_1 = 0x3C,
SOUND_EFFECT_ARTISANS_GNORC_SHIVERING_2 = 0x3D,
SOUND_EFFECT_ARTISANS_GNORC_HIT = 0x3E,
SOUND_EFFECT_UNK_HIT_3 = 0x3F,
SOUND_EFFECT_UNK_HIT_4 = 0x40,
SOUND_EFFECT_WOODEN_CHEST_BREAK = 0x41,
SOUND_EFFECT_LIFE_CHEST_OPEN = 0x42,
SOUND_EFFECT_LIFE_CHEST_RUMBLE = 0x43,
SOUND_EFFECT_LIFE_CHEST_BREAK = 0x44,
SOUND_EFFECT_LIFE_CHEST_CLOSE = 0x45,
SOUND_EFFECT_SHEEP_BOUNCE = 0x46,
SOUND_EFFECT_SHEEP_HIT = 0x47,
SOUND_EFFECT_SPYRO_2_POWERUP = 0x48,
SOUND_EFFECT_SPARX_EAT = 0x49,
SOUND_EFFECT_SPARX_FULL_EAT = 0x4A,
SOUND_EFFECT_LIFE_CHEST_BLINK = 0x4B,
SOUND_EFFECT_DRAGON_IDLE_SHAKE = 0x4C
};

enum SoundPlaybackModes
{
    SOUND_PLAYBACK_MODE_NORMAL = 0x10,
    SOUND_PLAYBACK_MODE_CONNECTED_TO_MOBY = 0x8
};

#endif //SOUND_H