//#include "stdafx.h"

#include "SmartPtr.h"

void SmartPtrProtho::init() {
    if (_refs_map) {
        release();
    }
    _refs_map = new std::map<void*, size_t>();
}

void SmartPtrProtho::release() {
    if (_refs_map) {
        delete _refs_map;
        _refs_map = 0;
    }
}

SmartPtrProtho::~SmartPtrProtho() {
    if (_refs_map && _refs_map->size() == 0) {
        release();
    }
}

bool SmartPtrProtho::decrease(void *ptr) {
    if (!_refs_map) {
        return false;
    }
    if (_refs_map->count(ptr)) {
        if (--((*_refs_map)[ptr]) == 0) {
            _refs_map->erase(ptr);
        }

        return true;
    }
    return false;
}

bool SmartPtrProtho::increase(void *ptr) {
    if (!_refs_map) {
        init();
    }
    if (!_refs_map) {
        return false;
    }
    if (_refs_map->count(ptr)) {
        (*_refs_map)[ptr]++;
    } else {
        (*_refs_map)[ptr] = 1;
    }
    return true;
}

size_t SmartPtrProtho::count(void *ptr) const {
    if (_refs_map && _refs_map->count(ptr)) {
        return (*_refs_map)[ptr];
    }
    return 0;
}

#ifndef __SMART_PTR_INIT
#define __SMART_PTR_INIT
    std::map<void*, size_t> *SmartPtrProtho::_refs_map = 0;
#endif
