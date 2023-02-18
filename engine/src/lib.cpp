#include<node/node_api.h>

namespace shallowBlue {

napi_value Move(napi_env env, napi_callback_info args) {
    napi_status status;
    napi_value move;

    status = napi_create_string_utf8(env, "d5", NAPI_AUTO_LENGTH, &move);
    if(status != napi_ok) return nullptr;

    return move;
}

napi_value init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, nullptr, 0, Move, nullptr, &fn);
    if(status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "move", fn);

    if(status != napi_ok) return nullptr;
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);

} // namespace shallowBlue
