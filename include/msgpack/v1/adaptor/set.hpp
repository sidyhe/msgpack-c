//
// MessagePack for C++ static resolution routine
//
// Copyright (C) 2008-2015 FURUHASHI Sadayuki
//
//    Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//    http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef MSGPACK_V1_TYPE_SET_HPP
#define MSGPACK_V1_TYPE_SET_HPP

#include "msgpack/versioning.hpp"
#include "msgpack/adaptor/adaptor_base.hpp"
#include "msgpack/adaptor/check_container_size.hpp"

#include <eastl/set.h>

namespace msgpack {

/// @cond
MSGPACK_API_VERSION_NAMESPACE(v1) {
/// @endcond

namespace adaptor {

#if !defined(MSGPACK_USE_CPP03)

template <typename T, typename Compare, typename Alloc>
struct as<eastl::set<T, Compare, Alloc>, typename std::enable_if<msgpack::has_as<T>::value>::type> {
    eastl::set<T, Compare, Alloc> operator()(msgpack::object const& o) const {
        if (o.type != msgpack::type::ARRAY) { ExRaiseStatus(EMSGPACK_TYPE_ERROR); }
        msgpack::object* p = o.via.array.ptr + o.via.array.size;
        msgpack::object* const pbegin = o.via.array.ptr;
        eastl::set<T, Compare, Alloc> v;
        while (p > pbegin) {
            --p;
            v.insert(p->as<T>());
        }
        return v;
    }
};

#endif // !defined(MSGPACK_USE_CPP03)

template <typename T, typename Compare, typename Alloc>
struct convert<eastl::set<T, Compare, Alloc> > {
    msgpack::object const& operator()(msgpack::object const& o, eastl::set<T, Compare, Alloc>& v) const {
        if (o.type != msgpack::type::ARRAY) { ExRaiseStatus(EMSGPACK_TYPE_ERROR); }
        msgpack::object* p = o.via.array.ptr + o.via.array.size;
        msgpack::object* const pbegin = o.via.array.ptr;
        eastl::set<T, Compare, Alloc> tmp;
        while (p > pbegin) {
            --p;
            tmp.insert(p->as<T>());
        }
#if __cplusplus >= 201103L
        v = std::move(tmp);
#else
        tmp.swap(v);
#endif
        return o;
    }
};

template <typename T, typename Compare, typename Alloc>
struct pack<eastl::set<T, Compare, Alloc> > {
    template <typename Stream>
    msgpack::packer<Stream>& operator()(msgpack::packer<Stream>& o, const eastl::set<T, Compare, Alloc>& v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for (typename eastl::set<T, Compare, Alloc>::const_iterator it(v.begin()), it_end(v.end());
            it != it_end; ++it) {
            o.pack(*it);
        }
        return o;
    }
};

template <typename T, typename Compare, typename Alloc>
struct object_with_zone<eastl::set<T, Compare, Alloc> > {
    void operator()(msgpack::object::with_zone& o, const eastl::set<T, Compare, Alloc>& v) const {
        o.type = msgpack::type::ARRAY;
        if (v.empty()) {
            o.via.array.ptr = MSGPACK_NULLPTR;
            o.via.array.size = 0;
        }
        else {
            uint32_t size = checked_get_container_size(v.size());
            msgpack::object* p = static_cast<msgpack::object*>(o.zone.allocate_align(sizeof(msgpack::object)*size, MSGPACK_ZONE_ALIGNOF(msgpack::object)));
            msgpack::object* const pend = p + size;
            o.via.array.ptr = p;
            o.via.array.size = size;
            typename eastl::set<T, Compare, Alloc>::const_iterator it(v.begin());
            do {
                *p = msgpack::object(*it, o.zone);
                ++p;
                ++it;
            } while(p < pend);
        }
    }
};

#if !defined(MSGPACK_USE_CPP03)

template <typename T, typename Compare, typename Alloc>
struct as<eastl::multiset<T, Compare, Alloc>, typename std::enable_if<msgpack::has_as<T>::value>::type> {
    eastl::multiset<T, Compare, Alloc> operator()(msgpack::object const& o) const {
        if (o.type != msgpack::type::ARRAY) { ExRaiseStatus(EMSGPACK_TYPE_ERROR); }
        msgpack::object* p = o.via.array.ptr + o.via.array.size;
        msgpack::object* const pbegin = o.via.array.ptr;
        eastl::multiset<T, Compare, Alloc> v;
        while (p > pbegin) {
            --p;
            v.insert(p->as<T>());
        }
        return v;
    }
};

#endif // !defined(MSGPACK_USE_CPP03)

template <typename T, typename Compare, typename Alloc>
struct convert<eastl::multiset<T, Compare, Alloc> > {
    msgpack::object const& operator()(msgpack::object const& o, eastl::multiset<T, Compare, Alloc>& v) const {
        if (o.type != msgpack::type::ARRAY) { ExRaiseStatus(EMSGPACK_TYPE_ERROR); }
        msgpack::object* p = o.via.array.ptr + o.via.array.size;
        msgpack::object* const pbegin = o.via.array.ptr;
        eastl::multiset<T, Compare, Alloc> tmp;
        while (p > pbegin) {
            --p;
            tmp.insert(p->as<T>());
        }
#if __cplusplus >= 201103L
        v = std::move(tmp);
#else
        tmp.swap(v);
#endif
        return o;
    }
};

template <typename T, typename Compare, typename Alloc>
struct pack<eastl::multiset<T, Compare, Alloc> > {
    template <typename Stream>
    msgpack::packer<Stream>& operator()(msgpack::packer<Stream>& o, const eastl::multiset<T, Compare, Alloc>& v) const {
        uint32_t size = checked_get_container_size(v.size());
        o.pack_array(size);
        for (typename eastl::multiset<T, Compare, Alloc>::const_iterator it(v.begin()), it_end(v.end());
            it != it_end; ++it) {
            o.pack(*it);
        }
        return o;
    }
};

template <typename T, typename Compare, typename Alloc>
struct object_with_zone<eastl::multiset<T, Compare, Alloc> > {
    void operator()(msgpack::object::with_zone& o, const eastl::multiset<T, Compare, Alloc>& v) const {
        o.type = msgpack::type::ARRAY;
        if (v.empty()) {
            o.via.array.ptr = MSGPACK_NULLPTR;
            o.via.array.size = 0;
        } else {
            uint32_t size = checked_get_container_size(v.size());
            msgpack::object* p = static_cast<msgpack::object*>(o.zone.allocate_align(sizeof(msgpack::object)*size, MSGPACK_ZONE_ALIGNOF(msgpack::object)));
            msgpack::object* const pend = p + size;
            o.via.array.ptr = p;
            o.via.array.size = size;
            typename eastl::multiset<T, Compare, Alloc>::const_iterator it(v.begin());
            do {
                *p = msgpack::object(*it, o.zone);
                ++p;
                ++it;
            } while(p < pend);
        }
    }
};

} // namespace adaptor

/// @cond
}  // MSGPACK_API_VERSION_NAMESPACE(v1)
/// @endcond

}  // namespace msgpack

#endif // MSGPACK_V1_TYPE_SET_HPP
