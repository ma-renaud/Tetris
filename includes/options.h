#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>

namespace Options {

enum class DisplayMode : uint8_t {
  WINDOW,
  FULLSCREEN,
  NB_MODES
};

static const DisplayMode display_modes[] = {DisplayMode::WINDOW, DisplayMode::FULLSCREEN};

enum class Resolution : uint8_t {
  R1280x720,
  R1920x1080,
  NB_RESOLUTIONS
};

static const Resolution resolutions[] = {Resolution::R1280x720, Resolution::R1920x1080};

static std::unordered_map<DisplayMode, std::string> const display_mode_to_string =
    {{DisplayMode::WINDOW, "Windowed"},
     {DisplayMode::FULLSCREEN, "Fullscreen"}};

static std::unordered_map<Resolution, std::string> const resolution_to_string =
    {{Resolution::R1280x720, "1280 x 720"},
     {Resolution::R1920x1080, "1920 x 1080"}};

[[maybe_unused]] static std::string get_string_from_display_mode(const DisplayMode &display_mode) {
  auto it = display_mode_to_string.find(display_mode);
  if (it != display_mode_to_string.end()) {
    return it->second;
  } else {
    return "What?";
  }
}

[[maybe_unused]] static std::string get_string_from_resolution(const Resolution &resolution) {
  auto it = resolution_to_string.find(resolution);
  if (it != resolution_to_string.end()) {
    return it->second;
  } else {
    return "What?";
  }
}

}

#endif //OPTIONS_H
