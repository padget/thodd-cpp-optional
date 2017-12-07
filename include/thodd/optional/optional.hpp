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

  constexpr auto 
  make_optional (
    auto && obj) 
  {
    optional<std::decay_t<decltype(obj)>> opt ;
    opt.opt = obj ;           
    return opt ;
  }

  template <
    typename type_t>
  constexpr auto 
  make_optional () 
  {
    return 
    optional<type_t> {} ;
  }

  constexpr auto 
  make_optional_if (auto && obj, auto && predicate, auto && transform)
  {
    using type_t = std::decay_t<decltype(std::forward<decltype(transform)>(transform)(std::forward<decltype(obj)>(obj)))>;

    if (std::forward<decltype(predicate)>(predicate) (std::forward<decltype(obj)>(obj)))
      return thodd::make_optional(std::forward<decltype(transform)>(transform)(std::forward<decltype(obj)>(obj))) ;
    else 
      return thodd::make_optional<type_t>() ;
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





  constexpr auto 
  if_exists (
      optional<auto> & opt, 
      auto && func, 
      auto && efunc)
  {
      if (has_value(opt))
          std::forward<decltype(func)>(func)(value_of(opt)) ;
      else
          std::forward<decltype(efunc)>(efunc)() ; 
  }   

  constexpr auto 
  if_exists (
      optional<auto> const & opt, 
      auto && func, 
      auto && efunc)
  {
      if (has_value(opt))
          std::forward<decltype(func)>(func)(value_of(opt)) ;
      else
          std::forward<decltype(efunc)>(efunc)() ;
  }

  constexpr auto 
  if_exists (
      optional<auto> && opt, 
      auto && func, 
      auto && efunc)
  {
      if (has_value(opt))
          std::forward<decltype(func)>(func)(value_of(opt)) ;
      else
          std::forward<decltype(efunc)>(efunc)() ;
  }
}

namespace 
thodd
{
  template <typename type_t>
  struct maybe 
  {
    type_t* data { nullptr } ;
  } ;

  template <typename type_t>
  constexpr auto 
  maybe_of (type_t * data) 
  { return maybe<type_t> { data } ; }


  template <typename type_t>
  constexpr auto 
  maybe_of () 
  { return maybe<type_t> {} ; }


  constexpr auto 
  maybe_if (
    auto && something, 
    auto && predicate, 
    auto && transform)
  -> decltype(auto)
  {
    if (std::forward<decltype(predicate)>(predicate)(std::forward<decltype(something)>(something)))
      return maybe_of(std::forward<decltype(transform)>(transform)(std::forward<decltype(something)>(something))) ;
    else 
      return maybe_of<std::remove_pointer_t<std::decay_t<decltype(std::forward<decltype(transform)>(transform)(std::forward<decltype(something)>(something)))>>>() ;
  }


  constexpr bool
  has_value (maybe<auto> const & mb) 
  { return mb.data != nullptr ; }


  constexpr auto 
  value_of (maybe<auto> & mb)
  -> decltype(auto)
  { return *mb.data ; }

  constexpr auto 
  value_of (maybe<auto> const & mb)
  -> decltype(auto)
  { return *mb.data ; }

  constexpr auto 
  value_of (maybe<auto> && mb)
  -> decltype(auto)
  { return *mb.data ; }


  if_exists (
    maybe<auto> & mb,
    auto && todo)
  {
    if (has_value (mb)) 
      std::forward<decltype(todo)>(todo)(value_of(mb)) ; 
  }

  if_exists (
    maybe<auto> const & mb,
    auto && todo)
  {
    if (has_value (mb)) 
      std::forward<decltype(todo)>(todo)(value_of(mb)) ; 
  }

  if_exists (
    maybe<auto> && mb,
    auto && todo)
  {
    if (has_value (mb)) 
      std::forward<decltype(todo)>(todo)(value_of(mb)) ; 
  }
}

namespace 
thodd
{
  constexpr bool
  has_value (std::unique_ptr<auto> const & u) 
  { return (bool) u ; }


  constexpr auto 
  value_of (std::unique_ptr<auto> & u)
  -> decltype(auto)
  { return *u ; }

  constexpr auto 
  value_of (std::unique_ptr<auto> const & u)
  -> decltype(auto)
  { return *u ; }

  constexpr auto 
  value_of (std::unique_ptr<auto> && u)
  -> decltype(auto)
  { return *u ; }


  if_exists (
    std::unique_ptr<auto> & u,
    auto && todo)
  {
    if (has_value (u)) 
      std::forward<decltype(todo)>(todo) (value_of(u)) ; 
  }

  if_exists (
    std::unique_ptr<auto> const & u,
    auto && todo)
  {
    if (has_value (u)) 
      std::forward<decltype(todo)>(todo) (value_of(u)) ; 
  }

  if_exists (
    std::unique_ptr<auto> && u,
    auto && todo)
  {
    if (has_value (u)) 
      std::forward<decltype(todo)>(todo) (value_of(u)) ; 
  }

  if_not_exists (
    std::unique_ptr<auto> & u,
    auto && todo)
  {
    if (!has_value (u)) 
      std::forward<decltype(todo)>(todo) (u) ; 
  }

  if_not_exists (
    std::unique_ptr<auto> const & u,
    auto && todo)
  {
    if (!has_value (u)) 
      std::forward<decltype(todo)>(todo) (u) ; 
  }

  if_not_exists (
    std::unique_ptr<auto> && u,
    auto && todo)
  {
    if (!has_value (u)) 
      std::forward<decltype(todo)>(todo) (u) ; 
  }
}


#endif