#ifndef CACHE_H_INCLUDED
#define CACHE_H_INCLUDED

#include <map>

template <class Key, class Value>
class Cache {
    std::map<Key, Value> m_cache;

public:
    template <class Generator>
    Value get(const Key & key, const Generator & generator) {
        typename std::map<Key, Value>::const_iterator it = m_cache.find(key);

        if (it == m_cache.end()) {
            Value newValue(generator(key));
            m_cache[key] = newValue;

            return newValue;
        }

        return it->second;
    }
};

#endif // CACHE_H_INCLUDED
