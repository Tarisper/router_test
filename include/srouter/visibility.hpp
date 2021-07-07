/**
 * @file visibility.hpp.
 * @brief DSO symbols visibility definitions.
 * @author Khayitov D. D. (c).
 * @date 2020.
 */
#pragma once

// Generic helper definitions for DSO support.
#if defined _WIN32 || defined __CYGWIN__
#define HELPER_DSO_LOCAL
#define HELPER_DSO_EXPORT __declspec(dllexport)
#define HELPER_DSO_IMPORT __declspec(dllimport)
#elif __GNUC__ >= 4
#define HELPER_DSO_LOCAL __attribute__((visibility("hidden")))
#define HELPER_DSO_EXPORT __attribute__((visibility("default")))
#define HELPER_DSO_IMPORT __attribute__((visibility("default")))
#else
#define HELPER_DSO_LOCAL
#define HELPER_DSO_EXPORT
#define HELPER_DSO_IMPORT
#endif

// LIBX_LOCAL and LIBX_API definitions.
// LIBX_LOCAL - for non-api symbols.
// LIBX_API - for the public API symbols:
//   - export at building DSO library;
//   - import at using DSO library;
//   - does nothing at linking static library.
#ifdef SROUTER_DSO  // DSO library.
#ifdef SROUTER_DSO_EXPORT
#define SROUTER_LOCAL HELPER_DSO_LOCAL
#define SROUTER_API HELPER_DSO_EXPORT  // DSO building.
#else
#define SROUTER_API HELPER_DSO_IMPORT  // DSO using.
#endif
#else
#define SROUTER_LOCAL
#define SROUTER_API  // Static library.
#endif
