#include<napi.h>
#include"engine/engine.hpp"
#include"engine/game.hpp"

namespace sb {

Napi::Value Move(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if(info.Length() != 1) {
      Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
      return env.Null();
  }

  if(!info[0].IsString()) {
      Napi::TypeError::New(env, "Arguement must be string").ThrowAsJavaScriptException();
      return env.Null();
  }

  std::string fen = info[0].As<Napi::String>().ToString();
  Engine engine = Engine(fen);
  std::string m = engine.get_move();
  Napi::String s = Napi::String::New(env, m);

  return s;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "move"), Napi::Function::New(env, Move));
  return exports;
}

NODE_API_MODULE(move, Init);

} // namespace sb
