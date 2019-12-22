// Copyright 2018 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <iostream>
#include <map>
#include <stdint.h>
#include <utility>

using std::map;
using std::int64_t;

static std::map<int64_t, size_t> count;

template <typename T>

class SharedPtr{
public:
    T* pointer;
    SharedPtr(){
        pointer = nullptr;
    }

    explicit SharedPtr(T* ptr){
        pointer = ptr;
        if (count.find(reinterpret_cast<int64_t>(pointer)) != count.end()) {
            count[reinterpret_cast<int64_t>(pointer)]++;
        } else {
            count.insert({reinterpret_cast<int64_t>(pointer), 1});
        }
    }

    SharedPtr(const SharedPtr& r){
        pointer = r.pointer;
        count[reinterpret_cast<int64_t>(pointer)]++;
    }

    SharedPtr(SharedPtr &&r){
        pointer = r->pointer;
        count[reinterpret_cast<int64_t>(pointer)]++;
        delete(r);
    }
    ~SharedPtr(){
        count[reinterpret_cast<int64_t>(pointer)]--;
        if (count[reinterpret_cast<int64_t>(pointer)] == 0) {
            count.erase(reinterpret_cast<int64_t>(pointer));
            delete pointer;
        }
    }

    auto operator=(const SharedPtr& r) -> SharedPtr&;

    auto operator=(SharedPtr&& r) -> SharedPtr&;

    explicit operator bool() const{
        if (!pointer){
            return false;
        } else {
            return true;
        }
    }
    auto operator*() const -> T&{
        return pointer;
    }
    auto operator->() const -> T*{
        return pointer;
    }

    auto get() -> T*{
        return pointer;
    }
    void reset(){
        if (count[reinterpret_cast<int64_t>(pointer)] == 0) {
            delete (pointer);
            count.erase(reinterpret_cast<int64_t>(pointer));
        } else {
            count[reinterpret_cast<int64_t>(pointer)]--;
            pointer = nullptr;
        }
    }
    void reset(T* ptr){
        if (count[reinterpret_cast<int64_t>(ptr)] == 1) {
            delete (pointer);
            count[reinterpret_cast<int64_t>(ptr)] = 0;
            count.erase(reinterpret_cast<int64_t>(ptr));
        } else {
            count[reinterpret_cast<int64_t>(ptr)]--;
            pointer = nullptr;
        }
    }
    void swap(SharedPtr& r){
        T* tmp;
        tmp = r.pointer;
        r.pointer = pointer;
        pointer = tmp;
    }
    auto use_count() const -> size_t{
        return count[reinterpret_cast<int64_t>(pointer)];
    }
};
#endif // INCLUDE_HEADER_HPP_
