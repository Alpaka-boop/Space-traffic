#ifndef ISTYPE_H
#define ISTYPE_H

#include <type_traits>

#include "Conditions.h"
#include "Engine.h"

template <typename T, typename = void>
struct is_free_space: std::false_type {};

template <typename T>
struct is_free_space<T, std::void_t<FreeSpace>>: std::true_type {};

template <typename T>
constexpr inline bool is_free_space_v = is_free_space<T>();

template <typename T, typename = void>
struct is_density_space: std::false_type {};

template <typename T>
struct is_density_space<T, std::void_t<DensitySpace>>: std::true_type {};

template <typename T>
constexpr inline bool is_density_space_v = is_density_space<T>();

template <typename T, typename = void>
struct is_nitrine_space: std::false_type {};

template <typename T>
struct is_nitrine_space<T, std::void_t<NitrineSpace>>: std::true_type {};

template <typename T>
constexpr inline bool is_nitrine_space_v = is_nitrine_space<T>();

template <typename T, typename = void>
struct is_jump_engine: std::false_type {};

template <typename T>
struct is_jump_engine<T, std::void_t<JumpClassEngine>>: std::true_type {};

template <typename T>
constexpr inline bool is_jump_engine_v = is_jump_engine<T>();

template <typename T, typename = void>
struct is_pulse_c_engine: std::false_type {};

template <typename T>
struct is_pulse_c_engine<T, std::void_t<PulseClassCEngine>>: std::true_type {};

template <typename T>
constexpr inline bool is_pulse_c_engine_v = is_pulse_c_engine<T>();

template <typename T, typename = void>
struct is_pulse_e_engine: std::false_type {};

template <typename T>
struct is_pulse_e_engine<T, std::void_t<PulseClassEEngine>>: std::true_type {};

template <typename T>
constexpr inline bool is_pulse_e_engine_v = is_pulse_e_engine<T>();

template <typename T, typename = void>
struct is_pulse_engine: std::false_type {};

template <typename T>
struct is_pulse_engine<T, std::void_t<std::enable_if<is_pulse_e_engine_v<T> || is_pulse_c_engine_v<T>>>>
        : std::true_type {};

template <typename T>
constexpr inline bool is_pulse_engine_v = is_pulse_engine<T>();

#endif
