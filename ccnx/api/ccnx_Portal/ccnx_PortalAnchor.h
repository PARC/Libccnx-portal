/*
 * Copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX OR PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ################################################################################
 * #
 * # PATENT NOTICE
 * #
 * # This software is distributed under the BSD 2-clause License (see LICENSE
 * # file).  This BSD License does not make any patent claims and as such, does
 * # not act as a patent grant.  The purpose of this section is for each contributor
 * # to define their intentions with respect to intellectual property.
 * #
 * # Each contributor to this source code is encouraged to state their patent
 * # claims and licensing mechanisms for any contributions made. At the end of
 * # this section contributors may each make their own statements.  Contributor's
 * # claims and grants only apply to the pieces (source code, programs, text,
 * # media, etc) that they have contributed directly to this software.
 * #
 * # There is no guarantee that this section is complete, up to date or accurate. It
 * # is up to the contributors to maintain their portion of this section and up to
 * # the user of the software to verify any claims herein.
 * #
 * # Do not remove this header notification.  The contents of this section must be
 * # present in all distributions of the software.  You may only modify your own
 * # intellectual property statements.  Please provide contact information.
 *
 * - Palo Alto Research Center, Inc
 * This software distribution does not grant any rights to patents owned by Palo
 * Alto Research Center, Inc (PARC). Rights to these patents are available via
 * various mechanisms. As of January 2016 PARC has committed to FRAND licensing any
 * intellectual property used by its contributions to this software. You may
 * contact PARC at cipo@parc.com for more information or visit http://www.ccnx.org
 */
/**
 * @file ccnx_PortalAnchor.h
 * @brief CCN Routing control for CCNxPortal
 *
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#ifndef CCNxPortal_ccnx_PortalAnchor
#define CCNxPortal_ccnx_PortalAnchor
#include <stdbool.h>

#include <parc/algol/parc_JSON.h>
#include <parc/algol/parc_HashCode.h>

#include <ccnx/common/ccnx_Name.h>

struct CCNxPortalAnchor;
typedef struct CCNxPortalAnchor CCNxPortalAnchor;

/**
 * Increase the number of references to a `CCNxPortalAnchor` instance.
 *
 * Note that new `CCNxPortalAnchor` is not created,
 * only that the given `CCNxPortalAnchor` reference count is incremented.
 * Discard the reference by invoking `ccnxPortalAnchor_Release`.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return The same value as @p instance.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create();
 *
 *     CCNxPortalAnchor *b = ccnxPortalAnchor_Acquire();

 *     ccnxPortalAnchor_Release(&a);
 *     ccnxPortalAnchor_Release(&b);
 * }
 * @endcode
 */
CCNxPortalAnchor *ccnxPortalAnchor_Acquire(const CCNxPortalAnchor *instance);

#ifdef CCNxPortal_DISABLE_VALIDATION
#  define ccnxPortalAnchor_OptionalAssertValid(_instance_)
#else
#  define ccnxPortalAnchor_OptionalAssertValid(_instance_) ccnxPortalAnchor_AssertValid(_instance_)
#endif

/**
 * Assert that the given `CCNxPortalAnchor` instance is valid.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     ccnxPortalAnchor_AssertValid(a);
 *
 *     printf("Instance is valid.\n");
 *
 *     ccnxPortalAnchor_Release(&b);
 * }
 * @endcode
 */
void ccnxPortalAnchor_AssertValid(const CCNxPortalAnchor *instance);

/**
 * Create an instance of CCNxPortalAnchor
 *
 * @return non-NULL A pointer to a valid CCNxPortalAnchor instance.
 * @return NULL An error occurred.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     ccnxPortalAnchor_Release(&a);
 * }
 * @endcode
 */
CCNxPortalAnchor *ccnxPortalAnchor_Create(const CCNxName *name, time_t expireTime);

/**
 * Create an instance of `CCNxPortalAnchor` from an instance of `PARCJSON`.
 *
 * @return non-NULL A pointer to a valid CCNxPortalAnchor instance.
 * @return NULL An error occurred.
 */
CCNxPortalAnchor *ccnxPortalAnchor_CreateFromJSON(const PARCJSON *json);

