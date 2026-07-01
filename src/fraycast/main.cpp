#include <iostream>
#include <fstream>

#include <SDL3/SDL.h>

#include <fmt/format.h>

#include <fraycast/global/global.hpp>
#include <fraycast/util/argparse/argparse.hpp>

#include <tengine/util/filesystem/recur_file_by_ext.hpp>
#include <tengine/util/logger/logger.hpp>
#include <tengine/util/logger/logger_macros.hpp>
#include <tengine/util/cfgparse/cfg_node.hpp>
#include <tengine/util/cfgparse/parser.hpp>
#include <tengine/util/cfgparse/serializer.hpp>


fraycast::ARGParse argParse;


// --- Core function protoypes ---
void readCoreConfig();



int main(int argc, char** argv){

  // --- Initialize globals ---
  argParse.init(argc, argv);
  fraycast::fraycastGlobals.cmdline = &argParse;

  readCoreConfig();

}


void readCoreConfig(){

  const std::string cfgFilePath = "fraycast-assets/core.fcfg";
  std::ifstream cfgFile(cfgFilePath);

  if(!cfgFile.is_open()){
    std::cerr << fmt::format("Could not open core config file at {}", cfgFilePath) << std::endl;
    TENGINE_LOG_ERROR("readCoreConfig()", fmt::format("Could not open core config file at {}", cfgFilePath));
    std::abort();
  }

  tengine::util::CFGNode coreConfigNode = tengine::util::CFGParser::parse(cfgFile).front();
  tengine::util::CFGNode sdlFlags          = coreConfigNode.getChild("sdl_window_flags");

  fraycast::fraycastGlobals.CFG_WIN_RESIZABLE      = sdlFlags.getBoolean("resizeable", false);
  fraycast::fraycastGlobals.CFG_WIN_WIDTH          = sdlFlags.getInteger("win_width", 640);
  fraycast::fraycastGlobals.CFG_WIN_HEIGHT         = sdlFlags.getInteger("win_height", 480);
  fraycast::fraycastGlobals.CFG_WIN_FULLSCREEN     = sdlFlags.getBoolean("fullscreen", false);
  fraycast::fraycastGlobals.CFG_WIN_GRABS_MOUSE    = sdlFlags.getBoolean("grabs_mouse", false);
  fraycast::fraycastGlobals.CFG_WIN_GRABS_KEYBOARD = sdlFlags.getBoolean("grabs_keyboard", false);

}