// Copyright 2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _UTLIS_STORE_H_
#define _UTLIS_STORE_H_

#include "mdf_common.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef enum{
	US_SPA_SYS,
	US_SPA_SCH,
	US_SPA_MAX
}Store_space_t;
extern char *_p_store_space_str[];
/**
 * @brief Initialize the default NVS partition
 *
 * @return
 *     - ESP_FAIL
 *     - ESP_OK
 */ 
//esp_err_t utlis_info_init(void);

/**
 * @brief save the information with given key
 *
 * @param  key    Key name. Maximal length is 15 characters. Shouldn't be empty.
 * @param  value  The value to set.
 * @param  length length of binary value to set, in bytes; Maximum length is
 *                1984 bytes (508000 bytes or (97.6% of the partition size - 4000) bytes
 *                whichever is lower, in case multi-page blob support is enabled).
 *
 * @return
 *     - ESP_FAIL
 *     - ESP_OK
 */
esp_err_t utlis_store_save(Store_space_t spa_type, const char *key, const void *value, size_t length);

/**
 * @brief  Load the information,
 *         esp_err_t mdf_info_load(const char *key, void *value, size_t *length);
 *         esp_err_t mdf_info_load(const char *key, void *value, size_t length);
 *
 * @attention  The interface of this api supports size_t and size_t * types.
 *             When the length parameter of the pass is size_t, it is only the
 *             length of the value. When the length parameter of the pass is size_t *,
 *             the length of the saved information can be obtained.
 *
 * @param  key    The corresponding key of the information that want to load
 * @param  value  The corresponding value of key
 * @param  length The length of the value, Pointer type will return length
 *
 * @return
 *     - ESP_FAIL
 *     - ESP_OK
 */

#define LENGTH_TYPE_NUMBER  1
#define LENGTH_TYPE_POINTER 2
esp_err_t __utlis_store_load(Store_space_t spa_type, const char *key, void *value, size_t len, uint32_t type);

#define utlis_store_load(space, key, value, len) \
    __utlis_store_load(space, key, value, (size_t)(len), \
                    builtin_types_compatible_p(len, int8_t) * LENGTH_TYPE_NUMBER \
                    +builtin_types_compatible_p(len, uint8_t) * LENGTH_TYPE_NUMBER \
                    + builtin_types_compatible_p(len, int16_t) * LENGTH_TYPE_NUMBER \
                    + builtin_types_compatible_p(len, uint16_t) * LENGTH_TYPE_NUMBER \
                    + builtin_types_compatible_p(len, int) * LENGTH_TYPE_NUMBER \
                    + builtin_types_compatible_p(len, uint32_t) * LENGTH_TYPE_NUMBER \
                    + builtin_types_compatible_p(len, int *) * LENGTH_TYPE_POINTER \
                    + builtin_types_compatible_p(len, uint32_t *) * LENGTH_TYPE_POINTER)

/*
 * @brief  Erase the information with given key
 *
 * @param  key The corresponding key of the information that want to erase
 *
 * @return
 *     - ESP_FAIL
 *     - ESP_OK
 */
esp_err_t utlis_store_erase(Store_space_t spa_type,const char *key);
esp_err_t utlis_store_blob_get(Store_space_t spa_type, const char *key, void **pp_value, size_t *p_len);

#ifdef __cplusplus
}
#endif

#endif /* _UTLIS_STORE_H_ */
