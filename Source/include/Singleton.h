#ifndef SINGLETON_H
#define SINGLETON_H

#include <mutex>

template <typename T>
class Singleton {
public:
    static T*   GetInstance();
    static void Destroy();

private:
    static T*         instance;
    static std::mutex locker;
    Singleton()                       = default;
    Singleton(const Singleton& other) = default;
    Singleton& operator=(const Singleton& other) = default;
};

template <typename T>
T* Singleton<T>::instance = nullptr;

template <typename T>
std::mutex Singleton<T>::locker;

template <typename T>
T* Singleton<T>::GetInstance() {
    if (nullptr == instance) {
        std::lock_guard<std::mutex> lock(locker);
        if (nullptr == instance) {
            instance = new T();
        }
    }
    return instance;
}

template <typename T>
void Singleton<T>::Destroy() {
    if (nullptr == instance) {
        std::lock_guard<std::mutex> lock(locker);
        delete instance;
        instance = nullptr;
    }
}

#define SINGLETON(C)              \
private:                          \
    C();                          \
    ~C();                         \
    C(const C& other);            \
    C& operator=(const C& other); \
    friend class Singleton<C>;

#endif // SINGLETON_H