/**
 * Compares @p instance with @p other for order.
 *
 * Returns a negative integer, zero, or a positive integer as @p instance
 * is less than, equal to, or greater than @p other.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 * @param [in] other A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return <0 Instance is less than @p other.
 * @return 0 Instance a and instance b compare the same.
 * @return >0 Instance a is greater than instance b.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *     CCNxPortalAnchor *b = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     if (ccnxPortalAnchor_Compare(a, b) == 0) {
 *         printf("Instances are equal.\n");
 *     }
 *
 *     ccnxPortalAnchor_Release(&a);
 *     ccnxPortalAnchor_Release(&b);
 * }
 * @endcode
 *
 * @see ccnxPortalAnchor_Equals
 */
int ccnxPortalAnchor_Compare(const CCNxPortalAnchor *instance, const CCNxPortalAnchor *other);

/**
 * Create an independent copy the given `PARCBuffer`
 *
 * A new buffer is created as a complete copy of the original.
 *
 * @param [in] original A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return NULL Memory could not be allocated.
 * @return non-NULL A pointer to a new `CCNxPortalAnchor` instance.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     CCNxPortalAnchor *copy = ccnxPortalAnchor_Copy(&b);
 *
 *     ccnxPortalAnchor_Release(&b);
 *     ccnxPortalAnchor_Release(&copy);
 * }
 * @endcode
 */
CCNxPortalAnchor *ccnxPortalAnchor_Copy(const CCNxPortalAnchor *original);

/**
 * Print a human readable representation of the given `CCNxPortalAnchor`.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 * @param [in] indentation The indentation level to use for printing.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     ccnxPortalAnchor_Display(a, 0);
 *
 *     ccnxPortalAnchor_Release(&a);
 * }
 * @endcode
 */
void ccnxPortalAnchor_Display(const CCNxPortalAnchor *instance, int indentation);

/**
 * Determine if two `CCNxPortalAnchor` instances are equal.
 *
 * The following equivalence relations on non-null `CCNxPortalAnchor` instances are maintained: *
 *   * It is reflexive: for any non-null reference value x, `ccnxPortalAnchor_Equals(x, x)` must return true.
 *
 *   * It is symmetric: for any non-null reference values x and y, `ccnxPortalAnchor_Equals(x, y)` must return true if and only if
 *        `ccnxPortalAnchor_Equals(y x)` returns true.
 *
 *   * It is transitive: for any non-null reference values x, y, and z, if
 *        `ccnxPortalAnchor_Equals(x, y)` returns true and
 *        `ccnxPortalAnchor_Equals(y, z)` returns true,
 *        then `ccnxPortalAnchor_Equals(x, z)` must return true.
 *
 *   * It is consistent: for any non-null reference values x and y, multiple invocations of `ccnxPortalAnchor_Equals(x, y)`
 *         consistently return true or consistently return false.
 *
 *   * For any non-null reference value x, `ccnxPortalAnchor_Equals(x, NULL)` must return false.
 *
 * @param [in] x A pointer to a valid CCNxPortalAnchor instance.
 * @param [in] y A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return true The instances x and y are equal.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *     CCNxPortalAnchor *b = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     if (ccnxPortalAnchor_Equals(a, b)) {
 *         printf("Instances are equal.\n");
 *     }
 *
 *     ccnxPortalAnchor_Release(&a);
 *     ccnxPortalAnchor_Release(&b);
 * }
 * @endcode
 * @see ccnxPortalAnchor_HashCode
 */
bool ccnxPortalAnchor_Equals(const CCNxPortalAnchor *x, const CCNxPortalAnchor *y);

/**
 * Returns a hash code value for the given instance.
 *
 * The general contract of `HashCode` is:
 *
 * Whenever it is invoked on the same instance more than once during an execution of an application,
 * the `HashCode` function must consistently return the same value,
 * provided no information used in a corresponding comparisons on the instance is modified.
 *
 * This value need not remain consistent from one execution of an application to another execution of the same application.
 * If two instances are equal according to the {@link ccnxPortalAnchor_Equals} method,
 * then calling the {@link ccnxPortalAnchor_HashCode} method on each of the two instances must produce the same integer result.
 *
 * It is not required that if two instances are unequal according to the
 * {@link ccnxPortalAnchor_Equals} function,
 * then calling the `ccnxPortalAnchor_HashCode`
 * method on each of the two objects must produce distinct integer results.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return The hashcode for the given instance.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     PARCHashCode hashValue = ccnxPortalAnchor_HashCode(buffer);
 *     ccnxPortalAnchor_Release(&a);
 * }
 * @endcode
 */
