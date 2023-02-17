#include<node/node.h> // NOLINT

namespace shallowBlue {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void Add(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check arg length
    if(args.Length() < 2) {
        // Throw js expection
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong Number of Arguments").ToLocalChecked()));
        return;
    }

    // Check arg types
    if(!args[0]->IsNumber() || !args[1]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong Type Arguments").ToLocalChecked()));
        return;
    }

    // Perform Operation
    double value = args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
    Local<Number> num = Number::New(isolate, value);

    args.GetReturnValue().Set(num);
}

void Initialize(Local<Object> exports) {
  NODE_SET_METHOD(exports, "add", Add);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

} // namespace shallowBlue
