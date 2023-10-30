/*
 * Copyright 2011-2023 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include <bx/uint32_t.h>
#define BX_PLATFORM_EMSCRIPTEN 1
#include <iostream>

#include "./entry/entry.h"
#include "./entry/entry_html5.cpp"
#include "./entry/input.h"
#include "memory"
#include "logo.h"


namespace {

struct Point {
  double x;
  double y;
  Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class MainApp : public entry::AppI {
 public:
  // settings
  double scale_mult = 0.0001;

  // position data
  Point origin;
  double scale = 1;

  // input data
  std::shared_ptr<Point> last_mouse;
  int32_t last_wheel = 0;

  MainApp(const char* _name, const char* _description,
                    const char* _url)
      : entry::AppI(_name, _description, _url) {}

  void init(int32_t _argc, const char* const* _argv, uint32_t _width,
            uint32_t _height) override {
    // Args args(_argc, _argv);

    m_width = _width;
    m_height = _height;
    m_debug = BGFX_DEBUG_TEXT;
    m_reset = BGFX_RESET_VSYNC;

    bgfx::Init init;
    // init.type     = args.m_type;
    // init.vendorId = args.m_pciId;
    init.platformData.nwh =
        entry::getNativeWindowHandle(entry::kDefaultWindowHandle);
    init.platformData.ndt = entry::getNativeDisplayHandle();
    init.platformData.type =
        entry::getNativeWindowHandleType(entry::kDefaultWindowHandle);
    init.resolution.width = m_width;
    init.resolution.height = m_height;
    init.resolution.reset = m_reset;
    bgfx::init(init);

    // Enable debug text.
    bgfx::setDebug(m_debug);

    // Set view 0 clear state.
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f,
                       0);

    // imguiCreate();
  }

  virtual int shutdown() override {
    // imguiDestroy();

    // Shutdown bgfx.
    bgfx::shutdown();

    return 0;
  }

  bool update() override {
    if (!entry::processEvents(m_width, m_height, m_debug, m_reset,
                              &m_mouseState)) {
      // mouse begin
      auto mouse_cur = std::shared_ptr<Point>(
          new Point(m_mouseState.m_mx, m_mouseState.m_my));
      if (!last_mouse.get()) {
        last_mouse = mouse_cur;
      }

      // mouse process
      if (m_mouseState.m_buttons[entry::MouseButton::Left]) {
        double dx = mouse_cur->x - last_mouse->x;
        double dy = mouse_cur->y - last_mouse->y;
        origin.x += dx;
        origin.y += dy;
      }
      // scroll process
      auto cur_wheel = m_mouseState.m_mz;
      auto d_wheel = cur_wheel - last_wheel;
      auto new_scale = scale * (1 + d_wheel * scale_mult);
      scale = new_scale;

      // mouse end
      last_mouse = mouse_cur;
      last_wheel = cur_wheel;

      // Set view 0 default viewport.
      bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

      // This dummy draw call is here to make sure that view 0 is cleared
      // if no other draw calls are submitted to view 0.
      bgfx::touch(0);

      // Use debug font to print information about this example.
      bgfx::dbgTextClear();

      const bgfx::Stats* stats = bgfx::getStats();

      // bgfx::ima
      bgfx::dbgTextImage(bx::max<uint16_t>(uint16_t(stats->textWidth / 2), 20) -
                             20 + origin.x / 8,
                         bx::max<uint16_t>(uint16_t(stats->textHeight / 2), 6) -
                             6 + origin.y / 16,
                         40, 12, s_logo, 160);
      bgfx::dbgTextPrintf(0, 1, 0x0f, "scale=%lf x=%lf y=%lf", this->scale,
                          this->origin.x, this->origin.y);

      bgfx::dbgTextPrintf(
          80, 1, 0x0f,
          "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    "
          "\x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
      bgfx::dbgTextPrintf(
          80, 2, 0x0f,
          "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    "
          "\x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

      bgfx::dbgTextPrintf(
          0, 2, 0x0f,
          "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters.",
          stats->width, stats->height, stats->textWidth, stats->textHeight);

      // Advance to next frame. Rendering thread will be kicked to
      // process submitted rendering primitives.
      bgfx::frame();

      return true;
    }

    return false;
  }

  entry::MouseState m_mouseState;

  uint32_t m_width;
  uint32_t m_height;
  uint32_t m_debug;
  uint32_t m_reset;
};

}  // namespace

ENTRY_IMPLEMENT_MAIN(
    MainApp, "00-helloworld", "Initialization and debug text.",
    "https://bkaradzic.github.io/bgfx/examples.html#helloworld");
