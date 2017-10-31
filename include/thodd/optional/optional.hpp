#ifndef __THODD_OPTIONAL_OPTIONAL_HPP__
#  define __THODD_OPTIONAL_OPTIONAL_HPP__

#  include <type_traits>
#  include <optional>

namespace 
thodd 
{
    template <
        typename type_t>
    struct optional
    {
        std::optional<type_t> opt {} ;
        type_t* ptr { nullptr };
    } ;

    template <
        typename type_t>
    constexpr auto 
    make_optional (
        type_t && obj) 
    {
        optional<std::decay_t<decltype(obj)>> opt ;
        opt.opt = obj ;           
        return opt ;
    }

    template <typename type_t>
    constexpr optional<type_t> 
    make_optional (type_t * obj) 
    {
        optional<type_t> opt ;
        opt.ptr = obj ;
        return opt ;
    }

    constexpr bool
    has_value (
        optional<auto> const & opt)
    {
        return 
        opt.opt.has_value() || opt.ptr != nullptr ;
    }

    constexpr auto
    value_of (
        optional<auto> & opt)
    -> decltype(auto) 
    {
        return 
        opt.opt.has_value() ? (opt.opt.value()) : (*opt.ptr) ;
    }

    constexpr auto
    value_of (
        optional<auto> const & opt)
    -> decltype(auto) 
    {
        return 
        opt.opt.has_value() ? (opt.opt.value()) : (*opt.ptr) ;
    }
    
    constexpr auto
    value_of (
        optional<auto> && opt)
    -> decltype(auto) 
    {
        return 
        opt.opt.has_value() ? (opt.opt.value()) : (*opt.ptr) ;
    }

    constexpr auto 
    if_exists (
        optional<auto> & opt, 
        auto && func)
    {
        if (has_value(opt))
            std::forward<decltype(func)>(func)(value_of(opt)) ;
    }

    constexpr auto 
    if_exists (
        optional<auto> const & opt, 
        auto && func)
    {
        if (has_value(opt))
            std::forward<decltype(func)>(func)(value_of(opt)) ;
    }

    constexpr auto 
    if_exists (
        optional<auto> && opt, 
        auto && func)
    {
        if (has_value(opt))
            std::forward<decltype(func)>(func)(value_of(opt)) ;
    }
}

#endif