PARCHashCode ccnxPortalAnchor_HashCode(const CCNxPortalAnchor *instance);

/**
 * Determine if an instance of `CCNxPortalAnchor` is valid.
 *
 * Valid means the internal state of the type is consistent with its required current or future behaviour.
 * This may include the validation of internal instances of types.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return true The instance is valid.
 * @return false The instance is not valid.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     if (ccnxPortalAnchor_IsValid(a)) {
 *         printf("Instance is valid.\n");
 *     }
 *
 *     ccnxPortalAnchor_Release(&a);
 * }
 * @endcode
 *
 */
bool ccnxPortalAnchor_IsValid(const CCNxPortalAnchor *instance);

/**
 * Release a previously acquired reference to the given `CCNxPortalAnchor` instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] instancePtr A pointer to a pointer to the instance to release.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     ccnxPortalAnchor_Release(&a);
 * }
 * @endcode
 */
void ccnxPortalAnchor_Release(CCNxPortalAnchor **instancePtr);

/**
 * Create a `PARCJSON` instance (representation) of the given object.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return NULL Memory could not be allocated to contain the `PARCJSON` instance.
 * @return non-NULL An allocated C string that must be deallocated via parcMemory_Deallocate().
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     PARCJSON *json = ccnxPortalAnchor_ToJSON(a);
 *
 *     printf("JSON representation: %s\n", parcJSON_ToString(json));
 *     parcJSON_Release(&json);
 *
 *     ccnxPortalAnchor_Release(&a);
 * }
 * @endcode
 */
PARCJSON *ccnxPortalAnchor_ToJSON(const CCNxPortalAnchor *instance);

/**
 * Produce a null-terminated string representation of the specified `CCNxPortalAnchor`.
 *
 * The result must be freed by the caller via {@link parcMemory_Deallocate}.
 *
 * @param [in] instance A pointer to a valid CCNxPortalAnchor instance.
 *
 * @return NULL Cannot allocate memory.
 * @return non-NULL A pointer to an allocated, null-terminated C string that must be deallocated via {@link parcMemory_Deallocate}.
 *
 * Example:
 * @code
 * {
 *     CCNxPortalAnchor *a = ccnxPortalAnchor_Create(name, expireTime);
 *
 *     char *string = ccnxPortalAnchor_ToString(a);
 *
 *     ccnxPortalAnchor_Release(&a);
 *
 *     parcMemory_Deallocate(&string);
 * }
 * @endcode
 *
 * @see ccnxPortalAnchor_Display
 */
char *ccnxPortalAnchor_ToString(const CCNxPortalAnchor *instance);

/**
 * Append a representation of the specified `CCNxPortalAnchor` instance to the given `PARCBufferComposer`.
 *
 * @param [in] name A pointer to a `CCNxPortalAnchor` instance whose representation should be appended to the @p composer.
 * @param [in,out] composer A pointer to a `PARCBufferComposer` instance to be modified.
 *
 * @return NULL Cannot allocate memory.
 * @return non-NULL The @p composer.
 *
 * Example:
 * @code
 * {
 *     PARCBufferComposer *result = parcBufferComposer_Create(name, expireTime);
 *
 *     ccnxPortalAnchor_BuildString(anchor, result);
 *
 *     char *string = parcBufferComposer_ToString(result);
 *     printf("Hello: %s\n", string);
 *     parcMemory_Deallocate(string);
 *
 *     parcBufferComposer_Release(&result);
 * }
 * @endcode
 */
PARCBufferComposer *ccnxPortalAnchor_BuildString(const CCNxPortalAnchor *anchor, PARCBufferComposer *composer);

CCNxPortalAnchor *ccnxPortalAnchor_Deserialize(PARCBuffer *buffer);

PARCBufferComposer *ccnxPortalAnchor_Serialize(const CCNxPortalAnchor *anchor, PARCBufferComposer *composer);

CCNxName *ccnxPortalAnchor_GetNamePrefix(const CCNxPortalAnchor *anchor);

time_t ccnxPortalAnchor_GetExpireTime(const CCNxPortalAnchor *anchor);

time_t ccnxPortalAnchor_SetExpireTime(CCNxPortalAnchor *anchor, const time_t expireTime);
#endif
