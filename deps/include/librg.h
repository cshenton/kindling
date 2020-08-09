/**
 * librg - a library for building simple and elegant cross-platform multiplayer client-server solutions.
 *
 * Usage:
 * #define LIBRG_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:
 *
 * #define LIBRG_IMPLEMENTATION
 * #include <librg.h>
 *
 * Credits:
 *  - Vladyslav Hrytsenko (GitHub: inlife)
 *  - Dominik Madarasz (GitHub: zaklaus)
 *
 * Dependencies:
 *  - librg.h -> zpl.h (built-in)
 *  - librg_enet.h -> enet.h (built-in)
 *
 * ===================================
 *  Version History:
 * ===================================
 *
 * 6.0.0
 *  - Major library rewrite
 *
 * 5.0.6 - Fix forced_inline on librg__space_insert
 * 5.0.5 - Fixes to selection and deduplication flow
 * 5.0.3 - Minor fixes by @markatk
 * 5.0.2 - Fixed issue related to visiblity destruction
 * 5.0.1 - Fixed entity visiblity states after disconnection
 *
 * 5.0.0
 *  - Changed API for visibility feature:
 *    - Instead of booleans setting whether or not entity would be included in the query or not
 *      a multiple constant-based states were inroduced:
 *        - LIBRG_VISIBILITY_DEFAULT - the original state of visibility, entity is only visible if it is in the stream range
 *        - LIBRG_ALWAYS_VISIBLE - the entity is visible disregarding if it is the stream range or not
 *        - LIBRG_ALWAYS_INVISIBLE - opposite of the above, entity will be always invisible
 *      Entity visibility can be set on per entity-to-entity or global levels. The entity-to-entity relation has a bigger
 *      priority, so f.e. setting entity to be LIBRG_ALWAYS_VISIBLE on relation level, will override global visibility.
 *   - Aditionally, if the virtual world feature is enabled, it gains main priotity over visibility, thus entities located in 2 different
 *     virtual worlds will not be able to see each other in spite of visibility settings.
 *
 * 4.1.5
 *  - Fix to data send
 *
 * 4.1.4
 *  - Fixed issue with async flow inconsitensies of control_generations
 *  - Fixed boolean validation in disconnection flow
 *  - Added proxying of user_data from msg to evt in disconnect event
 *
 * 4.1.1
 * - Added compile-time 'features':
 *     - Ability to enable/disable some librg compile-time features
 *     - Entity igore tables are now optional, and can be disabled
 *     - Implmented simple optional Virtual world feature for entities
 *     - Implemented a feature to enable/disable octree culler (falls back to linear check)
 *     - Multiple features can be combined
 * - Added 'generation' to entity control lists:
 *     Setting, removing and setting control to the same entity again with same owner
 *     will now distinct between old and new controllers, and messages still coming
 *     from old control generation will be rejected in favor of new ones.
 * - Added guard to minimum sized packet in receive for both sides
 * - Added spherical culler handler, and ability to do runtime switch (LIBRG_USE_RADIUS_CULLING)
 * - Added return codes to some functions @markatk
 * - Streamed entities are now going to be always returned in query for controlling peer
 * - Fixed issue with host setting on the server side
 * - Fixed nullptr crash on empty host string for client on connect
 * - Removed experimental multithreading code
 *
 * 4.1.0  - Added new, extended message methods and sending options
 * 4.0.0 - Coding style changes and bug fixes
 *
 * 3.3.1
 * - Updated zpl dependencies
 * - Removed zpl_math dependency (replaced by internal module in zpl)
 *
 * 3.3.0
 * - Added ipv6 support
 * - Added safe bitstream reads for internal methods
 * - Updated enet to latest version (2.0.1, ipv6 support)
 * - Updated zpl to latest version
 *
 * 3.2.0
 * - Fixed minor memory client-side memory leak with empty control list
 * - Fixed issue with client stream update and removed entity on server
 * - Updated zpl to new major version, watch out for possible incompatibilities
 * - Added method for alloc/dealloc the librg_ctx, librg_data, librg_event for the bindings
 * - Added experimental support for update buffering, disabled by default, and not recommended to use
 * - Added built-in timesyncer, working on top of monotonic time, syncing client clock to server one
 * - Added helper methods: librg_time_now, librg_standard_deviation
 * - Changed ctx->tick_delay from u16 to f64 (slightly more precision)
 *
 * 3.1.0
 * - Removed zpl_cull and zpl_event dependencies
 * - added librg_network_kick()
 * - saving current librg_address to ctx->network
 * - refactor to proper disconnection code
 * - exclude local client entity from LIBRG_CONNECTION_DISCONNECT
 * - moved options and some few other things to the implementation part
 * - fixed issue with replacing entity control
 * - fixed issue with add control queuing beign sent before create entity packet
 *
 * 3.0.7 - Fix for entity query dublication for player entities
 * 3.0.5 - Patched librg_callback_cb arg value
 * 3.0.4 - Fixed Android and iOS support
 * 3.0.3 - Small fixes
 * 3.0.2 - Dependency updates
 * 3.0.1 - minor api patch
 * 3.0.0 - contexts, major api changes, fried potato, other stuff
 *
 * 2.2.3 - fixed mem leak on net event
 * 2.2.2 - Fixed client issue with librg_message_send_instream_except
 * 2.2.1 - Fixed cpp issues with librg_data pointers
 * 2.2.0 - Inner message system rafactor
 * 2.1.0 - Inner bitstream refactors, with slight interface changes
 * 2.0.2 - C++ and MSVC related fixes
 * 2.0.0 - Initial C version rewrite
 *
 * ============================
 *  License notice
 * ============================
 * Copyright (c) 2017-2020 Vladyslav Hrytsenko. All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef LIBRG_H
#define LIBRG_H

#define LIBRG_VERSION_MAJOR 6
#define LIBRG_VERSION_MINOR 0
#define LIBRG_VERSION_PATCH 4
#define LIBRG_VERSION_PRE ""

// file: librg_hedley.h

/* Hedley - https://nemequ.github.io/hedley
 * Created by Evan Nemerson <evan@nemerson.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to
 * the public domain worldwide. This software is distributed without
 * any warranty.
 *
 * For details, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 * SPDX-License-Identifier: CC0-1.0
 */

#if !defined(LIBRG_HEDLEY_VERSION) || (LIBRG_HEDLEY_VERSION < 13)
#if defined(LIBRG_HEDLEY_VERSION)
#  undef LIBRG_HEDLEY_VERSION
#endif
#define LIBRG_HEDLEY_VERSION 13

#if defined(LIBRG_STRINGIFY_EX)
#  undef LIBRG_STRINGIFY_EX
#endif
#define LIBRG_STRINGIFY_EX(x) #x

#if defined(LIBRG_STRINGIFY)
#  undef LIBRG_STRINGIFY
#endif
#define LIBRG_STRINGIFY(x) LIBRG_STRINGIFY_EX(x)

#if defined(LIBRG_CONCAT_EX)
#  undef LIBRG_CONCAT_EX
#endif
#define LIBRG_CONCAT_EX(a,b) a##b

#if defined(LIBRG_CONCAT)
#  undef LIBRG_CONCAT
#endif
#define LIBRG_CONCAT(a,b) LIBRG_CONCAT_EX(a,b)

#if defined(LIBRG_CONCAT3_EX)
#  undef LIBRG_CONCAT3_EX
#endif
#define LIBRG_CONCAT3_EX(a,b,c) a##b##c

#if defined(LIBRG_CONCAT3)
#  undef LIBRG_CONCAT3
#endif
#define LIBRG_CONCAT3(a,b,c) LIBRG_CONCAT3_EX(a,b,c)

#if defined(LIBRG_VERSION_ENCODE)
#  undef LIBRG_VERSION_ENCODE
#endif
#define LIBRG_VERSION_ENCODE(major,minor,revision) (((major) * 1000000) + ((minor) * 1000) + (revision))

#if defined(LIBRG_VERSION_DECODE_MAJOR)
#  undef LIBRG_VERSION_DECODE_MAJOR
#endif
#define LIBRG_VERSION_DECODE_MAJOR(version) ((version) / 1000000)

#if defined(LIBRG_VERSION_DECODE_MINOR)
#  undef LIBRG_VERSION_DECODE_MINOR
#endif
#define LIBRG_VERSION_DECODE_MINOR(version) (((version) % 1000000) / 1000)

#if defined(LIBRG_VERSION_DECODE_REVISION)
#  undef LIBRG_VERSION_DECODE_REVISION
#endif
#define LIBRG_VERSION_DECODE_REVISION(version) ((version) % 1000)

#if defined(LIBRG_GNUC_VERSION)
#  undef LIBRG_GNUC_VERSION
#endif
#if defined(__GNUC__) && defined(__GNUC_PATCHLEVEL__)
#  define LIBRG_GNUC_VERSION LIBRG_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
#elif defined(__GNUC__)
#  define LIBRG_GNUC_VERSION LIBRG_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, 0)
#endif

#if defined(LIBRG_GNUC_VERSION_CHECK)
#  undef LIBRG_GNUC_VERSION_CHECK
#endif
#if defined(LIBRG_GNUC_VERSION)
#  define LIBRG_GNUC_VERSION_CHECK(major,minor,patch) (LIBRG_GNUC_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_GNUC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_MSVC_VERSION)
#  undef LIBRG_MSVC_VERSION
#endif
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140000000)
#  define LIBRG_MSVC_VERSION LIBRG_VERSION_ENCODE(_MSC_FULL_VER / 10000000, (_MSC_FULL_VER % 10000000) / 100000, (_MSC_FULL_VER % 100000) / 100)
#elif defined(_MSC_FULL_VER)
#  define LIBRG_MSVC_VERSION LIBRG_VERSION_ENCODE(_MSC_FULL_VER / 1000000, (_MSC_FULL_VER % 1000000) / 10000, (_MSC_FULL_VER % 10000) / 10)
#elif defined(_MSC_VER)
#  define LIBRG_MSVC_VERSION LIBRG_VERSION_ENCODE(_MSC_VER / 100, _MSC_VER % 100, 0)
#endif

#if defined(LIBRG_MSVC_VERSION_CHECK)
#  undef LIBRG_MSVC_VERSION_CHECK
#endif
#if !defined(_MSC_VER)
#  define LIBRG_MSVC_VERSION_CHECK(major,minor,patch) (0)
#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#  define LIBRG_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 10000000) + (minor * 100000) + (patch)))
#elif defined(_MSC_VER) && (_MSC_VER >= 1200)
#  define LIBRG_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000) + (patch)))
#else
#  define LIBRG_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_VER >= ((major * 100) + (minor)))
#endif

#if defined(LIBRG_INTEL_VERSION)
#  undef LIBRG_INTEL_VERSION
#endif
#if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_UPDATE)
#  define LIBRG_INTEL_VERSION LIBRG_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, __INTEL_COMPILER_UPDATE)
#elif defined(__INTEL_COMPILER)
#  define LIBRG_INTEL_VERSION LIBRG_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, 0)
#endif

#if defined(LIBRG_INTEL_VERSION_CHECK)
#  undef LIBRG_INTEL_VERSION_CHECK
#endif
#if defined(LIBRG_INTEL_VERSION)
#  define LIBRG_INTEL_VERSION_CHECK(major,minor,patch) (LIBRG_INTEL_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_INTEL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_PGI_VERSION)
#  undef LIBRG_PGI_VERSION
#endif
#if defined(__PGI) && defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__)
#  define LIBRG_PGI_VERSION LIBRG_VERSION_ENCODE(__PGIC__, __PGIC_MINOR__, __PGIC_PATCHLEVEL__)
#endif

#if defined(LIBRG_PGI_VERSION_CHECK)
#  undef LIBRG_PGI_VERSION_CHECK
#endif
#if defined(LIBRG_PGI_VERSION)
#  define LIBRG_PGI_VERSION_CHECK(major,minor,patch) (LIBRG_PGI_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_PGI_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_SUNPRO_VERSION)
#  undef LIBRG_SUNPRO_VERSION
#endif
#if defined(__SUNPRO_C) && (__SUNPRO_C > 0x1000)
#  define LIBRG_SUNPRO_VERSION LIBRG_VERSION_ENCODE((((__SUNPRO_C >> 16) & 0xf) * 10) + ((__SUNPRO_C >> 12) & 0xf), (((__SUNPRO_C >> 8) & 0xf) * 10) + ((__SUNPRO_C >> 4) & 0xf), (__SUNPRO_C & 0xf) * 10)
#elif defined(__SUNPRO_C)
#  define LIBRG_SUNPRO_VERSION LIBRG_VERSION_ENCODE((__SUNPRO_C >> 8) & 0xf, (__SUNPRO_C >> 4) & 0xf, (__SUNPRO_C) & 0xf)
#elif defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x1000)
#  define LIBRG_SUNPRO_VERSION LIBRG_VERSION_ENCODE((((__SUNPRO_CC >> 16) & 0xf) * 10) + ((__SUNPRO_CC >> 12) & 0xf), (((__SUNPRO_CC >> 8) & 0xf) * 10) + ((__SUNPRO_CC >> 4) & 0xf), (__SUNPRO_CC & 0xf) * 10)
#elif defined(__SUNPRO_CC)
#  define LIBRG_SUNPRO_VERSION LIBRG_VERSION_ENCODE((__SUNPRO_CC >> 8) & 0xf, (__SUNPRO_CC >> 4) & 0xf, (__SUNPRO_CC) & 0xf)
#endif

#if defined(LIBRG_SUNPRO_VERSION_CHECK)
#  undef LIBRG_SUNPRO_VERSION_CHECK
#endif
#if defined(LIBRG_SUNPRO_VERSION)
#  define LIBRG_SUNPRO_VERSION_CHECK(major,minor,patch) (LIBRG_SUNPRO_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_SUNPRO_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_EMSCRIPTEN_VERSION)
#  undef LIBRG_EMSCRIPTEN_VERSION
#endif
#if defined(__EMSCRIPTEN__)
#  define LIBRG_EMSCRIPTEN_VERSION LIBRG_VERSION_ENCODE(__EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__)
#endif

#if defined(LIBRG_EMSCRIPTEN_VERSION_CHECK)
#  undef LIBRG_EMSCRIPTEN_VERSION_CHECK
#endif
#if defined(LIBRG_EMSCRIPTEN_VERSION)
#  define LIBRG_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (LIBRG_EMSCRIPTEN_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_ARM_VERSION)
#  undef LIBRG_ARM_VERSION
#endif
#if defined(__CC_ARM) && defined(__ARMCOMPILER_VERSION)
#  define LIBRG_ARM_VERSION LIBRG_VERSION_ENCODE(__ARMCOMPILER_VERSION / 1000000, (__ARMCOMPILER_VERSION % 1000000) / 10000, (__ARMCOMPILER_VERSION % 10000) / 100)
#elif defined(__CC_ARM) && defined(__ARMCC_VERSION)
#  define LIBRG_ARM_VERSION LIBRG_VERSION_ENCODE(__ARMCC_VERSION / 1000000, (__ARMCC_VERSION % 1000000) / 10000, (__ARMCC_VERSION % 10000) / 100)
#endif

#if defined(LIBRG_ARM_VERSION_CHECK)
#  undef LIBRG_ARM_VERSION_CHECK
#endif
#if defined(LIBRG_ARM_VERSION)
#  define LIBRG_ARM_VERSION_CHECK(major,minor,patch) (LIBRG_ARM_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_ARM_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_IBM_VERSION)
#  undef LIBRG_IBM_VERSION
#endif
#if defined(__ibmxl__)
#  define LIBRG_IBM_VERSION LIBRG_VERSION_ENCODE(__ibmxl_version__, __ibmxl_release__, __ibmxl_modification__)
#elif defined(__xlC__) && defined(__xlC_ver__)
#  define LIBRG_IBM_VERSION LIBRG_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, (__xlC_ver__ >> 8) & 0xff)
#elif defined(__xlC__)
#  define LIBRG_IBM_VERSION LIBRG_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, 0)
#endif

#if defined(LIBRG_IBM_VERSION_CHECK)
#  undef LIBRG_IBM_VERSION_CHECK
#endif
#if defined(LIBRG_IBM_VERSION)
#  define LIBRG_IBM_VERSION_CHECK(major,minor,patch) (LIBRG_IBM_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_IBM_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_VERSION)
#  undef LIBRG_TI_VERSION
#endif
#if \
    defined(__TI_COMPILER_VERSION__) && \
    ( \
      defined(__TMS470__) || defined(__TI_ARM__) || \
      defined(__MSP430__) || \
      defined(__TMS320C2000__) \
    )
#  if (__TI_COMPILER_VERSION__ >= 16000000)
#    define LIBRG_TI_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#  endif
#endif

#if defined(LIBRG_TI_VERSION_CHECK)
#  undef LIBRG_TI_VERSION_CHECK
#endif
#if defined(LIBRG_TI_VERSION)
#  define LIBRG_TI_VERSION_CHECK(major,minor,patch) (LIBRG_TI_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_CL2000_VERSION)
#  undef LIBRG_TI_CL2000_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C2000__)
#  define LIBRG_TI_CL2000_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(LIBRG_TI_CL2000_VERSION_CHECK)
#  undef LIBRG_TI_CL2000_VERSION_CHECK
#endif
#if defined(LIBRG_TI_CL2000_VERSION)
#  define LIBRG_TI_CL2000_VERSION_CHECK(major,minor,patch) (LIBRG_TI_CL2000_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_CL2000_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_CL430_VERSION)
#  undef LIBRG_TI_CL430_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__MSP430__)
#  define LIBRG_TI_CL430_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(LIBRG_TI_CL430_VERSION_CHECK)
#  undef LIBRG_TI_CL430_VERSION_CHECK
#endif
#if defined(LIBRG_TI_CL430_VERSION)
#  define LIBRG_TI_CL430_VERSION_CHECK(major,minor,patch) (LIBRG_TI_CL430_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_CL430_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_ARMCL_VERSION)
#  undef LIBRG_TI_ARMCL_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && (defined(__TMS470__) || defined(__TI_ARM__))
#  define LIBRG_TI_ARMCL_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(LIBRG_TI_ARMCL_VERSION_CHECK)
#  undef LIBRG_TI_ARMCL_VERSION_CHECK
#endif
#if defined(LIBRG_TI_ARMCL_VERSION)
#  define LIBRG_TI_ARMCL_VERSION_CHECK(major,minor,patch) (LIBRG_TI_ARMCL_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_ARMCL_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_CL6X_VERSION)
#  undef LIBRG_TI_CL6X_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C6X__)
#  define LIBRG_TI_CL6X_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(LIBRG_TI_CL6X_VERSION_CHECK)
#  undef LIBRG_TI_CL6X_VERSION_CHECK
#endif
#if defined(LIBRG_TI_CL6X_VERSION)
#  define LIBRG_TI_CL6X_VERSION_CHECK(major,minor,patch) (LIBRG_TI_CL6X_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_CL6X_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_CL7X_VERSION)
#  undef LIBRG_TI_CL7X_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__C7000__)
#  define LIBRG_TI_CL7X_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(LIBRG_TI_CL7X_VERSION_CHECK)
#  undef LIBRG_TI_CL7X_VERSION_CHECK
#endif
#if defined(LIBRG_TI_CL7X_VERSION)
#  define LIBRG_TI_CL7X_VERSION_CHECK(major,minor,patch) (LIBRG_TI_CL7X_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_CL7X_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TI_CLPRU_VERSION)
#  undef LIBRG_TI_CLPRU_VERSION
#endif
#if defined(__TI_COMPILER_VERSION__) && defined(__PRU__)
#  define LIBRG_TI_CLPRU_VERSION LIBRG_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
#endif

#if defined(LIBRG_TI_CLPRU_VERSION_CHECK)
#  undef LIBRG_TI_CLPRU_VERSION_CHECK
#endif
#if defined(LIBRG_TI_CLPRU_VERSION)
#  define LIBRG_TI_CLPRU_VERSION_CHECK(major,minor,patch) (LIBRG_TI_CLPRU_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TI_CLPRU_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_CRAY_VERSION)
#  undef LIBRG_CRAY_VERSION
#endif
#if defined(_CRAYC)
#  if defined(_RELEASE_PATCHLEVEL)
#    define LIBRG_CRAY_VERSION LIBRG_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, _RELEASE_PATCHLEVEL)
#  else
#    define LIBRG_CRAY_VERSION LIBRG_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, 0)
#  endif
#endif

#if defined(LIBRG_CRAY_VERSION_CHECK)
#  undef LIBRG_CRAY_VERSION_CHECK
#endif
#if defined(LIBRG_CRAY_VERSION)
#  define LIBRG_CRAY_VERSION_CHECK(major,minor,patch) (LIBRG_CRAY_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_CRAY_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_IAR_VERSION)
#  undef LIBRG_IAR_VERSION
#endif
#if defined(__IAR_SYSTEMS_ICC__)
#  if __VER__ > 1000
#    define LIBRG_IAR_VERSION LIBRG_VERSION_ENCODE((__VER__ / 1000000), ((__VER__ / 1000) % 1000), (__VER__ % 1000))
#  else
#    define LIBRG_IAR_VERSION LIBRG_VERSION_ENCODE(VER / 100, __VER__ % 100, 0)
#  endif
#endif

#if defined(LIBRG_IAR_VERSION_CHECK)
#  undef LIBRG_IAR_VERSION_CHECK
#endif
#if defined(LIBRG_IAR_VERSION)
#  define LIBRG_IAR_VERSION_CHECK(major,minor,patch) (LIBRG_IAR_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_IAR_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_TINYC_VERSION)
#  undef LIBRG_TINYC_VERSION
#endif
#if defined(__TINYC__)
#  define LIBRG_TINYC_VERSION LIBRG_VERSION_ENCODE(__TINYC__ / 1000, (__TINYC__ / 100) % 10, __TINYC__ % 100)
#endif

#if defined(LIBRG_TINYC_VERSION_CHECK)
#  undef LIBRG_TINYC_VERSION_CHECK
#endif
#if defined(LIBRG_TINYC_VERSION)
#  define LIBRG_TINYC_VERSION_CHECK(major,minor,patch) (LIBRG_TINYC_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_TINYC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_DMC_VERSION)
#  undef LIBRG_DMC_VERSION
#endif
#if defined(__DMC__)
#  define LIBRG_DMC_VERSION LIBRG_VERSION_ENCODE(__DMC__ >> 8, (__DMC__ >> 4) & 0xf, __DMC__ & 0xf)
#endif

#if defined(LIBRG_DMC_VERSION_CHECK)
#  undef LIBRG_DMC_VERSION_CHECK
#endif
#if defined(LIBRG_DMC_VERSION)
#  define LIBRG_DMC_VERSION_CHECK(major,minor,patch) (LIBRG_DMC_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_DMC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_COMPCERT_VERSION)
#  undef LIBRG_COMPCERT_VERSION
#endif
#if defined(__COMPCERT_VERSION__)
#  define LIBRG_COMPCERT_VERSION LIBRG_VERSION_ENCODE(__COMPCERT_VERSION__ / 10000, (__COMPCERT_VERSION__ / 100) % 100, __COMPCERT_VERSION__ % 100)
#endif

#if defined(LIBRG_COMPCERT_VERSION_CHECK)
#  undef LIBRG_COMPCERT_VERSION_CHECK
#endif
#if defined(LIBRG_COMPCERT_VERSION)
#  define LIBRG_COMPCERT_VERSION_CHECK(major,minor,patch) (LIBRG_COMPCERT_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_COMPCERT_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_PELLES_VERSION)
#  undef LIBRG_PELLES_VERSION
#endif
#if defined(__POCC__)
#  define LIBRG_PELLES_VERSION LIBRG_VERSION_ENCODE(__POCC__ / 100, __POCC__ % 100, 0)
#endif

#if defined(LIBRG_PELLES_VERSION_CHECK)
#  undef LIBRG_PELLES_VERSION_CHECK
#endif
#if defined(LIBRG_PELLES_VERSION)
#  define LIBRG_PELLES_VERSION_CHECK(major,minor,patch) (LIBRG_PELLES_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_PELLES_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_GCC_VERSION)
#  undef LIBRG_GCC_VERSION
#endif
#if \
  defined(LIBRG_GNUC_VERSION) && \
  !defined(__clang__) && \
  !defined(LIBRG_INTEL_VERSION) && \
  !defined(LIBRG_PGI_VERSION) && \
  !defined(LIBRG_ARM_VERSION) && \
  !defined(LIBRG_TI_VERSION) && \
  !defined(LIBRG_TI_ARMCL_VERSION) && \
  !defined(LIBRG_TI_CL430_VERSION) && \
  !defined(LIBRG_TI_CL2000_VERSION) && \
  !defined(LIBRG_TI_CL6X_VERSION) && \
  !defined(LIBRG_TI_CL7X_VERSION) && \
  !defined(LIBRG_TI_CLPRU_VERSION) && \
  !defined(__COMPCERT__)
#  define LIBRG_GCC_VERSION LIBRG_GNUC_VERSION
#endif

#if defined(LIBRG_GCC_VERSION_CHECK)
#  undef LIBRG_GCC_VERSION_CHECK
#endif
#if defined(LIBRG_GCC_VERSION)
#  define LIBRG_GCC_VERSION_CHECK(major,minor,patch) (LIBRG_GCC_VERSION >= LIBRG_VERSION_ENCODE(major, minor, patch))
#else
#  define LIBRG_GCC_VERSION_CHECK(major,minor,patch) (0)
#endif

#if defined(LIBRG_HAS_ATTRIBUTE)
#  undef LIBRG_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define LIBRG_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
#else
#  define LIBRG_HAS_ATTRIBUTE(attribute) (0)
#endif

#if defined(LIBRG_GNUC_HAS_ATTRIBUTE)
#  undef LIBRG_GNUC_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define LIBRG_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) __has_attribute(attribute)
#else
#  define LIBRG_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_ATTRIBUTE)
#  undef LIBRG_GCC_HAS_ATTRIBUTE
#endif
#if defined(__has_attribute)
#  define LIBRG_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) __has_attribute(attribute)
#else
#  define LIBRG_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_HAS_CPP_ATTRIBUTE)
#  undef LIBRG_HAS_CPP_ATTRIBUTE
#endif
#if \
  defined(__has_cpp_attribute) && \
  defined(__cplusplus) && \
  (!defined(LIBRG_SUNPRO_VERSION) || LIBRG_SUNPRO_VERSION_CHECK(5,15,0))
#  define LIBRG_HAS_CPP_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#else
#  define LIBRG_HAS_CPP_ATTRIBUTE(attribute) (0)
#endif

#if defined(LIBRG_HAS_CPP_ATTRIBUTE_NS)
#  undef LIBRG_HAS_CPP_ATTRIBUTE_NS
#endif
#if !defined(__cplusplus) || !defined(__has_cpp_attribute)
#  define LIBRG_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
#elif \
  !defined(LIBRG_PGI_VERSION) && \
  !defined(LIBRG_IAR_VERSION) && \
  (!defined(LIBRG_SUNPRO_VERSION) || LIBRG_SUNPRO_VERSION_CHECK(5,15,0)) && \
  (!defined(LIBRG_MSVC_VERSION) || LIBRG_MSVC_VERSION_CHECK(19,20,0))
#  define LIBRG_HAS_CPP_ATTRIBUTE_NS(ns,attribute) LIBRG_HAS_CPP_ATTRIBUTE(ns::attribute)
#else
#  define LIBRG_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
#endif

#if defined(LIBRG_GNUC_HAS_CPP_ATTRIBUTE)
#  undef LIBRG_GNUC_HAS_CPP_ATTRIBUTE
#endif
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define LIBRG_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
#else
#  define LIBRG_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_CPP_ATTRIBUTE)
#  undef LIBRG_GCC_HAS_CPP_ATTRIBUTE
#endif
#if defined(__has_cpp_attribute) && defined(__cplusplus)
#  define LIBRG_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
#else
#  define LIBRG_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_HAS_BUILTIN)
#  undef LIBRG_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define LIBRG_HAS_BUILTIN(builtin) __has_builtin(builtin)
#else
#  define LIBRG_HAS_BUILTIN(builtin) (0)
#endif

#if defined(LIBRG_GNUC_HAS_BUILTIN)
#  undef LIBRG_GNUC_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define LIBRG_GNUC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
#else
#  define LIBRG_GNUC_HAS_BUILTIN(builtin,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_BUILTIN)
#  undef LIBRG_GCC_HAS_BUILTIN
#endif
#if defined(__has_builtin)
#  define LIBRG_GCC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
#else
#  define LIBRG_GCC_HAS_BUILTIN(builtin,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_HAS_FEATURE)
#  undef LIBRG_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define LIBRG_HAS_FEATURE(feature) __has_feature(feature)
#else
#  define LIBRG_HAS_FEATURE(feature) (0)
#endif

#if defined(LIBRG_GNUC_HAS_FEATURE)
#  undef LIBRG_GNUC_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define LIBRG_GNUC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
#else
#  define LIBRG_GNUC_HAS_FEATURE(feature,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_FEATURE)
#  undef LIBRG_GCC_HAS_FEATURE
#endif
#if defined(__has_feature)
#  define LIBRG_GCC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
#else
#  define LIBRG_GCC_HAS_FEATURE(feature,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_HAS_EXTENSION)
#  undef LIBRG_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define LIBRG_HAS_EXTENSION(extension) __has_extension(extension)
#else
#  define LIBRG_HAS_EXTENSION(extension) (0)
#endif

#if defined(LIBRG_GNUC_HAS_EXTENSION)
#  undef LIBRG_GNUC_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define LIBRG_GNUC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
#else
#  define LIBRG_GNUC_HAS_EXTENSION(extension,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_EXTENSION)
#  undef LIBRG_GCC_HAS_EXTENSION
#endif
#if defined(__has_extension)
#  define LIBRG_GCC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
#else
#  define LIBRG_GCC_HAS_EXTENSION(extension,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_HAS_DECLSPEC_ATTRIBUTE)
#  undef LIBRG_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define LIBRG_HAS_DECLSPEC_ATTRIBUTE(attribute) __has_declspec_attribute(attribute)
#else
#  define LIBRG_HAS_DECLSPEC_ATTRIBUTE(attribute) (0)
#endif

#if defined(LIBRG_GNUC_HAS_DECLSPEC_ATTRIBUTE)
#  undef LIBRG_GNUC_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define LIBRG_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
#else
#  define LIBRG_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_DECLSPEC_ATTRIBUTE)
#  undef LIBRG_GCC_HAS_DECLSPEC_ATTRIBUTE
#endif
#if defined(__has_declspec_attribute)
#  define LIBRG_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
#else
#  define LIBRG_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_HAS_WARNING)
#  undef LIBRG_HAS_WARNING
#endif
#if defined(__has_warning)
#  define LIBRG_HAS_WARNING(warning) __has_warning(warning)
#else
#  define LIBRG_HAS_WARNING(warning) (0)
#endif

#if defined(LIBRG_GNUC_HAS_WARNING)
#  undef LIBRG_GNUC_HAS_WARNING
#endif
#if defined(__has_warning)
#  define LIBRG_GNUC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
#else
#  define LIBRG_GNUC_HAS_WARNING(warning,major,minor,patch) LIBRG_GNUC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_GCC_HAS_WARNING)
#  undef LIBRG_GCC_HAS_WARNING
#endif
#if defined(__has_warning)
#  define LIBRG_GCC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
#else
#  define LIBRG_GCC_HAS_WARNING(warning,major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

/* LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_ is for
   LIBRG INTERNAL USE ONLY.  API subject to change without notice. */
#if defined(LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
#  undef LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_
#endif
#if defined(__cplusplus)
#  if LIBRG_HAS_WARNING("-Wc++98-compat")
#    if LIBRG_HAS_WARNING("-Wc++17-extensions")
#      define LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
         LIBRG_DIAGNOSTIC_PUSH \
         _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
         _Pragma("clang diagnostic ignored \"-Wc++17-extensions\"") \
         xpr \
         LIBRG_DIAGNOSTIC_POP
#    else
#      define LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
         LIBRG_DIAGNOSTIC_PUSH \
         _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
         xpr \
         LIBRG_DIAGNOSTIC_POP
#    endif
#  endif
#endif
#if !defined(LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
#  define LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(x) x
#endif

#if defined(LIBRG_CONST_CAST)
#  undef LIBRG_CONST_CAST
#endif
#if defined(__cplusplus)
#  define LIBRG_CONST_CAST(T, expr) (const_cast<T>(expr))
#elif \
  LIBRG_HAS_WARNING("-Wcast-qual") || \
  LIBRG_GCC_VERSION_CHECK(4,6,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_CONST_CAST(T, expr) (__extension__ ({ \
      LIBRG_DIAGNOSTIC_PUSH \
      LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL \
      ((T) (expr)); \
      LIBRG_DIAGNOSTIC_POP \
    }))
#else
#  define LIBRG_CONST_CAST(T, expr) ((T) (expr))
#endif

#if defined(LIBRG_REINTERPRET_CAST)
#  undef LIBRG_REINTERPRET_CAST
#endif
#if defined(__cplusplus)
#  define LIBRG_REINTERPRET_CAST(T, expr) (reinterpret_cast<T>(expr))
#else
#  define LIBRG_REINTERPRET_CAST(T, expr) ((T) (expr))
#endif

#if defined(LIBRG_STATIC_CAST)
#  undef LIBRG_STATIC_CAST
#endif
#if defined(__cplusplus)
#  define LIBRG_STATIC_CAST(T, expr) (static_cast<T>(expr))
#else
#  define LIBRG_STATIC_CAST(T, expr) ((T) (expr))
#endif

#if defined(LIBRG_CPP_CAST)
#  undef LIBRG_CPP_CAST
#endif
#if defined(__cplusplus)
#  if LIBRG_HAS_WARNING("-Wold-style-cast")
#    define LIBRG_CPP_CAST(T, expr) \
       LIBRG_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wold-style-cast\"") \
       ((T) (expr)) \
       LIBRG_DIAGNOSTIC_POP
#  elif LIBRG_IAR_VERSION_CHECK(8,3,0)
#    define LIBRG_CPP_CAST(T, expr) \
       LIBRG_DIAGNOSTIC_PUSH \
       _Pragma("diag_suppress=Pe137") \
       LIBRG_DIAGNOSTIC_POP \
#  else
#    define LIBRG_CPP_CAST(T, expr) ((T) (expr))
#  endif
#else
#  define LIBRG_CPP_CAST(T, expr) (expr)
#endif

#if \
  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
  defined(__clang__) || \
  LIBRG_GCC_VERSION_CHECK(3,0,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_IAR_VERSION_CHECK(8,0,0) || \
  LIBRG_PGI_VERSION_CHECK(18,4,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(4,7,0) || \
  LIBRG_TI_CL430_VERSION_CHECK(2,0,1) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,1,0) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,0,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  LIBRG_CRAY_VERSION_CHECK(5,0,0) || \
  LIBRG_TINYC_VERSION_CHECK(0,9,17) || \
  LIBRG_SUNPRO_VERSION_CHECK(8,0,0) || \
  (LIBRG_IBM_VERSION_CHECK(10,1,0) && defined(__C99_PRAGMA_OPERATOR))
#  define LIBRG_PRAGMA(value) _Pragma(#value)
#elif LIBRG_MSVC_VERSION_CHECK(15,0,0)
#  define LIBRG_PRAGMA(value) __pragma(value)
#else
#  define LIBRG_PRAGMA(value)
#endif

#if defined(LIBRG_DIAGNOSTIC_PUSH)
#  undef LIBRG_DIAGNOSTIC_PUSH
#endif
#if defined(LIBRG_DIAGNOSTIC_POP)
#  undef LIBRG_DIAGNOSTIC_POP
#endif
#if defined(__clang__)
#  define LIBRG_DIAGNOSTIC_PUSH _Pragma("clang diagnostic push")
#  define LIBRG_DIAGNOSTIC_POP _Pragma("clang diagnostic pop")
#elif LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_DIAGNOSTIC_PUSH _Pragma("warning(push)")
#  define LIBRG_DIAGNOSTIC_POP _Pragma("warning(pop)")
#elif LIBRG_GCC_VERSION_CHECK(4,6,0)
#  define LIBRG_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
#  define LIBRG_DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
#elif LIBRG_MSVC_VERSION_CHECK(15,0,0)
#  define LIBRG_DIAGNOSTIC_PUSH __pragma(warning(push))
#  define LIBRG_DIAGNOSTIC_POP __pragma(warning(pop))
#elif LIBRG_ARM_VERSION_CHECK(5,6,0)
#  define LIBRG_DIAGNOSTIC_PUSH _Pragma("push")
#  define LIBRG_DIAGNOSTIC_POP _Pragma("pop")
#elif \
    LIBRG_TI_VERSION_CHECK(15,12,0) || \
    LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
    LIBRG_TI_CL430_VERSION_CHECK(4,4,0) || \
    LIBRG_TI_CL6X_VERSION_CHECK(8,1,0) || \
    LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
    LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_DIAGNOSTIC_PUSH _Pragma("diag_push")
#  define LIBRG_DIAGNOSTIC_POP _Pragma("diag_pop")
#elif LIBRG_PELLES_VERSION_CHECK(2,90,0)
#  define LIBRG_DIAGNOSTIC_PUSH _Pragma("warning(push)")
#  define LIBRG_DIAGNOSTIC_POP _Pragma("warning(pop)")
#else
#  define LIBRG_DIAGNOSTIC_PUSH
#  define LIBRG_DIAGNOSTIC_POP
#endif

#if defined(LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED)
#  undef LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED
#endif
#if LIBRG_HAS_WARNING("-Wdeprecated-declarations")
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
#elif LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warning(disable:1478 1786)")
#elif LIBRG_PGI_VERSION_CHECK(17,10,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1215,1444")
#elif LIBRG_GCC_VERSION_CHECK(4,3,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#elif LIBRG_MSVC_VERSION_CHECK(15,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED __pragma(warning(disable:4996))
#elif \
    LIBRG_TI_VERSION_CHECK(15,12,0) || \
    (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
    (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
    (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
    (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
    LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
    LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
    LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1291,1718")
#elif LIBRG_SUNPRO_VERSION_CHECK(5,13,0) && !defined(__cplusplus)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,E_DEPRECATED_ATT,E_DEPRECATED_ATT_MESS)")
#elif LIBRG_SUNPRO_VERSION_CHECK(5,13,0) && defined(__cplusplus)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,symdeprecated,symdeprecated2)")
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress=Pe1444,Pe1215")
#elif LIBRG_PELLES_VERSION_CHECK(2,90,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warn(disable:2241)")
#else
#  define LIBRG_DIAGNOSTIC_DISABLE_DEPRECATED
#endif

#if defined(LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS)
#  undef LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#endif
#if LIBRG_HAS_WARNING("-Wunknown-pragmas")
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"")
#elif LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("warning(disable:161)")
#elif LIBRG_PGI_VERSION_CHECK(17,10,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 1675")
#elif LIBRG_GCC_VERSION_CHECK(4,3,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("GCC diagnostic ignored \"-Wunknown-pragmas\"")
#elif LIBRG_MSVC_VERSION_CHECK(15,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS __pragma(warning(disable:4068))
#elif \
    LIBRG_TI_VERSION_CHECK(16,9,0) || \
    LIBRG_TI_CL6X_VERSION_CHECK(8,0,0) || \
    LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
    LIBRG_TI_CLPRU_VERSION_CHECK(2,3,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
#elif LIBRG_TI_CL6X_VERSION_CHECK(8,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress=Pe161")
#else
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
#endif

#if defined(LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES)
#  undef LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
#endif
#if LIBRG_HAS_WARNING("-Wunknown-attributes")
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("clang diagnostic ignored \"-Wunknown-attributes\"")
#elif LIBRG_GCC_VERSION_CHECK(4,6,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
#elif LIBRG_INTEL_VERSION_CHECK(17,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("warning(disable:1292)")
#elif LIBRG_MSVC_VERSION_CHECK(19,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES __pragma(warning(disable:5030))
#elif LIBRG_PGI_VERSION_CHECK(17,10,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1097")
#elif LIBRG_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("error_messages(off,attrskipunsup)")
#elif \
    LIBRG_TI_VERSION_CHECK(18,1,0) || \
    LIBRG_TI_CL6X_VERSION_CHECK(8,3,0) || \
    LIBRG_TI_CL7X_VERSION_CHECK(1,2,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1173")
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress=Pe1097")
#else
#  define LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
#endif

#if defined(LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL)
#  undef LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL
#endif
#if LIBRG_HAS_WARNING("-Wcast-qual")
#  define LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("clang diagnostic ignored \"-Wcast-qual\"")
#elif LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("warning(disable:2203 2331)")
#elif LIBRG_GCC_VERSION_CHECK(3,0,0)
#  define LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("GCC diagnostic ignored \"-Wcast-qual\"")
#else
#  define LIBRG_DIAGNOSTIC_DISABLE_CAST_QUAL
#endif

#if defined(LIBRG_DEPRECATED)
#  undef LIBRG_DEPRECATED
#endif
#if defined(LIBRG_DEPRECATED_FOR)
#  undef LIBRG_DEPRECATED_FOR
#endif
#if LIBRG_MSVC_VERSION_CHECK(14,0,0)
#  define LIBRG_DEPRECATED(since) __declspec(deprecated("Since " # since))
#  define LIBRG_DEPRECATED_FOR(since, replacement) __declspec(deprecated("Since " #since "; use " #replacement))
#elif defined(__cplusplus) && (__cplusplus >= 201402L)
#  define LIBRG_DEPRECATED(since) LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since)]])
#  define LIBRG_DEPRECATED_FOR(since, replacement) LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since "; use " #replacement)]])
#elif \
  LIBRG_HAS_EXTENSION(attribute_deprecated_with_message) || \
  LIBRG_GCC_VERSION_CHECK(4,5,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_ARM_VERSION_CHECK(5,6,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,13,0) || \
  LIBRG_PGI_VERSION_CHECK(17,10,0) || \
  LIBRG_TI_VERSION_CHECK(18,1,0) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(18,1,0) || \
  LIBRG_TI_CL6X_VERSION_CHECK(8,3,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,3,0)
#  define LIBRG_DEPRECATED(since) __attribute__((__deprecated__("Since " #since)))
#  define LIBRG_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__("Since " #since "; use " #replacement)))
#elif \
  LIBRG_HAS_ATTRIBUTE(deprecated) || \
  LIBRG_GCC_VERSION_CHECK(3,1,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_DEPRECATED(since) __attribute__((__deprecated__))
#  define LIBRG_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__))
#elif \
  LIBRG_MSVC_VERSION_CHECK(13,10,0) || \
  LIBRG_PELLES_VERSION_CHECK(6,50,0)
#  define LIBRG_DEPRECATED(since) __declspec(deprecated)
#  define LIBRG_DEPRECATED_FOR(since, replacement) __declspec(deprecated)
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_DEPRECATED(since) _Pragma("deprecated")
#  define LIBRG_DEPRECATED_FOR(since, replacement) _Pragma("deprecated")
#else
#  define LIBRG_DEPRECATED(since)
#  define LIBRG_DEPRECATED_FOR(since, replacement)
#endif

#if defined(LIBRG_UNAVAILABLE)
#  undef LIBRG_UNAVAILABLE
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(warning) || \
  LIBRG_GCC_VERSION_CHECK(4,3,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_UNAVAILABLE(available_since) __attribute__((__warning__("Not available until " #available_since)))
#else
#  define LIBRG_UNAVAILABLE(available_since)
#endif

#if defined(LIBRG_WARN_UNUSED_RESULT)
#  undef LIBRG_WARN_UNUSED_RESULT
#endif
#if defined(LIBRG_WARN_UNUSED_RESULT_MSG)
#  undef LIBRG_WARN_UNUSED_RESULT_MSG
#endif
#if (LIBRG_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907L)
#  define LIBRG_WARN_UNUSED_RESULT LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#  define LIBRG_WARN_UNUSED_RESULT_MSG(msg) LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard(msg)]])
#elif LIBRG_HAS_CPP_ATTRIBUTE(nodiscard)
#  define LIBRG_WARN_UNUSED_RESULT LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#  define LIBRG_WARN_UNUSED_RESULT_MSG(msg) LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
#elif \
  LIBRG_HAS_ATTRIBUTE(warn_unused_result) || \
  LIBRG_GCC_VERSION_CHECK(3,4,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  (LIBRG_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
  LIBRG_PGI_VERSION_CHECK(17,10,0)
#  define LIBRG_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
#  define LIBRG_WARN_UNUSED_RESULT_MSG(msg) __attribute__((__warn_unused_result__))
#elif defined(_Check_return_) /* SAL */
#  define LIBRG_WARN_UNUSED_RESULT _Check_return_
#  define LIBRG_WARN_UNUSED_RESULT_MSG(msg) _Check_return_
#else
#  define LIBRG_WARN_UNUSED_RESULT
#  define LIBRG_WARN_UNUSED_RESULT_MSG(msg)
#endif

#if defined(LIBRG_SENTINEL)
#  undef LIBRG_SENTINEL
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(sentinel) || \
  LIBRG_GCC_VERSION_CHECK(4,0,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_ARM_VERSION_CHECK(5,4,0)
#  define LIBRG_SENTINEL(position) __attribute__((__sentinel__(position)))
#else
#  define LIBRG_SENTINEL(position)
#endif

#if defined(LIBRG_NO_RETURN)
#  undef LIBRG_NO_RETURN
#endif
#if LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_NO_RETURN __noreturn
#elif LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_NO_RETURN __attribute__((__noreturn__))
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#  define LIBRG_NO_RETURN _Noreturn
#elif defined(__cplusplus) && (__cplusplus >= 201103L)
#  define LIBRG_NO_RETURN LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[noreturn]])
#elif \
  LIBRG_HAS_ATTRIBUTE(noreturn) || \
  LIBRG_GCC_VERSION_CHECK(3,2,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_NO_RETURN __attribute__((__noreturn__))
#elif LIBRG_SUNPRO_VERSION_CHECK(5,10,0)
#  define LIBRG_NO_RETURN _Pragma("does_not_return")
#elif LIBRG_MSVC_VERSION_CHECK(13,10,0)
#  define LIBRG_NO_RETURN __declspec(noreturn)
#elif LIBRG_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
#  define LIBRG_NO_RETURN _Pragma("FUNC_NEVER_RETURNS;")
#elif LIBRG_COMPCERT_VERSION_CHECK(3,2,0)
#  define LIBRG_NO_RETURN __attribute((noreturn))
#elif LIBRG_PELLES_VERSION_CHECK(9,0,0)
#  define LIBRG_NO_RETURN __declspec(noreturn)
#else
#  define LIBRG_NO_RETURN
#endif

#if defined(LIBRG_NO_ESCAPE)
#  undef LIBRG_NO_ESCAPE
#endif
#if LIBRG_HAS_ATTRIBUTE(noescape)
#  define LIBRG_NO_ESCAPE __attribute__((__noescape__))
#else
#  define LIBRG_NO_ESCAPE
#endif

#if defined(LIBRG_UNREACHABLE)
#  undef LIBRG_UNREACHABLE
#endif
#if defined(LIBRG_UNREACHABLE_RETURN)
#  undef LIBRG_UNREACHABLE_RETURN
#endif
#if defined(LIBRG_ASSUME)
#  undef LIBRG_ASSUME
#endif
#if \
  LIBRG_MSVC_VERSION_CHECK(13,10,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_ASSUME(expr) __assume(expr)
#elif LIBRG_HAS_BUILTIN(__builtin_assume)
#  define LIBRG_ASSUME(expr) __builtin_assume(expr)
#elif \
    LIBRG_TI_CL2000_VERSION_CHECK(6,2,0) || \
    LIBRG_TI_CL6X_VERSION_CHECK(4,0,0)
#  if defined(__cplusplus)
#    define LIBRG_ASSUME(expr) std::_nassert(expr)
#  else
#    define LIBRG_ASSUME(expr) _nassert(expr)
#  endif
#endif
#if \
  (LIBRG_HAS_BUILTIN(__builtin_unreachable) && (!defined(LIBRG_ARM_VERSION))) || \
  LIBRG_GCC_VERSION_CHECK(4,5,0) || \
  LIBRG_PGI_VERSION_CHECK(18,10,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_IBM_VERSION_CHECK(13,1,5)
#  define LIBRG_UNREACHABLE() __builtin_unreachable()
#elif defined(LIBRG_ASSUME)
#  define LIBRG_UNREACHABLE() LIBRG_ASSUME(0)
#endif
#if !defined(LIBRG_ASSUME)
#  if defined(LIBRG_UNREACHABLE)
#    define LIBRG_ASSUME(expr) LIBRG_STATIC_CAST(void, ((expr) ? 1 : (LIBRG_UNREACHABLE(), 1)))
#  else
#    define LIBRG_ASSUME(expr) LIBRG_STATIC_CAST(void, expr)
#  endif
#endif
#if defined(LIBRG_UNREACHABLE)
#  if  \
      LIBRG_TI_CL2000_VERSION_CHECK(6,2,0) || \
      LIBRG_TI_CL6X_VERSION_CHECK(4,0,0)
#    define LIBRG_UNREACHABLE_RETURN(value) return (LIBRG_STATIC_CAST(void, LIBRG_ASSUME(0)), (value))
#  else
#    define LIBRG_UNREACHABLE_RETURN(value) LIBRG_UNREACHABLE()
#  endif
#else
#  define LIBRG_UNREACHABLE_RETURN(value) return (value)
#endif
#if !defined(LIBRG_UNREACHABLE)
#  define LIBRG_UNREACHABLE() LIBRG_ASSUME(0)
#endif

LIBRG_DIAGNOSTIC_PUSH
#if LIBRG_HAS_WARNING("-Wpedantic")
#  pragma clang diagnostic ignored "-Wpedantic"
#endif
#if LIBRG_HAS_WARNING("-Wc++98-compat-pedantic") && defined(__cplusplus)
#  pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
#endif
#if LIBRG_GCC_HAS_WARNING("-Wvariadic-macros",4,0,0)
#  if defined(__clang__)
#    pragma clang diagnostic ignored "-Wvariadic-macros"
#  elif defined(LIBRG_GCC_VERSION)
#    pragma GCC diagnostic ignored "-Wvariadic-macros"
#  endif
#endif
#if defined(LIBRG_NON_NULL)
#  undef LIBRG_NON_NULL
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(nonnull) || \
  LIBRG_GCC_VERSION_CHECK(3,3,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0)
#  define LIBRG_NON_NULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
#else
#  define LIBRG_NON_NULL(...)
#endif
LIBRG_DIAGNOSTIC_POP

#if defined(LIBRG_PRINTF_FORMAT)
#  undef LIBRG_PRINTF_FORMAT
#endif
#if defined(__MINGW32__) && LIBRG_GCC_HAS_ATTRIBUTE(format,4,4,0) && !defined(__USE_MINGW_ANSI_STDIO)
#  define LIBRG_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(ms_printf, string_idx, first_to_check)))
#elif defined(__MINGW32__) && LIBRG_GCC_HAS_ATTRIBUTE(format,4,4,0) && defined(__USE_MINGW_ANSI_STDIO)
#  define LIBRG_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(gnu_printf, string_idx, first_to_check)))
#elif \
  LIBRG_HAS_ATTRIBUTE(format) || \
  LIBRG_GCC_VERSION_CHECK(3,1,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_ARM_VERSION_CHECK(5,6,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(__printf__, string_idx, first_to_check)))
#elif LIBRG_PELLES_VERSION_CHECK(6,0,0)
#  define LIBRG_PRINTF_FORMAT(string_idx,first_to_check) __declspec(vaformat(printf,string_idx,first_to_check))
#else
#  define LIBRG_PRINTF_FORMAT(string_idx,first_to_check)
#endif

#if defined(LIBRG_CONSTEXPR)
#  undef LIBRG_CONSTEXPR
#endif
#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define LIBRG_CONSTEXPR LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(constexpr)
#  endif
#endif
#if !defined(LIBRG_CONSTEXPR)
#  define LIBRG_CONSTEXPR
#endif

#if defined(LIBRG_PREDICT)
#  undef LIBRG_PREDICT
#endif
#if defined(LIBRG_LIKELY)
#  undef LIBRG_LIKELY
#endif
#if defined(LIBRG_UNLIKELY)
#  undef LIBRG_UNLIKELY
#endif
#if defined(LIBRG_UNPREDICTABLE)
#  undef LIBRG_UNPREDICTABLE
#endif
#if LIBRG_HAS_BUILTIN(__builtin_unpredictable)
#  define LIBRG_UNPREDICTABLE(expr) __builtin_unpredictable((expr))
#endif
#if \
  LIBRG_HAS_BUILTIN(__builtin_expect_with_probability) || \
  LIBRG_GCC_VERSION_CHECK(9,0,0)
#  define LIBRG_PREDICT(expr, value, probability) __builtin_expect_with_probability(  (expr), (value), (probability))
#  define LIBRG_PREDICT_TRUE(expr, probability)   __builtin_expect_with_probability(!!(expr),    1   , (probability))
#  define LIBRG_PREDICT_FALSE(expr, probability)  __builtin_expect_with_probability(!!(expr),    0   , (probability))
#  define LIBRG_LIKELY(expr)                      __builtin_expect                 (!!(expr),    1                  )
#  define LIBRG_UNLIKELY(expr)                    __builtin_expect                 (!!(expr),    0                  )
#elif \
  LIBRG_HAS_BUILTIN(__builtin_expect) || \
  LIBRG_GCC_VERSION_CHECK(3,0,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  (LIBRG_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(4,7,0) || \
  LIBRG_TI_CL430_VERSION_CHECK(3,1,0) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,1,0) || \
  LIBRG_TI_CL6X_VERSION_CHECK(6,1,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  LIBRG_TINYC_VERSION_CHECK(0,9,27) || \
  LIBRG_CRAY_VERSION_CHECK(8,1,0)
#  define LIBRG_PREDICT(expr, expected, probability) \
     (((probability) >= 0.9) ? __builtin_expect((expr), (expected)) : (LIBRG_STATIC_CAST(void, expected), (expr)))
#  define LIBRG_PREDICT_TRUE(expr, probability) \
     (__extension__ ({ \
       double librg_hedley_probability_ = (probability); \
       ((librg_hedley_probability_ >= 0.9) ? __builtin_expect(!!(expr), 1) : ((librg_hedley_probability_ <= 0.1) ? __builtin_expect(!!(expr), 0) : !!(expr))); \
     }))
#  define LIBRG_PREDICT_FALSE(expr, probability) \
     (__extension__ ({ \
       double librg_hedley_probability_ = (probability); \
       ((librg_hedley_probability_ >= 0.9) ? __builtin_expect(!!(expr), 0) : ((librg_hedley_probability_ <= 0.1) ? __builtin_expect(!!(expr), 1) : !!(expr))); \
     }))
#  define LIBRG_LIKELY(expr)   __builtin_expect(!!(expr), 1)
#  define LIBRG_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
#else
#  define LIBRG_PREDICT(expr, expected, probability) (LIBRG_STATIC_CAST(void, expected), (expr))
#  define LIBRG_PREDICT_TRUE(expr, probability) (!!(expr))
#  define LIBRG_PREDICT_FALSE(expr, probability) (!!(expr))
#  define LIBRG_LIKELY(expr) (!!(expr))
#  define LIBRG_UNLIKELY(expr) (!!(expr))
#endif
#if !defined(LIBRG_UNPREDICTABLE)
#  define LIBRG_UNPREDICTABLE(expr) LIBRG_PREDICT(expr, 1, 0.5)
#endif

#if defined(LIBRG_MALLOC)
#  undef LIBRG_MALLOC
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(malloc) || \
  LIBRG_GCC_VERSION_CHECK(3,1,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(12,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_MALLOC __attribute__((__malloc__))
#elif LIBRG_SUNPRO_VERSION_CHECK(5,10,0)
#  define LIBRG_MALLOC _Pragma("returns_new_memory")
#elif LIBRG_MSVC_VERSION_CHECK(14, 0, 0)
#  define LIBRG_MALLOC __declspec(restrict)
#else
#  define LIBRG_MALLOC
#endif

#if defined(LIBRG_PURE)
#  undef LIBRG_PURE
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(pure) || \
  LIBRG_GCC_VERSION_CHECK(2,96,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  LIBRG_PGI_VERSION_CHECK(17,10,0)
#  define LIBRG_PURE __attribute__((__pure__))
#elif LIBRG_SUNPRO_VERSION_CHECK(5,10,0)
#  define LIBRG_PURE _Pragma("does_not_write_global_data")
#elif defined(__cplusplus) && \
    ( \
      LIBRG_TI_CL430_VERSION_CHECK(2,0,1) || \
      LIBRG_TI_CL6X_VERSION_CHECK(4,0,0) || \
      LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) \
    )
#  define LIBRG_PURE _Pragma("FUNC_IS_PURE;")
#else
#  define LIBRG_PURE
#endif

#if defined(LIBRG_CONST)
#  undef LIBRG_CONST
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(const) || \
  LIBRG_GCC_VERSION_CHECK(2,5,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0) || \
  LIBRG_PGI_VERSION_CHECK(17,10,0)
#  define LIBRG_CONST __attribute__((__const__))
#elif \
  LIBRG_SUNPRO_VERSION_CHECK(5,10,0)
#  define LIBRG_CONST _Pragma("no_side_effect")
#else
#  define LIBRG_CONST LIBRG_PURE
#endif

#if defined(LIBRG_RESTRICT)
#  undef LIBRG_RESTRICT
#endif
#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__cplusplus)
#  define LIBRG_RESTRICT restrict
#elif \
  LIBRG_GCC_VERSION_CHECK(3,1,0) || \
  LIBRG_MSVC_VERSION_CHECK(14,0,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_PGI_VERSION_CHECK(17,10,0) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,2,4) || \
  LIBRG_TI_CL6X_VERSION_CHECK(8,1,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  (LIBRG_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)) || \
  LIBRG_IAR_VERSION_CHECK(8,0,0) || \
  defined(__clang__)
#  define LIBRG_RESTRICT __restrict
#elif LIBRG_SUNPRO_VERSION_CHECK(5,3,0) && !defined(__cplusplus)
#  define LIBRG_RESTRICT _Restrict
#else
#  define LIBRG_RESTRICT
#endif

#if defined(LIBRG_INLINE)
#  undef LIBRG_INLINE
#endif
#if \
  (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
  (defined(__cplusplus) && (__cplusplus >= 199711L))
#  define LIBRG_INLINE inline
#elif \
  defined(LIBRG_GCC_VERSION) || \
  LIBRG_ARM_VERSION_CHECK(6,2,0)
#  define LIBRG_INLINE __inline__
#elif \
  LIBRG_MSVC_VERSION_CHECK(12,0,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,1,0) || \
  LIBRG_TI_CL430_VERSION_CHECK(3,1,0) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,2,0) || \
  LIBRG_TI_CL6X_VERSION_CHECK(8,0,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_INLINE __inline
#else
#  define LIBRG_INLINE
#endif

#if defined(LIBRG_ALWAYS_INLINE)
#  undef LIBRG_ALWAYS_INLINE
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(always_inline) || \
  LIBRG_GCC_VERSION_CHECK(4,0,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_ALWAYS_INLINE __attribute__((__always_inline__)) LIBRG_INLINE
#elif LIBRG_MSVC_VERSION_CHECK(12,0,0)
#  define LIBRG_ALWAYS_INLINE __forceinline
#elif defined(__cplusplus) && \
    ( \
      LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
      LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
      LIBRG_TI_CL6X_VERSION_CHECK(6,1,0) || \
      LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
      LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0) \
    )
#  define LIBRG_ALWAYS_INLINE _Pragma("FUNC_ALWAYS_INLINE;")
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_ALWAYS_INLINE _Pragma("inline=forced")
#else
#  define LIBRG_ALWAYS_INLINE LIBRG_INLINE
#endif

#if defined(LIBRG_NEVER_INLINE)
#  undef LIBRG_NEVER_INLINE
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(noinline) || \
  LIBRG_GCC_VERSION_CHECK(4,0,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(10,1,0) || \
  LIBRG_TI_VERSION_CHECK(15,12,0) || \
  (LIBRG_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_ARMCL_VERSION_CHECK(5,2,0) || \
  (LIBRG_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL2000_VERSION_CHECK(6,4,0) || \
  (LIBRG_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL430_VERSION_CHECK(4,3,0) || \
  (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
  LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) || \
  LIBRG_TI_CL7X_VERSION_CHECK(1,2,0) || \
  LIBRG_TI_CLPRU_VERSION_CHECK(2,1,0)
#  define LIBRG_NEVER_INLINE __attribute__((__noinline__))
#elif LIBRG_MSVC_VERSION_CHECK(13,10,0)
#  define LIBRG_NEVER_INLINE __declspec(noinline)
#elif LIBRG_PGI_VERSION_CHECK(10,2,0)
#  define LIBRG_NEVER_INLINE _Pragma("noinline")
#elif LIBRG_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
#  define LIBRG_NEVER_INLINE _Pragma("FUNC_CANNOT_INLINE;")
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_NEVER_INLINE _Pragma("inline=never")
#elif LIBRG_COMPCERT_VERSION_CHECK(3,2,0)
#  define LIBRG_NEVER_INLINE __attribute((noinline))
#elif LIBRG_PELLES_VERSION_CHECK(9,0,0)
#  define LIBRG_NEVER_INLINE __declspec(noinline)
#else
#  define LIBRG_NEVER_INLINE
#endif

#if defined(LIBRG_PRIVATE)
#  undef LIBRG_PRIVATE
#endif
#if defined(LIBRG_PUBLIC)
#  undef LIBRG_PUBLIC
#endif
#if defined(LIBRG_IMPORT)
#  undef LIBRG_IMPORT
#endif
#if defined(_WIN32) || defined(__CYGWIN__)
#  define LIBRG_PRIVATE
#  define LIBRG_PUBLIC   __declspec(dllexport)
#  define LIBRG_IMPORT   __declspec(dllimport)
#else
#  if \
    LIBRG_HAS_ATTRIBUTE(visibility) || \
    LIBRG_GCC_VERSION_CHECK(3,3,0) || \
    LIBRG_SUNPRO_VERSION_CHECK(5,11,0) || \
    LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
    LIBRG_ARM_VERSION_CHECK(4,1,0) || \
    LIBRG_IBM_VERSION_CHECK(13,1,0) || \
    ( \
      defined(__TI_EABI__) && \
      ( \
        (LIBRG_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        LIBRG_TI_CL6X_VERSION_CHECK(7,5,0) \
      ) \
    )
#    define LIBRG_PRIVATE __attribute__((__visibility__("hidden")))
#    define LIBRG_PUBLIC  __attribute__((__visibility__("default")))
#  else
#    define LIBRG_PRIVATE
#    define LIBRG_PUBLIC
#  endif
#  define LIBRG_IMPORT    extern
#endif

#if defined(LIBRG_NO_THROW)
#  undef LIBRG_NO_THROW
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(nothrow) || \
  LIBRG_GCC_VERSION_CHECK(3,3,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_NO_THROW __attribute__((__nothrow__))
#elif \
  LIBRG_MSVC_VERSION_CHECK(13,1,0) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0)
#  define LIBRG_NO_THROW __declspec(nothrow)
#else
#  define LIBRG_NO_THROW
#endif

#if defined(LIBRG_FALL_THROUGH)
# undef LIBRG_FALL_THROUGH
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(fallthrough) || \
  LIBRG_GCC_VERSION_CHECK(7,0,0)
#  define LIBRG_FALL_THROUGH __attribute__((__fallthrough__))
#elif LIBRG_HAS_CPP_ATTRIBUTE_NS(clang,fallthrough)
#  define LIBRG_FALL_THROUGH LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[clang::fallthrough]])
#elif LIBRG_HAS_CPP_ATTRIBUTE(fallthrough)
#  define LIBRG_FALL_THROUGH LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[fallthrough]])
#elif defined(__fallthrough) /* SAL */
#  define LIBRG_FALL_THROUGH __fallthrough
#else
#  define LIBRG_FALL_THROUGH
#endif

#if defined(LIBRG_RETURNS_NON_NULL)
#  undef LIBRG_RETURNS_NON_NULL
#endif
#if \
  LIBRG_HAS_ATTRIBUTE(returns_nonnull) || \
  LIBRG_GCC_VERSION_CHECK(4,9,0)
#  define LIBRG_RETURNS_NON_NULL __attribute__((__returns_nonnull__))
#elif defined(_Ret_notnull_) /* SAL */
#  define LIBRG_RETURNS_NON_NULL _Ret_notnull_
#else
#  define LIBRG_RETURNS_NON_NULL
#endif

#if defined(LIBRG_ARRAY_PARAM)
#  undef LIBRG_ARRAY_PARAM
#endif
#if \
  defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && \
  !defined(__STDC_NO_VLA__) && \
  !defined(__cplusplus) && \
  !defined(LIBRG_PGI_VERSION) && \
  !defined(LIBRG_TINYC_VERSION)
#  define LIBRG_ARRAY_PARAM(name) (name)
#else
#  define LIBRG_ARRAY_PARAM(name)
#endif

#if defined(LIBRG_IS_CONSTANT)
#  undef LIBRG_IS_CONSTANT
#endif
#if defined(LIBRG_REQUIRE_CONSTEXPR)
#  undef LIBRG_REQUIRE_CONSTEXPR
#endif
/* LIBRG_IS_CONSTEXPR_ is for
   LIBRG INTERNAL USE ONLY.  API subject to change without notice. */
#if defined(LIBRG_IS_CONSTEXPR_)
#  undef LIBRG_IS_CONSTEXPR_
#endif
#if \
  LIBRG_HAS_BUILTIN(__builtin_constant_p) || \
  LIBRG_GCC_VERSION_CHECK(3,4,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
  LIBRG_TINYC_VERSION_CHECK(0,9,19) || \
  LIBRG_ARM_VERSION_CHECK(4,1,0) || \
  LIBRG_IBM_VERSION_CHECK(13,1,0) || \
  LIBRG_TI_CL6X_VERSION_CHECK(6,1,0) || \
  (LIBRG_SUNPRO_VERSION_CHECK(5,10,0) && !defined(__cplusplus)) || \
  LIBRG_CRAY_VERSION_CHECK(8,1,0)
#  define LIBRG_IS_CONSTANT(expr) __builtin_constant_p(expr)
#endif
#if !defined(__cplusplus)
#  if \
       LIBRG_HAS_BUILTIN(__builtin_types_compatible_p) || \
       LIBRG_GCC_VERSION_CHECK(3,4,0) || \
       LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
       LIBRG_IBM_VERSION_CHECK(13,1,0) || \
       LIBRG_CRAY_VERSION_CHECK(8,1,0) || \
       LIBRG_ARM_VERSION_CHECK(5,4,0) || \
       LIBRG_TINYC_VERSION_CHECK(0,9,24)
#    if defined(__INTPTR_TYPE__)
#      define LIBRG_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0)), int*)
#    else
#      include <stdint.h>
#      define LIBRG_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((intptr_t) ((expr) * 0)) : (int*) 0)), int*)
#    endif
#  elif \
       ( \
          defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && \
          !defined(LIBRG_SUNPRO_VERSION) && \
          !defined(LIBRG_PGI_VERSION) && \
          !defined(LIBRG_IAR_VERSION)) || \
       LIBRG_HAS_EXTENSION(c_generic_selections) || \
       LIBRG_GCC_VERSION_CHECK(4,9,0) || \
       LIBRG_INTEL_VERSION_CHECK(17,0,0) || \
       LIBRG_IBM_VERSION_CHECK(12,1,0) || \
       LIBRG_ARM_VERSION_CHECK(5,3,0)
#    if defined(__INTPTR_TYPE__)
#      define LIBRG_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0), int*: 1, void*: 0)
#    else
#      include <stdint.h>
#      define LIBRG_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((intptr_t) * 0) : (int*) 0), int*: 1, void*: 0)
#    endif
#  elif \
       defined(LIBRG_GCC_VERSION) || \
       defined(LIBRG_INTEL_VERSION) || \
       defined(LIBRG_TINYC_VERSION) || \
       defined(LIBRG_TI_ARMCL_VERSION) || \
       LIBRG_TI_CL430_VERSION_CHECK(18,12,0) || \
       defined(LIBRG_TI_CL2000_VERSION) || \
       defined(LIBRG_TI_CL6X_VERSION) || \
       defined(LIBRG_TI_CL7X_VERSION) || \
       defined(LIBRG_TI_CLPRU_VERSION) || \
       defined(__clang__)
#    define LIBRG_IS_CONSTEXPR_(expr) ( \
         sizeof(void) != \
         sizeof(*( \
           1 ? \
             ((void*) ((expr) * 0L) ) : \
             ((struct { char v[sizeof(void) * 2]; } *) 1) \
           ) \
         ) \
       )
#  endif
#endif
#if defined(LIBRG_IS_CONSTEXPR_)
#  if !defined(LIBRG_IS_CONSTANT)
#    define LIBRG_IS_CONSTANT(expr) LIBRG_IS_CONSTEXPR_(expr)
#  endif
#  define LIBRG_REQUIRE_CONSTEXPR(expr) (LIBRG_IS_CONSTEXPR_(expr) ? (expr) : (-1))
#else
#  if !defined(LIBRG_IS_CONSTANT)
#    define LIBRG_IS_CONSTANT(expr) (0)
#  endif
#  define LIBRG_REQUIRE_CONSTEXPR(expr) (expr)
#endif

#if defined(LIBRG_BEGIN_C_DECLS)
#  undef LIBRG_BEGIN_C_DECLS
#endif
#if defined(LIBRG_END_C_DECLS)
#  undef LIBRG_END_C_DECLS
#endif
#if defined(LIBRG_C_DECL)
#  undef LIBRG_C_DECL
#endif
#if defined(__cplusplus)
#  define LIBRG_BEGIN_C_DECLS extern "C" {
#  define LIBRG_END_C_DECLS }
#  define LIBRG_C_DECL extern "C"
#else
#  define LIBRG_BEGIN_C_DECLS
#  define LIBRG_END_C_DECLS
#  define LIBRG_C_DECL
#endif

#if defined(LIBRG_STATIC_ASSERT)
#  undef LIBRG_STATIC_ASSERT
#endif
#if \
  !defined(__cplusplus) && ( \
      (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || \
      LIBRG_HAS_FEATURE(c_static_assert) || \
      LIBRG_GCC_VERSION_CHECK(6,0,0) || \
      LIBRG_INTEL_VERSION_CHECK(13,0,0) || \
      defined(_Static_assert) \
    )
#  define LIBRG_STATIC_ASSERT(expr, message) _Static_assert(expr, message)
#elif \
  (defined(__cplusplus) && (__cplusplus >= 201103L)) || \
  LIBRG_MSVC_VERSION_CHECK(16,0,0)
#  define LIBRG_STATIC_ASSERT(expr, message) LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(static_assert(expr, message))
#else
#  define LIBRG_STATIC_ASSERT(expr, message)
#endif

#if defined(LIBRG_NULL)
#  undef LIBRG_NULL
#endif
#if defined(__cplusplus)
#  if __cplusplus >= 201103L
#    define LIBRG_NULL LIBRG_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(nullptr)
#  elif defined(NULL)
#    define LIBRG_NULL NULL
#  else
#    define LIBRG_NULL LIBRG_STATIC_CAST(void*, 0)
#  endif
#elif defined(NULL)
#  define LIBRG_NULL NULL
#else
#  define LIBRG_NULL ((void*) 0)
#endif

#if defined(LIBRG_MESSAGE)
#  undef LIBRG_MESSAGE
#endif
#if LIBRG_HAS_WARNING("-Wunknown-pragmas")
#  define LIBRG_MESSAGE(msg) \
  LIBRG_DIAGNOSTIC_PUSH \
  LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
  LIBRG_PRAGMA(message msg) \
  LIBRG_DIAGNOSTIC_POP
#elif \
  LIBRG_GCC_VERSION_CHECK(4,4,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_MESSAGE(msg) LIBRG_PRAGMA(message msg)
#elif LIBRG_CRAY_VERSION_CHECK(5,0,0)
#  define LIBRG_MESSAGE(msg) LIBRG_PRAGMA(_CRI message msg)
#elif LIBRG_IAR_VERSION_CHECK(8,0,0)
#  define LIBRG_MESSAGE(msg) LIBRG_PRAGMA(message(msg))
#elif LIBRG_PELLES_VERSION_CHECK(2,0,0)
#  define LIBRG_MESSAGE(msg) LIBRG_PRAGMA(message(msg))
#else
#  define LIBRG_MESSAGE(msg)
#endif

#if defined(LIBRG_WARNING)
#  undef LIBRG_WARNING
#endif
#if LIBRG_HAS_WARNING("-Wunknown-pragmas")
#  define LIBRG_WARNING(msg) \
  LIBRG_DIAGNOSTIC_PUSH \
  LIBRG_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
  LIBRG_PRAGMA(clang warning msg) \
  LIBRG_DIAGNOSTIC_POP
#elif \
  LIBRG_GCC_VERSION_CHECK(4,8,0) || \
  LIBRG_PGI_VERSION_CHECK(18,4,0) || \
  LIBRG_INTEL_VERSION_CHECK(13,0,0)
#  define LIBRG_WARNING(msg) LIBRG_PRAGMA(GCC warning msg)
#elif LIBRG_MSVC_VERSION_CHECK(15,0,0)
#  define LIBRG_WARNING(msg) LIBRG_PRAGMA(message(msg))
#else
#  define LIBRG_WARNING(msg) LIBRG_MESSAGE(msg)
#endif

#if defined(LIBRG_REQUIRE)
#  undef LIBRG_REQUIRE
#endif
#if defined(LIBRG_REQUIRE_MSG)
#  undef LIBRG_REQUIRE_MSG
#endif
#if LIBRG_HAS_ATTRIBUTE(diagnose_if)
#  if LIBRG_HAS_WARNING("-Wgcc-compat")
#    define LIBRG_REQUIRE(expr) \
       LIBRG_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
       __attribute__((diagnose_if(!(expr), #expr, "error"))) \
       LIBRG_DIAGNOSTIC_POP
#    define LIBRG_REQUIRE_MSG(expr,msg) \
       LIBRG_DIAGNOSTIC_PUSH \
       _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
       __attribute__((diagnose_if(!(expr), msg, "error"))) \
       LIBRG_DIAGNOSTIC_POP
#  else
#    define LIBRG_REQUIRE(expr) __attribute__((diagnose_if(!(expr), #expr, "error")))
#    define LIBRG_REQUIRE_MSG(expr,msg) __attribute__((diagnose_if(!(expr), msg, "error")))
#  endif
#else
#  define LIBRG_REQUIRE(expr)
#  define LIBRG_REQUIRE_MSG(expr,msg)
#endif

#if defined(LIBRG_FLAGS)
#  undef LIBRG_FLAGS
#endif
#if LIBRG_HAS_ATTRIBUTE(flag_enum)
#  define LIBRG_FLAGS __attribute__((__flag_enum__))
#endif

#if defined(LIBRG_FLAGS_CAST)
#  undef LIBRG_FLAGS_CAST
#endif
#if LIBRG_INTEL_VERSION_CHECK(19,0,0)
#  define LIBRG_FLAGS_CAST(T, expr) (__extension__ ({ \
  LIBRG_DIAGNOSTIC_PUSH \
      _Pragma("warning(disable:188)") \
      ((T) (expr)); \
      LIBRG_DIAGNOSTIC_POP \
    }))
#else
#  define LIBRG_FLAGS_CAST(T, expr) LIBRG_STATIC_CAST(T, expr)
#endif

#if defined(LIBRG_EMPTY_BASES)
#  undef LIBRG_EMPTY_BASES
#endif
#if LIBRG_MSVC_VERSION_CHECK(19,0,23918) && !LIBRG_MSVC_VERSION_CHECK(20,0,0)
#  define LIBRG_EMPTY_BASES __declspec(empty_bases)
#else
#  define LIBRG_EMPTY_BASES
#endif

/* Remaining macros are deprecated. */

#if defined(LIBRG_GCC_NOT_CLANG_VERSION_CHECK)
#  undef LIBRG_GCC_NOT_CLANG_VERSION_CHECK
#endif
#if defined(__clang__)
#  define LIBRG_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) (0)
#else
#  define LIBRG_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) LIBRG_GCC_VERSION_CHECK(major,minor,patch)
#endif

#if defined(LIBRG_CLANG_HAS_ATTRIBUTE)
#  undef LIBRG_CLANG_HAS_ATTRIBUTE
#endif
#define LIBRG_CLANG_HAS_ATTRIBUTE(attribute) LIBRG_HAS_ATTRIBUTE(attribute)

#if defined(LIBRG_CLANG_HAS_CPP_ATTRIBUTE)
#  undef LIBRG_CLANG_HAS_CPP_ATTRIBUTE
#endif
#define LIBRG_CLANG_HAS_CPP_ATTRIBUTE(attribute) LIBRG_HAS_CPP_ATTRIBUTE(attribute)

#if defined(LIBRG_CLANG_HAS_BUILTIN)
#  undef LIBRG_CLANG_HAS_BUILTIN
#endif
#define LIBRG_CLANG_HAS_BUILTIN(builtin) LIBRG_HAS_BUILTIN(builtin)

#if defined(LIBRG_CLANG_HAS_FEATURE)
#  undef LIBRG_CLANG_HAS_FEATURE
#endif
#define LIBRG_CLANG_HAS_FEATURE(feature) LIBRG_HAS_FEATURE(feature)

#if defined(LIBRG_CLANG_HAS_EXTENSION)
#  undef LIBRG_CLANG_HAS_EXTENSION
#endif
#define LIBRG_CLANG_HAS_EXTENSION(extension) LIBRG_HAS_EXTENSION(extension)

#if defined(LIBRG_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE)
#  undef LIBRG_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE
#endif
#define LIBRG_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) LIBRG_HAS_DECLSPEC_ATTRIBUTE(attribute)

#if defined(LIBRG_CLANG_HAS_WARNING)
#  undef LIBRG_CLANG_HAS_WARNING
#endif
#define LIBRG_CLANG_HAS_WARNING(warning) LIBRG_HAS_WARNING(warning)

#endif /* !defined(LIBRG_HEDLEY_VERSION) || (LIBRG_HEDLEY_VERSION < X) */

#define LIBRG_VERSION LIBRG_VERSION_ENCODE(LIBRG_VERSION_MAJOR, LIBRG_VERSION_MINOR, LIBRG_VERSION_PATCH)

#ifdef LIBRG_IMPL
    #ifndef LIBRG_IMPLEMENTATION
    #define LIBRG_IMPLEMENTATION
    #endif
#endif

#if defined(__cplusplus) && !defined(LIBRG_EXTERN)
    #define LIBRG_EXTERN extern "C"
#else
    #define LIBRG_EXTERN extern
#endif

#ifndef LIBRG_API
    #if defined(LIBRG_SHARED_LIB)
        #ifdef LIBRG_IMPLEMENTATION
            #define LIBRG_API LIBRG_PUBLIC
        #else
            #define LIBRG_API LIBRG_IMPORT
        #endif
    #elif defined(LIBRG_STATIC_LIB)
        #ifdef LIBRG_IMPLEMENTATION
            #define LIBRG_API
        #else
            #define LIBRG_API LIBRG_EXTERN
        #endif
    #elif defined(LIBRG_STATIC)
        #define LIBRG_API static
    #elif defined(LIBRG_EMSCRIPTEN)
        #define LIBRG_API EMSCRIPTEN_KEEPALIVE
    #else
        #define LIBRG_API LIBRG_EXTERN
    #endif
#endif

#include <stdint.h>
#include <stddef.h>

#if defined(__EMSCRIPTEN__)
    #include <emscripten.h>
#endif

// file: header/types.h

#ifdef LIBRG_EDITOR
#include <librg.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Main type definitions
// !
// =======================================================================//

typedef void librg_world;
typedef void librg_event;
typedef int64_t librg_chunk;

#define LIBRG_OFFSET_BEG ((int16_t)0x8000)
#define LIBRG_OFFSET_MID ((int16_t)0x0000)
#define LIBRG_OFFSET_END ((int16_t)0x7fff)

#define LIBRG_IN
#define LIBRG_OUT
#define LIBRG_INOUT

typedef enum librg_event_type {
    LIBRG_WRITE_CREATE,
    LIBRG_WRITE_UPDATE,
    LIBRG_WRITE_REMOVE,

    LIBRG_READ_CREATE,
    LIBRG_READ_UPDATE,
    LIBRG_READ_REMOVE,

    LIBRG_ERROR_CREATE,
    LIBRG_ERROR_UPDATE,
    LIBRG_ERROR_REMOVE,
} librg_event_type;

typedef int32_t (*librg_event_fn)(librg_world *world, librg_event *event);

typedef enum librg_visibility {
    LIBRG_VISIBLITY_DEFAULT,
    LIBRG_VISIBLITY_NEVER,
    LIBRG_VISIBLITY_ALWAYS,
} librg_visibility;


// =======================================================================//
// !
// ! Errors, statuses, warnings and information message codes
// !
// =======================================================================//

#define LIBRG_OK                        (+0x0000)
#define LIBRG_FAIL(code)                (code < 0)
#define LIBRG_TRUE                      (+0x0001)
#define LIBRG_FALSE                     (+0x0000)

#define LIBRG_WORLD_INVALID             (-0x0001)
#define LIBRG_OWNER_INVALID             (-0x0002)
#define LIBRG_CHUNK_INVALID             (-0x0003)
#define LIBRG_ENTITY_INVALID            (-0x0004)
#define LIBRG_ENTITY_FOREIGN            (-0x0005)
#define LIBRG_EVENT_INVALID             (-0x0006)
#define LIBRG_HANDLER_REPLACED          (-0x0002)
#define LIBRG_HANDLER_EMPTY             (-0x0002)
#define LIBRG_ENTITY_UNTRACKED          (-0x0002)
#define LIBRG_ENTITY_ALREADY_TRACKED    (-0x0002)
#define LIBRG_ENTITY_VISIBILITY_IGNORED (-0x0003)
#define LIBRG_WRITE_REJECT              (-0x0001)
#define LIBRG_READ_INVALID              (-0x0003)
#define LIBRG_NULL_REFERENCE            (-0x0007)

LIBRG_END_C_DECLS
// file: header/general.h

#ifdef LIBRG_EDITOR
#include <librg.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Context methods
// !
// =======================================================================//

LIBRG_API uint32_t      librg_version();
LIBRG_API librg_world * librg_world_create();
LIBRG_API int8_t        librg_world_destroy(librg_world *world);
LIBRG_API int8_t        librg_world_valid(librg_world *world);
LIBRG_API int8_t        librg_world_userdata_set(librg_world *world, void *data);
LIBRG_API void *        librg_world_userdata_get(librg_world *world);

// =======================================================================//
// !
// ! Configuration methods
// !
// =======================================================================//

LIBRG_API int8_t librg_config_chunkamount_set(librg_world *world, uint16_t x, uint16_t y, uint16_t z);
LIBRG_API int8_t librg_config_chunkamount_get(librg_world *world, uint16_t *x, uint16_t *y, uint16_t *z);
LIBRG_API int8_t librg_config_chunksize_set(librg_world *world, uint16_t x, uint16_t y, uint16_t z);
LIBRG_API int8_t librg_config_chunksize_get(librg_world *world, uint16_t *x, uint16_t *y, uint16_t *z);
LIBRG_API int8_t librg_config_chunkoffset_set(librg_world *world, int16_t x, int16_t y, int16_t z);
LIBRG_API int8_t librg_config_chunkoffset_get(librg_world *world, int16_t *x, int16_t *y, int16_t *z);

// =======================================================================//
// !
// ! Events
// !
// =======================================================================//

LIBRG_API int8_t            librg_event_set(librg_world *world, librg_event_type, librg_event_fn);
LIBRG_API int8_t            librg_event_remove(librg_world *world, librg_event_type);

LIBRG_API librg_event_type  librg_event_type_get(librg_world *world, librg_event *event);
LIBRG_API int64_t           librg_event_owner_get(librg_world *world, librg_event *event);
LIBRG_API int64_t           librg_event_entity_get(librg_world *world, librg_event *event);
LIBRG_API char *            librg_event_buffer_get(librg_world *world, librg_event *event);
LIBRG_API int32_t           librg_event_size_get(librg_world *world, librg_event *event);
LIBRG_API void *            librg_event_userdata_get(librg_world *world, librg_event *event);

// =======================================================================//
// !
// ! Utility methods
// !
// =======================================================================//

LIBRG_API librg_chunk librg_chunk_from_realpos(librg_world *world, double x, double y, double z);
LIBRG_API librg_chunk librg_chunk_from_chunkpos(librg_world *world, int16_t chunk_x, int16_t chunk_y, int16_t chunk_z);
LIBRG_API int8_t      librg_chunk_to_chunkpos(librg_world *world, librg_chunk id, int16_t *chunk_x, int16_t *chunk_y, int16_t *chunk_z);

LIBRG_END_C_DECLS
// file: header/entity.h

#ifdef LIBRG_EDITOR
#include <librg.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Basic entity manipulation
// !
// =======================================================================//

LIBRG_API int8_t  librg_entity_track(librg_world *world, int64_t entity_id);
LIBRG_API int8_t  librg_entity_untrack(librg_world *world, int64_t entity_id);
LIBRG_API int8_t  librg_entity_tracked(librg_world *world, int64_t entity_id);
LIBRG_API int8_t  librg_entity_foreign(librg_world *world, int64_t entity_id);
LIBRG_API int8_t  librg_entity_owned(librg_world *world, int64_t entity_id);
LIBRG_API int32_t librg_entity_count(librg_world *world);

// =======================================================================//
// !
// ! Entity data methods
// !
// =======================================================================//

LIBRG_API int8_t        librg_entity_userdata_set(librg_world *world, int64_t entity_id, void *data);
LIBRG_API void *        librg_entity_userdata_get(librg_world *world, int64_t entity_id);
LIBRG_API int8_t        librg_entity_chunk_set(librg_world *world, int64_t entity_id, librg_chunk);
LIBRG_API librg_chunk   librg_entity_chunk_get(librg_world *world, int64_t entity_id);
LIBRG_API int8_t        librg_entity_chunkarray_set(librg_world *world, int64_t entity_id, const librg_chunk *chunks, size_t chunk_amount);
LIBRG_API int8_t        librg_entity_chunkarray_get(librg_world *world, int64_t entity_id, LIBRG_OUT librg_chunk *chunks, LIBRG_INOUT size_t *chunk_amount);
LIBRG_API int8_t        librg_entity_dimension_set(librg_world *world, int64_t entity_id, int32_t dimension);
LIBRG_API int32_t       librg_entity_dimension_get(librg_world *world, int64_t entity_id);
LIBRG_API int8_t        librg_entity_owner_set(librg_world *world, int64_t entity_id, int64_t owner_id);
LIBRG_API int64_t       librg_entity_owner_get(librg_world *world, int64_t entity_id);
LIBRG_API int8_t        librg_entity_radius_set(librg_world *world, int64_t entity_id, int8_t observed_chunk_radius);
LIBRG_API int8_t        librg_entity_radius_get(librg_world *world, int64_t entity_id);
LIBRG_API int8_t        librg_entity_visibility_global_set(librg_world *world, int64_t entity_id, librg_visibility value);
LIBRG_API int8_t        librg_entity_visibility_global_get(librg_world *world, int64_t entity_id);
LIBRG_API int8_t        librg_entity_visibility_owner_set(librg_world *world, int64_t entity_id, int64_t owner_id, librg_visibility value);
LIBRG_API int8_t        librg_entity_visibility_owner_get(librg_world *world, int64_t entity_id, int64_t owner_id);

#if 0 /* for future releases */
LIBRG_API int8_t        librg_entity_behavior_set(librg_world *world, int64_t entity_id, librg_behavior key, int32_t value);
LIBRG_API int32_t       librg_entity_behavior_get(librg_world *world, int64_t entity_id, librg_behavior key);
#endif

LIBRG_END_C_DECLS
// file: header/query.h

#ifdef LIBRG_EDITOR
#include <librg.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! World data/query methods
// !
// =======================================================================//

LIBRG_API int32_t librg_world_fetch_all(librg_world *world, LIBRG_OUT int64_t *entity_ids, LIBRG_INOUT size_t *entity_amount);
LIBRG_API int32_t librg_world_fetch_chunk(librg_world *world, librg_chunk chunk, LIBRG_OUT int64_t *entity_ids, LIBRG_INOUT size_t *entity_amount);
LIBRG_API int32_t librg_world_fetch_chunkarray(librg_world *world, const librg_chunk *chunks, size_t chunk_amount, LIBRG_OUT int64_t *entity_ids, LIBRG_INOUT size_t *entity_amount);
LIBRG_API int32_t librg_world_fetch_owner(librg_world *world, int64_t owner_id, LIBRG_OUT int64_t *entity_ids, LIBRG_INOUT size_t *entity_amount);
LIBRG_API int32_t librg_world_fetch_ownerarray(librg_world *world, const int64_t *owner_ids, size_t owner_amount, LIBRG_OUT int64_t *entity_ids, LIBRG_INOUT size_t *entity_amount);
LIBRG_API int32_t librg_world_query(librg_world *world, int64_t owner_id, LIBRG_OUT int64_t *entity_ids, LIBRG_INOUT size_t *entity_amount);

LIBRG_END_C_DECLS
// file: header/packing.h

#ifdef LIBRG_EDITOR
#include <librg.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! World data (de)packing methods
// !
// =======================================================================//

LIBRG_API int32_t librg_world_read(librg_world *world, int64_t owner_id, const char *buffer, size_t size, void *userdata);
LIBRG_API int32_t librg_world_write(librg_world *world, int64_t owner_id, LIBRG_OUT char *buffer, LIBRG_INOUT size_t *size, void *userdata);

LIBRG_END_C_DECLS

/* Implementation part */
#if defined(LIBRG_IMPLEMENTATION) && !defined(LIBRG_IMPLEMENTATION_DONE)
#define LIBRG_IMPLEMENTATION_DONE

#ifndef LIBRG_CUSTOM_ZPL
    #define ZPL_NANO
    #define ZPL_IMPL

    /**
      ZPL - Global module

    Usage:
      #define ZPL_IMPLEMENTATION exactly in ONE source file right BEFORE including the library, like:

      #define ZPL_IMPLEMENTATION
      #include "zpl.h"

      You can also use a freestanding version of ZPL by using ZPL_NANO, like:

      #define ZPL_IMPLEMENTATION
      #define ZPL_NANO
      #include "zpl.h"

    Options:

      ZPL_EDITOR - This macro should be used by the IDE's Intellisense to parse ZPL correctly. It can NEVER be used for actual compilation of the library!
      ZPL_PREFIX_TYPES - to make sure all ZPL defined types have a prefix to avoid cluttering the global namespace.
      ZPL_DEFINE_NULL_MACRO - to let ZPL define what NULL stands for in case it is undefined.
      ZPL_NO_MATH_H - disables the use of math.h library and replaces it with custom routines or SIMD.

    Credits:
      Read AUTHORS.md

    GitHub:
      https://github.com/zpl-c/zpl

    Version History:
      10.5.1  - Fixed zpl_rdtsc for Emscripten
      10.5.0  - Changed casts to memcopy in random methods, added embed cmd
      10.4.1  - Jobs system now enqueues jobs with def priority of 1.0
      10.4.0  - [META] version bump
      10.3.0  - Pool allocator now supports zpl_free_all
      10.2.0  - [META] version bump
      10.1.0  - Additional math methods (thanks to funZX and msmshazan)
      10.0.15 - WIP Emscripten fixes
      10.0.14 - FreeBSD support
      10.0.13 - OpenBSD support
      10.0.12 - Cygwin fixes
      10.0.11 - Tweak module dependencies
      10.0.10 - Fix zero-allocation regression in filesystem module
      10.0.9 - Fix multi-compilation unit builds
      10.0.8 - Fix zpl_printf "%0d" format specifier
      10.0.4 - Flush tester output to fix ordering
      10.0.3 - Fix ZPL_STATIC_ASSERT under MSVC
      10.0.0 - Major overhaul of the library

      9.8.10 - JSON fix array-based documents with objects
      9.8.9 - JSON document structured as array now properly recognizes the root object as array.
      9.8.8 - Fixed an incorrect parsing of empty array nodes.
      9.8.7 - Improve FreeBSD support
      9.8.6 - WIP: Handle inlined methods properly
      9.8.5 - Fix incorrect usage of EOF and opts dependency on JSON5 module's methods
      9.8.4 - Fix MSVC ZPL_NO_MATH_H code branch using incorrect methods internally
      9.8.3 - Fix MinGW GCC related issue with zpl_printf %lld format
      9.8.2 - Fix VS C4190 issue
      9.8.1 - Fix several C++ type casting quirks
      9.8.0 - Incorporated OpenGL into ZPL core as an optional module
      9.7.0 - Added co-routine module
      9.6.0 - Added process module for creation and manipulation
      9.5.2 - zpl_printf family now prints (null) on NULL string arguments
      9.5.1 - Fixed JSON5 real number export support + indentation fixes
      9.5.0 - Added base64 encode/decode methods
      9.4.10- Small enum style changes
      9.4.9 - Remove #undef for cast and hard_cast (sorry)
      9.4.8 - Fix quote-less JSON node name resolution
      9.4.7 - Additional change to the code
      9.4.6 - Fix issue where zpl_json_find would have false match on substrings
      9.4.5 - Mistakes were made, fixed compilation errors
      9.4.3 - Fix old API shenanigans
      9.4.2 - Fix small API typos
      9.4.1 - Reordered JSON5 constants to integrate better with conditions
      9.4.0 - JSON5 API changes made to zpl_json_find
      9.3.0 - Change how zpl uses basic types internally
      9.2.0 - Directory listing was added. Check dirlist_api.c test for more info
      9.1.1 - Fix WIN32_LEAN_AND_MEAN redefinition properly
      9.1.0 - get_env rework and fixes
      9.0.3 - Small fixes and removals
      9.0.0 - New documentation format, removed deprecated code, changed styles

      8.14.1 - Fix string library
      8.14.0 - Added zpl_re_match_all
      8.13.0 - Update system command API
      8.12.6 - Fix warning in CLI options parser
      8.12.5 - Support parametric options preceding positionals
      8.12.4 - Fixed opts positionals ordering
      8.12.3 - Fixed incorrect handling of flags preceding positionals
      8.12.2 - JSON parsing remark added
      8.12.1 - Fixed a lot of important stuff
      8.12.0 - Added helper constructors for containers
      8.11.2 - Fix bug in opts module
      8.11.1 - Small code improvements
      8.11.0 - Ported regex processor from https://github.com/gingerBill/gb/ and applied fixes on top of it
      8.10.2 - Fix zpl_strtok
      8.10.1 - Replace zpl_strchr by zpl_char_last_occurence
      8.10.0 - Added zpl_strchr
      8.9.0  - API improvements for JSON5 parser
      8.8.4  - Add support for SJSON formatting http://bitsquid.blogspot.com/2009/10/simplified-json-notation.html

      6.8.3  - JSON5 exp fix
      6.8.2  - Bugfixes applied from gb
      6.8.1  - Performance improvements for JSON5 parser
      6.8.0  - zpl.h is now generated by build.py
      6.7.0  - Several fixes and added switches
      6.6.0  - Several significant changes made to the repository
      6.5.0  - Ported platform layer from https://github.com/gingerBill/gb/
      6.4.1  - Use zpl_strlen in zpl_strdup
      6.4.0  - Deprecated zpl_buffer_free and added zpl_array_end, zpl_buffer_end
      6.3.0  - Added zpl_strdup
      6.2.1  - Remove math redundancies
      6.2.0  - Integrated zpl_math.h into zpl.h
      6.1.1  - Added direct.h include for win c++ dir methods
      6.1.0  - Added zpl_path_mkdir, zpl_path_rmdir, and few new zplFileErrors
      6.0.4  - More MSVC(++) satisfaction by fixing warnings
      6.0.3  - Satisfy MSVC by fixing a warning
      6.0.2  - Fixed warnings for json5 i64 printfs
      6.0.1  - Fixed warnings for particual win compiler in dirlist method
      6.0.0  - New build, include/ was renamed to code/

      5.8.3  - Naming fixes
      5.8.2  - Job system now supports prioritized tasks
      5.8.1  - Renames zpl_pad to zpl_ring
      5.8.0  - Added instantiated scratch pad (circular buffer)
      5.7.2  - Added Windows support for zpl_path_dirlist
      5.7.1  - Fixed few things in job system + macOS support for zpl_path_dirlist
      5.7.0  - Added a job system (zpl_thread_pool)
      5.6.5  - Fixes extra error cases for zpl_opts when input is:
             - missing a value for an option,
             - having an extra value for a flag (e.g. --enable-log shouldn't get a value.)
      5.6.4  - Several tweaks to the zpl_opts API
      5.6.3  - Added support for flags without values
      5.6.2  - Improve error handling for zpl_opts
      5.6.1  - Added support for strings with spaces in zpl_opts
      5.6.0  - Added zpl_opts for CLI argument parsing
      5.5.1  - Fixed time method for win
      5.5.0  - Integrate JSON5 writer into the core
      5.4.0  - Improved storage support for numbers in JSON5 parser
      5.3.0  - Integrated zpl_json into ZPL
      5.2.0  - Added zpl_string_sprintf
      5.1.1  - Added zpl_system_command_nores for output-less execution
      5.1.0  - Added event handler
      5.0.4  - Fix alias for zpl_list
      5.0.3  - Finalizing syntax changes
      5.0.2  - Fix segfault when using zpl_stack_memory
      5.0.1  - Small code improvements
      5.0.0  - Project structure changes

      4.7.2  - Got rid of size arg for zpl_str_split_lines
      4.7.1  - Added an example
      4.7.0  - Added zpl_path_dirlist
      4.6.1  - zpl_memcopy x86 patch from upstream
      4.6.0  - Added few string-related functions
      4.5.9  - Error fixes
      4.5.8  - Warning fixes
      4.5.7  - Fixed timer loops. zpl_time* related functions work with seconds now
      4.5.6  - Fixed zpl_time_now() for Windows and Linux
      4.5.5  - Small cosmetic changes
      4.5.4  - Fixed issue when zpl_list_add would break the links
             - when adding a new item between nodes
      4.5.3  - Fixed malformed enum values
      4.5.1  - Fixed some warnings
      4.5.0  - Added zpl_array_append_at
      4.4.0  - Added zpl_array_back, zpl_array_front
      4.3.0  - Added zpl_list
      4.2.0  - Added zpl_system_command_str
      4.1.2  - GG, fixed small compilation error
      4.1.1  - Fixed possible security issue in zpl_system_command
      4.1.0  - Added zpl_string_make_reserve and small fixes
      4.0.2  - Warning fix for _LARGEFILE64_SOURCE
      4.0.1  - include stdlib.h for getenv (temp)
      4.0.0  - ARM support, coding style changes and various improvements

      3.4.1  - zpl_memcopy now uses memcpy for ARM arch-family
      3.4.0  - Removed obsolete code
      3.3.4  - Added Travis CI config
      3.3.3  - Small macro formatting changes + ZPL_SYSTEM_IOS
      3.3.2  - Fixes for android arm
      3.3.1  - Fixed some type cast warnings
      3.3.0  - Added Android support
      3.1.5  - Renamed userptr to user_data in timer
      3.1.4  - Fix for zpl_buffer not allocating correctly
      3.1.2  - Small fix in zpl_memcompare
      3.1.1  - Added char* conversion for data field in zpl_array_header
      3.1.0  - Added data field to zpl_array_header
      3.0.7  - Added timer userptr as argument to callback
      3.0.6  - Small changes
      3.0.5  - Fixed compilation for emscripten
      3.0.4  - Small fixes for tiny cpp warnings
      3.0.3  - Small fixes for various cpp warnings and errors
      3.0.2  - Fixed linux part, and removed trailing spaces
      3.0.1  - Small bugfix in zpl_file_open
      3.0.0  - Added several fixes and features

      2.4.0  - Added remove to hash table
      2.3.3  - Removed redundant code
      2.3.2  - Eliminated extra warnings
      2.3.1  - Warning hunt
      2.3.0  - Added the ability to copy array/buffer and fixed bug in hash table.
      2.2.1  - Used tmpfile() for Windows
      2.2.0  - Added zpl_file_temp
      2.1.1  - Very small fix (forgive me)
      2.1.0  - Added the ability to resize bitstream
      2.0.8  - Small adjustments
      2.0.7  - MinGW related fixes
      2.0.0  - New NPM based version

      1.2.2  - Small fix
      1.2.1  - Macro fixes
      1.2.0  - Added zpl_async macro
      1.1.0  - Added timer feature
      1.0.0  - Initial version

      This Software is dual licensed under the following licenses:

      Unlicense
      This is free and unencumbered software released into the public domain.

      Anyone is free to copy, modify, publish, use, compile, sell, or
      distribute this software, either in source code form or as a compiled
      binary, for any purpose, commercial or non-commercial, and by any
      means.

      In jurisdictions that recognize copyright laws, the author or authors
      of this software dedicate any and all copyright interest in the
      software to the public domain. We make this dedication for the benefit
      of the public at large and to the detriment of our heirs and
      successors. We intend this dedication to be an overt act of
      relinquishment in perpetuity of all present and future rights to this
      software under copyright law.

      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
      EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
      MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
      IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
      OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
      ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
      OTHER DEALINGS IN THE SOFTWARE.

      For more information, please refer to <http://unlicense.org/>

      Apache 2.0
      Copyright 2017-2019 Dominik Madarász <zaklaus@outlook.com>
      Licensed under the Apache License, Version 2.0 (the "License");
      you may not use this file except in compliance with the License.
      You may obtain a copy of the License at

          http://www.apache.org/licenses/LICENSE-2.0

      Unless required by applicable law or agreed to in writing, software
      distributed under the License is distributed on an "AS IS" BASIS,
      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
      See the License for the specific language governing permissions and
      limitations under the License.

    */

    #ifndef ZPL_H
    #define ZPL_H

    #define ZPL_VERSION_MAJOR 10
    #define ZPL_VERSION_MINOR 5
    #define ZPL_VERSION_PATCH 1
    #define ZPL_VERSION_PRE ""

    // file: zpl_hedley.h

    /* Hedley - https://nemequ.github.io/hedley
     * Created by Evan Nemerson <evan@nemerson.com>
     *
     * To the extent possible under law, the author(s) have dedicated all
     * copyright and related and neighboring rights to this software to
     * the public domain worldwide. This software is distributed without
     * any warranty.
     *
     * For details, see <http://creativecommons.org/publicdomain/zero/1.0/>.
     * SPDX-License-Identifier: CC0-1.0
     */

    #if !defined(ZPL_HEDLEY_VERSION) || (ZPL_HEDLEY_VERSION < 12)
    #if defined(ZPL_HEDLEY_VERSION)
    #  undef ZPL_HEDLEY_VERSION
    #endif
    #define ZPL_HEDLEY_VERSION 12

    #if defined(ZPL_STRINGIFY_EX)
    #  undef ZPL_STRINGIFY_EX
    #endif
    #define ZPL_STRINGIFY_EX(x) #x

    #if defined(ZPL_STRINGIFY)
    #  undef ZPL_STRINGIFY
    #endif
    #define ZPL_STRINGIFY(x) ZPL_STRINGIFY_EX(x)

    #if defined(ZPL_CONCAT_EX)
    #  undef ZPL_CONCAT_EX
    #endif
    #define ZPL_CONCAT_EX(a,b) a##b

    #if defined(ZPL_CONCAT)
    #  undef ZPL_CONCAT
    #endif
    #define ZPL_CONCAT(a,b) ZPL_CONCAT_EX(a,b)

    #if defined(ZPL_VERSION_ENCODE)
    #  undef ZPL_VERSION_ENCODE
    #endif
    #define ZPL_VERSION_ENCODE(major,minor,patch) (((major) * 1000000) + ((minor) * 1000) + (patch))

    #if defined(ZPL_VERSION_DECODE_MAJOR)
    #  undef ZPL_VERSION_DECODE_MAJOR
    #endif
    #define ZPL_VERSION_DECODE_MAJOR(version) ((version) / 1000000)

    #if defined(ZPL_VERSION_DECODE_MINOR)
    #  undef ZPL_VERSION_DECODE_MINOR
    #endif
    #define ZPL_VERSION_DECODE_MINOR(version) (((version) % 1000000) / 1000)

    #if defined(ZPL_VERSION_DECODE_PATCH)
    #  undef ZPL_VERSION_DECODE_PATCH
    #endif
    #define ZPL_VERSION_DECODE_PATCH(version) ((version) % 1000)

    #if defined(ZPL_GNUC_VERSION)
    #  undef ZPL_GNUC_VERSION
    #endif
    #if defined(__GNUC__) && defined(__GNUC_PATCHLEVEL__)
    #  define ZPL_GNUC_VERSION ZPL_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__)
    #elif defined(__GNUC__)
    #  define ZPL_GNUC_VERSION ZPL_VERSION_ENCODE(__GNUC__, __GNUC_MINOR__, 0)
    #endif

    #if defined(ZPL_GNUC_VERSION_CHECK)
    #  undef ZPL_GNUC_VERSION_CHECK
    #endif
    #if defined(ZPL_GNUC_VERSION)
    #  define ZPL_GNUC_VERSION_CHECK(major,minor,patch) (ZPL_GNUC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_GNUC_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_MSVC_VERSION)
    #  undef ZPL_MSVC_VERSION
    #endif
    #if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 140000000)
    #  define ZPL_MSVC_VERSION ZPL_VERSION_ENCODE(_MSC_FULL_VER / 10000000, (_MSC_FULL_VER % 10000000) / 100000, (_MSC_FULL_VER % 100000) / 100)
    #elif defined(_MSC_FULL_VER)
    #  define ZPL_MSVC_VERSION ZPL_VERSION_ENCODE(_MSC_FULL_VER / 1000000, (_MSC_FULL_VER % 1000000) / 10000, (_MSC_FULL_VER % 10000) / 10)
    #elif defined(_MSC_VER)
    #  define ZPL_MSVC_VERSION ZPL_VERSION_ENCODE(_MSC_VER / 100, _MSC_VER % 100, 0)
    #endif

    #if defined(ZPL_MSVC_VERSION_CHECK)
    #  undef ZPL_MSVC_VERSION_CHECK
    #endif
    #if !defined(_MSC_VER)
    #  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (0)
    #elif defined(_MSC_VER) && (_MSC_VER >= 1400)
    #  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 10000000) + (minor * 100000) + (patch)))
    #elif defined(_MSC_VER) && (_MSC_VER >= 1200)
    #  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_FULL_VER >= ((major * 1000000) + (minor * 10000) + (patch)))
    #else
    #  define ZPL_MSVC_VERSION_CHECK(major,minor,patch) (_MSC_VER >= ((major * 100) + (minor)))
    #endif

    #if defined(ZPL_INTEL_VERSION)
    #  undef ZPL_INTEL_VERSION
    #endif
    #if defined(__INTEL_COMPILER) && defined(__INTEL_COMPILER_UPDATE)
    #  define ZPL_INTEL_VERSION ZPL_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, __INTEL_COMPILER_UPDATE)
    #elif defined(__INTEL_COMPILER)
    #  define ZPL_INTEL_VERSION ZPL_VERSION_ENCODE(__INTEL_COMPILER / 100, __INTEL_COMPILER % 100, 0)
    #endif

    #if defined(ZPL_INTEL_VERSION_CHECK)
    #  undef ZPL_INTEL_VERSION_CHECK
    #endif
    #if defined(ZPL_INTEL_VERSION)
    #  define ZPL_INTEL_VERSION_CHECK(major,minor,patch) (ZPL_INTEL_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_INTEL_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_PGI_VERSION)
    #  undef ZPL_PGI_VERSION
    #endif
    #if defined(__PGI) && defined(__PGIC__) && defined(__PGIC_MINOR__) && defined(__PGIC_PATCHLEVEL__)
    #  define ZPL_PGI_VERSION ZPL_VERSION_ENCODE(__PGIC__, __PGIC_MINOR__, __PGIC_PATCHLEVEL__)
    #endif

    #if defined(ZPL_PGI_VERSION_CHECK)
    #  undef ZPL_PGI_VERSION_CHECK
    #endif
    #if defined(ZPL_PGI_VERSION)
    #  define ZPL_PGI_VERSION_CHECK(major,minor,patch) (ZPL_PGI_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_PGI_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_SUNPRO_VERSION)
    #  undef ZPL_SUNPRO_VERSION
    #endif
    #if defined(__SUNPRO_C) && (__SUNPRO_C > 0x1000)
    #  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((((__SUNPRO_C >> 16) & 0xf) * 10) + ((__SUNPRO_C >> 12) & 0xf), (((__SUNPRO_C >> 8) & 0xf) * 10) + ((__SUNPRO_C >> 4) & 0xf), (__SUNPRO_C & 0xf) * 10)
    #elif defined(__SUNPRO_C)
    #  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((__SUNPRO_C >> 8) & 0xf, (__SUNPRO_C >> 4) & 0xf, (__SUNPRO_C) & 0xf)
    #elif defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x1000)
    #  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((((__SUNPRO_CC >> 16) & 0xf) * 10) + ((__SUNPRO_CC >> 12) & 0xf), (((__SUNPRO_CC >> 8) & 0xf) * 10) + ((__SUNPRO_CC >> 4) & 0xf), (__SUNPRO_CC & 0xf) * 10)
    #elif defined(__SUNPRO_CC)
    #  define ZPL_SUNPRO_VERSION ZPL_VERSION_ENCODE((__SUNPRO_CC >> 8) & 0xf, (__SUNPRO_CC >> 4) & 0xf, (__SUNPRO_CC) & 0xf)
    #endif

    #if defined(ZPL_SUNPRO_VERSION_CHECK)
    #  undef ZPL_SUNPRO_VERSION_CHECK
    #endif
    #if defined(ZPL_SUNPRO_VERSION)
    #  define ZPL_SUNPRO_VERSION_CHECK(major,minor,patch) (ZPL_SUNPRO_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_SUNPRO_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_EMSCRIPTEN_VERSION)
    #  undef ZPL_EMSCRIPTEN_VERSION
    #endif
    #if defined(__EMSCRIPTEN__)
    #  define ZPL_EMSCRIPTEN_VERSION ZPL_VERSION_ENCODE(__EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__)
    #endif

    #if defined(ZPL_EMSCRIPTEN_VERSION_CHECK)
    #  undef ZPL_EMSCRIPTEN_VERSION_CHECK
    #endif
    #if defined(ZPL_EMSCRIPTEN_VERSION)
    #  define ZPL_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (ZPL_EMSCRIPTEN_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_EMSCRIPTEN_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_ARM_VERSION)
    #  undef ZPL_ARM_VERSION
    #endif
    #if defined(__CC_ARM) && defined(__ARMCOMPILER_VERSION)
    #  define ZPL_ARM_VERSION ZPL_VERSION_ENCODE(__ARMCOMPILER_VERSION / 1000000, (__ARMCOMPILER_VERSION % 1000000) / 10000, (__ARMCOMPILER_VERSION % 10000) / 100)
    #elif defined(__CC_ARM) && defined(__ARMCC_VERSION)
    #  define ZPL_ARM_VERSION ZPL_VERSION_ENCODE(__ARMCC_VERSION / 1000000, (__ARMCC_VERSION % 1000000) / 10000, (__ARMCC_VERSION % 10000) / 100)
    #endif

    #if defined(ZPL_ARM_VERSION_CHECK)
    #  undef ZPL_ARM_VERSION_CHECK
    #endif
    #if defined(ZPL_ARM_VERSION)
    #  define ZPL_ARM_VERSION_CHECK(major,minor,patch) (ZPL_ARM_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_ARM_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_IBM_VERSION)
    #  undef ZPL_IBM_VERSION
    #endif
    #if defined(__ibmxl__)
    #  define ZPL_IBM_VERSION ZPL_VERSION_ENCODE(__ibmxl_version__, __ibmxl_release__, __ibmxl_modification__)
    #elif defined(__xlC__) && defined(__xlC_ver__)
    #  define ZPL_IBM_VERSION ZPL_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, (__xlC_ver__ >> 8) & 0xff)
    #elif defined(__xlC__)
    #  define ZPL_IBM_VERSION ZPL_VERSION_ENCODE(__xlC__ >> 8, __xlC__ & 0xff, 0)
    #endif

    #if defined(ZPL_IBM_VERSION_CHECK)
    #  undef ZPL_IBM_VERSION_CHECK
    #endif
    #if defined(ZPL_IBM_VERSION)
    #  define ZPL_IBM_VERSION_CHECK(major,minor,patch) (ZPL_IBM_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_IBM_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_VERSION)
    #  undef ZPL_TI_VERSION
    #endif
    #if \
        defined(__TI_COMPILER_VERSION__) && \
        ( \
          defined(__TMS470__) || defined(__TI_ARM__) || \
          defined(__MSP430__) || \
          defined(__TMS320C2000__) \
        )
    #  if (__TI_COMPILER_VERSION__ >= 16000000)
    #    define ZPL_TI_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #  endif
    #endif

    #if defined(ZPL_TI_VERSION_CHECK)
    #  undef ZPL_TI_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_VERSION)
    #  define ZPL_TI_VERSION_CHECK(major,minor,patch) (ZPL_TI_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_CL2000_VERSION)
    #  undef ZPL_TI_CL2000_VERSION
    #endif
    #if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C2000__)
    #  define ZPL_TI_CL2000_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #endif

    #if defined(ZPL_TI_CL2000_VERSION_CHECK)
    #  undef ZPL_TI_CL2000_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_CL2000_VERSION)
    #  define ZPL_TI_CL2000_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL2000_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_CL2000_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_CL430_VERSION)
    #  undef ZPL_TI_CL430_VERSION
    #endif
    #if defined(__TI_COMPILER_VERSION__) && defined(__MSP430__)
    #  define ZPL_TI_CL430_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #endif

    #if defined(ZPL_TI_CL430_VERSION_CHECK)
    #  undef ZPL_TI_CL430_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_CL430_VERSION)
    #  define ZPL_TI_CL430_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL430_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_CL430_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_ARMCL_VERSION)
    #  undef ZPL_TI_ARMCL_VERSION
    #endif
    #if defined(__TI_COMPILER_VERSION__) && (defined(__TMS470__) || defined(__TI_ARM__))
    #  define ZPL_TI_ARMCL_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #endif

    #if defined(ZPL_TI_ARMCL_VERSION_CHECK)
    #  undef ZPL_TI_ARMCL_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_ARMCL_VERSION)
    #  define ZPL_TI_ARMCL_VERSION_CHECK(major,minor,patch) (ZPL_TI_ARMCL_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_ARMCL_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_CL6X_VERSION)
    #  undef ZPL_TI_CL6X_VERSION
    #endif
    #if defined(__TI_COMPILER_VERSION__) && defined(__TMS320C6X__)
    #  define ZPL_TI_CL6X_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #endif

    #if defined(ZPL_TI_CL6X_VERSION_CHECK)
    #  undef ZPL_TI_CL6X_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_CL6X_VERSION)
    #  define ZPL_TI_CL6X_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL6X_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_CL6X_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_CL7X_VERSION)
    #  undef ZPL_TI_CL7X_VERSION
    #endif
    #if defined(__TI_COMPILER_VERSION__) && defined(__C7000__)
    #  define ZPL_TI_CL7X_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #endif

    #if defined(ZPL_TI_CL7X_VERSION_CHECK)
    #  undef ZPL_TI_CL7X_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_CL7X_VERSION)
    #  define ZPL_TI_CL7X_VERSION_CHECK(major,minor,patch) (ZPL_TI_CL7X_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_CL7X_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TI_CLPRU_VERSION)
    #  undef ZPL_TI_CLPRU_VERSION
    #endif
    #if defined(__TI_COMPILER_VERSION__) && defined(__PRU__)
    #  define ZPL_TI_CLPRU_VERSION ZPL_VERSION_ENCODE(__TI_COMPILER_VERSION__ / 1000000, (__TI_COMPILER_VERSION__ % 1000000) / 1000, (__TI_COMPILER_VERSION__ % 1000))
    #endif

    #if defined(ZPL_TI_CLPRU_VERSION_CHECK)
    #  undef ZPL_TI_CLPRU_VERSION_CHECK
    #endif
    #if defined(ZPL_TI_CLPRU_VERSION)
    #  define ZPL_TI_CLPRU_VERSION_CHECK(major,minor,patch) (ZPL_TI_CLPRU_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TI_CLPRU_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_CRAY_VERSION)
    #  undef ZPL_CRAY_VERSION
    #endif
    #if defined(_CRAYC)
    #  if defined(_RELEASE_PATCHLEVEL)
    #    define ZPL_CRAY_VERSION ZPL_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, _RELEASE_PATCHLEVEL)
    #  else
    #    define ZPL_CRAY_VERSION ZPL_VERSION_ENCODE(_RELEASE_MAJOR, _RELEASE_MINOR, 0)
    #  endif
    #endif

    #if defined(ZPL_CRAY_VERSION_CHECK)
    #  undef ZPL_CRAY_VERSION_CHECK
    #endif
    #if defined(ZPL_CRAY_VERSION)
    #  define ZPL_CRAY_VERSION_CHECK(major,minor,patch) (ZPL_CRAY_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_CRAY_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_IAR_VERSION)
    #  undef ZPL_IAR_VERSION
    #endif
    #if defined(__IAR_SYSTEMS_ICC__)
    #  if __VER__ > 1000
    #    define ZPL_IAR_VERSION ZPL_VERSION_ENCODE((__VER__ / 1000000), ((__VER__ / 1000) % 1000), (__VER__ % 1000))
    #  else
    #    define ZPL_IAR_VERSION ZPL_VERSION_ENCODE(VER / 100, __VER__ % 100, 0)
    #  endif
    #endif

    #if defined(ZPL_IAR_VERSION_CHECK)
    #  undef ZPL_IAR_VERSION_CHECK
    #endif
    #if defined(ZPL_IAR_VERSION)
    #  define ZPL_IAR_VERSION_CHECK(major,minor,patch) (ZPL_IAR_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_IAR_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_TINYC_VERSION)
    #  undef ZPL_TINYC_VERSION
    #endif
    #if defined(__TINYC__)
    #  define ZPL_TINYC_VERSION ZPL_VERSION_ENCODE(__TINYC__ / 1000, (__TINYC__ / 100) % 10, __TINYC__ % 100)
    #endif

    #if defined(ZPL_TINYC_VERSION_CHECK)
    #  undef ZPL_TINYC_VERSION_CHECK
    #endif
    #if defined(ZPL_TINYC_VERSION)
    #  define ZPL_TINYC_VERSION_CHECK(major,minor,patch) (ZPL_TINYC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_TINYC_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_DMC_VERSION)
    #  undef ZPL_DMC_VERSION
    #endif
    #if defined(__DMC__)
    #  define ZPL_DMC_VERSION ZPL_VERSION_ENCODE(__DMC__ >> 8, (__DMC__ >> 4) & 0xf, __DMC__ & 0xf)
    #endif

    #if defined(ZPL_DMC_VERSION_CHECK)
    #  undef ZPL_DMC_VERSION_CHECK
    #endif
    #if defined(ZPL_DMC_VERSION)
    #  define ZPL_DMC_VERSION_CHECK(major,minor,patch) (ZPL_DMC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_DMC_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_COMPCERT_VERSION)
    #  undef ZPL_COMPCERT_VERSION
    #endif
    #if defined(__COMPCERT_VERSION__)
    #  define ZPL_COMPCERT_VERSION ZPL_VERSION_ENCODE(__COMPCERT_VERSION__ / 10000, (__COMPCERT_VERSION__ / 100) % 100, __COMPCERT_VERSION__ % 100)
    #endif

    #if defined(ZPL_COMPCERT_VERSION_CHECK)
    #  undef ZPL_COMPCERT_VERSION_CHECK
    #endif
    #if defined(ZPL_COMPCERT_VERSION)
    #  define ZPL_COMPCERT_VERSION_CHECK(major,minor,patch) (ZPL_COMPCERT_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_COMPCERT_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_PELLES_VERSION)
    #  undef ZPL_PELLES_VERSION
    #endif
    #if defined(__POCC__)
    #  define ZPL_PELLES_VERSION ZPL_VERSION_ENCODE(__POCC__ / 100, __POCC__ % 100, 0)
    #endif

    #if defined(ZPL_PELLES_VERSION_CHECK)
    #  undef ZPL_PELLES_VERSION_CHECK
    #endif
    #if defined(ZPL_PELLES_VERSION)
    #  define ZPL_PELLES_VERSION_CHECK(major,minor,patch) (ZPL_PELLES_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_PELLES_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_GCC_VERSION)
    #  undef ZPL_GCC_VERSION
    #endif
    #if \
      defined(ZPL_GNUC_VERSION) && \
      !defined(__clang__) && \
      !defined(ZPL_INTEL_VERSION) && \
      !defined(ZPL_PGI_VERSION) && \
      !defined(ZPL_ARM_VERSION) && \
      !defined(ZPL_TI_VERSION) && \
      !defined(ZPL_TI_ARMCL_VERSION) && \
      !defined(ZPL_TI_CL430_VERSION) && \
      !defined(ZPL_TI_CL2000_VERSION) && \
      !defined(ZPL_TI_CL6X_VERSION) && \
      !defined(ZPL_TI_CL7X_VERSION) && \
      !defined(ZPL_TI_CLPRU_VERSION) && \
      !defined(__COMPCERT__)
    #  define ZPL_GCC_VERSION ZPL_GNUC_VERSION
    #endif

    #if defined(ZPL_GCC_VERSION_CHECK)
    #  undef ZPL_GCC_VERSION_CHECK
    #endif
    #if defined(ZPL_GCC_VERSION)
    #  define ZPL_GCC_VERSION_CHECK(major,minor,patch) (ZPL_GCC_VERSION >= ZPL_VERSION_ENCODE(major, minor, patch))
    #else
    #  define ZPL_GCC_VERSION_CHECK(major,minor,patch) (0)
    #endif

    #if defined(ZPL_HAS_ATTRIBUTE)
    #  undef ZPL_HAS_ATTRIBUTE
    #endif
    #if defined(__has_attribute)
    #  define ZPL_HAS_ATTRIBUTE(attribute) __has_attribute(attribute)
    #else
    #  define ZPL_HAS_ATTRIBUTE(attribute) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_ATTRIBUTE)
    #  undef ZPL_GNUC_HAS_ATTRIBUTE
    #endif
    #if defined(__has_attribute)
    #  define ZPL_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) __has_attribute(attribute)
    #else
    #  define ZPL_GNUC_HAS_ATTRIBUTE(attribute,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_ATTRIBUTE)
    #  undef ZPL_GCC_HAS_ATTRIBUTE
    #endif
    #if defined(__has_attribute)
    #  define ZPL_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) __has_attribute(attribute)
    #else
    #  define ZPL_GCC_HAS_ATTRIBUTE(attribute,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_HAS_CPP_ATTRIBUTE)
    #  undef ZPL_HAS_CPP_ATTRIBUTE
    #endif
    #if \
      defined(__has_cpp_attribute) && \
      defined(__cplusplus) && \
      (!defined(ZPL_SUNPRO_VERSION) || ZPL_SUNPRO_VERSION_CHECK(5,15,0))
    #  define ZPL_HAS_CPP_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
    #else
    #  define ZPL_HAS_CPP_ATTRIBUTE(attribute) (0)
    #endif

    #if defined(ZPL_HAS_CPP_ATTRIBUTE_NS)
    #  undef ZPL_HAS_CPP_ATTRIBUTE_NS
    #endif
    #if !defined(__cplusplus) || !defined(__has_cpp_attribute)
    #  define ZPL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
    #elif \
      !defined(ZPL_PGI_VERSION) && \
      !defined(ZPL_IAR_VERSION) && \
      (!defined(ZPL_SUNPRO_VERSION) || ZPL_SUNPRO_VERSION_CHECK(5,15,0)) && \
      (!defined(ZPL_MSVC_VERSION) || ZPL_MSVC_VERSION_CHECK(19,20,0))
    #  define ZPL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) ZPL_HAS_CPP_ATTRIBUTE(ns::attribute)
    #else
    #  define ZPL_HAS_CPP_ATTRIBUTE_NS(ns,attribute) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_CPP_ATTRIBUTE)
    #  undef ZPL_GNUC_HAS_CPP_ATTRIBUTE
    #endif
    #if defined(__has_cpp_attribute) && defined(__cplusplus)
    #  define ZPL_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
    #else
    #  define ZPL_GNUC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_CPP_ATTRIBUTE)
    #  undef ZPL_GCC_HAS_CPP_ATTRIBUTE
    #endif
    #if defined(__has_cpp_attribute) && defined(__cplusplus)
    #  define ZPL_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) __has_cpp_attribute(attribute)
    #else
    #  define ZPL_GCC_HAS_CPP_ATTRIBUTE(attribute,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_HAS_BUILTIN)
    #  undef ZPL_HAS_BUILTIN
    #endif
    #if defined(__has_builtin)
    #  define ZPL_HAS_BUILTIN(builtin) __has_builtin(builtin)
    #else
    #  define ZPL_HAS_BUILTIN(builtin) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_BUILTIN)
    #  undef ZPL_GNUC_HAS_BUILTIN
    #endif
    #if defined(__has_builtin)
    #  define ZPL_GNUC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
    #else
    #  define ZPL_GNUC_HAS_BUILTIN(builtin,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_BUILTIN)
    #  undef ZPL_GCC_HAS_BUILTIN
    #endif
    #if defined(__has_builtin)
    #  define ZPL_GCC_HAS_BUILTIN(builtin,major,minor,patch) __has_builtin(builtin)
    #else
    #  define ZPL_GCC_HAS_BUILTIN(builtin,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_HAS_FEATURE)
    #  undef ZPL_HAS_FEATURE
    #endif
    #if defined(__has_feature)
    #  define ZPL_HAS_FEATURE(feature) __has_feature(feature)
    #else
    #  define ZPL_HAS_FEATURE(feature) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_FEATURE)
    #  undef ZPL_GNUC_HAS_FEATURE
    #endif
    #if defined(__has_feature)
    #  define ZPL_GNUC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
    #else
    #  define ZPL_GNUC_HAS_FEATURE(feature,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_FEATURE)
    #  undef ZPL_GCC_HAS_FEATURE
    #endif
    #if defined(__has_feature)
    #  define ZPL_GCC_HAS_FEATURE(feature,major,minor,patch) __has_feature(feature)
    #else
    #  define ZPL_GCC_HAS_FEATURE(feature,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_HAS_EXTENSION)
    #  undef ZPL_HAS_EXTENSION
    #endif
    #if defined(__has_extension)
    #  define ZPL_HAS_EXTENSION(extension) __has_extension(extension)
    #else
    #  define ZPL_HAS_EXTENSION(extension) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_EXTENSION)
    #  undef ZPL_GNUC_HAS_EXTENSION
    #endif
    #if defined(__has_extension)
    #  define ZPL_GNUC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
    #else
    #  define ZPL_GNUC_HAS_EXTENSION(extension,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_EXTENSION)
    #  undef ZPL_GCC_HAS_EXTENSION
    #endif
    #if defined(__has_extension)
    #  define ZPL_GCC_HAS_EXTENSION(extension,major,minor,patch) __has_extension(extension)
    #else
    #  define ZPL_GCC_HAS_EXTENSION(extension,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_HAS_DECLSPEC_ATTRIBUTE)
    #  undef ZPL_HAS_DECLSPEC_ATTRIBUTE
    #endif
    #if defined(__has_declspec_attribute)
    #  define ZPL_HAS_DECLSPEC_ATTRIBUTE(attribute) __has_declspec_attribute(attribute)
    #else
    #  define ZPL_HAS_DECLSPEC_ATTRIBUTE(attribute) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE)
    #  undef ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE
    #endif
    #if defined(__has_declspec_attribute)
    #  define ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
    #else
    #  define ZPL_GNUC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE)
    #  undef ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE
    #endif
    #if defined(__has_declspec_attribute)
    #  define ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) __has_declspec_attribute(attribute)
    #else
    #  define ZPL_GCC_HAS_DECLSPEC_ATTRIBUTE(attribute,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_HAS_WARNING)
    #  undef ZPL_HAS_WARNING
    #endif
    #if defined(__has_warning)
    #  define ZPL_HAS_WARNING(warning) __has_warning(warning)
    #else
    #  define ZPL_HAS_WARNING(warning) (0)
    #endif

    #if defined(ZPL_GNUC_HAS_WARNING)
    #  undef ZPL_GNUC_HAS_WARNING
    #endif
    #if defined(__has_warning)
    #  define ZPL_GNUC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
    #else
    #  define ZPL_GNUC_HAS_WARNING(warning,major,minor,patch) ZPL_GNUC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_GCC_HAS_WARNING)
    #  undef ZPL_GCC_HAS_WARNING
    #endif
    #if defined(__has_warning)
    #  define ZPL_GCC_HAS_WARNING(warning,major,minor,patch) __has_warning(warning)
    #else
    #  define ZPL_GCC_HAS_WARNING(warning,major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    /* ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_ is for
       ZPL INTERNAL USE ONLY.  API subject to change without notice. */
    #if defined(ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
    #  undef ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_
    #endif
    #if defined(__cplusplus)
    #  if ZPL_HAS_WARNING("-Wc++98-compat")
    #    if ZPL_HAS_WARNING("-Wc++17-extensions")
    #      define ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
             ZPL_DIAGNOSTIC_PUSH \
             _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
             _Pragma("clang diagnostic ignored \"-Wc++17-extensions\"") \
             xpr \
             ZPL_DIAGNOSTIC_POP
    #    else
    #      define ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(xpr) \
             ZPL_DIAGNOSTIC_PUSH \
             _Pragma("clang diagnostic ignored \"-Wc++98-compat\"") \
             xpr \
             ZPL_DIAGNOSTIC_POP
    #    endif
    #  endif
    #endif
    #if !defined(ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_)
    #  define ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(x) x
    #endif

    #if defined(ZPL_CONST_CAST)
    #  undef ZPL_CONST_CAST
    #endif
    #if defined(__cplusplus)
    #  define ZPL_CONST_CAST(T, expr) (const_cast<T>(expr))
    #elif \
      ZPL_HAS_WARNING("-Wcast-qual") || \
      ZPL_GCC_VERSION_CHECK(4,6,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_CONST_CAST(T, expr) (__extension__ ({ \
          ZPL_DIAGNOSTIC_PUSH \
          ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL \
          ((T) (expr)); \
          ZPL_DIAGNOSTIC_POP \
        }))
    #else
    #  define ZPL_CONST_CAST(T, expr) ((T) (expr))
    #endif

    #if defined(ZPL_REINTERPRET_CAST)
    #  undef ZPL_REINTERPRET_CAST
    #endif
    #if defined(__cplusplus)
    #  define ZPL_REINTERPRET_CAST(T, expr) (reinterpret_cast<T>(expr))
    #else
    #  define ZPL_REINTERPRET_CAST(T, expr) ((T) (expr))
    #endif

    #if defined(ZPL_STATIC_CAST)
    #  undef ZPL_STATIC_CAST
    #endif
    #if defined(__cplusplus)
    #  define ZPL_STATIC_CAST(T, expr) (static_cast<T>(expr))
    #else
    #  define ZPL_STATIC_CAST(T, expr) ((T) (expr))
    #endif

    #if defined(ZPL_CPP_CAST)
    #  undef ZPL_CPP_CAST
    #endif
    #if defined(__cplusplus)
    #  if ZPL_HAS_WARNING("-Wold-style-cast")
    #    define ZPL_CPP_CAST(T, expr) \
           ZPL_DIAGNOSTIC_PUSH \
           _Pragma("clang diagnostic ignored \"-Wold-style-cast\"") \
           ((T) (expr)) \
           ZPL_DIAGNOSTIC_POP
    #  elif ZPL_IAR_VERSION_CHECK(8,3,0)
    #    define ZPL_CPP_CAST(T, expr) \
           ZPL_DIAGNOSTIC_PUSH \
           _Pragma("diag_suppress=Pe137") \
           ZPL_DIAGNOSTIC_POP \
    #  else
    #    define ZPL_CPP_CAST(T, expr) ((T) (expr))
    #  endif
    #else
    #  define ZPL_CPP_CAST(T, expr) (expr)
    #endif

    #if \
      (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
      defined(__clang__) || \
      ZPL_GCC_VERSION_CHECK(3,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_IAR_VERSION_CHECK(8,0,0) || \
      ZPL_PGI_VERSION_CHECK(18,4,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      ZPL_TI_ARMCL_VERSION_CHECK(4,7,0) || \
      ZPL_TI_CL430_VERSION_CHECK(2,0,1) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,1,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,0,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
      ZPL_CRAY_VERSION_CHECK(5,0,0) || \
      ZPL_TINYC_VERSION_CHECK(0,9,17) || \
      ZPL_SUNPRO_VERSION_CHECK(8,0,0) || \
      (ZPL_IBM_VERSION_CHECK(10,1,0) && defined(__C99_PRAGMA_OPERATOR))
    #  define ZPL_PRAGMA(value) _Pragma(#value)
    #elif ZPL_MSVC_VERSION_CHECK(15,0,0)
    #  define ZPL_PRAGMA(value) __pragma(value)
    #else
    #  define ZPL_PRAGMA(value)
    #endif

    #if defined(ZPL_DIAGNOSTIC_PUSH)
    #  undef ZPL_DIAGNOSTIC_PUSH
    #endif
    #if defined(ZPL_DIAGNOSTIC_POP)
    #  undef ZPL_DIAGNOSTIC_POP
    #endif
    #if defined(__clang__)
    #  define ZPL_DIAGNOSTIC_PUSH _Pragma("clang diagnostic push")
    #  define ZPL_DIAGNOSTIC_POP _Pragma("clang diagnostic pop")
    #elif ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_DIAGNOSTIC_PUSH _Pragma("warning(push)")
    #  define ZPL_DIAGNOSTIC_POP _Pragma("warning(pop)")
    #elif ZPL_GCC_VERSION_CHECK(4,6,0)
    #  define ZPL_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
    #  define ZPL_DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
    #elif ZPL_MSVC_VERSION_CHECK(15,0,0)
    #  define ZPL_DIAGNOSTIC_PUSH __pragma(warning(push))
    #  define ZPL_DIAGNOSTIC_POP __pragma(warning(pop))
    #elif ZPL_ARM_VERSION_CHECK(5,6,0)
    #  define ZPL_DIAGNOSTIC_PUSH _Pragma("push")
    #  define ZPL_DIAGNOSTIC_POP _Pragma("pop")
    #elif \
        ZPL_TI_VERSION_CHECK(15,12,0) || \
        ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
        ZPL_TI_CL430_VERSION_CHECK(4,4,0) || \
        ZPL_TI_CL6X_VERSION_CHECK(8,1,0) || \
        ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
        ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_DIAGNOSTIC_PUSH _Pragma("diag_push")
    #  define ZPL_DIAGNOSTIC_POP _Pragma("diag_pop")
    #elif ZPL_PELLES_VERSION_CHECK(2,90,0)
    #  define ZPL_DIAGNOSTIC_PUSH _Pragma("warning(push)")
    #  define ZPL_DIAGNOSTIC_POP _Pragma("warning(pop)")
    #else
    #  define ZPL_DIAGNOSTIC_PUSH
    #  define ZPL_DIAGNOSTIC_POP
    #endif

    #if defined(ZPL_DIAGNOSTIC_DISABLE_DEPRECATED)
    #  undef ZPL_DIAGNOSTIC_DISABLE_DEPRECATED
    #endif
    #if ZPL_HAS_WARNING("-Wdeprecated-declarations")
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("clang diagnostic ignored \"-Wdeprecated-declarations\"")
    #elif ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warning(disable:1478 1786)")
    #elif ZPL_PGI_VERSION_CHECK(17,10,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1215,1444")
    #elif ZPL_GCC_VERSION_CHECK(4,3,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
    #elif ZPL_MSVC_VERSION_CHECK(15,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED __pragma(warning(disable:4996))
    #elif \
        ZPL_TI_VERSION_CHECK(15,12,0) || \
        (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
        (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
        (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
        (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
        ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
        ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
        ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress 1291,1718")
    #elif ZPL_SUNPRO_VERSION_CHECK(5,13,0) && !defined(__cplusplus)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,E_DEPRECATED_ATT,E_DEPRECATED_ATT_MESS)")
    #elif ZPL_SUNPRO_VERSION_CHECK(5,13,0) && defined(__cplusplus)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("error_messages(off,symdeprecated,symdeprecated2)")
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("diag_suppress=Pe1444,Pe1215")
    #elif ZPL_PELLES_VERSION_CHECK(2,90,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED _Pragma("warn(disable:2241)")
    #else
    #  define ZPL_DIAGNOSTIC_DISABLE_DEPRECATED
    #endif

    #if defined(ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS)
    #  undef ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
    #endif
    #if ZPL_HAS_WARNING("-Wunknown-pragmas")
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("clang diagnostic ignored \"-Wunknown-pragmas\"")
    #elif ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("warning(disable:161)")
    #elif ZPL_PGI_VERSION_CHECK(17,10,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 1675")
    #elif ZPL_GCC_VERSION_CHECK(4,3,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("GCC diagnostic ignored \"-Wunknown-pragmas\"")
    #elif ZPL_MSVC_VERSION_CHECK(15,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS __pragma(warning(disable:4068))
    #elif \
        ZPL_TI_VERSION_CHECK(16,9,0) || \
        ZPL_TI_CL6X_VERSION_CHECK(8,0,0) || \
        ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
        ZPL_TI_CLPRU_VERSION_CHECK(2,3,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
    #elif ZPL_TI_CL6X_VERSION_CHECK(8,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress 163")
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS _Pragma("diag_suppress=Pe161")
    #else
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS
    #endif

    #if defined(ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES)
    #  undef ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
    #endif
    #if ZPL_HAS_WARNING("-Wunknown-attributes")
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("clang diagnostic ignored \"-Wunknown-attributes\"")
    #elif ZPL_GCC_VERSION_CHECK(4,6,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
    #elif ZPL_INTEL_VERSION_CHECK(17,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("warning(disable:1292)")
    #elif ZPL_MSVC_VERSION_CHECK(19,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES __pragma(warning(disable:5030))
    #elif ZPL_PGI_VERSION_CHECK(17,10,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1097")
    #elif ZPL_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("error_messages(off,attrskipunsup)")
    #elif \
        ZPL_TI_VERSION_CHECK(18,1,0) || \
        ZPL_TI_CL6X_VERSION_CHECK(8,3,0) || \
        ZPL_TI_CL7X_VERSION_CHECK(1,2,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress 1173")
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES _Pragma("diag_suppress=Pe1097")
    #else
    #  define ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_CPP_ATTRIBUTES
    #endif

    #if defined(ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL)
    #  undef ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL
    #endif
    #if ZPL_HAS_WARNING("-Wcast-qual")
    #  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("clang diagnostic ignored \"-Wcast-qual\"")
    #elif ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("warning(disable:2203 2331)")
    #elif ZPL_GCC_VERSION_CHECK(3,0,0)
    #  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL _Pragma("GCC diagnostic ignored \"-Wcast-qual\"")
    #else
    #  define ZPL_DIAGNOSTIC_DISABLE_CAST_QUAL
    #endif

    #if defined(ZPL_DEPRECATED)
    #  undef ZPL_DEPRECATED
    #endif
    #if defined(ZPL_DEPRECATED_FOR)
    #  undef ZPL_DEPRECATED_FOR
    #endif
    #if defined(__cplusplus) && (__cplusplus >= 201402L)
    #  define ZPL_DEPRECATED(since) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since)]])
    #  define ZPL_DEPRECATED_FOR(since, replacement) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[deprecated("Since " #since "; use " #replacement)]])
    #elif \
      ZPL_HAS_EXTENSION(attribute_deprecated_with_message) || \
      ZPL_GCC_VERSION_CHECK(4,5,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_ARM_VERSION_CHECK(5,6,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,13,0) || \
      ZPL_PGI_VERSION_CHECK(17,10,0) || \
      ZPL_TI_VERSION_CHECK(18,1,0) || \
      ZPL_TI_ARMCL_VERSION_CHECK(18,1,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(8,3,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,3,0)
    #  define ZPL_DEPRECATED(since) __attribute__((__deprecated__("Since " #since)))
    #  define ZPL_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__("Since " #since "; use " #replacement)))
    #elif \
      ZPL_HAS_ATTRIBUTE(deprecated) || \
      ZPL_GCC_VERSION_CHECK(3,1,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_DEPRECATED(since) __attribute__((__deprecated__))
    #  define ZPL_DEPRECATED_FOR(since, replacement) __attribute__((__deprecated__))
    #elif ZPL_MSVC_VERSION_CHECK(14,0,0)
    #  define ZPL_DEPRECATED(since) __declspec(deprecated("Since " # since))
    #  define ZPL_DEPRECATED_FOR(since, replacement) __declspec(deprecated("Since " #since "; use " #replacement))
    #elif \
      ZPL_MSVC_VERSION_CHECK(13,10,0) || \
      ZPL_PELLES_VERSION_CHECK(6,50,0)
    #  define ZPL_DEPRECATED(since) __declspec(deprecated)
    #  define ZPL_DEPRECATED_FOR(since, replacement) __declspec(deprecated)
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_DEPRECATED(since) _Pragma("deprecated")
    #  define ZPL_DEPRECATED_FOR(since, replacement) _Pragma("deprecated")
    #else
    #  define ZPL_DEPRECATED(since)
    #  define ZPL_DEPRECATED_FOR(since, replacement)
    #endif

    #if defined(ZPL_UNAVAILABLE)
    #  undef ZPL_UNAVAILABLE
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(warning) || \
      ZPL_GCC_VERSION_CHECK(4,3,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_UNAVAILABLE(available_since) __attribute__((__warning__("Not available until " #available_since)))
    #else
    #  define ZPL_UNAVAILABLE(available_since)
    #endif

    #if defined(ZPL_WARN_UNUSED_RESULT)
    #  undef ZPL_WARN_UNUSED_RESULT
    #endif
    #if defined(ZPL_WARN_UNUSED_RESULT_MSG)
    #  undef ZPL_WARN_UNUSED_RESULT_MSG
    #endif
    #if (ZPL_HAS_CPP_ATTRIBUTE(nodiscard) >= 201907L)
    #  define ZPL_WARN_UNUSED_RESULT ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
    #  define ZPL_WARN_UNUSED_RESULT_MSG(msg) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard(msg)]])
    #elif ZPL_HAS_CPP_ATTRIBUTE(nodiscard)
    #  define ZPL_WARN_UNUSED_RESULT ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
    #  define ZPL_WARN_UNUSED_RESULT_MSG(msg) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[nodiscard]])
    #elif \
      ZPL_HAS_ATTRIBUTE(warn_unused_result) || \
      ZPL_GCC_VERSION_CHECK(3,4,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
      (ZPL_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
      ZPL_PGI_VERSION_CHECK(17,10,0)
    #  define ZPL_WARN_UNUSED_RESULT __attribute__((__warn_unused_result__))
    #  define ZPL_WARN_UNUSED_RESULT_MSG(msg) __attribute__((__warn_unused_result__))
    #elif defined(_Check_return_) /* SAL */
    #  define ZPL_WARN_UNUSED_RESULT _Check_return_
    #  define ZPL_WARN_UNUSED_RESULT_MSG(msg) _Check_return_
    #else
    #  define ZPL_WARN_UNUSED_RESULT
    #  define ZPL_WARN_UNUSED_RESULT_MSG(msg)
    #endif

    #if defined(ZPL_SENTINEL)
    #  undef ZPL_SENTINEL
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(sentinel) || \
      ZPL_GCC_VERSION_CHECK(4,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_ARM_VERSION_CHECK(5,4,0)
    #  define ZPL_SENTINEL(position) __attribute__((__sentinel__(position)))
    #else
    #  define ZPL_SENTINEL(position)
    #endif

    #if defined(ZPL_NO_RETURN)
    #  undef ZPL_NO_RETURN
    #endif
    #if ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_NO_RETURN __noreturn
    #elif ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_NO_RETURN __attribute__((__noreturn__))
    #elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    #  define ZPL_NO_RETURN _Noreturn
    #elif defined(__cplusplus) && (__cplusplus >= 201103L)
    #  define ZPL_NO_RETURN ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[noreturn]])
    #elif \
      ZPL_HAS_ATTRIBUTE(noreturn) || \
      ZPL_GCC_VERSION_CHECK(3,2,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_NO_RETURN __attribute__((__noreturn__))
    #elif ZPL_SUNPRO_VERSION_CHECK(5,10,0)
    #  define ZPL_NO_RETURN _Pragma("does_not_return")
    #elif ZPL_MSVC_VERSION_CHECK(13,10,0)
    #  define ZPL_NO_RETURN __declspec(noreturn)
    #elif ZPL_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
    #  define ZPL_NO_RETURN _Pragma("FUNC_NEVER_RETURNS;")
    #elif ZPL_COMPCERT_VERSION_CHECK(3,2,0)
    #  define ZPL_NO_RETURN __attribute((noreturn))
    #elif ZPL_PELLES_VERSION_CHECK(9,0,0)
    #  define ZPL_NO_RETURN __declspec(noreturn)
    #else
    #  define ZPL_NO_RETURN
    #endif

    #if defined(ZPL_NO_ESCAPE)
    #  undef ZPL_NO_ESCAPE
    #endif
    #if ZPL_HAS_ATTRIBUTE(noescape)
    #  define ZPL_NO_ESCAPE __attribute__((__noescape__))
    #else
    #  define ZPL_NO_ESCAPE
    #endif

    #if defined(ZPL_UNREACHABLE)
    #  undef ZPL_UNREACHABLE
    #endif
    #if defined(ZPL_UNREACHABLE_RETURN)
    #  undef ZPL_UNREACHABLE_RETURN
    #endif
    #if defined(ZPL_ASSUME)
    #  undef ZPL_ASSUME
    #endif
    #if \
      ZPL_MSVC_VERSION_CHECK(13,10,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_ASSUME(expr) __assume(expr)
    #elif ZPL_HAS_BUILTIN(__builtin_assume)
    #  define ZPL_ASSUME(expr) __builtin_assume(expr)
    #elif \
        ZPL_TI_CL2000_VERSION_CHECK(6,2,0) || \
        ZPL_TI_CL6X_VERSION_CHECK(4,0,0)
    #  if defined(__cplusplus)
    #    define ZPL_ASSUME(expr) std::_nassert(expr)
    #  else
    #    define ZPL_ASSUME(expr) _nassert(expr)
    #  endif
    #endif
    #if \
      (ZPL_HAS_BUILTIN(__builtin_unreachable) && (!defined(ZPL_ARM_VERSION))) || \
      ZPL_GCC_VERSION_CHECK(4,5,0) || \
      ZPL_PGI_VERSION_CHECK(18,10,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_IBM_VERSION_CHECK(13,1,5)
    #  define ZPL_UNREACHABLE() __builtin_unreachable()
    #elif defined(ZPL_ASSUME)
    #  define ZPL_UNREACHABLE() ZPL_ASSUME(0)
    #endif
    #if !defined(ZPL_ASSUME)
    #  if defined(ZPL_UNREACHABLE)
    #    define ZPL_ASSUME(expr) ZPL_STATIC_CAST(void, ((expr) ? 1 : (ZPL_UNREACHABLE(), 1)))
    #  else
    #    define ZPL_ASSUME(expr) ZPL_STATIC_CAST(void, expr)
    #  endif
    #endif
    #if defined(ZPL_UNREACHABLE)
    #  if  \
          ZPL_TI_CL2000_VERSION_CHECK(6,2,0) || \
          ZPL_TI_CL6X_VERSION_CHECK(4,0,0)
    #    define ZPL_UNREACHABLE_RETURN(value) return (ZPL_STATIC_CAST(void, ZPL_ASSUME(0)), (value))
    #  else
    #    define ZPL_UNREACHABLE_RETURN(value) ZPL_UNREACHABLE()
    #  endif
    #else
    #  define ZPL_UNREACHABLE_RETURN(value) return (value)
    #endif
    #if !defined(ZPL_UNREACHABLE)
    #  define ZPL_UNREACHABLE() ZPL_ASSUME(0)
    #endif

    ZPL_DIAGNOSTIC_PUSH
    #if ZPL_HAS_WARNING("-Wpedantic")
    #  pragma clang diagnostic ignored "-Wpedantic"
    #endif
    #if ZPL_HAS_WARNING("-Wc++98-compat-pedantic") && defined(__cplusplus)
    #  pragma clang diagnostic ignored "-Wc++98-compat-pedantic"
    #endif
    #if ZPL_GCC_HAS_WARNING("-Wvariadic-macros",4,0,0)
    #  if defined(__clang__)
    #    pragma clang diagnostic ignored "-Wvariadic-macros"
    #  elif defined(ZPL_GCC_VERSION)
    #    pragma GCC diagnostic ignored "-Wvariadic-macros"
    #  endif
    #endif
    #if defined(ZPL_NON_NULL)
    #  undef ZPL_NON_NULL
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(nonnull) || \
      ZPL_GCC_VERSION_CHECK(3,3,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0)
    #  define ZPL_NON_NULL(...) __attribute__((__nonnull__(__VA_ARGS__)))
    #else
    #  define ZPL_NON_NULL(...)
    #endif
    ZPL_DIAGNOSTIC_POP

    #if defined(ZPL_PRINTF_FORMAT)
    #  undef ZPL_PRINTF_FORMAT
    #endif
    #if defined(__MINGW32__) && ZPL_GCC_HAS_ATTRIBUTE(format,4,4,0) && !defined(__USE_MINGW_ANSI_STDIO)
    #  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(ms_printf, string_idx, first_to_check)))
    #elif defined(__MINGW32__) && ZPL_GCC_HAS_ATTRIBUTE(format,4,4,0) && defined(__USE_MINGW_ANSI_STDIO)
    #  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(gnu_printf, string_idx, first_to_check)))
    #elif \
      ZPL_HAS_ATTRIBUTE(format) || \
      ZPL_GCC_VERSION_CHECK(3,1,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_ARM_VERSION_CHECK(5,6,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __attribute__((__format__(__printf__, string_idx, first_to_check)))
    #elif ZPL_PELLES_VERSION_CHECK(6,0,0)
    #  define ZPL_PRINTF_FORMAT(string_idx,first_to_check) __declspec(vaformat(printf,string_idx,first_to_check))
    #else
    #  define ZPL_PRINTF_FORMAT(string_idx,first_to_check)
    #endif

    #if defined(ZPL_CONSTEXPR)
    #  undef ZPL_CONSTEXPR
    #endif
    #if defined(__cplusplus)
    #  if __cplusplus >= 201103L
    #    define ZPL_CONSTEXPR ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(constexpr)
    #  endif
    #endif
    #if !defined(ZPL_CONSTEXPR)
    #  define ZPL_CONSTEXPR
    #endif

    #if defined(ZPL_PREDICT)
    #  undef ZPL_PREDICT
    #endif
    #if defined(ZPL_LIKELY)
    #  undef ZPL_LIKELY
    #endif
    #if defined(ZPL_UNLIKELY)
    #  undef ZPL_UNLIKELY
    #endif
    #if defined(ZPL_UNPREDICTABLE)
    #  undef ZPL_UNPREDICTABLE
    #endif
    #if ZPL_HAS_BUILTIN(__builtin_unpredictable)
    #  define ZPL_UNPREDICTABLE(expr) __builtin_unpredictable((expr))
    #endif
    #if \
      ZPL_HAS_BUILTIN(__builtin_expect_with_probability) || \
      ZPL_GCC_VERSION_CHECK(9,0,0)
    #  define ZPL_PREDICT(expr, value, probability) __builtin_expect_with_probability(  (expr), (value), (probability))
    #  define ZPL_PREDICT_TRUE(expr, probability)   __builtin_expect_with_probability(!!(expr),    1   , (probability))
    #  define ZPL_PREDICT_FALSE(expr, probability)  __builtin_expect_with_probability(!!(expr),    0   , (probability))
    #  define ZPL_LIKELY(expr)                      __builtin_expect                 (!!(expr),    1                  )
    #  define ZPL_UNLIKELY(expr)                    __builtin_expect                 (!!(expr),    0                  )
    #elif \
      ZPL_HAS_BUILTIN(__builtin_expect) || \
      ZPL_GCC_VERSION_CHECK(3,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      (ZPL_SUNPRO_VERSION_CHECK(5,15,0) && defined(__cplusplus)) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      ZPL_TI_ARMCL_VERSION_CHECK(4,7,0) || \
      ZPL_TI_CL430_VERSION_CHECK(3,1,0) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,1,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(6,1,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
      ZPL_TINYC_VERSION_CHECK(0,9,27) || \
      ZPL_CRAY_VERSION_CHECK(8,1,0)
    #  define ZPL_PREDICT(expr, expected, probability) \
         (((probability) >= 0.9) ? __builtin_expect((expr), (expected)) : (ZPL_STATIC_CAST(void, expected), (expr)))
    #  define ZPL_PREDICT_TRUE(expr, probability) \
         (__extension__ ({ \
           double zpl_probability_ = (probability); \
           ((zpl_probability_ >= 0.9) ? __builtin_expect(!!(expr), 1) : ((zpl_probability_ <= 0.1) ? __builtin_expect(!!(expr), 0) : !!(expr))); \
         }))
    #  define ZPL_PREDICT_FALSE(expr, probability) \
         (__extension__ ({ \
           double zpl_probability_ = (probability); \
           ((zpl_probability_ >= 0.9) ? __builtin_expect(!!(expr), 0) : ((zpl_probability_ <= 0.1) ? __builtin_expect(!!(expr), 1) : !!(expr))); \
         }))
    #  define ZPL_LIKELY(expr)   __builtin_expect(!!(expr), 1)
    #  define ZPL_UNLIKELY(expr) __builtin_expect(!!(expr), 0)
    #else
    #  define ZPL_PREDICT(expr, expected, probability) (ZPL_STATIC_CAST(void, expected), (expr))
    #  define ZPL_PREDICT_TRUE(expr, probability) (!!(expr))
    #  define ZPL_PREDICT_FALSE(expr, probability) (!!(expr))
    #  define ZPL_LIKELY(expr) (!!(expr))
    #  define ZPL_UNLIKELY(expr) (!!(expr))
    #endif
    #if !defined(ZPL_UNPREDICTABLE)
    #  define ZPL_UNPREDICTABLE(expr) ZPL_PREDICT(expr, 1, 0.5)
    #endif

    #if defined(ZPL_MALLOC)
    #  undef ZPL_MALLOC
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(malloc) || \
      ZPL_GCC_VERSION_CHECK(3,1,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(12,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_MALLOC __attribute__((__malloc__))
    #elif ZPL_SUNPRO_VERSION_CHECK(5,10,0)
    #  define ZPL_MALLOC _Pragma("returns_new_memory")
    #elif ZPL_MSVC_VERSION_CHECK(14, 0, 0)
    #  define ZPL_MALLOC __declspec(restrict)
    #else
    #  define ZPL_MALLOC
    #endif

    #if defined(ZPL_PURE)
    #  undef ZPL_PURE
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(pure) || \
      ZPL_GCC_VERSION_CHECK(2,96,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
      ZPL_PGI_VERSION_CHECK(17,10,0)
    #  define ZPL_PURE __attribute__((__pure__))
    #elif ZPL_SUNPRO_VERSION_CHECK(5,10,0)
    #  define ZPL_PURE _Pragma("does_not_write_global_data")
    #elif defined(__cplusplus) && \
        ( \
          ZPL_TI_CL430_VERSION_CHECK(2,0,1) || \
          ZPL_TI_CL6X_VERSION_CHECK(4,0,0) || \
          ZPL_TI_CL7X_VERSION_CHECK(1,2,0) \
        )
    #  define ZPL_PURE _Pragma("FUNC_IS_PURE;")
    #else
    #  define ZPL_PURE
    #endif

    #if defined(ZPL_CONST)
    #  undef ZPL_CONST
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(const) || \
      ZPL_GCC_VERSION_CHECK(2,5,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) || \
      ZPL_PGI_VERSION_CHECK(17,10,0)
    #  define ZPL_CONST __attribute__((__const__))
    #elif \
      ZPL_SUNPRO_VERSION_CHECK(5,10,0)
    #  define ZPL_CONST _Pragma("no_side_effect")
    #else
    #  define ZPL_CONST ZPL_PURE
    #endif

    #if defined(ZPL_RESTRICT)
    #  undef ZPL_RESTRICT
    #endif
    #if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && !defined(__cplusplus)
    #  define ZPL_RESTRICT restrict
    #elif \
      ZPL_GCC_VERSION_CHECK(3,1,0) || \
      ZPL_MSVC_VERSION_CHECK(14,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_PGI_VERSION_CHECK(17,10,0) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,2,4) || \
      ZPL_TI_CL6X_VERSION_CHECK(8,1,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      (ZPL_SUNPRO_VERSION_CHECK(5,14,0) && defined(__cplusplus)) || \
      ZPL_IAR_VERSION_CHECK(8,0,0) || \
      defined(__clang__)
    #  define ZPL_RESTRICT __restrict
    #elif ZPL_SUNPRO_VERSION_CHECK(5,3,0) && !defined(__cplusplus)
    #  define ZPL_RESTRICT _Restrict
    #else
    #  define ZPL_RESTRICT
    #endif

    #if defined(ZPL_INLINE)
    #  undef ZPL_INLINE
    #endif
    #if \
      (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)) || \
      (defined(__cplusplus) && (__cplusplus >= 199711L))
    #  define ZPL_INLINE inline
    #elif \
      defined(ZPL_GCC_VERSION) || \
      ZPL_ARM_VERSION_CHECK(6,2,0)
    #  define ZPL_INLINE __inline__
    #elif \
      ZPL_MSVC_VERSION_CHECK(12,0,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,1,0) || \
      ZPL_TI_CL430_VERSION_CHECK(3,1,0) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,2,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(8,0,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_INLINE __inline
    #else
    #  define ZPL_INLINE
    #endif

    #if defined(ZPL_ALWAYS_INLINE)
    #  undef ZPL_ALWAYS_INLINE
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(always_inline) || \
      ZPL_GCC_VERSION_CHECK(4,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_ALWAYS_INLINE __attribute__((__always_inline__)) ZPL_INLINE
    #elif ZPL_MSVC_VERSION_CHECK(12,0,0)
    #  define ZPL_ALWAYS_INLINE __forceinline
    #elif defined(__cplusplus) && \
        ( \
          ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
          ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
          ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
          ZPL_TI_CL6X_VERSION_CHECK(6,1,0) || \
          ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
          ZPL_TI_CLPRU_VERSION_CHECK(2,1,0) \
        )
    #  define ZPL_ALWAYS_INLINE _Pragma("FUNC_ALWAYS_INLINE;")
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_ALWAYS_INLINE _Pragma("inline=forced")
    #else
    #  define ZPL_ALWAYS_INLINE ZPL_INLINE
    #endif

    #if defined(ZPL_NEVER_INLINE)
    #  undef ZPL_NEVER_INLINE
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(noinline) || \
      ZPL_GCC_VERSION_CHECK(4,0,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(10,1,0) || \
      ZPL_TI_VERSION_CHECK(15,12,0) || \
      (ZPL_TI_ARMCL_VERSION_CHECK(4,8,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_ARMCL_VERSION_CHECK(5,2,0) || \
      (ZPL_TI_CL2000_VERSION_CHECK(6,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL2000_VERSION_CHECK(6,4,0) || \
      (ZPL_TI_CL430_VERSION_CHECK(4,0,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL430_VERSION_CHECK(4,3,0) || \
      (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
      ZPL_TI_CL6X_VERSION_CHECK(7,5,0) || \
      ZPL_TI_CL7X_VERSION_CHECK(1,2,0) || \
      ZPL_TI_CLPRU_VERSION_CHECK(2,1,0)
    #  define ZPL_NEVER_INLINE __attribute__((__noinline__))
    #elif ZPL_MSVC_VERSION_CHECK(13,10,0)
    #  define ZPL_NEVER_INLINE __declspec(noinline)
    #elif ZPL_PGI_VERSION_CHECK(10,2,0)
    #  define ZPL_NEVER_INLINE _Pragma("noinline")
    #elif ZPL_TI_CL6X_VERSION_CHECK(6,0,0) && defined(__cplusplus)
    #  define ZPL_NEVER_INLINE _Pragma("FUNC_CANNOT_INLINE;")
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_NEVER_INLINE _Pragma("inline=never")
    #elif ZPL_COMPCERT_VERSION_CHECK(3,2,0)
    #  define ZPL_NEVER_INLINE __attribute((noinline))
    #elif ZPL_PELLES_VERSION_CHECK(9,0,0)
    #  define ZPL_NEVER_INLINE __declspec(noinline)
    #else
    #  define ZPL_NEVER_INLINE
    #endif

    #if defined(ZPL_PRIVATE)
    #  undef ZPL_PRIVATE
    #endif
    #if defined(ZPL_PUBLIC)
    #  undef ZPL_PUBLIC
    #endif
    #if defined(ZPL_IMPORT)
    #  undef ZPL_IMPORT
    #endif
    #if defined(_WIN32) || defined(__CYGWIN__)
    #  define ZPL_PRIVATE
    #  define ZPL_PUBLIC   __declspec(dllexport)
    #  define ZPL_IMPORT   __declspec(dllimport)
    #else
    #  if \
        ZPL_HAS_ATTRIBUTE(visibility) || \
        ZPL_GCC_VERSION_CHECK(3,3,0) || \
        ZPL_SUNPRO_VERSION_CHECK(5,11,0) || \
        ZPL_INTEL_VERSION_CHECK(13,0,0) || \
        ZPL_ARM_VERSION_CHECK(4,1,0) || \
        ZPL_IBM_VERSION_CHECK(13,1,0) || \
        ( \
          defined(__TI_EABI__) && \
          ( \
            (ZPL_TI_CL6X_VERSION_CHECK(7,2,0) && defined(__TI_GNU_ATTRIBUTE_SUPPORT__)) || \
            ZPL_TI_CL6X_VERSION_CHECK(7,5,0) \
          ) \
        )
    #    define ZPL_PRIVATE __attribute__((__visibility__("hidden")))
    #    define ZPL_PUBLIC  __attribute__((__visibility__("default")))
    #  else
    #    define ZPL_PRIVATE
    #    define ZPL_PUBLIC
    #  endif
    #  define ZPL_IMPORT    extern
    #endif

    #if defined(ZPL_NO_THROW)
    #  undef ZPL_NO_THROW
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(nothrow) || \
      ZPL_GCC_VERSION_CHECK(3,3,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_NO_THROW __attribute__((__nothrow__))
    #elif \
      ZPL_MSVC_VERSION_CHECK(13,1,0) || \
      ZPL_ARM_VERSION_CHECK(4,1,0)
    #  define ZPL_NO_THROW __declspec(nothrow)
    #else
    #  define ZPL_NO_THROW
    #endif

    #if defined(ZPL_FALL_THROUGH)
    # undef ZPL_FALL_THROUGH
    #endif
    #if ZPL_GNUC_HAS_ATTRIBUTE(fallthrough,7,0,0) && !defined(ZPL_PGI_VERSION)
    #  define ZPL_FALL_THROUGH __attribute__((__fallthrough__))
    #elif ZPL_HAS_CPP_ATTRIBUTE_NS(clang,fallthrough)
    #  define ZPL_FALL_THROUGH ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[clang::fallthrough]])
    #elif ZPL_HAS_CPP_ATTRIBUTE(fallthrough)
    #  define ZPL_FALL_THROUGH ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_([[fallthrough]])
    #elif defined(__fallthrough) /* SAL */
    #  define ZPL_FALL_THROUGH __fallthrough
    #else
    #  define ZPL_FALL_THROUGH
    #endif

    #if defined(ZPL_RETURNS_NON_NULL)
    #  undef ZPL_RETURNS_NON_NULL
    #endif
    #if \
      ZPL_HAS_ATTRIBUTE(returns_nonnull) || \
      ZPL_GCC_VERSION_CHECK(4,9,0)
    #  define ZPL_RETURNS_NON_NULL __attribute__((__returns_nonnull__))
    #elif defined(_Ret_notnull_) /* SAL */
    #  define ZPL_RETURNS_NON_NULL _Ret_notnull_
    #else
    #  define ZPL_RETURNS_NON_NULL
    #endif

    #if defined(ZPL_ARRAY_PARAM)
    #  undef ZPL_ARRAY_PARAM
    #endif
    #if \
      defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L) && \
      !defined(__STDC_NO_VLA__) && \
      !defined(__cplusplus) && \
      !defined(ZPL_PGI_VERSION) && \
      !defined(ZPL_TINYC_VERSION)
    #  define ZPL_ARRAY_PARAM(name) (name)
    #else
    #  define ZPL_ARRAY_PARAM(name)
    #endif

    #if defined(ZPL_IS_CONSTANT)
    #  undef ZPL_IS_CONSTANT
    #endif
    #if defined(ZPL_REQUIRE_CONSTEXPR)
    #  undef ZPL_REQUIRE_CONSTEXPR
    #endif
    /* ZPL_IS_CONSTEXPR_ is for
       ZPL INTERNAL USE ONLY.  API subject to change without notice. */
    #if defined(ZPL_IS_CONSTEXPR_)
    #  undef ZPL_IS_CONSTEXPR_
    #endif
    #if \
      ZPL_HAS_BUILTIN(__builtin_constant_p) || \
      ZPL_GCC_VERSION_CHECK(3,4,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0) || \
      ZPL_TINYC_VERSION_CHECK(0,9,19) || \
      ZPL_ARM_VERSION_CHECK(4,1,0) || \
      ZPL_IBM_VERSION_CHECK(13,1,0) || \
      ZPL_TI_CL6X_VERSION_CHECK(6,1,0) || \
      (ZPL_SUNPRO_VERSION_CHECK(5,10,0) && !defined(__cplusplus)) || \
      ZPL_CRAY_VERSION_CHECK(8,1,0)
    #  define ZPL_IS_CONSTANT(expr) __builtin_constant_p(expr)
    #endif
    #if !defined(__cplusplus)
    #  if \
           ZPL_HAS_BUILTIN(__builtin_types_compatible_p) || \
           ZPL_GCC_VERSION_CHECK(3,4,0) || \
           ZPL_INTEL_VERSION_CHECK(13,0,0) || \
           ZPL_IBM_VERSION_CHECK(13,1,0) || \
           ZPL_CRAY_VERSION_CHECK(8,1,0) || \
           ZPL_ARM_VERSION_CHECK(5,4,0) || \
           ZPL_TINYC_VERSION_CHECK(0,9,24)
    #    if defined(__INTPTR_TYPE__)
    #      define ZPL_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0)), int*)
    #    else
    #      include <stdint.h>
    #      define ZPL_IS_CONSTEXPR_(expr) __builtin_types_compatible_p(__typeof__((1 ? (void*) ((intptr_t) ((expr) * 0)) : (int*) 0)), int*)
    #    endif
    #  elif \
           ( \
              defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L) && \
              !defined(ZPL_SUNPRO_VERSION) && \
              !defined(ZPL_PGI_VERSION) && \
              !defined(ZPL_IAR_VERSION)) || \
           ZPL_HAS_EXTENSION(c_generic_selections) || \
           ZPL_GCC_VERSION_CHECK(4,9,0) || \
           ZPL_INTEL_VERSION_CHECK(17,0,0) || \
           ZPL_IBM_VERSION_CHECK(12,1,0) || \
           ZPL_ARM_VERSION_CHECK(5,3,0)
    #    if defined(__INTPTR_TYPE__)
    #      define ZPL_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((__INTPTR_TYPE__) ((expr) * 0)) : (int*) 0), int*: 1, void*: 0)
    #    else
    #      include <stdint.h>
    #      define ZPL_IS_CONSTEXPR_(expr) _Generic((1 ? (void*) ((intptr_t) * 0) : (int*) 0), int*: 1, void*: 0)
    #    endif
    #  elif \
           defined(ZPL_GCC_VERSION) || \
           defined(ZPL_INTEL_VERSION) || \
           defined(ZPL_TINYC_VERSION) || \
           defined(ZPL_TI_ARMCL_VERSION) || \
           ZPL_TI_CL430_VERSION_CHECK(18,12,0) || \
           defined(ZPL_TI_CL2000_VERSION) || \
           defined(ZPL_TI_CL6X_VERSION) || \
           defined(ZPL_TI_CL7X_VERSION) || \
           defined(ZPL_TI_CLPRU_VERSION) || \
           defined(__clang__)
    #    define ZPL_IS_CONSTEXPR_(expr) ( \
             sizeof(void) != \
             sizeof(*( \
               1 ? \
                 ((void*) ((expr) * 0L) ) : \
                 ((struct { char v[sizeof(void) * 2]; } *) 1) \
               ) \
             ) \
           )
    #  endif
    #endif
    #if defined(ZPL_IS_CONSTEXPR_)
    #  if !defined(ZPL_IS_CONSTANT)
    #    define ZPL_IS_CONSTANT(expr) ZPL_IS_CONSTEXPR_(expr)
    #  endif
    #  define ZPL_REQUIRE_CONSTEXPR(expr) (ZPL_IS_CONSTEXPR_(expr) ? (expr) : (-1))
    #else
    #  if !defined(ZPL_IS_CONSTANT)
    #    define ZPL_IS_CONSTANT(expr) (0)
    #  endif
    #  define ZPL_REQUIRE_CONSTEXPR(expr) (expr)
    #endif

    #if defined(ZPL_BEGIN_C_DECLS)
    #  undef ZPL_BEGIN_C_DECLS
    #endif
    #if defined(ZPL_END_C_DECLS)
    #  undef ZPL_END_C_DECLS
    #endif
    #if defined(ZPL_C_DECL)
    #  undef ZPL_C_DECL
    #endif
    #if defined(__cplusplus)
    #  define ZPL_BEGIN_C_DECLS extern "C" {
    #  define ZPL_END_C_DECLS }
    #  define ZPL_C_DECL extern "C"
    #else
    #  define ZPL_BEGIN_C_DECLS
    #  define ZPL_END_C_DECLS
    #  define ZPL_C_DECL
    #endif

    #if defined(ZPL_STATIC_ASSERT)
    #  undef ZPL_STATIC_ASSERT
    #endif
    #if \
      !defined(__cplusplus) && ( \
          (defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)) || \
          ZPL_HAS_FEATURE(c_static_assert) || \
          ZPL_GCC_VERSION_CHECK(6,0,0) || \
          ZPL_INTEL_VERSION_CHECK(13,0,0) || \
          defined(_Static_assert) \
        )
    #  define ZPL_STATIC_ASSERT(expr, message) _Static_assert(expr, message)
    #elif \
      (defined(__cplusplus) && (__cplusplus >= 201103L)) || \
      ZPL_MSVC_VERSION_CHECK(16,0,0)
    #  define ZPL_STATIC_ASSERT(expr, message) ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(static_assert(expr, message))
    #else
      #define ZPL_STATIC_ASSERT3(cond, msg) typedef char static_assertion_##msg[(!!(cond)) * 2 - 1]
      #define ZPL_STATIC_ASSERT2(cond, line) ZPL_STATIC_ASSERT3(cond, static_assertion_at_line_##line)
      #define ZPL_STATIC_ASSERT1(cond, line) ZPL_STATIC_ASSERT2(cond, line)
      #define ZPL_STATIC_ASSERT(cond, unused) ZPL_STATIC_ASSERT1(cond, __LINE__)
    #endif

    #if defined(ZPL_NULL)
    #  undef ZPL_NULL
    #endif
    #if defined(__cplusplus)
    #  if __cplusplus >= 201103L
    #    define ZPL_NULL ZPL_DIAGNOSTIC_DISABLE_CPP98_COMPAT_WRAP_(nullptr)
    #  elif defined(NULL)
    #    define ZPL_NULL NULL
    #  else
    #    define ZPL_NULL ZPL_STATIC_CAST(void*, 0)
    #  endif
    #elif defined(NULL)
    #  define ZPL_NULL NULL
    #else
    #  define ZPL_NULL ((void*) 0)
    #endif

    #if defined(ZPL_MESSAGE)
    #  undef ZPL_MESSAGE
    #endif
    #if ZPL_HAS_WARNING("-Wunknown-pragmas")
    #  define ZPL_MESSAGE(msg) \
      ZPL_DIAGNOSTIC_PUSH \
      ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
      ZPL_PRAGMA(message msg) \
      ZPL_DIAGNOSTIC_POP
    #elif \
      ZPL_GCC_VERSION_CHECK(4,4,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_MESSAGE(msg) ZPL_PRAGMA(message msg)
    #elif ZPL_CRAY_VERSION_CHECK(5,0,0)
    #  define ZPL_MESSAGE(msg) ZPL_PRAGMA(_CRI message msg)
    #elif ZPL_IAR_VERSION_CHECK(8,0,0)
    #  define ZPL_MESSAGE(msg) ZPL_PRAGMA(message(msg))
    #elif ZPL_PELLES_VERSION_CHECK(2,0,0)
    #  define ZPL_MESSAGE(msg) ZPL_PRAGMA(message(msg))
    #else
    #  define ZPL_MESSAGE(msg)
    #endif

    #if defined(ZPL_WARNING)
    #  undef ZPL_WARNING
    #endif
    #if ZPL_HAS_WARNING("-Wunknown-pragmas")
    #  define ZPL_WARNING(msg) \
      ZPL_DIAGNOSTIC_PUSH \
      ZPL_DIAGNOSTIC_DISABLE_UNKNOWN_PRAGMAS \
      ZPL_PRAGMA(clang warning msg) \
      ZPL_DIAGNOSTIC_POP
    #elif \
      ZPL_GCC_VERSION_CHECK(4,8,0) || \
      ZPL_PGI_VERSION_CHECK(18,4,0) || \
      ZPL_INTEL_VERSION_CHECK(13,0,0)
    #  define ZPL_WARNING(msg) ZPL_PRAGMA(GCC warning msg)
    #elif ZPL_MSVC_VERSION_CHECK(15,0,0)
    #  define ZPL_WARNING(msg) ZPL_PRAGMA(message(msg))
    #else
    #  define ZPL_WARNING(msg) ZPL_MESSAGE(msg)
    #endif

    #if defined(ZPL_REQUIRE)
    #  undef ZPL_REQUIRE
    #endif
    #if defined(ZPL_REQUIRE_MSG)
    #  undef ZPL_REQUIRE_MSG
    #endif
    #if ZPL_HAS_ATTRIBUTE(diagnose_if)
    #  if ZPL_HAS_WARNING("-Wgcc-compat")
    #    define ZPL_REQUIRE(expr) \
           ZPL_DIAGNOSTIC_PUSH \
           _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
           __attribute__((diagnose_if(!(expr), #expr, "error"))) \
           ZPL_DIAGNOSTIC_POP
    #    define ZPL_REQUIRE_MSG(expr,msg) \
           ZPL_DIAGNOSTIC_PUSH \
           _Pragma("clang diagnostic ignored \"-Wgcc-compat\"") \
           __attribute__((diagnose_if(!(expr), msg, "error"))) \
           ZPL_DIAGNOSTIC_POP
    #  else
    #    define ZPL_REQUIRE(expr) __attribute__((diagnose_if(!(expr), #expr, "error")))
    #    define ZPL_REQUIRE_MSG(expr,msg) __attribute__((diagnose_if(!(expr), msg, "error")))
    #  endif
    #else
    #  define ZPL_REQUIRE(expr)
    #  define ZPL_REQUIRE_MSG(expr,msg)
    #endif

    #if defined(ZPL_FLAGS)
    #  undef ZPL_FLAGS
    #endif
    #if ZPL_HAS_ATTRIBUTE(flag_enum)
    #  define ZPL_FLAGS __attribute__((__flag_enum__))
    #endif

    #if defined(ZPL_FLAGS_CAST)
    #  undef ZPL_FLAGS_CAST
    #endif
    #if ZPL_INTEL_VERSION_CHECK(19,0,0)
    #  define ZPL_FLAGS_CAST(T, expr) (__extension__ ({ \
      ZPL_DIAGNOSTIC_PUSH \
          _Pragma("warning(disable:188)") \
          ((T) (expr)); \
          ZPL_DIAGNOSTIC_POP \
        }))
    #else
    #  define ZPL_FLAGS_CAST(T, expr) ZPL_STATIC_CAST(T, expr)
    #endif

    #if defined(ZPL_EMPTY_BASES)
    #  undef ZPL_EMPTY_BASES
    #endif
    #if ZPL_MSVC_VERSION_CHECK(19,0,23918) && !ZPL_MSVC_VERSION_CHECK(20,0,0)
    #  define ZPL_EMPTY_BASES __declspec(empty_bases)
    #else
    #  define ZPL_EMPTY_BASES
    #endif

    /* Remaining macros are deprecated. */

    #if defined(ZPL_GCC_NOT_CLANG_VERSION_CHECK)
    #  undef ZPL_GCC_NOT_CLANG_VERSION_CHECK
    #endif
    #if defined(__clang__)
    #  define ZPL_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) (0)
    #else
    #  define ZPL_GCC_NOT_CLANG_VERSION_CHECK(major,minor,patch) ZPL_GCC_VERSION_CHECK(major,minor,patch)
    #endif

    #if defined(ZPL_CLANG_HAS_ATTRIBUTE)
    #  undef ZPL_CLANG_HAS_ATTRIBUTE
    #endif
    #define ZPL_CLANG_HAS_ATTRIBUTE(attribute) ZPL_HAS_ATTRIBUTE(attribute)

    #if defined(ZPL_CLANG_HAS_CPP_ATTRIBUTE)
    #  undef ZPL_CLANG_HAS_CPP_ATTRIBUTE
    #endif
    #define ZPL_CLANG_HAS_CPP_ATTRIBUTE(attribute) ZPL_HAS_CPP_ATTRIBUTE(attribute)

    #if defined(ZPL_CLANG_HAS_BUILTIN)
    #  undef ZPL_CLANG_HAS_BUILTIN
    #endif
    #define ZPL_CLANG_HAS_BUILTIN(builtin) ZPL_HAS_BUILTIN(builtin)

    #if defined(ZPL_CLANG_HAS_FEATURE)
    #  undef ZPL_CLANG_HAS_FEATURE
    #endif
    #define ZPL_CLANG_HAS_FEATURE(feature) ZPL_HAS_FEATURE(feature)

    #if defined(ZPL_CLANG_HAS_EXTENSION)
    #  undef ZPL_CLANG_HAS_EXTENSION
    #endif
    #define ZPL_CLANG_HAS_EXTENSION(extension) ZPL_HAS_EXTENSION(extension)

    #if defined(ZPL_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE)
    #  undef ZPL_CLANG_HAS_DECLSPEC_DECLSPEC_ATTRIBUTE
    #endif
    #define ZPL_CLANG_HAS_DECLSPEC_ATTRIBUTE(attribute) ZPL_HAS_DECLSPEC_ATTRIBUTE(attribute)

    #if defined(ZPL_CLANG_HAS_WARNING)
    #  undef ZPL_CLANG_HAS_WARNING
    #endif
    #define ZPL_CLANG_HAS_WARNING(warning) ZPL_HAS_WARNING(warning)

    #endif /* !defined(ZPL_HEDLEY_VERSION) || (ZPL_HEDLEY_VERSION < X) */

    #define ZPL_VERSION ZPL_VERSION_ENCODE(ZPL_VERSION_MAJOR, ZPL_VERSION_MINOR, ZPL_VERSION_PATCH)

    #ifdef ZPL_IMPL
        #ifndef ZPL_IMPLEMENTATION
        #define ZPL_IMPLEMENTATION
        #endif
    #endif

    #if defined(__cplusplus) && !defined(ZPL_EXTERN)
        #define ZPL_EXTERN extern "C"
    #else
        #define ZPL_EXTERN extern
    #endif

    #ifndef ZPL_DEF
        #if defined(ZPL_SHARED_LIB)
            #ifdef ZPL_IMPLEMENTATION
                #define ZPL_DEF ZPL_PUBLIC
            #else
                #define ZPL_DEF ZPL_IMPORT
            #endif
        #elif defined(ZPL_STATIC_LIB)
            #ifdef ZPL_IMPLEMENTATION
                #define ZPL_DEF
            #else
                #define ZPL_DEF ZPL_EXTERN
            #endif
        #elif defined(ZPL_STATIC)
            #define ZPL_DEF static
        #else
            #define ZPL_DEF ZPL_EXTERN
        #endif
    #endif

    #ifndef ZPL_DEF_INLINE
        #if defined(ZPL_STATIC)
            #define ZPL_DEF_INLINE
            #define ZPL_IMPL_INLINE
        #else
            #define ZPL_DEF_INLINE ZPL_ALWAYS_INLINE
            #define ZPL_IMPL_INLINE ZPL_INLINE
        #endif
    #endif

    /* Distributions */
    #ifndef ZPL_CUSTOM_MODULES
        /* default distribution */
        #define ZPL_MODULE_CORE
        #define ZPL_MODULE_TIMER
        #define ZPL_MODULE_HASHING
        #define ZPL_MODULE_REGEX
        #define ZPL_MODULE_EVENT
        #define ZPL_MODULE_DLL
        #define ZPL_MODULE_OPTS
        #define ZPL_MODULE_PROCESS
        #define ZPL_MODULE_MATH
        #define ZPL_MODULE_JSON
        #define ZPL_MODULE_THREADING
        #define ZPL_MODULE_JOBS
        #define ZPL_MODULE_COROUTINES

        /* zpl nano distribution */
        #if defined(ZPL_NANO)
            #undef ZPL_MODULE_TIMER
            #undef ZPL_MODULE_HASHING
            #undef ZPL_MODULE_REGEX
            #undef ZPL_MODULE_EVENT
            #undef ZPL_MODULE_DLL
            #undef ZPL_MODULE_OPTS
            #undef ZPL_MODULE_PROCESS
            #undef ZPL_MODULE_MATH
            #undef ZPL_MODULE_JSON
            #undef ZPL_MODULE_THREADING
            #undef ZPL_MODULE_JOBS
            #undef ZPL_MODULE_COROUTINES
        #endif

        /* module enabling overrides */
        #if defined(ZPL_ENABLE_CORE) && !defined(ZPL_MODULE_CORE)
            #define ZPL_MODULE_CORE
        #endif
        #if defined(ZPL_ENABLE_TIMER) && !defined(ZPL_MODULE_TIMER)
            #define ZPL_MODULE_TIMER
        #endif
        #if defined(ZPL_ENABLE_HASHING) && !defined(ZPL_MODULE_HASHING)
            #define ZPL_MODULE_HASHING
        #endif
        #if defined(ZPL_ENABLE_REGEX) && !defined(ZPL_MODULE_REGEX)
            #define ZPL_MODULE_REGEX
        #endif
        #if defined(ZPL_ENABLE_EVENT) && !defined(ZPL_MODULE_EVENT)
            #define ZPL_MODULE_EVENT
        #endif
        #if defined(ZPL_ENABLE_DLL) && !defined(ZPL_MODULE_DLL)
            #define ZPL_MODULE_DLL
        #endif
        #if defined(ZPL_ENABLE_OPTS) && !defined(ZPL_MODULE_OPTS)
            #define ZPL_MODULE_OPTS
        #endif
        #if defined(ZPL_ENABLE_PROCESS) && !defined(ZPL_MODULE_PROCESS)
            #define ZPL_MODULE_PROCESS
        #endif
        #if defined(ZPL_ENABLE_MATH) && !defined(ZPL_MODULE_MATH)
            #define ZPL_MODULE_MATH
        #endif
        #if defined(ZPL_ENABLE_JSON) && !defined(ZPL_MODULE_JSON)
            #define ZPL_MODULE_JSON
        #endif
        #if defined(ZPL_ENABLE_THREADING) && !defined(ZPL_MODULE_THREADING)
            #define ZPL_MODULE_THREADING
        #endif
        #if defined(ZPL_ENABLE_JOBS) && !defined(ZPL_MODULE_JOBS)
            #ifndef ZPL_MODULE_THREADING
            #define ZPL_MODULE_THREADING /* dependency */
            #endif
            #define ZPL_MODULE_JOBS
        #endif
        #if defined(ZPL_ENABLE_COROUTINES) && !defined(ZPL_MODULE_COROUTINES)
            #ifndef ZPL_MODULE_THREADING
            #define ZPL_MODULE_THREADING /* dependency */
            #endif

            #ifndef ZPL_MODULE_JOBS
            #define ZPL_MODULE_JOBS /* dependency */
            #endif

            #define ZPL_MODULE_COROUTINES
        #endif

        /* module disabling overrides */
        #if defined(ZPL_DISABLE_CORE) && defined(ZPL_MODULE_CORE)
            #undef ZPL_MODULE_CORE
        #endif
        #if defined(ZPL_DISABLE_TIMER) && defined(ZPL_MODULE_TIMER)
            #undef ZPL_MODULE_TIMER
        #endif
        #if defined(ZPL_DISABLE_HASHING) && defined(ZPL_MODULE_HASHING)
            #undef ZPL_MODULE_HASHING
        #endif
        #if defined(ZPL_DISABLE_REGEX) && defined(ZPL_MODULE_REGEX)
            #undef ZPL_MODULE_REGEX
        #endif
        #if defined(ZPL_DISABLE_EVENT) && defined(ZPL_MODULE_EVENT)
            #undef ZPL_MODULE_EVENT
        #endif
        #if defined(ZPL_DISABLE_DLL) && defined(ZPL_MODULE_DLL)
            #undef ZPL_MODULE_DLL
        #endif
        #if defined(ZPL_DISABLE_OPTS) && defined(ZPL_MODULE_OPTS)
            #undef ZPL_MODULE_OPTS
        #endif
        #if defined(ZPL_DISABLE_PROCESS) && defined(ZPL_MODULE_PROCESS)
            #undef ZPL_MODULE_PROCESS
        #endif
        #if defined(ZPL_DISABLE_MATH) && defined(ZPL_MODULE_MATH)
            #undef ZPL_MODULE_MATH
        #endif
        #if defined(ZPL_DISABLE_JSON) && defined(ZPL_MODULE_JSON)
            #undef ZPL_MODULE_JSON
        #endif
        #if defined(ZPL_DISABLE_THREADING) && defined(ZPL_MODULE_THREADING)
            #ifdef ZPL_MODULE_JOBS
            #undef ZPL_MODULE_JOBS /* user */
            #endif

            #ifdef ZPL_MODULE_COROUTINES
            #undef ZPL_MODULE_COROUTINES /* user */
            #endif

            #undef ZPL_MODULE_THREADING
        #endif
        #if defined(ZPL_DISABLE_JOBS) && defined(ZPL_MODULE_JOBS)
            #ifdef ZPL_MODULE_COROUTINES
            #undef ZPL_MODULE_COROUTINES /* user */
            #endif

            #undef ZPL_MODULE_JOBS
        #endif
        #if defined(ZPL_DISABLE_COROUTINES) && defined(ZPL_MODULE_COROUTINES)
            #undef ZPL_MODULE_COROUTINES
        #endif
    #endif

    #if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wunused-function"
        #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
        #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
    #endif

    #if defined(_MSC_VER)
        #pragma warning(push)
        #pragma warning(disable : 4201)
        #pragma warning(disable : 4127) // Conditional expression is constant
    #endif

    /* general purpose includes */

    // file: header/core/system.h

    #ifdef ZPL_EDITOR
    #include <zpl.h>
    #endif

    ZPL_BEGIN_C_DECLS

    /* Platform architecture */

    #if defined(_WIN64) || defined(__x86_64__) || defined(_M_X64) || defined(__64BIT__) || defined(__powerpc64__) ||       \
    defined(__ppc64__) || defined(__aarch64__)
        #ifndef ZPL_ARCH_64_BIT
            #define ZPL_ARCH_64_BIT 1
        #endif
    #else
        #ifndef ZPL_ARCH_32_BIT
            #define ZPL_ARCH_32_BIT 1
        #endif
    #endif

    /* Platform endiannes */

    #ifndef ZPL_ENDIAN_ORDER
        #define ZPL_ENDIAN_ORDER
        #define ZPL_IS_BIG_ENDIAN (!*(zpl_u8 *)&(zpl_u16){ 1 })
        #define ZPL_IS_LITTLE_ENDIAN (!ZPL_IS_BIG_ENDIAN)
    #endif

    /* Platform OS */

    #if defined(_WIN32) || defined(_WIN64)
        #ifndef ZPL_SYSTEM_WINDOWS
            #define ZPL_SYSTEM_WINDOWS 1
        #endif
    #elif defined(__APPLE__) && defined(__MACH__)
        #ifndef ZPL_SYSTEM_OSX
            #define ZPL_SYSTEM_OSX 1
        #endif
        #ifndef ZPL_SYSTEM_MACOS
            #define ZPL_SYSTEM_MACOS 1
        #endif
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR == 1 || TARGET_OS_IPHONE == 1
            #ifndef ZPL_SYSTEM_IOS
                #define ZPL_SYSTEM_IOS 1
            #endif
        #endif
    #elif defined(__unix__)
        #ifndef ZPL_SYSTEM_UNIX
            #define ZPL_SYSTEM_UNIX 1
        #endif
        #if defined(ANDROID) || defined(__ANDROID__)
            #ifndef ZPL_SYSTEM_ANDROID
                #define ZPL_SYSTEM_ANDROID 1
            #endif
            #ifndef ZPL_SYSTEM_LINUX
                #define ZPL_SYSTEM_LINUX 1
            #endif
        #elif defined(__linux__)
        #ifndef ZPL_SYSTEM_LINUX
            #define ZPL_SYSTEM_LINUX 1
        #endif
        #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
            #ifndef ZPL_SYSTEM_FREEBSD
                #define ZPL_SYSTEM_FREEBSD 1
            #endif
        #elif defined(__OpenBSD__)
            #ifndef ZPL_SYSTEM_OPENBSD
                #define ZPL_SYSTEM_OPENBSD 1
            #endif
        #elif defined(__EMSCRIPTEN__)
            #ifndef ZPL_SYSTEM_EMSCRIPTEN
                #define ZPL_SYSTEM_EMSCRIPTEN 1
            #endif
        #elif defined(__CYGWIN__)
            #ifndef ZPL_SYSTEM_CYGWIN
                #define ZPL_SYSTEM_CYGWIN 1
            #endif
        #else
            #error This UNIX operating system is not supported
        #endif
    #else
        #error This operating system is not supported
    #endif

    /* Platform compiler */

    #if defined(_MSC_VER)
        #define ZPL_COMPILER_MSVC 1
    #elif defined(__GNUC__)
        #define ZPL_COMPILER_GCC 1
    #elif defined(__clang__)
        #define ZPL_COMPILER_CLANG 1
    #elif defined(__MINGW32__)
        #define ZPL_COMPILER_MINGW 1
    #else
        #error Unknown compiler
    #endif

    /* Platform CPU */

    #if defined(__arm__) || defined(__aarch64__)
        #ifndef ZPL_CPU_ARM
            #define ZPL_CPU_ARM 1
        #endif
        #ifndef ZPL_CACHE_LINE_SIZE
            #define ZPL_CACHE_LINE_SIZE 64
        #endif
    #elif defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__x86_64__) || defined(ZPL_SYSTEM_EMSCRIPTEN)
        #ifndef ZPL_CPU_X86
            #define ZPL_CPU_X86 1
        #endif
        #ifndef ZPL_CACHE_LINE_SIZE
            #define ZPL_CACHE_LINE_SIZE 64
        #endif
    #elif defined(_M_PPC) || defined(__powerpc__) || defined(__powerpc64__)
        #ifndef ZPL_CPU_PPC
            #define ZPL_CPU_PPC 1
        #endif
        #ifndef ZPL_CACHE_LINE_SIZE
            #define ZPL_CACHE_LINE_SIZE 128
        #endif
    #elif defined(__MIPSEL__) || defined(__mips_isa_rev)
        #ifndef ZPL_CPU_MIPS
            #define ZPL_CPU_MIPS 1
        #endif
        #ifndef ZPL_CACHE_LINE_SIZE
            #define ZPL_CACHE_LINE_SIZE 64
        #endif
    #else
        #error Unknown CPU Type
    #endif

    // TODO(ZaKlaus): Find a better way to get this flag in MinGW.
    #if defined(ZPL_COMPILER_GCC) && !defined(WC_ERR_INVALID_CHARS)
        #define WC_ERR_INVALID_CHARS 0x0080
    #endif

    #if defined(ZPL_COMPILER_GCC) && defined(ZPL_SYSTEM_WINDOWS)
        #ifndef ZPL_COMPILER_MINGW
        #define ZPL_COMPILER_MINGW // assume we use mingw as a compiler
        #endif
    #endif

    #if defined(ZPL_SYSTEM_UNIX)
        #ifndef _GNU_SOURCE
        #define _GNU_SOURCE
        #endif

        #ifndef _LARGEFILE64_SOURCE
        #define _LARGEFILE64_SOURCE
        #endif
    #endif

    ZPL_END_C_DECLS

    #include <stdarg.h>
    #include <stddef.h>

    #if defined(ZPL_SYSTEM_WINDOWS)
        #include <intrin.h>
    #endif

    // file: header/core/types.h

    #ifdef ZPL_EDITOR
    #include <zpl.h>
    #endif

    ZPL_BEGIN_C_DECLS

    /* Basic types */

    #if defined(ZPL_COMPILER_MSVC)
        #if _MSC_VER < 1300
            typedef unsigned char zpl_u8;
            typedef signed char zpl_i8;
            typedef unsigned short zpl_u16;
            typedef signed short zpl_i16;
            typedef unsigned int zpl_u32;
            typedef signed int zpl_i32;
        #else
            typedef unsigned __int8 zpl_u8;
            typedef signed __int8 zpl_i8;
            typedef unsigned __int16 zpl_u16;
            typedef signed __int16 zpl_i16;
            typedef unsigned __int32 zpl_u32;
            typedef signed __int32 zpl_i32;
        #endif
        typedef unsigned __int64 zpl_u64;
        typedef signed __int64 zpl_i64;
    #else
        #include <stdint.h>

        typedef uint8_t zpl_u8;
        typedef int8_t zpl_i8;
        typedef uint16_t zpl_u16;
        typedef int16_t zpl_i16;
        typedef uint32_t zpl_u32;
        typedef int32_t zpl_i32;
        typedef uint64_t zpl_u64;
        typedef int64_t zpl_i64;
    #endif

    ZPL_STATIC_ASSERT(sizeof(zpl_u8) == sizeof(zpl_i8), "sizeof(zpl_u8) != sizeof(zpl_i8)");
    ZPL_STATIC_ASSERT(sizeof(zpl_u16) == sizeof(zpl_i16), "sizeof(zpl_u16) != sizeof(zpl_i16)");
    ZPL_STATIC_ASSERT(sizeof(zpl_u32) == sizeof(zpl_i32), "sizeof(zpl_u32) != sizeof(zpl_i32)");
    ZPL_STATIC_ASSERT(sizeof(zpl_u64) == sizeof(zpl_i64), "sizeof(zpl_u64) != sizeof(zpl_i64)");

    ZPL_STATIC_ASSERT(sizeof(zpl_u8) == 1, "sizeof(zpl_u8) != 1");
    ZPL_STATIC_ASSERT(sizeof(zpl_u16) == 2, "sizeof(zpl_u16) != 2");
    ZPL_STATIC_ASSERT(sizeof(zpl_u32) == 4, "sizeof(zpl_u32) != 4");
    ZPL_STATIC_ASSERT(sizeof(zpl_u64) == 8, "sizeof(zpl_u64) != 8");

    typedef size_t zpl_usize;
    typedef ptrdiff_t zpl_isize;

    ZPL_STATIC_ASSERT(sizeof(zpl_usize) == sizeof(zpl_isize), "sizeof(zpl_usize) != sizeof(zpl_isize)");

    // NOTE: (u)zpl_intptr is only here for semantic reasons really as this library will only support 32/64 bit OSes.
    #if defined(_WIN64)
        typedef signed __int64 zpl_intptr;
        typedef unsigned __int64 zpl_uintptr;
    #elif defined(_WIN32)
        // NOTE; To mark types changing their size, e.g. zpl_intptr
        #ifndef _W64
            #if !defined(__midl) && (defined(_X86_) || defined(_M_IX86)) && _MSC_VER >= 1300
                #define _W64 __w64
            #else
                #define _W64
            #endif
        #endif
        typedef _W64 signed int zpl_intptr;
        typedef _W64 unsigned int zpl_uintptr;
    #else
        typedef uintptr_t zpl_uintptr;
        typedef intptr_t zpl_intptr;
    #endif

    ZPL_STATIC_ASSERT(sizeof(zpl_uintptr) == sizeof(zpl_intptr), "sizeof(zpl_uintptr) != sizeof(zpl_intptr)");

    typedef float zpl_f32;
    typedef double zpl_f64;

    ZPL_STATIC_ASSERT(sizeof(zpl_f32) == 4, "sizeof(zpl_f32) != 4");
    ZPL_STATIC_ASSERT(sizeof(zpl_f64) == 8, "sizeof(zpl_f64) != 8");

    typedef zpl_i32 zpl_rune; // NOTE: Unicode codepoint
    typedef zpl_i32 zpl_char32;
    #define ZPL_RUNE_INVALID cast(zpl_rune)(0xfffd)
    #define ZPL_RUNE_MAX cast(zpl_rune)(0x0010ffff)
    #define ZPL_RUNE_BOM cast(zpl_rune)(0xfeff)
    #define ZPL_RUNE_EOF cast(zpl_rune)(-1)

    typedef zpl_i8 zpl_b8;
    typedef zpl_i16 zpl_b16;
    typedef zpl_i32 zpl_b32;

    #if !defined(__cplusplus)
        #if (defined(_MSC_VER) && _MSC_VER < 1800) || (!defined(_MSC_VER) && !defined(__STDC_VERSION__))
            #ifndef true
                #define true(0 == 0)
            #endif
            #ifndef false
                #define false(0 != 0)
            #endif

            typedef zpl_b8 bool;
        #else
            #include <stdbool.h>
        #endif
    #endif

    #if __cplusplus > 199711L
    #define register      // Deprecated in C++11.
    #endif  // #if __cplusplus > 199711L

    #ifndef ZPL_U8_MIN
        #define ZPL_U8_MIN 0u
        #define ZPL_U8_MAX 0xffu
        #define ZPL_I8_MIN (-0x7f - 1)
        #define ZPL_I8_MAX 0x7f

        #define ZPL_U16_MIN 0u
        #define ZPL_U16_MAX 0xffffu
        #define ZPL_I16_MIN (-0x7fff - 1)
        #define ZPL_I16_MAX 0x7fff

        #define ZPL_U32_MIN 0u
        #define ZPL_U32_MAX 0xffffffffu
        #define ZPL_I32_MIN (-0x7fffffff - 1)
        #define ZPL_I32_MAX 0x7fffffff

        #define ZPL_U64_MIN 0ull
        #define ZPL_U64_MAX 0xffffffffffffffffull
        #define ZPL_I64_MIN (-0x7fffffffffffffffll - 1)
        #define ZPL_I64_MAX 0x7fffffffffffffffll

        #if defined(ZPL_ARCH_32_BIT)
            #define ZPL_USIZE_MIN ZPL_U32_MIN
            #define ZPL_USIZE_MAX ZPL_U32_MAX
            #define ZPL_ISIZE_MIN ZPL_S32_MIN
        #define ZPL_ISIZE_MAX ZPL_S32_MAX
            #elif defined(ZPL_ARCH_64_BIT)
            #define ZPL_USIZE_MIN ZPL_U64_MIN
            #define ZPL_USIZE_MAX ZPL_U64_MAX
            #define ZPL_ISIZE_MIN ZPL_I64_MIN
            #define ZPL_ISIZE_MAX ZPL_I64_MAX
        #else
            #error Unknown architecture size. This library only supports 32 bit and 64 bit architectures.
        #endif

        #define ZPL_F32_MIN 1.17549435e-38f
        #define ZPL_F32_MAX 3.40282347e+38f

        #define ZPL_F64_MIN 2.2250738585072014e-308
        #define ZPL_F64_MAX 1.7976931348623157e+308
    #endif

    #ifdef ZPL_DEFINE_NULL_MACRO
        #ifndef NULL
            #define NULL ZPL_NULL
        #endif
    #endif

    ZPL_END_C_DECLS
    // file: header/core/helpers.h

    /* Various macro based helpers */
    #ifdef ZPL_EDITOR
    #include <zpl.h>
    #endif

    ZPL_BEGIN_C_DECLS

    #ifndef cast
        #define cast(Type) (Type)
    #endif

    #ifndef zpl_size_of
        #define zpl_size_of(x) (zpl_isize)(sizeof(x))
    #endif

    #ifndef zpl_count_of
        #define zpl_count_of(x) ((zpl_size_of(x) / zpl_size_of(0 [x])) / ((zpl_isize)(!(zpl_size_of(x) % zpl_size_of(0 [x])))))
    #endif

    #ifndef zpl_offset_of
    #ifdef _MSC_VER
        #define zpl_offset_of(Type, element) ((zpl_isize) & (((Type *)0)->element))
    #else
        #define zpl_offset_of(Type, element) __builtin_offsetof(Type, element)
    #endif
    #endif

    #if defined(__cplusplus)
        #ifndef zpl_align_of
            #if __cplusplus >= 201103L
                #define zpl_align_of(Type) (zpl_isize)alignof(Type)
            #else
                extern "C++" {
                    template <typename T> struct zpl_alignment_trick {
                        char c;
                        T member;
                    };
                }
                #define zpl_align_of(Type) zpl_offset_of(zpl_alignment_trick<Type>, member)
            #endif
        #endif
    #else
        #ifndef zpl_align_of
            #define zpl_align_of(Type) \
            zpl_offset_of(             \
            struct {                   \
                char c;                \
                Type member;           \
            },                         \
            member)
        #endif
    #endif

    #ifndef zpl_swap
        #define zpl_swap(Type, a, b) \
        do {                         \
            Type tmp = (a);          \
            (a) = (b);               \
            (b) = tmp;               \
        } while (0)
    #endif



    #ifndef zpl_global
        #define zpl_global static        // Global variables
    #endif

    #ifndef zpl_internal
        #define zpl_internal static      // Internal linkage
    #endif

    #ifndef zpl_local_persist
        #define zpl_local_persist static // Local Persisting variables
    #endif

    #ifndef zpl_unused
        #if defined(_MSC_VER)
            #define zpl_unused(x) (__pragma(warning(suppress : 4100))(x))
        #elif defined(__GCC__)
            #define zpl_unused(x) __attribute__((__unused__))(x)
        #else
            #define zpl_unused(x) ((void)(zpl_size_of(x)))
        #endif
    #endif


    #ifndef ZPL_JOIN_MACROS
        #define ZPL_JOIN_MACROS

        #define ZPL_JOIN2 ZPL_CONCAT
        #define ZPL_JOIN3(a, b, c) ZPL_JOIN2(ZPL_JOIN2(a, b), c)
        #define ZPL_JOIN4(a, b, c, d) ZPL_JOIN2(ZPL_JOIN2(ZPL_JOIN2(a, b), c), d)
    #endif

    #ifndef ZPL_BIT
        #define ZPL_BIT(x) (1 << (x))
    #endif

    #ifndef zpl_min
        #define zpl_min(a, b) ((a) < (b) ? (a) : (b))
    #endif

    #ifndef zpl_max
        #define zpl_max(a, b) ((a) > (b) ? (a) : (b))
    #endif

    #ifndef zpl_min3
        #define zpl_min3(a, b, c) zpl_min(zpl_min(a, b), c)
    #endif

    #ifndef zpl_max3
        #define zpl_max3(a, b, c) zpl_max(zpl_max(a, b), c)
    #endif

    #ifndef zpl_clamp
        #define zpl_clamp(x, lower, upper) zpl_min(zpl_max((x), (lower)), (upper))
    #endif

    #ifndef zpl_clamp01
        #define zpl_clamp01(x) zpl_clamp((x), 0, 1)
    #endif

    #ifndef zpl_is_between
        #define zpl_is_between(x, lower, upper) (((lower) <= (x)) && ((x) <= (upper)))
    #endif

    #ifndef zpl_abs
        #define zpl_abs(x) ((x) < 0 ? -(x) : (x))
    #endif

    #ifndef hard_cast
        #define hard_cast(type) *cast(type) &
    #endif

    // WARN(ZaKlaus): Supported only on GCC via GNU extensions!!!
    #ifndef zpl_lambda
        #define zpl_lambda(b_) ({ b_ _; })
    #endif

    #ifndef zpl_when
        #define zpl_when(init, type, name) \
        type name = init;                  \
        if (name)
    #endif

    /* NOTE: Very useful bit setting */
    #ifndef ZPL_MASK_SET
        #define ZPL_MASK_SET(var, set, mask) \
        do {                                 \
            if (set)                         \
            (var) |= (mask);                 \
            else                             \
            (var) &= ~(mask);                \
        } while (0)
    #endif

    // Multiline string literals in C99!
    #ifndef ZPL_MULTILINE
        #define ZPL_MULTILINE(...) #__VA_ARGS__
    #endif

    ZPL_END_C_DECLS

    #if defined(ZPL_MODULE_CORE)
        // file: header/core/debug.h

        /* Debugging stuff */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #ifndef ZPL_DEBUG_TRAP
            #if defined(_MSC_VER)
                #if _MSC_VER < 1300
                    #define ZPL_DEBUG_TRAP( ) __asm int 3 /* Trap to debugger! */
                #else
                    #define ZPL_DEBUG_TRAP( ) __debugbreak( )
                #endif
            #else
                #define ZPL_DEBUG_TRAP( ) __builtin_trap( )
            #endif
        #endif

        #ifndef ZPL_ASSERT_MSG
            #define ZPL_ASSERT_MSG(cond, msg, ...)                                                                             \
            do {                                                                                                               \
                if (!(cond)) {                                                                                                 \
                    zpl_assert_handler(#cond, __FILE__, cast(zpl_i64) __LINE__, msg, ##__VA_ARGS__);                           \
                    ZPL_DEBUG_TRAP( );                                                                                         \
                }                                                                                                              \
            } while (0)
        #endif

        #ifndef ZPL_ASSERT
            #define ZPL_ASSERT(cond) ZPL_ASSERT_MSG(cond, NULL)
        #endif

        #ifndef ZPL_ASSERT_NOT_NULL
            #define ZPL_ASSERT_NOT_NULL(ptr) ZPL_ASSERT_MSG((ptr) != NULL, #ptr " must not be NULL")
        #endif

        // NOTE: Things that shouldn't happen with a message!
        #ifndef ZPL_PANIC
            #define ZPL_PANIC(msg, ...) ZPL_ASSERT_MSG(0, msg, ##__VA_ARGS__)
        #endif

        #ifndef ZPL_NOT_IMPLEMENTED
            #define ZPL_NOT_IMPLEMENTED ZPL_PANIC("not implemented")
        #endif

        /* Functions */

        ZPL_DEF void    zpl_assert_handler(char const *condition, char const *file, zpl_i32 line, char const *msg, ...);
        ZPL_DEF zpl_i32 zpl_assert_crash(char const *condition);

        ZPL_END_C_DECLS
        // file: header/core/memory.h

        /** @file mem.c
        @brief Memory manipulation and helpers.
        @defgroup memman Memory management

         Consists of pointer arithmetic methods, virtual memory management and custom memory allocators.

         @{
         */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        //! Checks if value is power of 2.
        ZPL_DEF_INLINE zpl_b32 zpl_is_power_of_two(zpl_isize x);

        //! Aligns address to specified alignment.
        ZPL_DEF_INLINE void *zpl_align_forward(void *ptr, zpl_isize alignment);

        //! Moves pointer forward by bytes.
        ZPL_DEF_INLINE void *zpl_pointer_add(void *ptr, zpl_isize bytes);

        //! Moves pointer backward by bytes.
        ZPL_DEF_INLINE void *zpl_pointer_sub(void *ptr, zpl_isize bytes);

        //! Moves pointer forward by bytes.
        ZPL_DEF_INLINE void const *zpl_pointer_add_const(void const *ptr, zpl_isize bytes);

        //! Moves pointer backward by bytes.
        ZPL_DEF_INLINE void const *zpl_pointer_sub_const(void const *ptr, zpl_isize bytes);

        //! Calculates difference between two addresses.
        ZPL_DEF_INLINE zpl_isize zpl_pointer_diff(void const *begin, void const *end);

        #define zpl_ptr_add zpl_pointer_add
        #define zpl_ptr_sub zpl_pointer_sub
        #define zpl_ptr_add_const zpl_pointer_add_const
        #define zpl_ptr_sub_const zpl_pointer_sub_const
        #define zpl_ptr_diff zpl_pointer_diff

        //! Clears up memory at location by specified size.

        //! @param ptr Memory location to clear up.
        //! @param size The size to clear up with.
        ZPL_DEF_INLINE void zpl_zero_size(void *ptr, zpl_isize size);

        #ifndef zpl_zero_item
        //! Clears up an item.
        #define zpl_zero_item(t) zpl_zero_size((t), zpl_size_of(*(t))) // NOTE: Pass pointer of struct

        //! Clears up an array.
        #define zpl_zero_array(a, count) zpl_zero_size((a), zpl_size_of(*(a)) * count)
        #endif

        //! Copy memory from source to destination.
        ZPL_DEF_INLINE void *zpl_memmove(void *dest, void const *source, zpl_isize size);

        //! Set constant value at memory location with specified size.
        ZPL_DEF_INLINE void *zpl_memset(void *data, zpl_u8 byte_value, zpl_isize size);

        //! Compare two memory locations with specified size.
        ZPL_DEF_INLINE zpl_i32 zpl_memcompare(void const *s1, void const *s2, zpl_isize size);

        //! Swap memory contents between 2 locations with size.
        ZPL_DEF void zpl_memswap(void *i, void *j, zpl_isize size);

        //! Search for a constant value within the size limit at memory location.
        ZPL_DEF void const *zpl_memchr(void const *data, zpl_u8 byte_value, zpl_isize size);

        //! Search for a constant value within the size limit at memory location in backwards.
        ZPL_DEF void const *zpl_memrchr(void const *data, zpl_u8 byte_value, zpl_isize size);

        //! Copy non-overlapping memory from source to destination.
        ZPL_DEF void *zpl_memcopy(void *dest, void const *source, zpl_isize size);

        #ifndef zpl_memcopy_array

        //! Copy non-overlapping array.
        #define zpl_memcopy_array(dst, src, count) zpl_memcopy((dst), (src), zpl_size_of(*(dst)) * (count))
        #endif

        //! Copy an array.
        #ifndef zpl_memmove_array
        #define zpl_memmove_array(dst, src, count) zpl_memmove((dst), (src), zpl_size_of(*(dst)) * (count))
        #endif

        #ifndef ZPL_BIT_CAST
        #define ZPL_BIT_CAST(dest, source)                                                                                 \
        do {                                                                                                               \
            ZPL_STATIC_ASSERT(zpl_size_of(*(dest)) <= zpl_size_of(source), "zpl_size_of(*(dest)) !<= zpl_size_of(source)");\
            zpl_memcopy((dest), &(source), zpl_size_of(*dest));                                                            \
        } while (0)
        #endif

        #ifndef zpl_kilobytes
        #define zpl_kilobytes(x) ((x)              * (zpl_i64)(1024))
        #define zpl_megabytes(x) (zpl_kilobytes(x) * (zpl_i64)(1024))
        #define zpl_gigabytes(x) (zpl_megabytes(x) * (zpl_i64)(1024))
        #define zpl_terabytes(x) (zpl_gigabytes(x) * (zpl_i64)(1024))
        #endif


        /* inlines */

        #define ZPL__ONES (cast(zpl_usize) - 1 / ZPL_U8_MAX)
        #define ZPL__HIGHS (ZPL__ONES * (ZPL_U8_MAX / 2 + 1))
        #define ZPL__HAS_ZERO(x) (((x)-ZPL__ONES) & ~(x)&ZPL__HIGHS)

        ZPL_IMPL_INLINE void *zpl_align_forward(void *ptr, zpl_isize alignment) {
            zpl_uintptr p;

            ZPL_ASSERT(zpl_is_power_of_two(alignment));

            p = cast(zpl_uintptr) ptr;
            return cast(void *)((p + (alignment - 1)) & ~(alignment - 1));
        }

        ZPL_IMPL_INLINE void *zpl_pointer_add(void *ptr, zpl_isize bytes) { return cast(void *)(cast(zpl_u8 *) ptr + bytes); }
        ZPL_IMPL_INLINE void *zpl_pointer_sub(void *ptr, zpl_isize bytes) { return cast(void *)(cast(zpl_u8 *) ptr - bytes); }
        ZPL_IMPL_INLINE void const *zpl_pointer_add_const(void const *ptr, zpl_isize bytes) {
            return cast(void const *)(cast(zpl_u8 const *) ptr + bytes);
        }
        ZPL_IMPL_INLINE void const *zpl_pointer_sub_const(void const *ptr, zpl_isize bytes) {
            return cast(void const *)(cast(zpl_u8 const *) ptr - bytes);
        }
        ZPL_IMPL_INLINE zpl_isize zpl_pointer_diff(void const *begin, void const *end) {
            return cast(zpl_isize)(cast(zpl_u8 const *) end - cast(zpl_u8 const *) begin);
        }

        ZPL_IMPL_INLINE void zpl_zero_size(void *ptr, zpl_isize size) { zpl_memset(ptr, 0, size); }

        #if defined(_MSC_VER) && !defined(__clang__)
        #pragma intrinsic(__movsb)
        #endif

        ZPL_IMPL_INLINE void *zpl_memmove(void *dest, void const *source, zpl_isize n) {
            if (dest == NULL) { return NULL; }

            zpl_u8 *d = cast(zpl_u8 *) dest;
            zpl_u8 const *s = cast(zpl_u8 const *) source;

            if (d == s) return d;
            if (s + n <= d || d + n <= s) // NOTE: Non-overlapping
                return zpl_memcopy(d, s, n);

            if (d < s) {
                if (cast(zpl_uintptr) s % zpl_size_of(zpl_isize) == cast(zpl_uintptr) d % zpl_size_of(zpl_isize)) {
                    while (cast(zpl_uintptr) d % zpl_size_of(zpl_isize)) {
                        if (!n--) return dest;
                        *d++ = *s++;
                    }
                    while (n >= zpl_size_of(zpl_isize)) {
                        *cast(zpl_isize *) d = *cast(zpl_isize *) s;
                        n -= zpl_size_of(zpl_isize);
                        d += zpl_size_of(zpl_isize);
                        s += zpl_size_of(zpl_isize);
                    }
                }
                for (; n; n--) *d++ = *s++;
            } else {
                if ((cast(zpl_uintptr) s % zpl_size_of(zpl_isize)) == (cast(zpl_uintptr) d % zpl_size_of(zpl_isize))) {
                    while (cast(zpl_uintptr)(d + n) % zpl_size_of(zpl_isize)) {
                        if (!n--) return dest;
                        d[n] = s[n];
                    }
                    while (n >= zpl_size_of(zpl_isize)) {
                        n -= zpl_size_of(zpl_isize);
                        *cast(zpl_isize *)(d + n) = *cast(zpl_isize *)(s + n);
                    }
                }
                while (n) n--, d[n] = s[n];
            }

            return dest;
        }

        ZPL_IMPL_INLINE void *zpl_memset(void *dest, zpl_u8 c, zpl_isize n) {
            if (dest == NULL) { return NULL; }

            zpl_u8 *s = cast(zpl_u8 *) dest;
            zpl_isize k;
            zpl_u32 c32 = ((zpl_u32)-1) / 255 * c;

            if (n == 0) return dest;
            s[0] = s[n - 1] = c;
            if (n < 3) return dest;
            s[1] = s[n - 2] = c;
            s[2] = s[n - 3] = c;
            if (n < 7) return dest;
            s[3] = s[n - 4] = c;
            if (n < 9) return dest;

            k = -cast(zpl_intptr) s & 3;
            s += k;
            n -= k;
            n &= -4;

            *cast(zpl_u32 *)(s + 0) = c32;
            *cast(zpl_u32 *)(s + n - 4) = c32;
            if (n < 9) return dest;
            *cast(zpl_u32 *)(s + 4) = c32;
            *cast(zpl_u32 *)(s + 8) = c32;
            *cast(zpl_u32 *)(s + n - 12) = c32;
            *cast(zpl_u32 *)(s + n - 8) = c32;
            if (n < 25) return dest;
            *cast(zpl_u32 *)(s + 12) = c32;
            *cast(zpl_u32 *)(s + 16) = c32;
            *cast(zpl_u32 *)(s + 20) = c32;
            *cast(zpl_u32 *)(s + 24) = c32;
            *cast(zpl_u32 *)(s + n - 28) = c32;
            *cast(zpl_u32 *)(s + n - 24) = c32;
            *cast(zpl_u32 *)(s + n - 20) = c32;
            *cast(zpl_u32 *)(s + n - 16) = c32;

            k = 24 + (cast(zpl_uintptr) s & 4);
            s += k;
            n -= k;

            {
                zpl_u64 c64 = (cast(zpl_u64) c32 << 32) | c32;
                while (n > 31) {
                    *cast(zpl_u64 *)(s + 0) = c64;
                    *cast(zpl_u64 *)(s + 8) = c64;
                    *cast(zpl_u64 *)(s + 16) = c64;
                    *cast(zpl_u64 *)(s + 24) = c64;

                    n -= 32;
                    s += 32;
                }
            }

            return dest;
        }

        ZPL_IMPL_INLINE zpl_i32 zpl_memcompare(void const *s1, void const *s2, zpl_isize size) {
            zpl_u8 const *s1p8 = cast(zpl_u8 const *) s1;
            zpl_u8 const *s2p8 = cast(zpl_u8 const *) s2;

            if (s1 == NULL || s2 == NULL) { return 0; }

            while (size--) {
                zpl_isize d;
                if ((d = (*s1p8++ - *s2p8++)) != 0) return cast(zpl_i32) d;
            }
            return 0;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_is_power_of_two(zpl_isize x) {
            if (x <= 0) return false;
            return !(x & (x - 1));
        }

        ZPL_END_C_DECLS
        // file: header/core/memory_virtual.h


        ////////////////////////////////////////////////////////////////
        //
        // Virtual Memory
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_virtual_memory {
            void *data;
            zpl_isize size;
        } zpl_virtual_memory;

        //! Initialize virtual memory from existing data.
        ZPL_DEF zpl_virtual_memory zpl_vm(void *data, zpl_isize size);

        //! Allocate virtual memory at address with size.

        //! @param addr The starting address of the region to reserve. If NULL, it lets operating system to decide where to allocate it.
        //! @param size The size to server.
        ZPL_DEF zpl_virtual_memory zpl_vm_alloc(void *addr, zpl_isize size);

        //! Release the virtual memory.
        ZPL_DEF zpl_b32 zpl_vm_free(zpl_virtual_memory vm);

        //! Trim virtual memory.
        ZPL_DEF zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, zpl_isize lead_size, zpl_isize size);

        //! Purge virtual memory.
        ZPL_DEF zpl_b32 zpl_vm_purge(zpl_virtual_memory vm);

        //! Retrieve VM's page size and alignment.
        ZPL_DEF zpl_isize zpl_virtual_memory_page_size(zpl_isize *alignment_out);

        ZPL_END_C_DECLS
        // file: header/core/memory_custom.h

        ////////////////////////////////////////////////////////////////
        //
        // Custom Allocation
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef enum zplAllocationType {
            ZPL_ALLOCATION_ALLOC,
            ZPL_ALLOCATION_FREE,
            ZPL_ALLOCATION_FREE_ALL,
            ZPL_ALLOCATION_RESIZE,
        } zplAllocationType;

        // NOTE: This is useful so you can define an allocator of the same type and parameters
        #define ZPL_ALLOCATOR_PROC(name)                                                                                       \
        void *name(void *allocator_data, zplAllocationType type, zpl_isize size, zpl_isize alignment, void *old_memory,            \
        zpl_isize old_size, zpl_u64 flags)
        typedef ZPL_ALLOCATOR_PROC(zpl_allocator_proc);


        typedef struct zpl_allocator {
            zpl_allocator_proc *proc;
            void *data;
        } zpl_allocator;

        typedef enum zplAllocatorFlag {
            ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO = ZPL_BIT(0),
        } zplAllocatorFlag;

        #ifndef ZPL_DEFAULT_MEMORY_ALIGNMENT
        #define ZPL_DEFAULT_MEMORY_ALIGNMENT (2 * zpl_size_of(void *))
        #endif

        #ifndef ZPL_DEFAULT_ALLOCATOR_FLAGS
        #define ZPL_DEFAULT_ALLOCATOR_FLAGS (ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO)
        #endif

        //! Allocate memory with specified alignment.
        ZPL_DEF_INLINE void *zpl_alloc_align(zpl_allocator a, zpl_isize size, zpl_isize alignment);

        //! Allocate memory with default alignment.
        ZPL_DEF_INLINE void *zpl_alloc(zpl_allocator a, zpl_isize size);

        //! Free allocated memory.
        ZPL_DEF_INLINE void zpl_free(zpl_allocator a, void *ptr);

        //! Free all memory allocated by an allocator.
        ZPL_DEF_INLINE void zpl_free_all(zpl_allocator a);

        //! Resize an allocated memory.
        ZPL_DEF_INLINE void *zpl_resize(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size);

        //! Resize an allocated memory with specified alignment.
        ZPL_DEF_INLINE void *zpl_resize_align(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size, zpl_isize alignment);

        //! Allocate memory and copy data into it.
        ZPL_DEF_INLINE void *zpl_alloc_copy(zpl_allocator a, void const *src, zpl_isize size);

        //! Allocate memory with specified alignment and copy data into it.
        ZPL_DEF_INLINE void *zpl_alloc_copy_align(zpl_allocator a, void const *src, zpl_isize size, zpl_isize alignment);

        //! Allocate memory for null-terminated C-String.
        ZPL_DEF_INLINE char *zpl_alloc_str(zpl_allocator a, char const *str);

        //! Allocate memory for C-String with specified size.
        ZPL_DEF_INLINE char *zpl_alloc_str_len(zpl_allocator a, char const *str, zpl_isize len);

        #ifndef zpl_alloc_item

        //! Allocate memory for an item.
        #define zpl_alloc_item(allocator_, Type) (Type *)zpl_alloc(allocator_, zpl_size_of(Type))

        //! Allocate memory for an array of items.
        #define zpl_alloc_array(allocator_, Type, count) (Type *)zpl_alloc(allocator_, zpl_size_of(Type) * (count))
        #endif

        //! Allocate/Resize memory using default options.

        //! Use this if you don't need a "fancy" resize allocation
        ZPL_DEF_INLINE void *zpl_default_resize_align(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size, zpl_isize alignment);

        //! The heap allocator backed by operating system's memory manager.
        ZPL_DEF_INLINE zpl_allocator zpl_heap_allocator(void);
        ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_heap_allocator_proc);

        #ifndef zpl_malloc

        //! Helper to allocate memory using heap allocator.
        #define zpl_malloc(sz) zpl_alloc(zpl_heap_allocator( ), sz)

        //! Helper to free memory allocated by heap allocator.
        #define zpl_mfree(ptr) zpl_free(zpl_heap_allocator( ), ptr)

        //! Alias to heap allocator.
        #define zpl_heap zpl_heap_allocator
        #endif

        //
        // Arena Allocator
        //

        typedef struct zpl_arena {
            zpl_allocator backing;
            void *physical_start;
            zpl_isize total_size;
            zpl_isize total_allocated;
            zpl_isize temp_count;
        } zpl_arena;

        //! Initialize memory arena from existing memory region.
        ZPL_DEF_INLINE void zpl_arena_init_from_memory(zpl_arena *arena, void *start, zpl_isize size);

        //! Initialize memory arena using existing memory allocator.
        ZPL_DEF_INLINE void zpl_arena_init_from_allocator(zpl_arena *arena, zpl_allocator backing, zpl_isize size);

        //! Initialize memory arena within an existing parent memory arena.
        ZPL_DEF_INLINE void zpl_arena_init_sub(zpl_arena *arena, zpl_arena *parent_arena, zpl_isize size);

        //! Release the memory used by memory arena.
        ZPL_DEF_INLINE void zpl_arena_free(zpl_arena *arena);


        //! Retrieve memory arena's aligned allocation address.
        ZPL_DEF_INLINE zpl_isize zpl_arena_alignment_of(zpl_arena *arena, zpl_isize alignment);

        //! Retrieve memory arena's remaining size.
        ZPL_DEF_INLINE zpl_isize zpl_arena_size_remaining(zpl_arena *arena, zpl_isize alignment);

        //! Check whether memory arena has any temporary snapshots.
        ZPL_DEF_INLINE void zpl_arena_check(zpl_arena *arena);

        //! Allocation Types: alloc, free_all, resize
        ZPL_DEF_INLINE zpl_allocator zpl_arena_allocator(zpl_arena *arena);
        ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_arena_allocator_proc);


        typedef struct zpl_temp_arena_memory {
            zpl_arena *arena;
            zpl_isize original_count;
        } zpl_temp_arena_memory;

        //! Capture a snapshot of used memory in a memory arena.
        ZPL_DEF_INLINE zpl_temp_arena_memory zpl_temp_arena_memory_begin(zpl_arena *arena);

        //! Reset memory arena's usage by a captured snapshot.
        ZPL_DEF_INLINE void zpl_temp_arena_memory_end(zpl_temp_arena_memory tmp_mem);

        //
        // Pool Allocator
        //


        typedef struct zpl_pool {
            zpl_allocator backing;
            void *physical_start;
            void *free_list;
            zpl_isize block_size;
            zpl_isize block_align;
            zpl_isize total_size;
            zpl_isize num_blocks;
        } zpl_pool;


        //! Initialize pool allocator.
        ZPL_DEF_INLINE void zpl_pool_init(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size);

        //! Initialize pool allocator with specific block alignment.
        ZPL_DEF void zpl_pool_init_align(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size,
                                         zpl_isize block_align);

        //! Release the resources used by pool allocator.
        ZPL_DEF_INLINE void zpl_pool_free(zpl_pool *pool);

        //! Allocation Types: alloc, free
        ZPL_DEF_INLINE zpl_allocator zpl_pool_allocator(zpl_pool *pool);
        ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_pool_allocator_proc);


        typedef struct zpl_allocation_header_ev {
            zpl_isize size;
        } zpl_allocation_header_ev;

        ZPL_DEF_INLINE zpl_allocation_header_ev *zpl_allocation_header(void *data);
        ZPL_DEF_INLINE void zpl_allocation_header_fill(zpl_allocation_header_ev *header, void *data, zpl_isize size);

        #if defined(ZPL_ARCH_32_BIT)
        #define ZPL_ISIZE_HIGH_BIT 0x80000000
        #elif defined(ZPL_ARCH_64_BIT)
        #define ZPL_ISIZE_HIGH_BIT 0x8000000000000000ll
        #else
        #error
        #endif

        //
        // Scratch Memory Allocator - Ring Buffer Based Arena
        //


        typedef struct zpl_scratch_memory {
            void *physical_start;
            zpl_isize total_size;
            void *alloc_point;
            void *free_point;
        } zpl_scratch_memory;

        //! Initialize ring buffer arena.
        ZPL_DEF void zpl_scratch_memory_init(zpl_scratch_memory *s, void *start, zpl_isize size);

        //! Check whether ring buffer arena is in use.
        ZPL_DEF zpl_b32 zpl_scratch_memory_is_in_use(zpl_scratch_memory *s, void *ptr);

        //! Allocation Types: alloc, free, free_all, resize
        ZPL_DEF zpl_allocator zpl_scratch_allocator(zpl_scratch_memory *s);
        ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_scratch_allocator_proc);

        //
        // Stack Memory Allocator
        //


        typedef struct zpl_stack_memory {
            zpl_allocator backing;

            void *physical_start;
            zpl_usize total_size;
            zpl_usize allocated;
        } zpl_stack_memory;

        //! Initialize stack allocator from existing memory.
        ZPL_DEF_INLINE void zpl_stack_memory_init_from_memory(zpl_stack_memory *s, void *start, zpl_isize size);

        //! Initialize stack allocator using existing memory allocator.
        ZPL_DEF_INLINE void zpl_stack_memory_init(zpl_stack_memory *s, zpl_allocator backing, zpl_isize size);

        //! Check whether stack allocator is in use.
        ZPL_DEF_INLINE zpl_b32 zpl_stack_memory_is_in_use(zpl_stack_memory *s, void *ptr);

        //! Release the resources used by stack allocator.
        ZPL_DEF_INLINE void zpl_stack_memory_free(zpl_stack_memory *s);

        //! Allocation Types: alloc, free, free_all
        ZPL_DEF_INLINE zpl_allocator zpl_stack_allocator(zpl_stack_memory *s);
        ZPL_DEF ZPL_ALLOCATOR_PROC(zpl_stack_allocator_proc);

        // TODO: Fixed heap allocator
        // TODO: General heap allocator. Maybe a TCMalloc like clone?


        /* inlines */

        ZPL_IMPL_INLINE void *zpl_alloc_align(zpl_allocator a, zpl_isize size, zpl_isize alignment) {
            return a.proc(a.data, ZPL_ALLOCATION_ALLOC, size, alignment, NULL, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
        }
        ZPL_IMPL_INLINE void *zpl_alloc(zpl_allocator a, zpl_isize size) {
            return zpl_alloc_align(a, size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
        }
        ZPL_IMPL_INLINE void zpl_free(zpl_allocator a, void *ptr) {
            if (ptr != NULL) a.proc(a.data, ZPL_ALLOCATION_FREE, 0, 0, ptr, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
        }
        ZPL_IMPL_INLINE void zpl_free_all(zpl_allocator a) {
            a.proc(a.data, ZPL_ALLOCATION_FREE_ALL, 0, 0, NULL, 0, ZPL_DEFAULT_ALLOCATOR_FLAGS);
        }
        ZPL_IMPL_INLINE void *zpl_resize(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size) {
            return zpl_resize_align(a, ptr, old_size, new_size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
        }
        ZPL_IMPL_INLINE void *zpl_resize_align(zpl_allocator a, void *ptr, zpl_isize old_size, zpl_isize new_size, zpl_isize alignment) {
            return a.proc(a.data, ZPL_ALLOCATION_RESIZE, new_size, alignment, ptr, old_size, ZPL_DEFAULT_ALLOCATOR_FLAGS);
        }

        ZPL_IMPL_INLINE void *zpl_alloc_copy(zpl_allocator a, void const *src, zpl_isize size) {
            return zpl_memcopy(zpl_alloc(a, size), src, size);
        }
        ZPL_IMPL_INLINE void *zpl_alloc_copy_align(zpl_allocator a, void const *src, zpl_isize size, zpl_isize alignment) {
            return zpl_memcopy(zpl_alloc_align(a, size, alignment), src, size);
        }

        ZPL_IMPL_INLINE char *zpl_alloc_str_len(zpl_allocator a, char const *str, zpl_isize len) {
            char *result;
            result = cast(char *) zpl_alloc_copy(a, str, len + 1);
            result[len] = '\0';
            return result;
        }

        ZPL_IMPL_INLINE void *zpl_default_resize_align(zpl_allocator a, void *old_memory, zpl_isize old_size, zpl_isize new_size,
                                                  zpl_isize alignment) {
            if (!old_memory) return zpl_alloc_align(a, new_size, alignment);

            if (new_size == 0) {
                zpl_free(a, old_memory);
                return NULL;
            }

            if (new_size < old_size) new_size = old_size;

            if (old_size == new_size) {
                return old_memory;
            } else {
                void *new_memory = zpl_alloc_align(a, new_size, alignment);
                if (!new_memory) return NULL;
                zpl_memmove(new_memory, old_memory, zpl_min(new_size, old_size));
                zpl_free(a, old_memory);
                return new_memory;
            }
        }


        //
        // Heap Allocator
        //

        ZPL_IMPL_INLINE zpl_allocator zpl_heap_allocator(void) {
            zpl_allocator a;
            a.proc = zpl_heap_allocator_proc;
            a.data = NULL;
            return a;
        }

        //
        // Arena Allocator
        //

        ZPL_IMPL_INLINE void zpl_arena_init_from_memory(zpl_arena *arena, void *start, zpl_isize size) {
            arena->backing.proc = NULL;
            arena->backing.data = NULL;
            arena->physical_start = start;
            arena->total_size = size;
            arena->total_allocated = 0;
            arena->temp_count = 0;
        }

        ZPL_IMPL_INLINE void zpl_arena_init_from_allocator(zpl_arena *arena, zpl_allocator backing, zpl_isize size) {
            arena->backing = backing;
            arena->physical_start = zpl_alloc(backing, size); // NOTE: Uses default alignment
            arena->total_size = size;
            arena->total_allocated = 0;
            arena->temp_count = 0;
        }

        ZPL_IMPL_INLINE void zpl_arena_init_sub(zpl_arena *arena, zpl_arena *parent_arena, zpl_isize size) {
            zpl_arena_init_from_allocator(arena, zpl_arena_allocator(parent_arena), size);
        }

        ZPL_IMPL_INLINE void zpl_arena_free(zpl_arena *arena) {
            if (arena->backing.proc) {
                zpl_free(arena->backing, arena->physical_start);
                arena->physical_start = NULL;
            }
        }

        ZPL_IMPL_INLINE zpl_isize zpl_arena_alignment_of(zpl_arena *arena, zpl_isize alignment) {
            zpl_isize alignment_offset, result_pointer, mask;
            ZPL_ASSERT(zpl_is_power_of_two(alignment));

            alignment_offset = 0;
            result_pointer = cast(zpl_isize) arena->physical_start + arena->total_allocated;
            mask = alignment - 1;
            if (result_pointer & mask) alignment_offset = alignment - (result_pointer & mask);

            return alignment_offset;
        }

        ZPL_IMPL_INLINE zpl_isize zpl_arena_size_remaining(zpl_arena *arena, zpl_isize alignment) {
            zpl_isize result = arena->total_size - (arena->total_allocated + zpl_arena_alignment_of(arena, alignment));
            return result;
        }

        ZPL_IMPL_INLINE void zpl_arena_check(zpl_arena *arena) { ZPL_ASSERT(arena->temp_count == 0); }

        ZPL_IMPL_INLINE zpl_allocator zpl_arena_allocator(zpl_arena *arena) {
            zpl_allocator allocator;
            allocator.proc = zpl_arena_allocator_proc;
            allocator.data = arena;
            return allocator;
        }

        ZPL_IMPL_INLINE zpl_temp_arena_memory zpl_temp_arena_memory_begin(zpl_arena *arena) {
            zpl_temp_arena_memory tmp;
            tmp.arena = arena;
            tmp.original_count = arena->total_allocated;
            arena->temp_count++;
            return tmp;
        }

        ZPL_IMPL_INLINE void zpl_temp_arena_memory_end(zpl_temp_arena_memory tmp) {
            ZPL_ASSERT(tmp.arena->total_allocated >= tmp.original_count);
            ZPL_ASSERT(tmp.arena->temp_count > 0);
            tmp.arena->total_allocated = tmp.original_count;
            tmp.arena->temp_count--;
        }

        //
        // Pool Allocator
        //

        ZPL_IMPL_INLINE void zpl_pool_init(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size) {
            zpl_pool_init_align(pool, backing, num_blocks, block_size, ZPL_DEFAULT_MEMORY_ALIGNMENT);
        }

        ZPL_IMPL_INLINE void zpl_pool_free(zpl_pool *pool) {
            if (pool->backing.proc) { zpl_free(pool->backing, pool->physical_start); }
        }

        ZPL_IMPL_INLINE zpl_allocator zpl_pool_allocator(zpl_pool *pool) {
            zpl_allocator allocator;
            allocator.proc = zpl_pool_allocator_proc;
            allocator.data = pool;
            return allocator;
        }

        ZPL_IMPL_INLINE zpl_allocation_header_ev *zpl_allocation_header(void *data) {
            zpl_isize *p = cast(zpl_isize *) data;
            while (p[-1] == cast(zpl_isize)(-1)) p--;
            return cast(zpl_allocation_header_ev *) p - 1;
        }

        ZPL_IMPL_INLINE void zpl_allocation_header_fill(zpl_allocation_header_ev *header, void *data, zpl_isize size) {
            zpl_isize *ptr;
            header->size = size;
            ptr = cast(zpl_isize *)(header + 1);
            while (cast(void *) ptr < data) *ptr++ = cast(zpl_isize)(-1);
        }

        //
        // Stack Memory Allocator
        //

        #define ZPL_STACK_ALLOC_OFFSET sizeof(zpl_u64)
        ZPL_STATIC_ASSERT(ZPL_STACK_ALLOC_OFFSET == 8, "ZPL_STACK_ALLOC_OFFSET != 8");

        ZPL_IMPL_INLINE void zpl_stack_memory_init_from_memory(zpl_stack_memory *s, void *start, zpl_isize size) {
            s->physical_start = start;
            s->total_size = size;
            s->allocated = 0;
        }

        ZPL_IMPL_INLINE void zpl_stack_memory_init(zpl_stack_memory *s, zpl_allocator backing, zpl_isize size) {
            s->backing = backing;
            s->physical_start = zpl_alloc(backing, size);
            s->total_size = size;
            s->allocated = 0;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_stack_memory_is_in_use(zpl_stack_memory *s, void *ptr) {
            if (s->allocated == 0) return false;

            if (ptr > s->physical_start && ptr < zpl_pointer_add(s->physical_start, s->total_size)) { return true; }

            return false;
        }

        ZPL_IMPL_INLINE void zpl_stack_memory_free(zpl_stack_memory *s) {
            if (s->backing.proc) {
                zpl_free(s->backing, s->physical_start);
                s->physical_start = NULL;
            }
        }

        ZPL_IMPL_INLINE zpl_allocator zpl_stack_allocator(zpl_stack_memory *s) {
            zpl_allocator a;
            a.proc = zpl_stack_allocator_proc;
            a.data = s;
            return a;
        }

        ZPL_END_C_DECLS
        // file: header/core/collections/array.h

        ////////////////////////////////////////////////////////////////
        //
        // Dynamic Array (POD Types)
        //
        // zpl_array(Type) works like zpl_string or zpl_buffer where the actual type is just a pointer to the first
        // element.
        //
        // Available Procedures for zpl_array(Type)
        // zpl_array_init
        // zpl_array_free
        // zpl_array_set_capacity
        // zpl_array_grow
        // zpl_array_append
        // zpl_array_appendv
        // zpl_array_pop
        // zpl_array_clear
        // zpl_array_back
        // zpl_array_front
        // zpl_array_resize
        // zpl_array_reserve
        //

        #if 0 // Example
        void foo(void) {
            zpl_isize i;
            int test_values[] = {4, 2, 1, 7};
            zpl_allocator a = zpl_heap_allocator();
            zpl_array(int) items;

            zpl_array_init(items, a);

            zpl_array_append(items, 1);
            zpl_array_append(items, 4);
            zpl_array_append(items, 9);
            zpl_array_append(items, 16);

            items[1] = 3; // Manually set value
            // NOTE: No array bounds checking

            for (i = 0; i < items.count; i++)
                zpl_printf("%d\n", items[i]);
            // 1
            // 3
            // 9
            // 16

            zpl_array_clear(items);

            zpl_array_appendv(items, test_values, zpl_count_of(test_values));
            for (i = 0; i < items.count; i++)
                zpl_printf("%d\n", items[i]);
            // 4
            // 2
            // 1
            // 7

            zpl_array_free(items);
        }
        #endif

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_array_header {
            char *data;
            zpl_isize count;
            zpl_isize capacity;
            zpl_allocator allocator;
        } zpl_array_header;

        #define zpl_array(Type) Type *

        #define zpl_array_make(Type, Name, allocator) Type *Name; zpl_array_init(Name, allocator)

        #ifndef ZPL_ARRAY_GROW_FORMULA
        #define ZPL_ARRAY_GROW_FORMULA(x) (2 * (x) + 8)
        #endif

        ZPL_STATIC_ASSERT(ZPL_ARRAY_GROW_FORMULA(0) > 0, "ZPL_ARRAY_GROW_FORMULA(0) <= 0");

        #define ZPL_ARRAY_HEADER(x)    (cast(zpl_array_header *)(x) - 1)
        #define zpl_array_allocator(x) (ZPL_ARRAY_HEADER(x)->allocator)
        #define zpl_array_count(x)     (ZPL_ARRAY_HEADER(x)->count)
        #define zpl_array_capacity(x)  (ZPL_ARRAY_HEADER(x)->capacity)
        #define zpl_array_end(x)       (x + (zpl_array_count(x) - 1))

        #define zpl_array_init_reserve(x, allocator_, cap)                                                                     \
        do {                                                                                                               \
            void **zpl__array_ = cast(void **) & (x);                                                                      \
            zpl_array_header *zpl__ah =                                                                                    \
            cast(zpl_array_header *) zpl_alloc(allocator_, zpl_size_of(zpl_array_header) + zpl_size_of(*(x)) * (cap)); \
            zpl__ah->allocator = allocator_;                                                                               \
            zpl__ah->count = 0;                                                                                            \
            zpl__ah->data = (char *)x;                                                                                     \
            zpl__ah->capacity = cap;                                                                                       \
            *zpl__array_ = cast(void *)(zpl__ah + 1);                                                                      \
        } while (0)

        // NOTE: Give it an initial default capacity
        #define zpl_array_init(x, allocator) zpl_array_init_reserve(x, allocator, ZPL_ARRAY_GROW_FORMULA(0))

        #define zpl_array_free(x)                                                                                              \
        do {                                                                                                               \
            zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
            zpl_free(zpl__ah->allocator, zpl__ah);                                                                         \
        } while (0)

        #define zpl_array_set_capacity(x, capacity)                                                                            \
        do {                                                                                                               \
            if (x) {                                                                                                       \
                void **zpl__array_ = cast(void **) & (x);                                                                  \
                *zpl__array_ = zpl__array_set_capacity((x), (capacity), zpl_size_of(*(x)));                                \
            }                                                                                                              \
        } while (0)

        // NOTE: Do not use the thing below directly, use the macro
        ZPL_DEF void *zpl__array_set_capacity(void *array, zpl_isize capacity, zpl_isize element_size);

        #define zpl_array_grow(x, min_capacity)                                                                                \
        do {                                                                                                               \
            zpl_isize new_capacity = ZPL_ARRAY_GROW_FORMULA(zpl_array_capacity(x));                                            \
            if (new_capacity < (min_capacity)) new_capacity = (min_capacity);                                              \
            zpl_array_set_capacity(x, new_capacity);                                                                       \
        } while (0)

        #define zpl_array_append(x, item)                                                                                      \
        do {                                                                                                               \
            if (zpl_array_capacity(x) < zpl_array_count(x) + 1) zpl_array_grow(x, 0);                                      \
            (x)[zpl_array_count(x)++] = (item);                                                                            \
        } while (0)

        #define zpl_array_append_at(x, item, ind)                                                                              \
        do {                                                                                                               \
            zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
            if (ind == zpl__ah->count) { zpl_array_append(x, item); break; }                                               \
            if (zpl_array_capacity(x) < zpl_array_count(x) + 1) zpl_array_grow(x, 0);                                      \
            zpl_memmove(&(x)[ind + 1], (x + ind), zpl_size_of(x[0]) * (zpl__ah->count - ind));                             \
            x[ind] = item;                                                                                                 \
            zpl__ah->count++;                                                                                              \
        } while (0)

        #define zpl_array_appendv(x, items, item_count)                                                                        \
        do {                                                                                                               \
            zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
            ZPL_ASSERT(zpl_size_of((items)[0]) == zpl_size_of((x)[0]));                                                    \
            if (zpl__ah->capacity < zpl__ah->count + (item_count)) zpl_array_grow(x, zpl__ah->count + (item_count));       \
            zpl_memcopy(&(x)[zpl__ah->count], (items), zpl_size_of((x)[0]) * (item_count));                                \
            zpl__ah->count += (item_count);                                                                                \
        } while (0)

        #define zpl_array_remove_at(x, index)                                                                                  \
        do {                                                                                                               \
            zpl_array_header *zpl__ah = ZPL_ARRAY_HEADER(x);                                                               \
            ZPL_ASSERT(index < zpl__ah->count);                                                                            \
            zpl_memmove(x + index, x + index + 1, zpl_size_of(x[0]) * (zpl__ah->count - index));                           \
            --zpl__ah->count;                                                                                              \
        } while (0)

        #define zpl_array_copy_init(y, x)                                                                                      \
        do {                                                                                                               \
            zpl_array_init_reserve(y, zpl_array_allocator(x), zpl_array_capacity(x));                                      \
            zpl_memcopy(y, x, zpl_array_capacity(x) * zpl_size_of(*x));                                                    \
            zpl_array_count(y) = zpl_array_count(x);                                                                       \
        } while (0)

        #define zpl_array_pop(x)                                                                                               \
        do {                                                                                                               \
            ZPL_ASSERT(ZPL_ARRAY_HEADER(x)->count > 0);                                                                    \
            ZPL_ARRAY_HEADER(x)->count--;                                                                                  \
        } while (0)
        #define zpl_array_back(x) x[ZPL_ARRAY_HEADER(x)->count - 1]
        #define zpl_array_front(x) x[0]
        #define zpl_array_clear(x)                                                                                             \
        do { ZPL_ARRAY_HEADER(x)->count = 0; } while (0)

        #define zpl_array_resize(x, new_count)                                                                                 \
        do {                                                                                                               \
            if (ZPL_ARRAY_HEADER(x)->capacity < (new_count)) zpl_array_grow(x, (new_count));                               \
            ZPL_ARRAY_HEADER(x)->count = (new_count);                                                                      \
        } while (0)

        #define zpl_array_reserve(x, new_capacity)                                                                             \
        do {                                                                                                               \
            if (ZPL_ARRAY_HEADER(x)->capacity < (new_capacity)) zpl_array_set_capacity(x, new_capacity);                   \
        } while (0)

        ZPL_END_C_DECLS
        // file: header/core/collections/buffer.h

        ////////////////////////////////////////////////////////////////
        //
        // Fixed Capacity Buffer (POD Types)
        //
        //
        // zpl_buffer(Type) works like zpl_string or zpl_array where the actual type is just a pointer to the first
        // element.
        //
        // Available Procedures for zpl_buffer(Type)
        // zpl_buffer_init
        // zpl_buffer_free
        // zpl_buffer_append
        // zpl_buffer_appendv
        // zpl_buffer_pop
        // zpl_buffer_clear

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_buffer_header {
            zpl_allocator backing;
            zpl_isize count;
            zpl_isize capacity;
        } zpl_buffer_header;

        #define zpl_buffer(Type) Type *

        #define zpl_buffer_make(Type, Name, allocator, cap) Type *Name; zpl_buffer_init(Name, allocator, cap)

        #define ZPL_BUFFER_HEADER(x)   (cast(zpl_buffer_header *)(x) - 1)
        #define zpl_buffer_count(x)    (ZPL_BUFFER_HEADER(x)->count)
        #define zpl_buffer_capacity(x) (ZPL_BUFFER_HEADER(x)->capacity)
        #define zpl_buffer_end(x) (x + (zpl_buffer_count(x) - 1))

        #define zpl_buffer_init(x, allocator, cap)                                                                             \
        do {                                                                                                               \
            void **nx = cast(void **) & (x);                                                                               \
            zpl_buffer_header *zpl__bh =                                                                                   \
            cast(zpl_buffer_header *) zpl_alloc((allocator), sizeof(zpl_buffer_header) + (cap)*zpl_size_of(*(x)));     \
            zpl__bh->backing = allocator;                                                                                  \
            zpl__bh->count = 0;                                                                                            \
            zpl__bh->capacity = cap;                                                                                       \
            *nx = cast(void *)(zpl__bh + 1);                                                                               \
        } while (0)

        // DEPRECATED(zpl_buffer_free): Use zpl_buffer_free2 instead
        #define zpl_buffer_free(x, allocator) (zpl_free(allocator, ZPL_BUFFER_HEADER(x)))
        #define zpl_buffer_free2(x) (zpl_free(ZPL_BUFFER_HEADER(x)->backing, ZPL_BUFFER_HEADER(x)))

        #define zpl_buffer_append(x, item)                                                                                     \
        do { (x)[zpl_buffer_count(x)++] = (item); } while (0)

        #define zpl_buffer_appendv(x, items, item_count)                                                                       \
        do {                                                                                                               \
            ZPL_ASSERT(zpl_size_of(*(items)) == zpl_size_of(*(x)));                                                        \
            ZPL_ASSERT(zpl_buffer_count(x) + item_count <= zpl_buffer_capacity(x));                                        \
            zpl_memcopy(&(x)[zpl_buffer_count(x)], (items), zpl_size_of(*(x)) * (item_count));                             \
            zpl_buffer_count(x) += (item_count);                                                                           \
        } while (0)

        #define zpl_buffer_copy_init(y, x)                                                                                     \
        do {                                                                                                               \
            zpl_buffer_init_reserve(y, zpl_buffer_allocator(x), zpl_buffer_capacity(x));                                   \
            zpl_memcopy(y, x, zpl_buffer_capacity(x) * zpl_size_of(*x));                                                   \
            zpl_buffer_count(y) = zpl_buffer_count(x);                                                                     \
        } while (0)

        #define zpl_buffer_pop(x)                                                                                              \
        do {                                                                                                               \
            ZPL_ASSERT(zpl_buffer_count(x) > 0);                                                                           \
            zpl_buffer_count(x)--;                                                                                         \
        } while (0)
        #define zpl_buffer_clear(x)                                                                                            \
        do { zpl_buffer_count(x) = 0; } while (0)

        ZPL_END_C_DECLS
        // file: header/core/collections/list.h

        ////////////////////////////////////////////////////////////////
        //
        // Linked List
        //
        // zpl_list encapsulates pointer to data and points to the next and the previous element in the list.
        //
        // Available Procedures for zpl_list
        // zpl_list_init
        // zpl_list_add
        // zpl_list_remove

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if 0
        #define ZPL_IMPLEMENTATION
        #include "zpl.h"
        int main(void)
        {
            zpl_list s, *head, *cursor;
            zpl_list_init(&s, "it is optional to call init: ");
            head = cursor = &s;

            // since we can construct an element implicitly this way
            // the second field gets overwritten once we add it to a list.
            zpl_list a = {"hello"};
            cursor = zpl_list_add(cursor, &a);

            zpl_list b = {"world"};
            cursor = zpl_list_add(cursor, &b);

            zpl_list c = {"!!! OK"};
            cursor = zpl_list_add(cursor, &c);

            for (zpl_list *l=head; l; l=l->next) {
                zpl_printf("%s ", cast(char *)l->ptr);
            }
            zpl_printf("\n");

            return 0;
        }
        #endif


        typedef struct zpl__list {
            void const *ptr;
            struct zpl__list *next, *prev;
        } zpl_list;

        ZPL_DEF_INLINE void      zpl_list_init(zpl_list *list, void const *ptr);
        ZPL_DEF_INLINE zpl_list *zpl_list_add(zpl_list *list, zpl_list *item);

        // NOTE(zaklaus): Returns a pointer to the next node (or NULL if the removed node has no trailing node.)
        ZPL_DEF_INLINE zpl_list *zpl_list_remove(zpl_list *list);


        ZPL_IMPL_INLINE void zpl_list_init(zpl_list *list, void const *ptr) {
            zpl_list list_ = { 0 };
            *list = list_;
            list->ptr = ptr;
        }

        ZPL_IMPL_INLINE zpl_list *zpl_list_add(zpl_list *list, zpl_list *item) {
            item->next = NULL;

            if (list->next) { item->next = list->next; }

            list->next = item;
            item->prev = list;
            return item;
        }

        ZPL_IMPL_INLINE zpl_list *zpl_list_remove(zpl_list *list) {
            if (list->prev) { list->prev->next = list->next; }

            return list->next;
        }

        ZPL_END_C_DECLS
        // file: header/core/collections/ring.h

        ////////////////////////////////////////////////////////////////
        //
        // Instantiated Circular buffer
        //
        /*
        int main()
        {
            zpl_ring_zpl_u32 pad={0};
            zpl_ring_zpl_u32_init(&pad, zpl_heap(), 3);
            zpl_ring_zpl_u32_append(&pad, 1);
            zpl_ring_zpl_u32_append(&pad, 2);
            zpl_ring_zpl_u32_append(&pad, 3);

            while (!zpl_ring_zpl_u32_empty(&pad)) {
                zpl_printf("Result is %d\n", *zpl_ring_zpl_u32_get(&pad));
            }

            zpl_ring_zpl_u32_free(&pad);

            return 0;
        }
        */

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #define ZPL_RING_DECLARE(type)                                                                                         \
        typedef struct {                                                                                                   \
            zpl_allocator backing;                                                                                         \
            zpl_buffer(type) buf;                                                                                          \
            zpl_usize head, tail;                                                                                              \
            zpl_usize capacity;                                                                                                \
        } ZPL_JOIN2(zpl_ring_, type);                                                                                      \
        \
        ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _init)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_allocator a, zpl_isize max_size); \
        ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _free)(ZPL_JOIN2(zpl_ring_, type) * pad);                                  \
        ZPL_DEF zpl_b32 ZPL_JOIN3(zpl_ring_, type, _full)(ZPL_JOIN2(zpl_ring_, type) * pad);                                   \
        ZPL_DEF zpl_b32 ZPL_JOIN3(zpl_ring_, type, _empty)(ZPL_JOIN2(zpl_ring_, type) * pad);                                  \
        ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _append)(ZPL_JOIN2(zpl_ring_, type) * pad, type data);                     \
        ZPL_DEF void ZPL_JOIN3(zpl_ring_, type, _append_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_array(type) data);    \
        ZPL_DEF type *ZPL_JOIN3(zpl_ring_, type, _get)(ZPL_JOIN2(zpl_ring_, type) * pad);                                  \
        ZPL_DEF zpl_array(type)                                                                                            \
        ZPL_JOIN3(zpl_ring_, type, _get_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_usize max_size, zpl_allocator a);

        #define ZPL_RING_DEFINE(type)                                                                                          \
        void ZPL_JOIN3(zpl_ring_, type, _init)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_allocator a, zpl_isize max_size) {        \
            ZPL_JOIN2(zpl_ring_, type) pad_ = { 0 };                                                                       \
            *pad = pad_;                                                                                                   \
            \
            pad->backing = a;                                                                                              \
            zpl_buffer_init(pad->buf, a, max_size + 1);                                                                    \
            pad->capacity = max_size + 1;                                                                                  \
            pad->head = pad->tail = 0;                                                                                     \
        }                                                                                                                  \
        void ZPL_JOIN3(zpl_ring_, type, _free)(ZPL_JOIN2(zpl_ring_, type) * pad) {                                         \
            zpl_buffer_free(pad->buf, pad->backing);                                                                       \
        }                                                                                                                  \
        \
        zpl_b32 ZPL_JOIN3(zpl_ring_, type, _full)(ZPL_JOIN2(zpl_ring_, type) * pad) {                                          \
            return ((pad->head + 1) % pad->capacity) == pad->tail;                                                         \
        }                                                                                                                  \
        \
        zpl_b32 ZPL_JOIN3(zpl_ring_, type, _empty)(ZPL_JOIN2(zpl_ring_, type) * pad) { return pad->head == pad->tail; }        \
        \
        void ZPL_JOIN3(zpl_ring_, type, _append)(ZPL_JOIN2(zpl_ring_, type) * pad, type data) {                            \
            pad->buf[pad->head] = data;                                                                                    \
            pad->head = (pad->head + 1) % pad->capacity;                                                                   \
            \
            if (pad->head == pad->tail) { pad->tail = (pad->tail + 1) % pad->capacity; }                                   \
        }                                                                                                                  \
        \
        void ZPL_JOIN3(zpl_ring_, type, _append_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_array(type) data) {           \
            zpl_usize c = zpl_array_count(data);                                                                               \
            for (zpl_usize i = 0; i < c; ++i) { ZPL_JOIN3(zpl_ring_, type, _append)(pad, data[i]); }                           \
        }                                                                                                                  \
        \
        type *ZPL_JOIN3(zpl_ring_, type, _get)(ZPL_JOIN2(zpl_ring_, type) * pad) {                                         \
            if (ZPL_JOIN3(zpl_ring_, type, _empty)(pad)) { return NULL; }                                                  \
            \
            type *data = &pad->buf[pad->tail];                                                                             \
            pad->tail = (pad->tail + 1) % pad->capacity;                                                                   \
            \
            return data;                                                                                                   \
        }                                                                                                                  \
        \
        zpl_array(type)                                                                                                    \
        ZPL_JOIN3(zpl_ring_, type, _get_array)(ZPL_JOIN2(zpl_ring_, type) * pad, zpl_usize max_size, zpl_allocator a) {    \
            zpl_array(type) vals;                                                                                          \
            zpl_array_init(vals, a);                                                                                       \
            while (--max_size && !ZPL_JOIN3(zpl_ring_, type, _empty)(pad)) {                                               \
                zpl_array_append(vals, *ZPL_JOIN3(zpl_ring_, type, _get)(pad));                                            \
            }                                                                                                              \
            return vals;                                                                                                   \
        }

        ZPL_END_C_DECLS
        // file: header/core/collections/hashtable.h

        /** @file hashtable.c
        @brief Instantiated hash table
        @defgroup hashtable Instantiated hash table

        @n
        @n This is an attempt to implement a templated hash table
        @n NOTE: The key is always a zpl_u64 for simplicity and you will _probably_ _never_ need anything bigger.
        @n
        @n Hash table type and function declaration, call: ZPL_TABLE_DECLARE(PREFIX, NAME, N, VALUE)
        @n Hash table function definitions, call: ZPL_TABLE_DEFINE(NAME, N, VALUE)
        @n
        @n     PREFIX  - a prefix for function prototypes e.g. extern, static, etc.
        @n     NAME    - Name of the Hash Table
        @n     FUNC    - the name will prefix function names
        @n     VALUE   - the type of the value to be stored
        @n
        @n tablename_init(NAME * h, zpl_allocator a);
        @n tablename_destroy(NAME * h);
        @n tablename_get(NAME * h, zpl_u64 key);
        @n tablename_set(NAME * h, zpl_u64 key, VALUE value);
        @n tablename_grow(NAME * h);
        @n tablename_rehash(NAME * h, zpl_isize new_count);
        @n tablename_remove(NAME * h, zpl_u64 key);

         @{
        */

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_hash_table_find_result {
            zpl_isize hash_index;
            zpl_isize entry_prev;
            zpl_isize entry_index;
        } zpl_hash_table_find_result;

        #define ZPL_TABLE(PREFIX, NAME, FUNC, VALUE)                                                                           \
        ZPL_TABLE_DECLARE(PREFIX, NAME, FUNC, VALUE);                                                                      \
        ZPL_TABLE_DEFINE(NAME, FUNC, VALUE);

        #define ZPL_TABLE_DECLARE(PREFIX, NAME, FUNC, VALUE)                                                                   \
        typedef struct ZPL_JOIN2(NAME, Entry) {                                                                            \
            zpl_u64 key;                                                                                                       \
            zpl_isize next;                                                                                                    \
            VALUE value;                                                                                                   \
        } ZPL_JOIN2(NAME, Entry);                                                                                          \
        \
        typedef struct NAME {                                                                                              \
            zpl_array(zpl_isize) hashes;                                                                                       \
            zpl_array(ZPL_JOIN2(NAME, Entry)) entries;                                                                     \
        } NAME;                                                                                                            \
        \
        PREFIX void ZPL_JOIN2(FUNC, init)(NAME * h, zpl_allocator a);                                                      \
        PREFIX void ZPL_JOIN2(FUNC, destroy)(NAME * h);                                                                    \
        PREFIX VALUE *ZPL_JOIN2(FUNC, get)(NAME * h, zpl_u64 key);                                                             \
        PREFIX void ZPL_JOIN2(FUNC, set)(NAME * h, zpl_u64 key, VALUE value);                                                  \
        PREFIX void ZPL_JOIN2(FUNC, grow)(NAME * h);                                                                       \
        PREFIX void ZPL_JOIN2(FUNC, rehash)(NAME * h, zpl_isize new_count);                                                    \
        PREFIX void ZPL_JOIN2(FUNC, remove)(NAME * h, zpl_u64 key);

        #define ZPL_TABLE_DEFINE(NAME, FUNC, VALUE)                                                                            \
        void ZPL_JOIN2(FUNC, init)(NAME * h, zpl_allocator a) {                                                            \
            zpl_array_init(h->hashes, a);                                                                                  \
            zpl_array_init(h->entries, a);                                                                                 \
        }                                                                                                                  \
        \
        void ZPL_JOIN2(FUNC, destroy)(NAME * h) {                                                                          \
            if (h->entries) zpl_array_free(h->entries);                                                                    \
            if (h->hashes) zpl_array_free(h->hashes);                                                                      \
        }                                                                                                                  \
        \
        zpl_internal zpl_isize ZPL_JOIN2(FUNC, _add_entry)(NAME * h, zpl_u64 key) {                                                \
            zpl_isize index;                                                                                                   \
            ZPL_JOIN2(NAME, Entry) e = { 0 };                                                                              \
            e.key = key;                                                                                                   \
            e.next = -1;                                                                                                   \
            index = zpl_array_count(h->entries);                                                                           \
            zpl_array_append(h->entries, e);                                                                               \
            return index;                                                                                                  \
        }                                                                                                                  \
        \
        zpl_internal zpl_hash_table_find_result ZPL_JOIN2(FUNC, _find)(NAME * h, zpl_u64 key) {                                \
            zpl_hash_table_find_result r = { -1, -1, -1 };                                                                 \
            if (zpl_array_count(h->hashes) > 0) {                                                                          \
                r.hash_index = key % zpl_array_count(h->hashes);                                                           \
                r.entry_index = h->hashes[r.hash_index];                                                                   \
                while (r.entry_index >= 0) {                                                                               \
                    if (h->entries[r.entry_index].key == key) return r;                                                    \
                    r.entry_prev = r.entry_index;                                                                          \
                    r.entry_index = h->entries[r.entry_index].next;                                                        \
                }                                                                                                          \
            }                                                                                                              \
            return r;                                                                                                      \
        }                                                                                                                  \
        \
        zpl_internal zpl_b32 ZPL_JOIN2(FUNC, _full)(NAME * h) {                                                                \
            return 0.75f * zpl_array_count(h->hashes) < zpl_array_count(h->entries);                                       \
        }                                                                                                                  \
        \
        void ZPL_JOIN2(FUNC, grow)(NAME * h) {                                                                             \
            zpl_isize new_count = ZPL_ARRAY_GROW_FORMULA(zpl_array_count(h->entries));                                         \
            ZPL_JOIN2(FUNC, rehash)(h, new_count);                                                                         \
        }                                                                                                                  \
        \
        void ZPL_JOIN2(FUNC, rehash)(NAME * h, zpl_isize new_count) {                                                          \
            zpl_isize i, j;                                                                                                    \
            NAME nh = { 0 };                                                                                               \
            ZPL_JOIN2(FUNC, init)(&nh, zpl_array_allocator(h->hashes));                                                    \
            zpl_array_resize(nh.hashes, new_count);                                                                        \
            zpl_array_reserve(nh.entries, zpl_array_count(h->entries));                                                    \
            for (i = 0; i < new_count; i++) nh.hashes[i] = -1;                                                             \
            for (i = 0; i < zpl_array_count(h->entries); i++) {                                                            \
                ZPL_JOIN2(NAME, Entry) * e;                                                                                \
                zpl_hash_table_find_result fr;                                                                             \
                if (zpl_array_count(nh.hashes) == 0) ZPL_JOIN2(FUNC, grow)(&nh);                                           \
                e = &h->entries[i];                                                                                        \
                fr = ZPL_JOIN2(FUNC, _find)(&nh, e->key);                                                                  \
                j = ZPL_JOIN2(FUNC, _add_entry)(&nh, e->key);                                                              \
                if (fr.entry_prev < 0)                                                                                     \
                nh.hashes[fr.hash_index] = j;                                                                          \
                else                                                                                                       \
                nh.entries[fr.entry_prev].next = j;                                                                    \
                nh.entries[j].next = fr.entry_index;                                                                       \
                nh.entries[j].value = e->value;                                                                            \
            }                                                                                                              \
            ZPL_JOIN2(FUNC, destroy)(h);                                                                                   \
            h->hashes = nh.hashes;                                                                                         \
            h->entries = nh.entries;                                                                                       \
        }                                                                                                                  \
        \
        VALUE *ZPL_JOIN2(FUNC, get)(NAME * h, zpl_u64 key) {                                                                   \
            zpl_isize index = ZPL_JOIN2(FUNC, _find)(h, key).entry_index;                                                      \
            if (index >= 0) return &h->entries[index].value;                                                               \
            return NULL;                                                                                                   \
        }                                                                                                                  \
        \
        void ZPL_JOIN2(FUNC, remove)(NAME * h, zpl_u64 key) {                                                                  \
            zpl_hash_table_find_result fr = ZPL_JOIN2(FUNC, _find)(h, key);                                                \
            if (fr.entry_index >= 0) {                                                                                     \
                if (fr.entry_prev >= 0) {                                                                                  \
                    h->entries[fr.entry_prev].next = h->entries[fr.entry_index].next;                                      \
                } else {                                                                                                   \
                    h->hashes[fr.hash_index] = fr.entry_index;                                                             \
                }                                                                                                          \
                zpl_array_remove_at(h->entries, fr.entry_index);                                                           \
            }                                                                                                              \
            ZPL_JOIN2(FUNC, rehash)(h, zpl_array_count(h->entries));                                                       \
        }                                                                                                                  \
        \
        void ZPL_JOIN2(FUNC, set)(NAME * h, zpl_u64 key, VALUE value) {                                                        \
            zpl_isize index;                                                                                                   \
            zpl_hash_table_find_result fr;                                                                                 \
            if (zpl_array_count(h->hashes) == 0) ZPL_JOIN2(FUNC, grow)(h);                                                 \
            fr = ZPL_JOIN2(FUNC, _find)(h, key);                                                                           \
            if (fr.entry_index >= 0) {                                                                                     \
                index = fr.entry_index;                                                                                    \
            } else {                                                                                                       \
                index = ZPL_JOIN2(FUNC, _add_entry)(h, key);                                                               \
                if (fr.entry_prev >= 0) {                                                                                  \
                    h->entries[fr.entry_prev].next = index;                                                                \
                } else {                                                                                                   \
                    h->hashes[fr.hash_index] = index;                                                                      \
                }                                                                                                          \
            }                                                                                                              \
            h->entries[index].value = value;                                                                               \
            if (ZPL_JOIN2(FUNC, _full)(h)) ZPL_JOIN2(FUNC, grow)(h);                                                       \
        }\

        //! @}

        ZPL_END_C_DECLS
        // file: header/core/string.h

        /** @file string.c
        @brief String operations and library
        @defgroup string String library

        Offers methods for c-string manipulation, but also a string library based on gb_string, which is c-string friendly.

        @{
        */

        ////////////////////////////////////////////////////////////////
        //
        // Char Functions
        //
        //

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_DEF_INLINE char    zpl_char_to_lower(char c);
        ZPL_DEF_INLINE char    zpl_char_to_upper(char c);
        ZPL_DEF_INLINE zpl_b32 zpl_char_is_space(char c);
        ZPL_DEF_INLINE zpl_b32 zpl_char_is_digit(char c);
        ZPL_DEF_INLINE zpl_b32 zpl_char_is_hex_digit(char c);
        ZPL_DEF_INLINE zpl_b32 zpl_char_is_alpha(char c);
        ZPL_DEF_INLINE zpl_b32 zpl_char_is_alphanumeric(char c);
        ZPL_DEF_INLINE zpl_i32 zpl_digit_to_int(char c);
        ZPL_DEF_INLINE zpl_i32 zpl_hex_digit_to_int(char c);
        ZPL_DEF_INLINE zpl_u8  zpl_char_to_hex_digit(char c);
        ZPL_DEF_INLINE zpl_b32 zpl_char_is_control(char c);

        // NOTE: ASCII only
        ZPL_DEF_INLINE void zpl_str_to_lower(char *str);
        ZPL_DEF_INLINE void zpl_str_to_upper(char *str);

        ZPL_DEF_INLINE char *zpl_str_trim(char *str, zpl_b32 skip_newline);
        ZPL_DEF_INLINE char *zpl_str_skip(char *str, char c);
        ZPL_DEF_INLINE char *zpl_str_control_skip(char *str, char c);

        ZPL_DEF_INLINE zpl_isize   zpl_strlen(const char *str);
        ZPL_DEF_INLINE zpl_isize   zpl_strnlen(const char *str, zpl_isize max_len);
        ZPL_DEF_INLINE zpl_i32     zpl_strcmp(const char *s1, const char *s2);
        ZPL_DEF_INLINE zpl_i32     zpl_strncmp(const char *s1, const char *s2, zpl_isize len);
        ZPL_DEF_INLINE char       *zpl_strcpy(char *dest, const char *source);
        ZPL_DEF_INLINE char       *zpl_strncpy(char *dest, const char *source, zpl_isize len);
        ZPL_DEF_INLINE zpl_isize   zpl_strlcpy(char *dest, const char *source, zpl_isize len);
        ZPL_DEF_INLINE char       *zpl_strrev(char *str); // NOTE: ASCII only
        ZPL_DEF_INLINE const char *zpl_strtok(char *output, const char *src, const char *delimit);

        ZPL_DEF_INLINE char   *zpl_strdup(zpl_allocator a, char *src, zpl_isize max_len);
        ZPL_DEF_INLINE char  **zpl_str_split_lines(zpl_allocator alloc, char *source, zpl_b32 strip_whitespace);

        #define zpl_str_expand(str) str, zpl_strlen(str)

        ZPL_DEF_INLINE zpl_b32 zpl_str_has_prefix(const char *str, const char *prefix);
        ZPL_DEF_INLINE zpl_b32 zpl_str_has_suffix(const char *str, const char *suffix);

        ZPL_DEF_INLINE const char *zpl_char_first_occurence(const char *str, char c);
        ZPL_DEF_INLINE const char *zpl_char_last_occurence(const char *str, char c);
        #define zpl_strchr zpl_char_first_occurence

        ZPL_DEF_INLINE void zpl_str_concat(char *dest, zpl_isize dest_len, const char *src_a, zpl_isize src_a_len, const char *src_b, zpl_isize src_b_len);

        ZPL_DEF zpl_u64 zpl_str_to_u64(const char *str, char **end_ptr, zpl_i32 base); // TODO: Support more than just decimal and hexadecimal
        ZPL_DEF zpl_i64 zpl_str_to_i64(const char *str, char **end_ptr, zpl_i32 base); // TODO: Support more than just decimal and hexadecimal
        ZPL_DEF zpl_f64 zpl_str_to_f64(const char *str, char **end_ptr);
        ZPL_DEF void    zpl_i64_to_str(zpl_i64 value, char *string, zpl_i32 base);
        ZPL_DEF void    zpl_u64_to_str(zpl_u64 value, char *string, zpl_i32 base);

        ZPL_DEF_INLINE zpl_f32 zpl_str_to_f32(const char *str, char **end_ptr);

        ////////////////////////////////////////////////////////////////
        //
        // UTF-8 Handling
        //
        //

        // NOTE: Does not check if utf-8 string is valid
        ZPL_IMPL_INLINE zpl_isize zpl_utf8_strlen(zpl_u8 const *str);
        ZPL_IMPL_INLINE zpl_isize zpl_utf8_strnlen(zpl_u8 const *str, zpl_isize max_len);

        // NOTE: Windows doesn't handle 8 bit filenames well
        ZPL_DEF zpl_u16 *zpl_utf8_to_ucs2(zpl_u16 *buffer, zpl_isize len, zpl_u8 const *str);
        ZPL_DEF zpl_u8  *zpl_ucs2_to_utf8(zpl_u8 *buffer, zpl_isize len, zpl_u16 const *str);
        ZPL_DEF zpl_u16 *zpl_utf8_to_ucs2_buf(zpl_u8 const *str); // NOTE: Uses locally persisting buffer
        ZPL_DEF zpl_u8  *zpl_ucs2_to_utf8_buf(zpl_u16 const *str); // NOTE: Uses locally persisting buffer

        // NOTE: Returns size of codepoint in bytes
        ZPL_DEF zpl_isize zpl_utf8_decode(zpl_u8 const *str, zpl_isize str_len, zpl_rune *codepoint);
        ZPL_DEF zpl_isize zpl_utf8_codepoint_size(zpl_u8 const *str, zpl_isize str_len);
        ZPL_DEF zpl_isize zpl_utf8_encode_rune(zpl_u8 buf[4], zpl_rune r);

        /* inlines */

        ZPL_IMPL_INLINE char zpl_char_to_lower(char c) {
            if (c >= 'A' && c <= 'Z') return 'a' + (c - 'A');
            return c;
        }

        ZPL_IMPL_INLINE char zpl_char_to_upper(char c) {
            if (c >= 'a' && c <= 'z') return 'A' + (c - 'a');
            return c;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_char_is_space(char c) {
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v') return true;
            return false;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_char_is_digit(char c) {
            if (c >= '0' && c <= '9') return true;
            return false;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_char_is_hex_digit(char c) {
            if (zpl_char_is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return true;
            return false;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_char_is_alpha(char c) {
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
            return false;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_char_is_alphanumeric(char c) { return zpl_char_is_alpha(c) || zpl_char_is_digit(c); }

        ZPL_IMPL_INLINE zpl_i32 zpl_digit_to_int(char c) { return zpl_char_is_digit(c) ? c - '0' : c - 'W'; }

        ZPL_IMPL_INLINE zpl_i32 zpl_hex_digit_to_int(char c) {
            if (zpl_char_is_digit(c))
                return zpl_digit_to_int(c);
            else if (zpl_is_between(c, 'a', 'f'))
                return c - 'a' + 10;
            else if (zpl_is_between(c, 'A', 'F'))
                return c - 'A' + 10;
            return -1;
        }

        ZPL_IMPL_INLINE zpl_u8 zpl_char_to_hex_digit(char c) {
            if (c >= '0' && c <= '9')
                return (zpl_u8)(c - '0');
            if (c >= 'a' && c <= 'f')
                return (zpl_u8)(c - 'a');
            if (c >= 'A' && c <= 'F')
                return (zpl_u8)(c - 'A');
            return 0;
        }


        ZPL_IMPL_INLINE void zpl_str_to_lower(char *str) {
            if (!str) return;
            while (*str) {
                *str = zpl_char_to_lower(*str);
                str++;
            }
        }

        ZPL_IMPL_INLINE void zpl_str_to_upper(char *str) {
            if (!str) return;
            while (*str) {
                *str = zpl_char_to_upper(*str);
                str++;
            }
        }

        ZPL_IMPL_INLINE zpl_isize zpl_strlen(const char *str) {
            if (str == NULL) { return 0; }

            const char *begin = str;
            zpl_isize const *w;
            while (cast(zpl_uintptr) str % sizeof(zpl_usize)) {
                if (!*str) return str - begin;
                str++;
            }
            w = cast(zpl_isize const *) str;
            while (!ZPL__HAS_ZERO(*w)) w++;
            str = cast(const char *) w;
            while (*str) str++;
            return str - begin;
        }

        ZPL_IMPL_INLINE zpl_isize zpl_strnlen(const char *str, zpl_isize max_len) {
            const char *end = cast(const char *) zpl_memchr(str, 0, max_len);
            if (end) return end - str;
            return max_len;
        }

        ZPL_IMPL_INLINE zpl_isize zpl_utf8_strlen(zpl_u8 const *str) {
            zpl_isize count = 0;
            for (; *str; count++) {
                zpl_u8 c = *str;
                zpl_isize inc = 0;
                if (c < 0x80)
                    inc = 1;
                else if ((c & 0xe0) == 0xc0)
                    inc = 2;
                else if ((c & 0xf0) == 0xe0)
                    inc = 3;
                else if ((c & 0xf8) == 0xf0)
                    inc = 4;
                else
                    return -1;

                str += inc;
            }
            return count;
        }

        ZPL_IMPL_INLINE zpl_isize zpl_utf8_strnlen(zpl_u8 const *str, zpl_isize max_len) {
            zpl_isize count = 0;
            for (; *str && max_len > 0; count++) {
                zpl_u8 c = *str;
                zpl_isize inc = 0;
                if (c < 0x80)
                    inc = 1;
                else if ((c & 0xe0) == 0xc0)
                    inc = 2;
                else if ((c & 0xf0) == 0xe0)
                    inc = 3;
                else if ((c & 0xf8) == 0xf0)
                    inc = 4;
                else
                    return -1;

                str += inc;
                max_len -= inc;
            }
            return count;
        }

        ZPL_IMPL_INLINE zpl_i32 zpl_strcmp(const char *s1, const char *s2) {
            while (*s1 && (*s1 == *s2)) { s1++, s2++; }
            return *(zpl_u8 *)s1 - *(zpl_u8 *)s2;
        }

        ZPL_IMPL_INLINE char *zpl_strcpy(char *dest, const char *source) {
            ZPL_ASSERT_NOT_NULL(dest);
            if (source) {
                char *str = dest;
                while (*source) *str++ = *source++;
            }
            return dest;
        }

        ZPL_IMPL_INLINE char *zpl_strncpy(char *dest, const char *source, zpl_isize len) {
            ZPL_ASSERT_NOT_NULL(dest);
            if (source) {
                char *str = dest;
                while (len > 0 && *source) {
                    *str++ = *source++;
                    len--;
                }
                while (len > 0) {
                    *str++ = '\0';
                    len--;
                }
            }
            return dest;
        }

        ZPL_IMPL_INLINE zpl_isize zpl_strlcpy(char *dest, const char *source, zpl_isize len) {
            zpl_isize result = 0;
            ZPL_ASSERT_NOT_NULL(dest);
            if (source) {
                const char *source_start = source;
                char *str = dest;
                while (len > 0 && *source) {
                    *str++ = *source++;
                    len--;
                }
                while (len > 0) {
                    *str++ = '\0';
                    len--;
                }

                result = source - source_start;
            }
            return result;
        }

        ZPL_IMPL_INLINE char *zpl_strrev(char *str) {
            zpl_isize len = zpl_strlen(str);
            char *a = str + 0;
            char *b = str + len - 1;
            len /= 2;
            while (len--) {
                zpl_swap(char, *a, *b);
                a++, b--;
            }
            return str;
        }

        ZPL_IMPL_INLINE zpl_i32 zpl_strncmp(const char *s1, const char *s2, zpl_isize len) {
            for (; len > 0; s1++, s2++, len--) {
                if (*s1 != *s2)
                    return ((s1 < s2) ? -1 : +1);
                else if (*s1 == '\0')
                    return 0;
            }
            return 0;
        }

        ZPL_IMPL_INLINE const char *zpl_strtok(char *output, const char *src, const char *delimit) {
            while (*src && zpl_char_first_occurence(delimit, *src) == NULL) *output++ = *src++;

            *output = 0;
            return *src ? src + 1 : src;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_char_is_control(char c) {
            return !!zpl_strchr("\"\\/bfnrt", c);
        }

        ZPL_IMPL_INLINE zpl_b32 zpl__is_special_char(char c) { return !!zpl_strchr("<>:/", c); }
        ZPL_IMPL_INLINE zpl_b32 zpl__is_assign_char(char c) { return !!zpl_strchr(":=|", c); }
        ZPL_IMPL_INLINE zpl_b32 zpl__is_delim_char(char c) { return !!zpl_strchr(",|\n", c); }


        ZPL_IMPL_INLINE char *zpl_str_control_skip(char *str, char c) {
            while ((*str && *str != c) || (*(str - 1) == '\\' && *str == c && zpl_char_is_control(c))) { ++str; }

            return str;
        }


        ZPL_IMPL_INLINE zpl_b32 zpl_str_has_prefix(const char *str, const char *prefix) {
            while (*prefix) {
                if (*str++ != *prefix++) return false;
            }
            return true;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_str_has_suffix(const char *str, const char *suffix) {
            zpl_isize i = zpl_strlen(str);
            zpl_isize j = zpl_strlen(suffix);
            if (j <= i) return zpl_strcmp(str + i - j, suffix) == 0;
            return false;
        }

        ZPL_IMPL_INLINE const char *zpl_char_first_occurence(const char *s, char c) {
            char ch = c;
            for (; *s != ch; s++) {
                if (*s == '\0') return NULL;
            }
            return s;
        }

        ZPL_IMPL_INLINE const char *zpl_char_last_occurence(const char *s, char c) {
            char *result = (char*)NULL;
            do {
                if (*s == c) result = (char *)s;
            } while (*s++);

            return result;
        }

        ZPL_IMPL_INLINE char *zpl_str_trim(char *str, zpl_b32 skip_newline)
        {
            while (*str && zpl_char_is_space(*str) && (!skip_newline || (skip_newline && *str != '\n'))) { ++str; }
            return str;
        }

        ZPL_IMPL_INLINE char *zpl_str_skip(char *str, char c) {
            while (*str && *str != c) { ++str; }
            return str;
        }

        ZPL_IMPL_INLINE void zpl_str_concat(char *dest, zpl_isize dest_len, const char *src_a, zpl_isize src_a_len, const char *src_b,
                                       zpl_isize src_b_len) {
            ZPL_ASSERT(dest_len >= src_a_len + src_b_len + 1);
            if (dest) {
                zpl_memcopy(dest, src_a, src_a_len);
                zpl_memcopy(dest + src_a_len, src_b, src_b_len);
                dest[src_a_len + src_b_len] = '\0';
            }
        }

        ZPL_IMPL_INLINE zpl_f32 zpl_str_to_f32(const char *str, char **end_ptr) {
            zpl_f64 f = zpl_str_to_f64(str, end_ptr);
            zpl_f32 r = cast(zpl_f32) f;
            return r;
        }

        ZPL_IMPL_INLINE char *zpl_strdup(zpl_allocator a, char *src, zpl_isize max_len) {
            ZPL_ASSERT_NOT_NULL(src);
            zpl_isize len = zpl_strlen(src);
            char *dest = cast(char *) zpl_alloc(a, max_len);
            zpl_memset(dest + len, 0, max_len - len);
            zpl_strncpy(dest, src, max_len);

            return dest;
        }

        ZPL_IMPL_INLINE char **zpl_str_split_lines(zpl_allocator alloc, char *source, zpl_b32 strip_whitespace) {
            char **lines = NULL, *p = source, *pd = p;
            zpl_array_init(lines, alloc);

            while (*p) {
                if (*pd == '\n') {
                    *pd = 0;
                    if (*(pd - 1) == '\r') *(pd - 1) = 0;
                    if (strip_whitespace && (pd - p) == 0) {
                        p = pd + 1;
                        continue;
                    }
                    zpl_array_append(lines, p);
                    p = pd + 1;
                }
                ++pd;
            }
            return lines;
        }

        ZPL_END_C_DECLS
        // file: header/core/stringlib.h

        ////////////////////////////////////////////////////////////////
        //
        // zpl_string - C Read-Only-Compatible
        //
        //
        /*
            Reasoning:

            By default, strings in C are null terminated which means you have to count
            the number of character up to the null character to calculate the length.
            Many "better" C string libraries will create a struct for a string.
            i.e.

            struct String {
            Allocator allocator;
            size_t    length;
            size_t    capacity;
            char *    cstring;
            };

            This library tries to augment normal C strings in a better way that is still
            compatible with C-style strings.

            +--------+-----------------------+-----------------+
            | Header | Binary C-style String | Null Terminator |
            +--------+-----------------------+-----------------+
            |
            +-> Pointer returned by functions

            Due to the meta-data being stored before the string pointer and every zpl string
            having an implicit null terminator, zpl strings are full compatible with c-style
            strings and read-only functions.

            Advantages:

            * zpl strings can be passed to C-style string functions without accessing a struct
            member of calling a function, i.e.

            zpl_printf("%s\n", zpl_str);

            Many other libraries do either of these:

            zpl_printf("%s\n", string->cstr);
            zpl_printf("%s\n", get_cstring(string));

            * You can access each character just like a C-style string:

            zpl_printf("%c %c\n", str[0], str[13]);

            * zpl strings are singularly allocated. The meta-data is next to the character
            array which is better for the cache.

            Disadvantages:

            * In the C version of these functions, many return the new string. i.e.
            str = zpl_string_appendc(str, "another string");
            This could be changed to zpl_string_appendc(&str, "another string"); but I'm still not sure.
        */

        #if 0
        #define ZPL_IMPLEMENTATION
        #include "zpl.h"
        int main(int argc, char **argv) {
            zpl_string str = zpl_string_make("Hello");
            zpl_string other_str = zpl_string_make_length(", ", 2);
            str = zpl_string_append(str, other_str);
            str = zpl_string_appendc(str, "world!");

            zpl_printf("%s\n", str); // Hello, world!

            zpl_printf("str length = %d\n", zpl_string_length(str));

            str = zpl_string_set(str, "Potato soup");
            zpl_printf("%s\n", str); // Potato soup

            str = zpl_string_set(str, "Hello");
            other_str = zpl_string_set(other_str, "Pizza");
            if (zpl_strings_are_equal(str, other_str))
                zpl_printf("Not called\n");
            else
                zpl_printf("Called\n");

            str = zpl_string_set(str, "Ab.;!...AHello World       ??");
            str = zpl_string_trim(str, "Ab.;!. ?");
            zpl_printf("%s\n", str); // "Hello World"

            zpl_string_free(str);
            zpl_string_free(other_str);

            return 0;
        }
        #endif

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef char *zpl_string;

        typedef struct zpl_string_header {
            zpl_allocator allocator;
            zpl_isize length;
            zpl_isize capacity;
        } zpl_string_header;

        #define ZPL_STRING_HEADER(str) (cast(zpl_string_header *)(str) - 1)

        ZPL_DEF zpl_string zpl_string_make_reserve(zpl_allocator a, zpl_isize capacity);
        ZPL_DEF zpl_string zpl_string_make_length(zpl_allocator a, void const *str, zpl_isize num_bytes);
        ZPL_DEF zpl_string zpl_string_sprintf(zpl_allocator a, char *buf, zpl_isize num_bytes, const char *fmt, ...);
        ZPL_DEF zpl_string zpl_string_sprintf_buf(zpl_allocator a, const char *fmt, ...); // NOTE: Uses locally persistent buffer
        ZPL_DEF zpl_string zpl_string_append_length(zpl_string str, void const *other, zpl_isize num_bytes);
        ZPL_DEF zpl_string zpl_string_appendc(zpl_string str, const char *other);
        ZPL_DEF zpl_string zpl_string_join(zpl_allocator a, const char **parts, zpl_isize count, const char *glue);
        ZPL_DEF zpl_string zpl_string_set(zpl_string str, const char *cstr);
        ZPL_DEF zpl_string zpl_string_make_space_for(zpl_string str, zpl_isize add_len);
        ZPL_DEF zpl_isize  zpl_string_allocation_size(zpl_string const str);
        ZPL_DEF zpl_b32    zpl_string_are_equal(zpl_string const lhs, zpl_string const rhs);
        ZPL_DEF zpl_string zpl_string_trim(zpl_string str, const char *cut_set);
        ZPL_DEF zpl_string zpl_string_append_rune(zpl_string str, zpl_rune r);
        ZPL_DEF zpl_string zpl_string_append_fmt(zpl_string str, const char *fmt, ...);

        ZPL_DEF_INLINE zpl_string zpl_string_make(zpl_allocator a, const char *str);
        ZPL_DEF_INLINE void       zpl_string_free(zpl_string str);
        ZPL_DEF_INLINE void       zpl_string_clear(zpl_string str);
        ZPL_DEF_INLINE zpl_string zpl_string_duplicate(zpl_allocator a, zpl_string const str);
        ZPL_DEF_INLINE zpl_isize  zpl_string_length(zpl_string const str);
        ZPL_DEF_INLINE zpl_isize  zpl_string_capacity(zpl_string const str);
        ZPL_DEF_INLINE zpl_isize  zpl_string_available_space(zpl_string const str);
        ZPL_DEF_INLINE zpl_string zpl_string_append(zpl_string str, zpl_string const other);
        ZPL_DEF_INLINE zpl_string zpl_string_trim_space(zpl_string str); // Whitespace ` \t\r\n\v\f`
        ZPL_DEF_INLINE void       zpl__set_string_length(zpl_string str, zpl_isize len);
        ZPL_DEF_INLINE void       zpl__set_string_capacity(zpl_string str, zpl_isize cap);

        ZPL_IMPL_INLINE void zpl__set_string_length(zpl_string str, zpl_isize len) { ZPL_STRING_HEADER(str)->length = len; }
        ZPL_IMPL_INLINE void zpl__set_string_capacity(zpl_string str, zpl_isize cap) { ZPL_STRING_HEADER(str)->capacity = cap; }
        ZPL_IMPL_INLINE zpl_string zpl_string_make(zpl_allocator a, const char *str) {
            zpl_isize len = str ? zpl_strlen(str) : 0;
            return zpl_string_make_length(a, str, len);
        }

        ZPL_IMPL_INLINE void zpl_string_free(zpl_string str) {
            if (str) {
                zpl_string_header *header = ZPL_STRING_HEADER(str);
                zpl_free(header->allocator, header);
            }
        }

        ZPL_IMPL_INLINE zpl_string zpl_string_duplicate(zpl_allocator a, zpl_string const str) {
            return zpl_string_make_length(a, str, zpl_string_length(str));
        }

        ZPL_IMPL_INLINE zpl_isize zpl_string_length(zpl_string const str) { return ZPL_STRING_HEADER(str)->length; }
        ZPL_IMPL_INLINE zpl_isize zpl_string_capacity(zpl_string const str) { return ZPL_STRING_HEADER(str)->capacity; }

        ZPL_IMPL_INLINE zpl_isize zpl_string_available_space(zpl_string const str) {
            zpl_string_header *h = ZPL_STRING_HEADER(str);
            if (h->capacity > h->length) return h->capacity - h->length;
            return 0;
        }

        ZPL_IMPL_INLINE void zpl_string_clear(zpl_string str) {
            zpl__set_string_length(str, 0);
            str[0] = '\0';
        }

        ZPL_IMPL_INLINE zpl_string zpl_string_append(zpl_string str, zpl_string const other) {
            return zpl_string_append_length(str, other, zpl_string_length(other));
        }

        ZPL_IMPL_INLINE zpl_string zpl_string_trim_space(zpl_string str) { return zpl_string_trim(str, " \t\r\n\v\f"); }


        ZPL_END_C_DECLS
        // file: header/core/file.h

        /** @file file.c
        @brief File handling
        @defgroup fileio File handling

        File I/O operations as well as path and folder structure manipulation methods. With threading enabled, it also offers async read/write methods.

        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef zpl_u32 zpl_file_mode;

        typedef enum zpl_file_mode_flag {
            ZPL_FILE_MODE_READ   = ZPL_BIT(0),
            ZPL_FILE_MODE_WRITE  = ZPL_BIT(1),
            ZPL_FILE_MODE_APPEND = ZPL_BIT(2),
            ZPL_FILE_MODE_RW     = ZPL_BIT(3),
            ZPL_FILE_MODES       = ZPL_FILE_MODE_READ | ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW,
        } zpl_file_mode_flag;

        // NOTE: Only used internally and for the file operations
        typedef enum zpl_seek_whence_type {
            ZPL_SEEK_WHENCE_BEGIN   = 0,
            ZPL_SEEK_WHENCE_CURRENT = 1,
            ZPL_SEEK_WHENCE_END     = 2,
        } zpl_seek_whence_type;

        typedef enum zpl_file_error {
            ZPL_FILE_ERROR_NONE,
            ZPL_FILE_ERROR_INVALID,
            ZPL_FILE_ERROR_INVALID_FILENAME,
            ZPL_FILE_ERROR_EXISTS,
            ZPL_FILE_ERROR_NOT_EXISTS,
            ZPL_FILE_ERROR_PERMISSION,
            ZPL_FILE_ERROR_TRUNCATION_FAILURE,
            ZPL_FILE_ERROR_NOT_EMPTY,
            ZPL_FILE_ERROR_NAME_TOO_LONG,
            ZPL_FILE_ERROR_UNKNOWN,
        } zpl_file_error;

        typedef union zpl_file_descriptor {
            void *p;
            zpl_intptr i;
            zpl_uintptr u;
        } zpl_file_descriptor;

        typedef struct zpl_file_operations zpl_file_operations;

        #define ZPL_FILE_OPEN_PROC(name) zpl_file_error name(zpl_file_descriptor *fd, zpl_file_operations *ops, zpl_file_mode mode, char const *filename)
        #define ZPL_FILE_READ_AT_PROC(name) zpl_b32 name(zpl_file_descriptor fd, void *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_read, zpl_b32 stop_at_newline)
        #define ZPL_FILE_WRITE_AT_PROC(name) zpl_b32 name(zpl_file_descriptor fd, void const *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_written)
        #define ZPL_FILE_SEEK_PROC(name) zpl_b32 name(zpl_file_descriptor fd, zpl_i64 offset, zpl_seek_whence_type whence, zpl_i64 *new_offset)
        #define ZPL_FILE_CLOSE_PROC(name) void name(zpl_file_descriptor fd)

        typedef ZPL_FILE_OPEN_PROC(zpl_file_open_proc);
        typedef ZPL_FILE_READ_AT_PROC(zpl_file_read_proc);
        typedef ZPL_FILE_WRITE_AT_PROC(zpl_file_write_proc);
        typedef ZPL_FILE_SEEK_PROC(zpl_file_seek_proc);
        typedef ZPL_FILE_CLOSE_PROC(zpl_file_close_proc);

        struct zpl_file_operations {
            zpl_file_read_proc  *read_at;
            zpl_file_write_proc *write_at;
            zpl_file_seek_proc  *seek;
            zpl_file_close_proc *close;
        };

        extern zpl_file_operations const zpl_default_file_operations;

        typedef zpl_u64 zpl_file_time;
        typedef enum zpl_dir_type {
            ZPL_DIR_TYPE_FILE,
            ZPL_DIR_TYPE_FOLDER,
            ZPL_DIR_TYPE_UNKNOWN,
        } zpl_dir_type;

        struct zpl_dir_info;

        typedef struct zpl_dir_entry {
            char const *filename;
            struct zpl_dir_info *dir_info;
            zpl_u8 type;
        } zpl_dir_entry;

        typedef struct zpl_dir_info {
            char const    *fullpath;
            zpl_dir_entry *entries; // zpl_array

            // Internals
            char **filenames; // zpl_array
            zpl_string buf;
        } zpl_dir_info;

        typedef struct zpl_file {
            zpl_file_operations ops;
            zpl_file_descriptor fd;

            char const    *filename;
            zpl_file_time last_write_time;
            zpl_dir_entry *dir;
        } zpl_file;

        typedef enum zpl_file_standard_type {
            ZPL_FILE_STANDARD_INPUT,
            ZPL_FILE_STANDARD_OUTPUT,
            ZPL_FILE_STANDARD_ERROR,

            ZPL_FILE_STANDARD_COUNT,
        } zpl_file_standard_type;

        /**
         * Get standard file I/O.
         * @param  std Check zpl_file_standard_type
         * @return     File handle to standard I/O
         */
        ZPL_DEF zpl_file      *zpl_file_get_standard(zpl_file_standard_type std);

        /**
         * Connects a system handle to a ZPL file.
         * @param  file   Pointer to ZPL file
         * @param  handle Low-level OS handle to connect
         */
        ZPL_DEF void           zpl_file_connect_handle(zpl_file *file, void *handle);

        /**
         * Creates a new file
         * @param  file
         * @param  filename
         */
        ZPL_DEF zpl_file_error zpl_file_create(zpl_file *file, char const *filename);

        /**
         * Opens a file
         * @param  file
         * @param  filename
         */
        ZPL_DEF zpl_file_error zpl_file_open(zpl_file *file, char const *filename);

        /**
         * Opens a file using a specified mode
         * @param  file
         * @param  mode     Access mode to use
         * @param  filename
         */
        ZPL_DEF zpl_file_error zpl_file_open_mode(zpl_file *file, zpl_file_mode mode, char const *filename);

        /**
         * Constructs a new file from data
         * @param  file
         * @param  fd       Low-level file descriptor to use
         * @param  ops      File operations to rely upon
         * @param  filename
         */
        ZPL_DEF zpl_file_error zpl_file_new(zpl_file *file, zpl_file_descriptor fd, zpl_file_operations ops, char const *filename);

        /**
         * Returns a size of the file
         * @param  file
         * @return      File size
         */
        ZPL_DEF zpl_i64        zpl_file_size(zpl_file *file);

        /**
         * Returns the currently opened file's name
         * @param  file
         */
        ZPL_DEF char const    *zpl_file_name(zpl_file *file);

        /**
         * Truncates the file by a specified size
         * @param  file
         * @param  size Size to truncate
         */
        ZPL_DEF zpl_file_error zpl_file_truncate(zpl_file *file, zpl_i64 size);

        /**
         * Checks whether a file's been changed since the last check
         * @param  file
         */
        ZPL_DEF zpl_b32 zpl_file_has_changed(zpl_file *file);

        /**
         * Retrieves a directory listing relative to the file
         * @param file
         */
        ZPL_DEF void zpl_file_dirinfo_refresh(zpl_file *file);

        /**
         * Creates a temporary file
         * @param  file
         */
        zpl_file_error zpl_file_temp(zpl_file *file);

        /**
         * Closes the file
         * @param  file
         */
        ZPL_DEF zpl_file_error zpl_file_close(zpl_file *file);

        /**
         * Reads file safely
         * @param  file
         * @param  buffer     Buffer to read to
         * @param  size       Size to read
         * @param  offset     Offset to read from
         * @param  bytes_read How much data we've actually read
         */
        ZPL_DEF_INLINE zpl_b32 zpl_file_read_at_check(zpl_file *file, void *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_read);

        /**
         * Writes to file safely
         * @param  file
         * @param  buffer        Buffer to read from
         * @param  size          Size to write
         * @param  offset        Offset to write to
         * @param  bytes_written How much data we've actually written
         */
        ZPL_DEF_INLINE zpl_b32 zpl_file_write_at_check(zpl_file *file, void const *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_written);


        /**
         * Reads file at a specific offset
         * @param  file
         * @param  buffer     Buffer to read to
         * @param  size       Size to read
         * @param  offset     Offset to read from
         * @param  bytes_read How much data we've actually read
         */
        ZPL_DEF_INLINE zpl_b32 zpl_file_read_at(zpl_file *file, void *buffer, zpl_isize size, zpl_i64 offset);

        /**
         * Writes to file at a specific offset
         * @param  file
         * @param  buffer        Buffer to read from
         * @param  size          Size to write
         * @param  offset        Offset to write to
         * @param  bytes_written How much data we've actually written
         */
        ZPL_DEF_INLINE zpl_b32 zpl_file_write_at(zpl_file *file, void const *buffer, zpl_isize size, zpl_i64 offset);

        /**
         * Seeks the file cursor from the beginning of file to a specific position
         * @param  file
         * @param  offset Offset to seek to
         */
        ZPL_DEF_INLINE zpl_i64 zpl_file_seek(zpl_file *file, zpl_i64 offset);

        /**
         * Seeks the file cursor to the end of the file
         * @param  file
         */
        ZPL_DEF_INLINE zpl_i64 zpl_file_seek_to_end(zpl_file *file);

        /**
         * Skips N bytes at the current position
         * @param  file
         * @param  bytes Bytes to skip
         */
        ZPL_DEF_INLINE zpl_i64 zpl_file_skip(zpl_file *file, zpl_i64 bytes); // NOTE: Skips a certain amount of bytes

        /**
         * Returns the length from the beginning of the file we've read so far
         * @param  file
         * @return      Our current position in file
         */
        ZPL_DEF_INLINE zpl_i64 zpl_file_tell(zpl_file *file);

        /**
         * Reads from a file
         * @param  file
         * @param  buffer Buffer to read to
         * @param  size   Size to read
         */
        ZPL_DEF_INLINE zpl_b32 zpl_file_read(zpl_file *file, void *buffer, zpl_isize size);

        /**
         * Writes to a file
         * @param  file
         * @param  buffer Buffer to read from
         * @param  size   Size to read
         */
        ZPL_DEF_INLINE zpl_b32 zpl_file_write(zpl_file *file, void const *buffer, zpl_isize size);


        typedef struct zpl_file_contents {
            zpl_allocator allocator;
            void *data;
            zpl_isize size;
        } zpl_file_contents;

        /**
         * Reads the whole file contents
         * @param  a              Allocator to use
         * @param  zero_terminate End the read data with null terminator
         * @param  filepath       Path to the file
         * @return                File contents data
         */
        ZPL_DEF zpl_file_contents zpl_file_read_contents(zpl_allocator a, zpl_b32 zero_terminate, char const *filepath);

        /**
         * Frees the file content data previously read
         * @param  fc
         */
        ZPL_DEF void              zpl_file_free_contents(zpl_file_contents *fc);

        /**
         * Reads the file as array of lines
         *
         * Make sure you free both the returned buffer and the lines (zpl_array)
         * @param  alloc            Allocator to use
         * @param  lines            Reference to zpl_array container we store lines to
         * @param  filename         Path to the file
         * @param  strip_whitespace Strip whitespace when we split to lines?
         * @return                  File content we've read itself
         */
        ZPL_DEF char *zpl_file_read_lines(zpl_allocator alloc, zpl_array(char *)*lines, char const *filename, zpl_b32 strip_whitespace);

        //! @}

        /* inlines */


        ZPL_IMPL_INLINE zpl_b32 zpl_file_read_at_check(zpl_file *f, void *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_read) {
            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            return f->ops.read_at(f->fd, buffer, size, offset, bytes_read, false);
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_file_write_at_check(zpl_file *f, void const *buffer, zpl_isize size, zpl_i64 offset, zpl_isize *bytes_written) {
            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            return f->ops.write_at(f->fd, buffer, size, offset, bytes_written);
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_file_read_at(zpl_file *f, void *buffer, zpl_isize size, zpl_i64 offset) {
            return zpl_file_read_at_check(f, buffer, size, offset, NULL);
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_file_write_at(zpl_file *f, void const *buffer, zpl_isize size, zpl_i64 offset) {
            return zpl_file_write_at_check(f, buffer, size, offset, NULL);
        }

        ZPL_IMPL_INLINE zpl_i64 zpl_file_seek(zpl_file *f, zpl_i64 offset) {
            zpl_i64 new_offset = 0;
            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            f->ops.seek(f->fd, offset, ZPL_SEEK_WHENCE_BEGIN, &new_offset);
            return new_offset;
        }

        ZPL_IMPL_INLINE zpl_i64 zpl_file_seek_to_end(zpl_file *f) {
            zpl_i64 new_offset = 0;
            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            f->ops.seek(f->fd, 0, ZPL_SEEK_WHENCE_END, &new_offset);
            return new_offset;
        }

        // NOTE: Skips a certain amount of bytes
        ZPL_IMPL_INLINE zpl_i64 zpl_file_skip(zpl_file *f, zpl_i64 bytes) {
            zpl_i64 new_offset = 0;
            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            f->ops.seek(f->fd, bytes, ZPL_SEEK_WHENCE_CURRENT, &new_offset);
            return new_offset;
        }

        ZPL_IMPL_INLINE zpl_i64 zpl_file_tell(zpl_file *f) {
            zpl_i64 new_offset = 0;
            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            f->ops.seek(f->fd, 0, ZPL_SEEK_WHENCE_CURRENT, &new_offset);
            return new_offset;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_file_read(zpl_file *f, void *buffer, zpl_isize size) {
            zpl_i64 cur_offset = zpl_file_tell(f);
            zpl_b32 result = zpl_file_read_at(f, buffer, size, zpl_file_tell(f));
            zpl_file_seek(f, cur_offset + size);
            return result;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_file_write(zpl_file *f, void const *buffer, zpl_isize size) {
            zpl_i64 cur_offset = zpl_file_tell(f);
            zpl_b32 result = zpl_file_write_at(f, buffer, size, zpl_file_tell(f));
            zpl_file_seek(f, cur_offset + size);
            return result;
        }

        ZPL_END_C_DECLS
        // file: header/core/filesystem.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #ifndef ZPL_PATH_SEPARATOR
            #if defined(ZPL_SYSTEM_WINDOWS)
                #define ZPL_PATH_SEPARATOR '\\'
            #else
                #define ZPL_PATH_SEPARATOR '/'
            #endif
        #endif

        /**
         * Checks if file/directory exists
         * @param  filepath
         */
        ZPL_DEF zpl_b32       zpl_fs_exists(char const *filepath);

        /**
         * Retrieves node's type (file, folder, ...)
         * @param  path
         */
        ZPL_DEF zpl_u8        zpl_fs_get_type(char const *path);

        /**
         * Retrieves file's last write time
         * @param  filepath
         */
        ZPL_DEF zpl_file_time zpl_fs_last_write_time(char const *filepath);

        /**
         * Copies the file to a directory
         * @param  existing_filename
         * @param  new_filename
         * @param  fail_if_exists
         */
        ZPL_DEF zpl_b32       zpl_fs_copy(char const *existing_filename, char const *new_filename, zpl_b32 fail_if_exists);

        /**
         * Moves the file to a directory
         * @param  existing_filename
         * @param  new_filename
         */
        ZPL_DEF zpl_b32       zpl_fs_move(char const *existing_filename, char const *new_filename);

        /**
         * Removes a file from a directory
         * @param  filename
         */
        ZPL_DEF zpl_b32       zpl_fs_remove(char const *filename);

        ZPL_DEF_INLINE zpl_b32 zpl_path_is_absolute(char const *path);
        ZPL_DEF_INLINE zpl_b32 zpl_path_is_relative(char const *path);
        ZPL_DEF_INLINE zpl_b32 zpl_path_is_root(char const *path);

        ZPL_DEF_INLINE char const *zpl_path_base_name(char const *path);
        ZPL_DEF_INLINE char const *zpl_path_extension(char const *path);

        ZPL_DEF void    zpl_path_fix_slashes(char *path);

        ZPL_DEF zpl_file_error zpl_path_mkdir(char const *path, zpl_i32 mode);
        ZPL_DEF zpl_file_error zpl_path_rmdir(char const *path);

        ZPL_DEF char       *zpl_path_get_full_name(zpl_allocator a, char const *path);

        /**
         * Returns file paths terminated by newline (\n)
         * @param  alloc   [description]
         * @param  dirname [description]
         * @param  recurse [description]
         * @return         [description]
         */
        ZPL_DEF /*zpl_string*/char * zpl_path_dirlist(zpl_allocator alloc, char const *dirname, zpl_b32 recurse);

        /**
         * Initialize dirinfo from specified path
         * @param dir  [description]
         * @param path [description]
         */
        ZPL_DEF void zpl_dirinfo_init(zpl_dir_info *dir, char const *path);
        ZPL_DEF void zpl_dirinfo_free(zpl_dir_info *dir);

        /**
         * Analyze the entry's dirinfo
         * @param dir_entry [description]
         */
        ZPL_DEF void zpl_dirinfo_step(zpl_dir_entry *dir_entry);


        /* inlines */

        ZPL_IMPL_INLINE zpl_b32 zpl_path_is_absolute(char const *path) {
            zpl_b32 result = false;
            ZPL_ASSERT_NOT_NULL(path);
        #if defined(ZPL_SYSTEM_WINDOWS)
            result = (zpl_strlen(path) > 2) && zpl_char_is_alpha(path[0]) && (path[1] == ':' && path[2] == ZPL_PATH_SEPARATOR);
        #else
            result = (zpl_strlen(path) > 0 && path[0] == ZPL_PATH_SEPARATOR);
        #endif
            return result;
        }

        ZPL_IMPL_INLINE zpl_b32 zpl_path_is_relative(char const *path) { return !zpl_path_is_absolute(path); }

        ZPL_IMPL_INLINE zpl_b32 zpl_path_is_root(char const *path) {
            zpl_b32 result = false;
            ZPL_ASSERT_NOT_NULL(path);
        #if defined(ZPL_SYSTEM_WINDOWS)
            result = zpl_path_is_absolute(path) && (zpl_strlen(path) == 3);
        #else
            result = zpl_path_is_absolute(path) && (zpl_strlen(path) == 1);
        #endif
            return result;
        }

        ZPL_IMPL_INLINE char const *zpl_path_base_name(char const *path) {
            char const *ls;
            ZPL_ASSERT_NOT_NULL(path);
            zpl_path_fix_slashes((char *)path);
            ls = zpl_char_last_occurence(path, ZPL_PATH_SEPARATOR);
            return (ls == NULL) ? path : ls + 1;
        }

        ZPL_IMPL_INLINE char const *zpl_path_extension(char const *path) {
            char const *ld;
            ZPL_ASSERT_NOT_NULL(path);
            ld = zpl_char_last_occurence(path, '.');
            return (ld == NULL) ? NULL : ld + 1;
        }

        ZPL_END_C_DECLS
        // file: header/core/print.h

        /** @file print.c
        @brief Printing methods
        @defgroup print Printing methods

        Various printing methods.
        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_DEF zpl_isize zpl_printf(char const *fmt, ...);
        ZPL_DEF zpl_isize zpl_printf_va(char const *fmt, va_list va);
        ZPL_DEF zpl_isize zpl_printf_err(char const *fmt, ...);
        ZPL_DEF zpl_isize zpl_printf_err_va(char const *fmt, va_list va);
        ZPL_DEF zpl_isize zpl_fprintf(zpl_file *f, char const *fmt, ...);
        ZPL_DEF zpl_isize zpl_fprintf_va(zpl_file *f, char const *fmt, va_list va);

        // NOTE: A locally persisting buffer is used internally
        ZPL_DEF char *zpl_bprintf(char const *fmt, ...);

        // NOTE: A locally persisting buffer is used internally
        ZPL_DEF char *zpl_bprintf_va(char const *fmt, va_list va);

        ZPL_DEF zpl_isize zpl_snprintf(char *str, zpl_isize n, char const *fmt, ...);
        ZPL_DEF zpl_isize zpl_snprintf_va(char *str, zpl_isize n, char const *fmt, va_list va);

        ZPL_END_C_DECLS
        // file: header/core/time.h

        /** @file time.c
        @brief Time helper methods.
        @defgroup time Time helpers

         Helper methods for retrieving the current time in many forms under different precisions. It also offers a simple to use timer library.

         @{
         */

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        //! Return CPU timestamp.
        ZPL_DEF zpl_u64 zpl_rdtsc(void);

        //! Return relative time since the application start.
        ZPL_DEF zpl_f64 zpl_time_now(void);

        //! Return time since 1601-01-01 UTC.
        ZPL_DEF zpl_f64 zpl_utc_time_now(void);

        //! Sleep for specified number of milliseconds.
        ZPL_DEF void zpl_sleep_ms(zpl_u32 ms);

        ZPL_END_C_DECLS
        // file: header/core/random.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_random {
            zpl_u32 offsets[8];
            zpl_u32 value;
        } zpl_random;

        // NOTE: Generates from numerous sources to produce a decent pseudo-random seed
        ZPL_DEF void      zpl_random_init(zpl_random *r);
        ZPL_DEF zpl_u32   zpl_random_gen_u32(zpl_random *r);
        ZPL_DEF zpl_u32   zpl_random_gen_u32_unique(zpl_random *r);
        ZPL_DEF zpl_u64   zpl_random_gen_u64(zpl_random *r); // NOTE: (zpl_random_gen_u32() << 32) | zpl_random_gen_u32()
        ZPL_DEF zpl_isize zpl_random_gen_isize(zpl_random *r);
        ZPL_DEF zpl_i64   zpl_random_range_i64(zpl_random *r, zpl_i64 lower_inc, zpl_i64 higher_inc);
        ZPL_DEF zpl_isize zpl_random_range_isize(zpl_random *r, zpl_isize lower_inc, zpl_isize higher_inc);
        ZPL_DEF zpl_f64   zpl_random_range_f64(zpl_random *r, zpl_f64 lower_inc, zpl_f64 higher_inc);

        ZPL_END_C_DECLS
        // file: header/core/misc.h

        /** @file misc.c
        @brief Various other stuff
        @defgroup misc Various other stuff

         Methods that don't belong anywhere but are still very useful in many occasions.

         @{
         */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_DEF void zpl_exit(zpl_u32 code);
        ZPL_DEF void zpl_yield(void);

        //! Returns allocated buffer
        ZPL_DEF const char *zpl_get_env(const char *name);
        ZPL_DEF const char *zpl_get_env_buf(const char *name);
        ZPL_DEF zpl_string  zpl_get_env_str(const char *name);
        ZPL_DEF void        zpl_set_env(const char *name, const char *value);
        ZPL_DEF void        zpl_unset_env(const char *name);

        ZPL_DEF zpl_u32    zpl_system_command(const char *command, zpl_usize buffer_len, char *buffer);
        ZPL_DEF zpl_string zpl_system_command_str(const char *command, zpl_allocator backing);

        ZPL_DEF_INLINE zpl_u16 zpl_endian_swap16(zpl_u16 i);
        ZPL_DEF_INLINE zpl_u32 zpl_endian_swap32(zpl_u32 i);
        ZPL_DEF_INLINE zpl_u64 zpl_endian_swap64(zpl_u64 i);

        ZPL_DEF_INLINE zpl_isize zpl_count_set_bits(zpl_u64 mask);

        //! @}
        //$$

        ZPL_IMPL_INLINE zpl_u16 zpl_endian_swap16(zpl_u16 i) {
            return (i>>8) | (i<<8);
        }

        ZPL_IMPL_INLINE zpl_u32 zpl_endian_swap32(zpl_u32 i) {
            return (i>>24) |(i<<24) |
                ((i&0x00ff0000u)>>8)  | ((i&0x0000ff00u)<<8);
        }

        ZPL_IMPL_INLINE zpl_u64 zpl_endian_swap64(zpl_u64 i) {
            return (i>>56) | (i<<56) |
                ((i&0x00ff000000000000ull)>>40) | ((i&0x000000000000ff00ull)<<40) |
                ((i&0x0000ff0000000000ull)>>24) | ((i&0x0000000000ff0000ull)<<24) |
                ((i&0x000000ff00000000ull)>>8)  | ((i&0x00000000ff000000ull)<<8);
        }

        ZPL_IMPL_INLINE zpl_i32 zpl_next_pow2(zpl_i32 x) {
            x--;
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            x |= x >> 8;
            x |= x >> 16;
            return x + 1;
        }

        ZPL_IMPL_INLINE void zpl_bit_set(zpl_u32* x, zpl_u32 bit) { *x = *x | (1 << bit); }
        ZPL_IMPL_INLINE zpl_b8 zpl_bit_get(zpl_u32 x, zpl_u32 bit) { return (x & (1 << bit)); }
        ZPL_IMPL_INLINE void zpl_bit_reset(zpl_u32* x, zpl_u32 bit) { *x = *x & ~(1 << bit); }

        ZPL_IMPL_INLINE zpl_isize zpl_count_set_bits(zpl_u64 mask) {
            zpl_isize count = 0;
            while (mask) {
                count += (mask & 1);
                mask >>= 1;
            }
            return count;
        }

        ZPL_END_C_DECLS
        // file: header/core/sort.h

        /** @file sort.c
        @brief Sorting and searching methods.
        @defgroup sort Sorting and searching

        Methods for sorting arrays using either Quick/Merge-sort combo or Radix sort. It also contains simple implementation of binary search, as well as an easy to use API to define your own comparators.

        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #define ZPL_COMPARE_PROC(name) int name(void const *a, void const *b)
        typedef ZPL_COMPARE_PROC(zpl_compare_proc);

        #define ZPL_COMPARE_PROC_PTR(def) ZPL_COMPARE_PROC((*def))

        // Procedure pointers
        // NOTE: The offset parameter specifies the offset in the structure
        // e.g. zpl_i32_cmp(zpl_offset_of(Thing, value))
        // Use 0 if it's just the type instead.

        ZPL_DEF ZPL_COMPARE_PROC_PTR(i16_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(u8_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(i32_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(i64_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(isize_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(str_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(f32_cmp(zpl_isize offset));
        ZPL_DEF ZPL_COMPARE_PROC_PTR(f64_cmp(zpl_isize offset));

        // TODO: Better sorting algorithms

        //! Sorts an array.

        //! Uses quick sort for large arrays but insertion sort for small ones.
        #define zpl_sort_array(array, count, compare_proc) zpl_sort(array, count, zpl_size_of(*(array)), compare_proc)

        //! Perform sorting operation on a memory location with a specified item count and size.
        ZPL_DEF void zpl_sort(void *base, zpl_isize count, zpl_isize size, zpl_compare_proc compare_proc);

        // NOTE: the count of temp == count of items
        #define zpl_radix_sort(Type) zpl_radix_sort_##Type
        #define ZPL_RADIX_SORT_PROC(Type) void zpl_radix_sort(Type)(zpl_##Type * items, zpl_##Type * temp, zpl_isize count)

        ZPL_DEF ZPL_RADIX_SORT_PROC(u8);
        ZPL_DEF ZPL_RADIX_SORT_PROC(u16);
        ZPL_DEF ZPL_RADIX_SORT_PROC(u32);
        ZPL_DEF ZPL_RADIX_SORT_PROC(u64);

        //! Performs binary search on an array.

        //! Returns index or -1 if not found
        #define zpl_binary_search_array(array, count, key, compare_proc)                                                       \
        zpl_binary_search(array, count, zpl_size_of(*(array)), key, compare_proc)

        //! Performs binary search on a memory location with specified item count and size.
        ZPL_DEF_INLINE zpl_isize zpl_binary_search(void const *base, zpl_isize count, zpl_isize size, void const *key,
                                        zpl_compare_proc compare_proc);

        #define zpl_shuffle_array(array, count) zpl_shuffle(array, count, zpl_size_of(*(array)))

        //! Shuffles a memory.
        ZPL_DEF void zpl_shuffle(void *base, zpl_isize count, zpl_isize size);

        #define zpl_reverse_array(array, count) zpl_reverse(array, count, zpl_size_of(*(array)))

        //! Reverses memory's contents
        ZPL_DEF void zpl_reverse(void *base, zpl_isize count, zpl_isize size);

        //! @}


        ZPL_IMPL_INLINE zpl_isize zpl_binary_search(void const *base, zpl_isize count, zpl_isize size, void const *key,
                                           zpl_compare_proc compare_proc) {
            zpl_isize start = 0;
            zpl_isize end = count;

            while (start < end) {
                zpl_isize mid = start + (end - start) / 2;
                zpl_isize result = compare_proc(key, cast(zpl_u8 *) base + mid * size);
                if (result < 0)
                    end = mid;
                else if (result > 0)
                    start = mid + 1;
                else
                    return mid;
            }

            return -1;
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_TIMER)
        // file: header/timer.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef void (*zpl_timer_cb)(void *data);

        //! Timer data structure
        typedef struct zpl_timer {
            zpl_timer_cb callback;
            zpl_b32 enabled;
            zpl_i32 remaining_calls;
            zpl_i32 initial_calls;
            zpl_f64 next_call_ts;
            zpl_f64 duration;
            void *user_data;
        } zpl_timer;

        typedef zpl_timer *zpl_timer_pool; ///< zpl_array

        //! Initialize timer pool.
        #define zpl_timer_init(pool, allocator) zpl_array_init(pool, allocator)

        //! Add new timer to pool and return it.
        ZPL_DEF zpl_timer *zpl_timer_add(zpl_timer_pool pool);

        //! Perform timer pool update.

        //! Traverse over all timers and update them accordingly. Should be called by Main Thread in a tight loop.
        ZPL_DEF void zpl_timer_update(zpl_timer_pool pool);

        //! Set up timer.

        //! Set up timer with specific options.
        //! @param timer
        //! @param duration How long/often to fire a timer.
        //! @param count How many times we fire a timer. Use -1 for infinity.
        //! @param callback A method to execute once a timer triggers.
        ZPL_DEF void zpl_timer_set(zpl_timer *timer, zpl_f64 /* microseconds */ duration, zpl_i32 /* -1 for INFINITY */ count,
                                   zpl_timer_cb callback);

        //! Start timer with specified delay.
        ZPL_DEF void zpl_timer_start(zpl_timer *timer, zpl_f64 delay_start);

        //! Stop timer and prevent it from triggering.
        ZPL_DEF void zpl_timer_stop(zpl_timer *timer);

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_HASHING)
        // file: header/hashing.h

        /** @file hashing.c
        @brief Hashing and Checksum Functions
        @defgroup hashing Hashing and Checksum Functions

        Several hashing methods used by ZPL internally but possibly useful outside of it. Contains: adler32, crc32/64, fnv32/64/a and murmur32/64

        @{
        */

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_DEF zpl_u32 zpl_adler32(void const *data, zpl_isize len);

        ZPL_DEF zpl_u32 zpl_crc32(void const *data, zpl_isize len);
        ZPL_DEF zpl_u64 zpl_crc64(void const *data, zpl_isize len);

        ZPL_DEF zpl_u32 zpl_fnv32(void const *data, zpl_isize len);
        ZPL_DEF zpl_u64 zpl_fnv64(void const *data, zpl_isize len);
        ZPL_DEF zpl_u32 zpl_fnv32a(void const *data, zpl_isize len);
        ZPL_DEF zpl_u64 zpl_fnv64a(void const *data, zpl_isize len);

        ZPL_DEF zpl_u8 *zpl_base64_encode(zpl_allocator a, void const *data, zpl_isize len);
        ZPL_DEF zpl_u8 *zpl_base64_decode(zpl_allocator a, void const *data, zpl_isize len);

        ZPL_DEF zpl_u32 zpl_murmur32_seed(void const *data, zpl_isize len, zpl_u32 seed);
        ZPL_DEF zpl_u64 zpl_murmur64_seed(void const *data, zpl_isize len, zpl_u64 seed);

        //! Default seed of 0x9747b28c
        ZPL_DEF_INLINE zpl_u32 zpl_murmur32(void const *data, zpl_isize len);

        //! Default seed of 0x9747b28c
        ZPL_DEF_INLINE zpl_u64 zpl_murmur64(void const *data, zpl_isize len);

        //! @}

        ZPL_IMPL_INLINE zpl_u32 zpl_murmur32(void const *data, zpl_isize len) { return zpl_murmur32_seed(data, len, 0x9747b28c); }
        ZPL_IMPL_INLINE zpl_u64 zpl_murmur64(void const *data, zpl_isize len) { return zpl_murmur64_seed(data, len, 0x9747b28c); }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_REGEX)
        // file: header/regex.h

        /** @file regex.c
        @brief Regular expressions parser.
        @defgroup regex Regex processor

        Port of gb_regex with several bugfixes applied. This is a simple regex library and is fast to perform.

        Supported Matching:
            @n ^       - Beginning of string
            @n $       - End of string
            @n .       - Match one (anything)
            @n |       - Branch (or)
            @n ()      - Capturing group
            @n []      - Any character included in set
            @n [^]     - Any character excluded from set
            @n +       - One or more  (greedy)
            @n +?      - One or more  (non-greedy)
            @n *       - Zero or more (greedy)
            @n *?      - Zero or more (non-greedy)
            @n ?       - Zero or once
            @n [BACKSLASH]XX     - Hex decimal digit (must be 2 digits)
            @n [BACKSLASH]meta   - Meta character
            @n [BACKSLASH]s      - Whitespace
            @n [BACKSLASH]S      - Not whitespace
            @n [BACKSLASH]d      - Digit
            @n [BACKSLASH]D      - Not digit
            @n [BACKSLASH]a      - Alphabetic character
            @n [BACKSLASH]l      - Lower case letter
            @n [BACKSLASH]u      - Upper case letter
            @n [BACKSLASH]w      - Word
            @n [BACKSLASH]W      - Not word
            @n [BACKSLASH]x      - Hex Digit
            @n [BACKSLASH]p      - Printable ASCII character
            @n --Whitespace--
            @n [BACKSLASH]t      - Tab
            @n [BACKSLASH]n      - New line
            @n [BACKSLASH]r      - Return carriage
            @n [BACKSLASH]v      - Vertical Tab
            @n [BACKSLASH]f      - Form feed

            @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_re {
            zpl_allocator backing;
            zpl_isize capture_count;
            char *buf;
            zpl_isize buf_len, buf_cap;
            zpl_b32 can_realloc;
        } zpl_re;

        typedef struct zpl_re_capture {
            char const *str;
            zpl_isize len;
        } zpl_re_capture;

        #define zplRegexError zpl_regex_error
        typedef enum zpl_regex_error {
            ZPL_RE_ERROR_NONE,
            ZPL_RE_ERROR_NO_MATCH,
            ZPL_RE_ERROR_TOO_LONG,
            ZPL_RE_ERROR_MISMATCHED_CAPTURES,
            ZPL_RE_ERROR_MISMATCHED_BLOCKS,
            ZPL_RE_ERROR_BRANCH_FAILURE,
            ZPL_RE_ERROR_INVALID_QUANTIFIER,
            ZPL_RE_ERROR_INTERNAL_FAILURE,
        } zpl_regex_error;

        //! Compile regex pattern.
        ZPL_DEF zpl_regex_error zpl_re_compile(zpl_re *re, zpl_allocator backing, char const *pattern, zpl_isize pattern_len);

        //! Compile regex pattern using a buffer.
        ZPL_DEF zpl_regex_error zpl_re_compile_from_buffer(zpl_re *re, char const *pattern, zpl_isize pattern_len, void *buffer, zpl_isize buffer_len);

        //! Destroy regex object.
        ZPL_DEF void            zpl_re_destroy(zpl_re *re);

        //! Retrieve number of retrievable captures.
        ZPL_DEF zpl_isize       zpl_re_capture_count(zpl_re *re);

        //! Match input string and output captures of the occurence.
        ZPL_DEF zpl_b32         zpl_re_match(zpl_re *re, char const *str, zpl_isize str_len, zpl_re_capture *captures, zpl_isize max_capture_count, zpl_isize *offset);

        //! Match all occurences in an input string and output them into captures. Array of captures is allocated on the heap and needs to be freed afterwards.
        ZPL_DEF zpl_b32         zpl_re_match_all(zpl_re *re, char const *str, zpl_isize str_len, zpl_isize max_capture_count, zpl_re_capture **out_captures);

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_EVENT)
        // file: header/event.h

        /** @file event.c
        @brief Event handler

        @n
        @n Event handler
        @n
        @n Uses hash table to store array of callbacks per
        @n each valid event type.
        @n
        @n Each event callback receives an anonymous pointer
        @n which has to be casted to proper base type.
        @n
        @n Usage:
        @n - Initialize event pool.
        @n - Declare your event callbacks and any data layout
        @n   used by the events.
        @n - Add event callbacks to the pool. (Returns callback ID.)
        @n - Trigger arbitrary event in pool with specified dataset.
        @n - (Optional) Remove arbitrary event callback
        @n   by refering to it through event type and its callback ID.
        @n

        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef void *zpl_event_data;
        typedef void (*zpl_event_cb)(zpl_event_data evt);
        typedef zpl_event_cb* zpl_event_block; ///< zpl_array

        #define ZPL_EVENT_CAST(Type, name) Type * name = cast(Type *)evt
        ZPL_TABLE_DECLARE(static, zpl_event_pool, zpl_event_pool_, zpl_event_block);

        ZPL_DEF void    zpl_event_init   (zpl_event_pool *pool, zpl_allocator alloc);
        ZPL_DEF void    zpl_event_destroy(zpl_event_pool *pool);
        ZPL_DEF zpl_u64 zpl_event_add    (zpl_event_pool *pool, zpl_u64 slot, zpl_event_cb cb);
        ZPL_DEF void    zpl_event_remove (zpl_event_pool *pool, zpl_u64 slot, zpl_u64 index);
        ZPL_DEF void    zpl_event_trigger(zpl_event_pool *pool, zpl_u64 slot, zpl_event_data evt);

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_DLL)
        // file: header/dll.h

        /** @file dll.c
        @brief DLL Handling
        @defgroup dll DLL handling

        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef void *zpl_dll_handle;
        typedef void (*zpl_dll_proc)(void);

        ZPL_DEF zpl_dll_handle zpl_dll_load(char const *filepath);
        ZPL_DEF void           zpl_dll_unload(zpl_dll_handle dll);
        ZPL_DEF zpl_dll_proc   zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name);

        //! @}

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_OPTS)
        // file: header/opts.h

        /** @file opts.c
        @brief CLI options processor
        @defgroup cli CLI options processor

         Opts is a CLI options parser, it can parse flags, switches and arguments from command line
         and offers an easy way to express input errors as well as the ability to display help screen.

        @{
         */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef enum {
            ZPL_OPTS_STRING,
            ZPL_OPTS_FLOAT,
            ZPL_OPTS_FLAG,
            ZPL_OPTS_INT,
        } zpl_opts_types;

        typedef struct {
            char const *name, *lname, *desc;
            zpl_u8 type;
            zpl_b32 met, pos;

            //! values
            union {
                zpl_string text;
                zpl_i64 integer;
                zpl_f64 real;
            };
        } zpl_opts_entry;

        typedef enum {
            ZPL_OPTS_ERR_VALUE,
            ZPL_OPTS_ERR_OPTION,
            ZPL_OPTS_ERR_EXTRA_VALUE,
            ZPL_OPTS_ERR_MISSING_VALUE,
        } zpl_opts_err_type;

        typedef struct {
            char *val;
            zpl_u8 type;
        } zpl_opts_err;

        typedef struct {
            zpl_allocator    alloc;
            zpl_opts_entry  *entries;   ///< zpl_array
            zpl_opts_err    *errors;    ///< zpl_array
            zpl_opts_entry **positioned; ///< zpl_array
            char const      *appname;
        } zpl_opts;

        //! Initializes options parser.

        //! Initializes CLI options parser using specified memory allocator and provided application name.
        //! @param opts Options parser to initialize.
        //! @param allocator Memory allocator to use. (ex. zpl_heap())
        //! @param app Application name displayed in help screen.
        ZPL_DEF void zpl_opts_init(zpl_opts *opts, zpl_allocator allocator, char const *app);

        //! Releases the resources used by options parser.
        ZPL_DEF void zpl_opts_free(zpl_opts *opts);

        //! Registers an option.

        //! Registers an option with its short and long name, specifies option's type and its description.
        //! @param opts Options parser to add to.
        //! @param lname Shorter name of option. (ex. "f")
        //! @param name Full name of option. (ex. "foo") Note that rest of the module uses longer names to manipulate opts.
        //! @param desc Description shown in the help screen.
        //! @param type Option's type (see zpl_opts_types)
        //! @see zpl_opts_types
        ZPL_DEF void zpl_opts_add(zpl_opts *opts, char const *name, char const *lname, const char *desc, zpl_u8 type);

        //! Registers option as positional.

        //! Registers added option as positional, so that we can pass it anonymously. Arguments are expected on the command input in the same order they were registered as.
        //! @param opts
        //! @param name Name of already registered option.
        ZPL_DEF void zpl_opts_positional_add(zpl_opts *opts, char const *name);

        //! Compiles CLI arguments.

        // This method takes CLI arguments as input and processes them based on rules that were set up.
        //! @param opts
        //! @param argc Argument count in an array.
        //! @param argv Array of arguments.
        ZPL_DEF zpl_b32 zpl_opts_compile(zpl_opts *opts, int argc, char **argv);

        //! Prints out help screen.

        //! Prints out help screen with example usage of application as well as with all the flags available.
        ZPL_DEF void zpl_opts_print_help(zpl_opts *opts);

        //! Prints out parsing errors.

        //! Prints out possible errors caused by CLI input.
        ZPL_DEF void zpl_opts_print_errors(zpl_opts *opts);

        //! Fetches a string from an option.

        //! @param opts
        //! @param name Name of an option.
        //! @param fallback Fallback string we return if option wasn't found.
        ZPL_DEF zpl_string zpl_opts_string(zpl_opts *opts, char const *name, char const *fallback);

        //! Fetches a real number from an option.

        //! @param opts
        //! @param name Name of an option.
        //! @param fallback Fallback real number we return if option was not found.
        ZPL_DEF zpl_f64 zpl_opts_real(zpl_opts *opts, char const *name, zpl_f64 fallback);

        //! Fetches an integer number from an option.

        //! @param opts
        //! @param name Name of an option.
        //! @param fallback Fallback integer number we return if option was not found.
        ZPL_DEF zpl_i64 zpl_opts_integer(zpl_opts *opts, char const *name, zpl_i64 fallback);

        //! Checks whether an option was used.

        //! @param opts
        //! @param name Name of an option.
        ZPL_DEF zpl_b32 zpl_opts_has_arg(zpl_opts *opts, char const *name);

        //! Checks whether all positionals have been passed in.
        ZPL_DEF zpl_b32 zpl_opts_positionals_filled(zpl_opts *opts);

        //! @}

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_PROCESS)
        // file: header/process.h

        /** @file process.c
        @brief Process creation and manipulation methods
        @defgroup process Process creation and manipulation methods

        Gives you the ability to create a new process, wait for it to end or terminate it.
        It also exposes standard I/O with configurable options.

        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS
        // TODO(zaklaus): Add Linux support

        typedef enum {
            ZPL_PR_OPTS_COMBINE_STD_OUTPUT  = ZPL_BIT(1),
            ZPL_PR_OPTS_INHERIT_ENV         = ZPL_BIT(2),
            ZPL_PR_OPTS_CUSTOM_ENV          = ZPL_BIT(3),
        } zpl_pr_opts;

        typedef struct {
            zpl_file in, out, err;
            void *f_stdin, *f_stdout, *f_stderr;
        #ifdef ZPL_SYSTEM_WINDOWS
            void *win32_handle;
        #else
            // todo
        #endif
        } zpl_pr;

        typedef struct {
            char *con_title;
            char *workdir;

            zpl_isize env_count;
            char **env; // format: "var=name"

            zpl_u32 posx, posy;
            zpl_u32 resx, resy;
            zpl_u32 bufx, bufy;
            zpl_u32 fill_attr;
            zpl_u32 flags;
            zpl_b32 show_window;
        } zpl_pr_si;

        ZPL_DEF zpl_i32 zpl_pr_create(zpl_pr *process, const char **args, zpl_isize argc, zpl_pr_si si, zpl_pr_opts options);
        ZPL_DEF void    zpl_pr_destroy(zpl_pr *process);
        ZPL_DEF void    zpl_pr_terminate(zpl_pr *process, zpl_i32 err_code);
        ZPL_DEF zpl_i32 zpl_pr_join(zpl_pr *process);

        //! @}
        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_MATH)
        // file: header/math.h

        /** @file math.c
        @brief Math operations
        @defgroup math Math operations

        OpenGL gamedev friendly library for math.

        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef union zpl_vec2 {
            struct {
                zpl_f32 x, y;
            };
            struct {
                zpl_f32 s, t;
            };
            zpl_f32 e[2];
        } zpl_vec2;

        typedef union zpl_vec3 {
            struct {
                zpl_f32 x, y, z;
            };
            struct {
                zpl_f32 r, g, b;
            };
            struct {
                zpl_f32 s, t, p;
            };

            zpl_vec2 xy;
            zpl_vec2 st;
            zpl_f32 e[3];
        } zpl_vec3;

        typedef union zpl_vec4 {
            struct {
                zpl_f32 x, y, z, w;
            };
            struct {
                zpl_f32 r, g, b, a;
            };
            struct {
                zpl_f32 s, t, p, q;
            };
            struct {
                zpl_vec2 xy, zw;
            };
            struct {
                zpl_vec2 st, pq;
            };
            zpl_vec3 xyz;
            zpl_vec3 rgb;
            zpl_f32 e[4];
        } zpl_vec4;

        typedef union zpl_mat2 {
            struct {
                zpl_vec2 x, y;
            };
            zpl_vec2 col[2];
            zpl_f32 e[4];
        } zpl_mat2;

        typedef union zpl_mat3 {
            struct {
                zpl_vec3 x, y, z;
            };
            zpl_vec3 col[3];
            zpl_f32 e[9];
        } zpl_mat3;

        typedef union zpl_mat4 {
            struct {
                zpl_vec4 x, y, z, w;
            };
            zpl_vec4 col[4];
            zpl_f32 e[16];
        } zpl_mat4;

        typedef union zpl_quat {
            struct {
                zpl_f32 x, y, z, w;
            };
            zpl_vec4 xyzw;
            zpl_vec3 xyz;
            zpl_f32 e[4];
        } zpl_quat;

        typedef union zpl_plane {
            struct {
                zpl_f32 a, b, c, d;
            };
            zpl_vec4 xyzw;
            zpl_vec3 n;
            zpl_f32 e[4];
        } zpl_plane;

        typedef struct zpl_frustum {
            zpl_plane x1;
            zpl_plane x2;
            zpl_plane y1;
            zpl_plane y2;
            zpl_plane z1;
            zpl_plane z2;
        } zpl_frustum;

        typedef zpl_f32 zpl_float2[2];
        typedef zpl_f32 zpl_float3[3];
        typedef zpl_f32 zpl_float4[4];

        typedef struct zpl_rect2 {
            zpl_vec2 pos, dim;
        } zpl_rect2;
        typedef struct zpl_rect3 {
            zpl_vec3 pos, dim;
        } zpl_rect3;

        typedef struct zpl_aabb2 {
            zpl_vec2 centre, half_size;
        } zpl_aabb2;
        typedef struct zpl_aabb3 {
            zpl_vec3 centre, half_size;
        } zpl_aabb3;

        typedef short zpl_half;

        #ifndef ZPL_CONSTANTS
        #define ZPL_CONSTANTS
        #define ZPL_EPSILON    1.19209290e-7f
        #define ZPL_ZERO       0.0f
        #define ZPL_ONE        1.0f
        #define ZPL_TWO_THIRDS 0.666666666666666666666666666666666666667f

        #define ZPL_TAU          6.28318530717958647692528676655900576f
        #define ZPL_PI           3.14159265358979323846264338327950288f
        #define ZPL_ONE_OVER_TAU 0.636619772367581343075535053490057448f
        #define ZPL_ONE_OVER_PI  0.159154943091895335768883763372514362f

        #define ZPL_TAU_OVER_2 3.14159265358979323846264338327950288f
        #define ZPL_TAU_OVER_4 1.570796326794896619231321691639751442f
        #define ZPL_TAU_OVER_8 0.785398163397448309615660845819875721f

        #define ZPL_E          2.71828182845904523536f
        #define ZPL_SQRT_TWO   1.41421356237309504880168872420969808f
        #define ZPL_SQRT_THREE 1.73205080756887729352744634150587236f
        #define ZPL_SQRT_FIVE  2.23606797749978969640917366873127623f

        #define ZPL_LOG_TWO 0.693147180559945309417232121458176568f
        #define ZPL_LOG_TEN 2.30258509299404568401799145468436421f
        #endif // ZPL_CONSTANTS

        #ifndef zpl_square
        #define zpl_square(x) ((x) * (x))
        #endif

        #ifndef zpl_cube
        #define zpl_cube(x) ((x) * (x) * (x))
        #endif

        #ifndef zpl_sign
        #define zpl_sign(x) ((x) >= 0 ? 1 : -1)
        #endif

        ZPL_DEF zpl_f32 zpl_to_radians(zpl_f32 degrees);
        ZPL_DEF zpl_f32 zpl_to_degrees(zpl_f32 radians);

        /* NOTE: Because to interpolate angles */
        ZPL_DEF zpl_f32 zpl_angle_diff(zpl_f32 radians_a, zpl_f32 radians_b);

        ZPL_DEF zpl_f32 zpl_copy_sign(zpl_f32 x, zpl_f32 y);
        ZPL_DEF zpl_f32 zpl_remainder(zpl_f32 x, zpl_f32 y);
        ZPL_DEF zpl_f32 zpl_mod(zpl_f32 x, zpl_f32 y);
        ZPL_DEF zpl_f64 zpl_copy_sign64(zpl_f64 x, zpl_f64 y);
        ZPL_DEF zpl_f64 zpl_floor64(zpl_f64 x);
        ZPL_DEF zpl_f64 zpl_ceil64(zpl_f64 x);
        ZPL_DEF zpl_f64 zpl_round64(zpl_f64 x);
        ZPL_DEF zpl_f64 zpl_remainder64(zpl_f64 x, zpl_f64 y);
        ZPL_DEF zpl_f64 zpl_abs64(zpl_f64 x);
        ZPL_DEF zpl_f64 zpl_sign64(zpl_f64 x);
        ZPL_DEF zpl_f64 zpl_mod64(zpl_f64 x, zpl_f64 y);
        ZPL_DEF zpl_f32 zpl_sqrt(zpl_f32 a);
        ZPL_DEF zpl_f32 zpl_rsqrt(zpl_f32 a);
        ZPL_DEF zpl_f32 zpl_quake_rsqrt(zpl_f32 a); /* NOTE: It's probably better to use 1.0f/zpl_sqrt(a)
                                             * And for simd, there is usually isqrt functions too!
                                             */
        ZPL_DEF zpl_f32 zpl_sin(zpl_f32 radians);
        ZPL_DEF zpl_f32 zpl_cos(zpl_f32 radians);
        ZPL_DEF zpl_f32 zpl_tan(zpl_f32 radians);
        ZPL_DEF zpl_f32 zpl_arcsin(zpl_f32 a);
        ZPL_DEF zpl_f32 zpl_arccos(zpl_f32 a);
        ZPL_DEF zpl_f32 zpl_arctan(zpl_f32 a);
        ZPL_DEF zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x);

        ZPL_DEF zpl_f32 zpl_exp(zpl_f32 x);
        ZPL_DEF zpl_f32 zpl_exp2(zpl_f32 x);
        ZPL_DEF zpl_f32 zpl_log(zpl_f32 x);
        ZPL_DEF zpl_f32 zpl_log2(zpl_f32 x);
        ZPL_DEF zpl_f32 zpl_fast_exp(zpl_f32 x);   /* NOTE: Only valid from -1 <= x <= +1 */
        ZPL_DEF zpl_f32 zpl_fast_exp2(zpl_f32 x);  /* NOTE: Only valid from -1 <= x <= +1 */
        ZPL_DEF zpl_f32 zpl_pow(zpl_f32 x, zpl_f32 y); /* x^y */

        ZPL_DEF zpl_f32 zpl_round(zpl_f32 x);
        ZPL_DEF zpl_f32 zpl_floor(zpl_f32 x);
        ZPL_DEF zpl_f32 zpl_ceil(zpl_f32 x);

        ZPL_DEF zpl_f32  zpl_half_to_float(zpl_half value);
        ZPL_DEF zpl_half zpl_float_to_half(zpl_f32 value);

        ZPL_DEF zpl_vec2 zpl_vec2f_zero(void);
        ZPL_DEF zpl_vec2 zpl_vec2f(zpl_f32 x, zpl_f32 y);
        ZPL_DEF zpl_vec2 zpl_vec2fv(zpl_f32 x[2]);

        ZPL_DEF zpl_vec3 zpl_vec3f_zero(void);
        ZPL_DEF zpl_vec3 zpl_vec3f(zpl_f32 x, zpl_f32 y, zpl_f32 z);
        ZPL_DEF zpl_vec3 zpl_vec3fv(zpl_f32 x[3]);

        ZPL_DEF zpl_vec4 zpl_vec4f_zero(void);
        ZPL_DEF zpl_vec4 zpl_vec4f(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w);
        ZPL_DEF zpl_vec4 zpl_vec4fv(zpl_f32 x[4]);

        ZPL_DEF zpl_f32 zpl_vec2_max(zpl_vec2 v);
        ZPL_DEF zpl_f32 zpl_vec2_side(zpl_vec2 p, zpl_vec2 q, zpl_vec2 r);
        ZPL_DEF void zpl_vec2_add(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1);
        ZPL_DEF void zpl_vec2_sub(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1);
        ZPL_DEF void zpl_vec2_mul(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s);
        ZPL_DEF void zpl_vec2_div(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s);

        ZPL_DEF zpl_f32 zpl_vec3_max(zpl_vec3 v);
        ZPL_DEF void zpl_vec3_add(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1);
        ZPL_DEF void zpl_vec3_sub(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1);
        ZPL_DEF void zpl_vec3_mul(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s);
        ZPL_DEF void zpl_vec3_div(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s);

        ZPL_DEF void zpl_vec4_add(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1);
        ZPL_DEF void zpl_vec4_sub(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1);
        ZPL_DEF void zpl_vec4_mul(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s);
        ZPL_DEF void zpl_vec4_div(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s);

        ZPL_DEF void zpl_vec2_addeq(zpl_vec2 *d, zpl_vec2 v);
        ZPL_DEF void zpl_vec2_subeq(zpl_vec2 *d, zpl_vec2 v);
        ZPL_DEF void zpl_vec2_muleq(zpl_vec2 *d, zpl_f32 s);
        ZPL_DEF void zpl_vec2_diveq(zpl_vec2 *d, zpl_f32 s);

        ZPL_DEF void zpl_vec3_addeq(zpl_vec3 *d, zpl_vec3 v);
        ZPL_DEF void zpl_vec3_subeq(zpl_vec3 *d, zpl_vec3 v);
        ZPL_DEF void zpl_vec3_muleq(zpl_vec3 *d, zpl_f32 s);
        ZPL_DEF void zpl_vec3_diveq(zpl_vec3 *d, zpl_f32 s);

        ZPL_DEF void zpl_vec4_addeq(zpl_vec4 *d, zpl_vec4 v);
        ZPL_DEF void zpl_vec4_subeq(zpl_vec4 *d, zpl_vec4 v);
        ZPL_DEF void zpl_vec4_muleq(zpl_vec4 *d, zpl_f32 s);
        ZPL_DEF void zpl_vec4_diveq(zpl_vec4 *d, zpl_f32 s);

        ZPL_DEF zpl_f32 zpl_vec2_dot(zpl_vec2 v0, zpl_vec2 v1);
        ZPL_DEF zpl_f32 zpl_vec3_dot(zpl_vec3 v0, zpl_vec3 v1);
        ZPL_DEF zpl_f32 zpl_vec4_dot(zpl_vec4 v0, zpl_vec4 v1);

        ZPL_DEF void zpl_vec2_cross(zpl_f32 *d, zpl_vec2 v0, zpl_vec2 v1);
        ZPL_DEF void zpl_vec3_cross(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1);

        ZPL_DEF zpl_f32 zpl_vec2_mag2(zpl_vec2 v);
        ZPL_DEF zpl_f32 zpl_vec3_mag2(zpl_vec3 v);
        ZPL_DEF zpl_f32 zpl_vec4_mag2(zpl_vec4 v);

        ZPL_DEF zpl_f32 zpl_vec2_mag(zpl_vec2 v);
        ZPL_DEF zpl_f32 zpl_vec3_mag(zpl_vec3 v);
        ZPL_DEF zpl_f32 zpl_vec4_mag(zpl_vec4 v);

        ZPL_DEF void zpl_vec2_norm(zpl_vec2 *d, zpl_vec2 v);
        ZPL_DEF void zpl_vec3_norm(zpl_vec3 *d, zpl_vec3 v);
        ZPL_DEF void zpl_vec4_norm(zpl_vec4 *d, zpl_vec4 v);

        ZPL_DEF void zpl_vec2_norm0(zpl_vec2 *d, zpl_vec2 v);
        ZPL_DEF void zpl_vec3_norm0(zpl_vec3 *d, zpl_vec3 v);
        ZPL_DEF void zpl_vec4_norm0(zpl_vec4 *d, zpl_vec4 v);

        ZPL_DEF void zpl_vec2_reflect(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n);
        ZPL_DEF void zpl_vec3_reflect(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n);
        ZPL_DEF void zpl_vec2_refract(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n, zpl_f32 eta);
        ZPL_DEF void zpl_vec3_refract(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n, zpl_f32 eta);

        ZPL_DEF zpl_f32 zpl_vec2_aspect_ratio(zpl_vec2 v);

        ZPL_DEF void zpl_mat2_identity(zpl_mat2 *m);
        ZPL_DEF void zpl_float22_identity(zpl_f32 m[2][2]);

        ZPL_DEF void    zpl_mat2_transpose(zpl_mat2 *m);
        ZPL_DEF void    zpl_mat2_mul(zpl_mat2 *out, zpl_mat2 *m1, zpl_mat2 *m2);
        ZPL_DEF void    zpl_mat2_mul_vec2(zpl_vec2 *out, zpl_mat2 *m, zpl_vec2 in);
        ZPL_DEF void    zpl_mat2_inverse(zpl_mat2 *out, zpl_mat2 *in);
        ZPL_DEF zpl_f32 zpl_mat2_determinate(zpl_mat2 *m);

        ZPL_DEF zpl_mat2   *zpl_mat2_v(zpl_vec2 m[2]);
        ZPL_DEF zpl_mat2   *zpl_mat2_f(zpl_f32 m[2][2]);
        ZPL_DEF zpl_float2 *zpl_float22_m(zpl_mat2 *m);
        ZPL_DEF zpl_float2 *zpl_float22_v(zpl_vec2 m[2]);
        ZPL_DEF zpl_float2 *zpl_float22_4(zpl_f32 m[4]);

        ZPL_DEF void zpl_float22_transpose(zpl_f32 (*vec)[2]);
        ZPL_DEF void zpl_float22_mul(zpl_f32 (*out)[2], zpl_f32 (*mat1)[2], zpl_f32 (*mat2)[2]);
        ZPL_DEF void zpl_float22_mul_vec2(zpl_vec2 *out, zpl_f32 m[2][2], zpl_vec2 in);

        ZPL_DEF void zpl_mat3_identity(zpl_mat3 *m);
        ZPL_DEF void zpl_float33_identity(zpl_f32 m[3][3]);

        ZPL_DEF void    zpl_mat3_transpose(zpl_mat3 *m);
        ZPL_DEF void    zpl_mat3_mul(zpl_mat3 *out, zpl_mat3 *m1, zpl_mat3 *m2);
        ZPL_DEF void    zpl_mat3_mul_vec3(zpl_vec3 *out, zpl_mat3 *m, zpl_vec3 in);
        ZPL_DEF void    zpl_mat3_inverse(zpl_mat3 *out, zpl_mat3 *in);
        ZPL_DEF zpl_f32 zpl_mat3_determinate(zpl_mat3 *m);

        ZPL_DEF zpl_mat3   *zpl_mat3_v(zpl_vec3 m[3]);
        ZPL_DEF zpl_mat3   *zpl_mat3_f(zpl_f32 m[3][3]);

        ZPL_DEF zpl_float3 *zpl_float33_m(zpl_mat3 *m);
        ZPL_DEF zpl_float3 *zpl_float33_v(zpl_vec3 m[3]);
        ZPL_DEF zpl_float3 *zpl_float33_9(zpl_f32 m[9]);

        ZPL_DEF void zpl_float33_transpose(zpl_f32 (*vec)[3]);
        ZPL_DEF void zpl_float33_mul(zpl_f32 (*out)[3], zpl_f32 (*mat1)[3], zpl_f32 (*mat2)[3]);
        ZPL_DEF void zpl_float33_mul_vec3(zpl_vec3 *out, zpl_f32 m[3][3], zpl_vec3 in);

        ZPL_DEF void zpl_mat4_identity(zpl_mat4 *m);
        ZPL_DEF void zpl_float44_identity(zpl_f32 m[4][4]);
        ZPL_DEF void zpl_mat4_copy(zpl_mat4* out, zpl_mat4* m);

        ZPL_DEF void zpl_mat4_transpose(zpl_mat4 *m);
        ZPL_DEF void zpl_mat4_mul(zpl_mat4 *out, zpl_mat4 *m1, zpl_mat4 *m2);
        ZPL_DEF void zpl_mat4_mul_vec4(zpl_vec4 *out, zpl_mat4 *m, zpl_vec4 in);
        ZPL_DEF void zpl_mat4_inverse(zpl_mat4 *out, zpl_mat4 *in);

        ZPL_DEF zpl_mat4 *zpl_mat4_v(zpl_vec4 m[4]);
        ZPL_DEF zpl_mat4 *zpl_mat4_f(zpl_f32 m[4][4]);

        ZPL_DEF zpl_float4 *zpl_float44_m(zpl_mat4 *m);
        ZPL_DEF zpl_float4 *zpl_float44_v(zpl_vec4 m[4]);
        ZPL_DEF zpl_float4 *zpl_float44_16(zpl_f32 m[16]);

        ZPL_DEF void zpl_float44_transpose(zpl_f32 (*vec)[4]);
        ZPL_DEF void zpl_float44_mul(zpl_f32 (*out)[4], zpl_f32 (*mat1)[4], zpl_f32 (*mat2)[4]);
        ZPL_DEF void zpl_float44_mul_vec4(zpl_vec4 *out, zpl_f32 m[4][4], zpl_vec4 in);

        ZPL_DEF void zpl_mat4_translate(zpl_mat4 *out, zpl_vec3 v);
        ZPL_DEF void zpl_mat4_rotate(zpl_mat4 *out, zpl_vec3 v, zpl_f32 angle_radians);
        ZPL_DEF void zpl_mat4_scale(zpl_mat4 *out, zpl_vec3 v);
        ZPL_DEF void zpl_mat4_scalef(zpl_mat4 *out, zpl_f32 s);
        ZPL_DEF void zpl_mat4_ortho2d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top);
        ZPL_DEF void zpl_mat4_ortho3d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top, zpl_f32 z_near, zpl_f32 z_far);
        ZPL_DEF void zpl_mat4_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near, zpl_f32 z_far);
        ZPL_DEF void zpl_mat4_infinite_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near);

        ZPL_DEF void zpl_mat4_ortho2d_dx(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top);
        ZPL_DEF void zpl_mat4_ortho3d_dx(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top, zpl_f32 z_near, zpl_f32 z_far);
        ZPL_DEF void zpl_mat4_perspective_dx(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near, zpl_f32 z_far);
        ZPL_DEF void zpl_mat4_infinite_perspective_dx(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near);

        ZPL_DEF void zpl_mat4_look_at(zpl_mat4 *out, zpl_vec3 eye, zpl_vec3 centre, zpl_vec3 up);

        ZPL_DEF void zpl_mat4_look_at_lh(zpl_mat4 *out, zpl_vec3 eye, zpl_vec3 centre, zpl_vec3 up);

        ZPL_DEF zpl_quat zpl_quatf(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w);
        ZPL_DEF zpl_quat zpl_quatfv(zpl_f32 e[4]);
        ZPL_DEF zpl_quat zpl_quat_axis_angle(zpl_vec3 axis, zpl_f32 angle_radians);
        ZPL_DEF zpl_quat zpl_quat_euler_angles(zpl_f32 pitch, zpl_f32 yaw, zpl_f32 roll);
        ZPL_DEF zpl_quat zpl_quat_identity(void);

        ZPL_DEF void zpl_quat_add(zpl_quat *d, zpl_quat q0, zpl_quat q1);
        ZPL_DEF void zpl_quat_sub(zpl_quat *d, zpl_quat q0, zpl_quat q1);
        ZPL_DEF void zpl_quat_mul(zpl_quat *d, zpl_quat q0, zpl_quat q1);
        ZPL_DEF void zpl_quat_div(zpl_quat *d, zpl_quat q0, zpl_quat q1);

        ZPL_DEF void zpl_quat_mulf(zpl_quat *d, zpl_quat q, zpl_f32 s);
        ZPL_DEF void zpl_quat_divf(zpl_quat *d, zpl_quat q, zpl_f32 s);

        ZPL_DEF void zpl_quat_addeq(zpl_quat *d, zpl_quat q);
        ZPL_DEF void zpl_quat_subeq(zpl_quat *d, zpl_quat q);
        ZPL_DEF void zpl_quat_muleq(zpl_quat *d, zpl_quat q);
        ZPL_DEF void zpl_quat_diveq(zpl_quat *d, zpl_quat q);

        ZPL_DEF void zpl_quat_muleqf(zpl_quat *d, zpl_f32 s);
        ZPL_DEF void zpl_quat_diveqf(zpl_quat *d, zpl_f32 s);

        ZPL_DEF zpl_f32 zpl_quat_dot(zpl_quat q0, zpl_quat q1);
        ZPL_DEF zpl_f32 zpl_quat_mag(zpl_quat q);

        ZPL_DEF void zpl_quat_norm(zpl_quat *d, zpl_quat q);
        ZPL_DEF void zpl_quat_conj(zpl_quat *d, zpl_quat q);
        ZPL_DEF void zpl_quat_inverse(zpl_quat *d, zpl_quat q);

        ZPL_DEF void    zpl_quat_axis(zpl_vec3 *axis, zpl_quat q);
        ZPL_DEF zpl_f32 zpl_quat_angle(zpl_quat q);

        ZPL_DEF zpl_f32 zpl_quat_pitch(zpl_quat q);
        ZPL_DEF zpl_f32 zpl_quat_yaw(zpl_quat q);
        ZPL_DEF zpl_f32 zpl_quat_roll(zpl_quat q);

        /* NOTE: Rotate v by q */
        ZPL_DEF void zpl_quat_rotate_vec3(zpl_vec3 *d, zpl_quat q, zpl_vec3 v);
        ZPL_DEF void zpl_mat4_from_quat(zpl_mat4 *out, zpl_quat q);
        ZPL_DEF void zpl_quat_from_mat4(zpl_quat *out, zpl_mat4 *m);

        /* Plane math. */
        ZPL_DEF zpl_f32 zpl_plane_distance(zpl_plane* p, zpl_vec3 v);

        /* Frustum culling. */
        ZPL_DEF void zpl_frustum_create(zpl_frustum* out, zpl_mat4* camera, zpl_mat4* proj);
        ZPL_DEF zpl_b8 zpl_frustum_sphere_inside(zpl_frustum* frustum, zpl_vec3 center, zpl_f32 radius);
        ZPL_DEF zpl_b8 zpl_frustum_point_inside(zpl_frustum* frustum, zpl_vec3 point);
        ZPL_DEF zpl_b8 zpl_frustum_box_inside(zpl_frustum* frustum, zpl_aabb3 box);

        /* Interpolations */
        ZPL_DEF zpl_f32 zpl_lerp(zpl_f32 a, zpl_f32 b, zpl_f32 t);
        ZPL_DEF zpl_f32 zpl_unlerp(zpl_f32 t, zpl_f32 a, zpl_f32 b);
        ZPL_DEF zpl_f32 zpl_smooth_step(zpl_f32 a, zpl_f32 b, zpl_f32 t);
        ZPL_DEF zpl_f32 zpl_smoother_step(zpl_f32 a, zpl_f32 b, zpl_f32 t);

        ZPL_DEF void zpl_vec2_lerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 b, zpl_f32 t);
        ZPL_DEF void zpl_vec3_lerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 b, zpl_f32 t);
        ZPL_DEF void zpl_vec4_lerp(zpl_vec4 *d, zpl_vec4 a, zpl_vec4 b, zpl_f32 t);

        ZPL_DEF void zpl_vec2_cslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t);
        ZPL_DEF void zpl_vec3_cslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t);
        ZPL_DEF void zpl_vec2_dcslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t);
        ZPL_DEF void zpl_vec3_dcslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t);

        ZPL_DEF void zpl_quat_lerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
        ZPL_DEF void zpl_quat_nlerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
        ZPL_DEF void zpl_quat_slerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
        ZPL_DEF void zpl_quat_nquad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t);
        ZPL_DEF void zpl_quat_squad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t);
        ZPL_DEF void zpl_quat_slerp_approx(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t);
        ZPL_DEF void zpl_quat_squad_approx(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t);

        /* Rects */
        ZPL_DEF zpl_rect2 zpl_rect2f(zpl_vec2 pos, zpl_vec2 dim);
        ZPL_DEF zpl_rect3 zpl_rect3f(zpl_vec3 pos, zpl_vec3 dim);

        ZPL_DEF int zpl_rect2_contains(zpl_rect2 a, zpl_f32 x, zpl_f32 y);
        ZPL_DEF int zpl_rect2_contains_vec2(zpl_rect2 a, zpl_vec2 p);
        ZPL_DEF int zpl_rect2_intersects(zpl_rect2 a, zpl_rect2 b);
        ZPL_DEF int zpl_rect2_intersection_result(zpl_rect2 a, zpl_rect2 b, zpl_rect2 *intersection);

        //! @}
        ZPL_END_C_DECLS
        #if defined(__cplusplus)
            ZPL_INLINE bool operator==(zpl_vec2 a, zpl_vec2 b) { return (a.x == b.x) && (a.y == b.y); }
            ZPL_INLINE bool operator!=(zpl_vec2 a, zpl_vec2 b) { return !operator==(a, b); }

            ZPL_INLINE zpl_vec2 operator+(zpl_vec2 a) { return a; }
            ZPL_INLINE zpl_vec2 operator-(zpl_vec2 a) { zpl_vec2 r = {-a.x, -a.y}; return r; }

            ZPL_INLINE zpl_vec2 operator+(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r; zpl_vec2_add(&r, a, b); return r; }
            ZPL_INLINE zpl_vec2 operator-(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r; zpl_vec2_sub(&r, a, b); return r; }

            ZPL_INLINE zpl_vec2 operator*(zpl_vec2 a, float scalar) { zpl_vec2 r; zpl_vec2_mul(&r, a, scalar); return r; }
            ZPL_INLINE zpl_vec2 operator*(float scalar, zpl_vec2 a) { return operator*(a, scalar); }

            ZPL_INLINE zpl_vec2 operator/(zpl_vec2 a, float scalar) { return operator*(a, 1.0f/scalar); }

            /* Hadamard Product */
            ZPL_INLINE zpl_vec2 operator*(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r = {a.x*b.x, a.y*b.y}; return r; }
            ZPL_INLINE zpl_vec2 operator/(zpl_vec2 a, zpl_vec2 b) { zpl_vec2 r = {a.x/b.x, a.y/b.y}; return r; }

            ZPL_INLINE zpl_vec2 &operator+=(zpl_vec2 &a, zpl_vec2 b)       { return (a = a + b); }
            ZPL_INLINE zpl_vec2 &operator-=(zpl_vec2 &a, zpl_vec2 b)       { return (a = a - b); }
            ZPL_INLINE zpl_vec2 &operator*=(zpl_vec2 &a, float scalar) { return (a = a * scalar); }
            ZPL_INLINE zpl_vec2 &operator/=(zpl_vec2 &a, float scalar) { return (a = a / scalar); }


            ZPL_INLINE bool operator==(zpl_vec3 a, zpl_vec3 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z); }
            ZPL_INLINE bool operator!=(zpl_vec3 a, zpl_vec3 b) { return !operator==(a, b); }

            ZPL_INLINE zpl_vec3 operator+(zpl_vec3 a) { return a; }
            ZPL_INLINE zpl_vec3 operator-(zpl_vec3 a) { zpl_vec3 r = {-a.x, -a.y, -a.z}; return r; }

            ZPL_INLINE zpl_vec3 operator+(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r; zpl_vec3_add(&r, a, b); return r; }
            ZPL_INLINE zpl_vec3 operator-(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r; zpl_vec3_sub(&r, a, b); return r; }

            ZPL_INLINE zpl_vec3 operator*(zpl_vec3 a, float scalar) { zpl_vec3 r; zpl_vec3_mul(&r, a, scalar); return r; }
            ZPL_INLINE zpl_vec3 operator*(float scalar, zpl_vec3 a) { return operator*(a, scalar); }

            ZPL_INLINE zpl_vec3 operator/(zpl_vec3 a, float scalar) { return operator*(a, 1.0f/scalar); }

            /* Hadamard Product */
            ZPL_INLINE zpl_vec3 operator*(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r = {a.x*b.x, a.y*b.y, a.z*b.z}; return r; }
            ZPL_INLINE zpl_vec3 operator/(zpl_vec3 a, zpl_vec3 b) { zpl_vec3 r = {a.x/b.x, a.y/b.y, a.z/b.z}; return r; }

            ZPL_INLINE zpl_vec3 &operator+=(zpl_vec3 &a, zpl_vec3 b)       { return (a = a + b); }
            ZPL_INLINE zpl_vec3 &operator-=(zpl_vec3 &a, zpl_vec3 b)       { return (a = a - b); }
            ZPL_INLINE zpl_vec3 &operator*=(zpl_vec3 &a, float scalar) { return (a = a * scalar); }
            ZPL_INLINE zpl_vec3 &operator/=(zpl_vec3 &a, float scalar) { return (a = a / scalar); }


            ZPL_INLINE bool operator==(zpl_vec4 a, zpl_vec4 b) { return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w); }
            ZPL_INLINE bool operator!=(zpl_vec4 a, zpl_vec4 b) { return !operator==(a, b); }

            ZPL_INLINE zpl_vec4 operator+(zpl_vec4 a) { return a; }
            ZPL_INLINE zpl_vec4 operator-(zpl_vec4 a) { zpl_vec4 r = {-a.x, -a.y, -a.z, -a.w}; return r; }

            ZPL_INLINE zpl_vec4 operator+(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r; zpl_vec4_add(&r, a, b); return r; }
            ZPL_INLINE zpl_vec4 operator-(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r; zpl_vec4_sub(&r, a, b); return r; }

            ZPL_INLINE zpl_vec4 operator*(zpl_vec4 a, float scalar) { zpl_vec4 r; zpl_vec4_mul(&r, a, scalar); return r; }
            ZPL_INLINE zpl_vec4 operator*(float scalar, zpl_vec4 a) { return operator*(a, scalar); }

            ZPL_INLINE zpl_vec4 operator/(zpl_vec4 a, float scalar) { return operator*(a, 1.0f/scalar); }

            /* Hadamard Product */
            ZPL_INLINE zpl_vec4 operator*(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r = {a.x*b.x, a.y*b.y, a.z*b.z, a.w*b.w}; return r; }
            ZPL_INLINE zpl_vec4 operator/(zpl_vec4 a, zpl_vec4 b) { zpl_vec4 r = {a.x/b.x, a.y/b.y, a.z/b.z, a.w/b.w}; return r; }

            ZPL_INLINE zpl_vec4 &operator+=(zpl_vec4 &a, zpl_vec4 b)       { return (a = a + b); }
            ZPL_INLINE zpl_vec4 &operator-=(zpl_vec4 &a, zpl_vec4 b)       { return (a = a - b); }
            ZPL_INLINE zpl_vec4 &operator*=(zpl_vec4 &a, float scalar) { return (a = a * scalar); }
            ZPL_INLINE zpl_vec4 &operator/=(zpl_vec4 &a, float scalar) { return (a = a / scalar); }


            ZPL_INLINE zpl_mat2 operator+(zpl_mat2 const &a, zpl_mat2 const &b) {
                int i, j;
                zpl_mat2 r = {0};
                for (j = 0; j < 2; j++) {
                    for (i = 0; i < 2; i++)
                        r.e[2*j+i] = a.e[2*j+i] + b.e[2*j+i];
                }
                return r;
            }

            ZPL_INLINE zpl_mat2 operator-(zpl_mat2 const &a, zpl_mat2 const &b) {
                int i, j;
                zpl_mat2 r = {0};
                for (j = 0; j < 2; j++) {
                    for (i = 0; i < 2; i++)
                        r.e[2*j+i] = a.e[2*j+i] - b.e[2*j+i];
                }
                return r;
            }

            ZPL_INLINE zpl_mat2 operator*(zpl_mat2 const &a, zpl_mat2 const &b) { zpl_mat2 r; zpl_mat2_mul(&r, (zpl_mat2 *)&a, (zpl_mat2 *)&b); return r; }
            ZPL_INLINE zpl_vec2 operator*(zpl_mat2 const &a, zpl_vec2 v) { zpl_vec2 r; zpl_mat2_mul_vec2(&r, (zpl_mat2 *)&a, v); return r; }
            ZPL_INLINE zpl_mat2 operator*(zpl_mat2 const &a, float scalar) {
                zpl_mat2 r = {0};
                int i;
                for (i = 0; i < 2*2; i++) r.e[i] = a.e[i] * scalar;
                return r;
            }
            ZPL_INLINE zpl_mat2 operator*(float scalar, zpl_mat2 const &a) { return operator*(a, scalar); }
            ZPL_INLINE zpl_mat2 operator/(zpl_mat2 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

            ZPL_INLINE zpl_mat2& operator+=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a + b); }
            ZPL_INLINE zpl_mat2& operator-=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a - b); }
            ZPL_INLINE zpl_mat2& operator*=(zpl_mat2& a, zpl_mat2 const &b) { return (a = a * b); }



            ZPL_INLINE zpl_mat3 operator+(zpl_mat3 const &a, zpl_mat3 const &b) {
                int i, j;
                zpl_mat3 r = {0};
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 3; i++)
                        r.e[3*j+i] = a.e[3*j+i] + b.e[3*j+i];
                }
                return r;
            }

            ZPL_INLINE zpl_mat3 operator-(zpl_mat3 const &a, zpl_mat3 const &b) {
                int i, j;
                zpl_mat3 r = {0};
                for (j = 0; j < 3; j++) {
                    for (i = 0; i < 3; i++)
                        r.e[3*j+i] = a.e[3*j+i] - b.e[3*j+i];
                }
                return r;
            }

            ZPL_INLINE zpl_mat3 operator*(zpl_mat3 const &a, zpl_mat3 const &b) { zpl_mat3 r; zpl_mat3_mul(&r, (zpl_mat3 *)&a, (zpl_mat3 *)&b); return r; }
            ZPL_INLINE zpl_vec3 operator*(zpl_mat3 const &a, zpl_vec3 v) { zpl_vec3 r; zpl_mat3_mul_vec3(&r, (zpl_mat3 *)&a, v); return r; }
            ZPL_INLINE zpl_mat3 operator*(zpl_mat3 const &a, float scalar) {
                zpl_mat3 r = {0};
                int i;
                for (i = 0; i < 3*3; i++) r.e[i] = a.e[i] * scalar;
                return r;
            }
            ZPL_INLINE zpl_mat3 operator*(float scalar, zpl_mat3 const &a) { return operator*(a, scalar); }
            ZPL_INLINE zpl_mat3 operator/(zpl_mat3 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

            ZPL_INLINE zpl_mat3& operator+=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a + b); }
            ZPL_INLINE zpl_mat3& operator-=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a - b); }
            ZPL_INLINE zpl_mat3& operator*=(zpl_mat3& a, zpl_mat3 const &b) { return (a = a * b); }



            ZPL_INLINE zpl_mat4 operator+(zpl_mat4 const &a, zpl_mat4 const &b) {
                int i, j;
                zpl_mat4 r = {0};
                for (j = 0; j < 4; j++) {
                    for (i = 0; i < 4; i++)
                        r.e[4*j+i] = a.e[4*j+i] + b.e[4*j+i];
                }
                return r;
            }

            ZPL_INLINE zpl_mat4 operator-(zpl_mat4 const &a, zpl_mat4 const &b) {
                int i, j;
                zpl_mat4 r = {0};
                for (j = 0; j < 4; j++) {
                    for (i = 0; i < 4; i++)
                        r.e[4*j+i] = a.e[4*j+i] - b.e[4*j+i];
                }
                return r;
            }

            ZPL_INLINE zpl_mat4 operator*(zpl_mat4 const &a, zpl_mat4 const &b) { zpl_mat4 r; zpl_mat4_mul(&r, (zpl_mat4 *)&a, (zpl_mat4 *)&b); return r; }
            ZPL_INLINE zpl_vec4 operator*(zpl_mat4 const &a, zpl_vec4 v) { zpl_vec4 r; zpl_mat4_mul_vec4(&r, (zpl_mat4 *)&a, v); return r; }
            ZPL_INLINE zpl_mat4 operator*(zpl_mat4 const &a, float scalar) {
                zpl_mat4 r = {0};
                int i;
                for (i = 0; i < 4*4; i++) r.e[i] = a.e[i] * scalar;
                return r;
            }
            ZPL_INLINE zpl_mat4 operator*(float scalar, zpl_mat4 const &a) { return operator*(a, scalar); }
            ZPL_INLINE zpl_mat4 operator/(zpl_mat4 const &a, float scalar) { return operator*(a, 1.0f/scalar); }

            ZPL_INLINE zpl_mat4& operator+=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a + b); }
            ZPL_INLINE zpl_mat4& operator-=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a - b); }
            ZPL_INLINE zpl_mat4& operator*=(zpl_mat4 &a, zpl_mat4 const &b) { return (a = a * b); }



            ZPL_INLINE bool operator==(zpl_quat a, zpl_quat b) { return a.xyzw == b.xyzw; }
            ZPL_INLINE bool operator!=(zpl_quat a, zpl_quat b) { return !operator==(a, b); }

            ZPL_INLINE zpl_quat operator+(zpl_quat q) { return q; }
            ZPL_INLINE zpl_quat operator-(zpl_quat q) { return zpl_quatf(-q.x, -q.y, -q.z, -q.w); }

            ZPL_INLINE zpl_quat operator+(zpl_quat a, zpl_quat b) { zpl_quat r; zpl_quat_add(&r, a, b); return r; }
            ZPL_INLINE zpl_quat operator-(zpl_quat a, zpl_quat b) { zpl_quat r; zpl_quat_sub(&r, a, b); return r; }

            ZPL_INLINE zpl_quat operator*(zpl_quat a, zpl_quat b)  { zpl_quat r; zpl_quat_mul(&r, a, b); return r; }
            ZPL_INLINE zpl_quat operator*(zpl_quat q, float s) { zpl_quat r; zpl_quat_mulf(&r, q, s); return r; }
            ZPL_INLINE zpl_quat operator*(float s, zpl_quat q) { return operator*(q, s); }
            ZPL_INLINE zpl_quat operator/(zpl_quat q, float s) { zpl_quat r; zpl_quat_divf(&r, q, s); return r; }

            ZPL_INLINE zpl_quat &operator+=(zpl_quat &a, zpl_quat b) { zpl_quat_addeq(&a, b); return a; }
            ZPL_INLINE zpl_quat &operator-=(zpl_quat &a, zpl_quat b) { zpl_quat_subeq(&a, b); return a; }
            ZPL_INLINE zpl_quat &operator*=(zpl_quat &a, zpl_quat b) { zpl_quat_muleq(&a, b); return a; }
            ZPL_INLINE zpl_quat &operator/=(zpl_quat &a, zpl_quat b) { zpl_quat_diveq(&a, b); return a; }

            ZPL_INLINE zpl_quat &operator*=(zpl_quat &a, float b) { zpl_quat_muleqf(&a, b); return a; }
            ZPL_INLINE zpl_quat &operator/=(zpl_quat &a, float b) { zpl_quat_diveqf(&a, b); return a; }

            /* Rotate v by a */
            ZPL_INLINE zpl_vec3 operator*(zpl_quat q, zpl_vec3 v) { zpl_vec3 r; zpl_quat_rotate_vec3(&r, q, v); return r; }
        #endif
    #endif

    #if defined(ZPL_MODULE_JSON)
        // file: header/json.h

        /** @file json.c
        @brief JSON5 Parser/Writer
        @defgroup json JSON5 parser/writer

        Easy to use and very fast JSON5 parser that can easily load 50 megabytes of JSON content under half a second. It also contains simple JSON5 writer and acts as a good library for handling config files. The parser also supports the **Simplified JSON (SJSON)** format.

        We can parse JSON5 files in two different modes:
            @n 1) Fast way (useful for raw data), which can not handle comments and might cause parsing failure if comment is present.
            @n 2) Slower way (useful for config files), which handles comments perfectly but **might** have performance impact
                on bigger JSON files. (+50MiB)
        @{
        */
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        //! Debug mode

        #ifdef ZPL_JSON_DEBUG
        #define ZPL_JSON_ASSERT ZPL_ASSERT(0)
        #else
        #define ZPL_JSON_ASSERT
        #endif

        //! JSON object types
        typedef enum zpl_json_type {
            ZPL_JSON_TYPE_OBJECT,
            ZPL_JSON_TYPE_STRING,
            ZPL_JSON_TYPE_MULTISTRING,
            ZPL_JSON_TYPE_ARRAY,
            ZPL_JSON_TYPE_INTEGER,
            ZPL_JSON_TYPE_REAL,
            ZPL_JSON_TYPE_CONSTANT
        } zpl_json_type;

        //! Field value properties
        typedef enum zpl_json_props {
            ZPL_JSON_PROPS_NONE         = 0,
            ZPL_JSON_PROPS_NAN          = 1,
            ZPL_JSON_PROPS_NAN_NEG      = 2,
            ZPL_JSON_PROPS_INFINITY     = 3,
            ZPL_JSON_PROPS_INFINITY_NEG = 4,
            ZPL_JSON_PROPS_IS_EXP       = 5,
            ZPL_JSON_PROPS_IS_HEX       = 6,

            // Used internally so that people can fill in real numbers for JSON files they plan to write.
            ZPL_JSON_PROPS_IS_PARSED_REAL = 7,
        } zpl_json_props;

        //! Value constants
        typedef enum zpl_json_const {
            ZPL_JSON_CONST_FALSE,
            ZPL_JSON_CONST_TRUE,
            ZPL_JSON_CONST_NULL,
        } zpl_json_const;

        // TODO(ZaKlaus): Error handling
        //! Parser error types
        typedef enum zpl_json_error {
            ZPL_JSON_ERROR_NONE,
            ZPL_JSON_ERROR_INVALID_NAME,
            ZPL_JSON_ERROR_INVALID_VALUE,
            ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL,
        } zpl_json_error;

        //! Field name decoration style
        typedef enum zpl_json_naming_style {
            ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE,
            ZPL_JSON_NAME_STYLE_SINGLE_QUOTE,
            ZPL_JSON_NAME_STYLE_NO_QUOTES,
        } zpl_json_naming_style;

        //! Field value assign style
        typedef enum zpl_json_assign_style {
            ZPL_JSON_ASSIGN_STYLE_COLON,
            ZPL_JSON_ASSIGN_STYLE_EQUALS,
            ZPL_JSON_ASSIGN_STYLE_LINE,
        } zpl_json_assign_style;

        //! Field delimiter style
        typedef enum zpl_json_delim_style {
            ZPL_JSON_DELIM_STYLE_COMMA,
            ZPL_JSON_DELIM_STYLE_LINE,
            ZPL_JSON_DELIM_STYLE_NEWLINE,
        } zpl_json_delim_style;

        #define zpl_json_object zpl_json_object

        //! JSON object definition.
        typedef struct zpl_json_object {
            zpl_allocator backing;
            char *name;
            zpl_u8 type        :6;
            zpl_u8 name_style  :2;
            zpl_u8 props       :7;
            zpl_u8 cfg_mode    :1;
            zpl_u8 assign_style:4;
            zpl_u8 delim_style :4;
            zpl_u8 delim_line_width;

            union {
                struct zpl_json_object *nodes;  ///< zpl_array
                zpl_i64 integer;
                char *string;

                struct {
                    zpl_f64 real;
                    zpl_i32 base;
                    zpl_i32 base2;
                    zpl_i32 base2_offset;
                    zpl_i32 exp;
                    zpl_u8 exp_neg   :1;
                    zpl_u8 lead_digit:1;
                };
                zpl_u8 constant;
            };
        } zpl_json_object;

        //! Parses JSON5/SJSON text.

        //! This method takes text form of JSON document as a source and parses its contents into JSON object structure we can work with. It also optionally handles comments that usually appear in documents used for configuration.
        //! @param root JSON object we store data to.
        //! @param len Text length. (reserved)
        //! @param source Text to be processed.
        //! @param allocator Memory allocator to use. (ex. zpl_heap())
        //! @param handle_comments Whether to handle possible comments or not. Note that if we won't handle comments in a document containing them, the parser will error out. See remark in source code.
        //! @param err_code Variable we will store error code in.
        ZPL_DEF void zpl_json_parse(zpl_json_object *root, zpl_usize len, char const *source, zpl_allocator allocator, zpl_b32 handle_comments,
                                    zpl_u8 *err_code);

        //! Exports JSON5 document into text form and outputs it into a file.

        //! This method takes JSON object tree and exports it into valid JSON5 form with the support of various styles that were preserved during import or set up programatically.
        //! @param file File we write text to.
        //! @param obj JSON object we export data from.
        //! @param indent Text indentation used during export. Use 0 for root objects.
        ZPL_DEF void zpl_json_write(zpl_file *file, zpl_json_object *obj, zpl_isize indent);

        //! Releases used resources by a JSON object.

        //! @param obj JSON object to free.
        ZPL_DEF void zpl_json_free(zpl_json_object *obj);

        //! Searches for a JSON node within a document by its name.

        //! @param obj JSON object to search in.
        //! @param name JSON node's name to search for.
        //! @param deep_search Perform the search recursively.
        ZPL_DEF zpl_json_object *zpl_json_find(zpl_json_object *obj, char const *name, zpl_b32 deep_search);

        //! Initializes a JSON node.

        //! @param obj JSON node to initialize.
        //! @param backing Memory allocator to use (ex. zpl_heap())
        //! @param name JSON node's name.
        //! @param type JSON node's type. (See zpl_json_type)
        //! @see zpl_json_type
        ZPL_DEF void zpl_json_init_node(zpl_json_object *obj, zpl_allocator backing, char const *name, zpl_u8 type);

        //! Adds object into JSON document at a specific index.

        //! Initializes and adds a JSON object into a JSON document at a specific index.
        //! @param obj Root node to add to.
        //! @param index Index to store at.
        //! @param name JSON node's name.
        //! @param type JSON node's type. (See zpl_json_type)
        //! @see zpl_json_type
        ZPL_DEF zpl_json_object *zpl_json_add_at(zpl_json_object *obj, zpl_isize index, char const *name, zpl_u8 type);

        //! Appends object into JSON document.

        //! Initializes and appends a JSON object into a JSON document.
        //! @param obj Root node to add to.
        //! @param name JSON node's name.
        //! @param type JSON node's type. (See zpl_json_type)
        //! @see zpl_json_type
        ZPL_DEF zpl_json_object *zpl_json_add(zpl_json_object *obj, char const *name, zpl_u8 type);

        //! @}

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_THREADING)
        #if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
            #include <pthread.h>
        #endif

        #if defined(ZPL_SYSTEM_WINDOWS)
            #if !defined(ZPL_NO_WINDOWS_H)
                #ifndef WIN32_LEAN_AND_MEAN
                    #define NOMINMAX
                    #define WIN32_LEAN_AND_MEAN
                    #define WIN32_MEAN_AND_LEAN
                    #define VC_EXTRALEAN
                #endif
                #include <windows.h>
                #undef NOMINMAX
                #undef WIN32_LEAN_AND_MEAN
                #undef WIN32_MEAN_AND_LEAN
                #undef VC_EXTRALEAN

                /* prevent it from including later */
                #define ZPL_NO_WINDOWS_H
            #endif

            // include errno.h for MinGW
            #if defined(ZPL_COMPILER_GCC)
                #include <errno.h>
            #endif
        #endif

        #if !defined(zpl_thread_local)
            #if defined(_MSC_VER) && _MSC_VER >= 1300
                #define zpl_thread_local __declspec(thread)
            #elif defined(__GNUC__)
                #define zpl_thread_local __thread
            #else
                #define zpl_thread_local thread_local
            #endif
        #endif

        // file: header/threading/atomic.h

        // Atomics
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        // TODO: Be specific with memory order?
        // e.g. relaxed, acquire, release, acquire_release

        #if !defined(__cplusplus) && !defined(ZPL_COMPILER_MSVC)
        # include <stdatomic.h>
        # define zpl_atomic(X) volatile _Atomic(X)
        #else
        // TODO: Fix once C++ guys bother to add C atomics to std.
        //# include <atomic>
        # define zpl_atomic(X) volatile X /*std::atomic<X>*/
        #endif

        #define zpl_atomicarg(X) volatile X

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_COMPILER_MSVC)
            typedef struct zpl_atomic32  { zpl_atomic(zpl_i32) value; } zpl_atomic32;
            typedef struct zpl_atomic64  { zpl_atomic(zpl_i64) value; } zpl_atomic64;
            typedef struct zpl_atomic_ptr { zpl_atomic(void*) value; } zpl_atomic_ptr;
        #else
            #if defined(ZPL_ARCH_32_BIT)
                #define ZPL_ATOMIC_PTR_ALIGNMENT 4
            #elif defined(ZPL_ARCH_64_BIT)
                #define ZPL_ATOMIC_PTR_ALIGNMENT 8
            #else
                #error Unknown architecture
            #endif

            typedef struct zpl_atomic32   { zpl_atomic(zpl_i32) value; } __attribute__ ((aligned(4))) zpl_atomic32;
            typedef struct zpl_atomic64   { zpl_atomic(zpl_i64) value; } __attribute__ ((aligned(8))) zpl_atomic64;
            typedef struct zpl_atomic_ptr { zpl_atomic(void*) value; }     __attribute__ ((aligned(ZPL_ATOMIC_PTR_ALIGNMENT))) zpl_atomic_ptr;
        #endif

        ZPL_DEF zpl_i32  zpl_atomic32_load            (zpl_atomic32 const *a);
        ZPL_DEF void     zpl_atomic32_store           (zpl_atomic32 *a, zpl_atomicarg(zpl_i32) value);
        ZPL_DEF zpl_i32  zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) expected, zpl_atomicarg(zpl_i32) desired);
        ZPL_DEF zpl_i32  zpl_atomic32_exchange        (zpl_atomic32 *a, zpl_atomicarg(zpl_i32) desired);
        ZPL_DEF zpl_i32  zpl_atomic32_fetch_add       (zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand);
        ZPL_DEF zpl_i32  zpl_atomic32_fetch_and       (zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand);
        ZPL_DEF zpl_i32  zpl_atomic32_fetch_or        (zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand);
        ZPL_DEF zpl_b32  zpl_atomic32_spin_lock       (zpl_atomic32 *a, zpl_isize time_out); // NOTE: time_out = -1 as default
        ZPL_DEF void     zpl_atomic32_spin_unlock     (zpl_atomic32 *a);
        ZPL_DEF zpl_b32  zpl_atomic32_try_acquire_lock(zpl_atomic32 *a);


        ZPL_DEF zpl_i64  zpl_atomic64_load            (zpl_atomic64 const *a);
        ZPL_DEF void     zpl_atomic64_store           (zpl_atomic64 *a, zpl_atomicarg(zpl_i64) value);
        ZPL_DEF zpl_i64  zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) expected, zpl_atomicarg(zpl_i64) desired);
        ZPL_DEF zpl_i64  zpl_atomic64_exchange        (zpl_atomic64 *a, zpl_atomicarg(zpl_i64) desired);
        ZPL_DEF zpl_i64  zpl_atomic64_fetch_add       (zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand);
        ZPL_DEF zpl_i64  zpl_atomic64_fetch_and       (zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand);
        ZPL_DEF zpl_i64  zpl_atomic64_fetch_or        (zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand);
        ZPL_DEF zpl_b32  zpl_atomic64_spin_lock       (zpl_atomic64 *a, zpl_isize time_out); // NOTE: time_out = -1 as default
        ZPL_DEF void     zpl_atomic64_spin_unlock     (zpl_atomic64 *a);
        ZPL_DEF zpl_b32  zpl_atomic64_try_acquire_lock(zpl_atomic64 *a);


        ZPL_DEF void *zpl_atomic_ptr_load            (zpl_atomic_ptr const *a);
        ZPL_DEF void      zpl_atomic_ptr_store           (zpl_atomic_ptr *a, zpl_atomicarg(void *)value);
        ZPL_DEF void *zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)expected, zpl_atomicarg(void *)desired);
        ZPL_DEF void *zpl_atomic_ptr_exchange        (zpl_atomic_ptr *a, zpl_atomicarg(void *)desired);
        ZPL_DEF void *zpl_atomic_ptr_fetch_add       (zpl_atomic_ptr *a, zpl_atomicarg(void *)operand);
        ZPL_DEF void *zpl_atomic_ptr_fetch_and       (zpl_atomic_ptr *a, zpl_atomicarg(void *)operand);
        ZPL_DEF void *zpl_atomic_ptr_fetch_or        (zpl_atomic_ptr *a, zpl_atomicarg(void *)operand);
        ZPL_DEF zpl_b32   zpl_atomic_ptr_spin_lock       (zpl_atomic_ptr *a, zpl_isize time_out); // NOTE: time_out = -1 as default
        ZPL_DEF void      zpl_atomic_ptr_spin_unlock     (zpl_atomic_ptr *a);
        ZPL_DEF zpl_b32   zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr *a);

        ZPL_END_C_DECLS
        // file: header/threading/fence.h

        // Fences
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_DEF void zpl_yield_thread(void);
        ZPL_DEF void zpl_mfence      (void);
        ZPL_DEF void zpl_sfence      (void);
        ZPL_DEF void zpl_lfence      (void);

        ZPL_END_C_DECLS
        // file: header/threading/sem.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_SYSTEM_MACOS)
            #include <mach/thread_act.h>
        #elif defined(ZPL_SYSTEM_UNIX)
            #include <semaphore.h>
        #endif

        #if defined(ZPL_SYSTEM_WINDOWS)
            typedef struct zpl_semaphore { void *win32_handle; }     zpl_semaphore;
        #elif defined(ZPL_SYSTEM_MACOS)
            typedef struct zpl_semaphore { semaphore_t osx_handle; } zpl_semaphore;
        #elif defined(ZPL_SYSTEM_UNIX)
            typedef struct zpl_semaphore { sem_t unix_handle; }      zpl_semaphore;
        #else
            #error
        #endif

        ZPL_DEF void zpl_semaphore_init   (zpl_semaphore *s);
        ZPL_DEF void zpl_semaphore_destroy(zpl_semaphore *s);
        ZPL_DEF void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count);
        ZPL_DEF void zpl_semaphore_release(zpl_semaphore *s); // NOTE: zpl_semaphore_post(s, 1)
        ZPL_DEF void zpl_semaphore_wait   (zpl_semaphore *s);

        ZPL_END_C_DECLS
        // file: header/threading/mutex.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_mutex {
        #if defined(ZPL_SYSTEM_WINDOWS)
            CRITICAL_SECTION win32_critical_section;
        #else
            pthread_mutex_t pthread_mutex;
        #endif
        } zpl_mutex;

        ZPL_DEF void     zpl_mutex_init    (zpl_mutex *m);
        ZPL_DEF void     zpl_mutex_destroy (zpl_mutex *m);
        ZPL_DEF void     zpl_mutex_lock    (zpl_mutex *m);
        ZPL_DEF zpl_b32  zpl_mutex_try_lock(zpl_mutex *m);
        ZPL_DEF void     zpl_mutex_unlock  (zpl_mutex *m);

        ZPL_END_C_DECLS
        // file: header/threading/thread.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #else
        struct zpl_thread;
        #endif

        ZPL_BEGIN_C_DECLS

        typedef zpl_isize (*zpl_thread_proc)(struct zpl_thread *thread);

        typedef struct zpl_thread {
        #if defined(ZPL_SYSTEM_WINDOWS)
            void *        win32_handle;
        #else
            pthread_t     posix_handle;
        #endif

            zpl_thread_proc  proc;
            void *           user_data;
            zpl_isize        user_index;
            zpl_isize        return_value;

            zpl_semaphore    semaphore;
            zpl_isize        stack_size;
            zpl_b32          is_running;
        } zpl_thread;

        ZPL_DEF void     zpl_thread_init            (zpl_thread *t);
        ZPL_DEF void     zpl_thread_destroy         (zpl_thread *t);
        ZPL_DEF void     zpl_thread_start           (zpl_thread *t, zpl_thread_proc proc, void *data);
        ZPL_DEF void     zpl_thread_start_with_stack(zpl_thread *t, zpl_thread_proc proc, void *data, zpl_isize stack_size);
        ZPL_DEF void     zpl_thread_join            (zpl_thread *t);
        ZPL_DEF zpl_b32  zpl_thread_is_running      (zpl_thread const *t);
        ZPL_DEF zpl_u32  zpl_thread_current_id      (void);
        ZPL_DEF void     zpl_thread_set_name        (zpl_thread *t, char const *name);

        ZPL_END_C_DECLS
        // file: header/threading/sync.h

        // NOTE: Thread Merge Operation
        // Based on Sean Barrett's stb_sync
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef struct zpl_sync {
            zpl_i32 target;  // Target Number of threads
            zpl_i32 current; // Threads to hit
            zpl_i32 waiting; // Threads waiting

            zpl_mutex start;
            zpl_mutex mutex;
            zpl_semaphore release;
        } zpl_sync;

        ZPL_DEF void     zpl_sync_init          (zpl_sync *s);
        ZPL_DEF void     zpl_sync_destroy       (zpl_sync *s);
        ZPL_DEF void     zpl_sync_set_target    (zpl_sync *s, zpl_i32 count);
        ZPL_DEF void     zpl_sync_release       (zpl_sync *s);
        ZPL_DEF zpl_i32  zpl_sync_reach         (zpl_sync *s);
        ZPL_DEF void     zpl_sync_reach_and_wait(zpl_sync *s);

        ZPL_END_C_DECLS
        // file: header/threading/affinity.h

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_SYSTEM_WINDOWS) || defined (ZPL_SYSTEM_CYGWIN)

            typedef struct zpl_affinity {
                zpl_b32   is_accurate;
                zpl_isize core_count;
                zpl_isize thread_count;

            #define ZPL_WIN32_MAX_THREADS (8 * zpl_size_of(zpl_usize))
                zpl_usize core_masks[ZPL_WIN32_MAX_THREADS];
            } zpl_affinity;

        #elif defined(ZPL_SYSTEM_OSX)

            typedef struct zpl_affinity {
                zpl_b32   is_accurate;
                zpl_isize core_count;
                zpl_isize thread_count;
                zpl_isize threads_per_core;
            } zpl_affinity;

        #elif defined(ZPL_SYSTEM_LINUX) || defined(ZPL_SYSTEM_FREEBSD) || defined(ZPL_SYSTEM_EMSCRIPTEN) || defined(ZPL_SYSTEM_OPENBSD)

            typedef struct zpl_affinity {
                zpl_b32   is_accurate;
                zpl_isize core_count;
                zpl_isize thread_count;
                zpl_isize threads_per_core;
            } zpl_affinity;

        #else
            #error TODO: Unknown system
        #endif

        ZPL_DEF void      zpl_affinity_init   (zpl_affinity *a);
        ZPL_DEF void      zpl_affinity_destroy(zpl_affinity *a);
        ZPL_DEF zpl_b32   zpl_affinity_set    (zpl_affinity *a, zpl_isize core, zpl_isize thread);
        ZPL_DEF zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core);

        ZPL_END_C_DECLS

        #if defined(ZPL_MODULE_JOBS)
            // file: header/jobs.h

            /** @file threadpool.c
            @brief Job system
            @defgroup jobs Job system

             This job system follows thread pool pattern to minimize the costs of thread initialization.
             It reuses fixed number of threads to process variable number of jobs.

             @{
             */
            #ifdef ZPL_EDITOR
            #include <zpl.h>
            #endif

            ZPL_BEGIN_C_DECLS

            typedef void (*zpl_jobs_proc)(void *data);

            #define ZPL_INVALID_JOB ZPL_U32_MAX

            typedef enum {
                ZPL_JOBS_STATUS_READY,
                ZPL_JOBS_STATUS_BUSY,
                ZPL_JOBS_STATUS_WAITING,
                ZPL_JOBS_STATUS_TERM,
            } zpl_jobs_status;

            typedef struct {
                zpl_jobs_proc proc;
                void *data;

                zpl_i32 priority;
            } zpl_thread_job;

            typedef struct {
                zpl_thread thread;
                zpl_atomic32 status;
                zpl_u32 jobid;
                void *pool;
            } zpl_thread_worker;

            typedef struct {
                zpl_allocator alloc;
                zpl_u32 max_threads;
                zpl_f32 job_spawn_treshold;
                zpl_mutex access;
                zpl_thread_worker *workers; ///< zpl_buffer
                zpl_thread_job *jobs; ///< zpl_array
                zpl_u32 *queue; ///< zpl_array
                zpl_u32 *available; ///< zpl_array
            } zpl_thread_pool;

            //! Initialize thread pool with specified amount of fixed threads.
            ZPL_DEF void    zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads);

            //! Release the resources use by thread pool.
            ZPL_DEF void    zpl_jobs_free(zpl_thread_pool *pool);

            //! Enqueue a job with specified data.
            ZPL_DEF void    zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data);

            //! Enqueue a job with specific priority with specified data.
            ZPL_DEF void    zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, zpl_i32 priority);

            //! Process all jobs and check all threads. Should be called by Main Thread in a tight loop.
            ZPL_DEF zpl_b32 zpl_jobs_process(zpl_thread_pool *pool);

            ZPL_END_C_DECLS
        #endif

        #if defined(ZPL_MODULE_COROUTINES)
            // file: header/coroutines.h

            /** @file coroutines.c
            @brief Coroutines module
            @defgroup misc Coroutines module

             This module implements co-routines feature for C99.

             @{
             */
            /*
               See test/coroutines.c for an example usage
             */
            #ifdef ZPL_EDITOR
            #include <zpl.h>
            #endif

            ZPL_BEGIN_C_DECLS

            #ifndef ZPL_CO_ARG_STACK_CAPACITY
            #define ZPL_CO_ARG_STACK_CAPACITY 128
            #endif

            typedef enum {
                ZPL_CO_READY,
                ZPL_CO_ENQUEUED,
                ZPL_CO_RUNNING,
                ZPL_CO_WAITING,
                ZPL_CO_DEAD,
            } zpl_co_status;

            struct zpl_co;

            typedef void (*zpl_co_proc)(struct zpl_co *co);

            typedef struct zpl_co {
                zpl_atomic32  status;
                zpl_co_proc   f;
                void         *data; // overwritten internally, use inside of co-routines
                void         *data_stack[ZPL_CO_ARG_STACK_CAPACITY];
                zpl_i32       data_read_idx, data_write_idx;
                zpl_atomic32  resume, push_arg;
            } zpl_co;

            // These methods are used to initialize the co-routine subsystem

            /**
             * Initializes the coroutines subsystem
             * @param  a           Memory allocator to be used
             * @param  max_threads Maximum amount of threads to use for coroutines execution
             */
            ZPL_DEF void   zpl_co_init(zpl_allocator a, zpl_u32 max_threads);

            /**
             * Destroys the coroutines subsystem
             *
             * IMPORTANT: This is a blocking method that waits until all the coroutines are finished.
             * Please, make sure your coroutines are correctly designed, so that you
             * won't end up in an infinite loop.
             */
            ZPL_DEF void   zpl_co_destroy(void);

            // These methods are used by the host to create and run/resume co-routines
            // Make sure the co-routine subsystem is initialized first!

            /**
             * Create a paused coroutine
             * @param  co Coroutine reference
             * @param  f  Coroutine method
             */
            ZPL_DEF void zpl_co_make(zpl_co *co, zpl_co_proc f);

            /**
             * Starts/Resumes a coroutine execution.
             *
             * IMPORTANT: Data you pass is stored in a stack of up to ZPL_CO_ARG_STACK_CAPACITY.
             * This means that you can cause stack corruption if you
             * call 'zpl_co_resume' with data passed (ZPL_CO_ARG_STACK_CAPACITY+1) times.
             * Raise the number by defining ZPL_CO_ARG_STACK_CAPACITY if required.
             *
             * @param  co   Coroutine
             * @param  data Data we want to pass (or NULL)
             */
            ZPL_DEF void    zpl_co_resume(zpl_co *co, void *data);

            /**
             * Is a coroutine running at the moment?
             * @param  co Coroutine
             * @return
             */
            ZPL_DEF_INLINE zpl_b32 zpl_co_running(zpl_co *co);

            /**
             * Is a coroutine already finished?
             * @param  co Coroutine
             * @return
             */
            ZPL_DEF_INLINE zpl_b32 zpl_co_finished(zpl_co *co);

            /**
             * Is coroutine waiting? (in yield state)
             * @param  co Coroutine
             * @return
             */
            ZPL_DEF_INLINE zpl_b32 zpl_co_waiting(zpl_co *co);

            // This method is used by the co-routine to await execution
            //

            /**
             * Yield the coroutine.
             *
             * IMPORTANT: Only to be used by the coroutine!!
             * @param  co Coroutine
             */
            ZPL_DEF void   zpl_co_yield(zpl_co *co);

            //! @}

            ZPL_IMPL_INLINE zpl_b32 zpl_co_running(zpl_co *co) {
                return zpl_atomic32_load(&co->status) == ZPL_CO_RUNNING;
            }

            ZPL_IMPL_INLINE zpl_b32 zpl_co_finished(zpl_co *co) {
                return zpl_atomic32_load(&co->status) == ZPL_CO_DEAD;
            }

            ZPL_IMPL_INLINE zpl_b32 zpl_co_waiting(zpl_co *co) {
                return zpl_atomic32_load(&co->resume) == 0;
            }

            ZPL_END_C_DECLS
        #endif
    #endif

    #if defined(ZPL_COMPILER_MSVC)
        #pragma warning(pop)
    #endif

    #if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic pop
    #endif

    #if defined(ZPL_IMPLEMENTATION) && !defined(ZPL_IMPLEMENTATION_DONE)
    #define ZPL_IMPLEMENTATION_DONE

    #if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wattributes"
        #pragma GCC diagnostic ignored "-Wunused-value"
        #pragma GCC diagnostic ignored "-Wunused-function"
        #pragma GCC diagnostic ignored "-Wwrite-strings"
        #pragma GCC diagnostic ignored "-Wunused-parameter"
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        #pragma GCC diagnostic ignored "-Wmissing-braces"
        #pragma GCC diagnostic ignored "-Wmissing-field-initializers"
        #pragma GCC diagnostic ignored "-Wimplicit-fallthrough"
    #endif

    #if defined(_MSC_VER)
        #pragma warning(push)
        #pragma warning(disable : 4201)
        #pragma warning(disable : 4127) // Conditional expression is constant
    #endif

    /* general purpose includes */

    #include <stdio.h>

    #if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
        #include <unistd.h>
        #include <errno.h>
    #elif defined(ZPL_SYSTEM_WINDOWS)
        #if !defined(ZPL_NO_WINDOWS_H)
            #ifndef WIN32_LEAN_AND_MEAN
                #ifndef NOMINMAX
                #define NOMINMAX
                #endif

                #define WIN32_LEAN_AND_MEAN
                #define WIN32_MEAN_AND_LEAN
                #define VC_EXTRALEAN
            #endif
            #include <windows.h>
            #undef NOMINMAX
            #undef WIN32_LEAN_AND_MEAN
            #undef WIN32_MEAN_AND_LEAN
            #undef VC_EXTRALEAN
        #endif
    #endif

    #if defined(ZPL_MODULE_CORE)
        // file: source/core/debug.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        void zpl_assert_handler(char const *condition, char const *file, zpl_i32 line, char const *msg, ...) {
            zpl_printf_err("%s:(%d): Assert Failure: ", file, line);

            if (condition) zpl_printf_err("`%s` ", condition);

            if (msg) {
                va_list va;
                va_start(va, msg);
                zpl_printf_err_va(msg, va);
                va_end(va);
            }

            zpl_printf_err("\n");
        }

        zpl_i32 zpl_assert_crash(char const *condition) {
            ZPL_PANIC(condition);
            return 0;
        }

        ZPL_END_C_DECLS
        // file: source/core/memory.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #include <string.h>

        ZPL_BEGIN_C_DECLS


        void zpl_memswap(void *i, void *j, zpl_isize size) {
            if (i == j) return;

            if (size == 4) {
                zpl_swap(zpl_u32, *cast(zpl_u32 *) i, *cast(zpl_u32 *) j);
            } else if (size == 8) {
                zpl_swap(zpl_u64, *cast(zpl_u64 *) i, *cast(zpl_u64 *) j);
            } else if (size < 8) {
                zpl_u8 *a = cast(zpl_u8 *) i;
                zpl_u8 *b = cast(zpl_u8 *) j;
                if (a != b) {
                    while (size--) { zpl_swap(zpl_u8, *a++, *b++); }
                }
            } else {
                char buffer[256];

                while (size > zpl_size_of(buffer)) {
                    zpl_memswap(i, j, zpl_size_of(buffer));
                    i = zpl_pointer_add(i, zpl_size_of(buffer));
                    j = zpl_pointer_add(j, zpl_size_of(buffer));
                    size -= zpl_size_of(buffer);
                }

                zpl_memcopy(buffer, i, size);
                zpl_memcopy(i, j, size);
                zpl_memcopy(j, buffer, size);
            }
        }

        void const *zpl_memchr(void const *data, zpl_u8 c, zpl_isize n) {
            zpl_u8 const *s = cast(zpl_u8 const *) data;
            while ((cast(zpl_uintptr) s & (sizeof(zpl_usize) - 1)) && n && *s != c) {
                s++;
                n--;
            }
            if (n && *s != c) {
                zpl_isize const *w;
                zpl_isize k = ZPL__ONES * c;
                w = cast(zpl_isize const *) s;
                while (n >= zpl_size_of(zpl_isize) && !ZPL__HAS_ZERO(*w ^ k)) {
                    w++;
                    n -= zpl_size_of(zpl_isize);
                }
                s = cast(zpl_u8 const *) w;
                while (n && *s != c) {
                    s++;
                    n--;
                }
            }

            return n ? cast(void const *) s : NULL;
        }

        void const *zpl_memrchr(void const *data, zpl_u8 c, zpl_isize n) {
            zpl_u8 const *s = cast(zpl_u8 const *) data;
            while (n--) {
                if (s[n] == c) return cast(void const *)(s + n);
            }
            return NULL;
        }

        void *zpl_memcopy(void *dest, void const *source, zpl_isize n) {
            if (dest == NULL) { return NULL; }

            return memcpy(dest, source, n);

            // TODO: Re-work the whole method
        #if 0
        #if defined(_MSC_VER)
            __movsb(cast(zpl_u8 *) dest, cast(zpl_u8 *) source, n);
        #elif defined(ZPL_CPU_X86) && !defined(ZPL_SYSTEM_EMSCRIPTEN)
            zpl_u8 *__dest8 = cast(zpl_u8 *) dest;
            zpl_u8 *__source8 = cast(zpl_u8 *) source;
            __asm__ __volatile__("rep movsb" : "+D"(__dest8), "+S"(__source8), "+c"(n) : : "memory");
        #elif defined(ZPL_CPU_ARM)
            return memcpy(dest, source, n);
        #else
            zpl_u8 *d = cast(zpl_u8 *) dest;
            zpl_u8 const *s = cast(zpl_u8 const *) source;
            zpl_u32 w, x;

            for (; cast(zpl_uintptr) s % 4 && n; n--) *d++ = *s++;

            if (cast(zpl_uintptr) d % 4 == 0) {
                for (; n >= 16; s += 16, d += 16, n -= 16) {
                    *cast(zpl_u32 *)(d + 0) = *cast(zpl_u32 *)(s + 0);
                    *cast(zpl_u32 *)(d + 4) = *cast(zpl_u32 *)(s + 4);
                    *cast(zpl_u32 *)(d + 8) = *cast(zpl_u32 *)(s + 8);
                    *cast(zpl_u32 *)(d + 12) = *cast(zpl_u32 *)(s + 12);
                }
                if (n & 8) {
                    *cast(zpl_u32 *)(d + 0) = *cast(zpl_u32 *)(s + 0);
                    *cast(zpl_u32 *)(d + 4) = *cast(zpl_u32 *)(s + 4);
                    d += 8;
                    s += 8;
                }
                if (n & 4) {
                    *cast(zpl_u32 *)(d + 0) = *cast(zpl_u32 *)(s + 0);
                    d += 4;
                    s += 4;
                }
                if (n & 2) {
                    *d++ = *s++;
                    *d++ = *s++;
                }
                if (n & 1) { *d = *s; }
                return dest;
            }

            if (n >= 32) {
        #if __BYTE_ORDER == __BIG_ENDIAN
        #define LS <<
        #define RS >>
        #else
        #define LS >>
        #define RS <<
        #endif
                switch (cast(zpl_uintptr) d % 4) {
                    case 1: {
                        w = *cast(zpl_u32 *) s;
                        *d++ = *s++;
                        *d++ = *s++;
                        *d++ = *s++;
                        n -= 3;
                        while (n > 16) {
                            x = *cast(zpl_u32 *)(s + 1);
                            *cast(zpl_u32 *)(d + 0) = (w LS 24) | (x RS 8);
                            w = *cast(zpl_u32 *)(s + 5);
                            *cast(zpl_u32 *)(d + 4) = (x LS 24) | (w RS 8);
                            x = *cast(zpl_u32 *)(s + 9);
                            *cast(zpl_u32 *)(d + 8) = (w LS 24) | (x RS 8);
                            w = *cast(zpl_u32 *)(s + 13);
                            *cast(zpl_u32 *)(d + 12) = (x LS 24) | (w RS 8);

                            s += 16;
                            d += 16;
                            n -= 16;
                        }
                    } break;
                    case 2: {
                        w = *cast(zpl_u32 *) s;
                        *d++ = *s++;
                        *d++ = *s++;
                        n -= 2;
                        while (n > 17) {
                            x = *cast(zpl_u32 *)(s + 2);
                            *cast(zpl_u32 *)(d + 0) = (w LS 16) | (x RS 16);
                            w = *cast(zpl_u32 *)(s + 6);
                            *cast(zpl_u32 *)(d + 4) = (x LS 16) | (w RS 16);
                            x = *cast(zpl_u32 *)(s + 10);
                            *cast(zpl_u32 *)(d + 8) = (w LS 16) | (x RS 16);
                            w = *cast(zpl_u32 *)(s + 14);
                            *cast(zpl_u32 *)(d + 12) = (x LS 16) | (w RS 16);

                            s += 16;
                            d += 16;
                            n -= 16;
                        }
                    } break;
                    case 3: {
                        w = *cast(zpl_u32 *) s;
                        *d++ = *s++;
                        n -= 1;
                        while (n > 18) {
                            x = *cast(zpl_u32 *)(s + 3);
                            *cast(zpl_u32 *)(d + 0) = (w LS 8) | (x RS 24);
                            w = *cast(zpl_u32 *)(s + 7);
                            *cast(zpl_u32 *)(d + 4) = (x LS 8) | (w RS 24);
                            x = *cast(zpl_u32 *)(s + 11);
                            *cast(zpl_u32 *)(d + 8) = (w LS 8) | (x RS 24);
                            w = *cast(zpl_u32 *)(s + 15);
                            *cast(zpl_u32 *)(d + 12) = (x LS 8) | (w RS 24);

                            s += 16;
                            d += 16;
                            n -= 16;
                        }
                    } break;
                    default: break; // NOTE: Do nowt!
                }
        #undef LS
        #undef RS
                if (n & 16) {
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                }
                if (n & 8) {
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                }
                if (n & 4) {
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                    *d++ = *s++;
                }
                if (n & 2) {
                    *d++ = *s++;
                    *d++ = *s++;
                }
                if (n & 1) { *d = *s; }
            }

        #endif
        #endif

            return dest;
        }

        ZPL_END_C_DECLS
        // file: source/core/memory_virtual.c

        ////////////////////////////////////////////////////////////////
        //
        // Virtual Memory
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_virtual_memory zpl_vm(void *data, zpl_isize size) {
            zpl_virtual_memory vm;
            vm.data = data;
            vm.size = size;
            return vm;
        }

        #if defined(ZPL_SYSTEM_WINDOWS)
            zpl_virtual_memory zpl_vm_alloc(void *addr, zpl_isize size) {
                zpl_virtual_memory vm;
                ZPL_ASSERT(size > 0);
                vm.data = VirtualAlloc(addr, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
                vm.size = size;
                return vm;
            }

            zpl_b32 zpl_vm_free(zpl_virtual_memory vm) {
                MEMORY_BASIC_INFORMATION info;
                while (vm.size > 0) {
                    if (VirtualQuery(vm.data, &info, zpl_size_of(info)) == 0) return false;
                    if (info.BaseAddress != vm.data || info.AllocationBase != vm.data || info.State != MEM_COMMIT ||
                        info.RegionSize > cast(zpl_usize) vm.size) {
                        return false;
                    }
                    if (VirtualFree(vm.data, 0, MEM_RELEASE) == 0) return false;
                    vm.data = zpl_pointer_add(vm.data, info.RegionSize);
                    vm.size -= info.RegionSize;
                }
                return true;
            }

            zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, zpl_isize lead_size, zpl_isize size) {
                zpl_virtual_memory new_vm = { 0 };
                void *ptr;
                ZPL_ASSERT(vm.size >= lead_size + size);

                ptr = zpl_pointer_add(vm.data, lead_size);

                zpl_vm_free(vm);
                new_vm = zpl_vm_alloc(ptr, size);
                if (new_vm.data == ptr) return new_vm;
                if (new_vm.data) zpl_vm_free(new_vm);
                return new_vm;
            }

            zpl_b32 zpl_vm_purge(zpl_virtual_memory vm) {
                VirtualAlloc(vm.data, vm.size, MEM_RESET, PAGE_READWRITE);
                // NOTE: Can this really fail?
                return true;
            }

            zpl_isize zpl_virtual_memory_page_size(zpl_isize *alignment_out) {
                SYSTEM_INFO info;
                GetSystemInfo(&info);
                if (alignment_out) *alignment_out = info.dwAllocationGranularity;
                return info.dwPageSize;
            }

        #else
            #include <sys/mman.h>

            #ifndef MAP_ANONYMOUS
                #define MAP_ANONYMOUS MAP_ANON
            #endif

            zpl_virtual_memory zpl_vm_alloc(void *addr, zpl_isize size) {
                zpl_virtual_memory vm;
                ZPL_ASSERT(size > 0);
                vm.data = mmap(addr, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
                vm.size = size;
                return vm;
            }

            zpl_b32 zpl_vm_free(zpl_virtual_memory vm) {
                munmap(vm.data, vm.size);
                return true;
            }

            zpl_virtual_memory zpl_vm_trim(zpl_virtual_memory vm, zpl_isize lead_size, zpl_isize size) {
                void *ptr;
                zpl_isize trail_size;
                ZPL_ASSERT(vm.size >= lead_size + size);

                ptr = zpl_pointer_add(vm.data, lead_size);
                trail_size = vm.size - lead_size - size;

                if (lead_size != 0) zpl_vm_free(zpl_vm(vm.data, lead_size));
                if (trail_size != 0) zpl_vm_free(zpl_vm(ptr, trail_size));
                return zpl_vm(ptr, size);
            }

            zpl_b32 zpl_vm_purge(zpl_virtual_memory vm) {
                int err = madvise(vm.data, vm.size, MADV_DONTNEED);
                return err != 0;
            }

            zpl_isize zpl_virtual_memory_page_size(zpl_isize *alignment_out) {
                // TODO: Is this always true?
                zpl_isize result = cast(zpl_isize) sysconf(_SC_PAGE_SIZE);
                if (alignment_out) *alignment_out = result;
                return result;
            }

        #endif

        ZPL_END_C_DECLS
        // file: source/core/memory_custom.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #ifndef _IOSC11_SOURCE
        #define _IOSC11_SOURCE
        #endif

        #include <stdlib.h>

        #if defined(ZPL_SYSTEM_WINDOWS)
            #include <malloc.h>
        #endif

        #if defined(ZPL_COMPILER_MINGW)
            #ifdef __MINGW32__
            #define _aligned_malloc __mingw_aligned_malloc
            #define _aligned_free  __mingw_aligned_free
            #endif //MINGW
        #endif

        ZPL_BEGIN_C_DECLS

        char *zpl_alloc_str(zpl_allocator a, char const *str) {
            return zpl_alloc_str_len(a, str, zpl_strlen(str));
        }

        ////////////////////////////////////////////////////////////////
        //
        // Custom Allocation
        //
        //

        //
        // Heap Allocator
        //

        ZPL_ALLOCATOR_PROC(zpl_heap_allocator_proc) {
            void *ptr = NULL;
            zpl_unused(allocator_data);
            zpl_unused(old_size);
            // TODO: Throughly test!
            switch (type) {
        #if defined(ZPL_COMPILER_MSVC) || (defined(ZPL_COMPILER_GCC) && defined(ZPL_SYSTEM_WINDOWS))
                case ZPL_ALLOCATION_ALLOC:
                ptr = _aligned_malloc(size, alignment);
                if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
                break;
                case ZPL_ALLOCATION_FREE: _aligned_free(old_memory); break;
                case ZPL_ALLOCATION_RESIZE: ptr = _aligned_realloc(old_memory, size, alignment); break;

        #elif defined(ZPL_SYSTEM_LINUX) && !defined(ZPL_CPU_ARM)
                case ZPL_ALLOCATION_ALLOC: {
                    ptr = aligned_alloc(alignment, size);

                    if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) { zpl_zero_size(ptr, size); }
                } break;

                case ZPL_ALLOCATION_FREE: {
                    free(old_memory);
                } break;

                case ZPL_ALLOCATION_RESIZE: {
                    zpl_allocator a = zpl_heap_allocator( );
                    ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment);
                } break;
        #else
                case ZPL_ALLOCATION_ALLOC: {
                    posix_memalign(&ptr, alignment, size);

                    if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) { zpl_zero_size(ptr, size); }
                } break;

                case ZPL_ALLOCATION_FREE: {
                    free(old_memory);
                } break;

                case ZPL_ALLOCATION_RESIZE: {
                    zpl_allocator a = zpl_heap_allocator( );
                    ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment);
                } break;
        #endif

                case ZPL_ALLOCATION_FREE_ALL: break;
            }

            return ptr;
        }

        //
        // Arena Allocator
        //

        ZPL_ALLOCATOR_PROC(zpl_arena_allocator_proc) {
            zpl_arena *arena = cast(zpl_arena *) allocator_data;
            void *ptr = NULL;

            zpl_unused(old_size);

            switch (type) {
                case ZPL_ALLOCATION_ALLOC: {
                    void *end = zpl_pointer_add(arena->physical_start, arena->total_allocated);
                    zpl_isize total_size = size + alignment;

                    // NOTE: Out of memory
                    if (arena->total_allocated + total_size > cast(zpl_isize) arena->total_size) {
                        zpl_printf_err("Arena out of memory\n");
                        return NULL;
                    }

                    ptr = zpl_align_forward(end, alignment);
                    arena->total_allocated += total_size;
                    if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
                } break;

                case ZPL_ALLOCATION_FREE:
                // NOTE: Free all at once
                // Use Temp_Arena_Memory if you want to free a block
                break;

                case ZPL_ALLOCATION_FREE_ALL: arena->total_allocated = 0; break;

                case ZPL_ALLOCATION_RESIZE: {
                    // TODO: Check if ptr is on top of stack and just extend
                    zpl_allocator a = zpl_arena_allocator(arena);
                    ptr = zpl_default_resize_align(a, old_memory, old_size, size, alignment);
                } break;
            }
            return ptr;
        }

        //
        // Pool Allocator
        //

        void zpl_pool_init_align(zpl_pool *pool, zpl_allocator backing, zpl_isize num_blocks, zpl_isize block_size, zpl_isize block_align) {
            zpl_isize actual_block_size, pool_size, block_index;
            void *data, *curr;
            zpl_uintptr *end;

            zpl_zero_item(pool);

            pool->backing = backing;
            pool->block_size = block_size;
            pool->block_align = block_align;
            pool->num_blocks = num_blocks;

            actual_block_size = block_size + block_align;
            pool_size = num_blocks * actual_block_size;

            data = zpl_alloc_align(backing, pool_size, block_align);

            // NOTE: Init intrusive freelist
            curr = data;
            for (block_index = 0; block_index < num_blocks - 1; block_index++) {
                zpl_uintptr *next = cast(zpl_uintptr *) curr;
                *next = cast(zpl_uintptr) curr + actual_block_size;
                curr = zpl_pointer_add(curr, actual_block_size);
            }

            end = cast(zpl_uintptr *) curr;
            *end = cast(zpl_uintptr) NULL;

            pool->physical_start = data;
            pool->free_list = data;
        }

        ZPL_ALLOCATOR_PROC(zpl_pool_allocator_proc) {
            zpl_pool *pool = cast(zpl_pool *) allocator_data;
            void *ptr = NULL;

            zpl_unused(old_size);

            switch (type) {
                case ZPL_ALLOCATION_ALLOC: {
                    zpl_uintptr next_free;
                    ZPL_ASSERT(size == pool->block_size);
                    ZPL_ASSERT(alignment == pool->block_align);
                    ZPL_ASSERT(pool->free_list != NULL);

                    next_free = *cast(zpl_uintptr *) pool->free_list;
                    ptr = pool->free_list;
                    pool->free_list = cast(void *) next_free;
                    pool->total_size += pool->block_size;
                    if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
                } break;

                case ZPL_ALLOCATION_FREE: {
                    zpl_uintptr *next;
                    if (old_memory == NULL) return NULL;

                    next = cast(zpl_uintptr *) old_memory;
                    *next = cast(zpl_uintptr) pool->free_list;
                    pool->free_list = old_memory;
                    pool->total_size -= pool->block_size;
                } break;

                case ZPL_ALLOCATION_FREE_ALL: {
                    zpl_isize actual_block_size, block_index;
                    void *curr;
                    zpl_uintptr *end;

                    actual_block_size = pool->block_size + pool->block_align;
                    pool->total_size = 0;

                    // NOTE: Init intrusive freelist
                    curr = pool->physical_start;
                    for (block_index = 0; block_index < pool->num_blocks - 1; block_index++) {
                        zpl_uintptr *next = cast(zpl_uintptr *) curr;
                        *next = cast(zpl_uintptr) curr + actual_block_size;
                        curr = zpl_pointer_add(curr, actual_block_size);
                    }

                    end = cast(zpl_uintptr *) curr;
                    *end = cast(zpl_uintptr) NULL;
                    pool->free_list = pool->physical_start;
                } break;

                case ZPL_ALLOCATION_RESIZE:
                // NOTE: Cannot resize
                ZPL_PANIC("You cannot resize something allocated by with a pool.");
                break;
            }

            return ptr;
        }


        //
        // Scratch Memory Allocator
        //

        void zpl_scratch_memory_init(zpl_scratch_memory *s, void *start, zpl_isize size) {
            s->physical_start = start;
            s->total_size = size;
            s->alloc_point = start;
            s->free_point = start;
        }

        zpl_b32 zpl_scratch_memory_is_in_use(zpl_scratch_memory *s, void *ptr) {
            if (s->free_point == s->alloc_point) return false;
            if (s->alloc_point > s->free_point) return ptr >= s->free_point && ptr < s->alloc_point;
            return ptr >= s->free_point || ptr < s->alloc_point;
        }

        zpl_allocator zpl_scratch_allocator(zpl_scratch_memory *s) {
            zpl_allocator a;
            a.proc = zpl_scratch_allocator_proc;
            a.data = s;
            return a;
        }

        ZPL_ALLOCATOR_PROC(zpl_scratch_allocator_proc) {
            zpl_scratch_memory *s = cast(zpl_scratch_memory *) allocator_data;
            void *ptr = NULL;
            ZPL_ASSERT_NOT_NULL(s);

            switch (type) {
                case ZPL_ALLOCATION_ALLOC: {
                    void *pt = s->alloc_point;
                    zpl_allocation_header_ev *header = cast(zpl_allocation_header_ev *) pt;
                    void *data = zpl_align_forward(header + 1, alignment);
                    void *end = zpl_pointer_add(s->physical_start, s->total_size);

                    ZPL_ASSERT(alignment % 4 == 0);
                    size = ((size + 3) / 4) * 4;
                    pt = zpl_pointer_add(pt, size);

                    // NOTE: Wrap around
                    if (pt > end) {
                        header->size = zpl_pointer_diff(header, end) | ZPL_ISIZE_HIGH_BIT;
                        pt = s->physical_start;
                        header = cast(zpl_allocation_header_ev *) pt;
                        data = zpl_align_forward(header + 1, alignment);
                        pt = zpl_pointer_add(pt, size);
                    }

                    if (!zpl_scratch_memory_is_in_use(s, pt)) {
                        zpl_allocation_header_fill(header, pt, zpl_pointer_diff(header, pt));
                        s->alloc_point = cast(zpl_u8 *) pt;
                        ptr = data;
                    }

                    if (flags & ZPL_ALLOCATOR_FLAG_CLEAR_TO_ZERO) zpl_zero_size(ptr, size);
                } break;

                case ZPL_ALLOCATION_FREE: {
                    if (old_memory) {
                        void *end = zpl_pointer_add(s->physical_start, s->total_size);
                        if (old_memory < s->physical_start || old_memory >= end) {
                            ZPL_ASSERT(false);
                        } else {
                            // NOTE: Mark as free
                            zpl_allocation_header_ev *h = zpl_allocation_header(old_memory);
                            ZPL_ASSERT((h->size & ZPL_ISIZE_HIGH_BIT) == 0);
                            h->size = h->size | ZPL_ISIZE_HIGH_BIT;

                            while (s->free_point != s->alloc_point) {
                                zpl_allocation_header_ev *header = cast(zpl_allocation_header_ev *) s->free_point;
                                if ((header->size & ZPL_ISIZE_HIGH_BIT) == 0) break;

                                s->free_point = zpl_pointer_add(s->free_point, h->size & (~ZPL_ISIZE_HIGH_BIT));
                                if (s->free_point == end) s->free_point = s->physical_start;
                            }
                        }
                    }
                } break;

                case ZPL_ALLOCATION_FREE_ALL:
                s->alloc_point = s->physical_start;
                s->free_point = s->physical_start;
                break;

                case ZPL_ALLOCATION_RESIZE:
                ptr = zpl_default_resize_align(zpl_scratch_allocator(s), old_memory, old_size, size, alignment);
                break;
            }

            return ptr;
        }

        //
        // Stack Memory Allocator
        //
        ZPL_ALLOCATOR_PROC(zpl_stack_allocator_proc) {
            zpl_stack_memory *s = cast(zpl_stack_memory *) allocator_data;
            void *ptr = NULL;
            ZPL_ASSERT_NOT_NULL(s);
            zpl_unused(old_size);
            zpl_unused(flags);

            switch (type) {
                case ZPL_ALLOCATION_ALLOC: {
                    size += ZPL_STACK_ALLOC_OFFSET;
                    zpl_u64 alloc_offset = s->allocated;

                    void *curr =
                        cast(zpl_u64 *) zpl_align_forward(cast(zpl_u64 *) zpl_pointer_add(s->physical_start, s->allocated), alignment);

                    if (cast(zpl_u64 *) zpl_pointer_add(curr, size) > cast(zpl_u64 *) zpl_pointer_add(s->physical_start, s->total_size)) {
                        if (s->backing.proc) {
                            void *old_start = s->physical_start;
                            s->physical_start =
                                zpl_resize_align(s->backing, s->physical_start, s->total_size, s->total_size + size, alignment);
                            curr = cast(zpl_u64 *)
                                zpl_align_forward(cast(zpl_u64 *) zpl_pointer_add(s->physical_start, s->allocated), alignment);
                            s->total_size = zpl_pointer_diff(old_start, s->physical_start);
                        } else {
                            ZPL_PANIC("Can not resize stack's memory! Allocator not defined!");
                        }
                    }

                    s->allocated = zpl_pointer_diff(s->physical_start, curr) + size;

                    *(zpl_u64 *)curr = alloc_offset;
                    curr = zpl_pointer_add(curr, ZPL_STACK_ALLOC_OFFSET);

                    ptr = curr;
                } break;

                case ZPL_ALLOCATION_FREE: {
                    if (old_memory) {
                        void *curr = old_memory;
                        curr = zpl_pointer_sub(curr, ZPL_STACK_ALLOC_OFFSET);

                        zpl_u64 alloc_offset = *(zpl_u64 *)curr;
                        s->allocated = (zpl_usize)alloc_offset;
                    }
                } break;

                case ZPL_ALLOCATION_FREE_ALL: {
                    s->allocated = 0;
                } break;

                case ZPL_ALLOCATION_RESIZE: {
                    ZPL_PANIC("You cannot resize something allocated by a stack.");
                } break;
            }
            return ptr;
        }

        ZPL_END_C_DECLS
        // file: source/core/array.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_NEVER_INLINE void *zpl__array_set_capacity(void *array, zpl_isize capacity, zpl_isize element_size) {
            zpl_array_header *h = ZPL_ARRAY_HEADER(array);

            ZPL_ASSERT(element_size > 0);

            if (capacity == h->capacity) return array;

            if (capacity < h->count) {
                if (h->capacity < capacity) {
                    zpl_isize new_capacity = ZPL_ARRAY_GROW_FORMULA(h->capacity);
                    if (new_capacity < capacity) new_capacity = capacity;
                    zpl__array_set_capacity(array, new_capacity, element_size);
                }
                h->count = capacity;
            }

            {
                zpl_isize size = zpl_size_of(zpl_array_header) + element_size * capacity;
                zpl_array_header *nh = cast(zpl_array_header *) zpl_alloc(h->allocator, size);
                zpl_memmove(nh, h, zpl_size_of(zpl_array_header) + element_size * h->count);
                nh->allocator = h->allocator;
                nh->count = h->count;
                nh->data = (char *)nh + 1;
                nh->capacity = capacity;
                zpl_free(h->allocator, h);
                return nh + 1;
            }
        }

        ZPL_END_C_DECLS
        // file: source/core/string.c

        ////////////////////////////////////////////////////////////////
        //
        // Char things
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_internal zpl_isize zpl__scan_zpl_i64(const char *text, zpl_i32 base, zpl_i64 *value) {
            const char *text_begin = text;
            zpl_i64 result = 0;
            zpl_b32 negative = false;

            if (*text == '-') {
                negative = true;
                text++;
            }

            if (base == 16 && zpl_strncmp(text, "0x", 2) == 0) text += 2;

            for (;;) {
                zpl_i64 v;
                if (zpl_char_is_digit(*text))
                    v = *text - '0';
                else if (base == 16 && zpl_char_is_hex_digit(*text))
                    v = zpl_hex_digit_to_int(*text);
                else
                    break;

                result *= base;
                result += v;
                text++;
            }

            if (value) {
                if (negative) result = -result;
                *value = result;
            }

            return (text - text_begin);
        }

        zpl_internal zpl_isize zpl__scan_zpl_u64(const char *text, zpl_i32 base, zpl_u64 *value) {
            const char *text_begin = text;
            zpl_u64 result = 0;

            if (base == 16 && zpl_strncmp(text, "0x", 2) == 0) text += 2;

            for (;;) {
                zpl_u64 v;
                if (zpl_char_is_digit(*text))
                    v = *text - '0';
                else if (base == 16 && zpl_char_is_hex_digit(*text))
                    v = zpl_hex_digit_to_int(*text);
                else {
                    break;
                }

                result *= base;
                result += v;
                text++;
            }

            if (value) *value = result;

            return (text - text_begin);
        }

        // TODO: Make better
        zpl_u64 zpl_str_to_u64(const char *str, char **end_ptr, zpl_i32 base) {
            zpl_isize len;
            zpl_u64 value = 0;

            if (!base) {
                if ((zpl_strlen(str) > 2) && (zpl_strncmp(str, "0x", 2) == 0))
                    base = 16;
                else
                    base = 10;
            }

            len = zpl__scan_zpl_u64(str, base, &value);
            if (end_ptr) *end_ptr = (char *)str + len;
            return value;
        }

        zpl_i64 zpl_str_to_i64(const char *str, char **end_ptr, zpl_i32 base) {
            zpl_isize len;
            zpl_i64 value;

            if (!base) {
                if ((zpl_strlen(str) > 2) && (zpl_strncmp(str, "0x", 2) == 0))
                    base = 16;
                else
                    base = 10;
            }

            len = zpl__scan_zpl_i64(str, base, &value);
            if (end_ptr) *end_ptr = (char *)str + len;
            return value;
        }

        // TODO: Are these good enough for characters?
        zpl_global const char zpl__num_to_char_table[] = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "@$";

        void zpl_i64_to_str(zpl_i64 value, char *string, zpl_i32 base) {
            char *buf = string;
            zpl_b32 negative = false;
            zpl_u64 v;

            if (value < 0) {
                negative = true;
                value = -value;
            }

            v = cast(zpl_u64) value;
            if (v != 0) {
                while (v > 0) {
                    *buf++ = zpl__num_to_char_table[v % base];
                    v /= base;
                }
            } else {
                *buf++ = '0';
            }
            if (negative) *buf++ = '-';
            *buf = '\0';
            zpl_strrev(string);
        }

        void zpl_u64_to_str(zpl_u64 value, char *string, zpl_i32 base) {
            char *buf = string;

            if (value) {
                while (value > 0) {
                    *buf++ = zpl__num_to_char_table[value % base];
                    value /= base;
                }
            } else {
                *buf++ = '0';
            }
            *buf = '\0';

            zpl_strrev(string);
        }

        zpl_f64 zpl_str_to_f64(const char *str, char **end_ptr) {
            zpl_f64 result, value, sign, scale;
            zpl_i32 frac;

            while (zpl_char_is_space(*str)) { str++; }

            sign = 1.0;
            if (*str == '-') {
                sign = -1.0;
                str++;
            } else if (*str == '+') {
                str++;
            }

            for (value = 0.0; zpl_char_is_digit(*str); str++) { value = value * 10.0 + (*str - '0'); }

            if (*str == '.') {
                zpl_f64 pow10 = 10.0;
                str++;
                while (zpl_char_is_digit(*str)) {
                    value += (*str - '0') / pow10;
                    pow10 *= 10.0;
                    str++;
                }
            }

            frac = 0;
            scale = 1.0;
            if ((*str == 'e') || (*str == 'E')) {
                zpl_u32 exp;

                str++;
                if (*str == '-') {
                    frac = 1;
                    str++;
                } else if (*str == '+') {
                    str++;
                }

                for (exp = 0; zpl_char_is_digit(*str); str++) { exp = exp * 10 + (*str - '0'); }
                if (exp > 308) exp = 308;

                while (exp >= 50) {
                    scale *= 1e50;
                    exp -= 50;
                }
                while (exp >= 8) {
                    scale *= 1e8;
                    exp -= 8;
                }
                while (exp > 0) {
                    scale *= 10.0;
                    exp -= 1;
                }
            }

            result = sign * (frac ? (value / scale) : (value * scale));

            if (end_ptr) *end_ptr = cast(char *) str;

            return result;
        }



        ////////////////////////////////////////////////////////////////
        //
        // Windows UTF-8 Handling
        //
        //

        zpl_u16 *zpl_utf8_to_ucs2(zpl_u16 *buffer, zpl_isize len, zpl_u8 const *str) {
            zpl_rune c;
            zpl_isize i = 0;
            len--;
            while (*str) {
                if (i >= len) return NULL;
                if (!(*str & 0x80)) {
                    buffer[i++] = *str++;
                } else if ((*str & 0xe0) == 0xc0) {
                    if (*str < 0xc2) return NULL;
                    c = (*str++ & 0x1f) << 6;
                    if ((*str & 0xc0) != 0x80) return NULL;
                    buffer[i++] = cast(zpl_u16)(c + (*str++ & 0x3f));
                } else if ((*str & 0xf0) == 0xe0) {
                    if (*str == 0xe0 && (str[1] < 0xa0 || str[1] > 0xbf)) return NULL;
                    if (*str == 0xed && str[1] > 0x9f) // str[1] < 0x80 is checked below
                        return NULL;
                    c = (*str++ & 0x0f) << 12;
                    if ((*str & 0xc0) != 0x80) return NULL;
                    c += (*str++ & 0x3f) << 6;
                    if ((*str & 0xc0) != 0x80) return NULL;
                    buffer[i++] = cast(zpl_u16)(c + (*str++ & 0x3f));
                } else if ((*str & 0xf8) == 0xf0) {
                    if (*str > 0xf4) return NULL;
                    if (*str == 0xf0 && (str[1] < 0x90 || str[1] > 0xbf)) return NULL;
                    if (*str == 0xf4 && str[1] > 0x8f) // str[1] < 0x80 is checked below
                        return NULL;
                    c = (*str++ & 0x07) << 18;
                    if ((*str & 0xc0) != 0x80) return NULL;
                    c += (*str++ & 0x3f) << 12;
                    if ((*str & 0xc0) != 0x80) return NULL;
                    c += (*str++ & 0x3f) << 6;
                    if ((*str & 0xc0) != 0x80) return NULL;
                    c += (*str++ & 0x3f);
                    // UTF-8 encodings of values used in surrogate pairs are invalid
                    if ((c & 0xfffff800) == 0xd800) return NULL;
                    if (c >= 0x10000) {
                        c -= 0x10000;
                        if (i + 2 > len) return NULL;
                        buffer[i++] = 0xd800 | (0x3ff & (c >> 10));
                        buffer[i++] = 0xdc00 | (0x3ff & (c));
                    }
                } else {
                    return NULL;
                }
            }
            buffer[i] = 0;
            return buffer;
        }

        zpl_u8 *zpl_ucs2_to_utf8(zpl_u8 *buffer, zpl_isize len, zpl_u16 const *str) {
            zpl_isize i = 0;
            len--;
            while (*str) {
                if (*str < 0x80) {
                    if (i + 1 > len) return NULL;
                    buffer[i++] = (char)*str++;
                } else if (*str < 0x800) {
                    if (i + 2 > len) return NULL;
                    buffer[i++] = cast(char)(0xc0 + (*str >> 6));
                    buffer[i++] = cast(char)(0x80 + (*str & 0x3f));
                    str += 1;
                } else if (*str >= 0xd800 && *str < 0xdc00) {
                    zpl_rune c;
                    if (i + 4 > len) return NULL;
                    c = ((str[0] - 0xd800) << 10) + ((str[1]) - 0xdc00) + 0x10000;
                    buffer[i++] = cast(char)(0xf0 + (c >> 18));
                    buffer[i++] = cast(char)(0x80 + ((c >> 12) & 0x3f));
                    buffer[i++] = cast(char)(0x80 + ((c >> 6) & 0x3f));
                    buffer[i++] = cast(char)(0x80 + ((c)&0x3f));
                    str += 2;
                } else if (*str >= 0xdc00 && *str < 0xe000) {
                    return NULL;
                } else {
                    if (i + 3 > len) return NULL;
                    buffer[i++] = 0xe0 + (*str >> 12);
                    buffer[i++] = 0x80 + ((*str >> 6) & 0x3f);
                    buffer[i++] = 0x80 + ((*str) & 0x3f);
                    str += 1;
                }
            }
            buffer[i] = 0;
            return buffer;
        }

        zpl_u16 *zpl_utf8_to_ucs2_buf(zpl_u8 const *str) { // NOTE: Uses locally persisting buffer
            zpl_local_persist zpl_u16 buf[4096];
            return zpl_utf8_to_ucs2(buf, zpl_count_of(buf), str);
        }

        zpl_u8 *zpl_ucs2_to_utf8_buf(zpl_u16 const *str) { // NOTE: Uses locally persisting buffer
            zpl_local_persist zpl_u8 buf[4096];
            return zpl_ucs2_to_utf8(buf, zpl_count_of(buf), str);
        }

        zpl_global zpl_u8 const zpl__utf8_first[256] = {
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x00-0x0F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x10-0x1F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x20-0x2F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x30-0x3F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x40-0x4F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x50-0x5F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x60-0x6F
            0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, // 0x70-0x7F
            0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0x80-0x8F
            0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0x90-0x9F
            0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0xA0-0xAF
            0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0xB0-0xBF
            0xf1, 0xf1, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, // 0xC0-0xCF
            0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, // 0xD0-0xDF
            0x13, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x23, 0x03, 0x03, // 0xE0-0xEF
            0x34, 0x04, 0x04, 0x04, 0x44, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, 0xf1, // 0xF0-0xFF
        };


        typedef struct zpl_utf8_accept_range {
            zpl_u8 lo, hi;
        } zpl_utf8_accept_range;

        zpl_global zpl_utf8_accept_range const zpl__utf8_accept_ranges[] = {
            { 0x80, 0xbf }, { 0xa0, 0xbf }, { 0x80, 0x9f }, { 0x90, 0xbf }, { 0x80, 0x8f },
        };

        zpl_isize zpl_utf8_decode(zpl_u8 const *str, zpl_isize str_len, zpl_rune *codepoint_out) {

            zpl_isize width = 0;
            zpl_rune codepoint = ZPL_RUNE_INVALID;

            if (str_len > 0) {
                zpl_u8 s0 = str[0];
                zpl_u8 x = zpl__utf8_first[s0], sz;
                zpl_u8 b1, b2, b3;
                zpl_utf8_accept_range accept;
                if (x >= 0xf0) {
                    zpl_rune mask = (cast(zpl_rune) x << 31) >> 31;
                    codepoint = (cast(zpl_rune) s0 & (~mask)) | (ZPL_RUNE_INVALID & mask);
                    width = 1;
                    goto end;
                }
                if (s0 < 0x80) {
                    codepoint = s0;
                    width = 1;
                    goto end;
                }

                sz = x & 7;
                accept = zpl__utf8_accept_ranges[x >> 4];
                if (str_len < zpl_size_of(sz)) goto invalid_codepoint;

                b1 = str[1];
                if (b1 < accept.lo || accept.hi < b1) goto invalid_codepoint;

                if (sz == 2) {
                    codepoint = (cast(zpl_rune) s0 & 0x1f) << 6 | (cast(zpl_rune) b1 & 0x3f);
                    width = 2;
                    goto end;
                }

                b2 = str[2];
                if (!zpl_is_between(b2, 0x80, 0xbf)) goto invalid_codepoint;

                if (sz == 3) {
                    codepoint = (cast(zpl_rune) s0 & 0x1f) << 12 | (cast(zpl_rune) b1 & 0x3f) << 6 | (cast(zpl_rune) b2 & 0x3f);
                    width = 3;
                    goto end;
                }

                b3 = str[3];
                if (!zpl_is_between(b3, 0x80, 0xbf)) goto invalid_codepoint;

                codepoint = (cast(zpl_rune) s0 & 0x07) << 18 | (cast(zpl_rune) b1 & 0x3f) << 12 | (cast(zpl_rune) b2 & 0x3f) << 6 |
                    (cast(zpl_rune) b3 & 0x3f);
                width = 4;
                goto end;

                invalid_codepoint:
                codepoint = ZPL_RUNE_INVALID;
                width = 1;
            }

            end:
            if (codepoint_out) *codepoint_out = codepoint;
            return width;
        }

        zpl_isize zpl_utf8_codepoint_size(zpl_u8 const *str, zpl_isize str_len) {
            zpl_isize i = 0;
            for (; i < str_len && str[i]; i++) {
                if ((str[i] & 0xc0) != 0x80) break;
            }
            return i + 1;
        }

        zpl_isize zpl_utf8_encode_rune(zpl_u8 buf[4], zpl_rune r) {
            zpl_u32 i = cast(zpl_u32) r;
            zpl_u8 mask = 0x3f;
            if (i <= (1 << 7) - 1) {
                buf[0] = cast(zpl_u8) r;
                return 1;
            }
            if (i <= (1 << 11) - 1) {
                buf[0] = 0xc0 | cast(zpl_u8)(r >> 6);
                buf[1] = 0x80 | (cast(zpl_u8)(r) & mask);
                return 2;
            }

            // Invalid or Surrogate range
            if (i > ZPL_RUNE_MAX || zpl_is_between(i, 0xd800, 0xdfff)) {
                r = ZPL_RUNE_INVALID;

                buf[0] = 0xe0 | cast(zpl_u8)(r >> 12);
                buf[1] = 0x80 | (cast(zpl_u8)(r >> 6) & mask);
                buf[2] = 0x80 | (cast(zpl_u8)(r) & mask);
                return 3;
            }

            if (i <= (1 << 16) - 1) {
                buf[0] = 0xe0 | cast(zpl_u8)(r >> 12);
                buf[1] = 0x80 | (cast(zpl_u8)(r >> 6) & mask);
                buf[2] = 0x80 | (cast(zpl_u8)(r) & mask);
                return 3;
            }

            buf[0] = 0xf0 | cast(zpl_u8)(r >> 18);
            buf[1] = 0x80 | (cast(zpl_u8)(r >> 12) & mask);
            buf[2] = 0x80 | (cast(zpl_u8)(r >> 6) & mask);
            buf[3] = 0x80 | (cast(zpl_u8)(r) & mask);
            return 4;
        }

        ZPL_END_C_DECLS
        // file: source/core/stringlib.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_string zpl_string_make_reserve(zpl_allocator a, zpl_isize capacity) {
            zpl_isize header_size = zpl_size_of(zpl_string_header);
            void *ptr = zpl_alloc(a, header_size + capacity + 1);

            zpl_string str;
            zpl_string_header *header;

            if (ptr == NULL) return NULL;
            zpl_zero_size(ptr, header_size + capacity + 1);

            str = cast(char *) ptr + header_size;
            header = ZPL_STRING_HEADER(str);
            header->allocator = a;
            header->length = 0;
            header->capacity = capacity;
            str[capacity] = '\0';

            return str;
        }


        zpl_string zpl_string_make_length(zpl_allocator a, void const *init_str, zpl_isize num_bytes) {
            zpl_isize header_size = zpl_size_of(zpl_string_header);
            void *ptr = zpl_alloc(a, header_size + num_bytes + 1);

            zpl_string str;
            zpl_string_header *header;

            if (ptr == NULL) return NULL;
            if (!init_str) zpl_zero_size(ptr, header_size + num_bytes + 1);

            str = cast(char *) ptr + header_size;
            header = ZPL_STRING_HEADER(str);
            header->allocator = a;
            header->length = num_bytes;
            header->capacity = num_bytes;
            if (num_bytes && init_str) zpl_memcopy(str, init_str, num_bytes);
            str[num_bytes] = '\0';

            return str;
        }

        zpl_string zpl_string_sprintf_buf(zpl_allocator a, const char *fmt, ...) {
            zpl_local_persist char buf[4096] = { 0 };
            va_list va;
            va_start(va, fmt);
            zpl_snprintf_va(buf, 4096, fmt, va);
            va_end(va);

            return zpl_string_make(a, buf);
        }

        zpl_string zpl_string_sprintf(zpl_allocator a, char *buf, zpl_isize num_bytes, const char *fmt, ...) {
            va_list va;
            va_start(va, fmt);
            zpl_snprintf_va(buf, num_bytes, fmt, va);
            va_end(va);

            return zpl_string_make(a, buf);
        }

        zpl_string zpl_string_append_length(zpl_string str, void const *other, zpl_isize other_len) {
            if (other_len > 0) {
                zpl_isize curr_len = zpl_string_length(str);

                str = zpl_string_make_space_for(str, other_len);
                if (str == NULL) return NULL;

                zpl_memcopy(str + curr_len, other, other_len);
                str[curr_len + other_len] = '\0';
                zpl__set_string_length(str, curr_len + other_len);
            }
            return str;
        }

        ZPL_ALWAYS_INLINE zpl_string zpl_string_appendc(zpl_string str, const char *other) {
            return zpl_string_append_length(str, other, zpl_strlen(other));
        }

        ZPL_ALWAYS_INLINE zpl_string zpl_string_join(zpl_allocator a, const char **parts, zpl_isize count, const char *glue) {
            zpl_string ret;
            zpl_isize i;

            ret = zpl_string_make(a, NULL);

            for (i=0; i<count; ++i) {
                ret = zpl_string_appendc(ret, parts[i]);

                if ((i+1) < count) {
                    ret = zpl_string_appendc(ret, glue);
                }
            }

            return ret;
        }

        zpl_string zpl_string_set(zpl_string str, const char *cstr) {
            zpl_isize len = zpl_strlen(cstr);
            if (zpl_string_capacity(str) < len) {
                str = zpl_string_make_space_for(str, len - zpl_string_length(str));
                if (str == NULL) return NULL;
            }

            zpl_memcopy(str, cstr, len);
            str[len] = '\0';
            zpl__set_string_length(str, len);

            return str;
        }

        zpl_string zpl_string_make_space_for(zpl_string str, zpl_isize add_len) {
            zpl_isize available = zpl_string_available_space(str);

            // NOTE: Return if there is enough space left
            if (available >= add_len) {
                return str;
            } else {
                zpl_isize new_len, old_size, new_size;
                void *ptr, *new_ptr;
                zpl_allocator a = ZPL_STRING_HEADER(str)->allocator;
                zpl_string_header *header;

                new_len = zpl_string_length(str) + add_len;
                ptr = ZPL_STRING_HEADER(str);
                old_size = zpl_size_of(zpl_string_header) + zpl_string_length(str) + 1;
                new_size = zpl_size_of(zpl_string_header) + new_len + 1;

                new_ptr = zpl_resize(a, ptr, old_size, new_size);
                if (new_ptr == NULL) return NULL;

                header = cast(zpl_string_header *) new_ptr;
                header->allocator = a;

                str = cast(zpl_string)(header + 1);
                zpl__set_string_capacity(str, new_len);

                return str;
            }
        }

        zpl_isize zpl_string_allocation_size(zpl_string const str) {
            zpl_isize cap = zpl_string_capacity(str);
            return zpl_size_of(zpl_string_header) + cap;
        }

        zpl_b32 zpl_string_are_equal(zpl_string const lhs, zpl_string const rhs) {
            zpl_isize lhs_len, rhs_len, i;
            lhs_len = zpl_string_length(lhs);
            rhs_len = zpl_string_length(rhs);
            if (lhs_len != rhs_len) return false;

            for (i = 0; i < lhs_len; i++) {
                if (lhs[i] != rhs[i]) return false;
            }

            return true;
        }

        zpl_string zpl_string_trim(zpl_string str, const char *cut_set) {
            char *start, *end, *start_pos, *end_pos;
            zpl_isize len;

            start_pos = start = str;
            end_pos = end = str + zpl_string_length(str) - 1;

            while (start_pos <= end && zpl_char_first_occurence(cut_set, *start_pos)) start_pos++;
            while (end_pos > start_pos && zpl_char_first_occurence(cut_set, *end_pos)) end_pos--;

            len = cast(zpl_isize)((start_pos > end_pos) ? 0 : ((end_pos - start_pos) + 1));

            if (str != start_pos) zpl_memmove(str, start_pos, len);
            str[len] = '\0';

            zpl__set_string_length(str, len);

            return str;
        }

        zpl_string zpl_string_append_rune(zpl_string str, zpl_rune r) {
            if (r >= 0) {
                zpl_u8 buf[8] = { 0 };
                zpl_isize len = zpl_utf8_encode_rune(buf, r);
                return zpl_string_append_length(str, buf, len);
            }

            return str;
        }

        zpl_string zpl_string_append_fmt(zpl_string str, const char *fmt, ...) {
            zpl_isize res;
            char buf[4096] = { 0 };
            va_list va;
            va_start(va, fmt);
            res = zpl_snprintf_va(buf, zpl_count_of(buf) - 1, fmt, va) - 1;
            va_end(va);
            return zpl_string_append_length(str, buf, res);
        }

        ZPL_END_C_DECLS
        // file: source/core/file.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ////////////////////////////////////////////////////////////////
        //
        // File Handling
        //
        //
        #include <sys/stat.h>

        #ifdef ZPL_SYSTEM_MACOS
            #include <copyfile.h>
        #endif

        #ifdef ZPL_SYSTEM_CYGWIN
        #   include <windows.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_SYSTEM_WINDOWS) || defined (ZPL_SYSTEM_CYGWIN)

            zpl_internal wchar_t *zpl__alloc_utf8_to_ucs2(zpl_allocator a, char const *text, zpl_isize *w_len_) {
                wchar_t *w_text = NULL;
                zpl_isize len = 0, w_len = 0, w_len1 = 0;
                if (text == NULL) {
                    if (w_len_) *w_len_ = w_len;
                    return NULL;
                }
                len = zpl_strlen(text);
                if (len == 0) {
                    if (w_len_) *w_len_ = w_len;
                    return NULL;
                }
                w_len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, cast(int) len, NULL, 0);
                if (w_len == 0) {
                    if (w_len_) *w_len_ = w_len;
                    return NULL;
                }
                w_text = zpl_alloc_array(a, wchar_t, w_len + 1);
                w_len1 = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, text, cast(int) len, w_text, cast(int) w_len);
                if (w_len1 == 0) {
                    zpl_free(a, w_text);
                    if (w_len_) *w_len_ = 0;
                    return NULL;
                }
                w_text[w_len] = 0;
                if (w_len_) *w_len_ = w_len;
                return w_text;
            }

            zpl_internal ZPL_FILE_SEEK_PROC(zpl__win32_file_seek) {
                LARGE_INTEGER li_offset;
                li_offset.QuadPart = offset;
                if (!SetFilePointerEx(fd.p, li_offset, &li_offset, whence)) { return false; }

                if (new_offset) *new_offset = li_offset.QuadPart;
                return true;
            }

            zpl_internal ZPL_FILE_READ_AT_PROC(zpl__win32_file_read) {
                zpl_unused(stop_at_newline);
                zpl_b32 result = false;
                zpl__win32_file_seek(fd, offset, ZPL_SEEK_WHENCE_BEGIN, NULL);
                DWORD size_ = cast(DWORD)(size > ZPL_I32_MAX ? ZPL_I32_MAX : size);
                DWORD bytes_read_;
                if (ReadFile(fd.p, buffer, size_, &bytes_read_, NULL)) {
                    if (bytes_read) *bytes_read = bytes_read_;
                    result = true;
                }

                return result;
            }

            zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__win32_file_write) {
                DWORD size_ = cast(DWORD)(size > ZPL_I32_MAX ? ZPL_I32_MAX : size);
                DWORD bytes_written_;
                zpl__win32_file_seek(fd, offset, ZPL_SEEK_WHENCE_BEGIN, NULL);
                if (WriteFile(fd.p, buffer, size_, &bytes_written_, NULL)) {
                    if (bytes_written) *bytes_written = bytes_written_;
                    return true;
                }
                return false;
            }

            zpl_internal ZPL_FILE_CLOSE_PROC(zpl__win32_file_close) { CloseHandle(fd.p); }

            zpl_file_operations const zpl_default_file_operations = { zpl__win32_file_read, zpl__win32_file_write,
                zpl__win32_file_seek, zpl__win32_file_close };

            ZPL_NEVER_INLINE ZPL_FILE_OPEN_PROC(zpl__win32_file_open) {
                DWORD desired_access;
                DWORD creation_disposition;
                void *handle;
                wchar_t *w_text;

                switch (mode & ZPL_FILE_MODES) {
                    case ZPL_FILE_MODE_READ:
                        desired_access = GENERIC_READ;
                        creation_disposition = OPEN_EXISTING;
                        break;
                    case ZPL_FILE_MODE_WRITE:
                        desired_access = GENERIC_WRITE;
                        creation_disposition = CREATE_ALWAYS;
                        break;
                    case ZPL_FILE_MODE_APPEND:
                        desired_access = GENERIC_WRITE;
                        creation_disposition = OPEN_ALWAYS;
                        break;
                    case ZPL_FILE_MODE_READ | ZPL_FILE_MODE_RW:
                        desired_access = GENERIC_READ | GENERIC_WRITE;
                        creation_disposition = OPEN_EXISTING;
                    break;
                    case ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW:
                        desired_access = GENERIC_READ | GENERIC_WRITE;
                        creation_disposition = CREATE_ALWAYS;
                        break;
                    case ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW:
                        desired_access = GENERIC_READ | GENERIC_WRITE;
                        creation_disposition = OPEN_ALWAYS;
                        break;
                    default: ZPL_PANIC("Invalid file mode"); return ZPL_FILE_ERROR_INVALID;
                }

                w_text = zpl__alloc_utf8_to_ucs2(zpl_heap_allocator( ), filename, NULL);
                handle = CreateFileW(w_text, desired_access, FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, creation_disposition,
                                     FILE_ATTRIBUTE_NORMAL, NULL);

                zpl_free(zpl_heap_allocator( ), w_text);

                if (handle == INVALID_HANDLE_VALUE) {
                    DWORD err = GetLastError( );
                    switch (err) {
                        case ERROR_FILE_NOT_FOUND: return ZPL_FILE_ERROR_NOT_EXISTS;
                        case ERROR_FILE_EXISTS: return ZPL_FILE_ERROR_EXISTS;
                        case ERROR_ALREADY_EXISTS: return ZPL_FILE_ERROR_EXISTS;
                        case ERROR_ACCESS_DENIED: return ZPL_FILE_ERROR_PERMISSION;
                    }
                    return ZPL_FILE_ERROR_INVALID;
                }

                if (mode & ZPL_FILE_MODE_APPEND) {
                    LARGE_INTEGER offset = { 0 };
                    if (!SetFilePointerEx(handle, offset, NULL, ZPL_SEEK_WHENCE_END)) {
                        CloseHandle(handle);
                        return ZPL_FILE_ERROR_INVALID;
                    }
                }

                fd->p = handle;
                *ops = zpl_default_file_operations;
                return ZPL_FILE_ERROR_NONE;
            }

        #else // POSIX
            #include <fcntl.h>

            zpl_internal ZPL_FILE_SEEK_PROC(zpl__posix_file_seek) {
            #if defined(ZPL_SYSTEM_OSX)
                zpl_i64 res = lseek(fd.i, offset, whence);
            #else // TODO(ZaKlaus): @fixme lseek64
                zpl_i64 res = lseek(fd.i, offset, whence);
            #endif
                if (res < 0) return false;
                if (new_offset) *new_offset = res;
                return true;
            }

            zpl_internal ZPL_FILE_READ_AT_PROC(zpl__posix_file_read) {
                zpl_unused(stop_at_newline);
                zpl_isize res = pread(fd.i, buffer, size, offset);
                if (res < 0) return false;
                if (bytes_read) *bytes_read = res;
                return true;
            }

            zpl_internal ZPL_FILE_WRITE_AT_PROC(zpl__posix_file_write) {
                zpl_isize res;
                zpl_i64 curr_offset = 0;
                zpl__posix_file_seek(fd, 0, ZPL_SEEK_WHENCE_CURRENT, &curr_offset);
                if (curr_offset == offset) {
                    // NOTE: Writing to stdout et al. doesn't like pwrite for numerous reasons
                    res = write(cast(int) fd.i, buffer, size);
                } else {
                    res = pwrite(cast(int) fd.i, buffer, size, offset);
                }
                if (res < 0) return false;
                if (bytes_written) *bytes_written = res;
                return true;
            }

            zpl_internal ZPL_FILE_CLOSE_PROC(zpl__posix_file_close) { close(fd.i); }

            zpl_file_operations const zpl_default_file_operations = { zpl__posix_file_read, zpl__posix_file_write,
                zpl__posix_file_seek, zpl__posix_file_close };

            ZPL_NEVER_INLINE ZPL_FILE_OPEN_PROC(zpl__posix_file_open) {
                zpl_i32 os_mode;
                switch (mode & ZPL_FILE_MODES) {
                    case ZPL_FILE_MODE_READ: os_mode = O_RDONLY; break;
                    case ZPL_FILE_MODE_WRITE: os_mode = O_WRONLY | O_CREAT | O_TRUNC; break;
                    case ZPL_FILE_MODE_APPEND: os_mode = O_WRONLY | O_APPEND | O_CREAT; break;
                    case ZPL_FILE_MODE_READ | ZPL_FILE_MODE_RW: os_mode = O_RDWR; break;
                    case ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW: os_mode = O_RDWR | O_CREAT | O_TRUNC; break;
                    case ZPL_FILE_MODE_APPEND | ZPL_FILE_MODE_RW: os_mode = O_RDWR | O_APPEND | O_CREAT; break;
                    default: ZPL_PANIC("Invalid file mode"); return ZPL_FILE_ERROR_INVALID;
                }

                fd->i = open(filename, os_mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
                if (fd->i < 0) {
                  printf("aaa %ld\n", fd->i);
                    // TODO: More file errors
                    return ZPL_FILE_ERROR_INVALID;
                }

                *ops = zpl_default_file_operations;
                return ZPL_FILE_ERROR_NONE;
            }

        #endif

        zpl_file_error zpl_file_new(zpl_file *f, zpl_file_descriptor fd, zpl_file_operations ops, char const *filename) {
            zpl_file_error err = ZPL_FILE_ERROR_NONE;
            zpl_isize len = zpl_strlen(filename);

            f->ops = ops;
            f->fd = fd;
            f->filename = zpl_alloc_array(zpl_heap_allocator( ), char, len + 1);
            zpl_memcopy(cast(char *) f->filename, cast(char *) filename, len + 1);
            f->last_write_time = zpl_fs_last_write_time(f->filename);

            return err;
        }

        zpl_file_error zpl_file_open_mode(zpl_file *f, zpl_file_mode mode, char const *filename) {
            zpl_file file_ = {0};
            *f = file_;
            zpl_file_error err;
        #if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)
            err = zpl__win32_file_open(&f->fd, &f->ops, mode, filename);
        #else
            err = zpl__posix_file_open(&f->fd, &f->ops, mode, filename);
        #endif
            if (err == ZPL_FILE_ERROR_NONE) return zpl_file_new(f, f->fd, f->ops, filename);
            return err;
        }

        zpl_internal void zpl__dirinfo_free_entry(zpl_dir_entry *entry);

        zpl_file_error zpl_file_close(zpl_file *f) {
            if (!f) return ZPL_FILE_ERROR_INVALID;

            if (f->filename) zpl_free(zpl_heap_allocator( ), cast(char *) f->filename);

        #if defined(ZPL_SYSTEM_WINDOWS)
            if (f->fd.p == INVALID_HANDLE_VALUE) return ZPL_FILE_ERROR_INVALID;
        #else
            if (f->fd.i < 0) return ZPL_FILE_ERROR_INVALID;
        #endif

            if (!f->ops.read_at) f->ops = zpl_default_file_operations;
            f->ops.close(f->fd);

            if (f->dir) {
                zpl__dirinfo_free_entry(f->dir);
                zpl_mfree(f->dir);
                f->dir = NULL;
            }

            return ZPL_FILE_ERROR_NONE;
        }


        zpl_file_error zpl_file_create(zpl_file *f, char const *filename) {
            return zpl_file_open_mode(f, ZPL_FILE_MODE_WRITE | ZPL_FILE_MODE_RW, filename);
        }

        zpl_file_error zpl_file_open(zpl_file *f, char const *filename) {
            return zpl_file_open_mode(f, ZPL_FILE_MODE_READ, filename);
        }

        char const *zpl_file_name(zpl_file *f) { return f->filename ? f->filename : ""; }

        zpl_b32 zpl_file_has_changed(zpl_file *f) {
            zpl_b32 result = false;
            zpl_file_time last_write_time = zpl_fs_last_write_time(f->filename);
            if (f->last_write_time != last_write_time) {
                result = true;
                f->last_write_time = last_write_time;
            }
            return result;
        }

        // TODO: Is this a bad idea?
        zpl_global zpl_b32 zpl__std_file_set = false;
        zpl_global zpl_file zpl__std_files[ZPL_FILE_STANDARD_COUNT] = { { 0 } };

        #if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)

        zpl_file *zpl_file_get_standard(zpl_file_standard_type std) {
            if (!zpl__std_file_set) {
        #define ZPL__SET_STD_FILE(type, v)                                                                                     \
                zpl__std_files[type].fd.p = v;                                                                                     \
                zpl__std_files[type].ops = zpl_default_file_operations
                ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_INPUT, GetStdHandle(STD_INPUT_HANDLE));
                ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_OUTPUT, GetStdHandle(STD_OUTPUT_HANDLE));
                ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_ERROR, GetStdHandle(STD_ERROR_HANDLE));
        #undef ZPL__SET_STD_FILE
                zpl__std_file_set = true;
            }
            return &zpl__std_files[std];
        }

        void zpl_file_connect_handle(zpl_file *file, void *handle) {
            ZPL_ASSERT_NOT_NULL(file);
            ZPL_ASSERT_NOT_NULL(handle);

            zpl_zero_item(file);

            file->fd.p = handle;
            file->ops = zpl_default_file_operations;
        }


        zpl_i64 zpl_file_size(zpl_file *f) {
            LARGE_INTEGER size;
            GetFileSizeEx(f->fd.p, &size);
            return size.QuadPart;
        }

        zpl_file_error zpl_file_truncate(zpl_file *f, zpl_i64 size) {
            zpl_file_error err = ZPL_FILE_ERROR_NONE;
            zpl_i64 prev_offset = zpl_file_tell(f);
            zpl_file_seek(f, size);
            if (!SetEndOfFile(f)) err = ZPL_FILE_ERROR_TRUNCATION_FAILURE;
            zpl_file_seek(f, prev_offset);
            return err;
        }

        zpl_b32 zpl_fs_exists(char const *name) {
            WIN32_FIND_DATAW data;
            wchar_t *w_text;
            void *handle;
            zpl_b32 found = false;
            zpl_allocator a = zpl_heap_allocator( );

            w_text = zpl__alloc_utf8_to_ucs2(a, name, NULL);
            if (w_text == NULL) { return false; }
            handle = FindFirstFileW(w_text, &data);
            zpl_free(a, w_text);
            found = handle != INVALID_HANDLE_VALUE;
            if (found) FindClose(handle);
            return found;
        }

        #else // POSIX

        zpl_file *zpl_file_get_standard(zpl_file_standard_type std) {
            if (!zpl__std_file_set) {
        #define ZPL__SET_STD_FILE(type, v)                                                                                     \
                zpl__std_files[type].fd.i = v;                                                                                     \
                zpl__std_files[type].ops = zpl_default_file_operations
                ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_INPUT, 0);
                ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_OUTPUT, 1);
                ZPL__SET_STD_FILE(ZPL_FILE_STANDARD_ERROR, 2);
        #undef ZPL__SET_STD_FILE
                zpl__std_file_set = true;
            }
            return &zpl__std_files[std];
        }

        zpl_i64 zpl_file_size(zpl_file *f) {
            zpl_i64 size = 0;
            zpl_i64 prev_offset = zpl_file_tell(f);
            zpl_file_seek_to_end(f);
            size = zpl_file_tell(f);
            zpl_file_seek(f, prev_offset);
            return size;
        }

        zpl_file_error zpl_file_truncate(zpl_file *f, zpl_i64 size) {
            zpl_file_error err = ZPL_FILE_ERROR_NONE;
            int i = ftruncate(f->fd.i, size);
            if (i != 0) err = ZPL_FILE_ERROR_TRUNCATION_FAILURE;
            return err;
        }

        zpl_b32 zpl_fs_exists(char const *name) { return access(name, F_OK) != -1; }

        #endif

        zpl_file_error zpl_file_temp(zpl_file *file) {
        #if defined(ZPL_SYSTEM_EMSCRIPTEN)
            ZPL_PANIC("zpl_file_temp is not supported for emscripten");
        #else
            zpl_zero_item(file);
            FILE *fd = NULL;

        #if ZPL_SYSTEM_WINDOWS && !defined(ZPL_COMPILER_GCC)
            errno_t errcode = tmpfile_s(&fd);

            if (errcode != 0) {
                fd = NULL;
            }
        #else
            fd = tmpfile();
        #endif

            if (fd == NULL) { return ZPL_FILE_ERROR_INVALID; }

            file->fd.p = fd;
            file->ops = zpl_default_file_operations;
        #endif
            return ZPL_FILE_ERROR_NONE;
        }

        zpl_file_contents zpl_file_read_contents(zpl_allocator a, zpl_b32 zero_terminate, char const *filepath) {
            zpl_file_contents result = { 0 };
            zpl_file file = { 0 };

            result.allocator = a;

            if (zpl_file_open(&file, filepath) == ZPL_FILE_ERROR_NONE) {
                zpl_isize file_size = cast(zpl_isize) zpl_file_size(&file);
                if (file_size > 0) {
                    result.data = zpl_alloc(a, zero_terminate ? file_size + 1 : file_size);
                    result.size = file_size;
                    zpl_file_read_at(&file, result.data, result.size, 0);
                    if (zero_terminate) {
                        zpl_u8 *str = cast(zpl_u8 *) result.data;
                        str[file_size] = '\0';
                    }
                }
                zpl_file_close(&file);
            }

            return result;
        }

        void zpl_file_free_contents(zpl_file_contents *fc) {
            ZPL_ASSERT_NOT_NULL(fc->data);
            zpl_free(fc->allocator, fc->data);
            fc->data = NULL;
            fc->size = 0;
        }

        char *zpl_file_read_lines(zpl_allocator alloc, zpl_array(char *)*lines, char const *filename, zpl_b32 strip_whitespace) {
            zpl_file f = { 0 };
            zpl_file_open(&f, filename);
            zpl_isize fsize = (zpl_isize)zpl_file_size(&f);

            char *contents = (char *)zpl_alloc(alloc, fsize + 1);
            zpl_file_read(&f, contents, fsize);
            contents[fsize] = 0;
            *lines = zpl_str_split_lines(alloc, contents, strip_whitespace);
            zpl_file_close(&f);

            return contents;
        }

        #if !defined(_WINDOWS_) && defined(ZPL_SYSTEM_WINDOWS)
            ZPL_IMPORT DWORD WINAPI GetFullPathNameA(char const *lpFileName, DWORD nBufferLength, char *lpBuffer, char **lpFilePart);
            ZPL_IMPORT DWORD WINAPI GetFullPathNameW(wchar_t const *lpFileName, DWORD nBufferLength, wchar_t *lpBuffer, wchar_t **lpFilePart);
        #endif

        ZPL_END_C_DECLS
        // file: source/core/filesystem.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
            #include <dirent.h>
        #endif

        #if defined(ZPL_SYSTEM_UNIX) && !defined(ZPL_SYSTEM_FREEBSD) && !defined(ZPL_SYSTEM_OPENBSD) && !defined(ZPL_SYSTEM_CYGWIN)
            #include <sys/sendfile.h>
        #endif

        #if defined(ZPL_SYSTEM_WINDOWS)
        #   include <io.h>
        #   include <direct.h>
        #endif

        #if defined(ZPL_SYSTEM_CYGWIN)
        #   include <io.h>
        #   include <dirent.h>
        #   include <windows.h>
        #endif

        ZPL_BEGIN_C_DECLS


        #if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)
            zpl_file_time zpl_fs_last_write_time(char const *filepath) {
                ULARGE_INTEGER li = { 0 };
                FILETIME last_write_time = { 0 };
                WIN32_FILE_ATTRIBUTE_DATA data = { 0 };
                zpl_allocator a = zpl_heap_allocator( );

                wchar_t *w_text = zpl__alloc_utf8_to_ucs2(a, filepath, NULL);
                if (w_text == NULL) { return 0; }
                if (GetFileAttributesExW(w_text, GetFileExInfoStandard, &data)) last_write_time = data.ftLastWriteTime;

                zpl_free(a, w_text);

                li.LowPart = last_write_time.dwLowDateTime;
                li.HighPart = last_write_time.dwHighDateTime;
                return cast(zpl_file_time) li.QuadPart;
            }

            zpl_b32 zpl_fs_copy(char const *existing_filename, char const *new_filename, zpl_b32 fail_if_exists) {
                zpl_b32 result = false;
                zpl_allocator a = zpl_heap_allocator( );

                wchar_t *w_old = zpl__alloc_utf8_to_ucs2(a, existing_filename, NULL);
                if (w_old == NULL) { return false; }

                wchar_t *w_new = zpl__alloc_utf8_to_ucs2(a, new_filename, NULL);
                if (w_new != NULL) { result = CopyFileW(w_old, w_new, fail_if_exists); }

                zpl_free(a, w_old);
                zpl_free(a, w_new);
                return result;
            }

            zpl_b32 zpl_fs_move(char const *existing_filename, char const *new_filename) {
                zpl_b32 result = false;
                zpl_allocator a = zpl_heap_allocator( );

                wchar_t *w_old = zpl__alloc_utf8_to_ucs2(a, existing_filename, NULL);
                if (w_old == NULL) { return false; }

                wchar_t *w_new = zpl__alloc_utf8_to_ucs2(a, new_filename, NULL);
                if (w_new != NULL) { result = MoveFileW(w_old, w_new); }

                zpl_free(a, w_old);
                zpl_free(a, w_new);
                return result;
            }

            zpl_b32 zpl_fs_remove(char const *filename) {
                zpl_b32 result = false;
                zpl_allocator a = zpl_heap_allocator( );

                wchar_t *w_filename = zpl__alloc_utf8_to_ucs2(a, filename, NULL);
                if (w_filename == NULL) { return false; }

                result = DeleteFileW(w_filename);

                zpl_free(a, w_filename);
                return result;
            }

        #else

            zpl_file_time zpl_fs_last_write_time(char const *filepath) {
                time_t result = 0;
                struct stat file_stat;

                if (stat(filepath, &file_stat)) result = file_stat.st_mtime;

                return cast(zpl_file_time) result;
            }

            #if defined(ZPL_SYSTEM_FREEBSD)
                #include <sys/types.h>
                #include <sys/socket.h>
                #include <sys/uio.h>
            #endif


            zpl_b32 zpl_fs_copy(char const *existing_filename, char const *new_filename, zpl_b32 fail_if_exists) {
                zpl_unused(fail_if_exists);
            #if defined(ZPL_SYSTEM_OSX)
                return copyfile(existing_filename, new_filename, NULL, COPYFILE_DATA) == 0;
            #elif defined(ZPL_SYSTEM_OPENBSD)
                ZPL_NOT_IMPLEMENTED;
                return 0;
            #else
                zpl_isize size;
                int existing_fd = open(existing_filename, O_RDONLY, 0);
                int new_fd = open(new_filename, O_WRONLY | O_CREAT, 0666);

                struct stat stat_existing;
                fstat(existing_fd, &stat_existing);

            #if defined(ZPL_SYSTEM_FREEBSD)
                size = sendfile(new_fd, existing_fd, 0, stat_existing.st_size, NULL, 0, 0);
            #else
                size = sendfile(new_fd, existing_fd, 0, stat_existing.st_size);
            #endif

                close(new_fd);
                close(existing_fd);

                return size == stat_existing.st_size;
            #endif
            }

            zpl_b32 zpl_fs_move(char const *existing_filename, char const *new_filename) {
                if (link(existing_filename, new_filename) == 0) { return (unlink(existing_filename) != -1); }
                return false;
            }

            zpl_b32 zpl_fs_remove(char const *filename) {
            #if defined(ZPL_SYSTEM_OSX) || defined(ZPL_SYSTEM_EMSCRIPTEN)
                return (unlink(filename) != -1);
            #else
                return (remove(filename) == 0);
            #endif
            }

        #endif

        char *zpl_path_get_full_name(zpl_allocator a, char const *path) {
        #if defined(ZPL_SYSTEM_WINDOWS)
            wchar_t *w_path = NULL;
            wchar_t *w_fullpath = NULL;
            zpl_isize w_len = 0;
            zpl_isize new_len = 0;
            zpl_isize new_len1 = 0;
            char *new_path = 0;

            w_path = zpl__alloc_utf8_to_ucs2(zpl_heap_allocator( ), path, NULL);
            if (w_path == NULL) { return NULL; }

            w_len = GetFullPathNameW(w_path, 0, NULL, NULL);
            if (w_len == 0) { return NULL; }

            w_fullpath = zpl_alloc_array(zpl_heap_allocator( ), wchar_t, w_len + 1);
            GetFullPathNameW(w_path, cast(int) w_len, w_fullpath, NULL);
            w_fullpath[w_len] = 0;

            zpl_free(zpl_heap_allocator( ), w_path);

            new_len = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, w_fullpath, cast(int) w_len, NULL, 0, NULL, NULL);

            if (new_len == 0) {
                zpl_free(zpl_heap_allocator( ), w_fullpath);
                return NULL;
            }

            new_path = zpl_alloc_array(a, char, new_len);
            new_len1 = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, w_fullpath, cast(int) w_len, new_path,
                                           cast(int) new_len, NULL, NULL);

            if (new_len1 == 0) {
                zpl_free(zpl_heap_allocator( ), w_fullpath);
                zpl_free(a, new_path);
                return NULL;
            }

            new_path[new_len] = 0;
            return new_path;
        #else
            char *p, *result, *fullpath = NULL;
            zpl_isize len;
            p = realpath(path, NULL);
            fullpath = p;
            if (p == NULL) {
                // NOTE(bill): File does not exist
                fullpath = cast(char *) path;
            }

            len = zpl_strlen(fullpath);

            result = zpl_alloc_array(a, char, len + 1);
            zpl_memmove(result, fullpath, len);
            result[len] = 0;
            zpl_free(a, p);

            return result;
        #endif
        }

        zpl_file_error zpl_path_mkdir(char const *path, zpl_i32 mode) {
            zpl_i32 error = 0;
        #if defined(ZPL_SYSTEM_WINDOWS)
            error = _wmkdir((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)path));
        #else
            error = mkdir(path, (mode_t)mode);
        #endif

            if (error == 0) { return ZPL_FILE_ERROR_NONE; }

            switch (errno) {
                case EPERM:
                case EACCES: return ZPL_FILE_ERROR_PERMISSION;
                case EEXIST: return ZPL_FILE_ERROR_EXISTS;
                case ENAMETOOLONG: return ZPL_FILE_ERROR_NAME_TOO_LONG;
            }

            return ZPL_FILE_ERROR_UNKNOWN;
        }

        zpl_file_error zpl_path_rmdir(char const *path) {
            zpl_i32 error = 0;
        #if defined(ZPL_SYSTEM_WINDOWS)
            error = _wrmdir((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)path));
        #else
            error = rmdir(path);
        #endif

            if (error == 0) { return ZPL_FILE_ERROR_NONE; }

            switch (errno) {
                case EPERM:
                case EACCES: return ZPL_FILE_ERROR_PERMISSION;
                case ENOENT: return ZPL_FILE_ERROR_NOT_EXISTS;
                case ENOTEMPTY: return ZPL_FILE_ERROR_NOT_EMPTY;
                case ENAMETOOLONG: return ZPL_FILE_ERROR_NAME_TOO_LONG;
            }

            return ZPL_FILE_ERROR_UNKNOWN;
        }

        void zpl__file_direntry(zpl_allocator alloc, char const *dirname, zpl_string *output, zpl_b32 recurse) {
        #if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_OSX)
            DIR *d, *cd;
            struct dirent *dir;
            d = opendir(dirname);

            if (d) {
                while ((dir = readdir(d))) {
                    if (!zpl_strncmp(dir->d_name, "..", 2)) continue;
                    if (dir->d_name[0] == '.' && dir->d_name[1] == 0) continue;

                    zpl_string dirpath = zpl_string_make(alloc, dirname);
                    dirpath = zpl_string_appendc(dirpath, "/");
                    dirpath = zpl_string_appendc(dirpath, dir->d_name);

                    *output = zpl_string_appendc(*output, dirpath);
                    *output = zpl_string_appendc(*output, "\n");

                    if (recurse && (cd = opendir(dirpath)) != NULL) { zpl__file_direntry(alloc, dirpath, output, recurse); }
                    zpl_string_free(dirpath);
                }
            }
        #elif defined(ZPL_SYSTEM_WINDOWS)
            zpl_usize length = zpl_strlen(dirname);
            struct _wfinddata_t data;
            zpl_intptr findhandle;

            char directory[MAX_PATH] = { 0 };
            zpl_strncpy(directory, dirname, length);

            // keeping it native
            for (zpl_usize i = 0; i < length; i++) {
                if (directory[i] == '/') directory[i] = '\\';
            }

            // remove trailing slashses
            if (directory[length - 1] == '\\') { directory[length - 1] = '\0'; }

            // attach search parttern
            zpl_string findpath = zpl_string_make(alloc, directory);
            findpath = zpl_string_appendc(findpath, "\\");
            findpath = zpl_string_appendc(findpath, "*");

            findhandle = _wfindfirst((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)findpath), &data);
            zpl_string_free(findpath);

            if (findhandle != -1) {
                do {
                    char *filename = (char *)zpl_ucs2_to_utf8_buf((const zpl_u16 *)data.name);
                    if (!zpl_strncmp(filename, "..", 2)) continue;
                    if (filename[0] == '.' && filename[1] == 0) continue;

                    zpl_string dirpath = zpl_string_make(alloc, directory);
                    dirpath = zpl_string_appendc(dirpath, "\\");
                    dirpath = zpl_string_appendc(dirpath, filename);

                    *output = zpl_string_appendc(*output, dirpath);
                    *output = zpl_string_appendc(*output, "\n");

                    if (recurse && (data.attrib & _A_SUBDIR)) { zpl__file_direntry(alloc, dirpath, output, recurse); }

                    zpl_string_free(dirpath);
                } while (_wfindnext(findhandle, &data) != -1);
                _findclose(findhandle);
            }
        #else
            // TODO: Implement other OSes
        #endif
        }

        zpl_string zpl_path_dirlist(zpl_allocator alloc, char const *dirname, zpl_b32 recurse) {
            zpl_string buf = zpl_string_make_reserve(alloc, 4);
            zpl__file_direntry(alloc, dirname, &buf, recurse);
            return buf;
        }

        void zpl_dirinfo_init(zpl_dir_info *dir, char const *path) {
            ZPL_ASSERT_NOT_NULL(dir);

            zpl_dir_info dir_ = {0};
            *dir = dir_;
            dir->fullpath = (char const*)zpl_malloc(zpl_strlen(path));
            zpl_strcpy((char *)dir->fullpath, path);


            zpl_string dirlist = zpl_path_dirlist(zpl_heap(), path, false);
            char **files=zpl_str_split_lines(zpl_heap(), dirlist, false);
            dir->filenames = files;
            dir->buf = dirlist;

            zpl_array_init(dir->entries, zpl_heap());

            for (zpl_i32 i=0; i<zpl_array_count(files); ++i) {
                zpl_dir_entry entry = {0};
                entry.filename = files[i];
                entry.type = zpl_fs_get_type(entry.filename);

                zpl_array_append(dir->entries, entry);
            }
        }

        zpl_internal void zpl__dirinfo_free_entry(zpl_dir_entry *entry) {
            if (entry->dir_info) {
                zpl_dirinfo_free(entry->dir_info);
                zpl_mfree(entry->dir_info);
                entry->dir_info = NULL;
            }
        }

        void zpl_dirinfo_free(zpl_dir_info *dir) {
            ZPL_ASSERT_NOT_NULL(dir);

            for (zpl_isize i = 0; i < zpl_array_count(dir->entries); ++i) {
                zpl__dirinfo_free_entry(dir->entries + i);
            }

            zpl_array_free(dir->entries);
            zpl_array_free(dir->filenames);
            zpl_string_free(dir->buf);
            zpl_mfree((void *)dir->fullpath);
        }


        zpl_u8 zpl_fs_get_type(char const *path) {
        #ifdef ZPL_SYSTEM_WINDOWS
            DWORD attrs = GetFileAttributesW((const wchar_t *)zpl_utf8_to_ucs2_buf((const zpl_u8 *)path));

            if (attrs == INVALID_FILE_ATTRIBUTES) {
                return ZPL_DIR_TYPE_UNKNOWN;
            }

            if (attrs & FILE_ATTRIBUTE_DIRECTORY) {
                return ZPL_DIR_TYPE_FOLDER;
            }
            else {
                return ZPL_DIR_TYPE_FILE;
            }

        #else
            struct stat s;
            if( stat(path,&s) == 0 )
            {
                if( s.st_mode & S_IFDIR )
                {
                    return ZPL_DIR_TYPE_FOLDER;
                }
                else
                {
                    return ZPL_DIR_TYPE_FILE;
                }
            }
        #endif

            return ZPL_DIR_TYPE_UNKNOWN;
        }

        void zpl_dirinfo_step(zpl_dir_entry *entry) {
            if (entry->dir_info) {
                zpl__dirinfo_free_entry(entry);
            }

            entry->dir_info = (zpl_dir_info *)zpl_malloc(sizeof(zpl_dir_info));
            zpl_dir_info dir_ = {0};
            *entry->dir_info = dir_;

            zpl_local_persist char buf[128] = {0};
            char const *path = entry->filename;

            if (entry->type != ZPL_DIR_TYPE_FOLDER) {
                zpl_path_fix_slashes((char *)path);
                char const* slash = zpl_char_last_occurence(path, ZPL_PATH_SEPARATOR);
                zpl_strncpy(buf, path, slash-path);
                path = buf;
            }

            zpl_dirinfo_init(entry->dir_info, path);
        }

        void zpl_file_dirinfo_refresh(zpl_file *file) {
            if (file->dir) {
                zpl__dirinfo_free_entry(file->dir);
                zpl_mfree(file->dir);
                file->dir = NULL;
            }

            file->dir = (zpl_dir_entry *)zpl_malloc(sizeof(zpl_dir_entry));
            zpl_dir_entry dir_ = {0};
            *file->dir = dir_;
            file->dir->filename = file->filename;
            file->dir->type = ZPL_DIR_TYPE_FILE;

            zpl_dirinfo_step(file->dir);
        }

        void zpl_path_fix_slashes(char *path) {
        #ifdef ZPL_SYSTEM_WINDOWS
            char *p = path;

            while (*p != '\0') {
                if (*p == '/')
                    *p = '\\';

                ++p;
            }
        #endif
        }

        ZPL_END_C_DECLS
        // file: source/core/print.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_isize zpl_printf_va(char const *fmt, va_list va) {
            return zpl_fprintf_va(zpl_file_get_standard(ZPL_FILE_STANDARD_OUTPUT), fmt, va);
        }

        zpl_isize zpl_printf_err_va(char const *fmt, va_list va) {
            return zpl_fprintf_va(zpl_file_get_standard(ZPL_FILE_STANDARD_ERROR), fmt, va);
        }

        zpl_isize zpl_fprintf_va(struct zpl_file *f, char const *fmt, va_list va) {
            zpl_local_persist char buf[4096];
            zpl_isize len = zpl_snprintf_va(buf, zpl_size_of(buf), fmt, va);
            zpl_file_write(f, buf, len - 1); // NOTE: prevent extra whitespace
            return len;
        }

        char *zpl_bprintf_va(char const *fmt, va_list va) {
            zpl_local_persist char buffer[4096];
            zpl_snprintf_va(buffer, zpl_size_of(buffer), fmt, va);
            return buffer;
        }

        zpl_isize zpl_printf(char const *fmt, ...) {
            zpl_isize res;
            va_list va;
            va_start(va, fmt);
            res = zpl_printf_va(fmt, va);
            va_end(va);
            return res;
        }

        zpl_isize zpl_printf_err(char const *fmt, ...) {
            zpl_isize res;
            va_list va;
            va_start(va, fmt);
            res = zpl_printf_err_va(fmt, va);
            va_end(va);
            return res;
        }

        zpl_isize zpl_fprintf(struct zpl_file *f, char const *fmt, ...) {
            zpl_isize res;
            va_list va;
            va_start(va, fmt);
            res = zpl_fprintf_va(f, fmt, va);
            va_end(va);
            return res;
        }

        char *zpl_bprintf(char const *fmt, ...) {
            va_list va;
            char *str;
            va_start(va, fmt);
            str = zpl_bprintf_va(fmt, va);
            va_end(va);
            return str;
        }

        zpl_isize zpl_snprintf(char *str, zpl_isize n, char const *fmt, ...) {
            zpl_isize res;
            va_list va;
            va_start(va, fmt);
            res = zpl_snprintf_va(str, n, fmt, va);
            va_end(va);
            return res;
        }


        enum {
            ZPL_FMT_MINUS = ZPL_BIT(0),
            ZPL_FMT_PLUS  = ZPL_BIT(1),
            ZPL_FMT_ALT   = ZPL_BIT(2),
            ZPL_FMT_SPACE = ZPL_BIT(3),
            ZPL_FMT_ZERO  = ZPL_BIT(4),

            ZPL_FMT_CHAR   = ZPL_BIT(5),
            ZPL_FMT_SHORT  = ZPL_BIT(6),
            ZPL_FMT_INT    = ZPL_BIT(7),
            ZPL_FMT_LONG   = ZPL_BIT(8),
            ZPL_FMT_LLONG  = ZPL_BIT(9),
            ZPL_FMT_SIZE   = ZPL_BIT(10),
            ZPL_FMT_INTPTR = ZPL_BIT(11),

            ZPL_FMT_UNSIGNED = ZPL_BIT(12),
            ZPL_FMT_LOWER    = ZPL_BIT(13),
            ZPL_FMT_UPPER    = ZPL_BIT(14),
            ZPL_FMT_WIDTH    = ZPL_BIT(15),

            ZPL_FMT_DONE = ZPL_BIT(30),

            ZPL_FMT_INTS =
                ZPL_FMT_CHAR | ZPL_FMT_SHORT | ZPL_FMT_INT  |
                ZPL_FMT_LONG | ZPL_FMT_LLONG | ZPL_FMT_SIZE | ZPL_FMT_INTPTR
        };

        typedef struct {
            zpl_i32 base;
            zpl_i32 flags;
            zpl_i32 width;
            zpl_i32 precision;
        } zpl__format_info;

        zpl_internal zpl_isize zpl__print_string(char *text, zpl_isize max_len, zpl__format_info *info, char const *str) {
            zpl_isize res = 0, len = 0;
            zpl_isize remaining = max_len;

            if (str == NULL && max_len >= 4) {
                res += zpl_strlcpy(text, "(null)", 6);
                return res;
            }

            if (info && info->precision >= 0)
                len = zpl_strnlen(str, info->precision);
            else
                len = zpl_strlen(str);

            if (info && (info->width == 0 && info->flags & ZPL_FMT_WIDTH)) {
                return res;
            }

            if (info && (info->width == 0 || info->flags & ZPL_FMT_MINUS)) {
                if (info->precision > 0) len = info->precision < len ? info->precision : len;

                res += zpl_strlcpy(text, str, len);

                if (info->width > res) {
                    zpl_isize padding = info->width - len;
                    char pad = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
                    while (padding-- > 0 && remaining-- > 0) *text++ = pad, res++;
                }
            } else {
                if (info && (info->width > res)) {
                    zpl_isize padding = info->width - len;
                    char pad = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
                    while (padding-- > 0 && remaining-- > 0) *text++ = pad, res++;
                }

                res += zpl_strlcpy(text, str, len);
            }

            if (info) {
                if (info->flags & ZPL_FMT_UPPER)
                    zpl_str_to_upper(text);
                else if (info->flags & ZPL_FMT_LOWER)
                    zpl_str_to_lower(text);
            }

            return res;
        }

        zpl_internal zpl_isize zpl__print_char(char *text, zpl_isize max_len, zpl__format_info *info, char arg) {
            char str[2] = "";
            str[0] = arg;
            return zpl__print_string(text, max_len, info, str);
        }

        zpl_internal zpl_isize zpl__print_i64(char *text, zpl_isize max_len, zpl__format_info *info, zpl_i64 value) {
            char num[130];
            zpl_i64_to_str(value, num, info ? info->base : 10);
            return zpl__print_string(text, max_len, info, num);
        }

        zpl_internal zpl_isize zpl__print_u64(char *text, zpl_isize max_len, zpl__format_info *info, zpl_u64 value) {
            char num[130];
            zpl_u64_to_str(value, num, info ? info->base : 10);
            return zpl__print_string(text, max_len, info, num);
        }

        zpl_internal zpl_isize zpl__print_f64(char *text, zpl_isize max_len, zpl__format_info *info, zpl_f64 arg) {
            // TODO: Handle exponent notation
            zpl_isize width, len, remaining = max_len;
            char *text_begin = text;

            if (arg) {
                zpl_u64 value;
                if (arg < 0) {
                    if (remaining > 1) *text = '-', remaining--;
                    text++;
                    arg = -arg;
                } else if (info->flags & ZPL_FMT_MINUS) {
                    if (remaining > 1) *text = '+', remaining--;
                    text++;
                }

                value = cast(zpl_u64) arg;
                len = zpl__print_u64(text, remaining, NULL, value);
                text += len;

                if (len >= remaining)
                    remaining = zpl_min(remaining, 1);
                else
                    remaining -= len;
                arg -= value;

                if (info->precision < 0) info->precision = 6;

                if ((info->flags & ZPL_FMT_ALT) || info->precision > 0) {
                    zpl_i64 mult = 10;
                    if (remaining > 1) *text = '.', remaining--;
                    text++;
                    while (info->precision-- > 0) {
                        value = cast(zpl_u64)(arg * mult);
                        len = zpl__print_u64(text, remaining, NULL, value);
                        text += len;
                        if (len >= remaining)
                            remaining = zpl_min(remaining, 1);
                        else
                            remaining -= len;
                        arg -= cast(zpl_f64) value / mult;
                        mult *= 10;
                    }
                }
            } else {
                if (remaining > 1) *text = '0', remaining--;
                text++;
                if (info->flags & ZPL_FMT_ALT) {
                    if (remaining > 1) *text = '.', remaining--;
                    text++;
                }
            }

            width = info->width - (text - text_begin);
            if (width > 0) {
                char fill = (info->flags & ZPL_FMT_ZERO) ? '0' : ' ';
                char *end = text + remaining - 1;
                len = (text - text_begin);

                for (len = (text - text_begin); len--;) {
                    if ((text_begin + len + width) < end) *(text_begin + len + width) = *(text_begin + len);
                }

                len = width;
                text += len;
                if (len >= remaining)
                    remaining = zpl_min(remaining, 1);
                else
                    remaining -= len;

                while (len--) {
                    if (text_begin + len < end) text_begin[len] = fill;
                }
            }

            return (text - text_begin);
        }

        ZPL_NEVER_INLINE zpl_isize zpl_snprintf_va(char *text, zpl_isize max_len, char const *fmt, va_list va) {
            char const *text_begin = text;
            zpl_isize remaining = max_len, res;

            while (*fmt) {
                zpl__format_info info = { 0 };
                zpl_isize len = 0;
                info.precision = -1;

                while (*fmt && *fmt != '%' && remaining) *text++ = *fmt++;

                if (*fmt == '%') {
                    do {
                        switch (*++fmt) {
                        case '-': {info.flags |= ZPL_FMT_MINUS; break;}
                        case '+': {info.flags |= ZPL_FMT_PLUS; break;}
                        case '#': {info.flags |= ZPL_FMT_ALT; break;}
                        case ' ': {info.flags |= ZPL_FMT_SPACE; break;}
                        case '0': {info.flags |= (ZPL_FMT_ZERO|ZPL_FMT_WIDTH); break;}
                        default: {info.flags |= ZPL_FMT_DONE; break;}
                        }
                    } while (!(info.flags & ZPL_FMT_DONE));
                }

                // NOTE: Optional Width
                if (*fmt == '*') {
                    int width = va_arg(va, int);
                    if (width < 0) {
                        info.flags |= ZPL_FMT_MINUS;
                        info.width = -width;
                    } else {
                        info.width = width;
                    }
                    info.flags |= ZPL_FMT_WIDTH;
                    fmt++;
                } else {
                    info.width = cast(zpl_i32) zpl_str_to_i64(fmt, cast(char **) & fmt, 10);
                    if (info.width != 0) {
                        info.flags |= ZPL_FMT_WIDTH;
                    }
                }

                // NOTE: Optional Precision
                if (*fmt == '.') {
                    fmt++;
                    if (*fmt == '*') {
                        info.precision = va_arg(va, int);
                        fmt++;
                    } else {
                        info.precision = cast(zpl_i32) zpl_str_to_i64(fmt, cast(char **) & fmt, 10);
                    }
                    info.flags &= ~ZPL_FMT_ZERO;
                }

                switch (*fmt++) {
                    case 'h':
                    if (*fmt == 'h') { // hh => char
                        info.flags |= ZPL_FMT_CHAR;
                        fmt++;
                    } else { // h => short
                        info.flags |= ZPL_FMT_SHORT;
                    }
                    break;

                    case 'l':
                    if (*fmt == 'l') { // ll => long long
                        info.flags |= ZPL_FMT_LLONG;
                        fmt++;
                    } else { // l => long
                        info.flags |= ZPL_FMT_LONG;
                    }
                    break;

                    break;

                    case 'z': // NOTE: zpl_usize
                        info.flags |= ZPL_FMT_UNSIGNED;
                        // fallthrough
                    case 't': // NOTE: zpl_isize
                        info.flags |= ZPL_FMT_SIZE;
                        break;

                    default: fmt--; break;
                }

                switch (*fmt) {
                    case 'u':
                        info.flags |= ZPL_FMT_UNSIGNED;
                        // fallthrough
                    case 'd':
                    case 'i': info.base = 10; break;

                    case 'o': info.base = 8; break;

                    case 'x':
                        info.base = 16;
                        info.flags |= (ZPL_FMT_UNSIGNED | ZPL_FMT_LOWER);
                        break;

                    case 'X':
                        info.base = 16;
                        info.flags |= (ZPL_FMT_UNSIGNED | ZPL_FMT_UPPER);
                        break;

                    case 'f':
                    case 'F':
                    case 'g':
                    case 'G': len = zpl__print_f64(text, remaining, &info, va_arg(va, zpl_f64)); break;

                    case 'a':
                    case 'A':
                        // TODO:
                        break;

                    case 'c': len = zpl__print_char(text, remaining, &info, cast(char) va_arg(va, int)); break;

                    case 's': len = zpl__print_string(text, remaining, &info, va_arg(va, char *)); break;

                    case 'p':
                        info.base = 16;
                        info.flags |= (ZPL_FMT_LOWER | ZPL_FMT_UNSIGNED | ZPL_FMT_ALT | ZPL_FMT_INTPTR);
                        break;

                    case '%': len = zpl__print_char(text, remaining, &info, '%'); break;

                    default: fmt--; break;
                }

                fmt++;

                if (info.base != 0) {
                    if (info.flags & ZPL_FMT_UNSIGNED) {
                        zpl_u64 value = 0;
                        switch (info.flags & ZPL_FMT_INTS) {
                            case ZPL_FMT_CHAR:   value = cast(zpl_u64) cast(zpl_u8) va_arg(va, int); break;
                            case ZPL_FMT_SHORT:  value = cast(zpl_u64) cast(zpl_u16) va_arg(va, int); break;
                            case ZPL_FMT_LONG:   value = cast(zpl_u64) va_arg(va, unsigned long); break;
                            case ZPL_FMT_LLONG:  value = cast(zpl_u64) va_arg(va, unsigned long long); break;
                            case ZPL_FMT_SIZE:   value = cast(zpl_u64) va_arg(va, zpl_usize); break;
                            case ZPL_FMT_INTPTR: value = cast(zpl_u64) va_arg(va, zpl_uintptr); break;
                            default: value             = cast(zpl_u64) va_arg(va, unsigned int); break;
                        }

                        len = zpl__print_u64(text, remaining, &info, value);

                    } else {
                        zpl_i64 value = 0;
                        switch (info.flags & ZPL_FMT_INTS) {
                            case ZPL_FMT_CHAR:   value = cast(zpl_i64) cast(zpl_i8) va_arg(va, int); break;
                            case ZPL_FMT_SHORT:  value = cast(zpl_i64) cast(zpl_i16) va_arg(va, int); break;
                            case ZPL_FMT_LONG:   value = cast(zpl_i64) va_arg(va, long); break;
                            case ZPL_FMT_LLONG:  value = cast(zpl_i64) va_arg(va, long long); break;
                            case ZPL_FMT_SIZE:   value = cast(zpl_i64) va_arg(va, zpl_usize); break;
                            case ZPL_FMT_INTPTR: value = cast(zpl_i64) va_arg(va, zpl_uintptr); break;
                            default: value             = cast(zpl_i64) va_arg(va, int); break;
                        }

                        len = zpl__print_i64(text, remaining, &info, value);
                    }
                }

                text += len;
                if (len >= remaining)
                    remaining = zpl_min(remaining, 1);
                else
                    remaining -= len;
            }

            *text++ = '\0';
            res = (text - text_begin);
            return (res >= max_len || res < 0) ? -1 : res;
        }

        ZPL_END_C_DECLS
        // file: source/core/time.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #if defined(ZPL_SYSTEM_MACOS) || ZPL_SYSTEM_UNIX
            #include <time.h>
        #endif

        #if defined(ZPL_SYSTEM_MACOS)
            #include <mach/mach.h>
            #include <mach/mach_time.h>
            #include <mach/clock.h>
        #endif

        #if defined(ZPL_SYSTEM_EMSCRIPTEN)
            #include <emscripten.h>
        #endif

        ZPL_BEGIN_C_DECLS

        //! @}
        //$$
        ////////////////////////////////////////////////////////////////
        //
        // Time
        //
        //

        #if defined(ZPL_COMPILER_MSVC) && !defined(__clang__)
            zpl_u64 zpl_rdtsc(void) { return __rdtsc( ); }
        #elif defined(__i386__)
            zpl_u64 zpl_rdtsc(void) {
                zpl_u64 x;
                __asm__ volatile(".byte 0x0f, 0x31" : "=A"(x));
                return x;
            }
        #elif defined(__x86_64__)
            zpl_u64 zpl_rdtsc(void) {
                zpl_u32 hi, lo;
                __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
                return (cast(zpl_u64) lo) | ((cast(zpl_u64) hi) << 32);
            }
        #elif defined(__powerpc__)
            zpl_u64 zpl_rdtsc(void) {
                zpl_u64 result = 0;
                zpl_u32 upper, lower, tmp;
                __asm__ volatile("0:                   \n"
                                 "\tmftbu   %0         \n"
                                 "\tmftb    %1         \n"
                                 "\tmftbu   %2         \n"
                                 "\tcmpw    %2,%0      \n"
                                 "\tbne     0b         \n"
                                 : "=r"(upper), "=r"(lower), "=r"(tmp));
                result = upper;
                result = result << 32;
                result = result | lower;

                return result;
            }
        #elif defined(ZPL_SYSTEM_EMSCRIPTEN)
            zpl_u64 zpl_rdtsc(void) {
                return (zpl_u64)(emscripten_get_now() * 1e+6);
            }
        #elif defined(ZPL_CPU_ARM)
            zpl_u64 zpl_rdtsc(void) {
                #if defined(__aarch64__)
                    int64_t r = 0;
                    asm volatile("mrs %0, cntvct_el0" : "=r"(r));
                #elif defined(__ARM_ARCH_7A__)
                    uint32_t r = 0;
                    asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r));
                #elif (__ARM_ARCH >= 6)
                    uint32_t pmccntr;
                    uint32_t pmuseren;
                    uint32_t pmcntenset;

                    // Read the user mode perf monitor counter access permissions.
                    asm volatile("mrc p15, 0, %0, c9, c14, 0" : "=r"(pmuseren));
                    if (pmuseren & 1) { // Allows reading perfmon counters for user mode code.
                        asm volatile("mrc p15, 0, %0, c9, c12, 1" : "=r"(pmcntenset));
                        if (pmcntenset & 0x80000000ul) { // Is it counting?
                            asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(pmccntr));
                            // The counter is set up to count every 64th cycle
                            return ((int64_t)pmccntr) * 64; // Should optimize to << 6
                        }
                    }
                #else
                    #error "No suitable method for zpl_rdtsc for this cpu type"
                #endif

                return r;
            }
        #endif

        #if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)

            zpl_f64 zpl_time_now(void) {
                zpl_local_persist LARGE_INTEGER win32_perf_count_freq = { 0 };
                zpl_f64 result;
                LARGE_INTEGER counter;
                zpl_local_persist LARGE_INTEGER win32_perf_counter = { 0 };
                if (!win32_perf_count_freq.QuadPart) {
                    QueryPerformanceFrequency(&win32_perf_count_freq);
                    ZPL_ASSERT(win32_perf_count_freq.QuadPart != 0);
                    QueryPerformanceCounter(&win32_perf_counter);
                }

                QueryPerformanceCounter(&counter);

                result = (counter.QuadPart - win32_perf_counter.QuadPart) / cast(zpl_f64)(win32_perf_count_freq.QuadPart);
                return result;
            }

            zpl_f64 zpl_utc_time_now(void) {
                FILETIME ft;
                ULARGE_INTEGER li;

                GetSystemTimeAsFileTime(&ft);
                li.LowPart = ft.dwLowDateTime;
                li.HighPart = ft.dwHighDateTime;

                return li.QuadPart / 10 / 10e5;
            }

            void zpl_sleep_ms(zpl_u32 ms) { Sleep(ms); }

        #else

            #if defined(ZPL_SYSTEM_LINUX) || defined(ZPL_SYSTEM_FREEBSD) || defined(ZPL_SYSTEM_OPENBSD) || defined(ZPL_SYSTEM_EMSCRIPTEN)
                zpl_f64 zpl__unix_getime(void) {
                    struct timespec t;
                    zpl_f64 result;

                    clock_gettime(1 /*CLOCK_MONOTONIC*/, &t);
                    result = t.tv_sec + 1.0e-9 * t.tv_nsec;
                    return result;
                }
            #endif

            zpl_f64 zpl_time_now(void) {
            #if defined(ZPL_SYSTEM_OSX)
                zpl_f64 result;

                zpl_local_persist zpl_f64 timebase = 0.0;
                zpl_local_persist zpl_u64 timestart = 0;

                if (!timestart) {
                    mach_timebase_info_data_t tb = { 0 };
                    mach_timebase_info(&tb);
                    timebase = tb.numer;
                    timebase /= tb.denom;
                    timestart = mach_absolute_time( );
                }

                // NOTE: mach_absolute_time() returns things in nanoseconds
                result = 1.0e-9 * (mach_absolute_time( ) - timestart) * timebase;
                return result;
            #else
                zpl_local_persist zpl_f64 unix_timestart = 0.0;

                if (!unix_timestart) { unix_timestart = zpl__unix_getime( ); }

                zpl_f64 now = zpl__unix_getime( );

                return (now - unix_timestart);
            #endif
            }

            zpl_f64 zpl_utc_time_now(void) {
                struct timespec t;
            #if defined(ZPL_SYSTEM_OSX)
                clock_serv_t cclock;
                mach_timespec_t mts;
                host_get_clock_service(mach_host_self( ), CALENDAR_CLOCK, &cclock);
                clock_get_time(cclock, &mts);
                mach_port_deallocate(mach_task_self( ), cclock);
                t.tv_sec = mts.tv_sec;
                t.tv_nsec = mts.tv_nsec;
            #else
                clock_gettime(0 /*CLOCK_REALTIME*/, &t);
            #endif
                return (cast(zpl_u64) t.tv_sec * 1000000ull + t.tv_nsec / 1000 + 11644473600000000ull) / 10e5;
            }

            void zpl_sleep_ms(zpl_u32 ms) {
                struct timespec req = { cast(time_t) ms / 1000, cast(long)((ms % 1000) * 1000000) };
                struct timespec rem = { 0, 0 };
                nanosleep(&req, &rem);
            }

        #endif

        ZPL_END_C_DECLS
        // file: source/core/random.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_MODULE_THREADING)
            zpl_global zpl_atomic32 zpl__random_shared_counter = {0};
        #else
            zpl_global zpl_i32 zpl__random_shared_counter = 0;
        #endif

        zpl_internal zpl_u32 zpl__get_noise_from_time(void) {
            zpl_u32 accum = 0;
            zpl_f64 start, remaining, end, curr = 0;
            zpl_u64 interval = 100000ll;

            start     = zpl_time_now();
            remaining = (interval - cast(zpl_u64)(interval*start)%interval) / cast(zpl_f64)interval;
            end       = start + remaining;

            do {
                curr = zpl_time_now();
                accum += cast(zpl_u32)curr;
            } while (curr >= end);
            return accum;
        }

        // NOTE: Partly from http://preshing.com/20121224/how-to-generate-a-sequence-of-unique-random-integers/
        // But the generation is even more random-er-est

        zpl_internal ZPL_ALWAYS_INLINE zpl_u32 zpl__permute_qpr(zpl_u32 x) {
            zpl_local_persist zpl_u32 const prime = 4294967291; // 2^32 - 5
            if (x >= prime) {
                return x;
            } else {
                zpl_u32 residue = cast(zpl_u32)(cast(zpl_u64) x * x) % prime;
                if (x <= prime / 2)
                    return residue;
                else
                    return prime - residue;
            }
        }

        zpl_internal ZPL_ALWAYS_INLINE zpl_u32 zpl__permute_with_offset(zpl_u32 x, zpl_u32 offset) {
            return (zpl__permute_qpr(x) + offset) ^ 0x5bf03635;
        }


        void zpl_random_init(zpl_random *r) {
            zpl_u64 time, tick;
            zpl_isize i, j;
            zpl_u32 x = 0;
            r->value = 0;

            r->offsets[0] = zpl__get_noise_from_time();
        #ifdef ZPL_MODULE_THREADING
            r->offsets[1] = zpl_atomic32_fetch_add(&zpl__random_shared_counter, 1);
            r->offsets[2] = zpl_thread_current_id();
            r->offsets[3] = zpl_thread_current_id() * 3 + 1;
        #else
            r->offsets[1] = zpl__random_shared_counter++;
            r->offsets[2] = 0;
            r->offsets[3] = 1;
        #endif
            time = cast(zpl_u64)zpl_utc_time_now();
            r->offsets[4] = cast(zpl_u32)(time >> 32);
            r->offsets[5] = cast(zpl_u32)time;
            r->offsets[6] = zpl__get_noise_from_time();
            tick = zpl_rdtsc();
            r->offsets[7] = cast(zpl_u32)(tick ^ (tick >> 32));

            for (j = 0; j < 4; j++) {
                for (i = 0; i < zpl_count_of(r->offsets); i++) {
                    r->offsets[i] = x = zpl__permute_with_offset(x, r->offsets[i]);
                }
            }
        }

        zpl_u32 zpl_random_gen_u32(zpl_random *r) {
            zpl_u32 x = r->value;
            zpl_u32 carry = 1;
            zpl_isize i;
            for (i = 0; i < zpl_count_of(r->offsets); i++) {
                x = zpl__permute_with_offset(x, r->offsets[i]);
                if (carry > 0) {
                    carry = ++r->offsets[i] ? 0 : 1;
                }
            }

            r->value = x;
            return x;
        }

        zpl_u32 zpl_random_gen_u32_unique(zpl_random *r) {
            zpl_u32 x = r->value;
            zpl_isize i;
            r->value++;
            for (i = 0; i < zpl_count_of(r->offsets); i++) {
                x = zpl__permute_with_offset(x, r->offsets[i]);
            }

            return x;
        }

        zpl_u64 zpl_random_gen_u64(zpl_random *r) {
            return ((cast(zpl_u64)zpl_random_gen_u32(r)) << 32) | zpl_random_gen_u32(r);
        }


        zpl_isize zpl_random_gen_isize(zpl_random *r) {
            zpl_u64 u = zpl_random_gen_u64(r);
            return *cast(zpl_isize *)&u;
        }


        zpl_i64 zpl_random_range_i64(zpl_random *r, zpl_i64 lower_inc, zpl_i64 higher_inc) {
            zpl_u64 u = zpl_random_gen_u64(r);
            zpl_i64 i = *cast(zpl_i64 *)&u;
            zpl_i64 diff = higher_inc-lower_inc+1;
            i %= diff;
            i += lower_inc;
            return i;
        }

        zpl_isize zpl_random_range_isize(zpl_random *r, zpl_isize lower_inc, zpl_isize higher_inc) {
            zpl_u64 u = zpl_random_gen_u64(r);
            zpl_isize i = *cast(zpl_isize *)&u;
            zpl_isize diff = higher_inc-lower_inc+1;
            i %= diff;
            i += lower_inc;
            return i;
        }

        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_copy_sign64(zpl_f64 x, zpl_f64 y) {
            zpl_i64 ix=0, iy=0;
            zpl_memcopy(&ix, &x, zpl_size_of(zpl_i64));
            zpl_memcopy(&iy, &y, zpl_size_of(zpl_i64));

            ix &= 0x7fffffffffffffff;
            ix |= iy & 0x8000000000000000;

            zpl_f64 r = 0.0;
            zpl_memcopy(&r, &ix, zpl_size_of(zpl_f64));
            return r;
        }

        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_floor64    (zpl_f64 x)        { return cast(zpl_f64)((x >= 0.0) ? cast(zpl_i64)x : cast(zpl_i64)(x-0.9999999999999999)); }
        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_ceil64     (zpl_f64 x)        { return cast(zpl_f64)((x < 0) ? cast(zpl_i64)x : (cast(zpl_i64)x)+1); }
        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_round64    (zpl_f64 x)        { return cast(zpl_f64)((x >= 0.0) ? zpl__random_floor64(x + 0.5) : zpl__random_ceil64(x - 0.5)); }
        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_remainder64(zpl_f64 x, zpl_f64 y) { return x - (zpl__random_round64(x/y)*y); }
        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_abs64      (zpl_f64 x)        { return x < 0 ? -x : x; }
        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_sign64     (zpl_f64 x)        { return x < 0 ? -1.0 : +1.0; }

        ZPL_ALWAYS_INLINE zpl_f64 zpl__random_mod64(zpl_f64 x, zpl_f64 y) {
            zpl_f64 result;
            y = zpl__random_abs64(y);
            result = zpl__random_remainder64(zpl__random_abs64(x), y);
            if (zpl__random_sign64(result)) result += y;
            return zpl__random_copy_sign64(result, x);
        }

        zpl_f64 zpl_random_range_f64(zpl_random *r, zpl_f64 lower_inc, zpl_f64 higher_inc) {
            zpl_u64 u = zpl_random_gen_u64(r);
            zpl_f64 f = 0;
            zpl_memcopy(&f, &u, zpl_size_of(zpl_f64));
            zpl_f64 diff = higher_inc-lower_inc+1.0;
            f = zpl__random_mod64(f, diff);
            f += lower_inc;
            return f;
        }

        ZPL_END_C_DECLS
        // file: source/core/misc.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
            #include <sched.h>
        #endif

        #if defined(ZPL_SYSTEM_WINDOWS)
            void zpl_exit(zpl_u32 code) { ExitProcess(code); }
        #else
            void zpl_exit(zpl_u32 code) { exit(code); }
        #endif

        void zpl_yield(void) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                Sleep(0);
            #else
                sched_yield();
            #endif
        }

        const char *zpl_get_env(const char *name) {
            char *buffer = NULL;
            const char *ptr = zpl_get_env_buf(name);

            if (ptr == NULL) {
                return NULL;
            }

            zpl_isize ptr_size = zpl_strlen(ptr);
            buffer = (char *)zpl_malloc(ptr_size * sizeof(char)+1);
            zpl_memcopy((char *)buffer, ptr, ptr_size+1);
            return buffer;
        }

        const char *zpl_get_env_buf(const char *name) {
            #ifdef ZPL_SYSTEM_WINDOWS
                zpl_local_persist wchar_t wbuffer[32767] = {0};
                zpl_local_persist char buffer[32767] = {0};

                if (!GetEnvironmentVariableW(
                        cast(LPCWSTR)zpl_utf8_to_ucs2_buf(cast(const zpl_u8 *)name),
                        cast(LPWSTR)wbuffer, 32767)) {
                    return NULL;
                }

                zpl_ucs2_to_utf8(cast(zpl_u8*)buffer, 32767, cast(const zpl_u16*)wbuffer);

                return (const char *)buffer;
            #else
                return (const char *)getenv(name);
            #endif
        }

        zpl_string zpl_get_env_str(const char *name) {
            const char *buf = zpl_get_env_buf(name);

            if (buf == NULL) {
                return NULL;
            }

            zpl_string str = zpl_string_make(zpl_heap(), buf);
            return str;
        }

        void zpl_set_env(const char *name, const char *value) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                SetEnvironmentVariableA(name, value);
            #else
                setenv(name, value, 1);
            #endif
        }

        void zpl_unset_env(const char *name) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                SetEnvironmentVariableA(name, NULL);
            #else
                unsetenv(name);
            #endif
        }

        #if !defined(ZPL_SYSTEM_WINDOWS)
            extern char **environ;
        #endif

        zpl_u32 zpl_system_command(const char *command, zpl_usize buffer_len, char *buffer) {
            #if defined(ZPL_SYSTEM_EMSCRIPTEN)
                ZPL_PANIC("zpl_system_command not supported");
            #else

                #if defined(ZPL_SYSTEM_WINDOWS)
                    FILE *handle = _popen(command, "r");
                #else
                    FILE *handle =  popen(command, "r");
                #endif

                if(!handle) return 0;

                int c;
                zpl_usize i=0;
                while ((c = getc(handle)) != EOF && i++ < buffer_len) {
                    *buffer++ = c;
                }

                #if defined(ZPL_SYSTEM_WINDOWS)
                    _pclose(handle);
                #else
                    pclose(handle);
                #endif

            #endif

            return 1;
        }

        zpl_string zpl_system_command_str(const char *command, zpl_allocator backing) {
            #if defined(ZPL_SYSTEM_EMSCRIPTEN)
                ZPL_PANIC("zpl_system_command not supported");
            #else

                #if defined(ZPL_SYSTEM_WINDOWS)
                    FILE *handle = _popen(command, "r");
                #else
                    FILE *handle =  popen(command, "r");
                #endif

                if(!handle) return NULL;

                zpl_string output = zpl_string_make_reserve(backing, 4);

                int c;
                while ((c = getc(handle)) != EOF) {
                    char ins[2] = {(char)c,0};
                    output = zpl_string_appendc(output, ins);
                }

                #if defined(ZPL_SYSTEM_WINDOWS)
                    _pclose(handle);
                #else
                    pclose(handle);
                #endif
                return output;
            #endif
            return NULL;
        }

        ZPL_END_C_DECLS
        // file: source/core/sort.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #define ZPL__COMPARE_PROC(Type)                                                                                        \
        zpl_global zpl_isize Type##__cmp_offset;                                                                         \
        ZPL_COMPARE_PROC(Type##__cmp) {                                                                              \
            Type const p = *cast(Type const *) zpl_pointer_add_const(a, Type##__cmp_offset);                         \
            Type const q = *cast(Type const *) zpl_pointer_add_const(b, Type##__cmp_offset);                         \
            return p < q ? -1 : p > q;                                                                                     \
        }                                                                                                                  \
        ZPL_COMPARE_PROC_PTR(Type##_cmp(zpl_isize offset)) {                                                             \
            Type##__cmp_offset = offset;                                                                             \
            return &Type##__cmp;                                                                                     \
        }

        ZPL__COMPARE_PROC(zpl_u8);
        ZPL__COMPARE_PROC(zpl_i16);
        ZPL__COMPARE_PROC(zpl_i32);
        ZPL__COMPARE_PROC(zpl_i64);
        ZPL__COMPARE_PROC(zpl_isize);
        ZPL__COMPARE_PROC(zpl_f32);
        ZPL__COMPARE_PROC(zpl_f64);

        // NOTE: str_cmp is special as it requires a funny type and funny comparison
        zpl_global zpl_isize zpl__str_cmp_offset;
        ZPL_COMPARE_PROC(zpl__str_cmp) {
            char const *p = *cast(char const **) zpl_pointer_add_const(a, zpl__str_cmp_offset);
            char const *q = *cast(char const **) zpl_pointer_add_const(b, zpl__str_cmp_offset);
            return zpl_strcmp(p, q);
        }
        ZPL_COMPARE_PROC_PTR(zpl_str_cmp(zpl_isize offset)) {
            zpl__str_cmp_offset = offset;
            return &zpl__str_cmp;
        }

        #undef ZPL__COMPARE_PROC

        // TODO: Make user definable?
        #define ZPL__SORT_STACK_SIZE 64
        #define zpl__SORT_INSERT_SORT_TRESHOLD 8

        #define ZPL__SORT_PUSH(_base, _limit)                                                                                  \
        do {                                                                                                               \
            stack_ptr[0] = (_base);                                                                                        \
            stack_ptr[1] = (_limit);                                                                                       \
            stack_ptr += 2;                                                                                                \
        } while (0)

        #define ZPL__SORT_POP(_base, _limit)                                                                                   \
        do {                                                                                                               \
            stack_ptr -= 2;                                                                                                \
            (_base) = stack_ptr[0];                                                                                        \
            (_limit) = stack_ptr[1];                                                                                       \
        } while (0)

        void zpl_sort(void *base_, zpl_isize count, zpl_isize size, zpl_compare_proc cmp) {
            zpl_u8 *i, *j;
            zpl_u8 *base = cast(zpl_u8 *) base_;
            zpl_u8 *limit = base + count * size;
            zpl_isize threshold = zpl__SORT_INSERT_SORT_TRESHOLD * size;

            // NOTE: Prepare the stack
            zpl_u8 *stack[ZPL__SORT_STACK_SIZE] = { 0 };
            zpl_u8 **stack_ptr = stack;

            for (;;) {
                if ((limit - base) > threshold) {
                    // NOTE: Quick sort
                    i = base + size;
                    j = limit - size;

                    zpl_memswap(((limit - base) / size / 2) * size + base, base, size);
                    if (cmp(i, j) > 0) zpl_memswap(i, j, size);
                    if (cmp(base, j) > 0) zpl_memswap(base, j, size);
                    if (cmp(i, base) > 0) zpl_memswap(i, base, size);

                    for (;;) {
                        do
                            i += size;
                        while (cmp(i, base) < 0);
                        do
                            j -= size;
                        while (cmp(j, base) > 0);
                        if (i > j) break;
                        zpl_memswap(i, j, size);
                    }

                    zpl_memswap(base, j, size);

                    if (j - base > limit - i) {
                        ZPL__SORT_PUSH(base, j);
                        base = i;
                    } else {
                        ZPL__SORT_PUSH(i, limit);
                        limit = j;
                    }
                } else {
                    // NOTE: Insertion sort
                    for (j = base, i = j + size; i < limit; j = i, i += size) {
                        for (; cmp(j, j + size) > 0; j -= size) {
                            zpl_memswap(j, j + size, size);
                            if (j == base) break;
                        }
                    }

                    if (stack_ptr == stack) break; // NOTE: Sorting is done!
                    ZPL__SORT_POP(base, limit);
                }
            }
        }

        #undef ZPL__SORT_PUSH
        #undef ZPL__SORT_POP

        #define ZPL_RADIX_SORT_PROC_GEN(Type)                                                                                  \
        ZPL_RADIX_SORT_PROC(Type) {                                                                                        \
            zpl_##Type *source = items;                                                                                          \
            zpl_##Type *dest = temp;                                                                                             \
            zpl_isize byte_index, i, byte_max = 8 * zpl_size_of(zpl_##Type);                                                         \
            for (byte_index = 0; byte_index < byte_max; byte_index += 8) {                                                 \
                zpl_isize offsets[256] = { 0 };                                                                                \
                zpl_isize total = 0;                                                                                           \
                /* NOTE: First pass - count how many of each key */                                                        \
                for (i = 0; i < count; i++) {                                                                              \
                    zpl_##Type radix_value = source[i];                                                                          \
                    zpl_##Type radix_piece = (radix_value >> byte_index) & 0xff;                                                 \
                    offsets[radix_piece]++;                                                                                \
                }                                                                                                          \
                /* NOTE: Change counts to offsets */                                                                       \
                for (i = 0; i < zpl_count_of(offsets); i++) {                                                              \
                    zpl_isize skcount = offsets[i];                                                                            \
                    offsets[i] = total;                                                                                    \
                    total += skcount;                                                                                      \
                }                                                                                                          \
                /* NOTE: Second pass - place elements into the right location */                                           \
                for (i = 0; i < count; i++) {                                                                              \
                    zpl_##Type radix_value = source[i];                                                                          \
                    zpl_##Type radix_piece = (radix_value >> byte_index) & 0xff;                                                 \
                    dest[offsets[radix_piece]++] = source[i];                                                              \
                }                                                                                                          \
                zpl_swap(zpl_##Type *, source, dest);                                                                            \
            }                                                                                                              \
        }

        ZPL_RADIX_SORT_PROC_GEN(u8);
        ZPL_RADIX_SORT_PROC_GEN(u16);
        ZPL_RADIX_SORT_PROC_GEN(u32);
        ZPL_RADIX_SORT_PROC_GEN(u64);

        void zpl_shuffle(void *base, zpl_isize count, zpl_isize size) {
            zpl_u8 *a;
            zpl_isize i, j;
            zpl_random random;
            zpl_random_init(&random);

            a = cast(zpl_u8 *) base + (count - 1) * size;
            for (i = count; i > 1; i--) {
                j = zpl_random_gen_isize(&random) % i;
                zpl_memswap(a, cast(zpl_u8 *) base + j * size, size);
                a -= size;
            }
        }

        void zpl_reverse(void *base, zpl_isize count, zpl_isize size) {
            zpl_isize i, j = count - 1;
            for (i = 0; i < j; i++, j++) zpl_memswap(cast(zpl_u8 *) base + i * size, cast(zpl_u8 *) base + j * size, size);
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_TIMER)
        // file: source/timer.c

        ////////////////////////////////////////////////////////////////
        //
        // Timer
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_timer *zpl_timer_add(zpl_timer_pool pool) {
            ZPL_ASSERT(pool);

            zpl_timer t = { 0 };
            zpl_array_append(pool, t);
            return pool + (zpl_array_count(pool) - 1);
        }

        void zpl_timer_set(zpl_timer *t, zpl_f64 duration, zpl_i32 count, zpl_timer_cb cb) {
            ZPL_ASSERT(t);

            t->duration = duration;
            t->remaining_calls = t->initial_calls = count;
            t->callback = cb;
            t->enabled = false;
        }

        void zpl_timer_start(zpl_timer *t, zpl_f64 delay_start) {
            ZPL_ASSERT(t && !t->enabled);

            t->enabled = true;
            t->remaining_calls = t->initial_calls;
            t->next_call_ts = zpl_time_now( ) + delay_start;
        }

        void zpl_timer_stop(zpl_timer *t) {
            ZPL_ASSERT(t && t->enabled);

            t->enabled = false;
        }

        void zpl_timer_update(zpl_timer_pool pool) {
            ZPL_ASSERT(pool);

            zpl_f64 now = zpl_time_now( );

            for (zpl_isize i = 0; i < zpl_array_count(pool); ++i) {
                zpl_timer *t = pool + i;

                if (t->enabled) {
                    if (t->remaining_calls > 0 || t->initial_calls == -1) {
                        if (t->next_call_ts <= now) {
                            if (t->initial_calls != -1) { --t->remaining_calls; }

                            if (t->remaining_calls == 0) {
                                t->enabled = false;
                            } else {
                                t->next_call_ts = now + t->duration;
                            }

                            t->callback(t->user_data);
                        }
                    }
                }
            }
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_HASHING)
        // file: source/hashing.c

        ////////////////////////////////////////////////////////////////
        //
        // Hashing functions
        //
        //

        #ifdef ZPL_EDITOR
        #include "../zpl.h"
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_u32 zpl_adler32(void const *data, zpl_isize len) {
            zpl_u32 const MOD_ALDER = 65521;
            zpl_u32 a = 1, b = 0;
            zpl_isize i, block_len;
            zpl_u8 const *bytes = cast(zpl_u8 const *) data;

            block_len = len % 5552;

            while (len) {
                for (i = 0; i + 7 < block_len; i += 8) {
                    a += bytes[0], b += a;
                    a += bytes[1], b += a;
                    a += bytes[2], b += a;
                    a += bytes[3], b += a;
                    a += bytes[4], b += a;
                    a += bytes[5], b += a;
                    a += bytes[6], b += a;
                    a += bytes[7], b += a;

                    bytes += 8;
                }
                for (; i < block_len; i++) a += *bytes++, b += a;

                a %= MOD_ALDER, b %= MOD_ALDER;
                len -= block_len;
                block_len = 5552;
            }

            return (b << 16) | a;
        }

        zpl_global zpl_u32 const ZPL__CRC32_TABLE[256] = {
            0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832,
            0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
            0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856, 0x646ba8c0, 0xfd62f97a,
            0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
            0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3,
            0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
            0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab,
            0xb6662d3d, 0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
            0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01, 0x6b6b51f4,
            0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
            0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074,
            0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
            0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525,
            0x206f85b3, 0xb966d409, 0xce61e49f, 0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
            0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615,
            0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
            0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7, 0xfed41b76,
            0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
            0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c, 0x36034af6,
            0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
            0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7,
            0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
            0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7,
            0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
            0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278,
            0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
            0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9, 0xbdbdf21c, 0xcabac28a, 0x53b39330,
            0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
            0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
        };

        zpl_global zpl_u64 const ZPL__CRC64_TABLE[256] = {
            0x0000000000000000ull, 0x42f0e1eba9ea3693ull, 0x85e1c3d753d46d26ull, 0xc711223cfa3e5bb5ull, 0x493366450e42ecdfull,
            0x0bc387aea7a8da4cull, 0xccd2a5925d9681f9ull, 0x8e224479f47cb76aull, 0x9266cc8a1c85d9beull, 0xd0962d61b56fef2dull,
            0x17870f5d4f51b498ull, 0x5577eeb6e6bb820bull, 0xdb55aacf12c73561ull, 0x99a54b24bb2d03f2ull, 0x5eb4691841135847ull,
            0x1c4488f3e8f96ed4ull, 0x663d78ff90e185efull, 0x24cd9914390bb37cull, 0xe3dcbb28c335e8c9ull, 0xa12c5ac36adfde5aull,
            0x2f0e1eba9ea36930ull, 0x6dfeff5137495fa3ull, 0xaaefdd6dcd770416ull, 0xe81f3c86649d3285ull, 0xf45bb4758c645c51ull,
            0xb6ab559e258e6ac2ull, 0x71ba77a2dfb03177ull, 0x334a9649765a07e4ull, 0xbd68d2308226b08eull, 0xff9833db2bcc861dull,
            0x388911e7d1f2dda8ull, 0x7a79f00c7818eb3bull, 0xcc7af1ff21c30bdeull, 0x8e8a101488293d4dull, 0x499b3228721766f8ull,
            0x0b6bd3c3dbfd506bull, 0x854997ba2f81e701ull, 0xc7b97651866bd192ull, 0x00a8546d7c558a27ull, 0x4258b586d5bfbcb4ull,
            0x5e1c3d753d46d260ull, 0x1cecdc9e94ace4f3ull, 0xdbfdfea26e92bf46ull, 0x990d1f49c77889d5ull, 0x172f5b3033043ebfull,
            0x55dfbadb9aee082cull, 0x92ce98e760d05399ull, 0xd03e790cc93a650aull, 0xaa478900b1228e31ull, 0xe8b768eb18c8b8a2ull,
            0x2fa64ad7e2f6e317ull, 0x6d56ab3c4b1cd584ull, 0xe374ef45bf6062eeull, 0xa1840eae168a547dull, 0x66952c92ecb40fc8ull,
            0x2465cd79455e395bull, 0x3821458aada7578full, 0x7ad1a461044d611cull, 0xbdc0865dfe733aa9ull, 0xff3067b657990c3aull,
            0x711223cfa3e5bb50ull, 0x33e2c2240a0f8dc3ull, 0xf4f3e018f031d676ull, 0xb60301f359dbe0e5ull, 0xda050215ea6c212full,
            0x98f5e3fe438617bcull, 0x5fe4c1c2b9b84c09ull, 0x1d14202910527a9aull, 0x93366450e42ecdf0ull, 0xd1c685bb4dc4fb63ull,
            0x16d7a787b7faa0d6ull, 0x5427466c1e109645ull, 0x4863ce9ff6e9f891ull, 0x0a932f745f03ce02ull, 0xcd820d48a53d95b7ull,
            0x8f72eca30cd7a324ull, 0x0150a8daf8ab144eull, 0x43a04931514122ddull, 0x84b16b0dab7f7968ull, 0xc6418ae602954ffbull,
            0xbc387aea7a8da4c0ull, 0xfec89b01d3679253ull, 0x39d9b93d2959c9e6ull, 0x7b2958d680b3ff75ull, 0xf50b1caf74cf481full,
            0xb7fbfd44dd257e8cull, 0x70eadf78271b2539ull, 0x321a3e938ef113aaull, 0x2e5eb66066087d7eull, 0x6cae578bcfe24bedull,
            0xabbf75b735dc1058ull, 0xe94f945c9c3626cbull, 0x676dd025684a91a1ull, 0x259d31cec1a0a732ull, 0xe28c13f23b9efc87ull,
            0xa07cf2199274ca14ull, 0x167ff3eacbaf2af1ull, 0x548f120162451c62ull, 0x939e303d987b47d7ull, 0xd16ed1d631917144ull,
            0x5f4c95afc5edc62eull, 0x1dbc74446c07f0bdull, 0xdaad56789639ab08ull, 0x985db7933fd39d9bull, 0x84193f60d72af34full,
            0xc6e9de8b7ec0c5dcull, 0x01f8fcb784fe9e69ull, 0x43081d5c2d14a8faull, 0xcd2a5925d9681f90ull, 0x8fdab8ce70822903ull,
            0x48cb9af28abc72b6ull, 0x0a3b7b1923564425ull, 0x70428b155b4eaf1eull, 0x32b26afef2a4998dull, 0xf5a348c2089ac238ull,
            0xb753a929a170f4abull, 0x3971ed50550c43c1ull, 0x7b810cbbfce67552ull, 0xbc902e8706d82ee7ull, 0xfe60cf6caf321874ull,
            0xe224479f47cb76a0ull, 0xa0d4a674ee214033ull, 0x67c58448141f1b86ull, 0x253565a3bdf52d15ull, 0xab1721da49899a7full,
            0xe9e7c031e063acecull, 0x2ef6e20d1a5df759ull, 0x6c0603e6b3b7c1caull, 0xf6fae5c07d3274cdull, 0xb40a042bd4d8425eull,
            0x731b26172ee619ebull, 0x31ebc7fc870c2f78ull, 0xbfc9838573709812ull, 0xfd39626eda9aae81ull, 0x3a28405220a4f534ull,
            0x78d8a1b9894ec3a7ull, 0x649c294a61b7ad73ull, 0x266cc8a1c85d9be0ull, 0xe17dea9d3263c055ull, 0xa38d0b769b89f6c6ull,
            0x2daf4f0f6ff541acull, 0x6f5faee4c61f773full, 0xa84e8cd83c212c8aull, 0xeabe6d3395cb1a19ull, 0x90c79d3fedd3f122ull,
            0xd2377cd44439c7b1ull, 0x15265ee8be079c04ull, 0x57d6bf0317edaa97ull, 0xd9f4fb7ae3911dfdull, 0x9b041a914a7b2b6eull,
            0x5c1538adb04570dbull, 0x1ee5d94619af4648ull, 0x02a151b5f156289cull, 0x4051b05e58bc1e0full, 0x87409262a28245baull,
            0xc5b073890b687329ull, 0x4b9237f0ff14c443ull, 0x0962d61b56fef2d0ull, 0xce73f427acc0a965ull, 0x8c8315cc052a9ff6ull,
            0x3a80143f5cf17f13ull, 0x7870f5d4f51b4980ull, 0xbf61d7e80f251235ull, 0xfd913603a6cf24a6ull, 0x73b3727a52b393ccull,
            0x31439391fb59a55full, 0xf652b1ad0167feeaull, 0xb4a25046a88dc879ull, 0xa8e6d8b54074a6adull, 0xea16395ee99e903eull,
            0x2d071b6213a0cb8bull, 0x6ff7fa89ba4afd18ull, 0xe1d5bef04e364a72ull, 0xa3255f1be7dc7ce1ull, 0x64347d271de22754ull,
            0x26c49cccb40811c7ull, 0x5cbd6cc0cc10fafcull, 0x1e4d8d2b65facc6full, 0xd95caf179fc497daull, 0x9bac4efc362ea149ull,
            0x158e0a85c2521623ull, 0x577eeb6e6bb820b0ull, 0x906fc95291867b05ull, 0xd29f28b9386c4d96ull, 0xcedba04ad0952342ull,
            0x8c2b41a1797f15d1ull, 0x4b3a639d83414e64ull, 0x09ca82762aab78f7ull, 0x87e8c60fded7cf9dull, 0xc51827e4773df90eull,
            0x020905d88d03a2bbull, 0x40f9e43324e99428ull, 0x2cffe7d5975e55e2ull, 0x6e0f063e3eb46371ull, 0xa91e2402c48a38c4ull,
            0xebeec5e96d600e57ull, 0x65cc8190991cb93dull, 0x273c607b30f68faeull, 0xe02d4247cac8d41bull, 0xa2dda3ac6322e288ull,
            0xbe992b5f8bdb8c5cull, 0xfc69cab42231bacfull, 0x3b78e888d80fe17aull, 0x7988096371e5d7e9ull, 0xf7aa4d1a85996083ull,
            0xb55aacf12c735610ull, 0x724b8ecdd64d0da5ull, 0x30bb6f267fa73b36ull, 0x4ac29f2a07bfd00dull, 0x08327ec1ae55e69eull,
            0xcf235cfd546bbd2bull, 0x8dd3bd16fd818bb8ull, 0x03f1f96f09fd3cd2ull, 0x41011884a0170a41ull, 0x86103ab85a2951f4ull,
            0xc4e0db53f3c36767ull, 0xd8a453a01b3a09b3ull, 0x9a54b24bb2d03f20ull, 0x5d45907748ee6495ull, 0x1fb5719ce1045206ull,
            0x919735e51578e56cull, 0xd367d40ebc92d3ffull, 0x1476f63246ac884aull, 0x568617d9ef46bed9ull, 0xe085162ab69d5e3cull,
            0xa275f7c11f7768afull, 0x6564d5fde549331aull, 0x279434164ca30589ull, 0xa9b6706fb8dfb2e3ull, 0xeb46918411358470ull,
            0x2c57b3b8eb0bdfc5ull, 0x6ea7525342e1e956ull, 0x72e3daa0aa188782ull, 0x30133b4b03f2b111ull, 0xf7021977f9cceaa4ull,
            0xb5f2f89c5026dc37ull, 0x3bd0bce5a45a6b5dull, 0x79205d0e0db05dceull, 0xbe317f32f78e067bull, 0xfcc19ed95e6430e8ull,
            0x86b86ed5267cdbd3ull, 0xc4488f3e8f96ed40ull, 0x0359ad0275a8b6f5ull, 0x41a94ce9dc428066ull, 0xcf8b0890283e370cull,
            0x8d7be97b81d4019full, 0x4a6acb477bea5a2aull, 0x089a2aacd2006cb9ull, 0x14dea25f3af9026dull, 0x562e43b4931334feull,
            0x913f6188692d6f4bull, 0xd3cf8063c0c759d8ull, 0x5dedc41a34bbeeb2ull, 0x1f1d25f19d51d821ull, 0xd80c07cd676f8394ull,
            0x9afce626ce85b507ull,
        };

        zpl_u32 zpl_crc32(void const *data, zpl_isize len) {
            zpl_isize remaining;
            zpl_u32 result = ~(cast(zpl_u32) 0);
            zpl_u8 const *c = cast(zpl_u8 const *) data;
            for (remaining = len; remaining--; c++) result = (result >> 8) ^ (ZPL__CRC32_TABLE[(result ^ *c) & 0xff]);
            return ~result;
        }

        zpl_u64 zpl_crc64(void const *data, zpl_isize len) {
            zpl_isize remaining;
            zpl_u64 result = ~(cast(zpl_u64) 0);
            zpl_u8 const *c = cast(zpl_u8 const *) data;
            for (remaining = len; remaining--; c++) result = (result >> 8) ^ (ZPL__CRC64_TABLE[(result ^ *c) & 0xff]);
            return ~result;
        }

        zpl_u32 zpl_fnv32(void const *data, zpl_isize len) {
            zpl_isize i;
            zpl_u32 h = 0x811c9dc5;
            zpl_u8 const *c = cast(zpl_u8 const *) data;

            for (i = 0; i < len; i++) h = (h * 0x01000193) ^ c[i];

            return h;
        }

        zpl_u64 zpl_fnv64(void const *data, zpl_isize len) {
            zpl_isize i;
            zpl_u64 h = 0xcbf29ce484222325ull;
            zpl_u8 const *c = cast(zpl_u8 const *) data;

            for (i = 0; i < len; i++) h = (h * 0x100000001b3ll) ^ c[i];

            return h;
        }

        zpl_u32 zpl_fnv32a(void const *data, zpl_isize len) {
            zpl_isize i;
            zpl_u32 h = 0x811c9dc5;
            zpl_u8 const *c = cast(zpl_u8 const *) data;

            for (i = 0; i < len; i++) h = (h ^ c[i]) * 0x01000193;

            return h;
        }

        zpl_u64 zpl_fnv64a(void const *data, zpl_isize len) {
            zpl_isize i;
            zpl_u64 h = 0xcbf29ce484222325ull;
            zpl_u8 const *c = cast(zpl_u8 const *) data;

            for (i = 0; i < len; i++) h = (h ^ c[i]) * 0x100000001b3ll;

            return h;
        }

        // base64 implementation based on https://nachtimwald.com/2017/11/18/base64-encode-and-decode-in-c/
        //
        zpl_global zpl_u8 zpl__base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


        /* generated table based on: */
        #if 0
        void zpl__base64_decode_table() {
            zpl_i32 inv[80];
            zpl_isize i;

            zpl_memset(inv, -1, zpl_size_of(inv));

            for (i=0; i < zpl_size_of(zpl__base64_chars)-1; i++) {
                inv[zpl__base64_chars[i]-43] = i;
            }
        }
        #endif
        /* === */
        zpl_global zpl_i32 zpl__base64_dec_table[] = {
            62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
            59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
            6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
            21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
            29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
            43, 44, 45, 46, 47, 48, 49, 50, 51 };

        zpl_isize zpl__base64_encoded_size(zpl_isize len) {
            zpl_isize ret = len;

            if (len % 3 != 0) {
                ret += 3 - (len % 3);
            }

            ret /= 3;
            ret *= 4;

            return ret;
        }

        zpl_isize zpl__base64_decoded_size(void const *data) {
            zpl_isize len, ret, i;
            const zpl_u8 *s = cast(const zpl_u8 *)data;

            if (s == NULL) {
                return 0;
            }

            len = zpl_strlen(cast(const char*)s);
            ret = len / 4 * 3;

            for (i=len; i-- > 0;) {
                if (s[i] == '=') {
                    ret--;
                } else {
                    break;
                }
            }

            return ret;
        }

        zpl_b32 zpl__base64_valid_char(zpl_u8 c) {
            if (c >= '0' && c <= '9')
                return true;
            if (c >= 'A' && c <= 'Z')
                return true;
            if (c >= 'a' && c <= 'z')
                return true;
            if (c == '+' || c == '/' || c == '=')
                return true;

            return false;
        }

        zpl_u8 *zpl_base64_encode(zpl_allocator a, void const *data, zpl_isize len) {
            const zpl_u8 *s = cast(const zpl_u8*)data;
            zpl_u8 *ret = NULL;
            zpl_isize enc_len, i, j, v;

            if (data == NULL || len == 0) {
                return NULL;
            }

            enc_len = zpl__base64_encoded_size(len);
            ret = cast(zpl_u8 *)zpl_alloc(a, enc_len+1);
            ret[enc_len] = 0;

            for (i=0, j=0; i < len; i+=3, j+=4) {
                v = s[i];
                v = (i+1 < len) ? (v << 8 | s[i+1]) : (v << 8);
                v = (i+2 < len) ? (v << 8 | s[i+2]) : (v << 8);

                ret[j] = zpl__base64_chars[(v >> 18) & 0x3F];
                ret[j+1] = zpl__base64_chars[(v >> 12) & 0x3F];

                if (i+1 < len)
                    ret[j+2] = zpl__base64_chars[(v >> 6) & 0x3F];

                else ret[j+2] = '=';

                if (i+2 < len)
                    ret[j+3] = zpl__base64_chars[v & 0x3F];

                else ret[j+3] = '=';

            }

            return ret;
        }

        zpl_u8 *zpl_base64_decode(zpl_allocator a, void const *data, zpl_isize len) {
            const zpl_u8 *s = cast(const zpl_u8*)data;
            zpl_u8 *ret = NULL;
            zpl_isize alen, i, j, v;

            if (data == NULL) {
                return NULL;
            }

            alen = zpl__base64_decoded_size(s);
            ret = cast(zpl_u8 *)zpl_alloc(a, alen+1);

            ZPL_ASSERT_NOT_NULL(ret);

            ret[alen] = 0;

            for (i=0; i<len; i++) {
                if (!zpl__base64_valid_char(s[i]))
                    return NULL;
            }

            for (i=0, j=0; i<len; i+=4, j+=3) {
                v = zpl__base64_dec_table[s[i]-43];
                v = (v << 6) | zpl__base64_dec_table[s[i+1]-43];
                v = (s[i+2] == '=') ? (v << 6) : ((v << 6) | zpl__base64_dec_table[s[i+2]-43]);
                v = (s[i+3] == '=') ? (v << 6) : ((v << 6) | zpl__base64_dec_table[s[i+3]-43]);

                ret[j] = (v >> 16) & 0xFF;

                if (s[i+2] != '=')
                    ret[j+1] = (v >> 8) & 0xFF;

                if (s[i+3] != '=')
                    ret[j+2] = v & 0xFF;
            }

            return ret;
        }

        zpl_u32 zpl_murmur32_seed(void const *data, zpl_isize len, zpl_u32 seed) {
            zpl_u32 const c1 = 0xcc9e2d51;
            zpl_u32 const c2 = 0x1b873593;
            zpl_u32 const r1 = 15;
            zpl_u32 const r2 = 13;
            zpl_u32 const m = 5;
            zpl_u32 const n = 0xe6546b64;

            zpl_isize i, nblocks = len / 4;
            zpl_u32 hash = seed, k1 = 0;
            zpl_u32 const *blocks = cast(zpl_u32 const *) data;
            zpl_u8 const *tail = cast(zpl_u8 const *)(data) + nblocks * 4;

            for (i = 0; i < nblocks; i++) {
                zpl_u32 k = blocks[i];
                k *= c1;
                k = (k << r1) | (k >> (32 - r1));
                k *= c2;

                hash ^= k;
                hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
            }

            switch (len & 3) {
                case 3: k1 ^= tail[2] << 16;
                case 2: k1 ^= tail[1] << 8;
                case 1:
                k1 ^= tail[0];

                k1 *= c1;
                k1 = (k1 << r1) | (k1 >> (32 - r1));
                k1 *= c2;
                hash ^= k1;
            }

            hash ^= len;
            hash ^= (hash >> 16);
            hash *= 0x85ebca6b;
            hash ^= (hash >> 13);
            hash *= 0xc2b2ae35;
            hash ^= (hash >> 16);

            return hash;
        }

        zpl_u64 zpl_murmur64_seed(void const *data_, zpl_isize len, zpl_u64 seed) {
        #if defined(ZPL_ARCH_64_BIT)
            zpl_u64 const m = 0xc6a4a7935bd1e995ULL;
            zpl_i32 const r = 47;

            zpl_u64 h = seed ^ (len * m);

            zpl_u64 const *data = cast(zpl_u64 const *) data_;
            zpl_u8 const *data2 = cast(zpl_u8 const *) data_;
            zpl_u64 const *end = data + (len / 8);

            while (data != end) {
                zpl_u64 k = *data++;

                k *= m;
                k ^= k >> r;
                k *= m;

                h ^= k;
                h *= m;
            }

            switch (len & 7) {
                case 7: h ^= cast(zpl_u64)(data2[6]) << 48;
                case 6: h ^= cast(zpl_u64)(data2[5]) << 40;
                case 5: h ^= cast(zpl_u64)(data2[4]) << 32;
                case 4: h ^= cast(zpl_u64)(data2[3]) << 24;
                case 3: h ^= cast(zpl_u64)(data2[2]) << 16;
                case 2: h ^= cast(zpl_u64)(data2[1]) << 8;
                case 1: h ^= cast(zpl_u64)(data2[0]); h *= m;
            };

            h ^= h >> r;
            h *= m;
            h ^= h >> r;

            return h;
        #else
            zpl_u64 h;
            zpl_u32 const m = 0x5bd1e995;
            zpl_i32 const r = 24;

            zpl_u32 h1 = cast(zpl_u32)(seed) ^ cast(zpl_u32)(len);
            zpl_u32 h2 = cast(zpl_u32)(seed >> 32);

            zpl_u32 const *data = cast(zpl_u32 const *) data_;

            while (len >= 8) {
                zpl_u32 k1, k2;
                k1 = *data++;
                k1 *= m;
                k1 ^= k1 >> r;
                k1 *= m;
                h1 *= m;
                h1 ^= k1;
                len -= 4;

                k2 = *data++;
                k2 *= m;
                k2 ^= k2 >> r;
                k2 *= m;
                h2 *= m;
                h2 ^= k2;
                len -= 4;
            }

            if (len >= 4) {
                zpl_u32 k1 = *data++;
                k1 *= m;
                k1 ^= k1 >> r;
                k1 *= m;
                h1 *= m;
                h1 ^= k1;
                len -= 4;
            }

            switch (len) {
                case 3: h2 ^= (cast(zpl_u8 const *) data)[2] << 16;
                case 2: h2 ^= (cast(zpl_u8 const *) data)[1] << 8;
                case 1: h2 ^= (cast(zpl_u8 const *) data)[0] << 0; h2 *= m;
            };

            h1 ^= h2 >> 18;
            h1 *= m;
            h2 ^= h1 >> 22;
            h2 *= m;
            h1 ^= h2 >> 17;
            h1 *= m;
            h2 ^= h1 >> 19;
            h2 *= m;

            h = h1;
            h = (h << 32) | h2;

            return h;
        #endif
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_REGEX)
        // file: source/regex.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        typedef enum zplreOp {
            ZPL_RE_OP_BEGIN_CAPTURE,
            ZPL_RE_OP_END_CAPTURE,

            ZPL_RE_OP_BEGINNING_OF_LINE,
            ZPL_RE_OP_END_OF_LINE,

            ZPL_RE_OP_EXACT_MATCH,
            ZPL_RE_OP_META_MATCH,

            ZPL_RE_OP_ANY,
            ZPL_RE_OP_ANY_OF,
            ZPL_RE_OP_ANY_BUT,

            ZPL_RE_OP_ZERO_OR_MORE,
            ZPL_RE_OP_ONE_OR_MORE,
            ZPL_RE_OP_ZERO_OR_MORE_SHORTEST,
            ZPL_RE_OP_ONE_OR_MORE_SHORTEST,
            ZPL_RE_OP_ZERO_OR_ONE,

            ZPL_RE_OP_BRANCH_START,
            ZPL_RE_OP_BRANCH_END
        } zplreOp;

        typedef enum zplreCode {
            ZPL_RE_CODE_NULL              = 0x0000,
            ZPL_RE_CODE_WHITESPACE        = 0x0100,
            ZPL_RE_CODE_NOT_WHITESPACE    = 0x0200,
            ZPL_RE_CODE_DIGIT             = 0x0300,
            ZPL_RE_CODE_NOT_DIGIT         = 0x0400,
            ZPL_RE_CODE_ALPHA             = 0x0500,
            ZPL_RE_CODE_LOWER             = 0x0600,
            ZPL_RE_CODE_UPPER             = 0x0700,
            ZPL_RE_CODE_WORD              = 0x0800,
            ZPL_RE_CODE_NOT_WORD          = 0x0900,

            ZPL_RE_CODE_XDIGIT            = 0x0a00,
            ZPL_RE_CODE_PRINTABLE         = 0x0b00,
        } zplreCode;

        typedef struct {
            zpl_isize op, offset;
        } zpl_re_ctx;

        enum {
            ZPL_RE__NO_MATCH = -1,
            ZPL_RE__INTERNAL_FAILURE = -2,
        };

        static char const ZPL_RE__META_CHARS[] = "^$()[].*+?|\\";
        static char const ZPL_RE__WHITESPACE[] = " \r\t\n\v\f";
        #define ZPL_RE__LITERAL(str) (str), zpl_size_of(str)-1

        static zpl_re_ctx zpl_re__exec_single(zpl_re *re, zpl_isize op, char const *str, zpl_isize str_len, zpl_isize offset, zpl_re_capture *captures, zpl_isize max_capture_count);
        static zpl_re_ctx zpl_re__exec(zpl_re *re, zpl_isize op, char const *str, zpl_isize str_len, zpl_isize offset, zpl_re_capture *captures, zpl_isize max_capture_count);

        static zpl_re_ctx zpl_re__ctx_no_match(zpl_isize op) {
            zpl_re_ctx c;
            c.op = op;
            c.offset = ZPL_RE__NO_MATCH;
            return c;
        }

        static zpl_re_ctx zpl_re__ctx_internal_failure(zpl_isize op) {
            zpl_re_ctx c;
            c.op = op;
            c.offset = ZPL_RE__INTERNAL_FAILURE;
            return c;
        }

        static zpl_u8 zpl_re__hex(char const *s) {
            return ((zpl_char_to_hex_digit(*s) << 4) & 0xf0) | (zpl_char_to_hex_digit(*(s+1)) & 0x0f);
        }

        static zpl_isize zpl_re__strfind(char const *s, zpl_isize len, char c, zpl_isize offset) {
            if (offset < len) {
                char const *found = (char const *)zpl_memchr(s+offset, c, len-offset);
                if (found)
                    return found - s;
            }

            return -1;
        }

        static zpl_b32 zpl_re__match_escape(char c, int code) {
            switch (code) {
                case ZPL_RE_CODE_NULL:           return c == 0;
                case ZPL_RE_CODE_WHITESPACE:     return zpl_re__strfind(ZPL_RE__LITERAL(ZPL_RE__WHITESPACE), c, 0) >= 0;
                case ZPL_RE_CODE_NOT_WHITESPACE: return zpl_re__strfind(ZPL_RE__LITERAL(ZPL_RE__WHITESPACE), c, 0) < 0;
                case ZPL_RE_CODE_DIGIT:          return (c >= '0' && c <= '9');
                case ZPL_RE_CODE_NOT_DIGIT:      return !(c >= '0' && c <= '9');
                case ZPL_RE_CODE_ALPHA:          return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
                case ZPL_RE_CODE_LOWER:          return (c >= 'a' && c <= 'z');
                case ZPL_RE_CODE_UPPER:          return (c >= 'A' && c <= 'Z');

                /* TODO(bill): Make better? */
                case ZPL_RE_CODE_WORD:           return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_';
                case ZPL_RE_CODE_NOT_WORD:       return !((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_');

                /* TODO(bill): Maybe replace with between tests? */
                case ZPL_RE_CODE_XDIGIT:         return zpl_re__strfind(ZPL_RE__LITERAL("0123456789ABCDEFabcdef"), c, 0) >= 0;
                case ZPL_RE_CODE_PRINTABLE:      return c >= 0x20 && c <= 0x7e;
                default: break;
            }

            return 0;
        }

        static zpl_re_ctx zpl_re__consume(zpl_re *re, zpl_isize op, char const *str, zpl_isize str_len, zpl_isize offset, zpl_re_capture *captures, zpl_isize max_capture_count, zpl_b32 is_greedy)
        {
            zpl_re_ctx c, best_c, next_c;

            c.op = op;
            c.offset = offset;

            best_c.op = ZPL_RE__NO_MATCH;
            best_c.offset = offset;

            for (;;) {
                c = zpl_re__exec_single(re, op, str, str_len, c.offset, 0, 0);
                if (c.offset > str_len || c.offset == -1) break;
                if (c.op >= re->buf_len) return c;

                next_c = zpl_re__exec(re, c.op, str, str_len, c.offset, captures, max_capture_count);
                if (next_c.offset <= str_len) {
                    if (captures)
                        zpl_re__exec(re, c.op, str, str_len, c.offset, captures, max_capture_count);

                    best_c = next_c;
                    if (!is_greedy) break;
                }

                if (best_c.op > re->buf_len)
                    best_c.op = c.op;

            }

            return best_c;
        }

        static zpl_re_ctx zpl_re__exec_single(zpl_re *re, zpl_isize op, char const *str, zpl_isize str_len, zpl_isize offset, zpl_re_capture *captures, zpl_isize max_capture_count) {
            zpl_re_ctx ctx;
            zpl_isize buffer_len;
            zpl_isize match_len;
            zpl_isize next_op;
            zpl_isize skip;

            switch (re->buf[op++]) {
                case ZPL_RE_OP_BEGIN_CAPTURE: {
                    zpl_u8 capture = re->buf[op++];
                    if (captures && (capture < max_capture_count))
                        captures[capture].str = str + offset;
                } break;

                case ZPL_RE_OP_END_CAPTURE: {
                    zpl_u8 capture = re->buf[op++];
                    if (captures && (capture < max_capture_count))
                        captures[capture].len = (str + offset) - captures[capture].str;
                } break;

                case ZPL_RE_OP_BEGINNING_OF_LINE: {
                    if (offset != 0)
                        return zpl_re__ctx_no_match(op);
                } break;

                case ZPL_RE_OP_END_OF_LINE: {
                    if (offset != str_len)
                        return zpl_re__ctx_no_match(op);
                } break;

                case ZPL_RE_OP_BRANCH_START: {
                    skip = re->buf[op++];
                    ctx = zpl_re__exec(re, op, str, str_len, offset, captures, max_capture_count);
                    if (ctx.offset <= str_len) {
                        offset = ctx.offset;
                        op = ctx.op;
                    } else {
                        ctx = zpl_re__exec(re, op + skip, str, str_len, offset, captures, max_capture_count);
                        offset = ctx.offset;
                        op = ctx.op;
                    }
                } break;

                case ZPL_RE_OP_BRANCH_END: {
                    skip = re->buf[op++];
                    op += skip;
                } break;

                case ZPL_RE_OP_ANY: {
                    if (offset < str_len) {
                        offset++;
                        break;
                    }
                    return zpl_re__ctx_no_match(op);
                } break;

                case ZPL_RE_OP_ANY_OF: {
                    zpl_isize i;
                    char cin = str[offset];
                    buffer_len = re->buf[op++];

                    if (offset >= str_len)
                        return zpl_re__ctx_no_match(op + buffer_len);

                    for (i = 0; i < buffer_len; i++) {
                        char cmatch = (char)re->buf[op+i];
                        if (!cmatch) {
                            i++;
                            if (zpl_re__match_escape(cin, re->buf[op+i] << 8))
                                break;
                        } else if (cin == cmatch) {
                            break;
                        }
                    }

                    if (i == buffer_len)
                        return zpl_re__ctx_no_match(op + buffer_len);

                    offset++;
                    op += buffer_len;
                } break;

                case ZPL_RE_OP_ANY_BUT: {
                    zpl_isize i;
                    char cin = str[offset];
                    buffer_len = re->buf[op++];

                    if (offset >= str_len)
                        return zpl_re__ctx_no_match(op + buffer_len);

                    for (i = 0; i < buffer_len; i++) {
                        char cmatch = (char)re->buf[op + i];
                        if (!cmatch) {
                            i++;
                            if (zpl_re__match_escape(cin, re->buf[op+i] << 8))
                                return zpl_re__ctx_no_match(op + buffer_len);
                        } else if (cin == cmatch) {
                            return zpl_re__ctx_no_match(op + buffer_len);
                        }
                    }

                    offset++;
                    op += buffer_len;
                } break;

                case ZPL_RE_OP_EXACT_MATCH: {
                    match_len = re->buf[op++];

                    if ((match_len > (str_len - offset)) ||
                        zpl_strncmp(str+offset, (const char*)re->buf + op, match_len) != 0)
                        return zpl_re__ctx_no_match(op + match_len);

                    op += match_len;
                    offset += match_len;
                } break;

                case ZPL_RE_OP_META_MATCH: {
                    char cin = (char)re->buf[op++];
                    char cmatch = str[offset++];

                    if (!cin) {
                        if (zpl_re__match_escape(cmatch, re->buf[op++] << 8))
                            break;
                    }
                    else if (cin == cmatch) break;

                    return zpl_re__ctx_no_match(op);
                } break;

                case ZPL_RE_OP_ZERO_OR_MORE: {
                    ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 1);
                    offset = ctx.offset;
                    op = ctx.op;
                } break;

                case ZPL_RE_OP_ONE_OR_MORE: {
                    ctx = zpl_re__exec_single(re, op, str, str_len, offset, captures, max_capture_count);

                    if (ctx.offset > str_len)
                        return ctx;

                    ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 1);
                    offset = ctx.offset;
                    op = ctx.op;
                } break;

                case ZPL_RE_OP_ZERO_OR_MORE_SHORTEST: {
                    ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 0);
                    offset = ctx.offset;
                    op = ctx.op;
                } break;

                case ZPL_RE_OP_ONE_OR_MORE_SHORTEST: {
                    ctx = zpl_re__exec_single(re, op, str, str_len, offset, captures, max_capture_count);

                    if (ctx.offset > str_len)
                        return ctx;

                    ctx = zpl_re__consume(re, op, str, str_len, offset, captures, max_capture_count, 0);
                    offset = ctx.offset;
                    op = ctx.op;
                } break;

                case ZPL_RE_OP_ZERO_OR_ONE: {
                    ctx = zpl_re__exec_single(re, op, str, str_len, offset, captures, max_capture_count);

                    if (ctx.offset <= str_len) {
                        zpl_re_ctx possible_ctx = zpl_re__exec(re, ctx.op, str, str_len, ctx.offset, captures, max_capture_count);

                        if (possible_ctx.offset <= str_len) {
                            op = possible_ctx.op;
                            offset = possible_ctx.offset;
                            break;
                        }
                    }

                    next_op = ctx.op;
                    ctx = zpl_re__exec(re, next_op, str, str_len, offset, captures, max_capture_count);

                    if (ctx.offset <= str_len) {
                        op = ctx.op;
                        offset = ctx.offset;
                        break;
                    }
                    return zpl_re__ctx_no_match(op);
                } break;

                default: {
                    return zpl_re__ctx_internal_failure(op);
                } break;
            }

            ctx.op = op;
            ctx.offset = offset;

            return ctx;
        }

        static zpl_re_ctx zpl_re__exec(zpl_re *re, zpl_isize op, char const *str, zpl_isize str_len, zpl_isize offset, zpl_re_capture *captures, zpl_isize max_capture_count) {
            zpl_re_ctx c;
            c.op = op;
            c.offset = offset;

            while (c.op < re->buf_len) {
                c = zpl_re__exec_single(re, c.op, str, str_len, c.offset, captures, max_capture_count);

                if (c.offset > str_len || c.offset == -1)
                    break;
            }

            return c;
        }

        static zpl_regex_error zpl_re__emit_ops(zpl_re *re, zpl_isize op_count, ...) {
            va_list va;

            if (re->buf_len + op_count > re->buf_cap) {
                if (!re->can_realloc) {
                    return ZPL_RE_ERROR_TOO_LONG;
                }
                else {
                    zpl_isize new_cap = (re->buf_cap*2) + op_count;
                    re->buf = (char *)zpl_resize(re->backing, re->buf, re->buf_cap, new_cap);
                    re->buf_cap = new_cap;
                }
            }

            va_start(va, op_count);
            for (zpl_isize i = 0; i < op_count; i++)
            {
                zpl_i32 v = va_arg(va, zpl_i32);
                if (v > 256)
                    return ZPL_RE_ERROR_TOO_LONG;
                re->buf[re->buf_len++] = (char)v;
            }
            va_end(va);

            return ZPL_RE_ERROR_NONE;
        }

        static zpl_regex_error zpl_re__emit_ops_buffer(zpl_re *re, zpl_isize op_count, char const *buffer) {
            if (re->buf_len + op_count > re->buf_cap) {
                if (!re->can_realloc) {
                    return ZPL_RE_ERROR_TOO_LONG;
                }
                else {
                    zpl_isize new_cap = (re->buf_cap*2) + op_count;
                    re->buf = (char *)zpl_resize(re->backing, re->buf, re->buf_cap, new_cap);
                    re->buf_cap = new_cap;
                }
            }

            for (zpl_isize i = 0; i < op_count; i++)
            {
                re->buf[re->buf_len++] = buffer[i];
            }

            return ZPL_RE_ERROR_NONE;
        }

        static int zpl_re__encode_escape(char code) {
            switch (code) {
                default:   break; /* NOTE(bill): It's a normal character */

                /* TODO(bill): Are there anymore? */
                case 't':  return '\t';
                case 'n':  return '\n';
                case 'r':  return '\r';
                case 'f':  return '\f';
                case 'v':  return '\v';

                case '0':  return ZPL_RE_CODE_NULL;

                case 's':  return ZPL_RE_CODE_WHITESPACE;
                case 'S':  return ZPL_RE_CODE_NOT_WHITESPACE;

                case 'd':  return ZPL_RE_CODE_DIGIT;
                case 'D':  return ZPL_RE_CODE_NOT_DIGIT;

                case 'a':  return ZPL_RE_CODE_ALPHA;
                case 'l':  return ZPL_RE_CODE_LOWER;
                case 'u':  return ZPL_RE_CODE_UPPER;

                case 'w':  return ZPL_RE_CODE_WORD;
                case 'W':  return ZPL_RE_CODE_NOT_WORD;

                case 'x':  return ZPL_RE_CODE_XDIGIT;
                case 'p':  return ZPL_RE_CODE_PRINTABLE;
            }
            return code;
        }

        static zpl_regex_error zpl_re__parse_group(zpl_re *re, char const *pattern, zpl_isize len, zpl_isize offset, zpl_isize *new_offset) {
            zpl_regex_error err = ZPL_RE_ERROR_NONE;
            char buffer[256] = {0};
            zpl_isize buffer_len = 0, buffer_cap = zpl_size_of(buffer);
            zpl_b32 closed = 0;
            zplreOp op = ZPL_RE_OP_ANY_OF;

            if (pattern[offset] == '^') {
                offset++;
                op = ZPL_RE_OP_ANY_BUT;
            }

            while(!closed &&
                  err == ZPL_RE_ERROR_NONE &&
                  offset < len)
            {
                if (pattern[offset] == ']') {
                    err = zpl_re__emit_ops(re, 2, (zpl_i32)op, (zpl_i32)buffer_len);
                    if (err) break;

                    err = zpl_re__emit_ops_buffer(re, buffer_len, (const char*)buffer);
                    if (err) break;
                    offset++;
                    closed = 1;
                    break;
                }

                if (buffer_len >= buffer_cap)
                    return ZPL_RE_ERROR_TOO_LONG;

                if (pattern[offset] == '\\') {
                    offset++;

                    if ((offset + 1 < len) && zpl_char_is_hex_digit(*(pattern+offset))) {
                        buffer[buffer_len++] = zpl_re__hex((pattern+offset));
                        offset++;
                    }
                    else if (offset < len) {
                        zpl_i32 code = zpl_re__encode_escape(pattern[offset]);

                        if (!code || code > 0xff) {
                            buffer[buffer_len++] = 0;

                            if (buffer_len >= buffer_cap)
                                return ZPL_RE_ERROR_TOO_LONG;

                            buffer[buffer_len++] = (code >> 8) & 0xff;
                        }
                        else {
                            buffer[buffer_len++] = code & 0xff;
                        }
                    }
                }
                else {
                    buffer[buffer_len++] = (unsigned char)pattern[offset];
                }

                offset++;
            }

            if (err) return err;
            if (!closed) return ZPL_RE_ERROR_MISMATCHED_BLOCKS;
            if (new_offset) *new_offset = offset;
            return ZPL_RE_ERROR_NONE;
        }

        static zpl_regex_error zpl_re__compile_quantifier(zpl_re *re, zpl_isize last_buf_len, unsigned char quantifier) {
            zpl_regex_error err;
            zpl_isize move_size;

            if ((re->buf[last_buf_len] == ZPL_RE_OP_EXACT_MATCH) &&
                (re->buf[last_buf_len+1] > 1))
            {
                unsigned char last_char = re->buf[re->buf_len-1];

                re->buf[last_buf_len+1]--;
                re->buf_len--;
                err = zpl_re__emit_ops(re, 4, (zpl_i32)quantifier, (zpl_i32)ZPL_RE_OP_EXACT_MATCH, 1, (zpl_i32)last_char);
                if (err) return err;
                return ZPL_RE_ERROR_NONE;
            }

            move_size = re->buf_len - last_buf_len + 1;

            err = zpl_re__emit_ops(re, 1, 0);
            if (err) return err;

            zpl_memmove(re->buf+last_buf_len+1, re->buf+last_buf_len, move_size);
            re->buf[last_buf_len] = quantifier;

            return ZPL_RE_ERROR_NONE;
        }

        static zpl_regex_error zpl_re__parse(zpl_re *re, char const *pattern, zpl_isize len, zpl_isize offset, zpl_isize level, zpl_isize *new_offset) {
            zpl_regex_error err = ZPL_RE_ERROR_NONE;
            zpl_isize last_buf_len = re->buf_len;
            zpl_isize branch_begin = re->buf_len;
            zpl_isize branch_op = -1;

            while (offset < len) {
                switch (pattern[offset++]) {
                    case '^': {
                        err = zpl_re__emit_ops(re, 1, ZPL_RE_OP_BEGINNING_OF_LINE);
                        if (err) return err;
                    } break;

                    case '$': {
                        err = zpl_re__emit_ops(re, 1, ZPL_RE_OP_END_OF_LINE);
                        if (err) return err;
                    } break;

                    case '(': {
                        zpl_isize capture = re->capture_count++;
                        last_buf_len = re->buf_len;
                        err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_BEGIN_CAPTURE, (zpl_i32)capture);
                        if (err) return err;

                        err = zpl_re__parse(re, pattern, len, offset, level+1, &offset);

                        if ((offset > len) || (pattern[offset-1] != ')'))
                            return ZPL_RE_ERROR_MISMATCHED_CAPTURES;

                        err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_END_CAPTURE, (zpl_i32)capture);
                        if (err) return err;
                    } break;

                    case ')': {
                        if (branch_op != -1)
                            re->buf[branch_op + 1] = (unsigned char)(re->buf_len - (branch_op+2));

                        if (level == 0)
                            return ZPL_RE_ERROR_MISMATCHED_CAPTURES;

                        if (new_offset) *new_offset = offset;
                        return ZPL_RE_ERROR_NONE;
                    } break;

                    case '[': {
                        last_buf_len = re->buf_len;
                        err = zpl_re__parse_group(re, pattern, len, offset, &offset);
                        if (offset > len)
                            return err;
                    } break;

                    /* NOTE(bill): Branching magic! */
                    case '|': {
                        if (branch_begin >= re->buf_len) {
                            return ZPL_RE_ERROR_BRANCH_FAILURE;
                        } else {
                            zpl_isize size = re->buf_len - branch_begin;
                            err = zpl_re__emit_ops(re, 4, 0, 0, ZPL_RE_OP_BRANCH_END, 0);
                            if (err) return err;

                            zpl_memmove(re->buf + branch_begin + 2, re->buf + branch_begin, size);
                            re->buf[branch_begin] = ZPL_RE_OP_BRANCH_START;
                            re->buf[branch_begin+1] = (size+2) & 0xff;
                            branch_op = re->buf_len-2;
                        }
                    } break;

                    case '.': {
                        last_buf_len = re->buf_len;
                        err = zpl_re__emit_ops(re, 1, ZPL_RE_OP_ANY);
                        if (err) return err;
                    } break;

                    case '*':
                    case '+':
                    {
                        unsigned char quantifier = ZPL_RE_OP_ONE_OR_MORE;
                        if (pattern[offset-1] == '*')
                            quantifier = ZPL_RE_OP_ZERO_OR_MORE;

                        if (last_buf_len >= re->buf_len)
                            return ZPL_RE_ERROR_INVALID_QUANTIFIER;
                        if ((re->buf[last_buf_len] < ZPL_RE_OP_EXACT_MATCH) ||
                            (re->buf[last_buf_len] > ZPL_RE_OP_ANY_BUT))
                            return ZPL_RE_ERROR_INVALID_QUANTIFIER;

                        if ((offset < len) && (pattern[offset] == '?')) {
                            quantifier = ZPL_RE_OP_ONE_OR_MORE_SHORTEST;
                            if (quantifier == ZPL_RE_OP_ZERO_OR_MORE)
                                quantifier = ZPL_RE_OP_ZERO_OR_MORE_SHORTEST;
                            offset++;
                        }

                        err = zpl_re__compile_quantifier(re, last_buf_len, quantifier);
                        if (err) return err;
                    } break;

                    case '?': {
                        if (last_buf_len >= re->buf_len)
                            return ZPL_RE_ERROR_INVALID_QUANTIFIER;
                        if ((re->buf[last_buf_len] < ZPL_RE_OP_EXACT_MATCH) ||
                            (re->buf[last_buf_len] > ZPL_RE_OP_ANY_BUT))
                            return ZPL_RE_ERROR_INVALID_QUANTIFIER;

                        err = zpl_re__compile_quantifier(re, last_buf_len,
                                                         (unsigned char)ZPL_RE_OP_ZERO_OR_ONE);
                        if (err) return err;
                    } break;

                    case '\\': {
                        last_buf_len = re->buf_len;
                        if ((offset+1 < len) && zpl_char_is_hex_digit(*(pattern+offset))) {
                            unsigned char hex_value = zpl_re__hex((pattern+offset));
                            offset += 2;
                            err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_META_MATCH, (int)hex_value);
                            if (err) return err;
                        } else if (offset < len) {
                            int code = zpl_re__encode_escape(pattern[offset++]);
                            if (!code || (code > 0xff)) {
                                err = zpl_re__emit_ops(re, 3, ZPL_RE_OP_META_MATCH, 0, (int)((code >> 8) & 0xff));
                                if (err) return err;
                            } else {
                                err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_META_MATCH, (int)code);
                                if (err) return err;
                            }
                        }
                    } break;

                    /* NOTE(bill): Exact match */
                    default: {
                        char const *match_start;
                        zpl_isize size = 0;
                        offset--;
                        match_start = pattern+offset;
                        while ((offset < len) &&
                               (zpl_re__strfind(ZPL_RE__LITERAL(ZPL_RE__META_CHARS), pattern[offset], 0) < 0)) {
                            size++, offset++;
                        }

                        last_buf_len = re->buf_len;
                        err = zpl_re__emit_ops(re, 2, ZPL_RE_OP_EXACT_MATCH, (int)size);
                        if (err) return err;
                        err = zpl_re__emit_ops_buffer(re, size, (char const *)match_start);
                        if (err) return err;
                    } break;
                }
            }

            if (new_offset) *new_offset = offset;
            return ZPL_RE_ERROR_NONE;
        }

        zpl_regex_error zpl_re_compile_from_buffer(zpl_re *re, char const *pattern, zpl_isize pattern_len, void *buffer, zpl_isize buffer_len) {
            zpl_regex_error err;
            re->capture_count = 0;
            re->buf = (char *)buffer;
            re->buf_len = 0;
            re->buf_cap = re->buf_len;
            re->can_realloc = 0;

            err = zpl_re__parse(re, pattern, pattern_len, 0, 0, 0);
            return err;
        }

        zpl_regex_error zpl_re_compile(zpl_re *re, zpl_allocator backing, char const *pattern, zpl_isize pattern_len) {
            zpl_regex_error err;
            zpl_isize cap = pattern_len+128;
            zpl_isize offset = 0;

            re->backing = backing;
            re->capture_count = 0;
            re->buf = (char *)zpl_alloc(backing, cap);
            re->buf_len = 0;
            re->buf_cap = cap;
            re->can_realloc = 1;

            err = zpl_re__parse(re, pattern, pattern_len, 0, 0, &offset);

            if (offset != pattern_len)
                zpl_free(backing, re->buf);

            return err;
        }

        zpl_isize zpl_re_capture_count(zpl_re *re) { return re->capture_count; }

        zpl_b32 zpl_re_match(zpl_re *re, char const *str, zpl_isize len, zpl_re_capture *captures, zpl_isize max_capture_count, zpl_isize *offset) {
            if (re && re->buf_len > 0) {
                if (re->buf[0] == ZPL_RE_OP_BEGINNING_OF_LINE) {
                    zpl_re_ctx c = zpl_re__exec(re, 0, str, len, 0, captures, max_capture_count);
                    if (c.offset >= 0 && c.offset <= len) { if (offset) *offset = c.offset; return 1; };
                    if (c.offset == ZPL_RE__INTERNAL_FAILURE) return 0;
                } else {
                    zpl_isize i;
                    for (i = 0; i < len; i++) {
                        zpl_re_ctx c = zpl_re__exec(re, 0, str, len, i, captures, max_capture_count);
                        if (c.offset >= 0 && c.offset <= len) { if (offset) *offset = c.offset; return 1; };
                        if (c.offset == ZPL_RE__INTERNAL_FAILURE) return 0;
                    }
                }
                return 0;
            }
            return 1;
        }


        zpl_b32 zpl_re_match_all(zpl_re *re, char const *str, zpl_isize str_len, zpl_isize max_capture_count,
                             zpl_re_capture **out_captures)
        {
            char *end = (char *)str + str_len;
            char *p = (char *)str;

            zpl_buffer_make(zpl_re_capture, cps, zpl_heap(), max_capture_count);

            zpl_isize offset = 0;

            while (p < end)
            {
                zpl_b32 ok = zpl_re_match(re, p, end - p, cps, max_capture_count, &offset);
                if (!ok) {
                    zpl_buffer_free2(cps);
                    return false;
                }

                p += offset;

                for (zpl_isize i = 0; i < max_capture_count; i++) {
                    zpl_array_append(*out_captures, cps[i]);
                }
            }

            zpl_buffer_free2(cps);

            return true;
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_EVENT)
        // file: source/event.c

        ////////////////////////////////////////////////////////////////
        //
        // Event Handler
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ZPL_TABLE_DEFINE(zpl_event_pool, zpl_event_pool_, zpl_event_block);

        void zpl_event_init(zpl_event_pool *pool, zpl_allocator alloc) { zpl_event_pool_init(pool, alloc); }

        void zpl_event_destroy(zpl_event_pool *pool) {
            for (zpl_isize i = 0; i < zpl_array_count(pool->entries); ++i) {
                zpl_event_block *block = &pool->entries[i].value;

                if (block) { zpl_array_free(*block); }
            }

            zpl_event_pool_destroy(pool);
        }

        zpl_u64 zpl_event_add(zpl_event_pool *pool, zpl_u64 slot, zpl_event_cb cb) {
            zpl_event_block *block = zpl_event_pool_get(pool, slot);

            if (!block) {
                zpl_event_block arr;
                zpl_array_init(arr, zpl_heap_allocator( ));
                zpl_event_pool_set(pool, slot, arr);
                block = zpl_event_pool_get(pool, slot);
            }

            zpl_u64 offset = zpl_array_count(block);
            zpl_array_append(*block, cb);
            return offset;
        }

        void zpl_event_remove(zpl_event_pool *pool, zpl_u64 slot, zpl_u64 index) {
            zpl_event_block *block = zpl_event_pool_get(pool, slot);

            if (block) { zpl_array_remove_at(*block, (zpl_isize)index); }
        }

        void zpl_event_trigger(zpl_event_pool *pool, zpl_u64 slot, zpl_event_data evt) {
            zpl_event_block *block = zpl_event_pool_get(pool, slot);

            if (block) {
                for (zpl_isize i = 0; i < zpl_array_count(*block); ++i) { (*block)[i](evt); }
            }
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_DLL)
        // file: source/dll.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #if defined(ZPL_SYSTEM_UNIX) || defined(ZPL_SYSTEM_MACOS)
            #include <dlfcn.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ////////////////////////////////////////////////////////////////
        //
        // DLL Handling
        //
        //

        #if defined(ZPL_SYSTEM_WINDOWS)
            zpl_dll_handle zpl_dll_load(char const *filepath) {
                return cast(zpl_dll_handle) LoadLibraryA(filepath);
            }

            void zpl_dll_unload(zpl_dll_handle dll) {
                FreeLibrary(cast(HMODULE) dll);
            }

            zpl_dll_proc zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name) {
                return cast(zpl_dll_proc) GetProcAddress(cast(HMODULE) dll, proc_name);
            }

        #else // POSIX

            zpl_dll_handle zpl_dll_load(char const *filepath) {
                return cast(zpl_dll_handle) dlopen(filepath, RTLD_LAZY | RTLD_GLOBAL);
            }

            void zpl_dll_unload(zpl_dll_handle dll) {
                dlclose(dll);
            }

            zpl_dll_proc zpl_dll_proc_address(zpl_dll_handle dll, char const *proc_name) {
                return cast(zpl_dll_proc) dlsym(dll, proc_name);
            }

        #endif

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_OPTS)
        // file: source/opts.c

        ////////////////////////////////////////////////////////////////
        //
        // CLI Options
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        void zpl_opts_init(zpl_opts *opts, zpl_allocator a, char const *app) {
            zpl_opts opts_ = { 0 };
            *opts = opts_;
            opts->alloc = a;
            opts->appname = app;

            zpl_array_init(opts->entries, a);
            zpl_array_init(opts->positioned, a);
            zpl_array_init(opts->errors, a);
        }

        void zpl_opts_free(zpl_opts *opts) {
            for (zpl_i32 i = 0; i < zpl_array_count(opts->entries); ++i) {
                zpl_opts_entry *e = opts->entries + i;
                if (e->type == ZPL_OPTS_STRING) {
                    zpl_string_free(e->text);
                }
            }

            zpl_array_free(opts->entries);
            zpl_array_free(opts->positioned);
            zpl_array_free(opts->errors);
        }

        void zpl_opts_add(zpl_opts *opts, char const *name, char const *lname, const char *desc, zpl_u8 type) {
            zpl_opts_entry e = { 0 };

            e.name = name;
            e.lname = lname;
            e.desc = desc;
            e.type = type;
            e.met = false;
            e.pos = false;

            zpl_array_append(opts->entries, e);
        }

        zpl_opts_entry *zpl__opts_find(zpl_opts *opts, char const *name, zpl_usize len, zpl_b32 longname) {
            zpl_opts_entry *e = 0;

            for (int i = 0; i < zpl_array_count(opts->entries); ++i) {
                e = opts->entries + i;
                char const *n = (longname ? e->lname : e->name);

                if (zpl_strnlen(name, len) == zpl_strlen(n) && !zpl_strncmp(n, name, len)) { return e; }
            }

            return NULL;
        }

        void zpl_opts_positional_add(zpl_opts *opts, char const *name) {
            zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

            if (e) {
                e->pos = true;
                zpl_array_append_at(opts->positioned, e, 0);
            }
        }

        zpl_b32 zpl_opts_positionals_filled(zpl_opts *opts) { return zpl_array_count(opts->positioned) == 0; }

        zpl_string zpl_opts_string(zpl_opts *opts, char const *name, char const *fallback) {
            zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

            return (char *)((e && e->met) ? e->text : fallback);
        }

        zpl_f64 zpl_opts_real(zpl_opts *opts, char const *name, zpl_f64 fallback) {
            zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

            return (e && e->met) ? e->real : fallback;
        }

        zpl_i64 zpl_opts_integer(zpl_opts *opts, char const *name, zpl_i64 fallback) {
            zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

            return (e && e->met) ? e->integer : fallback;
        }

        void zpl__opts_set_value(zpl_opts *opts, zpl_opts_entry *t, char *b) {
            t->met = true;

            switch (t->type) {
                case ZPL_OPTS_STRING: {
                    t->text = zpl_string_make(opts->alloc, b);
                } break;

                case ZPL_OPTS_FLOAT: {
                    t->real = zpl_str_to_f64(b, NULL);
                } break;

                case ZPL_OPTS_INT: {
                    t->integer = zpl_str_to_i64(b, NULL, 10);
                } break;
            }

            for (zpl_isize i=0; i < zpl_array_count(opts->positioned); i++) {
                if (!zpl_strcmp(opts->positioned[i]->lname, t->lname)) {
                    zpl_array_remove_at(opts->positioned, i);
                    break;
                }
            }
        }

        zpl_b32 zpl_opts_has_arg(zpl_opts *opts, char const *name) {
            zpl_opts_entry *e = zpl__opts_find(opts, name, zpl_strlen(name), true);

            if (e) { return e->met; }

            return false;
        }

        void zpl_opts_print_help(zpl_opts *opts) {
            zpl_printf("USAGE: %s", opts->appname);

            for (zpl_isize i = zpl_array_count(opts->entries); i >= 0; --i) {
                zpl_opts_entry *e = opts->entries + i;

                if (e->pos == (zpl_b32) true) { zpl_printf(" [%s]", e->lname); }
            }

            zpl_printf("\nOPTIONS:\n");

            for (zpl_isize i = 0; i < zpl_array_count(opts->entries); ++i) {
                zpl_opts_entry *e = opts->entries + i;

                zpl_printf("\t-%s, --%s: %s\n", e->name, e->lname, e->desc);
            }
        }

        void zpl_opts_print_errors(zpl_opts *opts) {
            for (int i = 0; i < zpl_array_count(opts->errors); ++i) {
                zpl_opts_err *err = (opts->errors + i);

                zpl_printf("ERROR: ");

                switch (err->type) {
                    case ZPL_OPTS_ERR_OPTION: zpl_printf("Invalid option \"%s\"", err->val); break;

                    case ZPL_OPTS_ERR_VALUE: zpl_printf("Invalid value \"%s\"", err->val); break;

                    case ZPL_OPTS_ERR_MISSING_VALUE: zpl_printf("Missing value for option \"%s\"", err->val); break;

                    case ZPL_OPTS_ERR_EXTRA_VALUE: zpl_printf("Extra value for option \"%s\"", err->val); break;
                }

                zpl_printf("\n");
            }
        }

        void zpl__opts_push_error(zpl_opts *opts, char *b, zpl_u8 errtype) {
            zpl_opts_err err = { 0 };
            err.val = b;
            err.type = errtype;
            zpl_array_append(opts->errors, err);
        }

        zpl_b32 zpl_opts_compile(zpl_opts *opts, int argc, char **argv) {
            zpl_b32 had_errors = false;
            for (int i = 1; i < argc; ++i) {
                char *p = argv[i];

                if (*p) {
                    p = zpl_str_trim(p, false);
                    if (*p == '-') {
                        zpl_opts_entry *t = 0;
                        zpl_b32 checkln = false;
                        if (*(p + 1) == '-') {
                            checkln = true;
                            ++p;
                        }

                        char *b = p + 1, *e = b;

                        while (zpl_char_is_alphanumeric(*e)) { ++e; }

                        t = zpl__opts_find(opts, b, (e - b), checkln);

                        if (t) {
                            char *ob = b;
                            b = e;

                            /**/ if (*e == '=') {
                                if (t->type == ZPL_OPTS_FLAG) {
                                    *e = '\0';
                                    zpl__opts_push_error(opts, ob, ZPL_OPTS_ERR_EXTRA_VALUE);
                                    had_errors = true;
                                    continue;
                                }

                                b = e = e + 1;
                            } else if (*e == '\0') {
                                char *sp = argv[i+1];

                                if (sp && *sp != '-' && (zpl_array_count(opts->positioned) < 1  || t->type != ZPL_OPTS_FLAG)) {
                                    if (t->type == ZPL_OPTS_FLAG) {
                                        zpl__opts_push_error(opts, b, ZPL_OPTS_ERR_EXTRA_VALUE);
                                        had_errors = true;
                                        continue;
                                    }

                                    p = sp;
                                    b = e = sp;
                                    ++i;
                                } else {
                                    if (t->type != ZPL_OPTS_FLAG) {
                                        zpl__opts_push_error(opts, ob, ZPL_OPTS_ERR_MISSING_VALUE);
                                        had_errors = true;
                                        continue;
                                    }
                                    t->met = true;
                                    continue;
                                }
                            }

                            e = zpl_str_control_skip(e, '\0');
                            zpl__opts_set_value(opts, t, b);
                        } else {
                            zpl__opts_push_error(opts, b, ZPL_OPTS_ERR_OPTION);
                            had_errors = true;
                        }
                    } else if (zpl_array_count(opts->positioned)) {
                        zpl_opts_entry *l = zpl_array_back(opts->positioned);
                        zpl_array_pop(opts->positioned);
                        zpl__opts_set_value(opts, l, p);
                    } else {
                        zpl__opts_push_error(opts, p, ZPL_OPTS_ERR_VALUE);
                        had_errors = true;
                    }
                }
            }
            return !had_errors;
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_PROCESS)
        // file: source/process.c

        ////////////////////////////////////////////////////////////////
        //
        // Process creation and manipulation methods
        //
        //
        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        static ZPL_ALWAYS_INLINE void zpl__pr_close_file_handle(zpl_file *f) {
            ZPL_ASSERT_NOT_NULL(f);
            f->fd.p  = NULL;
        }

        static ZPL_ALWAYS_INLINE void zpl__pr_close_file_handles(zpl_pr *process) {
            ZPL_ASSERT_NOT_NULL(process);

            zpl__pr_close_file_handle(&process->in);
            zpl__pr_close_file_handle(&process->out);
            zpl__pr_close_file_handle(&process->err);

            process->f_stdin = process->f_stdout = process->f_stderr = NULL;

        #ifdef ZPL_SYSTEM_WINDOWS
            process->win32_handle = NULL;
        #else
            ZPL_NOT_IMPLEMENTED;
        #endif
        }

        enum {
            ZPL_PR_HANDLE_MODE_READ,
            ZPL_PR_HANDLE_MODE_WRITE,
            ZPL_PR_HANDLE_MODES,
        };

        void *zpl__pr_open_handle(zpl_u8 type, const char *mode, void **handle) {
        #ifdef ZPL_SYSTEM_WINDOWS
            void *pipes[ZPL_PR_HANDLE_MODES];
            zpl_i32 fd;

            const zpl_u32 flag_inherit      = 0x00000001;
            SECURITY_ATTRIBUTES sa         = {zpl_size_of(sa), 0, 1};

            if (!CreatePipe(&pipes[0], &pipes[1], cast(LPSECURITY_ATTRIBUTES)&sa, 0)) {
                return NULL;
            }

            if (!SetHandleInformation(pipes[type], flag_inherit, 0)) {
                return NULL;
            }

            fd = _open_osfhandle(cast(zpl_intptr)pipes[type], 0);

            if (fd != -1) {
                *handle = pipes[1-type];
                return _fdopen(fd, mode);
            }

            return NULL;
        #else
            ZPL_NOT_IMPLEMENTED;
            return NULL;
        #endif
        }

        zpl_i32 zpl_pr_create(zpl_pr *process, const char **args, zpl_isize argc, zpl_pr_si si, zpl_pr_opts options) {
            ZPL_ASSERT_NOT_NULL(process);
            zpl_zero_item(process);

        #ifdef ZPL_SYSTEM_WINDOWS
            zpl_string cli, env;
            zpl_b32 c_env=false;
            STARTUPINFOW psi = {0};
            PROCESS_INFORMATION pi = {0};
            zpl_i32 err_code = 0;
            zpl_allocator a = zpl_heap();
            const zpl_u32 use_std_handles   = 0x00000100;

            psi.cb = zpl_size_of(psi);
            psi.dwFlags = use_std_handles | si.flags;

            if (options & ZPL_PR_OPTS_CUSTOM_ENV) {
                env = zpl_string_join(zpl_heap(), cast(const char**)si.env, si.env_count, "\0\0");
                env = zpl_string_appendc(env, "\0");
                c_env = true;
            }
            else if (!(options & ZPL_PR_OPTS_INHERIT_ENV)) {
                env = (zpl_string)"\0\0\0\0";
            } else {
                env = (zpl_string)NULL;
            }

            process->f_stdin  = zpl__pr_open_handle(ZPL_PR_HANDLE_MODE_WRITE, "wb", &psi.hStdInput);
            process->f_stdout = zpl__pr_open_handle(ZPL_PR_HANDLE_MODE_READ, "rb", &psi.hStdOutput);

            if (options & ZPL_PR_OPTS_COMBINE_STD_OUTPUT) {
                process->f_stderr = process->f_stdout;
                psi.hStdError = psi.hStdOutput;
            } else {
                process->f_stderr = zpl__pr_open_handle(ZPL_PR_HANDLE_MODE_READ, "rb", &psi.hStdError);
            }

            cli = zpl_string_join(zpl_heap(), args, argc, " ");

            psi.dwX = si.posx;
            psi.dwY = si.posy;
            psi.dwXSize = si.resx;
            psi.dwYSize = si.resy;
            psi.dwXCountChars = si.bufx;
            psi.dwYCountChars = si.bufy;
            psi.dwFillAttribute = si.fill_attr;
            psi.wShowWindow = si.show_window;

            wchar_t *w_cli = zpl__alloc_utf8_to_ucs2(a, cli, NULL);
            wchar_t *w_workdir = zpl__alloc_utf8_to_ucs2(a, si.workdir, NULL);

            if (!CreateProcessW(
                NULL,
                w_cli,
                NULL,
                NULL,
                1,
                0,
                env,
                w_workdir,
                cast(LPSTARTUPINFOW)&psi,
                cast(LPPROCESS_INFORMATION)&pi
            )) {
                err_code = -1;
                goto pr_free_data;
            }

            process->win32_handle = pi.hProcess;
            CloseHandle(pi.hThread);

            zpl_file_connect_handle(&process->in, process->f_stdin);
            zpl_file_connect_handle(&process->out, process->f_stdout);
            zpl_file_connect_handle(&process->err, process->f_stderr);

        pr_free_data:
            zpl_string_free(cli);
            zpl_free(a, w_cli);
            zpl_free(a, w_workdir);

            if (c_env)
                    zpl_string_free(env);

            return err_code;

        #else
            ZPL_NOT_IMPLEMENTED;
            return -1;
        #endif
        }


        zpl_i32 zpl_pr_join(zpl_pr *process) {
            zpl_i32 ret_code;

            ZPL_ASSERT_NOT_NULL(process);

        #ifdef ZPL_SYSTEM_WINDOWS
            if (process->f_stdin) {
                fclose(cast(FILE *)process->f_stdin);
            }

            WaitForSingleObject(process->win32_handle, INFINITE);

            if (!GetExitCodeProcess(process->win32_handle, cast(LPDWORD)&ret_code)) {
                zpl_pr_destroy(process);
                return -1;
            }

            zpl_pr_destroy(process);

            return ret_code;
        #else
            ZPL_NOT_IMPLEMENTED;
            ret_code = -1;
            return ret_code;
        #endif
        }

        void zpl_pr_destroy(zpl_pr *process) {
            ZPL_ASSERT_NOT_NULL(process);

        #ifdef ZPL_SYSTEM_WINDOWS
            if (process->f_stdin) {
                fclose(cast(FILE *)process->f_stdin);
            }

            fclose(cast(FILE *)process->f_stdout);

            if (process->f_stderr != process->f_stdout) {
                fclose(cast(FILE *)process->f_stderr);
            }

            CloseHandle(process->win32_handle);

            zpl__pr_close_file_handles(process);
        #else
            ZPL_NOT_IMPLEMENTED;
        #endif
        }

        void zpl_pr_terminate(zpl_pr *process, zpl_i32 err_code) {
            ZPL_ASSERT_NOT_NULL(process);

        #ifdef ZPL_SYSTEM_WINDOWS
            TerminateProcess(process->win32_handle, cast(UINT)err_code);
            zpl_pr_destroy(process);
        #else
            ZPL_NOT_IMPLEMENTED;
        #endif
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_MATH)
        // file: source/math.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif


        #if !defined(ZPL_NO_MATH_H)
            #include <math.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ////////////////////////////////////////////////////////////////
        //
        // Math
        //

        /* NOTE: To remove the need for memcpy */
        static void zpl__memcpy_4byte(void *dest, void const *src, zpl_isize size) {
            zpl_isize i;
            unsigned int *d, *s;
            d = (unsigned int *)dest;
            s = (unsigned int *)src;
            for (i = 0; i < size / 4; i++) { *d++ = *s++; }
        }

        zpl_f32 zpl_to_radians(zpl_f32 degrees) { return degrees * ZPL_TAU / 360.0f; }
        zpl_f32 zpl_to_degrees(zpl_f32 radians) { return radians * 360.0f / ZPL_TAU; }

        zpl_f32 zpl_angle_diff(zpl_f32 radians_a, zpl_f32 radians_b) {
            zpl_f32 delta = zpl_mod(radians_b - radians_a, ZPL_TAU);
            delta = zpl_mod(delta + 1.5f * ZPL_TAU, ZPL_TAU);
            delta -= 0.5f * ZPL_TAU;
            return delta;
        }

        zpl_f32 zpl_copy_sign(zpl_f32 x, zpl_f32 y) {
            int ix, iy;
            ix = *(int *)&x;
            iy = *(int *)&y;

            ix &= 0x7fffffff;
            ix |= iy & 0x80000000;
            return *(zpl_f32 *)&ix;
        }

        zpl_f32 zpl_remainder(zpl_f32 x, zpl_f32 y) { return x - (zpl_round(x / y) * y); }

        zpl_f32 zpl_mod(zpl_f32 x, zpl_f32 y) {
            zpl_f32 result;
            y = zpl_abs(y);
            result = zpl_remainder(zpl_abs(x), y);
            if (zpl_sign(result)) result += y;
            return zpl_copy_sign(result, x);
        }

        zpl_f64 zpl_copy_sign64(zpl_f64 x, zpl_f64 y) {
            zpl_i64 ix, iy;
            ix = *(zpl_i64 *)&x;
            iy = *(zpl_i64 *)&y;

            ix &= 0x7fffffffffffffff;
            ix |= iy & 0x8000000000000000;
            return *cast(zpl_f64 *) & ix;
        }

        zpl_f64 zpl_floor64(zpl_f64 x)                { return cast(zpl_f64)((x >= 0.0) ? cast(zpl_i64) x : cast(zpl_i64)(x - 0.9999999999999999)); }
        zpl_f64 zpl_ceil64(zpl_f64 x)                 { return cast(zpl_f64)((x < 0) ? cast(zpl_i64) x : (cast(zpl_i64) x) + 1); }
        zpl_f64 zpl_round64(zpl_f64 x)                { return cast(zpl_f64)((x >= 0.0) ? zpl_floor64(x + 0.5) : zpl_ceil64(x - 0.5)); }
        zpl_f64 zpl_remainder64(zpl_f64 x, zpl_f64 y) { return x - (zpl_round64(x / y) * y); }
        zpl_f64 zpl_abs64(zpl_f64 x)                  { return x < 0 ? -x : x; }
        zpl_f64 zpl_sign64(zpl_f64 x)                 { return x < 0 ? -1.0 : +1.0; }

        zpl_f64 zpl_mod64(zpl_f64 x, zpl_f64 y) {
            zpl_f64 result;
            y = zpl_abs64(y);
            result = zpl_remainder64(zpl_abs64(x), y);
            if (zpl_sign64(result)) result += y;
            return zpl_copy_sign64(result, x);
        }

        zpl_f32 zpl_quake_rsqrt(zpl_f32 a) {
            union {
                int i;
                zpl_f32 f;
            } t;
            zpl_f32 x2;
            zpl_f32 const three_halfs = 1.5f;

            x2 = a * 0.5f;
            t.f = a;
            t.i = 0x5f375a86 - (t.i >> 1);                /* What the fuck? */
            t.f = t.f * (three_halfs - (x2 * t.f * t.f)); /* 1st iteration */
            t.f = t.f * (three_halfs - (x2 * t.f * t.f)); /* 2nd iteration, this can be removed */

            return t.f;
        }

        #if defined(ZPL_NO_MATH_H)
            #if defined(_MSC_VER)

                zpl_f32 zpl_rsqrt(zpl_f32 a) { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(a))); }
                zpl_f32 zpl_sqrt(zpl_f32 a)  { return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(a))); };

                zpl_f32 zpl_sin(zpl_f32 a) {
                    static zpl_f32 const a0 = +1.91059300966915117e-31f;
                    static zpl_f32 const a1 = +1.00086760103908896f;
                    static zpl_f32 const a2 = -1.21276126894734565e-2f;
                    static zpl_f32 const a3 = -1.38078780785773762e-1f;
                    static zpl_f32 const a4 = -2.67353392911981221e-2f;
                    static zpl_f32 const a5 = +2.08026600266304389e-2f;
                    static zpl_f32 const a6 = -3.03996055049204407e-3f;
                    static zpl_f32 const a7 = +1.38235642404333740e-4f;
                    return a0 + a * (a1 + a * (a2 + a * (a3 + a * (a4 + a * (a5 + a * (a6 + a * a7))))));
                }

                zpl_f32 zpl_cos(zpl_f32 a) {
                    static zpl_f32 const a0 = +1.00238601909309722f;
                    static zpl_f32 const a1 = -3.81919947353040024e-2f;
                    static zpl_f32 const a2 = -3.94382342128062756e-1f;
                    static zpl_f32 const a3 = -1.18134036025221444e-1f;
                    static zpl_f32 const a4 = +1.07123798512170878e-1f;
                    static zpl_f32 const a5 = -1.86637164165180873e-2f;
                    static zpl_f32 const a6 = +9.90140908664079833e-4f;
                    static zpl_f32 const a7 = -5.23022132118824778e-14f;
                    return a0 + a * (a1 + a * (a2 + a * (a3 + a * (a4 + a * (a5 + a * (a6 + a * a7))))));
                }

                zpl_f32 zpl_tan(zpl_f32 radians) {
                    zpl_f32 rr = radians * radians;
                    zpl_f32 a = 9.5168091e-03f;
                    a *= rr;
                    a += 2.900525e-03f;
                    a *= rr;
                    a += 2.45650893e-02f;
                    a *= rr;
                    a += 5.33740603e-02f;
                    a *= rr;
                    a += 1.333923995e-01f;
                    a *= rr;
                    a += 3.333314036e-01f;
                    a *= rr;
                    a += 1.0f;
                    a *= radians;
                    return a;
                }

                zpl_f32 zpl_arcsin(zpl_f32 a) { return zpl_arctan2(a, zpl_sqrt((1.0f + a) * (1.0f - a))); }
                zpl_f32 zpl_arccos(zpl_f32 a) { return zpl_arctan2(zpl_sqrt((1.0f + a) * (1.0f - a)), a); }

                zpl_f32 zpl_arctan(zpl_f32 a) {
                    zpl_f32 u = a * a;
                    zpl_f32 u2 = u * u;
                    zpl_f32 u3 = u2 * u;
                    zpl_f32 u4 = u3 * u;
                    zpl_f32 f = 1.0f + 0.33288950512027f * u - 0.08467922817644f * u2 + 0.03252232640125f * u3 - 0.00749305860992f * u4;
                    return a / f;
                }

                zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x) {
                    if (zpl_abs(x) > zpl_abs(y)) {
                        zpl_f32 a = zpl_arctan(y / x);
                        if (x > 0.0f)
                            return a;
                        else
                            return y > 0.0f ? a + ZPL_TAU_OVER_2 : a - ZPL_TAU_OVER_2;
                    } else {
                        zpl_f32 a = zpl_arctan(x / y);
                        if (x > 0.0f)
                            return y > 0.0f ? ZPL_TAU_OVER_4 - a : -ZPL_TAU_OVER_4 - a;
                        else
                            return y > 0.0f ? ZPL_TAU_OVER_4 + a : -ZPL_TAU_OVER_4 + a;
                    }
                }

                zpl_f32 zpl_exp(zpl_f32 a) {
                    union {
                        zpl_f32 f;
                        int i;
                    } u, v;
                    u.i = (int)(6051102 * a + 1056478197);
                    v.i = (int)(1056478197 - 6051102 * a);
                    return u.f / v.f;
                }

                zpl_f32 zpl_log(zpl_f32 a) {
                    union {
                        zpl_f32 f;
                        int i;
                    } u = { a };
                    return (u.i - 1064866805) * 8.262958405176314e-8f; /* 1 / 12102203.0; */
                }

                zpl_f32 zpl_pow(zpl_f32 a, zpl_f32 b) {
                    int flipped = 0, e;
                    zpl_f32 f, r = 1.0f;
                    if (b < 0) {
                        flipped = 1;
                        b = -b;
                    }

                    e = (int)b;
                    f = zpl_exp(b - e);

                    while (e) {
                        if (e & 1) r *= a;
                        a *= a;
                        e >>= 1;
                    }

                    r *= f;
                    return flipped ? 1.0f / r : r;
                }

            #else

                zpl_f32 zpl_rsqrt(zpl_f32 a)              { return 1.0f / __builtin_sqrt(a); }
                zpl_f32 zpl_sqrt(zpl_f32 a)               { return __builtin_sqrt(a); }
                zpl_f32 zpl_sin(zpl_f32 radians)          { return __builtin_sinf(radians); }
                zpl_f32 zpl_cos(zpl_f32 radians)          { return __builtin_cosf(radians); }
                zpl_f32 zpl_tan(zpl_f32 radians)          { return __builtin_tanf(radians); }
                zpl_f32 zpl_arcsin(zpl_f32 a)             { return __builtin_asinf(a); }
                zpl_f32 zpl_arccos(zpl_f32 a)             { return __builtin_acosf(a); }
                zpl_f32 zpl_arctan(zpl_f32 a)             { return __builtin_atanf(a); }
                zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x) { return __builtin_atan2f(y, x); }

                zpl_f32 zpl_exp(zpl_f32 x) { return __builtin_expf(x); }
                zpl_f32 zpl_log(zpl_f32 x) { return __builtin_logf(x); }

                // TODO: Should this be zpl_exp(y * zpl_log(x)) ???
                zpl_f32 zpl_pow(zpl_f32 x, zpl_f32 y) { return __builtin_powf(x, y); }

            #endif
        #else
            zpl_f32 zpl_rsqrt(zpl_f32 a)                { return 1.0f / sqrtf(a); }
            zpl_f32 zpl_sqrt(zpl_f32 a)                 { return sqrtf(a); };
            zpl_f32 zpl_sin(zpl_f32 radians)            { return sinf(radians); };
            zpl_f32 zpl_cos(zpl_f32 radians)            { return cosf(radians); };
            zpl_f32 zpl_tan(zpl_f32 radians)            { return tanf(radians); };
            zpl_f32 zpl_arcsin(zpl_f32 a)               { return asinf(a); };
            zpl_f32 zpl_arccos(zpl_f32 a)               { return acosf(a); };
            zpl_f32 zpl_arctan(zpl_f32 a)               { return atanf(a); };
            zpl_f32 zpl_arctan2(zpl_f32 y, zpl_f32 x)   { return atan2f(y, x); };

            zpl_f32 zpl_exp(zpl_f32 x)            { return expf(x); }
            zpl_f32 zpl_log(zpl_f32 x)            { return logf(x); }
            zpl_f32 zpl_pow(zpl_f32 x, zpl_f32 y) { return powf(x, y); }
        #endif

        zpl_f32 zpl_exp2(zpl_f32 x) { return zpl_exp(ZPL_LOG_TWO * x); }
        zpl_f32 zpl_log2(zpl_f32 x) { return zpl_log(x) / ZPL_LOG_TWO; }

        zpl_f32 zpl_fast_exp(zpl_f32 x) {
            /* NOTE: Only works in the range -1 <= x <= +1 */
            zpl_f32 e = 1.0f + x * (1.0f + x * 0.5f * (1.0f + x * 0.3333333333f * (1.0f + x * 0.25f * (1.0f + x * 0.2f))));
            return e;
        }

        zpl_f32 zpl_fast_exp2(zpl_f32 x) { return zpl_fast_exp(ZPL_LOG_TWO * x); }

        zpl_f32 zpl_round(zpl_f32 x) { return (float)((x >= 0.0f) ? zpl_floor(x + 0.5f) : zpl_ceil(x - 0.5f)); }
        zpl_f32 zpl_floor(zpl_f32 x) { return (float)((x >= 0.0f) ? (int)x              : (int)(x - 0.9999999999999999f)); }
        zpl_f32 zpl_ceil(zpl_f32 x)  { return (float)((x <  0.0f) ? (int)x              : ((int)x) + 1); }

        zpl_f32 zpl_half_to_float(zpl_half value) {
            union {
                unsigned int i;
                zpl_f32 f;
            } result;
            int s = (value >> 15) & 0x001;
            int e = (value >> 10) & 0x01f;
            int m = value & 0x3ff;

            if (e == 0) {
                if (m == 0) {
                    /* Plus or minus zero */
                    result.i = (unsigned int)(s << 31);
                    return result.f;
                } else {
                    /* Denormalized number */
                    while (!(m & 0x00000400)) {
                        m <<= 1;
                        e -= 1;
                    }

                    e += 1;
                    m &= ~0x00000400;
                }
            } else if (e == 31) {
                if (m == 0) {
                    /* Positive or negative infinity */
                    result.i = (unsigned int)((s << 31) | 0x7f800000);
                    return result.f;
                } else {
                    /* Nan */
                    result.i = (unsigned int)((s << 31) | 0x7f800000 | (m << 13));
                    return result.f;
                }
            }

            e = e + (127 - 15);
            m = m << 13;

            result.i = (unsigned int)((s << 31) | (e << 23) | m);
            return result.f;
        }

        zpl_half zpl_float_to_half(zpl_f32 value) {
            union {
                unsigned int i;
                zpl_f32 f;
            } v;
            int i, s, e, m;

            v.f = value;
            i = (int)v.i;

            s = (i >> 16) & 0x00008000;
            e = ((i >> 23) & 0x000000ff) - (127 - 15);
            m = i & 0x007fffff;

            if (e <= 0) {
                if (e < -10) return (zpl_half)s;
                m = (m | 0x00800000) >> (1 - e);

                if (m & 0x00001000) m += 0x00002000;

                return (zpl_half)(s | (m >> 13));
            } else if (e == 0xff - (127 - 15)) {
                if (m == 0) {
                    return (zpl_half)(s | 0x7c00); /* NOTE: infinity */
                } else {
                    /* NOTE: NAN */
                    m >>= 13;
                    return (zpl_half)(s | 0x7c00 | m | (m == 0));
                }
            } else {
                if (m & 0x00001000) {
                    m += 0x00002000;
                    if (m & 0x00800000) {
                        m = 0;
                        e += 1;
                    }
                }

                if (e > 30) {
                    zpl_f32 volatile f = 1e12f;
                    int j;
                    for (j = 0; j < 10; j++) f *= f; /* NOTE: Cause overflow */

                    return (zpl_half)(s | 0x7c00);
                }

                return (zpl_half)(s | (e << 10) | (m >> 13));
            }
        }

        #define ZPL_VEC2_2OP(a, c, post) \
            a->x = c.x post;             \
            a->y = c.y post;

        #define ZPL_VEC2_3OP(a, b, op, c, post) \
            a->x = b.x op c.x post;             \
            a->y = b.y op c.y post;

        #define ZPL_VEC3_2OP(a, c, post) \
            a->x = c.x post;             \
            a->y = c.y post;             \
            a->z = c.z post;

        #define ZPL_VEC3_3OP(a, b, op, c, post) \
            a->x = b.x op c.x post;             \
            a->y = b.y op c.y post;             \
            a->z = b.z op c.z post;

        #define ZPL_VEC4_2OP(a, c, post) \
            a->x = c.x post;             \
            a->y = c.y post;             \
            a->z = c.z post;             \
            a->w = c.w post;

        #define ZPL_VEC4_3OP(a, b, op, c, post) \
            a->x = b.x op c.x post;             \
            a->y = b.y op c.y post;             \
            a->z = b.z op c.z post;             \
            a->w = b.w op c.w post;

        zpl_vec2 zpl_vec2f_zero(void) {
            zpl_vec2 v = { 0, 0 };
            return v;
        }
        zpl_vec2 zpl_vec2f(zpl_f32 x, zpl_f32 y) {
            zpl_vec2 v;
            v.x = x;
            v.y = y;
            return v;
        }
        zpl_vec2 zpl_vec2fv(zpl_f32 x[2]) {
            zpl_vec2 v;
            v.x = x[0];
            v.y = x[1];
            return v;
        }

        zpl_vec3 zpl_vec3f_zero(void) {
            zpl_vec3 v = { 0, 0, 0 };
            return v;
        }
        zpl_vec3 zpl_vec3f(zpl_f32 x, zpl_f32 y, zpl_f32 z) {
            zpl_vec3 v;
            v.x = x;
            v.y = y;
            v.z = z;
            return v;
        }
        zpl_vec3 zpl_vec3fv(zpl_f32 x[3]) {
            zpl_vec3 v;
            v.x = x[0];
            v.y = x[1];
            v.z = x[2];
            return v;
        }

        zpl_vec4 zpl_vec4f_zero(void) {
            zpl_vec4 v = { 0, 0, 0, 0 };
            return v;
        }
        zpl_vec4 zpl_vec4f(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w) {
            zpl_vec4 v;
            v.x = x;
            v.y = y;
            v.z = z;
            v.w = w;
            return v;
        }
        zpl_vec4 zpl_vec4fv(zpl_f32 x[4]) {
            zpl_vec4 v;
            v.x = x[0];
            v.y = x[1];
            v.z = x[2];
            v.w = x[3];
            return v;
        }

        zpl_f32 zpl_vec2_max(zpl_vec2 v) { return zpl_max(v.x, v.y); }
        zpl_f32 zpl_vec2_side(zpl_vec2 p, zpl_vec2 q, zpl_vec2 r) { return ((q.x - p.x) * (r.y - p.y) - (r.x - p.x) * (q.y - p.y)); }

        void zpl_vec2_add(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1) { ZPL_VEC2_3OP(d, v0, +, v1, +0); }
        void zpl_vec2_sub(zpl_vec2 *d, zpl_vec2 v0, zpl_vec2 v1) { ZPL_VEC2_3OP(d, v0, -, v1, +0); }
        void zpl_vec2_mul(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s)    { ZPL_VEC2_2OP(d, v, *s); }
        void zpl_vec2_div(zpl_vec2 *d, zpl_vec2 v, zpl_f32 s)    { ZPL_VEC2_2OP(d, v, / s); }

        zpl_f32 zpl_vec3_max(zpl_vec3 v) { return zpl_max3(v.x, v.y, v.z); }

        void zpl_vec3_add(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1) { ZPL_VEC3_3OP(d, v0, +, v1, +0); }
        void zpl_vec3_sub(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1) { ZPL_VEC3_3OP(d, v0, -, v1, +0); }
        void zpl_vec3_mul(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s)    { ZPL_VEC3_2OP(d, v, *s); }
        void zpl_vec3_div(zpl_vec3 *d, zpl_vec3 v, zpl_f32 s)    { ZPL_VEC3_2OP(d, v, / s); }

        void zpl_vec4_add(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1) { ZPL_VEC4_3OP(d, v0, +, v1, +0); }
        void zpl_vec4_sub(zpl_vec4 *d, zpl_vec4 v0, zpl_vec4 v1) { ZPL_VEC4_3OP(d, v0, -, v1, +0); }
        void zpl_vec4_mul(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s)    { ZPL_VEC4_2OP(d, v, *s); }
        void zpl_vec4_div(zpl_vec4 *d, zpl_vec4 v, zpl_f32 s)    { ZPL_VEC4_2OP(d, v, / s); }

        void zpl_vec2_addeq(zpl_vec2 *d, zpl_vec2 v) { ZPL_VEC2_3OP(d, (*d), +, v, +0); }
        void zpl_vec2_subeq(zpl_vec2 *d, zpl_vec2 v) { ZPL_VEC2_3OP(d, (*d), -, v, +0); }
        void zpl_vec2_muleq(zpl_vec2 *d, zpl_f32 s)  { ZPL_VEC2_2OP(d, (*d), *s); }
        void zpl_vec2_diveq(zpl_vec2 *d, zpl_f32 s)  { ZPL_VEC2_2OP(d, (*d), / s); }

        void zpl_vec3_addeq(zpl_vec3 *d, zpl_vec3 v) { ZPL_VEC3_3OP(d, (*d), +, v, +0); }
        void zpl_vec3_subeq(zpl_vec3 *d, zpl_vec3 v) { ZPL_VEC3_3OP(d, (*d), -, v, +0); }
        void zpl_vec3_muleq(zpl_vec3 *d, zpl_f32 s)  { ZPL_VEC3_2OP(d, (*d), *s); }
        void zpl_vec3_diveq(zpl_vec3 *d, zpl_f32 s)  { ZPL_VEC3_2OP(d, (*d), / s); }

        void zpl_vec4_addeq(zpl_vec4 *d, zpl_vec4 v) { ZPL_VEC4_3OP(d, (*d), +, v, +0); }
        void zpl_vec4_subeq(zpl_vec4 *d, zpl_vec4 v) { ZPL_VEC4_3OP(d, (*d), -, v, +0); }
        void zpl_vec4_muleq(zpl_vec4 *d, zpl_f32 s)  { ZPL_VEC4_2OP(d, (*d), *s); }
        void zpl_vec4_diveq(zpl_vec4 *d, zpl_f32 s)  { ZPL_VEC4_2OP(d, (*d), / s); }

        #undef ZPL_VEC2_2OP
        #undef ZPL_VEC2_3OP
        #undef ZPL_VEC3_3OP
        #undef ZPL_VEC3_2OP
        #undef ZPL_VEC4_2OP
        #undef ZPL_VEC4_3OP

        zpl_f32 zpl_vec2_dot(zpl_vec2 v0, zpl_vec2 v1) { return v0.x * v1.x + v0.y * v1.y; }
        zpl_f32 zpl_vec3_dot(zpl_vec3 v0, zpl_vec3 v1) { return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z; }
        zpl_f32 zpl_vec4_dot(zpl_vec4 v0, zpl_vec4 v1) { return v0.x * v1.x + v0.y * v1.y + v0.z * v1.z + v0.w * v1.w; }

        void zpl_vec2_cross(zpl_f32 *d, zpl_vec2 v0, zpl_vec2 v1) { *d = v0.x * v1.y - v1.x * v0.y; }
        void zpl_vec3_cross(zpl_vec3 *d, zpl_vec3 v0, zpl_vec3 v1) {
            d->x = v0.y * v1.z - v0.z * v1.y;
            d->y = v0.z * v1.x - v0.x * v1.z;
            d->z = v0.x * v1.y - v0.y * v1.x;
        }

        zpl_f32 zpl_vec2_mag2(zpl_vec2 v) { return zpl_vec2_dot(v, v); }
        zpl_f32 zpl_vec3_mag2(zpl_vec3 v) { return zpl_vec3_dot(v, v); }
        zpl_f32 zpl_vec4_mag2(zpl_vec4 v) { return zpl_vec4_dot(v, v); }

        /* TODO: Create custom sqrt function */
        zpl_f32 zpl_vec2_mag(zpl_vec2 v) { return zpl_sqrt(zpl_vec2_dot(v, v)); }
        zpl_f32 zpl_vec3_mag(zpl_vec3 v) { return zpl_sqrt(zpl_vec3_dot(v, v)); }
        zpl_f32 zpl_vec4_mag(zpl_vec4 v) { return zpl_sqrt(zpl_vec4_dot(v, v)); }

        void zpl_vec2_norm(zpl_vec2 *d, zpl_vec2 v) {
            zpl_f32 inv_mag = zpl_rsqrt(zpl_vec2_dot(v, v));
            zpl_vec2_mul(d, v, inv_mag);
        }
        void zpl_vec3_norm(zpl_vec3 *d, zpl_vec3 v) {
            zpl_f32 mag = zpl_vec3_mag(v);
            zpl_vec3_div(d, v, mag);
        }
        void zpl_vec4_norm(zpl_vec4 *d, zpl_vec4 v) {
            zpl_f32 mag = zpl_vec4_mag(v);
            zpl_vec4_div(d, v, mag);
        }

        void zpl_vec2_norm0(zpl_vec2 *d, zpl_vec2 v) {
            zpl_f32 mag = zpl_vec2_mag(v);
            if (mag > 0)
                zpl_vec2_div(d, v, mag);
            else
                *d = zpl_vec2f_zero( );
        }
        void zpl_vec3_norm0(zpl_vec3 *d, zpl_vec3 v) {
            zpl_f32 mag = zpl_vec3_mag(v);
            if (mag > 0)
                zpl_vec3_div(d, v, mag);
            else
                *d = zpl_vec3f_zero( );
        }
        void zpl_vec4_norm0(zpl_vec4 *d, zpl_vec4 v) {
            zpl_f32 mag = zpl_vec4_mag(v);
            if (mag > 0)
                zpl_vec4_div(d, v, mag);
            else
                *d = zpl_vec4f_zero( );
        }

        void zpl_vec2_reflect(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n) {
            zpl_vec2 b = n;
            zpl_vec2_muleq(&b, 2.0f * zpl_vec2_dot(n, i));
            zpl_vec2_sub(d, i, b);
        }

        void zpl_vec3_reflect(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n) {
            zpl_vec3 b = n;
            zpl_vec3_muleq(&b, 2.0f * zpl_vec3_dot(n, i));
            zpl_vec3_sub(d, i, b);
        }

        void zpl_vec2_refract(zpl_vec2 *d, zpl_vec2 i, zpl_vec2 n, zpl_f32 eta) {
            zpl_vec2 a, b;
            zpl_f32 dv, k;

            dv = zpl_vec2_dot(n, i);
            k = 1.0f - eta * eta * (1.0f - dv * dv);
            zpl_vec2_mul(&a, i, eta);
            zpl_vec2_mul(&b, n, eta * dv * zpl_sqrt(k));
            zpl_vec2_sub(d, a, b);
            zpl_vec2_muleq(d, (float)(k >= 0.0f));
        }

        void zpl_vec3_refract(zpl_vec3 *d, zpl_vec3 i, zpl_vec3 n, zpl_f32 eta) {
            zpl_vec3 a, b;
            zpl_f32 dv, k;

            dv = zpl_vec3_dot(n, i);
            k = 1.0f - eta * eta * (1.0f - dv * dv);
            zpl_vec3_mul(&a, i, eta);
            zpl_vec3_mul(&b, n, eta * dv * zpl_sqrt(k));
            zpl_vec3_sub(d, a, b);
            zpl_vec3_muleq(d, (float)(k >= 0.0f));
        }

        zpl_f32 zpl_vec2_aspect_ratio(zpl_vec2 v) { return (v.y < 0.0001f) ? 0.0f : v.x / v.y; }

        void zpl_mat2_transpose(zpl_mat2 *m) { zpl_float22_transpose(zpl_float22_m(m)); }
        void zpl_mat2_identity(zpl_mat2 *m) { zpl_float22_identity(zpl_float22_m(m)); }
        void zpl_mat2_mul(zpl_mat2 *out, zpl_mat2 *m1, zpl_mat2 *m2) {
            zpl_float22_mul(zpl_float22_m(out), zpl_float22_m(m1), zpl_float22_m(m2));
        }

        void zpl_float22_identity(zpl_f32 m[2][2]) {
            m[0][0] = 1;
            m[0][1] = 0;
            m[1][0] = 0;
            m[1][1] = 1;
        }

        void zpl_mat2_copy(zpl_mat2* out, zpl_mat2* m) {
            zpl_memcopy(out, m, sizeof(zpl_mat3));
        }

        void zpl_mat2_mul_vec2(zpl_vec2 *out, zpl_mat2 *m, zpl_vec2 in) { zpl_float22_mul_vec2(out, zpl_float22_m(m), in); }

        zpl_mat2 *zpl_mat2_v(zpl_vec2 m[2])   { return (zpl_mat2 *)m; }
        zpl_mat2 *zpl_mat2_f(zpl_f32 m[2][2]) { return (zpl_mat2 *)m; }

        zpl_float2 *zpl_float22_m(zpl_mat2 *m)   { return (zpl_float2 *)m; }
        zpl_float2 *zpl_float22_v(zpl_vec2 m[2]) { return (zpl_float2 *)m; }
        zpl_float2 *zpl_float22_4(zpl_f32 m[4])  { return (zpl_float2 *)m; }

        void zpl_float22_transpose(zpl_f32 (*vec)[2]) {
            int i, j;
            for (j = 0; j < 2; j++) {
                for (i = j + 1; i < 2; i++) {
                    zpl_f32 t = vec[i][j];
                    vec[i][j] = vec[j][i];
                    vec[j][i] = t;
                }
            }
        }

        void zpl_float22_mul(zpl_f32 (*out)[2], zpl_f32 (*mat1)[2], zpl_f32 (*mat2)[2]) {
            int i, j;
            zpl_f32 temp1[2][2], temp2[2][2];
            if (mat1 == out) {
                zpl__memcpy_4byte(temp1, mat1, sizeof(temp1));
                mat1 = temp1;
            }
            if (mat2 == out) {
                zpl__memcpy_4byte(temp2, mat2, sizeof(temp2));
                mat2 = temp2;
            }
            for (j = 0; j < 2; j++) {
                for (i = 0; i < 2; i++) { out[j][i] = mat1[0][i] * mat2[j][0] + mat1[1][i] * mat2[j][1]; }
            }
        }

        void zpl_float22_mul_vec2(zpl_vec2 *out, zpl_f32 m[2][2], zpl_vec2 v) {
            out->x = m[0][0] * v.x + m[0][1] * v.y;
            out->y = m[1][0] * v.x + m[1][1] * v.y;
        }

        zpl_f32 zpl_mat2_determinate(zpl_mat2 *m) {
            zpl_float2 *e = zpl_float22_m(m);
            return e[0][0] * e[1][1] - e[1][0] * e[0][1];
        }

        void zpl_mat2_inverse(zpl_mat2 *out, zpl_mat2 *in) {
            zpl_float2 *o = zpl_float22_m(out);
            zpl_float2 *i = zpl_float22_m(in);

            zpl_f32 ood = 1.0f / zpl_mat2_determinate(in);

            o[0][0] = +i[1][1] * ood;
            o[0][1] = -i[0][1] * ood;
            o[1][0] = -i[1][0] * ood;
            o[1][1] = +i[0][0] * ood;
        }

        void zpl_mat3_transpose(zpl_mat3 *m) { zpl_float33_transpose(zpl_float33_m(m)); }
        void zpl_mat3_identity(zpl_mat3 *m)  { zpl_float33_identity(zpl_float33_m(m)); }

        void zpl_mat3_copy(zpl_mat3* out, zpl_mat3* m) {
            zpl_memcopy(out, m, sizeof(zpl_mat3));
        }

        void zpl_mat3_mul(zpl_mat3 *out, zpl_mat3 *m1, zpl_mat3 *m2) {
            zpl_float33_mul(zpl_float33_m(out), zpl_float33_m(m1), zpl_float33_m(m2));
        }

        void zpl_float33_identity(zpl_f32 m[3][3]) {
            m[0][0] = 1;
            m[0][1] = 0;
            m[0][2] = 0;
            m[1][0] = 0;
            m[1][1] = 1;
            m[1][2] = 0;
            m[2][0] = 0;
            m[2][1] = 0;
            m[2][2] = 1;
        }

        void zpl_mat3_mul_vec3(zpl_vec3 *out, zpl_mat3 *m, zpl_vec3 in) { zpl_float33_mul_vec3(out, zpl_float33_m(m), in); }

        zpl_mat3 *zpl_mat3_v(zpl_vec3 m[3])   { return (zpl_mat3 *)m; }
        zpl_mat3 *zpl_mat3_f(zpl_f32 m[3][3]) { return (zpl_mat3 *)m; }

        zpl_float3 *zpl_float33_m(zpl_mat3 *m)   { return (zpl_float3 *)m; }
        zpl_float3 *zpl_float33_v(zpl_vec3 m[3]) { return (zpl_float3 *)m; }
        zpl_float3 *zpl_float33_9(zpl_f32 m[9])  { return (zpl_float3 *)m; }

        void zpl_float33_transpose(zpl_f32 (*vec)[3]) {
            int i, j;
            for (j = 0; j < 3; j++) {
                for (i = j + 1; i < 3; i++) {
                    zpl_f32 t = vec[i][j];
                    vec[i][j] = vec[j][i];
                    vec[j][i] = t;
                }
            }
        }

        void zpl_float33_mul(zpl_f32 (*out)[3], zpl_f32 (*mat1)[3], zpl_f32 (*mat2)[3]) {
            int i, j;
            zpl_f32 temp1[3][3], temp2[3][3];
            if (mat1 == out) {
                zpl__memcpy_4byte(temp1, mat1, sizeof(temp1));
                mat1 = temp1;
            }
            if (mat2 == out) {
                zpl__memcpy_4byte(temp2, mat2, sizeof(temp2));
                mat2 = temp2;
            }
            for (j = 0; j < 3; j++) {
                for (i = 0; i < 3; i++) {
                    out[j][i] = mat1[0][i] * mat2[j][0] + mat1[1][i] * mat2[j][1] + mat1[2][i] * mat2[j][2];
                }
            }
        }

        void zpl_float33_mul_vec3(zpl_vec3 *out, zpl_f32 m[3][3], zpl_vec3 v) {
            out->x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
            out->y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
            out->z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
        }

        zpl_f32 zpl_mat3_determinate(zpl_mat3 *m) {
            zpl_float3 *e = zpl_float33_m(m);
            zpl_f32 d =
                +e[0][0] * (e[1][1] * e[2][2] - e[1][2] * e[2][1])
                -e[0][1] * (e[1][0] * e[2][2] - e[1][2] * e[2][0])
                +e[0][2] * (e[1][0] * e[2][1] - e[1][1] * e[2][0]);
            return d;
        }

        void zpl_mat3_inverse(zpl_mat3 *out, zpl_mat3 *in) {
            zpl_float3 *o = zpl_float33_m(out);
            zpl_float3 *i = zpl_float33_m(in);

            zpl_f32 ood = 1.0f / zpl_mat3_determinate(in);

            o[0][0] = +(i[1][1] * i[2][2] - i[2][1] * i[1][2]) * ood;
            o[0][1] = -(i[1][0] * i[2][2] - i[2][0] * i[1][2]) * ood;
            o[0][2] = +(i[1][0] * i[2][1] - i[2][0] * i[1][1]) * ood;
            o[1][0] = -(i[0][1] * i[2][2] - i[2][1] * i[0][2]) * ood;
            o[1][1] = +(i[0][0] * i[2][2] - i[2][0] * i[0][2]) * ood;
            o[1][2] = -(i[0][0] * i[2][1] - i[2][0] * i[0][1]) * ood;
            o[2][0] = +(i[0][1] * i[1][2] - i[1][1] * i[0][2]) * ood;
            o[2][1] = -(i[0][0] * i[1][2] - i[1][0] * i[0][2]) * ood;
            o[2][2] = +(i[0][0] * i[1][1] - i[1][0] * i[0][1]) * ood;
        }

        void zpl_mat4_transpose(zpl_mat4 *m) { zpl_float44_transpose(zpl_float44_m(m)); }
        void zpl_mat4_identity(zpl_mat4 *m)  { zpl_float44_identity(zpl_float44_m(m)); }

        void zpl_mat4_copy(zpl_mat4* out, zpl_mat4* m) {
            zpl_memcopy(out, m, sizeof(zpl_mat4));
        }


        void zpl_mat4_mul(zpl_mat4 *out, zpl_mat4 *m1, zpl_mat4 *m2) {
            zpl_float44_mul(zpl_float44_m(out), zpl_float44_m(m1), zpl_float44_m(m2));
        }

        void zpl_float44_identity(zpl_f32 m[4][4]) {
            m[0][0] = 1;
            m[0][1] = 0;
            m[0][2] = 0;
            m[0][3] = 0;
            m[1][0] = 0;
            m[1][1] = 1;
            m[1][2] = 0;
            m[1][3] = 0;
            m[2][0] = 0;
            m[2][1] = 0;
            m[2][2] = 1;
            m[2][3] = 0;
            m[3][0] = 0;
            m[3][1] = 0;
            m[3][2] = 0;
            m[3][3] = 1;
        }

        void zpl_mat4_mul_vec4(zpl_vec4 *out, zpl_mat4 *m, zpl_vec4 in) { zpl_float44_mul_vec4(out, zpl_float44_m(m), in); }

        zpl_mat4 *zpl_mat4_v(zpl_vec4 m[4])   { return (zpl_mat4 *)m; }
        zpl_mat4 *zpl_mat4_f(zpl_f32 m[4][4]) { return (zpl_mat4 *)m; }

        zpl_float4 *zpl_float44_m(zpl_mat4 *m)    { return (zpl_float4 *)m; }
        zpl_float4 *zpl_float44_v(zpl_vec4 m[4])  { return (zpl_float4 *)m; }
        zpl_float4 *zpl_float44_16(zpl_f32 m[16]) { return (zpl_float4 *)m; }

        void zpl_float44_transpose(zpl_f32 (*vec)[4]) {
            zpl_f32 tmp;
            tmp = vec[1][0];
            vec[1][0] = vec[0][1];
            vec[0][1] = tmp;
            tmp = vec[2][0];
            vec[2][0] = vec[0][2];
            vec[0][2] = tmp;
            tmp = vec[3][0];
            vec[3][0] = vec[0][3];
            vec[0][3] = tmp;
            tmp = vec[2][1];
            vec[2][1] = vec[1][2];
            vec[1][2] = tmp;
            tmp = vec[3][1];
            vec[3][1] = vec[1][3];
            vec[1][3] = tmp;
            tmp = vec[3][2];
            vec[3][2] = vec[2][3];
            vec[2][3] = tmp;
        }

        void zpl_float44_mul(zpl_f32 (*out)[4], zpl_f32 (*mat1)[4], zpl_f32 (*mat2)[4]) {
            int i, j;
            zpl_f32 temp1[4][4], temp2[4][4];
            if (mat1 == out) {
                zpl__memcpy_4byte(temp1, mat1, sizeof(temp1));
                mat1 = temp1;
            }
            if (mat2 == out) {
                zpl__memcpy_4byte(temp2, mat2, sizeof(temp2));
                mat2 = temp2;
            }
            for (j = 0; j < 4; j++) {
                for (i = 0; i < 4; i++) {
                    out[j][i] =
                        mat1[0][i] * mat2[j][0] + mat1[1][i] * mat2[j][1]
                       +mat1[2][i] * mat2[j][2] + mat1[3][i] * mat2[j][3];
                }
            }
        }

        void zpl_float44_mul_vec4(zpl_vec4 *out, zpl_f32 m[4][4], zpl_vec4 v) {
            out->x = m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z + m[3][0] * v.w;
            out->y = m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z + m[3][1] * v.w;
            out->z = m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z + m[3][2] * v.w;
            out->w = m[0][3] * v.x + m[1][3] * v.y + m[2][3] * v.z + m[3][3] * v.w;
        }

        void zpl_mat4_inverse(zpl_mat4 *out, zpl_mat4 *in) {
            zpl_float4 *o = zpl_float44_m(out);
            zpl_float4 *m = zpl_float44_m(in);

            zpl_f32 ood;

            zpl_f32 sf00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
            zpl_f32 sf01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
            zpl_f32 sf02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
            zpl_f32 sf03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
            zpl_f32 sf04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
            zpl_f32 sf05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
            zpl_f32 sf06 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
            zpl_f32 sf07 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
            zpl_f32 sf08 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
            zpl_f32 sf09 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
            zpl_f32 sf10 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
            zpl_f32 sf11 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
            zpl_f32 sf12 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
            zpl_f32 sf13 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
            zpl_f32 sf14 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
            zpl_f32 sf15 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
            zpl_f32 sf16 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
            zpl_f32 sf17 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
            zpl_f32 sf18 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

            o[0][0] = +(m[1][1] * sf00 - m[1][2] * sf01 + m[1][3] * sf02);
            o[1][0] = -(m[1][0] * sf00 - m[1][2] * sf03 + m[1][3] * sf04);
            o[2][0] = +(m[1][0] * sf01 - m[1][1] * sf03 + m[1][3] * sf05);
            o[3][0] = -(m[1][0] * sf02 - m[1][1] * sf04 + m[1][2] * sf05);

            o[0][1] = -(m[0][1] * sf00 - m[0][2] * sf01 + m[0][3] * sf02);
            o[1][1] = +(m[0][0] * sf00 - m[0][2] * sf03 + m[0][3] * sf04);
            o[2][1] = -(m[0][0] * sf01 - m[0][1] * sf03 + m[0][3] * sf05);
            o[3][1] = +(m[0][0] * sf02 - m[0][1] * sf04 + m[0][2] * sf05);

            o[0][2] = +(m[0][1] * sf06 - m[0][2] * sf07 + m[0][3] * sf08);
            o[1][2] = -(m[0][0] * sf06 - m[0][2] * sf09 + m[0][3] * sf10);
            o[2][2] = +(m[0][0] * sf11 - m[0][1] * sf09 + m[0][3] * sf12);
            o[3][2] = -(m[0][0] * sf08 - m[0][1] * sf10 + m[0][2] * sf12);

            o[0][3] = -(m[0][1] * sf13 - m[0][2] * sf14 + m[0][3] * sf15);
            o[1][3] = +(m[0][0] * sf13 - m[0][2] * sf16 + m[0][3] * sf17);
            o[2][3] = -(m[0][0] * sf14 - m[0][1] * sf16 + m[0][3] * sf18);
            o[3][3] = +(m[0][0] * sf15 - m[0][1] * sf17 + m[0][2] * sf18);

            ood = 1.0f / (m[0][0] * o[0][0] + m[0][1] * o[1][0] + m[0][2] * o[2][0] + m[0][3] * o[3][0]);

            o[0][0] *= ood; o[1][0] *= ood; o[2][0] *= ood; o[3][0] *= ood;
            o[0][1] *= ood; o[1][1] *= ood; o[2][1] *= ood; o[3][1] *= ood;
            o[0][2] *= ood; o[1][2] *= ood; o[2][2] *= ood; o[3][2] *= ood;
            o[0][3] *= ood; o[1][3] *= ood; o[2][3] *= ood; o[3][3] *= ood;
        }

        void zpl_mat4_translate(zpl_mat4 *out, zpl_vec3 v) {
            zpl_mat4_identity(out);
            out->col[3].xyz = v;
            out->col[3].w = 1;
        }

        void zpl_mat4_rotate(zpl_mat4 *out, zpl_vec3 v, zpl_f32 angle_radians) {
            zpl_f32 c, s;
            zpl_vec3 axis, t;
            zpl_float4 *rot;

            c = zpl_cos(angle_radians);
            s = zpl_sin(angle_radians);

            zpl_vec3_norm(&axis, v);
            zpl_vec3_mul(&t, axis, 1.0f - c);

            zpl_mat4_identity(out);
            rot = zpl_float44_m(out);

            rot[0][0] = c + t.x * axis.x;
            rot[0][1] = 0 + t.x * axis.y + s * axis.z;
            rot[0][2] = 0 + t.x * axis.z - s * axis.y;
            rot[0][3] = 0;

            rot[1][0] = 0 + t.y * axis.x - s * axis.z;
            rot[1][1] = c + t.y * axis.y;
            rot[1][2] = 0 + t.y * axis.z + s * axis.x;
            rot[1][3] = 0;

            rot[2][0] = 0 + t.z * axis.x + s * axis.y;
            rot[2][1] = 0 + t.z * axis.y - s * axis.x;
            rot[2][2] = c + t.z * axis.z;
            rot[2][3] = 0;
        }

        void zpl_mat4_scale(zpl_mat4 *out, zpl_vec3 v) {
            zpl_mat4_identity(out);
            out->e[0]  = v.x;
            out->e[5]  = v.y;
            out->e[10] = v.z;
        }

        void zpl_mat4_scalef(zpl_mat4 *out, zpl_f32 s) {
            zpl_mat4_identity(out);
            out->e[0]  = s;
            out->e[5]  = s;
            out->e[10] = s;
        }

        void zpl_mat4_ortho2d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top) {
            zpl_float4 *m;
            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = 2.0f / (right - left);
            m[1][1] = 2.0f / (top - bottom);
            m[2][2] = -1.0f;
            m[3][0] = -(right + left) / (right - left);
            m[3][1] = -(top + bottom) / (top - bottom);
        }

        void zpl_mat4_ortho3d(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top, zpl_f32 z_near, zpl_f32 z_far) {
            zpl_float4 *m;
            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = +2.0f / (right - left);
            m[1][1] = +2.0f / (top - bottom);
            m[2][2] = -2.0f / (z_far - z_near);
            m[3][0] = -(right + left) / (right - left);
            m[3][1] = -(top + bottom) / (top - bottom);
            m[3][2] = -(z_far + z_near) / (z_far - z_near);
        }

        void zpl_mat4_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near, zpl_f32 z_far) {
            zpl_f32 tan_half_fovy = zpl_tan(0.5f * fovy);
            zpl_mat4 zero_mat = { 0 };
            zpl_float4 *m = zpl_float44_m(out);
            *out = zero_mat;

            m[0][0] = 1.0f / (aspect * tan_half_fovy);
            m[1][1] = 1.0f / (tan_half_fovy);
            m[2][2] = -(z_far + z_near) / (z_far - z_near);
            m[2][3] = -1.0f;
            m[3][2] = -2.0f * z_far * z_near / (z_far - z_near);
        }

        void zpl_mat4_infinite_perspective(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near) {
            zpl_f32 range = zpl_tan(0.5f * fovy) * z_near;
            zpl_f32 left = -range * aspect;
            zpl_f32 right = range * aspect;
            zpl_f32 bottom = -range;
            zpl_f32 top = range;
            zpl_mat4 zero_mat = { 0 };
            zpl_float4 *m = zpl_float44_m(out);
            *out = zero_mat;

            m[0][0] = (2.0f * z_near) / (right - left);
            m[1][1] = (2.0f * z_near) / (top - bottom);
            m[2][2] = -1.0f;
            m[2][3] = -1.0f;
            m[3][2] = -2.0f * z_near;
        }

        void zpl_mat4_ortho2d_dx(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top) {
            zpl_float4 *m;
            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = 2.0f / (right - left);
            m[1][1] = 2.0f / (top - bottom);
            m[2][2] = -1.0f;
            m[3][0] = -(right + left) / (right - left);
            m[3][1] = -(top + bottom) / (top - bottom);
        }

        void zpl_mat4_ortho3d_dx(zpl_mat4 *out, zpl_f32 left, zpl_f32 right, zpl_f32 bottom, zpl_f32 top, zpl_f32 z_near, zpl_f32 z_far) {
            zpl_float4 *m;
            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = +2.0f / (right - left);
            m[1][1] = +2.0f / (top - bottom);
            m[2][2] = -1.0f / (z_far - z_near);
            m[3][0] = -(right + left) / (right - left);
            m[3][1] = -(top + bottom) / (top - bottom);
            m[3][2] = -( z_near) / (z_far - z_near);
        }

        void zpl_mat4_perspective_dx(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near, zpl_f32 z_far) {
            zpl_f32 tan_half_fovy = zpl_tan(0.5f * fovy);
            zpl_mat4 zero_mat = { 0 };
            zpl_float4 *m = zpl_float44_m(out);
            *out = zero_mat;

            m[0][0] = 1.0f / (aspect * tan_half_fovy);
            m[1][1] = 1.0f / (tan_half_fovy);
            m[2][2] = -(z_far ) / (z_far - z_near);
            m[2][3] = -1.0f;
            m[3][2] = - z_near / (z_far - z_near);
        }

        void zpl_mat4_infinite_perspective_dx(zpl_mat4 *out, zpl_f32 fovy, zpl_f32 aspect, zpl_f32 z_near) {
             zpl_f32 tan_half_fovy = zpl_tan(0.5f * fovy);
            zpl_mat4 zero_mat = { 0 };
            zpl_float4 *m = zpl_float44_m(out);
            *out = zero_mat;

            m[0][0] = 1.0f / (aspect * tan_half_fovy);
            m[1][1] = 1.0f / (tan_half_fovy);
            m[2][2] = -1.0f;
            m[2][3] = -1.0f;
            m[3][2] = - z_near;
        }



        void zpl_mat4_look_at(zpl_mat4 *out, zpl_vec3 eye, zpl_vec3 centre, zpl_vec3 up) {
            zpl_vec3 f, s, u;
            zpl_float4 *m;

            zpl_vec3_sub(&f, centre, eye);
            zpl_vec3_norm(&f, f);

            zpl_vec3_cross(&s, f, up);
            zpl_vec3_norm(&s, s);

            zpl_vec3_cross(&u, s, f);

            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = +s.x;
            m[1][0] = +s.y;
            m[2][0] = +s.z;

            m[0][1] = +u.x;
            m[1][1] = +u.y;
            m[2][1] = +u.z;

            m[0][2] = -f.x;
            m[1][2] = -f.y;
            m[2][2] = -f.z;

            m[3][0] = -zpl_vec3_dot(s, eye);
            m[3][1] = -zpl_vec3_dot(u, eye);
            m[3][2] = +zpl_vec3_dot(f, eye);
        }

        void zpl_mat4_look_at_lh(zpl_mat4 *out, zpl_vec3 eye, zpl_vec3 centre, zpl_vec3 up) {
            zpl_vec3 f, s, u;
            zpl_float4 *m;

            zpl_vec3_sub(&f, centre, eye);
            zpl_vec3_norm(&f, f);

            zpl_vec3_cross(&s, up, f);
            zpl_vec3_norm(&s, s);

            zpl_vec3_cross(&u, f, s);

            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = +s.x;
            m[1][0] = +s.y;
            m[2][0] = +s.z;

            m[0][1] = +u.x;
            m[1][1] = +u.y;
            m[2][1] = +u.z;

            m[0][2] = +f.x;
            m[1][2] = +f.y;
            m[2][2] = +f.z;

            m[3][0] = -zpl_vec3_dot(s, eye);
            m[3][1] = -zpl_vec3_dot(u, eye);
            m[3][2] = -zpl_vec3_dot(f, eye);
        }

        zpl_quat zpl_quatf(zpl_f32 x, zpl_f32 y, zpl_f32 z, zpl_f32 w) {
            zpl_quat q;
            q.x = x;
            q.y = y;
            q.z = z;
            q.w = w;
            return q;
        }
        zpl_quat zpl_quatfv(zpl_f32 e[4]) {
            zpl_quat q;
            q.x = e[0];
            q.y = e[1];
            q.z = e[2];
            q.w = e[3];
            return q;
        }

        zpl_quat zpl_quat_axis_angle(zpl_vec3 axis, zpl_f32 angle_radians) {
            zpl_quat q;
            zpl_vec3_norm(&q.xyz, axis);
            zpl_vec3_muleq(&q.xyz, zpl_sin(0.5f * angle_radians));
            q.w = zpl_cos(0.5f * angle_radians);
            return q;
        }

        zpl_quat zpl_quat_euler_angles(zpl_f32 pitch, zpl_f32 yaw, zpl_f32 roll) {
            /* TODO: Do without multiplication, i.e. make it faster */
            zpl_quat q, p, y, r;
            p = zpl_quat_axis_angle(zpl_vec3f(1, 0, 0), pitch);
            y = zpl_quat_axis_angle(zpl_vec3f(0, 1, 0), yaw);
            r = zpl_quat_axis_angle(zpl_vec3f(0, 0, 1), roll);

            zpl_quat_mul(&q, y, p);
            zpl_quat_muleq(&q, r);

            return q;
        }

        zpl_quat zpl_quat_identity(void) {
            zpl_quat q = { 0, 0, 0, 1 };
            return q;
        }

        void zpl_quat_add(zpl_quat *d, zpl_quat q0, zpl_quat q1) { zpl_vec4_add(&d->xyzw, q0.xyzw, q1.xyzw); }
        void zpl_quat_sub(zpl_quat *d, zpl_quat q0, zpl_quat q1) { zpl_vec4_sub(&d->xyzw, q0.xyzw, q1.xyzw); }

        void zpl_quat_mul(zpl_quat *d, zpl_quat q0, zpl_quat q1) {
            d->x = q0.w * q1.x + q0.x * q1.w + q0.y * q1.z - q0.z * q1.y;
            d->y = q0.w * q1.y - q0.x * q1.z + q0.y * q1.w + q0.z * q1.x;
            d->z = q0.w * q1.z + q0.x * q1.y - q0.y * q1.x + q0.z * q1.w;
            d->w = q0.w * q1.w - q0.x * q1.x - q0.y * q1.y - q0.z * q1.z;
        }

        void zpl_quat_div(zpl_quat *d, zpl_quat q0, zpl_quat q1) {
            zpl_quat iq1;
            zpl_quat_inverse(&iq1, q1);
            zpl_quat_mul(d, q0, iq1);
        }

        void zpl_quat_mulf(zpl_quat *d, zpl_quat q0, zpl_f32 s) { zpl_vec4_mul(&d->xyzw, q0.xyzw, s); }
        void zpl_quat_divf(zpl_quat *d, zpl_quat q0, zpl_f32 s) { zpl_vec4_div(&d->xyzw, q0.xyzw, s); }

        void zpl_quat_addeq(zpl_quat *d, zpl_quat q) { zpl_vec4_addeq(&d->xyzw, q.xyzw); }
        void zpl_quat_subeq(zpl_quat *d, zpl_quat q) { zpl_vec4_subeq(&d->xyzw, q.xyzw); }
        void zpl_quat_muleq(zpl_quat *d, zpl_quat q) { zpl_quat_mul(d, *d, q); }
        void zpl_quat_diveq(zpl_quat *d, zpl_quat q) { zpl_quat_div(d, *d, q); }

        void zpl_quat_muleqf(zpl_quat *d, zpl_f32 s) { zpl_vec4_muleq(&d->xyzw, s); }
        void zpl_quat_diveqf(zpl_quat *d, zpl_f32 s) { zpl_vec4_diveq(&d->xyzw, s); }

        zpl_f32 zpl_quat_dot(zpl_quat q0, zpl_quat q1) {
            zpl_f32 r = zpl_vec3_dot(q0.xyz, q1.xyz) + q0.w * q1.w;
            return r;
        }
        zpl_f32 zpl_quat_mag(zpl_quat q) {
            zpl_f32 r = zpl_sqrt(zpl_quat_dot(q, q));
            return r;
        }

        void zpl_quat_norm(zpl_quat *d, zpl_quat q) { zpl_quat_divf(d, q, zpl_quat_mag(q)); }

        void zpl_quat_conj(zpl_quat *d, zpl_quat q) {
            d->xyz = zpl_vec3f(-q.x, -q.y, -q.z);
            d->w = q.w;
        }
        void zpl_quat_inverse(zpl_quat *d, zpl_quat q) {
            zpl_quat_conj(d, q);
            zpl_quat_diveqf(d, zpl_quat_dot(q, q));
        }

        void zpl_quat_axis(zpl_vec3 *axis, zpl_quat q) {
            zpl_quat n;
            zpl_quat_norm(&n, q);
            zpl_vec3_div(axis, n.xyz, zpl_sin(zpl_arccos(q.w)));
        }

        zpl_f32 zpl_quat_angle(zpl_quat q) {
            zpl_f32 mag   = zpl_quat_mag(q);
            zpl_f32 c     = q.w * (1.0f / mag);
            zpl_f32 angle = 2.0f * zpl_arccos(c);
            return angle;
        }

        zpl_f32 zpl_quat_roll(zpl_quat q) {
            return zpl_arctan2(2.0f * q.x * q.y + q.z * q.w, q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z);
        }
        zpl_f32 zpl_quat_pitch(zpl_quat q) {
            return zpl_arctan2(2.0f * q.y * q.z + q.w * q.x, q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z);
        }
        zpl_f32 zpl_quat_yaw(zpl_quat q) { return zpl_arcsin(-2.0f * (q.x * q.z - q.w * q.y)); }

        void zpl_quat_rotate_vec3(zpl_vec3 *d, zpl_quat q, zpl_vec3 v) {
            /* zpl_vec3 t = 2.0f * cross(q.xyz, v);
             * *d = q.w*t + v + cross(q.xyz, t);
             */
            zpl_vec3 t, p;
            zpl_vec3_cross(&t, q.xyz, v);
            zpl_vec3_muleq(&t, 2.0f);

            zpl_vec3_cross(&p, q.xyz, t);

            zpl_vec3_mul(d, t, q.w);
            zpl_vec3_addeq(d, v);
            zpl_vec3_addeq(d, p);
        }

        void zpl_mat4_from_quat(zpl_mat4 *out, zpl_quat q) {
            zpl_float4 *m;
            zpl_quat a;
            zpl_f32 xx, yy, zz, xy, xz, yz, wx, wy, wz;

            zpl_quat_norm(&a, q);
            xx = a.x * a.x;
            yy = a.y * a.y;
            zz = a.z * a.z;
            xy = a.x * a.y;
            xz = a.x * a.z;
            yz = a.y * a.z;
            wx = a.w * a.x;
            wy = a.w * a.y;
            wz = a.w * a.z;

            zpl_mat4_identity(out);
            m = zpl_float44_m(out);

            m[0][0] = 1.0f - 2.0f * (yy + zz);
            m[0][1] = 2.0f * (xy + wz);
            m[0][2] = 2.0f * (xz - wy);

            m[1][0] = 2.0f * (xy - wz);
            m[1][1] = 1.0f - 2.0f * (xx + zz);
            m[1][2] = 2.0f * (yz + wx);

            m[2][0] = 2.0f * (xz + wy);
            m[2][1] = 2.0f * (yz - wx);
            m[2][2] = 1.0f - 2.0f * (xx + yy);
        }

        void zpl_quat_from_mat4(zpl_quat *out, zpl_mat4 *mat) {
            zpl_float4 *m;
            zpl_f32 four_x_squared_minus_1, four_y_squared_minus_1, four_z_squared_minus_1, four_w_squared_minus_1,
            four_biggest_squared_minus_1;
            int biggest_index = 0;
            zpl_f32 biggest_value, mult;

            m = zpl_float44_m(mat);

            four_x_squared_minus_1 = m[0][0] - m[1][1] - m[2][2];
            four_y_squared_minus_1 = m[1][1] - m[0][0] - m[2][2];
            four_z_squared_minus_1 = m[2][2] - m[0][0] - m[1][1];
            four_w_squared_minus_1 = m[0][0] + m[1][1] + m[2][2];

            four_biggest_squared_minus_1 = four_w_squared_minus_1;
            if (four_x_squared_minus_1 > four_biggest_squared_minus_1) {
                four_biggest_squared_minus_1 = four_x_squared_minus_1;
                biggest_index = 1;
            }
            if (four_y_squared_minus_1 > four_biggest_squared_minus_1) {
                four_biggest_squared_minus_1 = four_y_squared_minus_1;
                biggest_index = 2;
            }
            if (four_z_squared_minus_1 > four_biggest_squared_minus_1) {
                four_biggest_squared_minus_1 = four_z_squared_minus_1;
                biggest_index = 3;
            }

            biggest_value = zpl_sqrt(four_biggest_squared_minus_1 + 1.0f) * 0.5f;
            mult = 0.25f / biggest_value;

            switch (biggest_index) {
                case 0:
                    out->w = biggest_value;
                    out->x = (m[1][2] - m[2][1]) * mult;
                    out->y = (m[2][0] - m[0][2]) * mult;
                    out->z = (m[0][1] - m[1][0]) * mult;
                    break;
                case 1:
                    out->w = (m[1][2] - m[2][1]) * mult;
                    out->x = biggest_value;
                    out->y = (m[0][1] + m[1][0]) * mult;
                    out->z = (m[2][0] + m[0][2]) * mult;
                    break;
                case 2:
                    out->w = (m[2][0] - m[0][2]) * mult;
                    out->x = (m[0][1] + m[1][0]) * mult;
                    out->y = biggest_value;
                    out->z = (m[1][2] + m[2][1]) * mult;
                    break;
                case 3:
                    out->w = (m[0][1] - m[1][0]) * mult;
                    out->x = (m[2][0] + m[0][2]) * mult;
                    out->y = (m[1][2] + m[2][1]) * mult;
                    out->z = biggest_value;
                    break;
            }
        }

        zpl_f32 zpl_plane_distance(zpl_plane* p, zpl_vec3 v) {
            return (p->a * v.x + p->b * v.y + p->c * v.z + p->d);
        }

        void zpl_frustum_create(zpl_frustum* out, zpl_mat4* camera, zpl_mat4* proj) {
            zpl_mat4 pv;

            zpl_mat4_mul(&pv, camera, proj);

            register zpl_plane* fp = 0;
            zpl_f32 rmag;

            fp = &out->x1;
            fp->a = pv.x.w + pv.x.x;
            fp->b = pv.y.w + pv.x.y;
            fp->c = pv.z.w + pv.x.z;
            fp->d = pv.w.w + pv.x.w;

            rmag = zpl_rsqrt(zpl_square(fp->a) + zpl_square(fp->b) + zpl_square(fp->c));

            fp->a *= rmag;
            fp->b *= rmag;
            fp->c *= rmag;
            fp->d *= rmag;

            fp = &out->x2;

            fp->a = pv.x.w - pv.x.x;
            fp->b = pv.y.w - pv.x.y;
            fp->c = pv.z.w - pv.x.z;
            fp->d = pv.w.w - pv.x.w;

            rmag = zpl_rsqrt(zpl_square(fp->a) + zpl_square(fp->b) + zpl_square(fp->c));

            fp->a *= rmag;
            fp->b *= rmag;
            fp->c *= rmag;
            fp->d *= rmag;

            fp = &out->y1;

            fp->a = pv.x.w - pv.y.x;
            fp->b = pv.y.w - pv.y.y;
            fp->c = pv.z.w - pv.y.w;
            fp->d = pv.w.w - pv.y.z;

            rmag = zpl_rsqrt(zpl_square(fp->a) + zpl_square(fp->b) + zpl_square(fp->c));

            fp->a *= rmag;
            fp->b *= rmag;
            fp->c *= rmag;
            fp->d *= rmag;

            fp = &out->y2;

            fp->a = pv.x.w + pv.y.x;
            fp->b = pv.y.w + pv.y.y;
            fp->c = pv.z.w + pv.y.z;
            fp->d = pv.w.w + pv.y.w;

            rmag = zpl_rsqrt(zpl_square(fp->a) + zpl_square(fp->b) + zpl_square(fp->c));

            fp->a *= rmag;
            fp->b *= rmag;
            fp->c *= rmag;
            fp->d *= rmag;;

            fp = &out->z1;

            fp->a = pv.x.w + pv.z.x;
            fp->b = pv.y.w + pv.z.y;
            fp->c = pv.z.w + pv.z.z;
            fp->d = pv.w.w + pv.z.w;

            rmag = zpl_rsqrt(zpl_square(fp->a) + zpl_square(fp->b) + zpl_square(fp->c));

            fp->a *= rmag;
            fp->b *= rmag;
            fp->c *= rmag;
            fp->d *= rmag;

            fp = &out->z2;

            fp->a = pv.x.w - pv.z.x;
            fp->b = pv.y.w - pv.z.y;
            fp->c = pv.z.w - pv.z.z;
            fp->d = pv.w.w - pv.z.w;

            rmag = zpl_rsqrt(zpl_square(fp->a) + zpl_square(fp->b) + zpl_square(fp->c));

            fp->a *= rmag;
            fp->b *= rmag;
            fp->c *= rmag;
            fp->d *= rmag;
        }

        zpl_b8 zpl_frustum_sphere_inside(zpl_frustum* frustum, zpl_vec3 center, zpl_f32 radius) {
            if (zpl_plane_distance(&frustum->x1, center) <= -radius) return 0;
            if (zpl_plane_distance(&frustum->x2, center) <= -radius) return 0;
            if (zpl_plane_distance(&frustum->y1, center) <= -radius) return 0;
            if (zpl_plane_distance(&frustum->y2, center) <= -radius) return 0;
            if (zpl_plane_distance(&frustum->z1, center) <= -radius) return 0;
            if (zpl_plane_distance(&frustum->z2, center) <= -radius) return 0;

            return 1;
        }

        zpl_b8 zpl_frustum_point_inside(zpl_frustum* frustum, zpl_vec3 point) {
            return zpl_frustum_sphere_inside(frustum, point, 0.0f);
        }

        zpl_b8 zpl_frustum_box_inside(zpl_frustum* frustum, zpl_aabb3 aabb) {
            
            zpl_vec3 box = aabb.half_size;
            zpl_vec3 v, b;

            b = zpl_vec3f(-box.x, -box.y, -box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(+box.x, -box.y, -box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(-box.x, +box.y, -box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(+box.x, +box.y, -box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(+box.x, +box.y, +box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(-box.x, +box.y, +box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(-box.x, -box.y, +box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            b = zpl_vec3f(+box.x, -box.y, +box.z);
            zpl_vec3_add(&v, b, aabb.centre);

            if (zpl_frustum_point_inside(frustum, v)) return 1;

            return 0;
        }

        zpl_f32 zpl_lerp(zpl_f32 a, zpl_f32 b, zpl_f32 t) { return a * (1.0f - t) + b * t; }
        zpl_f32 zpl_unlerp(zpl_f32 t, zpl_f32 a, zpl_f32 b) { return (t - a) / (b - a); }
        zpl_f32 zpl_smooth_step(zpl_f32 a, zpl_f32 b, zpl_f32 t) {
            zpl_f32 x = (t - a) / (b - a);
            return x * x * (3.0f - 2.0f * x);
        }
        zpl_f32 zpl_smoother_step(zpl_f32 a, zpl_f32 b, zpl_f32 t) {
            zpl_f32 x = (t - a) / (b - a);
            return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
        }

        #define ZPL_VEC_LERPN(N, d, a, b, t)     \
            zpl_vec##N db;                       \
            zpl_vec##N##_sub(&db, b, a);         \
            zpl_vec##N##_muleq(&db, t);          \
            zpl_vec##N##_add(d, a, db)

        void zpl_vec2_lerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 b, zpl_f32 t) { ZPL_VEC_LERPN(2, d, a, b, t); }
        void zpl_vec3_lerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 b, zpl_f32 t) { ZPL_VEC_LERPN(3, d, a, b, t); }
        void zpl_vec4_lerp(zpl_vec4 *d, zpl_vec4 a, zpl_vec4 b, zpl_f32 t) { ZPL_VEC_LERPN(4, d, a, b, t); }

        #undef ZPL_VEC_LERPN

        void zpl_vec2_cslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t) {
            zpl_f32 t2 = t * t;
            zpl_f32 ti = (t - 1);
            zpl_f32 ti2 = ti * ti;

            zpl_f32 h00 = (1 + 2 * t) * ti2;
            zpl_f32 h10 = t * ti2;
            zpl_f32 h01 = t2 * (3 - 2 * t);
            zpl_f32 h11 = t2 * ti;

            d->x = h00 * a.x + h10 * v0.x + h01 * b.x + h11 * v1.x;
            d->y = h00 * a.y + h10 * v0.y + h01 * b.y + h11 * v1.y;
        }

        void zpl_vec3_cslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t) {
            zpl_f32 t2 = t * t;
            zpl_f32 ti = (t - 1);
            zpl_f32 ti2 = ti * ti;

            zpl_f32 h00 = (1 + 2 * t) * ti2;
            zpl_f32 h10 = t * ti2;
            zpl_f32 h01 = t2 * (3 - 2 * t);
            zpl_f32 h11 = t2 * ti;

            d->x = h00 * a.x + h10 * v0.x + h01 * b.x + h11 * v1.x;
            d->y = h00 * a.y + h10 * v0.y + h01 * b.y + h11 * v1.y;
            d->z = h00 * a.z + h10 * v0.z + h01 * b.z + h11 * v1.z;
        }

        void zpl_vec2_dcslerp(zpl_vec2 *d, zpl_vec2 a, zpl_vec2 v0, zpl_vec2 b, zpl_vec2 v1, zpl_f32 t) {
            zpl_f32 t2 = t * t;

            zpl_f32 dh00 = 6 * t2 - 6 * t;
            zpl_f32 dh10 = 3 * t2 - 4 * t + 1;
            zpl_f32 dh01 = -6 * t2 + 6 * t;
            zpl_f32 dh11 = 3 * t2 - 2 * t;

            d->x = dh00 * a.x + dh10 * v0.x + dh01 * b.x + dh11 * v1.x;
            d->y = dh00 * a.y + dh10 * v0.y + dh01 * b.y + dh11 * v1.y;
        }

        void zpl_vec3_dcslerp(zpl_vec3 *d, zpl_vec3 a, zpl_vec3 v0, zpl_vec3 b, zpl_vec3 v1, zpl_f32 t) {
            zpl_f32 t2 = t * t;

            zpl_f32 dh00 = 6 * t2 - 6 * t;
            zpl_f32 dh10 = 3 * t2 - 4 * t + 1;
            zpl_f32 dh01 = -6 * t2 + 6 * t;
            zpl_f32 dh11 = 3 * t2 - 2 * t;

            d->x = dh00 * a.x + dh10 * v0.x + dh01 * b.x + dh11 * v1.x;
            d->y = dh00 * a.y + dh10 * v0.y + dh01 * b.y + dh11 * v1.y;
            d->z = dh00 * a.z + dh10 * v0.z + dh01 * b.z + dh11 * v1.z;
        }

        void zpl_quat_lerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) { zpl_vec4_lerp(&d->xyzw, a.xyzw, b.xyzw, t); }
        void zpl_quat_nlerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) {
            zpl_quat_lerp(d, a, b, t);
            zpl_quat_norm(d, *d);
        }

        void zpl_quat_slerp(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) {
            zpl_quat x, y, z;
            zpl_f32 cos_theta, angle;
            zpl_f32 s1, s0, is;

            z = b;
            cos_theta = zpl_quat_dot(a, b);

            if (cos_theta < 0.0f) {
                z = zpl_quatf(-b.x, -b.y, -b.z, -b.w);
                cos_theta = -cos_theta;
            }

            if (cos_theta > 1.0f) {
                /* NOTE: Use lerp not nlerp as it's not a real angle or they are not normalized */
                zpl_quat_lerp(d, a, b, t);
            }

            angle = zpl_arccos(cos_theta);

            s1 = zpl_sin((1.0f - t) * angle);
            s0 = zpl_sin(t * angle);
            is = 1.0f / zpl_sin(angle);
            zpl_quat_mulf(&x, a, s1);
            zpl_quat_mulf(&y, z, s0);
            zpl_quat_add(d, x, y);
            zpl_quat_muleqf(d, is);
        }

        void zpl_quat_slerp_approx(zpl_quat *d, zpl_quat a, zpl_quat b, zpl_f32 t) {
            /* NOTE: Derived by taylor expanding the geometric interpolation equation
             *             Even works okay for nearly anti-parallel versors!!!
             */
            /* NOTE: Extra interations cannot be used as they require angle^4 which is not worth it to approximate */
            zpl_f32 tp = t + (1.0f - zpl_quat_dot(a, b)) / 3.0f * t * (-2.0f * t * t + 3.0f * t - 1.0f);
            zpl_quat_nlerp(d, a, b, tp);
        }

        void zpl_quat_nquad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t) {
            zpl_quat x, y;
            zpl_quat_nlerp(&x, p, q, t);
            zpl_quat_nlerp(&y, a, b, t);
            zpl_quat_nlerp(d, x, y, 2.0f * t * (1.0f - t));
        }

        void zpl_quat_squad(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t) {
            zpl_quat x, y;
            zpl_quat_slerp(&x, p, q, t);
            zpl_quat_slerp(&y, a, b, t);
            zpl_quat_slerp(d, x, y, 2.0f * t * (1.0f - t));
        }

        void zpl_quat_squad_approx(zpl_quat *d, zpl_quat p, zpl_quat a, zpl_quat b, zpl_quat q, zpl_f32 t) {
            zpl_quat x, y;
            zpl_quat_slerp_approx(&x, p, q, t);
            zpl_quat_slerp_approx(&y, a, b, t);
            zpl_quat_slerp_approx(d, x, y, 2.0f * t * (1.0f - t));
        }

        zpl_rect2 zpl_rect2f(zpl_vec2 pos, zpl_vec2 dim) {
            zpl_rect2 r;
            r.pos = pos;
            r.dim = dim;
            return r;
        }

        zpl_rect3 zpl_rect3f(zpl_vec3 pos, zpl_vec3 dim) {
            zpl_rect3 r;
            r.pos = pos;
            r.dim = dim;
            return r;
        }

        int zpl_rect2_contains(zpl_rect2 a, zpl_f32 x, zpl_f32 y) {
            zpl_f32 min_x = zpl_min(a.pos.x, a.pos.x + a.dim.x);
            zpl_f32 max_x = zpl_max(a.pos.x, a.pos.x + a.dim.x);
            zpl_f32 min_y = zpl_min(a.pos.y, a.pos.y + a.dim.y);
            zpl_f32 max_y = zpl_max(a.pos.y, a.pos.y + a.dim.y);
            int result    =        (x >= min_x) & (x < max_x) & (y >= min_y) & (y < max_y);
            return result;
        }

        int zpl_rect2_contains_vec2(zpl_rect2 a, zpl_vec2 p) { return zpl_rect2_contains(a, p.x, p.y); }

        int zpl_rect2_intersects(zpl_rect2 a, zpl_rect2 b) {
            zpl_rect2 r = { 0 };
            return zpl_rect2_intersection_result(a, b, &r);
        }

        int zpl_rect2_intersection_result(zpl_rect2 a, zpl_rect2 b, zpl_rect2 *intersection) {
            zpl_f32 a_min_x = zpl_min(a.pos.x, a.pos.x + a.dim.x);
            zpl_f32 a_max_x = zpl_max(a.pos.x, a.pos.x + a.dim.x);
            zpl_f32 a_min_y = zpl_min(a.pos.y, a.pos.y + a.dim.y);
            zpl_f32 a_max_y = zpl_max(a.pos.y, a.pos.y + a.dim.y);

            zpl_f32 b_min_x = zpl_min(b.pos.x, b.pos.x + b.dim.x);
            zpl_f32 b_max_x = zpl_max(b.pos.x, b.pos.x + b.dim.x);
            zpl_f32 b_min_y = zpl_min(b.pos.y, b.pos.y + b.dim.y);
            zpl_f32 b_max_y = zpl_max(b.pos.y, b.pos.y + b.dim.y);

            zpl_f32 x0 = zpl_max(a_min_x, b_min_x);
            zpl_f32 y0 = zpl_max(a_min_y, b_min_y);
            zpl_f32 x1 = zpl_min(a_max_x, b_max_x);
            zpl_f32 y1 = zpl_min(a_max_y, b_max_y);

            if ((x0 < x1) && (y0 < y1)) {
                zpl_rect2 r = zpl_rect2f(zpl_vec2f(x0, y0), zpl_vec2f(x1 - x0, y1 - y0));
                *intersection = r;
                return 1;
            } else {
                zpl_rect2 r = { 0 };
                *intersection = r;
                return 0;
            }
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_JSON)
        // file: source/json.c

        ////////////////////////////////////////////////////////////////
        //
        // JSON5 Parser
        //
        //

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #include <math.h> /* needed for INFINITY and NAN */

        ZPL_BEGIN_C_DECLS

        static ZPL_ALWAYS_INLINE zpl_b32 zpl__json_is_special_char(char c) { return !!zpl_strchr("<>:/", c); }
        static ZPL_ALWAYS_INLINE zpl_b32 zpl__json_is_assign_char(char c) { return !!zpl_strchr(":=|", c); }
        static ZPL_ALWAYS_INLINE zpl_b32 zpl__json_is_delim_char(char c) { return !!zpl_strchr(",|\n", c); }

        char *zpl__json_parse_object(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
        char *zpl__json_parse_array(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code);
        char *zpl__json_parse_value(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code);

        #define jx(x) !zpl_char_is_hex_digit(str[x])
        ZPL_ALWAYS_INLINE zpl_b32 zpl__json_validate_name(char *str, char *err) {
            while (*str) {
                if ((str[0] == '\\' && !zpl_char_is_control(str[1])) &&
                    (str[0] == '\\' && jx(1) && jx(2) && jx(3) && jx(4))) {
                    *err = *str;
                    return false;
                }

                ++str;
            }

            return true;
        }
        #undef jx


        void zpl_json_parse(zpl_json_object *root, zpl_usize len, char const *source, zpl_allocator a, zpl_b32 handle_comments,
                            zpl_u8 *err_code) {

            if (!root || !source)
            {
                ZPL_JSON_ASSERT;
                if (err_code) *err_code = ZPL_JSON_ERROR_OBJECT_OR_SOURCE_WAS_NULL;
                return;
            }

            zpl_unused(len);

            char *dest = (char *)source;

            if (handle_comments) {
                zpl_b32 is_lit = false;
                char lit_c = '\0';
                char *p = dest;
                char *b = dest;
                zpl_isize l = 0;

                while (*p) {
                    if (!is_lit) {
                        if ((*p == '"' || *p == '\'')) {
                            lit_c = *p;
                            is_lit = true;
                            ++p;
                            continue;
                        }
                    } else {
                        if (*p == '\\' && *(p + 1) && *(p + 1) == lit_c) {
                            p += 2;
                            continue;
                        } else if (*p == lit_c) {
                            is_lit = false;
                            ++p;
                            continue;
                        }
                    }

                    if (!is_lit) {
                        // NOTE(ZaKlaus): block comment
                        if (p[0] == '/' && p[1] == '*') {
                            b = p;
                            l = 2;
                            p += 2;

                            while (p[0] != '*' && p[1] != '/') {
                                ++p;
                                ++l;
                            }
                            p += 2;
                            l += 2;
                            zpl_memset(b, ' ', l);
                        }

                        // NOTE(ZaKlaus): inline comment
                        if (p[0] == '/' && p[1] == '/') {
                            b = p;
                            l = 2;
                            p += 2;

                            while (p[0] != '\n') {
                                ++p;
                                ++l;
                            }
                            ++l;
                            zpl_memset(b, ' ', l);
                        }
                    }

                    ++p;
                }
            }

            if (err_code) *err_code = ZPL_JSON_ERROR_NONE;
            zpl_json_object root_ = { 0 };

            dest = zpl_str_trim(dest, false);

            zpl_b32 starts_with_bracket = false;

            if (*dest != '{' && *dest != '[') { root_.cfg_mode = true; }
            if (*dest == '[') { starts_with_bracket = true; }

            char *endp = NULL;

            if (!starts_with_bracket)
                endp = zpl__json_parse_object(&root_, dest, a, err_code);
            else
                endp = zpl__json_parse_array(&root_, (dest+1), a, err_code);

            if (!root_.cfg_mode && endp == NULL) {
                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            }

            // Replace root node with its child if the JSON document is an array.
            if (starts_with_bracket && root_.type != ZPL_JSON_TYPE_ARRAY) {
                zpl_json_object *replace = &root_;
                *replace = root_.nodes[0];
            }

            *root = root_;
        }

        #define zpl___ind(x)                                                                                                   \
        for (int i = 0; i < x; ++i) zpl_fprintf(f, " ");

        void zpl__json_write_value(zpl_file *f, zpl_json_object *o, zpl_json_object *t, zpl_isize indent, zpl_b32 is_inline, zpl_b32 is_last);

        void zpl_json_write(zpl_file *f, zpl_json_object *o, zpl_isize indent) {
            if (!o)
                return;

            zpl___ind(indent - 4);
            if (!o->cfg_mode)
                zpl_fprintf(f, "{\n");
            else {
                indent -= 4;
            }

            if (o->nodes)
            {
                zpl_isize cnt = zpl_array_count(o->nodes);

                for (int i = 0; i < cnt; ++i) {
                    if (i < cnt - 1) {
                        zpl__json_write_value(f, o->nodes + i, o, indent, false, false);
                    } else {
                        zpl__json_write_value(f, o->nodes + i, o, indent, false, true);
                    }
                }
            }

            zpl___ind(indent);

            if (indent > 0) {
                zpl_fprintf(f, "}");
            } else {
                if (!o->cfg_mode) zpl_fprintf(f, "}\n");
            }
        }

        void zpl__json_write_value(zpl_file *f, zpl_json_object *o, zpl_json_object *t, zpl_isize indent, zpl_b32 is_inline, zpl_b32 is_last) {
            zpl_json_object *node = o;
            indent += 4;

            if (!is_inline) {
                zpl___ind(indent);
                switch (node->name_style) {
                    case ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE: {
                        zpl_fprintf(f, "\"%s\"", node->name);
                    } break;

                    case ZPL_JSON_NAME_STYLE_SINGLE_QUOTE: {
                        zpl_fprintf(f, "\'%s\'", node->name);
                    } break;

                    case ZPL_JSON_NAME_STYLE_NO_QUOTES: {
                        zpl_fprintf(f, "%s", node->name);
                    } break;
                }

                if (o->assign_style == ZPL_JSON_ASSIGN_STYLE_COLON)
                    zpl_fprintf(f, ": ");
                else {
                    if (o->name_style != ZPL_JSON_NAME_STYLE_NO_QUOTES)
                        zpl___ind(1);

                    if (o->assign_style == ZPL_JSON_ASSIGN_STYLE_EQUALS)
                        zpl_fprintf(f, "= ");
                    else if (o->assign_style == ZPL_JSON_ASSIGN_STYLE_LINE)
                        zpl_fprintf(f, "| ");
                }

            }

            switch (node->type) {
                case ZPL_JSON_TYPE_STRING: {
                    zpl_fprintf(f, "\"%s\"", node->string);
                } break;

                case ZPL_JSON_TYPE_MULTISTRING: {
                    zpl_fprintf(f, "`%s`", node->string);
                } break;

                case ZPL_JSON_TYPE_ARRAY: {
                    zpl_fprintf(f, "[");
                    zpl_isize elemn = zpl_array_count(node->nodes);
                    for (int j = 0; j < elemn; ++j) {
                        if ((node->nodes + j)->type == ZPL_JSON_TYPE_OBJECT || (node->nodes + j)->type == ZPL_JSON_TYPE_ARRAY) {
                            zpl__json_write_value(f, node->nodes + j, o, 0, true, true);
                        } else {
                            zpl__json_write_value(f, node->nodes + j, o, -4, true, true);
                        }

                        if (j < elemn - 1) { zpl_fprintf(f, ", "); }
                    }
                    zpl_fprintf(f, "]");
                } break;

                case ZPL_JSON_TYPE_INTEGER: {
                    if (node->props == ZPL_JSON_PROPS_IS_HEX) {
                        zpl_fprintf(f, "0x%llx", (long long)node->integer);
                    } else {
                        zpl_fprintf(f, "%lld", (long long)node->integer);
                    }
                } break;

                case ZPL_JSON_TYPE_REAL: {
                    if (node->props == ZPL_JSON_PROPS_NAN) {
                        zpl_fprintf(f, "NaN");
                    } else if (node->props == ZPL_JSON_PROPS_NAN_NEG) {
                        zpl_fprintf(f, "-NaN");
                    } else if (node->props == ZPL_JSON_PROPS_INFINITY) {
                        zpl_fprintf(f, "Infinity");
                    } else if (node->props == ZPL_JSON_PROPS_INFINITY_NEG) {
                        zpl_fprintf(f, "-Infinity");
                    } else if (node->props == ZPL_JSON_PROPS_IS_EXP) {
                        zpl_fprintf(f, "%lld.%0*d%llde%c%lld", (long long)node->base, node->base2_offset, 0, (long long)node->base2, node->exp_neg ? '-' : '+',
                                    (long long)node->exp);
                    } else if (node->props == ZPL_JSON_PROPS_IS_PARSED_REAL) {
                        if (!node->lead_digit)
                            zpl_fprintf(f, ".%0*d%lld", node->base2_offset, 0, (long long)node->base2);
                        else
                            zpl_fprintf(f, "%lld.%0*d%lld", (long long int)node->base2_offset, 0, (int)node->base, (long long)node->base2);
                    } else {
                        zpl_fprintf(f, "%f", node->real);
                    }
                } break;

                case ZPL_JSON_TYPE_OBJECT: {
                    zpl_json_write(f, node, indent);
                } break;

                case ZPL_JSON_TYPE_CONSTANT: {
                    if (node->constant == ZPL_JSON_CONST_TRUE) {
                        zpl_fprintf(f, "true");
                    } else if (node->constant == ZPL_JSON_CONST_FALSE) {
                        zpl_fprintf(f, "false");
                    } else if (node->constant == ZPL_JSON_CONST_NULL) {
                        zpl_fprintf(f, "null");
                    }
                } break;
            }

            if (!is_inline) {

                if (o->delim_style != ZPL_JSON_DELIM_STYLE_COMMA)
                {
                    if (o->delim_style == ZPL_JSON_DELIM_STYLE_NEWLINE)
                        zpl_fprintf(f, "\n");
                    else if (o->delim_style == ZPL_JSON_DELIM_STYLE_LINE)
                    {
                        zpl___ind(o->delim_line_width);
                        zpl_fprintf(f, "|\n");
                    }
                }
                else
                {
                    if (!is_last) {
                        zpl_fprintf(f, ",\n");
                    } else {
                        zpl_fprintf(f, "\n");
                    }
                }
            }
        }
        #undef zpl___ind

        void zpl_json_free(zpl_json_object *obj) {
            if ((obj->type == ZPL_JSON_TYPE_OBJECT || obj->type == ZPL_JSON_TYPE_ARRAY) && obj->nodes) {
                for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); ++i) { zpl_json_free(obj->nodes + i); }

                zpl_array_free(obj->nodes);
            }
        }

        char *zpl__json_parse_array(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
            ZPL_ASSERT(obj && base);
            char *p = base;

            obj->type = ZPL_JSON_TYPE_ARRAY;
            zpl_array_init(obj->nodes, a);
            obj->backing = a;

            while (*p) {
                p = zpl_str_trim(p, false);

                if (p && *p == ']') {
                    return p;
                }

                zpl_json_object elem = { 0 };
                elem.backing = a;
                p = zpl__json_parse_value(&elem, p, a, err_code);

                if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

                zpl_array_append(obj->nodes, elem);

                p = zpl_str_trim(p, false);

                if (*p == ',') {
                    ++p;
                    continue;
                } else {
                    if (*p != ']') {
                        if (err_code) { *err_code = ZPL_JSON_ERROR_INVALID_VALUE; }
                    }
                    return p;
                }
            }

            if (err_code) { *err_code = ZPL_JSON_ERROR_INVALID_VALUE; }
            return p;
        }

        char *zpl__json_parse_value(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
            ZPL_ASSERT(obj && base);
            char *p = base;
            char *b = base;
            char *e = base;

            if (*p == '"' || *p == '\'') {
                char c = *p;
                obj->type = ZPL_JSON_TYPE_STRING;
                b = p + 1;
                e = b;
                obj->string = b;

                while (*e) {
                    if (*e == '\\' && *(e + 1) == c) {
                        e += 2;
                        continue;
                    } else if (*e == '\\' && (*(e + 1) == '\r' || *(e + 1) == '\n')) {
                        *e = ' ';
                        e++;
                        continue;
                    } else if (*e == c) {
                        break;
                    }
                    ++e;
                }

                *e = '\0';
                p = e + 1;
            } else if (*p == '`') {
                obj->type = ZPL_JSON_TYPE_MULTISTRING;
                b = p + 1;
                e = b;
                obj->string = b;

                while (*e) {
                    if (*e == '\\' && *(e + 1) == '`') {
                        e += 2;
                        continue;
                    } else if (*e == '`') {
                        break;
                    }
                    ++e;
                }

                *e = '\0';
                p = e + 1;
            } else if (zpl_char_is_alpha(*p) || (*p == '-' && !zpl_char_is_digit(*(p + 1)))) {
                obj->type = ZPL_JSON_TYPE_CONSTANT;

                if (!zpl_strncmp(p, "true", 4)) {
                    obj->constant = ZPL_JSON_CONST_TRUE;
                    p += 4;
                } else if (!zpl_strncmp(p, "false", 5)) {
                    obj->constant = ZPL_JSON_CONST_FALSE;
                    p += 5;
                } else if (!zpl_strncmp(p, "null", 4)) {
                    obj->constant = ZPL_JSON_CONST_NULL;
                    p += 4;
                } else if (!zpl_strncmp(p, "Infinity", 8)) {
                    obj->type = ZPL_JSON_TYPE_REAL;
                    obj->real = INFINITY;
                    obj->props = ZPL_JSON_PROPS_INFINITY;
                    p += 8;
                } else if (!zpl_strncmp(p, "-Infinity", 9)) {
                    obj->type = ZPL_JSON_TYPE_REAL;
                    obj->real = -INFINITY;
                    obj->props = ZPL_JSON_PROPS_INFINITY_NEG;
                    p += 9;
                } else if (!zpl_strncmp(p, "NaN", 3)) {
                    obj->type = ZPL_JSON_TYPE_REAL;
                    obj->real = NAN;
                    obj->props = ZPL_JSON_PROPS_NAN;
                    p += 3;
                } else if (!zpl_strncmp(p, "-NaN", 4)) {
                    obj->type = ZPL_JSON_TYPE_REAL;
                    obj->real = -NAN;
                    obj->props = ZPL_JSON_PROPS_NAN_NEG;
                    p += 4;
                } else {
                    ZPL_JSON_ASSERT;
                    if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
                    return NULL;
                }
            } else if (zpl_char_is_digit(*p) || *p == '+' || *p == '-' || *p == '.') {
                obj->type = ZPL_JSON_TYPE_INTEGER;

                b = p;
                e = b;

                zpl_isize ib = 0;
                char buf[48] = { 0 };

                if (*e == '+')
                    ++e;
                else if (*e == '-') {
                    buf[ib++] = *e++;
                }

                if (*e == '.') {
                    obj->type = ZPL_JSON_TYPE_REAL;
                    obj->props = ZPL_JSON_PROPS_IS_PARSED_REAL;
                    buf[ib++] = '0';
                    obj->lead_digit = false;

                    do {
                        buf[ib++] = *e;
                    } while (zpl_char_is_digit(*++e));
                } else {
                    if (*e == '0' && (*(e + 1) == 'x' || *(e + 1) == 'X')) { obj->props = ZPL_JSON_PROPS_IS_HEX; }
                    while (zpl_char_is_hex_digit(*e) || *e == 'x' || *e == 'X') { buf[ib++] = *e++; }

                    if (*e == '.') {
                        obj->type = ZPL_JSON_TYPE_REAL;
                        obj->lead_digit = true;
                        zpl_u32 step = 0;

                        do {
                            buf[ib++] = *e;
                            ++step;
                        } while (zpl_char_is_digit(*++e));

                        if (step < 2) { buf[ib++] = '0'; }
                    }
                }

                zpl_i32 exp = 0;
                zpl_f32 eb = 10;
                char expbuf[6] = { 0 };
                zpl_isize expi = 0;

                if (*e == 'e' || *e == 'E') {
                    ++e;
                    if (*e == '+' || *e == '-' || zpl_char_is_digit(*e)) {
                        if (*e == '-') { eb = 0.1f; }

                        if (!zpl_char_is_digit(*e)) { ++e; }

                        while (zpl_char_is_digit(*e)) { expbuf[expi++] = *e++; }
                    }

                    exp = (zpl_i32)zpl_str_to_i64(expbuf, NULL, 10);
                }

                if (obj->type == ZPL_JSON_TYPE_INTEGER) {
                    obj->integer = zpl_str_to_i64(buf, 0, 0);

                    while (exp-- > 0) { obj->integer *= (zpl_i64)eb; }
                } else {
                    obj->real = zpl_str_to_f64(buf, 0);

                    char *q = buf, *qp = q, *qp2 = q;
                    while (*qp != '.') ++qp;
                    *qp = '\0';
                    qp2 = qp + 1;
                    char *qpOff = qp2;
                    while (*qpOff++ == '0') obj->base2_offset++;

                    obj->base = (zpl_i32)zpl_str_to_i64(q, 0, 0);
                    obj->base2 = (zpl_i32)zpl_str_to_i64(qp2, 0, 0);

                    if (exp) {
                        obj->exp = exp;
                        obj->exp_neg = !(eb == 10.f);
                        obj->props = ZPL_JSON_PROPS_IS_EXP;
                    }

                    while (exp-- > 0) { obj->real *= eb; }
                }
                p = e;
            } else if (*p == '[') {
                p = zpl_str_trim(p + 1, false);
                obj->type = ZPL_JSON_TYPE_ARRAY;
                if (*p == ']') return (p+1);
                p = zpl__json_parse_array(obj, p, a, err_code);
                if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

                ++p;
            } else if (*p == '{') {
                p = zpl_str_trim(p + 1, false);
                obj->type = ZPL_JSON_TYPE_OBJECT;
                if (*p == '}') return (p+1);
                p = zpl__json_parse_object(obj, p, a, err_code);

                if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

                ++p;
            }

            return p;
        }

        char *zpl__json_parse_object(zpl_json_object *obj, char *base, zpl_allocator a, zpl_u8 *err_code) {
            ZPL_ASSERT(obj && base);
            char *p = base;
            char *b = base;
            char *e = base;

            zpl_array_init(obj->nodes, a);
            obj->backing = a;

            p = zpl_str_trim(p, false);
            zpl_b32 starts_with_brace = false;
            zpl_b32 starts_with_bracket = false;
            /**/ if (*p == '{') { ++p; starts_with_brace = true; obj->type = ZPL_JSON_TYPE_OBJECT; }
            else if (*p == '[') { ++p; starts_with_bracket = true; obj->type = ZPL_JSON_TYPE_ARRAY; }

            while (*p) {
                zpl_json_object node = { 0 };
                p = zpl_str_trim(p, false);
                if (*p == '}' && starts_with_brace) return p;
                if (*p == ']' && starts_with_bracket) return p;

                if (*p == ']' && starts_with_brace)     { if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE; return p; }
                if (*p == '}' && starts_with_bracket)   { if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE; return p; }

                if (*p == '"' || *p == '\'') {
                    if (*p == '"') {
                        node.name_style = ZPL_JSON_NAME_STYLE_DOUBLE_QUOTE;
                    } else {
                        node.name_style = ZPL_JSON_NAME_STYLE_SINGLE_QUOTE;
                    }

                    char c = *p;
                    b = ++p;
                    e = zpl_str_control_skip(b, c);
                    node.name = b;
                    *e = '\0';
                    p = ++e;
                    p = zpl_str_trim(p, false);
                    if (!zpl__json_is_assign_char(*p)) {
                        ZPL_JSON_ASSERT;
                        if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                        return NULL;
                    }
                }
                else {
                    if (*p == '[') {
                        starts_with_bracket = true;
                        if (node.name) *node.name = '\0';
                        p = zpl__json_parse_value(&node, p, a, err_code);
                        goto l_parsed;
                    }
                    else if (zpl_char_is_alpha(*p) || *p == '_' || *p == '$') {
                        b = p;
                        e = b;

                        do {
                            ++e;
                        } while (*e && (zpl_char_is_alphanumeric(*e) || *e == '_') && !zpl_char_is_space(*e) && !zpl__json_is_assign_char(*e));

                        if (zpl_char_is_space(*e)) {
                            // NOTE(zaklaus): We know this is where the node name ends, cut it here
                            *e = '\0';
                            ++e;
                        }

                        if (zpl__json_is_assign_char(*e)) {
                            p = e;

                            if (*e == '=')
                                node.assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
                            else if (*e == '|')
                                node.assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;
                        }
                        else {
                            while (*e) {
                                if (*e && (!zpl_char_is_space(*e) || zpl__json_is_assign_char(*e)))
                                {
                                    if (*e == '=')
                                        node.assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
                                    else if (*e == '|')
                                        node.assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;

                                    break;
                                }
                                ++e;
                            }

                            e = zpl_str_trim(e, false);
                            p = e;

                            if (*p && !zpl__json_is_assign_char(*p)) {
                                ZPL_JSON_ASSERT;
                                if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                                return NULL;
                            }
                            else
                            {
                                if (*p == '=')
                                    node.assign_style = ZPL_JSON_ASSIGN_STYLE_EQUALS;
                                else if (*p == '|')
                                    node.assign_style = ZPL_JSON_ASSIGN_STYLE_LINE;
                            }
                        }

                        *e = '\0';
                        node.name = b;
                        node.name_style = ZPL_JSON_NAME_STYLE_NO_QUOTES;
                    }
                }

                char errc;
                if (node.name && !zpl__json_validate_name(node.name, &errc)) {
                    ZPL_JSON_ASSERT;
                    if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_NAME;
                    return NULL;
                }

                p = zpl_str_trim(p + 1, false);
                p = zpl__json_parse_value(&node, p, a, err_code);
                node.backing = obj->backing;

                if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

                l_parsed:

                if (err_code && *err_code != ZPL_JSON_ERROR_NONE) { return NULL; }

                zpl_array_append(obj->nodes, node);

                char *wp = p;
                p = zpl_str_trim(p, true);
                zpl_u8 wl = cast(zpl_u8)(p-wp);

                if (zpl__json_is_delim_char(*p) || *p == '\0') {
                    zpl_json_object *n = zpl_array_end(obj->nodes);

                    if (*p == '\n')
                        n->delim_style = ZPL_JSON_DELIM_STYLE_NEWLINE;
                    else if (*p == '|') {
                        n->delim_style = ZPL_JSON_DELIM_STYLE_LINE;
                        n->delim_line_width = wl;
                    }
                    else if (*p == '\0') {
                        return p;
                    }

                    p = zpl_str_trim(p + 1, false);
                    if (*p == '\0' || *p == '}' || *p == ']')
                        return p;
                    else
                        continue;
                } else if (*p == '\0' || *p == '}' || *p == ']') {
                    if (starts_with_brace && *p != '}')
                    {
                        if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
                        return NULL;
                    }

                    if (starts_with_bracket && *p != ']')
                    {
                        if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
                        return NULL;
                    }

                    return p;
                } else {
                    ZPL_JSON_ASSERT;
                    if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
                    return NULL;
                }
            }
            if (err_code) *err_code = ZPL_JSON_ERROR_INVALID_VALUE;
            return p;
        }

        zpl_json_object *zpl_json_find(zpl_json_object *obj, char const *name, zpl_b32 deep_search)
        {
            if (obj->type != ZPL_JSON_TYPE_OBJECT)
            {
                return NULL;
            }

            for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); i++)
            {
                if (!zpl_strcmp(obj->nodes[i].name, name))
                {
                    return (obj->nodes + i);
                }
            }

            if (deep_search)
            {
                for (zpl_isize i = 0; i < zpl_array_count(obj->nodes); i++)
                {
                    zpl_json_object *res = zpl_json_find(obj->nodes + i, name, deep_search);

                    if (res != NULL)
                        return res;
                }
            }

            return NULL;
        }

        void zpl_json_init_node(zpl_json_object *obj, zpl_allocator backing, char const *name, zpl_u8 type)
        {
            obj->name = (char *)name;
            obj->type = type;
            obj->backing = backing;

            if (type == ZPL_JSON_TYPE_ARRAY || type == ZPL_JSON_TYPE_OBJECT)
            {
                zpl_array_init(obj->nodes, backing);
            }
        }

        zpl_json_object *zpl_json_add_at(zpl_json_object *obj, zpl_isize index, char const *name, zpl_u8 type)
        {
            if (!obj || (obj->type != ZPL_JSON_TYPE_OBJECT && obj->type != ZPL_JSON_TYPE_ARRAY))
            {
                return NULL;
            }

            if (!obj->nodes)
                return NULL;

            if (index < 0 || index > zpl_array_count(obj->nodes))
                return NULL;

            zpl_json_object o = {0};
            zpl_json_init_node(&o, obj->backing, name, type);

            zpl_array_append_at(obj->nodes, o, index);

            return obj->nodes + index;
        }

        zpl_json_object *zpl_json_add(zpl_json_object *obj, char const *name, zpl_u8 type)
        {
            if (!obj || (obj->type != ZPL_JSON_TYPE_OBJECT && obj->type != ZPL_JSON_TYPE_ARRAY))
            {
                return NULL;
            }

            if (!obj->nodes)
                return NULL;

            return zpl_json_add_at(obj, zpl_array_count(obj->nodes), name, type);
        }

        ZPL_END_C_DECLS
    #endif

    #if defined(ZPL_MODULE_THREADING)
        // file: source/threading/atomic.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        ////////////////////////////////////////////////////////////////
        //
        // Concurrency
        //
        //
        // IMPORTANT TODO: Use compiler intrinsics for the atomics

        #if defined(ZPL_COMPILER_MSVC) && !defined(ZPL_COMPILER_CLANG)
            zpl_i32 zpl_atomic32_load (zpl_atomic32 const *a)      { return a->value;  }
            void     zpl_atomic32_store(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) value) { a->value = value; }

            zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) expected, zpl_atomicarg(zpl_i32) desired) {
                return _InterlockedCompareExchange(cast(long *)a, desired, expected);
            }
            zpl_i32 zpl_atomic32_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) desired) {
                return _InterlockedExchange(cast(long *)a, desired);
            }
            zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
                return _InterlockedExchangeAdd(cast(long *)a, operand);
            }
            zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
                return _InterlockedAnd(cast(long *)a, operand);
            }
            zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
                return _InterlockedOr(cast(long *)a, operand);
            }

            zpl_i64 zpl_atomic64_load(zpl_atomic64 const *a) {
                #if defined(ZPL_ARCH_64_BIT)
                    return a->value;
                #elif ZPL_CPU_X86
                    // NOTE: The most compatible way to get an atomic 64-bit load on x86 is with cmpxchg8b
                    zpl_atomicarg(zpl_i64) result;
                    __asm {
                        mov esi, a;
                        mov ebx, eax;
                        mov ecx, edx;
                        lock cmpxchg8b [esi];
                        mov dword ptr result, eax;
                        mov dword ptr result[4], edx;
                    }
                    return result;
                #else
                    #error TODO: atomics for this CPU
                #endif
            }

            void zpl_atomic64_store(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) value) {
                #if defined(ZPL_ARCH_64_BIT)
                    a->value = value;
                #elif ZPL_CPU_X86
                    // NOTE: The most compatible way to get an atomic 64-bit store on x86 is with cmpxchg8b
                    __asm {
                        mov esi, a;
                        mov ebx, dword ptr value;
                        mov ecx, dword ptr value[4];
                        retry:
                        cmpxchg8b [esi];
                        jne retry;
                    }
                #else
                    #error TODO: atomics for this CPU
                #endif
            }

            zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) expected, zpl_atomicarg(zpl_i64) desired) {
                return _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, desired, expected);
            }

            zpl_i64 zpl_atomic64_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) desired) {
                #if defined(ZPL_ARCH_64_BIT)
                    return _InterlockedExchange64(cast(zpl_atomicarg(zpl_i64) *)a, desired);
                #elif ZPL_CPU_X86
                    zpl_atomicarg(zpl_i64) expected = a->value;
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, desired, expected);
                        if (original == expected)
                            return original;
                        expected = original;
                    }
                #else
                    #error TODO: atomics for this CPU
                #endif
            }

            zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
                #if defined(ZPL_ARCH_64_BIT)
                    return _InterlockedExchangeAdd64(cast(zpl_atomicarg(zpl_i64) *)a, operand);
                #elif ZPL_CPU_X86
                    zpl_atomicarg(zpl_i64) expected = a->value;
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, expected + operand, expected);
                        if (original == expected)
                            return original;
                        expected = original;
                    }
                #else
                    #error TODO: atomics for this CPU
                #endif
            }

            zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
                #if defined(ZPL_ARCH_64_BIT)
                    return _InterlockedAnd64(cast(zpl_atomicarg(zpl_i64) *)a, operand);
                #elif ZPL_CPU_X86
                    zpl_atomicarg(zpl_i64) expected = a->value;
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, expected & operand, expected);
                        if (original == expected)
                            return original;
                        expected = original;
                    }
                #else
                    #error TODO: atomics for this CPU
                #endif
            }

            zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
                #if defined(ZPL_ARCH_64_BIT)
                    return _InterlockedOr64(cast(zpl_atomicarg(zpl_i64) *)a, operand);
                #elif ZPL_CPU_X86
                    zpl_atomicarg(zpl_i64) expected = a->value;
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = _InterlockedCompareExchange64(cast(zpl_atomicarg(zpl_i64) *)a, expected | operand, expected);
                        if (original == expected)
                            return original;
                        expected = original;
                    }
                #else
                    #error TODO: atomics for this CPU
                #endif
            }

        #elif defined(ZPL_CPU_X86)

            zpl_i32 zpl_atomic32_load (zpl_atomic32 const *a)      { return a->value;  }
            void zpl_atomic32_store(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) value) { a->value = value; }

            zpl_i32 zpl_atomic32_compare_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) expected, zpl_atomicarg(zpl_i32) desired) {
                zpl_atomicarg(zpl_i32) original;
                __asm__(
                    "lock; cmpxchgl %2, %1"
                    : "=a"(original), "+m"(a->value)
                    : "q"(desired), "0"(expected)
                    );
                return original;
            }

            zpl_i32 zpl_atomic32_exchange(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) desired) {
                // NOTE: No lock prefix is necessary for xchgl
                zpl_atomicarg(zpl_i32) original;
                __asm__(
                    "xchgl %0, %1"
                    : "=r"(original), "+m"(a->value)
                    : "0"(desired)
                    );
                return original;
            }

            zpl_i32 zpl_atomic32_fetch_add(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
                zpl_atomicarg(zpl_i32) original;
                __asm__(
                    "lock; xaddl %0, %1"
                    : "=r"(original), "+m"(a->value)
                    : "0"(operand)
                    );
                return original;
            }

            zpl_i32 zpl_atomic32_fetch_and(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
                zpl_atomicarg(zpl_i32) original;
                zpl_atomicarg(zpl_i32) tmp;
                __asm__(
                    "1:     movl    %1, %0\n"
                    "       movl    %0, %2\n"
                    "       andl    %3, %2\n"
                    "       lock; cmpxchgl %2, %1\n"
                    "       jne     1b"
                    : "=&a"(original), "+m"(a->value), "=&r"(tmp)
                    : "r"(operand)
                    );
                return original;
            }

            zpl_i32 zpl_atomic32_fetch_or(zpl_atomic32 *a, zpl_atomicarg(zpl_i32) operand) {
                zpl_atomicarg(zpl_i32) original;
                zpl_atomicarg(zpl_i32) temp;
                __asm__(
                    "1:     movl    %1, %0\n"
                    "       movl    %0, %2\n"
                    "       orl     %3, %2\n"
                    "       lock; cmpxchgl %2, %1\n"
                    "       jne     1b"
                    : "=&a"(original), "+m"(a->value), "=&r"(temp)
                    : "r"(operand)
                    );
                return original;
            }


            zpl_i64 zpl_atomic64_load(zpl_atomic64 const *a) {
                #if defined(ZPL_ARCH_64_BIT)
                    return a->value;
                #else
                    zpl_atomicarg(zpl_i64) original;
                    __asm__(
                        "movl %%ebx, %%eax\n"
                        "movl %%ecx, %%edx\n"
                        "lock; cmpxchg8b %1"
                        : "=&A"(original)
                        : "m"(a->value)
                        );
                    return original;
                #endif
            }

            void zpl_atomic64_store(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) value) {
                #if defined(ZPL_ARCH_64_BIT)
                    a->value = value;
                #else
                    zpl_atomicarg(zpl_i64) expected = a->value;
                    __asm__(
                        "1:    cmpxchg8b %0\n"
                        "      jne 1b"
                        : "=m"(a->value)
                        : "b"((zpl_atomicarg(zpl_i32))value), "c"((zpl_atomicarg(zpl_i32))(value >> 32)), "A"(expected)
                        );
                #endif
            }

            zpl_i64 zpl_atomic64_compare_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) expected, zpl_atomicarg(zpl_i64) desired) {
                #if defined(ZPL_ARCH_64_BIT)
                    zpl_atomicarg(zpl_i64) original;
                    __asm__(
                        "lock; cmpxchgq %2, %1"
                        : "=a"(original), "+m"(a->value)
                        : "q"(desired), "0"(expected)
                        );
                    return original;
                #else
                    zpl_atomicarg(zpl_i64) original;
                    __asm__(
                        "lock; cmpxchg8b %1"
                        : "=A"(original), "+m"(a->value)
                        : "b"((zpl_atomicarg(zpl_i32))desired), "c"((zpl_atomicarg(zpl_i32))(desired >> 32)), "0"(expected)
                        );
                    return original;
                #endif
            }

            zpl_i64 zpl_atomic64_exchange(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) desired) {
                #if defined(ZPL_ARCH_64_BIT)
                    zpl_atomicarg(zpl_i64) original;
                    __asm__(
                        "xchgq %0, %1"
                        : "=r"(original), "+m"(a->value)
                        : "0"(desired)
                        );
                    return original;
                #else
                    zpl_atomicarg(zpl_i64) original = a->value;
                    for (;;) {
                        zpl_atomicarg(zpl_i64) previous = zpl_atomic64_compare_exchange(a, original, desired);
                        if (original == previous)
                            return original;
                        original = previous;
                    }
                #endif
            }

            zpl_i64 zpl_atomic64_fetch_add(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
                #if defined(ZPL_ARCH_64_BIT)
                    zpl_atomicarg(zpl_i64) original;
                    __asm__(
                        "lock; xaddq %0, %1"
                        : "=r"(original), "+m"(a->value)
                        : "0"(operand)
                        );
                    return original;
                #else
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = a->value;
                        if (zpl_atomic64_compare_exchange(a, original, original + operand) == original)
                            return original;
                    }
                #endif
            }

            zpl_i64 zpl_atomic64_fetch_and(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
                #if defined(ZPL_ARCH_64_BIT)
                    zpl_atomicarg(zpl_i64) original;
                    zpl_atomicarg(zpl_i64) tmp;
                    __asm__(
                        "1:     movq    %1, %0\n"
                        "       movq    %0, %2\n"
                        "       andq    %3, %2\n"
                        "       lock; cmpxchgq %2, %1\n"
                        "       jne     1b"
                        : "=&a"(original), "+m"(a->value), "=&r"(tmp)
                        : "r"(operand)
                        );
                    return original;
                #else
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = a->value;
                        if (zpl_atomic64_compare_exchange(a, original, original & operand) == original)
                            return original;
                    }
                #endif
            }

            zpl_i64 zpl_atomic64_fetch_or(zpl_atomic64 *a, zpl_atomicarg(zpl_i64) operand) {
                #if defined(ZPL_ARCH_64_BIT)
                    zpl_atomicarg(zpl_i64) original;
                    zpl_atomicarg(zpl_i64) temp;
                    __asm__(
                        "1:     movq    %1, %0\n"
                        "       movq    %0, %2\n"
                        "       orq     %3, %2\n"
                        "       lock; cmpxchgq %2, %1\n"
                        "       jne     1b"
                        : "=&a"(original), "+m"(a->value), "=&r"(temp)
                        : "r"(operand)
                        );
                    return original;
                #else
                    for (;;) {
                        zpl_atomicarg(zpl_i64) original = a->value;
                        if (zpl_atomic64_compare_exchange(a, original, original | operand) == original)
                            return original;
                    }
                #endif
            }

        #else
            #error TODO: Implement Atomics for this CPU
        #endif



        zpl_b32 zpl_atomic32_spin_lock(zpl_atomic32 *a, zpl_isize time_out) {
            zpl_atomicarg(zpl_i32) old_value = zpl_atomic32_compare_exchange(a, 1, 0);
            zpl_i32 counter = 0;
            while (old_value != 0 && (time_out < 0 || counter++ < time_out)) {
                zpl_yield_thread();
                old_value = zpl_atomic32_compare_exchange(a, 1, 0);
                zpl_mfence();
            }
            return old_value == 0;
        }

        void zpl_atomic32_spin_unlock(zpl_atomic32 *a) {
            zpl_atomic32_store(a, 0);
            zpl_mfence();
        }

        zpl_b32 zpl_atomic64_spin_lock(zpl_atomic64 *a, zpl_isize time_out) {
            zpl_atomicarg(zpl_i64) old_value = zpl_atomic64_compare_exchange(a, 1, 0);
            zpl_atomicarg(zpl_i64) counter = 0;
            while (old_value != 0 && (time_out < 0 || counter++ < time_out)) {
                zpl_yield_thread();
                old_value = zpl_atomic64_compare_exchange(a, 1, 0);
                zpl_mfence();
            }
            return old_value == 0;
        }

        void zpl_atomic64_spin_unlock(zpl_atomic64 *a) {
            zpl_atomic64_store(a, 0);
            zpl_mfence();
        }

        zpl_b32 zpl_atomic32_try_acquire_lock(zpl_atomic32 *a) {
            zpl_atomicarg(zpl_i32) old_value;
            zpl_yield_thread();
            old_value = zpl_atomic32_compare_exchange(a, 1, 0);
            zpl_mfence();
            return old_value == 0;
        }

        zpl_b32 zpl_atomic64_try_acquire_lock(zpl_atomic64 *a) {
            zpl_atomicarg(zpl_i64) old_value;
            zpl_yield_thread();
            old_value = zpl_atomic64_compare_exchange(a, 1, 0);
            zpl_mfence();
            return old_value == 0;
        }



        #if defined(ZPL_ARCH_32_BIT)

            void* zpl_atomic_ptr_load(zpl_atomic_ptr const *a) {
                return (void *)cast(zpl_intptr)zpl_atomic32_load(cast(zpl_atomic32 const *)a);
            }
            void zpl_atomic_ptr_store(zpl_atomic_ptr *a, zpl_atomicarg(void *)value) {
                zpl_atomic32_store(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)value);
            }
            void* zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)expected, zpl_atomicarg(void *)desired) {
                return (void *)cast(zpl_intptr)zpl_atomic32_compare_exchange(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)expected, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)desired);
            }
            void* zpl_atomic_ptr_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)desired) {
                return (void *)cast(zpl_intptr)zpl_atomic32_exchange(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)desired);
            }
            void* zpl_atomic_ptr_fetch_add(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
                return (void *)cast(zpl_intptr)zpl_atomic32_fetch_add(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)operand);
            }
            void* zpl_atomic_ptr_fetch_and(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
                return (void *)cast(zpl_intptr)zpl_atomic32_fetch_and(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)operand);
            }
            void* zpl_atomic_ptr_fetch_or(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
                return (void *)cast(zpl_intptr)zpl_atomic32_fetch_or(cast(zpl_atomic32 *)a, cast(zpl_atomicarg(zpl_i32))cast(zpl_intptr)operand);
            }
            zpl_b32 zpl_atomic_ptr_spin_lock(zpl_atomic_ptr *a, zpl_isize time_out) {
                return zpl_atomic32_spin_lock(cast(zpl_atomic32 *)a, time_out);
            }
            void zpl_atomic_ptr_spin_unlock(zpl_atomic_ptr *a) {
                zpl_atomic32_spin_unlock(cast(zpl_atomic32 *)a);
            }
            zpl_b32 zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr *a) {
                return zpl_atomic32_try_acquire_lock(cast(zpl_atomic32 *)a);
            }

        #elif defined(ZPL_ARCH_64_BIT)

            void* zpl_atomic_ptr_load(zpl_atomic_ptr const *a) {
                return (void *)cast(zpl_intptr)zpl_atomic64_load(cast(zpl_atomic64 const *)a);
            }
            void zpl_atomic_ptr_store(zpl_atomic_ptr *a, zpl_atomicarg(void *)value) {
                zpl_atomic64_store(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)value);
            }
            void* zpl_atomic_ptr_compare_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)expected, zpl_atomicarg(void *)desired) {
                return (void *)cast(zpl_intptr)zpl_atomic64_compare_exchange(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)expected, cast(zpl_i64)cast(zpl_intptr)desired);
            }
            void* zpl_atomic_ptr_exchange(zpl_atomic_ptr *a, zpl_atomicarg(void *)desired) {
                return (void *)cast(zpl_intptr)zpl_atomic64_exchange(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)desired);
            }
            void* zpl_atomic_ptr_fetch_add(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
                return (void *)cast(zpl_intptr)zpl_atomic64_fetch_add(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)operand);
            }
            void* zpl_atomic_ptr_fetch_and(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
                return (void *)cast(zpl_intptr)zpl_atomic64_fetch_and(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)operand);
            }
            void* zpl_atomic_ptr_fetch_or(zpl_atomic_ptr *a, zpl_atomicarg(void *)operand) {
                return (void *)cast(zpl_intptr)zpl_atomic64_fetch_or(cast(zpl_atomic64 *)a, cast(zpl_i64)cast(zpl_intptr)operand);
            }
            zpl_b32 zpl_atomic_ptr_spin_lock(zpl_atomic_ptr *a, zpl_isize time_out) {
                return zpl_atomic64_spin_lock(cast(zpl_atomic64 *)a, time_out);
            }
            void zpl_atomic_ptr_spin_unlock(zpl_atomic_ptr *a) {
                zpl_atomic64_spin_unlock(cast(zpl_atomic64 *)a);
            }
            zpl_b32 zpl_atomic_ptr_try_acquire_lock(zpl_atomic_ptr *a) {
                return zpl_atomic64_try_acquire_lock(cast(zpl_atomic64 *)a);
            }

        #endif

        ZPL_END_C_DECLS
        // file: source/threading/fence.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(_MSC_VER)
             /* Microsoft C/C++-compatible compiler */
             #include <intrin.h>
        #elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
             /* GCC-compatible compiler, targeting x86/x86-64 */
             #include <x86intrin.h>
        #elif defined(__GNUC__) && defined(__ARM_NEON__)
             /* GCC-compatible compiler, targeting ARM with NEON */
             #include <arm_neon.h>
        #elif defined(__GNUC__) && defined(__IWMMXT__)
             /* GCC-compatible compiler, targeting ARM with WMMX */
             #include <mmintrin.h>
        #elif (defined(__GNUC__) || defined(__xlC__)) && (defined(__VEC__) || defined(__ALTIVEC__))
             /* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
             #include <altivec.h>
        #elif defined(__GNUC__) && defined(__SPE__)
             /* GCC-compatible compiler, targeting PowerPC with SPE */
             #include <spe.h>
        #endif

        void zpl_yield_thread(void) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                _mm_pause();
            #elif defined(ZPL_SYSTEM_OSX)
                __asm__ volatile ("" : : : "memory");
            #elif defined(ZPL_CPU_X86)
                _mm_pause();
            #else
                #error Unknown architecture
            #endif
        }

        void zpl_mfence(void) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                _ReadWriteBarrier();
            #elif defined(ZPL_SYSTEM_OSX)
                __sync_synchronize();
            #elif defined(ZPL_CPU_X86)
                _mm_mfence();
            #else
                #error Unknown architecture
            #endif
        }

        void zpl_sfence(void) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                _WriteBarrier();
            #elif defined(ZPL_SYSTEM_OSX)
                __asm__ volatile ("" : : : "memory");
            #elif defined(ZPL_CPU_X86)
                _mm_sfence();
            #else
                #error Unknown architecture
            #endif
        }

        void zpl_lfence(void) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                _ReadBarrier();
            #elif defined(ZPL_SYSTEM_OSX)
                __asm__ volatile ("" : : : "memory");
            #elif defined(ZPL_CPU_X86)
                _mm_lfence();
            #else
                #error Unknown architecture
            #endif
        }

        ZPL_END_C_DECLS
        // file: source/threading/sem.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        void zpl_semaphore_release(zpl_semaphore *s) { zpl_semaphore_post(s, 1); }

        #if defined(ZPL_SYSTEM_WINDOWS)

            void zpl_semaphore_init   (zpl_semaphore *s)            { s->win32_handle = CreateSemaphoreA(NULL, 0, ZPL_I32_MAX, NULL); }
            void zpl_semaphore_destroy(zpl_semaphore *s)            { CloseHandle(s->win32_handle); }
            void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { ReleaseSemaphore(s->win32_handle, count, NULL); }
            void zpl_semaphore_wait   (zpl_semaphore *s)            { WaitForSingleObject(s->win32_handle, INFINITE); }

        #elif defined(ZPL_SYSTEM_OSX)

            void zpl_semaphore_init   (zpl_semaphore *s)            { semaphore_create(mach_task_self(), &s->osx_handle, SYNC_POLICY_FIFO, 0); }
            void zpl_semaphore_destroy(zpl_semaphore *s)            { semaphore_destroy(mach_task_self(), s->osx_handle); }
            void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { while (count --> 0) semaphore_signal(s->osx_handle); }
            void zpl_semaphore_wait   (zpl_semaphore *s)            { semaphore_wait(s->osx_handle); }

        #elif defined(ZPL_SYSTEM_UNIX)

            void zpl_semaphore_init   (zpl_semaphore *s)            { sem_init(&s->unix_handle, 0, 0); }
            void zpl_semaphore_destroy(zpl_semaphore *s)            { sem_destroy(&s->unix_handle); }
            void zpl_semaphore_post   (zpl_semaphore *s, zpl_i32 count) { while (count --> 0) sem_post(&s->unix_handle); }
            void zpl_semaphore_wait   (zpl_semaphore *s)            { int i; do { i = sem_wait(&s->unix_handle); } while (i == -1 && errno == EINTR); }

        #else
            #error Semaphores for this OS are not implemented
        #endif

        ZPL_END_C_DECLS
        // file: source/threading/mutex.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        void zpl_mutex_init(zpl_mutex *m) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                InitializeCriticalSection(&m->win32_critical_section);
            #else
                pthread_mutex_init(&m->pthread_mutex, NULL);
            #endif
        }

        void zpl_mutex_destroy(zpl_mutex *m) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                DeleteCriticalSection(&m->win32_critical_section);
            #else
                pthread_mutex_destroy(&m->pthread_mutex);
            #endif
        }

        void zpl_mutex_lock(zpl_mutex *m) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                EnterCriticalSection(&m->win32_critical_section);
            #else
                pthread_mutex_lock(&m->pthread_mutex);
            #endif
        }

        zpl_b32 zpl_mutex_try_lock(zpl_mutex *m) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                return TryEnterCriticalSection(&m->win32_critical_section);
            #else
                return pthread_mutex_trylock(&m->pthread_mutex);
            #endif
        }

        void zpl_mutex_unlock(zpl_mutex *m) {
            #if defined(ZPL_SYSTEM_WINDOWS)
                LeaveCriticalSection(&m->win32_critical_section);
            #else
                pthread_mutex_unlock(&m->pthread_mutex);
            #endif
        }

        ZPL_END_C_DECLS
        // file: source/threading/thread.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        zpl_b32 zpl_thread_is_running(zpl_thread const *t) { return t->is_running != 0; }

        void zpl_thread_init(zpl_thread *t) {
            zpl_zero_item(t);

            #if defined(ZPL_SYSTEM_WINDOWS)
                t->win32_handle = INVALID_HANDLE_VALUE;
            #else
                t->posix_handle = 0;
            #endif

            zpl_semaphore_init(&t->semaphore);
        }

        void zpl_thread_destroy(zpl_thread *t) {
            if (t->is_running) zpl_thread_join(t);
            zpl_semaphore_destroy(&t->semaphore);
        }

        void zpl__thread_run(zpl_thread *t) {
            zpl_semaphore_release(&t->semaphore);
            t->return_value = t->proc(t);
        }

        #if defined(ZPL_SYSTEM_WINDOWS)
            DWORD __stdcall zpl__thread_proc(void *arg) {
                zpl_thread *t = cast(zpl_thread *)arg;
                zpl__thread_run(t);
                t->is_running = false;
                return 0;
            }
        #else
            void *zpl__thread_proc(void *arg) {
                zpl_thread *t = cast(zpl_thread *)arg;
                zpl__thread_run(t);
                t->is_running = false;
                return NULL;
            }
        #endif

        void zpl_thread_start(zpl_thread *t, zpl_thread_proc proc, void *user_data) {
            zpl_thread_start_with_stack(t, proc, user_data, 0);
        }

        void zpl_thread_start_with_stack(zpl_thread *t, zpl_thread_proc proc, void *user_data, zpl_isize stack_size) {
            ZPL_ASSERT(!t->is_running);
            ZPL_ASSERT(proc != NULL);
            t->proc = proc;
            t->user_data = user_data;
            t->stack_size = stack_size;

            #if defined(ZPL_SYSTEM_WINDOWS)
                t->win32_handle = CreateThread(NULL, stack_size, zpl__thread_proc, t, 0, NULL);
                ZPL_ASSERT_MSG(t->win32_handle != NULL, "CreateThread: GetLastError");
            #else
                {
                    pthread_attr_t attr;
                    pthread_attr_init(&attr);
                    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
                    if (stack_size != 0)
                        pthread_attr_setstacksize(&attr, stack_size);
                    pthread_create(&t->posix_handle, &attr, zpl__thread_proc, t);
                    pthread_attr_destroy(&attr);
                }
            #endif

            t->is_running = true;
            zpl_semaphore_wait(&t->semaphore);
        }

        void zpl_thread_join(zpl_thread *t) {
            if (!t->is_running) return;

            #if defined(ZPL_SYSTEM_WINDOWS)
                WaitForSingleObject(t->win32_handle, INFINITE);
                CloseHandle(t->win32_handle);
                t->win32_handle = INVALID_HANDLE_VALUE;
            #else
                pthread_join(t->posix_handle, NULL);
                t->posix_handle = 0;
            #endif
                t->is_running = false;
            }

            zpl_u32 zpl_thread_current_id(void) {
                zpl_u32 thread_id;
            #if defined(ZPL_SYSTEM_WINDOWS)
                #if defined(ZPL_ARCH_32_BIT) && defined(ZPL_CPU_X86)
                    thread_id = (cast(zpl_u32 *)__readfsdword(24))[9];
                #elif defined(ZPL_ARCH_64_BIT) && defined(ZPL_CPU_X86)
                    thread_id = (cast(zpl_u32 *)__readgsqword(48))[18];
                #else
                    thread_id = GetCurrentThreadId();
                #endif

            #elif defined(ZPL_SYSTEM_OSX) && defined(ZPL_ARCH_64_BIT)
                thread_id = pthread_mach_thread_np(pthread_self());
            #elif defined(ZPL_ARCH_32_BIT) && defined(ZPL_CPU_X86)
                __asm__("mov %%gs:0x08,%0" : "=r"(thread_id));
            #elif defined(ZPL_ARCH_64_BIT) && defined(ZPL_CPU_X86)
                __asm__("mov %%fs:0x10,%0" : "=r"(thread_id));
            #else
                #error Unsupported architecture for zpl_thread_current_id()
            #endif

            return thread_id;
        }

        void zpl_thread_set_name(zpl_thread *t, char const *name) {
            #if defined(ZPL_COMPILER_MSVC)
                #pragma pack(push, 8)
                    typedef struct {
                        DWORD       type;
                        char const *name;
                        DWORD       id;
                        DWORD       flags;
                    } zplprivThreadName;
                #pragma pack(pop)

                zplprivThreadName tn;
                tn.type  = 0x1000;
                tn.name  = name;
                tn.id    = GetThreadId(cast(HANDLE)t->win32_handle);
                tn.flags = 0;

                __try {
                    RaiseException(0x406d1388, 0, zpl_size_of(tn)/4, cast(ULONG_PTR *)&tn);
                } __except(1 /*EXCEPTION_EXECUTE_HANDLER*/) {
                }

            #elif defined(ZPL_SYSTEM_WINDOWS) && !defined(ZPL_COMPILER_MSVC)
                zpl_unused(t);
                zpl_unused(name);
                // IMPORTANT TODO: Set thread name for GCC/Clang on windows
                return;
            #elif defined(ZPL_SYSTEM_OSX)
                // TODO: Test if this works
                pthread_setname_np(name);
            #else
                zpl_unused(t);
                zpl_unused(name);
                // TODO: Test if this works
                //        pthread_set_name_np(t->posix_handle, name);
            #endif
        }

        ZPL_END_C_DECLS
        // file: source/threading/sync.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        void zpl_sync_init(zpl_sync *s) {
            zpl_zero_item(s);
            zpl_mutex_init(&s->mutex);
            zpl_mutex_init(&s->start);
            zpl_semaphore_init(&s->release);
        }

        void zpl_sync_destroy(zpl_sync *s) {
            if (s->waiting) {
                ZPL_PANIC("Cannot destroy while threads are waiting!");
            }

            zpl_mutex_destroy(&s->mutex);
            zpl_mutex_destroy(&s->start);
            zpl_semaphore_destroy(&s->release);
        }

        void zpl_sync_set_target(zpl_sync *s, zpl_i32 count) {
            zpl_mutex_lock(&s->start);

            zpl_mutex_lock(&s->mutex);
            ZPL_ASSERT(s->target == 0);
            s->target = count;
            s->current = 0;
            s->waiting = 0;
            zpl_mutex_unlock(&s->mutex);
        }

        void zpl_sync_release(zpl_sync *s) {
            if (s->waiting) {
                zpl_semaphore_release(&s->release);
            } else {
                s->target = 0;
                zpl_mutex_unlock(&s->start);
            }
        }

        zpl_i32 zpl_sync_reach(zpl_sync *s) {
            zpl_i32 n;
            zpl_mutex_lock(&s->mutex);
            ZPL_ASSERT(s->current < s->target);
            n = ++s->current; // NOTE: Record this value to avoid possible race if `return s->current` was done
            if (s->current == s->target)
                zpl_sync_release(s);
            zpl_mutex_unlock(&s->mutex);
            return n;
        }

        void zpl_sync_reach_and_wait(zpl_sync *s) {
            zpl_mutex_lock(&s->mutex);
            ZPL_ASSERT(s->current < s->target);
            s->current++;
            if (s->current == s->target) {
                zpl_sync_release(s);
                zpl_mutex_unlock(&s->mutex);
            } else {
                s->waiting++;                   // NOTE: Waiting, so one more waiter
                zpl_mutex_unlock(&s->mutex);     // NOTE: Release the mutex to other threads
                zpl_semaphore_wait(&s->release); // NOTE: Wait for merge completion
                zpl_mutex_lock(&s->mutex);       // NOTE: On merge completion, lock mutex
                s->waiting--;                   // NOTE: Done waiting
                zpl_sync_release(s);             // NOTE: Restart the next waiter
                zpl_mutex_unlock(&s->mutex);
            }
        }

        ZPL_END_C_DECLS
        // file: source/threading/affinity.c

        #ifdef ZPL_EDITOR
        #include <zpl.h>
        #endif

        #if defined(ZPL_SYSTEM_MACOS)
            #include <sys/sysctl.h>
        #endif

        ZPL_BEGIN_C_DECLS

        #if defined(ZPL_SYSTEM_WINDOWS) || defined(ZPL_SYSTEM_CYGWIN)

            void zpl_affinity_init(zpl_affinity *a) {
                SYSTEM_LOGICAL_PROCESSOR_INFORMATION *start_processor_info = NULL;
                DWORD length = 0;
                zpl_b32 result  = GetLogicalProcessorInformation(NULL, &length);

                zpl_zero_item(a);

                if (!result && GetLastError() == 122l /*ERROR_INSUFFICIENT_BUFFER*/ && length > 0) {
                    start_processor_info = cast(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)zpl_alloc(zpl_heap_allocator(), length);
                    result = GetLogicalProcessorInformation(start_processor_info, &length);
                    if (result) {
                        SYSTEM_LOGICAL_PROCESSOR_INFORMATION *end_processor_info, *processor_info;

                        a->is_accurate  = true;
                        a->core_count   = 0;
                        a->thread_count = 0;
                        end_processor_info = cast(SYSTEM_LOGICAL_PROCESSOR_INFORMATION *)zpl_pointer_add(start_processor_info, length);

                        for (processor_info = start_processor_info;
                             processor_info < end_processor_info;
                             processor_info++) {
                            if (processor_info->Relationship == RelationProcessorCore) {
                                zpl_isize thread = zpl_count_set_bits(processor_info->ProcessorMask);
                                if (thread == 0) {
                                    a->is_accurate = false;
                                } else if (a->thread_count + thread > ZPL_WIN32_MAX_THREADS) {
                                    a->is_accurate = false;
                                } else {
                                    ZPL_ASSERT(a->core_count <= a->thread_count &&
                                               a->thread_count < ZPL_WIN32_MAX_THREADS);
                                    a->core_masks[a->core_count++] = processor_info->ProcessorMask;
                                    a->thread_count += thread;
                                }
                            }
                        }
                    }

                    zpl_free(zpl_heap_allocator(), start_processor_info);
                }

                ZPL_ASSERT(a->core_count <= a->thread_count);
                if (a->thread_count == 0) {
                    a->is_accurate   = false;
                    a->core_count    = 1;
                    a->thread_count  = 1;
                    a->core_masks[0] = 1;
                }

            }

            void zpl_affinity_destroy(zpl_affinity *a) {
                zpl_unused(a);
            }

            zpl_b32 zpl_affinity_set(zpl_affinity *a, zpl_isize core, zpl_isize thread) {
                zpl_usize available_mask, check_mask = 1;
                ZPL_ASSERT(thread < zpl_affinity_thread_count_for_core(a, core));

                available_mask = a->core_masks[core];
                for (;;) {
                    if ((available_mask & check_mask) != 0) {
                        if (thread-- == 0) {
                            zpl_usize result = SetThreadAffinityMask(GetCurrentThread(), check_mask);
                            return result != 0;
                        }
                    }
                    check_mask <<= 1; // NOTE: Onto the next bit
                }
            }

            zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core) {
                ZPL_ASSERT(core >= 0 && core < a->core_count);
                return zpl_count_set_bits(a->core_masks[core]);
            }

        #elif defined(ZPL_SYSTEM_MACOS)
            void zpl_affinity_init(zpl_affinity *a) {
                zpl_usize count, count_size = zpl_size_of(count);

                a->is_accurate      = false;
                a->thread_count     = 1;
                a->core_count       = 1;
                a->threads_per_core = 1;

                if (sysctlbyname("hw.logicalcpu", &count, &count_size, NULL, 0) == 0) {
                    if (count > 0) {
                        a->thread_count = count;
                        // Get # of physical cores
                        if (sysctlbyname("hw.physicalcpu", &count, &count_size, NULL, 0) == 0) {
                            if (count > 0) {
                                a->core_count = count;
                                a->threads_per_core = a->thread_count / count;
                                if (a->threads_per_core < 1)
                                    a->threads_per_core = 1;
                                else
                                    a->is_accurate = true;
                            }
                        }
                    }
                }

            }

            void zpl_affinity_destroy(zpl_affinity *a) {
                zpl_unused(a);
            }

            zpl_b32 zpl_affinity_set(zpl_affinity *a, zpl_isize core, zpl_isize thread_index) {
                zpl_isize index;
                thread_t thread;
                thread_affinity_policy_data_t info;
                kern_return_t result;

                ZPL_ASSERT(core < a->core_count);
                ZPL_ASSERT(thread_index < a->threads_per_core);

                index = core * a->threads_per_core + thread_index;
                thread = mach_thread_self();
                info.affinity_tag = cast(integer_t)index;
                result = thread_policy_set(thread, THREAD_AFFINITY_POLICY, cast(thread_policy_t)&info, THREAD_AFFINITY_POLICY_COUNT);
                return result == KERN_SUCCESS;
            }

            zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core) {
                ZPL_ASSERT(core >= 0 && core < a->core_count);
                return a->threads_per_core;
            }

        #elif defined(ZPL_SYSTEM_LINUX) || defined(ZPL_SYSTEM_FREEBSD) || defined(ZPL_SYSTEM_OPENBSD)

            // IMPORTANT TODO: This zpl_affinity stuff for linux needs be improved a lot!
            // NOTE(zangent): I have to read /proc/cpuinfo to get the number of threads per core.

            void zpl_affinity_init(zpl_affinity *a) {
                zpl_b32   accurate = true;
                zpl_isize threads = 0;

                a->thread_count     = 1;
                a->core_count       = sysconf(_SC_NPROCESSORS_ONLN);
                a->threads_per_core = 1;


                if(a->core_count <= 0) {
                    a->core_count = 1;
                    accurate = false;
                }

                // Parsing /proc/cpuinfo to get the number of threads per core.
                // NOTE(zangent): This calls the CPU's threads "cores", although the wording
                // is kind of weird. This should be right, though.
                FILE *cpu_info = fopen("/proc/cpuinfo", "r");
                if (cpu_info != NULL) {
                    for (;;) {
                        // The 'temporary char'. Everything goes into this char,
                        // so that we can check against EOF at the end of this loop.
                        int c;

            #define AF__CHECK(letter) ((c = getc(cpu_info)) == letter)
                        if (AF__CHECK('c') && AF__CHECK('p') && AF__CHECK('u') && AF__CHECK(' ') &&
                            AF__CHECK('c') && AF__CHECK('o') && AF__CHECK('r') && AF__CHECK('e') && AF__CHECK('s')) {
                            // We're on a CPU info line.
                            while (!AF__CHECK(EOF)) {
                                if (c == '\n') {
                                    break;
                                } else if (c < '0' || '9' > c) {
                                    continue;
                                }
                                threads = threads * 10 + (c - '0');
                            }
                            break;
                        } else {
                            while (!AF__CHECK('\n')) {
                                if (c==EOF) {
                                    break;
                                }
                            }
                        }
                        if (c == EOF) {
                            break;
                        }
            #undef AF__CHECK
                    }

                    fclose(cpu_info);
                }

                if (threads == 0) {
                    threads  = 1;
                    accurate = false;
                }

                a->threads_per_core = threads;
                a->thread_count = a->threads_per_core * a->core_count;
                a->is_accurate = accurate;

            }

            void zpl_affinity_destroy(zpl_affinity *a) {
                zpl_unused(a);
            }

            zpl_b32 zpl_affinity_set(zpl_affinity * a, zpl_isize core, zpl_isize thread_index) {
                zpl_unused(a);
                zpl_unused(core);
                zpl_unused(thread_index);
                return true;
            }

            zpl_isize zpl_affinity_thread_count_for_core(zpl_affinity *a, zpl_isize core) {
                ZPL_ASSERT(0 <= core && core < a->core_count);
                return a->threads_per_core;
            }

        #elif defined(ZPL_SYSTEM_EMSCRIPTEN)
            #error No affinity implementation for Emscripten
        #else
            #error TODO: Unknown system
        #endif

        ZPL_END_C_DECLS

        #if defined(ZPL_MODULE_JOBS)
            // file: source/jobs.c

            ///////////////////////////////////////////////////////////////
            //
            // Thread Pool
            //
            #ifdef ZPL_EDITOR
            #include <zpl.h>
            #endif

            ZPL_BEGIN_C_DECLS

            zpl_isize zpl__jobs_entry(struct zpl_thread *thread) {
                zpl_thread_worker *tw = (zpl_thread_worker *)thread->user_data;
                zpl_thread_pool *pool = (zpl_thread_pool *)tw->pool;

                for (;;) {
                    zpl_u32 status = zpl_atomic32_load(&tw->status);

                    switch (status) {
                        case ZPL_JOBS_STATUS_READY: {
                            zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_BUSY);

                            zpl_mutex_lock(&pool->access);
                            zpl_thread_job *job = pool->jobs + tw->jobid;
                            zpl_mutex_unlock(&pool->access);

                            job->proc(job->data);

                            zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_WAITING);
                        } break;

                        case ZPL_JOBS_STATUS_WAITING: {
                            zpl_yield( );
                        } break;

                        case ZPL_JOBS_STATUS_TERM: {
                            return 0;
                        } break;
                    }
                }

                return 0;
            }

            void zpl_jobs_init(zpl_thread_pool *pool, zpl_allocator a, zpl_u32 max_threads) {
                zpl_thread_pool pool_ = { 0 };
                *pool = pool_;
                zpl_mutex_init(&pool->access);

                pool->alloc = a;
                pool->max_threads = max_threads;

                // NOTE: Spawn a new job slot when number of available slots is below 25%
                // compared to the total number of slots.
                pool->job_spawn_treshold = 0.25;

                zpl_buffer_init(pool->workers, a, max_threads);
                zpl_array_init(pool->jobs, a);
                zpl_array_init(pool->queue, a);
                zpl_array_init(pool->available, a);

                for (zpl_usize i = 0; i < max_threads; ++i) {
                    zpl_thread_worker worker_ = { 0 };
                    zpl_thread_worker *tw = pool->workers + i;
                    *tw = worker_;

                    zpl_thread_init(&tw->thread);
                    zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_WAITING);
                    tw->pool = pool;
                    tw->jobid = ZPL_INVALID_JOB;
                    zpl_thread_start(&tw->thread, zpl__jobs_entry, (void *)tw);
                }
            }

            void zpl_jobs_free(zpl_thread_pool *pool) {
                for (zpl_usize i = 0; i < pool->max_threads; ++i) {
                    zpl_thread_worker *tw = pool->workers + i;

                    zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_TERM);
                    zpl_thread_destroy(&tw->thread);
                }

                zpl_buffer_free(pool->workers, pool->alloc);
                zpl_array_free(pool->jobs);
                zpl_array_free(pool->queue);
                zpl_array_free(pool->available);
            }

            void zpl_jobs_enqueue_with_priority(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data, zpl_i32 priority) {
                ZPL_ASSERT_NOT_NULL(proc);
                zpl_f32 treshold = 0.0f;

                if (zpl_array_count(pool->queue) > 0) {
                    treshold = (zpl_array_count(pool->available) / (zpl_f32)zpl_array_count(pool->jobs));
                }

                if (treshold <= pool->job_spawn_treshold) {
                    zpl_thread_job job = { 0 };
                    job.proc = proc;
                    job.data = data;
                    job.priority = priority;

                    zpl_array_append(pool->jobs, job);
                    zpl_u32 jobid = (zpl_u32)zpl_array_count(pool->jobs) - 1;
                    zpl_array_append(pool->queue, jobid);
                } else {
                    zpl_u32 jobid = zpl_array_back(pool->available);
                    zpl_thread_job *jp = pool->jobs + jobid;
                    zpl_array_pop(pool->available);

                    jp->proc = proc;
                    jp->data = data;
                    jp->priority = priority;

                    zpl_array_append(pool->queue, jobid);
                }
            }

            void zpl_jobs_enqueue(zpl_thread_pool *pool, zpl_jobs_proc proc, void *data) {
                ZPL_ASSERT_NOT_NULL(proc);
                zpl_jobs_enqueue_with_priority(pool, proc, data, 1);
            }

            zpl_thread_local zpl_thread_pool *zpl__thread_pool;

            ZPL_COMPARE_PROC(zpl___jobs_cmp) {
                zpl_thread_job *p = (zpl_thread_job *)(zpl__thread_pool->jobs + *(zpl_u32 *)a);
                zpl_thread_job *q = (zpl_thread_job *)(zpl__thread_pool->jobs + *(zpl_u32 *)b);
                return p->priority < q->priority ? 1 : p->priority > q->priority;
            }

            ZPL_COMPARE_PROC_PTR(zpl__jobs_cmp(zpl_thread_pool *pool)) {
                zpl__thread_pool = pool;
                return &zpl___jobs_cmp;
            }

            zpl_b32 zpl_jobs_process(zpl_thread_pool *pool) {
                // NOTE: Sort the queue based on the job priority
                if (zpl_array_count(pool->queue)) {
                    zpl_sort_array(pool->queue, zpl_array_count(pool->queue), zpl__jobs_cmp(pool));
                }

                // NOTE: Process the jobs
                for (zpl_usize i = 0; i < pool->max_threads; ++i) {
                    zpl_thread_worker *tw = pool->workers + i;
                    if (zpl_array_count(pool->queue) == 0) return false;

                    zpl_u32 status = zpl_atomic32_load(&tw->status);

                    if (status == ZPL_JOBS_STATUS_WAITING) {
                        if (tw->jobid != ZPL_INVALID_JOB) { zpl_array_append(pool->available, tw->jobid); }

                        zpl_u32 jobid = *pool->queue;
                        zpl_array_remove_at(pool->queue, 0);
                        tw->jobid = jobid;
                        zpl_atomic32_store(&tw->status, ZPL_JOBS_STATUS_READY);
                    }
                }

                return true;
            }

            ZPL_END_C_DECLS
        #endif

        #if defined(ZPL_MODULE_COROUTINES)
            // file: source/coroutines.c

            ////////////////////////////////////////////////////////////////
            //
            // Coroutines
            //
            //
            #ifdef ZPL_EDITOR
            #include <zpl.h>
            #endif

            ZPL_BEGIN_C_DECLS

            struct {
                zpl_b32 is_ready;
                zpl_thread_pool coroutines;
                zpl_thread runner;
                zpl_atomic32 request_term;
                zpl_mutex is_processing;
            } zpl__co_internals;

            zpl_thread_local zpl_u8 zpl__co_yield_barrier;

            zpl_isize zpl__co_runner(struct zpl_thread *t) {
                do {
                    if (zpl_atomic32_load(&zpl__co_internals.request_term))
                        break;

                    zpl_b32 lock = zpl_mutex_try_lock(&zpl__co_internals.is_processing);

                    while (!lock) {
                        zpl_yield_thread();
                        lock = zpl_mutex_try_lock(&zpl__co_internals.is_processing);

                        if (zpl_atomic32_load(&zpl__co_internals.request_term))
                            break;

                        zpl_mfence();
                    }

                    zpl_jobs_process(&zpl__co_internals.coroutines);
                    zpl_mutex_unlock(&zpl__co_internals.is_processing);
                } while (1);

                return 0;
            }

            void zpl__co_job(void *data) {
                zpl_co *co = cast(zpl_co *)data;

                zpl_atomic32_store(&co->status, ZPL_CO_RUNNING);
                co->f(co);
                zpl_atomic32_store(&co->status, ZPL_CO_DEAD);
            }

            void zpl_co_init(zpl_allocator a, zpl_u32 max_threads) {
                if (!zpl__co_internals.is_ready) {
                    zpl_zero_item(&zpl__co_internals);
                    zpl_mutex_init(&zpl__co_internals.is_processing);
                    zpl_jobs_init(&zpl__co_internals.coroutines, a, max_threads);
                    zpl_thread_init(&zpl__co_internals.runner);
                    zpl_thread_start(&zpl__co_internals.runner, zpl__co_runner, NULL);
                    zpl_atomic32_store(&zpl__co_internals.request_term, 0);
                    zpl__co_internals.is_ready = 1;

                    // Set up a barrier so that we won't let user call zpl_co_yield in a main thread.
                    zpl__co_yield_barrier = 1;
                }
            }

            void zpl_co_destroy(void) {
                zpl_atomic32_exchange(&zpl__co_internals.request_term, 1);
                zpl_thread_destroy(&zpl__co_internals.runner);
                zpl_mutex_destroy(&zpl__co_internals.is_processing);
                zpl_jobs_free(&zpl__co_internals.coroutines);
                zpl__co_internals.is_ready = 0;
                zpl_mfence();
            }

            void zpl_co_make(zpl_co *co, zpl_co_proc f) {
                ZPL_ASSERT_MSG(zpl__co_internals.is_ready, "Coroutines module is not initialized. Call zpl_co_init first!");
                ZPL_ASSERT_NOT_NULL(co);

                co->f = f;
                zpl_atomic32_store(&co->status, ZPL_CO_READY);
                zpl_atomic32_store(&co->resume, 0);
            }

            void zpl_co_resume(zpl_co *co, void *data) {
                ZPL_ASSERT_NOT_NULL(co);

                if (data != NULL) {
                    zpl_atomic32_store(&co->push_arg, 1);
                    co->data_stack[co->data_write_idx++] = data;
                    zpl_atomic32_spin_unlock(&co->push_arg);
                    zpl_mfence();
                }

                zpl_i32 status = zpl_atomic32_load(&co->status);

                // Initialize a job
                if (status == ZPL_CO_READY) {

                    if (data)
                        co->data = co->data_stack[co->data_read_idx++];

                    zpl_atomic32_store(&co->status, ZPL_CO_ENQUEUED);
                    zpl_mfence();

                    zpl_mutex_lock(&zpl__co_internals.is_processing);
                    zpl_jobs_enqueue(&zpl__co_internals.coroutines, zpl__co_job, cast(void *)co);
                    zpl_mutex_unlock(&zpl__co_internals.is_processing);
                }
                else {
                    zpl_atomic32_fetch_add(&co->resume, 1);
                    zpl_mfence();
                }
            }

            void zpl_co_yield(zpl_co *co) {
                zpl_i32 value;
                ZPL_ASSERT_NOT_NULL(co);
                ZPL_ASSERT_MSG((!zpl__co_yield_barrier), "zpl_co_yield can only be called inside of coroutines!");

                zpl_atomic32_store(&co->status, ZPL_CO_WAITING);

                value = zpl_atomic32_load(&co->resume);

                while (value == 0) {
                    zpl_yield_thread();
                    value = zpl_atomic32_load(&co->resume);
                    zpl_mfence();
                }

                zpl_atomic32_spin_lock(&co->push_arg, -1);
                co->data = co->data_stack[co->data_read_idx++];

                // null pointer is present, no arg is found, so return back by 1 index
                if (co->data == NULL) {
                    co->data_read_idx--;
                }

                zpl_atomic32_spin_unlock(&co->push_arg);

                zpl_atomic32_store(&co->status, ZPL_CO_RUNNING);
                zpl_atomic32_fetch_add(&co->resume, -1);
            }

            ZPL_END_C_DECLS
        #endif
    #endif


    #if defined(ZPL_COMPILER_MSVC)
        #pragma warning(pop)
    #endif

    #if defined(__GCC__) || defined(__GNUC__) || defined(__clang__)
        #pragma GCC diagnostic pop
    #endif

    #endif // ZPL_IMPLEMENTATION

    #if !defined(ZPL_PREFIX_TYPES)
        typedef zpl_u8 u8;
        typedef zpl_i8 i8;
        typedef zpl_u16 u16;
        typedef zpl_i16 i16;
        typedef zpl_u32 u32;
        typedef zpl_i32 i32;
        typedef zpl_u64 u64;
        typedef zpl_i64 i64;
        typedef zpl_b8 b8;
        typedef zpl_b16 b16;
        typedef zpl_b32 b32;
        typedef zpl_f32 f32;
        typedef zpl_f64 f64;
        typedef zpl_rune rune;
        typedef zpl_usize usize;
        typedef zpl_isize isize;
        typedef zpl_uintptr uintptr;
        typedef zpl_intptr intptr;
    #endif // ZPL_PREFIX_TYPES

    #endif // ZPL_H

    // TOC:
    // zpl.h
    // zpl_hedley.h
    // header/core/system.h
    // header/core/types.h
    // header/core/helpers.h
    // header/core/debug.h
    // header/core/memory.h
    // header/core/memory_virtual.h
    // header/core/memory_custom.h
    // header/core/collections/array.h
    // header/core/collections/buffer.h
    // header/core/collections/list.h
    // header/core/collections/ring.h
    // header/core/collections/hashtable.h
    // header/core/string.h
    // header/core/stringlib.h
    // header/core/file.h
    // header/core/filesystem.h
    // header/core/print.h
    // header/core/time.h
    // header/core/random.h
    // header/core/misc.h
    // header/core/sort.h
    // header/timer.h
    // header/hashing.h
    // header/regex.h
    // header/event.h
    // header/dll.h
    // header/opts.h
    // header/process.h
    // header/math.h
    // header/json.h
    // header/threading/atomic.h
    // header/threading/fence.h
    // header/threading/sem.h
    // header/threading/mutex.h
    // header/threading/thread.h
    // header/threading/sync.h
    // header/threading/affinity.h
    // header/jobs.h
    // header/coroutines.h
    // source/core/debug.c
    // source/core/memory.c
    // source/core/memory_virtual.c
    // source/core/memory_custom.c
    // source/core/array.c
    // source/core/string.c
    // source/core/stringlib.c
    // source/core/file.c
    // source/core/filesystem.c
    // source/core/print.c
    // source/core/time.c
    // source/core/random.c
    // source/core/misc.c
    // source/core/sort.c
    // source/timer.c
    // source/hashing.c
    // source/regex.c
    // source/event.c
    // source/dll.c
    // source/opts.c
    // source/process.c
    // source/math.c
    // source/json.c
    // source/threading/atomic.c
    // source/threading/fence.c
    // source/threading/sem.c
    // source/threading/mutex.c
    // source/threading/thread.c
    // source/threading/sync.c
    // source/threading/affinity.c
    // source/jobs.c
    // source/coroutines.c
#endif

// file: source/types.c

#ifdef LIBRG_EDITOR
#include <librg.h>
#include <zpl.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Macro based helpers, and functions available for redefintion
// !
// =======================================================================//

/* allows to define a custom allocator */
#ifndef LIBRG_MEM_ALLOC
#define LIBRG_MEM_ALLOC(size) zpl_malloc(size)
#endif

/* allows to define a custom de-allocator */
#ifndef LIBRG_MEM_FREE
#define LIBRG_MEM_FREE(ptr) zpl_mfree(ptr)
#endif

/* allows to define a custom assert handler */
#ifndef LIBRG_ASSERT
#if defined(_DEBUG) || defined(LIBRG_DEBUG)
#define LIBRG_ASSERT(x) ZPL_ASSERT(x)
#else
#define LIBRG_ASSERT(x)
#endif
#endif

#ifndef LIBRG_MIN
#define LIBRG_MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef LIBRG_MAX
#define LIBRG_MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

// =======================================================================//
// !
// ! Compile-time static configuration settings
// !
// =======================================================================//


/* defines how many max chunks an entity */
/* can be located in simultaneously */
#ifndef LIBRG_ENTITY_MAXCHUNKS
#define LIBRG_ENTITY_MAXCHUNKS 8
#endif

/* defines how many max entity ids could be used  */
/* inside of the librg_world_write call */
#ifndef LIBRG_WORLDWRITE_MAXQUERY
#define LIBRG_WORLDWRITE_MAXQUERY 16384
#endif

/* validate that value is less than maximum allowed */
#if LIBRG_WORLDWRITE_MAXQUERY > ZPL_U16_MAX
#error "LIBRG_WORLDWRITE_MAXQUERY must have value less than 65535"
#endif

// =======================================================================//
// !
// ! Internal data structures
// !
// =======================================================================//

ZPL_TABLE(static inline, librg_table_i8, librg_table_i8_, int8_t);
ZPL_TABLE(static inline, librg_table_i64, librg_table_i64_, int64_t);
ZPL_TABLE(static inline, librg_table_tbl, librg_table_tbl_, librg_table_i64);

enum  {
    LIBRG_WRITE_OWNER = (LIBRG_ERROR_REMOVE+1),
    LIBRG_READ_OWNER,
    LIBRG_ERROR_OWNER,
    LIBRG_PACKAGING_TOTAL,
};

typedef struct librg_entity_t {
    uint8_t type : 2;
    uint8_t visibility_global : 2;
    uint8_t flag_owner_updated : 1;
    uint8_t flag_foreign : 1;
    uint8_t flag_visbility_owner_enabled : 1;
    uint8_t flag_unused2 : 1;

    int8_t observed_radius;
    uint16_t ownership_token;

    int32_t dimension;
    int64_t owner_id;

    librg_chunk chunks[LIBRG_ENTITY_MAXCHUNKS];
    librg_table_i8 owner_visibility_map;

    void *userdata;
} librg_entity_t;

ZPL_TABLE(static inline, librg_table_ent, librg_table_ent_, librg_entity_t);

typedef struct librg_event_t {
    uint8_t     type;           /* type of the event that was called, might be useful in bindings */
    int64_t     owner_id;       /* id of the owner who this event is called for */
    int64_t     entity_id;      /* id of an entity which this event is called about */
    char      * buffer;         /* ptr to the buffer data */
    size_t      size;           /* depending on the event type, can show maximum amount of data you are able to write, or amount of data you can read */
    void      * userdata;       /* userpointer that is passed from librg_world_write/librg_world_read fns */
} librg_event_t;

typedef struct librg_world_t {
    uint8_t valid;
    zpl_allocator allocator;
    zpl_random random;

    struct { uint16_t x, y, z; } worldsize;
    struct { uint16_t x, y, z; } chunksize;
    struct { int16_t x, y, z; } chunkoffset;

    librg_event_fn handlers[LIBRG_PACKAGING_TOTAL];
    librg_table_ent entity_map;
    librg_table_tbl owner_map;

    void *userdata;
} librg_world_t;

/* unsued */

// #define LIBRG_OBSERVE_ALL               (-0x01)
// #define LIBRG_OBSERVE_NONE              (+0x00)

// typedef enum librg_entity_refreshing {
//     LIBRG_CONSTANT,     /* int argument, update entity every Nth tick */
//     LIBRG_LINEAR,       /* float argument, linearly decrease update interval based on distance step (argument) */
//     LIBRG_QUADRATIC,    /* float argument, cubicly decrease update inverval based on distance step (argument) */
// } librg_entity_refreshing;

// typedef enum {
//     LIBRG_ENTITY_DYNAMIC,
//     LIBRG_ENTITY_STATIC,
// } librg_behavior_type;

// typedef enum {
//     LIBRG_BEHAVIOR_TYPE,
//     LIBRG_BEHAVIOR_STEPBACK,
// } librg_behavior;

LIBRG_END_C_DECLS
// file: source/context.c

#ifdef LIBRG_EDITOR
#include <librg.h>
#include <zpl.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Custom internal zpl alloc proc hanlders
// !
// =======================================================================//

LIBRG_PRIVATE zpl_allocator librg_alloc_wrap();

ZPL_ALLOCATOR_PROC(librg_allocator_proc) {
    void *ptr = NULL;

    zpl_unused(allocator_data);
    zpl_unused(old_size);
    zpl_unused(flags);

    switch (type) {
        case ZPL_ALLOCATION_ALLOC:  { ptr = LIBRG_MEM_ALLOC(size); } break;
        case ZPL_ALLOCATION_FREE:   { LIBRG_MEM_FREE(old_memory); } break;
        case ZPL_ALLOCATION_RESIZE: { ptr = zpl_default_resize_align(librg_alloc_wrap(), old_memory, old_size, size, alignment); } break;
        case ZPL_ALLOCATION_FREE_ALL: break;
    }

    return ptr;
}

LIBRG_PRIVATE zpl_allocator librg_alloc_wrap() {
    zpl_allocator a = {0};
    a.proc = librg_allocator_proc;
    a.data = NULL;
    return a;
}

// =======================================================================//
// !
// ! Context methods
// !
// =======================================================================//

uint32_t librg_version() {
    return LIBRG_VERSION;
}

librg_world *librg_world_create() {
    librg_world_t *wld = LIBRG_MEM_ALLOC(sizeof(librg_world_t));
    zpl_memset(wld, 0, sizeof(librg_world_t));

    /* setup initials */
    wld->valid = LIBRG_TRUE;
    wld->allocator = librg_alloc_wrap();

    /* setup defaults */
    librg_config_chunksize_set((librg_world *)wld, 16, 16, 16);
    librg_config_chunkamount_set((librg_world *)wld, 256, 256, 256);
    librg_config_chunkoffset_set((librg_world *)wld, LIBRG_OFFSET_MID, LIBRG_OFFSET_MID, LIBRG_OFFSET_MID);

    /* initialize internal structs */
    librg_table_ent_init(&wld->entity_map, wld->allocator);
    librg_table_tbl_init(&wld->owner_map, wld->allocator);
    zpl_random_init(&wld->random);

    return (librg_world *)wld;
}

int8_t librg_world_destroy(librg_world *world) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    {/* free up entities */
        for (int i = 0; i < zpl_array_count(wld->entity_map.entries); ++i) {
            librg_entity_t *entity = &wld->entity_map.entries[i].value;

            if (entity->flag_visbility_owner_enabled) {
                entity->flag_visbility_owner_enabled = LIBRG_FALSE;
                librg_table_i8_destroy(&entity->owner_visibility_map);
            }
        }

        librg_table_ent_destroy(&wld->entity_map);
    }

    {/* free up owners */
        for (int i = 0; i < zpl_array_count(wld->owner_map.entries); ++i)
            librg_table_i64_destroy(&wld->owner_map.entries[i].value);

        librg_table_tbl_destroy(&wld->owner_map);
    }

    /* mark it invalid */
    wld->valid = LIBRG_FALSE;

    LIBRG_MEM_FREE(world);
    return LIBRG_OK;
}

int8_t librg_world_valid(librg_world *world) {
    if (!world) return LIBRG_FALSE;
    librg_world_t *wld = (librg_world_t *)world;
    return wld->valid;
}

int8_t librg_world_userdata_set(librg_world *world, void *data) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    wld->userdata = data;
    return LIBRG_OK;
}

void *librg_world_userdata_get(librg_world *world) {
    LIBRG_ASSERT(world); if (!world) return NULL;
    librg_world_t *wld = (librg_world_t *)world;
    return wld->userdata;
}

// =======================================================================//
// !
// ! Runtime configuration
// !
// =======================================================================//

int8_t librg_config_chunkamount_set(librg_world *world, uint16_t x, uint16_t y, uint16_t z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    wld->worldsize.x = x == 0 ? 1 : x;
    wld->worldsize.y = y == 0 ? 1 : y;
    wld->worldsize.z = z == 0 ? 1 : z;
    return LIBRG_OK;
}

int8_t librg_config_chunkamount_get(librg_world *world, uint16_t *x, uint16_t *y, uint16_t *z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    *x = wld->worldsize.x;
    *y = wld->worldsize.y;
    *z = wld->worldsize.z;
    return LIBRG_OK;
}

int8_t librg_config_chunksize_set(librg_world *world, uint16_t x, uint16_t y, uint16_t z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    wld->chunksize.x = x;
    wld->chunksize.y = y;
    wld->chunksize.z = z;
    return LIBRG_OK;
}

int8_t librg_config_chunksize_get(librg_world *world, uint16_t *x, uint16_t *y, uint16_t *z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    *x = wld->chunksize.x;
    *y = wld->chunksize.y;
    *z = wld->chunksize.z;
    return LIBRG_OK;
}

int8_t librg_config_chunkoffset_set(librg_world *world, int16_t x, int16_t y, int16_t z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    wld->chunkoffset.x = x;
    wld->chunkoffset.y = y;
    wld->chunkoffset.z = z;
    return LIBRG_OK;
}

int8_t librg_config_chunkoffset_get(librg_world *world, int16_t *x, int16_t *y, int16_t *z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    *x = wld->chunkoffset.x;
    *y = wld->chunkoffset.y;
    *z = wld->chunkoffset.z;
    return LIBRG_OK;
}

// =======================================================================//
// !
// ! Events
// !
// =======================================================================//

int8_t librg_event_set(librg_world *world, librg_event_type id, librg_event_fn handler) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    if (wld->handlers[id]) {
        wld->handlers[id] = handler;
        return LIBRG_HANDLER_REPLACED;
    }

    wld->handlers[id] = handler;
    return LIBRG_OK;
}

int8_t librg_event_remove(librg_world *world, librg_event_type id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    if (!wld->handlers[id]) {
        return LIBRG_HANDLER_EMPTY;
    }

    wld->handlers[id] = NULL;
    return LIBRG_OK;
}

librg_event_type librg_event_type_get(librg_world *world, librg_event *event) {
    LIBRG_ASSERT(event); if (!event) return LIBRG_EVENT_INVALID;
    zpl_unused(world);
    librg_event_t *e = (librg_event_t*)event;
    return e->type;
}

int64_t librg_event_owner_get(librg_world *world, librg_event *event) {
    LIBRG_ASSERT(event); if (!event) return LIBRG_EVENT_INVALID;
    zpl_unused(world);
    librg_event_t *e = (librg_event_t*)event;
    return e->owner_id;
}

int64_t librg_event_entity_get(librg_world *world, librg_event *event) {
    LIBRG_ASSERT(event); if (!event) return LIBRG_EVENT_INVALID;
    zpl_unused(world);
    librg_event_t *e = (librg_event_t*)event;
    return e->entity_id;
}

char * librg_event_buffer_get(librg_world *world, librg_event *event) {
    LIBRG_ASSERT(event); if (!event) return NULL;
    zpl_unused(world);
    librg_event_t *e = (librg_event_t*)event;
    return e->buffer;
}

int32_t librg_event_size_get(librg_world *world, librg_event *event) {
    LIBRG_ASSERT(event); if (!event) return LIBRG_EVENT_INVALID;
    zpl_unused(world);
    librg_event_t *e = (librg_event_t*)event;
    return e->size;
}

void * librg_event_userdata_get(librg_world *world, librg_event *event) {
    LIBRG_ASSERT(event); if (!event) return NULL;
    zpl_unused(world);
    librg_event_t *e = (librg_event_t*)event;
    return e->userdata;
}

// =======================================================================//
// !
// ! Utitilites
// !
// =======================================================================//

LIBRG_ALWAYS_INLINE int16_t librg_util_chunkoffset_line(int16_t v, int16_t off, int16_t size) {
    int16_t o = 0;
    if (off == LIBRG_OFFSET_BEG) o = 0;
    if (off == LIBRG_OFFSET_MID) o = (size/2);
    if (off == LIBRG_OFFSET_END) o = (size-1);
    return v + o;
}

librg_chunk librg_chunk_from_chunkpos(librg_world *world, int16_t chunk_x, int16_t chunk_y, int16_t chunk_z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    int16_t chx = librg_util_chunkoffset_line(chunk_x, wld->chunkoffset.x, wld->worldsize.x);
    int16_t chy = librg_util_chunkoffset_line(chunk_y, wld->chunkoffset.y, wld->worldsize.y);
    int16_t chz = librg_util_chunkoffset_line(chunk_z, wld->chunkoffset.z, wld->worldsize.z);

    librg_chunk id = (chz * wld->worldsize.y * wld->worldsize.z) + (chy * wld->worldsize.y) + (chx);

    if (id < 0 || id > (wld->worldsize.x * wld->worldsize.y * wld->worldsize.z)) {
        return LIBRG_CHUNK_INVALID;
    }

    return id;
}

int8_t librg_chunk_to_chunkpos(librg_world *world, librg_chunk id, int16_t *chunk_x, int16_t *chunk_y, int16_t *chunk_z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    if (id < 0 || id > (wld->worldsize.x * wld->worldsize.y * wld->worldsize.z)) {
        return LIBRG_CHUNK_INVALID;
    }

    int16_t z = (int16_t)(id / (wld->worldsize.z * wld->worldsize.y));
    int16_t r1 = (int16_t)(id % (wld->worldsize.z * wld->worldsize.y));
    int16_t y = r1 / wld->worldsize.y;
    int16_t x = r1 % wld->worldsize.y;

    *chunk_x = x - librg_util_chunkoffset_line(0, wld->chunkoffset.x, wld->worldsize.x);
    *chunk_y = y - librg_util_chunkoffset_line(0, wld->chunkoffset.y, wld->worldsize.y);
    *chunk_z = z - librg_util_chunkoffset_line(0, wld->chunkoffset.z, wld->worldsize.z);

    return LIBRG_OK;
}

librg_chunk librg_chunk_from_realpos(librg_world *world, double x, double y, double z) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    return librg_chunk_from_chunkpos(world, (int16_t)(x/wld->chunksize.x), (int16_t)(y/wld->chunksize.y), (int16_t)(z/wld->chunksize.z));
}

LIBRG_END_C_DECLS
// file: source/entity.c

#ifdef LIBRG_EDITOR
#include <librg.h>
#include <zpl.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Basic entity manipulation
// !
// =======================================================================//

int8_t librg_entity_track(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    if (librg_entity_tracked(world, entity_id) == LIBRG_TRUE) {
        return LIBRG_ENTITY_ALREADY_TRACKED;
    }

    if (entity_id < 0 || entity_id > ZPL_I64_MAX) {
        return LIBRG_ENTITY_INVALID;
    }

    librg_entity_t _entity = {0};
    librg_table_ent_set(&wld->entity_map, entity_id, _entity);

    /* set defaults */
    librg_entity_chunk_set(world, entity_id, LIBRG_CHUNK_INVALID);
    librg_entity_owner_set(world, entity_id, LIBRG_OWNER_INVALID);

    return LIBRG_OK;
}

int8_t librg_entity_untrack(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);

    if (!entity) {
        return LIBRG_ENTITY_UNTRACKED;
    }

    if (entity->flag_foreign == LIBRG_TRUE) {
        return LIBRG_ENTITY_FOREIGN;
    }

    /* cleanup owner snapshots */
    if (entity->owner_id != LIBRG_OWNER_INVALID) {
        size_t owned = 0;
        size_t total = zpl_array_count(wld->entity_map.entries);

        /* count already owned entities by this user */
        for (size_t i=0; i<total; i++) {
            if (librg_entity_owner_get(world, wld->entity_map.entries[i].key) == entity->owner_id)
                owned++;
        }

        librg_table_i64 *snapshot = librg_table_tbl_get(&wld->owner_map, entity->owner_id);

        /* free up our snapshot storage, if owner does not own other entities (except current one) */
        if (snapshot && owned <= 1) {
            librg_table_i64_destroy(snapshot);
            librg_table_tbl_remove(&wld->owner_map, entity->owner_id);
        }
    }

    /* cleanup owner visibility */
    if (entity->flag_visbility_owner_enabled) {
        entity->flag_visbility_owner_enabled = LIBRG_FALSE;
        librg_table_i8_destroy(&entity->owner_visibility_map);
    }

    librg_table_ent_remove(&wld->entity_map, entity_id);
    return LIBRG_OK;
}

int8_t librg_entity_tracked(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_FALSE;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    return entity == NULL ? LIBRG_FALSE : LIBRG_TRUE;
}

int8_t librg_entity_foreign(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_FALSE;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_FALSE;

    return entity->flag_foreign == LIBRG_TRUE;
}

int32_t librg_entity_count(librg_world *world) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    return (int32_t)zpl_array_count(wld->entity_map.entries);
}

// =======================================================================//
// !
// ! Main entity data methods
// !
// =======================================================================//

int8_t librg_entity_chunk_set(librg_world *world, int64_t entity_id, librg_chunk chunk) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    for (int i = 0; i < LIBRG_ENTITY_MAXCHUNKS; ++i) entity->chunks[i] = LIBRG_CHUNK_INVALID;
    entity->chunks[0] = chunk;

    return LIBRG_OK;
}

librg_chunk librg_entity_chunk_get(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->chunks[0];
}

int8_t librg_entity_owner_set(librg_world *world, int64_t entity_id, int64_t owner_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    if (entity->flag_foreign == LIBRG_TRUE) {
        return LIBRG_ENTITY_FOREIGN;
    }

    entity->owner_id = owner_id;
    entity->flag_owner_updated = LIBRG_TRUE;

    if (entity->owner_id != LIBRG_OWNER_INVALID) {
        /* set new token, and make sure to prevent collisions */
        uint16_t newtoken = 0;
        do { newtoken = (uint16_t)(zpl_random_gen_u32(&wld->random) % ZPL_U16_MAX); }
        while (newtoken == 0 || newtoken == entity->ownership_token);
        entity->ownership_token = newtoken;

        /* fetch or create a new subtable */
        librg_table_i64 *snapshot = librg_table_tbl_get(&wld->owner_map, owner_id);

        if (!snapshot) {
            librg_table_i64 _i64 = {0};
            librg_table_tbl_set(&wld->owner_map, owner_id, _i64);
            snapshot = librg_table_tbl_get(&wld->owner_map, owner_id);
            librg_table_i64_init(snapshot, wld->allocator);
        }
    } else {
        entity->ownership_token = 0;
    }

    return LIBRG_OK;
}

int64_t librg_entity_owner_get(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->owner_id;
}


int8_t librg_entity_radius_set(librg_world *world, int64_t entity_id, int8_t observed_chunk_radius) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->observed_radius = observed_chunk_radius;
    return LIBRG_OK;
}

int8_t librg_entity_radius_get(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->observed_radius;
}

int8_t librg_entity_dimension_set(librg_world *world, int64_t entity_id, int32_t dimension) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->dimension = dimension;
    return LIBRG_OK;
}

int32_t librg_entity_dimension_get(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->dimension;
}

int8_t librg_entity_userdata_set(librg_world *world, int64_t entity_id, void *data) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->userdata = data;
    return LIBRG_OK;
}

void *librg_entity_userdata_get(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return NULL;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return NULL;

    return entity->userdata;
}

int8_t librg_entity_chunkarray_set(librg_world *world, int64_t entity_id, const librg_chunk *values, size_t chunk_amount) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    LIBRG_ASSERT(chunk_amount > 0 && chunk_amount < LIBRG_ENTITY_MAXCHUNKS);

    for (int i = 0; i < LIBRG_ENTITY_MAXCHUNKS; ++i) entity->chunks[i] = LIBRG_CHUNK_INVALID;
    zpl_memcopy(entity->chunks, values, sizeof(librg_chunk) * LIBRG_MIN(chunk_amount, LIBRG_ENTITY_MAXCHUNKS));

    return LIBRG_OK;

}

int8_t librg_entity_chunkarray_get(librg_world *world, int64_t entity_id, librg_chunk *results, size_t *chunk_amount) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    LIBRG_ASSERT(results);
    size_t count = 0;
    size_t buffer_limit = *chunk_amount;

    for (size_t i = 0; i < LIBRG_MIN(buffer_limit, LIBRG_ENTITY_MAXCHUNKS); ++i) {
        if (entity->chunks[i] != LIBRG_CHUNK_INVALID) {
            results[count++] = entity->chunks[i];
        }
    }

    *chunk_amount = count;
    return (int8_t)(LIBRG_ENTITY_MAXCHUNKS - buffer_limit);
}


int8_t librg_entity_visibility_global_set(librg_world *world, int64_t entity_id, librg_visibility value) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    entity->visibility_global = value;

    return LIBRG_OK;
}

int8_t librg_entity_visibility_global_get(librg_world *world, int64_t entity_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    return entity->visibility_global;
}

int8_t librg_entity_visibility_owner_set(librg_world *world, int64_t entity_id, int64_t owner_id, librg_visibility value) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    /* prevent setting visiblity, for your own entity, it will be always visible */
    if (entity->owner_id == owner_id) {
        return LIBRG_ENTITY_VISIBILITY_IGNORED;
    }

    if (!entity->flag_visbility_owner_enabled) {
        entity->flag_visbility_owner_enabled = LIBRG_TRUE;
        librg_table_i8_init(&entity->owner_visibility_map, wld->allocator);
    }

    librg_table_i8_set(&entity->owner_visibility_map, owner_id, value);

    return LIBRG_OK;
}

int8_t librg_entity_visibility_owner_get(librg_world *world, int64_t entity_id, int64_t owner_id) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
    if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

    if (!entity->flag_visbility_owner_enabled)
        return LIBRG_VISIBLITY_DEFAULT;

    int8_t *value = librg_table_i8_get(&entity->owner_visibility_map, owner_id);
    return (value ? *value : LIBRG_VISIBLITY_DEFAULT);
}

#if 0
// int8_t librg_entity_type_set(librg_world *world, int64_t entity_id, uint8_t type) {
//     LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
//     librg_world_t *wld = (librg_world_t *)world;

//     librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
//     if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

//     entity->type = type;
//     return LIBRG_OK;
// }

// int16_t librg_entity_type_get(librg_world *world, int64_t entity_id) {
//     LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
//     librg_world_t *wld = (librg_world_t *)world;

//     librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, entity_id);
//     if (entity == NULL) return LIBRG_ENTITY_UNTRACKED;

//     return entity->type;
// }



int librg_entity_refresh_set(librg_world *, int64_t entity_id, int type, float value); // ? {
    return LIBRG_OK
}

int librg_entity_refresh_get(librg_world *, int64_t entity_id, int *type, float *value) {
    return LIBRG_OK
}
// TODO: entity visibility

#endif

LIBRG_END_C_DECLS
// file: source/world.c

#ifdef LIBRG_EDITOR
#include <librg.h>
#include <zpl.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Simple general fetching methods
// !
// =======================================================================//

int32_t librg_world_fetch_all(librg_world *world, int64_t *entity_ids, size_t *entity_amount) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    LIBRG_ASSERT(entity_amount); if (!entity_amount) return LIBRG_NULL_REFERENCE;
    librg_world_t *wld = (librg_world_t *)world;

    size_t count = 0;
    size_t buffer_limit = *entity_amount;
    size_t total_count = zpl_array_count(wld->entity_map.entries);

    for (size_t i=0; i < LIBRG_MIN(buffer_limit, total_count); ++i) {
        entity_ids[count++] = wld->entity_map.entries[i].key;
    }

    *entity_amount = count;
    return LIBRG_MAX(0, (int32_t)(total_count - buffer_limit));
}

int32_t librg_world_fetch_chunk(librg_world *world, librg_chunk chunk, int64_t *entity_ids, size_t *entity_amount) {
    return librg_world_fetch_chunkarray(world, (librg_chunk[]){chunk}, 1, entity_ids, entity_amount);
}

int32_t librg_world_fetch_chunkarray(librg_world *world, const librg_chunk *chunks, size_t chunk_amount, int64_t *entity_ids, size_t *entity_amount) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    LIBRG_ASSERT(entity_amount); if (!entity_amount) return LIBRG_NULL_REFERENCE;
    librg_world_t *wld = (librg_world_t *)world;

    size_t count = 0;
    size_t iterated = 0;
    size_t buffer_limit = *entity_amount;
    size_t total_count = zpl_array_count(wld->entity_map.entries);

    for (size_t i=0; i < LIBRG_MIN(buffer_limit, total_count); ++i) {
        uint64_t entity_id = wld->entity_map.entries[i].key;
        librg_entity_t *entity = &wld->entity_map.entries[i].value;
        iterated++;

        for (size_t k = 0; k < chunk_amount; ++k) {
            librg_chunk chunk = chunks[k];

            for (size_t j=0; j < LIBRG_ENTITY_MAXCHUNKS; ++j) {
                if (entity->chunks[j] == chunk) {
                    entity_ids[count++] = entity_id;
                    break;
                }

                /* immidiately exit if chunk is invalid (the rest will also be invalid) */
                if (entity->chunks[j] == LIBRG_CHUNK_INVALID) {
                    break;
                }
            }
        }
    }

    *entity_amount = count;
    return LIBRG_MAX(0, (int32_t)(total_count - iterated));
}

int32_t librg_world_fetch_owner(librg_world *world, int64_t owner_id, int64_t *entity_ids, size_t *entity_amount) {
    return librg_world_fetch_ownerarray(world, (int64_t[]){owner_id}, 1, entity_ids, entity_amount);
}

int32_t librg_world_fetch_ownerarray(librg_world *world, const int64_t *owner_ids, size_t owner_amount, int64_t *entity_ids, size_t *entity_amount) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    LIBRG_ASSERT(entity_amount); if (!entity_amount) return LIBRG_NULL_REFERENCE;
    librg_world_t *wld = (librg_world_t *)world;

    size_t count = 0;
    size_t iterated = 0;
    size_t buffer_limit = *entity_amount;
    size_t total_count = zpl_array_count(wld->entity_map.entries);

    for (size_t i=0; i < LIBRG_MIN(buffer_limit, total_count); ++i) {
        uint64_t entity_id = wld->entity_map.entries[i].key;
        librg_entity_t *entity = &wld->entity_map.entries[i].value;
        iterated++;

        for (size_t k = 0; k < owner_amount; ++k) {
            int64_t owner_id = owner_ids[k];
            if (entity->owner_id == owner_id) entity_ids[count++] = entity_id;
        }
    }

    *entity_amount = count;
    return LIBRG_MAX(0, (int32_t)(total_count - iterated));
}

// =======================================================================//
// !
// ! Main owner entity query method
// !
// =======================================================================//

static LIBRG_ALWAYS_INLINE void librg_util_chunkrange(librg_world *w, librg_table_i64 *ch, int cx, int cy, int cz, int8_t radius) {
    int radius2 = radius * radius;

    for (int z=-radius; z<=radius; z++) {
        for (int y=-radius; y<=radius; y++) {
            for (int x=-radius; x<=radius; x++) {
                if(x*x+y*y+z*z <= radius2) {
                    librg_chunk id = librg_chunk_from_chunkpos(w, cx+x, cy+y, cz+z);
                    if (id != LIBRG_CHUNK_INVALID) librg_table_i64_set(ch, id, 1);
                }
            }
        }
    }

    return;
}

int32_t librg_world_query(librg_world *world, int64_t owner_id, int64_t *entity_ids, size_t *entity_amount) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    LIBRG_ASSERT(entity_amount); if (!entity_amount) return LIBRG_NULL_REFERENCE;
    librg_world_t *wld = (librg_world_t *)world;

    size_t buffer_limit = *entity_amount;
    size_t total_count = zpl_array_count(wld->entity_map.entries);

    librg_table_i64 results = {0};
    librg_table_tbl dimensions = {0};

    librg_table_i64_init(&results, wld->allocator);
    librg_table_tbl_init(&dimensions, wld->allocator);

    /* generate a map of visible chunks (only counting owned entities) */
    for (size_t i=0; i < total_count; ++i) {
        uint64_t entity_id = wld->entity_map.entries[i].key;
        librg_entity_t *entity = &wld->entity_map.entries[i].value;

        /* allways add self-owned entities */
        if (entity->owner_id == owner_id) {
            librg_table_i64_set(&results, entity_id, 1);
        }

        /* immidiately skip, if entity was not placed correctly */
        if (entity->chunks[0] == LIBRG_CHUNK_INVALID) continue;
        /* and skip, if used is not an owner of the entity */
        if (entity->owner_id != owner_id) continue;
        /* and skip if entity is not an observer */
        if (entity->observed_radius == 0) continue;

        /* fetch, or create chunk set in this dimension if does not exist */
        librg_table_i64 *dim_chunks = librg_table_tbl_get(&dimensions, entity->dimension);

        if (!dim_chunks) {
            librg_table_i64 _chunks = {0};
            librg_table_tbl_set(&dimensions, entity->dimension, _chunks);
            dim_chunks = librg_table_tbl_get(&dimensions, entity->dimension);
            librg_table_i64_init(dim_chunks, wld->allocator);
        }

        /* add entity chunks to the total visible chunks */
        for (int k = 0; k < LIBRG_ENTITY_MAXCHUNKS; ++k) {
            if (entity->chunks[k] == LIBRG_CHUNK_INVALID) break;

            int16_t chx=0, chy=0, chz=0;
            librg_chunk_to_chunkpos(world, entity->chunks[k], &chx, &chy, &chz);
            librg_util_chunkrange(world, dim_chunks, chx, chy, chz, entity->observed_radius);
        }
    }

    /* a slightly increased buffer_limit, that includes own entities */
    /* that allows us to prevent edge-cases where the code below will include our entities in the result as well */
    size_t owned_entities = zpl_array_count(results.entries);
    size_t buffer_limit_extended = buffer_limit + owned_entities;

    /* iterate on all entities, and check if they are inside of the interested chunks */
    for (size_t i=0; i < LIBRG_MIN(buffer_limit_extended, total_count); ++i) {
        uint64_t entity_id = wld->entity_map.entries[i].key;
        librg_entity_t *entity = &wld->entity_map.entries[i].value;
        librg_table_i64 *chunks = librg_table_tbl_get(&dimensions, entity->dimension);

        /* owner visiblity (personal)*/
        int8_t vis_owner = librg_entity_visibility_owner_get(world, entity_id, owner_id);
        if (vis_owner == LIBRG_VISIBLITY_NEVER) {
            continue; /* prevent from being included */
        }
        else if (vis_owner == LIBRG_VISIBLITY_ALWAYS) {
            librg_table_i64_set(&results, entity_id, 1); /* always included */
            continue;
        }

        /* global entity visiblity */
        int8_t vis_global = librg_entity_visibility_global_get(world, entity_id);
        if (vis_global == LIBRG_VISIBLITY_NEVER) {
            continue; /* prevent from being included */
        }
        else if (vis_global == LIBRG_VISIBLITY_ALWAYS) {
            librg_table_i64_set(&results, entity_id, 1); /* always included */
            continue;
        }

        /* skip if there are no chunks in this dimension */
        if (!chunks) continue;
        size_t chunk_amount = zpl_array_count(chunks->entries);

        for (size_t k = 0; k < chunk_amount; ++k) {
            librg_chunk chunk = chunks->entries[k].key;

            for (size_t j=0; j < LIBRG_ENTITY_MAXCHUNKS; ++j) {
                /* immidiately exit if chunk is invalid (the rest will also be invalid) */
                if (entity->chunks[j] == LIBRG_CHUNK_INVALID) break;

                /* add entity and continue to the next one */
                if (entity->chunks[j] == chunk) {
                    librg_table_i64_set(&results, entity_id, 1);
                    break;
                }
            }
        }
    }

    /* copy/transform results to a plain array */
    size_t count = zpl_array_count(results.entries);
    for (size_t i = 0; i < LIBRG_MIN(buffer_limit, count); ++i)
        entity_ids[i] = results.entries[i].key;

    /* free up temp data */
    for (int i = 0; i < zpl_array_count(dimensions.entries); ++i)
        librg_table_i64_destroy(&dimensions.entries[i].value);

    librg_table_tbl_destroy(&dimensions);
    librg_table_i64_destroy(&results);

    *entity_amount = LIBRG_MIN(buffer_limit, count);
    return LIBRG_MAX(0, (int32_t)(count - buffer_limit));
}

LIBRG_END_C_DECLS
// file: source/packing.c

#ifdef LIBRG_EDITOR
#include <librg.h>
#include <zpl.h>
#endif

LIBRG_BEGIN_C_DECLS

// =======================================================================//
// !
// ! Primitives
// !
// =======================================================================//

LIBRG_PRAGMA(pack(push, 1));
typedef struct {
    uint64_t id;
    uint16_t token;
    uint16_t size;
} librg_segval_t;

typedef struct {
    uint8_t  type;
    uint8_t  unused_;
    uint16_t amount;
    uint32_t size;
} librg_segment_t;
LIBRG_PRAGMA(pack(pop));

LIBRG_STATIC_ASSERT(sizeof(librg_segval_t) == 12, "packed librg_segval_t should have a valid size");
LIBRG_STATIC_ASSERT(sizeof(librg_segment_t) == 8, "packed librg_segment_t should have a valid size");

// =======================================================================//
// !
// ! World data packing method
// !
// =======================================================================//

int32_t librg_world_write(librg_world *world, int64_t owner_id, char *buffer, size_t *size, void *userdata) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;
    librg_table_i64 *last_snapshot = librg_table_tbl_get(&wld->owner_map, owner_id);

    /* no snapshot - means we are asking an invalid owner */
    if (!last_snapshot) {
        *size = 0;
        return LIBRG_OWNER_INVALID;
    }

    /* get old, and preapre new snapshot handlers */
    librg_table_i64 next_snapshot = {0};
    librg_table_i64_init(&next_snapshot, wld->allocator);

    int64_t *results = LIBRG_MEM_ALLOC(LIBRG_WORLDWRITE_MAXQUERY * sizeof(int64_t));
    size_t total_amount = LIBRG_WORLDWRITE_MAXQUERY;
    librg_world_query(world, owner_id, results, &total_amount);

    size_t total_written = 0;
    librg_event_t evt = {0};

    #define sz_total (total_written + sizeof(librg_segment_t))
    #define sz_value (sz_total + value_written + sizeof(librg_segval_t))

    uint8_t action_id = LIBRG_WRITE_CREATE;
    size_t buffer_limit = *size;
    size_t insufficient_size = 0;

librg_lbl_ww:

    /* create and update */
    if (sz_total < buffer_limit) {
        librg_segment_t *seg = (librg_segment_t*)(buffer+total_written);
        char *segend = (buffer + sz_total);

        uint16_t amount = 0;
        size_t value_written = 0;
        size_t iterations = total_amount;

        int64_t entity_id = LIBRG_ENTITY_INVALID;
        int32_t condition = LIBRG_TRUE;
        librg_entity_t *entity_blob = NULL;

        /* for deletions we are iterating something else */
        if (action_id == LIBRG_WRITE_REMOVE) {
            iterations = zpl_array_count(last_snapshot->entries);
        }

        for (size_t i = 0; i < iterations; ++i) {
            int16_t action_rejected = LIBRG_TRUE;
            int32_t data_size = 0;

            /* preparation */
            if (action_id == LIBRG_WRITE_CREATE) {
                entity_id   = results[i]; /* it did not exist && not foreign */
                condition   = librg_table_i64_get(last_snapshot, entity_id) == NULL
                    && librg_entity_foreign(world, entity_id) != LIBRG_TRUE;
            }
            else if (action_id == LIBRG_WRITE_UPDATE) {
                entity_id   = results[i];  /* it did exist */
                entity_blob = librg_table_ent_get(&wld->entity_map, entity_id);
                condition   = librg_table_i64_get(last_snapshot, entity_id) != NULL || librg_entity_foreign(world, entity_id) == LIBRG_TRUE;

                /* mark entity as still alive, to prevent it from being removed */
                librg_table_i64_set(last_snapshot, entity_id, 2);
            }
            else if (action_id == LIBRG_WRITE_REMOVE) {
                entity_id   = last_snapshot->entries[i].key; /* it was not marked as updated && and not foreign */
                condition   = last_snapshot->entries[i].value != 2
                    && librg_entity_foreign(world, entity_id) != LIBRG_TRUE;
            }
            else if (action_id == LIBRG_WRITE_OWNER) {
                entity_id   = results[i]; /* if we are the owner and we havent yet notified reader about that */
                entity_blob = librg_table_ent_get(&wld->entity_map, entity_id);
                condition   = entity_blob
                    && entity_blob->owner_id == owner_id
                    && entity_blob->flag_owner_updated
                    && librg_table_i64_get(&next_snapshot, entity_id);
            }

            /* data write */
            if (condition && sz_value < buffer_limit) {
                librg_segval_t *val = (librg_segval_t*)(segend + value_written);
                char *valend = (segend + value_written + sizeof(librg_segval_t));

                /* fill in event */
                evt.entity_id = entity_id;
                evt.type = action_id;
                evt.size = buffer_limit - sz_value;
                evt.buffer = valend;
                evt.owner_id = owner_id;
                evt.userdata = userdata;

                /* call event handlers */
                if (wld->handlers[action_id]) {
                    data_size = (int32_t)wld->handlers[action_id](world, (librg_event*)&evt);
                }

                /* if user returned < 0, we consider that event rejected */
                if (data_size >= 0) {
                    /* fill in segval */
                    val->id = entity_id;
                    val->size = data_size;

                    if (action_id == LIBRG_WRITE_OWNER) {
                        val->token = entity_blob->ownership_token;
                    }
                    else if (action_id == LIBRG_WRITE_UPDATE && entity_blob->flag_foreign) {
                        val->token = entity_blob->ownership_token;
                    } else {
                        val->token = 0;
                    }

                    /* increase the total size written */
                    value_written += sizeof(librg_segval_t) + val->size;
                    action_rejected = LIBRG_FALSE;
                    amount++;
                }
            }

            /* accumulate insufficient buffer size */
            if (condition && sz_value >= buffer_limit) {
                insufficient_size += (sz_value - buffer_limit);
            }

            /* finaliztion */
            if (action_id == LIBRG_WRITE_CREATE && !action_rejected) {
                /* mark entity as created, so it can start updating */
                librg_table_i64_set(&next_snapshot, entity_id, 1);
            }
            else if (action_id == LIBRG_WRITE_UPDATE && condition) {
                /* consider entitry updated, without regards was it written or not */
                librg_table_i64_set(&next_snapshot, entity_id, 1);
            }
            else if (action_id == LIBRG_WRITE_REMOVE && condition && action_rejected) {
                /* consider entity alive, till we are able to send it */
                librg_table_i64_set(&next_snapshot, entity_id, 1);
            }
            else if (action_id == LIBRG_WRITE_OWNER && condition) {
                /* mark reader as notified */
                entity_blob->flag_owner_updated = LIBRG_FALSE;
            }
        }

        if (amount > 0) {
            seg->type = action_id;
            seg->size = (uint32_t)value_written;
            seg->amount = amount;

            total_written += sizeof(librg_segment_t) + seg->size;
        }
    } else {
        insufficient_size += sz_total - buffer_limit;
    }

    /* iterate it again till all tasks are finished */
    switch (action_id) {
        case LIBRG_WRITE_CREATE: action_id = LIBRG_WRITE_UPDATE; goto librg_lbl_ww;
        case LIBRG_WRITE_UPDATE: action_id = LIBRG_WRITE_REMOVE; goto librg_lbl_ww;
        case LIBRG_WRITE_REMOVE: action_id = LIBRG_WRITE_OWNER; goto librg_lbl_ww;
    }

    /* swap snapshot tables */
    librg_table_i64_destroy(last_snapshot);
    librg_table_tbl_set(&wld->owner_map, owner_id, next_snapshot);
    LIBRG_MEM_FREE(results);

    /* write our total size */
    *size = total_written;

    #undef sz_total
    #undef sz_value

    /* if we didnt have enough space, value will be > 0 */
    return insufficient_size;
}

// =======================================================================//
// !
// ! World data unpacking method
// !
// =======================================================================//

int32_t librg_world_read(librg_world *world, int64_t owner_id, const char *buffer, size_t size, void *userdata) {
    LIBRG_ASSERT(world); if (!world) return LIBRG_WORLD_INVALID;
    librg_world_t *wld = (librg_world_t *)world;

    librg_event_t evt = {0};
    size_t total_read = 0;

    #define sz_segment (total_read + sizeof(librg_segment_t))
    #define sz_segval (sz_segment + segment_read + sizeof(librg_segval_t))

    while ((size-total_read) > sizeof(librg_segment_t)) {
        librg_segment_t *seg = (librg_segment_t*)(buffer+total_read);
        size_t segment_read = 0;

        /* immidiately exit if we will not be able to read the segment data */
        if (sz_segment+seg->size > size || sz_segment + seg->amount * sizeof(librg_segval_t) > size) {
            break;
        }

        for (int i = 0; i < seg->amount; ++i) {
            librg_segval_t *val = (librg_segval_t*)(buffer+sz_segment+segment_read);
            librg_entity_t *entity_blob = librg_table_ent_get(&wld->entity_map, val->id);
            int8_t action_id = -1;

            /* do preparation for entity processing */
            if (seg->type == LIBRG_WRITE_CREATE) {
                /* attempt to create an entity */
                action_id = (librg_entity_track(world, val->id) == LIBRG_OK)
                    ? LIBRG_READ_CREATE
                    : LIBRG_ERROR_CREATE;
            }
            else if (seg->type == LIBRG_WRITE_UPDATE) {
                /* try to check if entity exists, and if it is foreign OR owner and token are correct */
                action_id = (librg_entity_tracked(world, val->id) == LIBRG_TRUE
                    && (entity_blob->flag_foreign
                        || (entity_blob->owner_id == owner_id
                            && entity_blob->ownership_token == val->token)))
                    ? LIBRG_READ_UPDATE
                    : LIBRG_ERROR_UPDATE;
            }
            else if (seg->type == LIBRG_WRITE_REMOVE) {
                /* attempt to check if it does exist and only foreign */
                action_id = (librg_entity_tracked(world, val->id) == LIBRG_TRUE
                    && librg_entity_foreign(world, val->id) == LIBRG_TRUE)
                    ? LIBRG_READ_REMOVE
                    : LIBRG_ERROR_REMOVE;
            }
            else if (seg->type == LIBRG_WRITE_OWNER) {
                /* attempt to check if it does exist and only foreign */
                action_id = (librg_entity_tracked(world, val->id) == LIBRG_TRUE
                    && librg_entity_foreign(world, val->id) == LIBRG_TRUE)
                    ? LIBRG_READ_OWNER
                    : LIBRG_ERROR_OWNER;
            }

            if (action_id == -1) {
                return LIBRG_READ_INVALID;
            }

            /* do the initial entity processing */
            if (action_id == LIBRG_READ_CREATE) {
                /* mark newly created entity as foreign */
                librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, val->id);
                if (!entity) return LIBRG_READ_INVALID; else entity->flag_foreign = LIBRG_TRUE;
            }

            /* fill in event */
            evt.entity_id = val->id;
            evt.type = action_id;
            evt.size = val->size;
            evt.buffer = (char*)(buffer+sz_segval);
            evt.owner_id = owner_id;
            evt.userdata = userdata;

            /* call event handlers */
            if (wld->handlers[action_id]) {
                /*ignore response*/
                wld->handlers[action_id](world, &evt);
            }

            /* do the afterwork processing */
            if (action_id == LIBRG_READ_REMOVE) {
                /* remove foreign mark from entity */
                librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, val->id);
                if (!entity) return LIBRG_READ_INVALID; else entity->flag_foreign = LIBRG_FALSE;
                librg_entity_untrack(world, val->id);
            }
            else if (action_id == LIBRG_READ_OWNER) {
                librg_entity_t *entity = librg_table_ent_get(&wld->entity_map, val->id);
                if (!entity) return LIBRG_READ_INVALID;

                /* immidiately mark entity as owned, set up & override additional info */
                entity->flag_foreign = LIBRG_FALSE; /* unmark it temp, while owner is set */
                librg_entity_owner_set(world, val->id, owner_id);
                entity->ownership_token = val->token;
                entity->flag_owner_updated = LIBRG_FALSE;
                entity->flag_foreign = LIBRG_TRUE;
            }

            segment_read += sizeof(librg_segval_t) + val->size;
        }

        /* validate sizes of the data we read */
        if (segment_read != seg->size) {
            return LIBRG_READ_INVALID;
        }

        total_read += sizeof(librg_segment_t) + segment_read;
    }

    #undef sz_segment
    #undef sz_segval

    if (total_read != size) {
        return (int32_t)(size - total_read);
    }

    return LIBRG_OK;
}

LIBRG_END_C_DECLS

#endif // LIBRG_IMPLEMENTATION

#endif // LIBRG_H
