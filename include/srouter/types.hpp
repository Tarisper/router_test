/**
 * @file types.hpp.
 * @brief Intermodular types.
 * @author Khayitov D. D. (c).
 * @date 2020.
 */
#pragma once

#include <cstddef>

namespace vmx {

/**
 * @brief SRouter set-function return code.
 */
enum SROUTER_SET : int {
  SROUTER_SET_INVALID = -2,    //!< Invalid arguments or initialization.
  SROUTER_SET_EXCEPTION = -1,  //!< Exception.
  SROUTER_SET_EMPTY = 0        //!< Empty recordset.
};

/**
 * @brief SRouter get-function return code.
 */
enum SROUTER_GET : int {
  SROUTER_GET_INVALID = -2,    //!< Invalid arguments or initialization.
  SROUTER_GET_EXCEPTION = -1,  //!< Exception.
  SROUTER_GET_EMPTY = 0        //!< Empty recordset.
};

struct Record {
  char* string;
  size_t length;
};

}  // namespace vmx
