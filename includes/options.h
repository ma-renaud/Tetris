#ifndef OPTIONS_H
#define OPTIONS_H

#include <cstdint>
#include <unordered_map>

namespace Options {

template <typename E>
constexpr auto to_underlying(E e) noexcept
{
  return static_cast<std::underlying_type_t<E>>(e);
}

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

struct GameOptions {
  DisplayMode display_mode{DisplayMode::WINDOW};
  Resolution resolution{Resolution::R1280x720};
  uint8_t nb_options = 2;
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

// Special behavior for ++DisplayMode
[[maybe_unused]] static DisplayMode &operator++(DisplayMode &dp) {
  using IntType = typename std::underlying_type<DisplayMode>::type;
  if (dp != static_cast<DisplayMode>( static_cast<IntType>(DisplayMode::NB_MODES) - 1 ))
    dp = static_cast<DisplayMode>( static_cast<IntType>(dp) + 1 );
  return dp;
}

// Special behavior for DisplayMode++
[[maybe_unused]] static DisplayMode operator++(DisplayMode &dp, int) {
  DisplayMode result = dp;
  ++dp;
  return result;
}

// Special behavior for --DisplayMode
[[maybe_unused]] static DisplayMode &operator--(DisplayMode &dp) {
  using IntType = typename std::underlying_type<DisplayMode>::type;
  if (static_cast<IntType>(dp) > 0)
    dp = static_cast<DisplayMode>( static_cast<IntType>(DisplayMode::NB_MODES) - 1 );
  return dp;
}

// Special behavior for DisplayMode--
[[maybe_unused]] static DisplayMode operator--(DisplayMode &dp, int) {
  DisplayMode result = dp;
  --dp;
  return result;
}

[[maybe_unused]] static std::string get_string_from_resolution(const Resolution &resolution) {
  auto it = resolution_to_string.find(resolution);
  if (it != resolution_to_string.end()) {
    return it->second;
  } else {
    return "What?";
  }
}

// Special behavior for ++Resolution
[[maybe_unused]] static Resolution &operator++(Resolution &r) {
  using IntType = typename std::underlying_type<Resolution>::type;
  r = static_cast<Resolution>( static_cast<IntType>(r) + 1 );
  if (r == Resolution::NB_RESOLUTIONS)
    r = static_cast<Resolution>( static_cast<IntType>(Resolution::NB_RESOLUTIONS) - 1 );
  return r;
}

// Special behavior for Resolution++
[[maybe_unused]] static Resolution operator++(Resolution &r, int) {
  Resolution result = r;
  ++r;
  return result;
}

// Special behavior for --DisplayMode
[[maybe_unused]] static Resolution &operator--(Resolution &dp) {
  using IntType = typename std::underlying_type<Resolution>::type;
  if (static_cast<IntType>(dp) > 0)
    dp = static_cast<Resolution>( static_cast<IntType>(Resolution::NB_RESOLUTIONS) - 1 );
  return dp;
}

// Special behavior for DisplayMode--
[[maybe_unused]] static Resolution operator--(Resolution &dp, int) {
  Resolution result = dp;
  --dp;
  return result;
}
}

#endif //OPTIONS_H
