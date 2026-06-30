#pragma once

#include <fraycast/util/argparse/argparse.hpp>

namespace fraycast{

struct fraycast_globals_t{

  // --- Read from config file ---
  bool    CFG_WIN_RESIZABLE       = true;
  int     CFG_WIN_WIDTH           = 640;
  int     CFG_WIN_HEIGHT          = 480;
  bool    CFG_WIN_FULLSCREEN      = false;
  bool    CFG_WIN_GRABS_MOUSE     = true;
  bool    CFG_WIN_GRABS_KEYBOARD  = false;

  // --- Pointers to various utilites --
  ARGParse* cmdline               = nullptr;

};

inline fraycast_globals_t fraycastGlobals;

}