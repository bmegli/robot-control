/*
 * RC Robot Control C library header
 *
 * Copyright 2020 (C) Bartosz Meglicki <meglickib@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#ifndef RC_H
#define RC_H

#include <stdint.h>

/**
 ******************************************************************************
 *
 *  \mainpage RC documentation
 *  \see https://github.com/bmegli/robot-control
 *
 *  \copyright  Copyright (C) 2020 Bartosz Meglicki
 *  \file       rc.h
 *  \brief      Library public interface header
 *
 ******************************************************************************
 */

// API compatible with C99 on various platorms
// Compatible with Unity Native Plugins
#if defined(__CYGWIN32__)
    #define RC_API __stdcall
    #define RC_EXPORT __declspec(dllexport)
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WINAPI_FAMILY)
    #define RC_API __stdcall
    #define RC_EXPORT __declspec(dllexport)
#elif defined(__MACH__) || defined(__ANDROID__) || defined(__linux__)
    #define RC_API
    #define RC_EXPORT
#else
    #define RC_API
    #define RC_EXPORT
#endif

/** \addtogroup interface Public interface
 *  @{
 */

/**
 * @struct rc
 * @brief Internal library data passed around by the user.
 * @see rc_init, rc_close
 */
struct rc;

/**
 * @struct rc_net_config
 * @brief Network configuration.
 *
 * For more details see:
 * <a href="https://github.com/bmegli/minimal-latency-streaming-protocol">MLSP</a>
 *
 * @see unhvd_init
 */
struct rc_net_config
{
	const char *ip; //!< IP to connect
	uint16_t port; //!< port to connect
};

/**
  * @brief Constants returned by most of library functions
  */
enum rc_retval_enum
{
	RC_ERROR=-1, //!< error occured
	RC_OK=0, //!< succesfull execution
};

/**
 * @brief Initialize internal library data.
 *
 * Initialize network layer and allocate memory.
 *
 * @param net_config network configuration
 * @return
 * - pointer to internal library data
 * - NULL on error, errors printed to stderr
 *
 * @see rc_net_config
 */
RC_EXPORT RC_API struct rc *rc_init(const struct rc_net_config *net_config);

/**
 * @brief Free library resources
 *
 * Cleans and frees library memory.
 *
 * @param r pointer to internal library data
 * @see rc_init
 *
 */
RC_EXPORT RC_API void rc_close(struct rc *r);

/**
  * @brief Command types
  */
enum rc_command
{
	RC_KEEPALIVE=0, //!< do nothing, network layer is ok
	RC_SPEED=1, //!< arg1 and arg2 are speeds for differential drive like control
};

/**
 * @brief Send robot command
 *
 * arg1 and arg2 meaning is command dependent
 *
 * @param r pointer to internal library data
 * @param arg1 command dependent (e.g. left motor speed for RC_SPEED command)
 * @param arg2 command dependent (e.g. right motor speed for RC_SPEED command)
 * @see rc_init, rc_command
 *
 */
RC_EXPORT RC_API int rc_command(struct rc *r, int16_t command, int16_t arg1, int16_t arg2);

/** @}*/

#endif
