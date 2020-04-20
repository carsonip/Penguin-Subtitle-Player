#ifndef PREFCONSTANTS_H
#define PREFCONSTANTS_H

#include "QString"

namespace PrefConstants {
const static int BG_COLOR = 0;
const static int BG_ALPHA = 30;
const static int BG_ALPHA_MIN = 2;

const static int ADJUST_INTERVAL = 1000;
const static int ADJUST_INTERVAL_MAX = 3600000;
const static int ADJUST_INTERVAL_STEP = 50;

const static double SPEED_FACTOR = 1.0;
const static double SPEED_FACTOR_MAX = 10.0;
const static double SPEED_FACTOR_MIN = 0.1;
const static double SPEED_FACTOR_STEP = 0.002;
const static bool RESET_SPEED_FACTOR_ON_LAUNCH = true;

const QString ENCODING = "UTF-8";
const static bool USE_DETECTED_ENCODING = true;

const QString FONT = "Noto Sans,22,-1,5,75,0,0,0,0,0,Bold";
const static bool FONT_SHADOW_ENABLE = true;
const static int FONT_SHADOW_BLUR_RADIUS = 8;
const static int FONT_SHADOW_BLUR_RADIUS_MAX = 100;
const static int FONT_SHADOW_BLUR_RADIUS_STEP = 1;
const static int FONT_SHADOW_COLOR = 0;
const static int FONT_SHADOW_OFFSET_X = 0;
const static int FONT_SHADOW_OFFSET_Y = 0;
const static int FONT_SHADOW_OFFSET_LIMIT = 100;

const static int FONT_COLOR = 4294967295; // white

const static bool REMEMBER_WINDOW_POS_AND_SIZE = true;
const static int WINDOW_X = 0;
const static int WINDOW_Y = 0;
const static int WINDOW_WIDTH = 700;
const static int WINDOW_HEIGHT = 200;
} // namespace PrefConstants

#endif // PREFCONSTANTS_H
