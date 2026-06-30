#pragma once

#include <vector>
#include <string>

namespace fraycast{

class ARGParse{

public:

  void init(int argc, char** argv){
    m_args.assign(argv, argv + argc);
  }

  bool exists(const std::string& name){

    for(std::string arg : m_args){
      if(arg == name){
        return true;
      }
    }

    return false;

  }

  std::string getArg(const std::string& name, const std::string& fallback = ""){

    if(!exists(name)){ return fallback; }

    for(int i = 0; i < m_args.size(); i++){

      if(m_args[i] == name){

        if(i == m_args.size() - 1){
          return fallback;
        }

        return m_args[i + 1];
      }

    }

    return fallback;

  }

private:
  std::vector<std::string> m_args;

};

}