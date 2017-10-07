#include <functional>

namespace tool {
    template<typename T, typename ...Args>
    T call(std::function<T(Args...)> fn, Args...args) {
        if (fn) {
            fn(args...);
        }
    }
}
