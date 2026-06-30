#include <iostream>

#include <SDL3/SDL.h>

#include <fraycast/global/global.hpp>
#include <fraycast/util/argparse/argparse.hpp>

fraycast::ARGParse argParse;

int main(int argc, char** argv){

  // --- Initialize globals ---
  argParse.init(argc, argv);

  fraycast::fraycastGlobals.cmdline = &argParse;

  std::cout << "exists called on --cfg: " << argParse.exists("--cfg") << std::endl;
  std::cout << "getarg called on --cfg: " << argParse.getArg("--cfg") << std::endl;

}