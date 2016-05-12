/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC)
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
 * @author Glenn Scott, Palo Alto Research Center (Xerox PARC)
 * @copyright (c) 2013-2015, Xerox Corporation (Xerox) and Palo Alto Research Center, Inc (PARC).  All rights reserved.
 */
#include <config.h>
#include <sys/errno.h>

#include <LongBow/runtime.h>

#include <ccnx/api/ccnx_Portal/ccnx_PortalStack.h>

#include <parc/algol/parc_Object.h>

struct CCNxPortalStack {
    CCNxPortalFactory *factory;

    const CCNxPortalAttributes *attributes;

    void *privateData;

    void (*start)(void *privateData);

    void (*stop)(void *privateData);

    CCNxMetaMessage *(*read)(void *privateData, const CCNxStackTimeout *microSeconds);

    bool (*write)(void *privateData, const CCNxMetaMessage *portalMessage, const CCNxStackTimeout *microSeconds);

    bool (*listen)(void *privateData, const CCNxName *restrict name, const CCNxStackTimeout *microSeconds);

    bool (*ignore)(void *privateData, const CCNxName *restrict name, const CCNxStackTimeout *microSeconds);

    int (*getFileId)(void *privateData);

    bool (*setAttributes)(void *privateData, const CCNxPortalAttributes *attributes);

    CCNxPortalAttributes * (*getAttributes)(void *privateData);

    void (*releasePrivateData)(void **privateData);
};

static void
_destroy(CCNxPortalStack **instancePtr)
{
    CCNxPortalStack *instance = *instancePtr;

    if (instance->privateData != NULL) {
        instance->releasePrivateData(&instance->privateData);
    }

    ccnxPortalFactory_Release(&instance->factory);
}

parcObject_ExtendPARCObject(CCNxPortalStack, _destroy, NULL, NULL, NULL, NULL, NULL, NULL);

parcObject_ImplementAcquire(ccnxPortalStack, CCNxPortalStack);

parcObject_ImplementRelease(ccnxPortalStack, CCNxPortalStack);

CCNxPortalStack *
ccnxPortalStack_Create(const CCNxPortalFactory *factory,
                       const CCNxPortalAttributes *attributes,
                       void (*start)(void *privateData),
                       void (*stop)(void *privateData),
                       CCNxMetaMessage *(*receive)(void *privateData, const CCNxStackTimeout *microSeconds),
                       bool (*send)(void *privateData, const CCNxMetaMessage *message, const CCNxStackTimeout *microSeconds),
                       bool (*listen)(void *privateData, const CCNxName *name, const CCNxStackTimeout *microSeconds),
                       bool (*ignore)(void *privateData, const CCNxName *name, const CCNxStackTimeout *microSeconds),
                       int (*getFileId)(void *privateData),
                       bool (*setAttributes)(void *privateData, const CCNxPortalAttributes *attributes),
                       CCNxPortalAttributes * (*getAttributes)(void *privateData),
                       void *privateData,
                       void (*releasePrivateData)(void **privateData))
{
    CCNxPortalStack *result = parcObject_CreateInstance(CCNxPortalStack);

    if (result != NULL) {
        result->factory = ccnxPortalFactory_Acquire(factory);
        result->attributes = attributes;
        result->start = start;
        result->stop = stop;
        result->read = receive;
        result->write = send;
        result->getFileId = getFileId;
        result->listen = listen;
        result->ignore = ignore;
        result->setAttributes = setAttributes;
        result->getAttributes = getAttributes;
        result->privateData = privateData;
        result->releasePrivateData = releasePrivateData;
    }
    return result;
}

bool
ccnxPortalStack_Start(const CCNxPortalStack *portalStack)
{
    portalStack->start(portalStack->privateData);
    return true;
}

bool
ccnxPortalStack_Stop(const CCNxPortalStack *portalStack)
{
    portalStack->stop(portalStack->privateData);
    return true;
}

CCNxMetaMessage *
ccnxPortalStack_Receive(const CCNxPortalStack *restrict portalStack, const CCNxStackTimeout *microSeconds)
{
    CCNxMetaMessage *result = portalStack->read(portalStack->privateData, microSeconds);

    return result;
}

bool
ccnxPortalStack_Send(const CCNxPortalStack *portalStack, const CCNxMetaMessage *portalMessage, const CCNxStackTimeout *microSeconds)
{
    return portalStack->write(portalStack->privateData, portalMessage, microSeconds);
}

bool
ccnxPortalStack_SetAttributes(const CCNxPortalStack *portalStack, const CCNxPortalAttributes *attributes)
{
    return portalStack->setAttributes(portalStack->privateData, attributes);
}

bool
ccnxPortalStack_Listen(const CCNxPortalStack *portalStack, const CCNxName *name, const CCNxStackTimeout *microSeconds)
{
    return portalStack->listen(portalStack->privateData, name, microSeconds);
}

bool
ccnxPortalStack_Ignore(const CCNxPortalStack *portalStack, const CCNxName *name, const CCNxStackTimeout *microSeconds)
{
    return portalStack->ignore(portalStack->privateData, name, microSeconds);
}

int
ccnxPortalStack_GetErrorCode(const CCNxPortalStack *portalStack)
{
    extern int errno;
    return errno;
}

const CCNxPortalAttributes *
ccnxPortalStack_GetAttributes(const CCNxPortalStack *portalStack)
{
    return portalStack->attributes;
}

int
ccnxPortalStack_GetFileId(const CCNxPortalStack *portalStack)
{
    return portalStack->getFileId(portalStack->privateData);
}

const PARCKeyId *
ccnxPortalStack_GetKeyId(const CCNxPortalStack *portalStack)
{
    return ccnxPortalFactory_GetKeyId(portalStack->factory);
}

PARCProperties *
ccnxPortalStack_GetProperties(const CCNxPortalStack *portalStack)
{
    return ccnxPortalFactory_GetProperties(portalStack->factory);
}

const char *
ccnxPortalStack_GetProperty(const CCNxPortalStack *portalStack, const char *restrict name, const char *restrict defaultValue)
{
    return ccnxPortalFactory_GetProperty(portalStack->factory, name, defaultValue);
}
