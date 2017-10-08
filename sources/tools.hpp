#include <functional>

namespace tools {
    template<typename T, typename ...Args>
    T call(std::function<T(Args...)> fn, Args&&...args) {
        if (fn) {
            fn(std::forward<Args>(args)...);
        }
    }
}
