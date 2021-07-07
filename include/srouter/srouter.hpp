/**
 * @file srouter.hpp.
 * @brief SRouter library API.
 * @author Khayitov D. D. (c).
 * @date 2020.
 */
#pragma once

#include "types.hpp"
#include "visibility.hpp"

namespace vmx {

/**
 * @brief Module initialization.
 * @param cfg[in] Path to configurations directory.
 * @param log[in] Path to log directory.
 * @return Success flag.
 */
SROUTER_API bool SRouter_Initialize(const char* cfg, const char* log = nullptr);

/**
 * @brief Create instance.
 * @param id Configuration id.
 * @param params[in] Instance advanced parameters.
 * @return Instance.
 */
SROUTER_API void* SRouter_Create(unsigned int id, void* params = nullptr);

/**
 * @brief Set data.
 * @param instance[in] Instance.
 * @param str[in] Query string.
 * @param array[out] Pointer to output data (see e.g. Record) array.
 * @param count[out] Output data array objects count.
 * @return Return code (see SROUTER_SET).
 */
SROUTER_API SROUTER_SET SRouter_Set(void* instance, const char* str,
                                    void* array, size_t& count, int& code,
                                    int apiId = 0);

/**
 * @brief Get data.
 * @param instance[in] Instance.
 * @param str[in] Query string.
 * @param array[out] Pointer to output data (see e.g. Record) array.
 * @param count[out] Output data array objects count.
 * @return Return code (see SROUTER_GET).
 */
SROUTER_API SROUTER_GET SRouter_Get(void* instance, const char* str,
                                    void* array, size_t& count,
                                    int& code, int apiId = 0);

/**
 * @brief Read configuration and force reinitialization.
 * @param instance[in,out] Instance.
 * @return Success flag.
 */
SROUTER_API bool SRouter_ReadConfig(void* instance);

/**
 * @brief Delete instance.
 * @param instance[in,out] Instance.
 * @return Success flag.
 */
SROUTER_API bool SRouter_Delete(void* instance);

/**
 * @brief Module deinitialization.
 * @return Success flag.
 */
SROUTER_API bool SRouter_Deinitialize();

}  // namespace vmx
