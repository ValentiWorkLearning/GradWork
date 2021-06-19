#pragma once

namespace Utils
{

struct noncopyable
{
    noncopyable() = default;
    noncopyable( const noncopyable& ) = delete;
    noncopyable& operator= ( const noncopyable&) = delete;
    ~noncopyable() = default;
};

}