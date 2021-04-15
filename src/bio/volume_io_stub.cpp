/*
 *   BSD LICENSE
 *   Copyright (c) 2021 Samsung Electronics Corporation
 *   All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "src/bio/volume_io.h"
#include "src/include/core_const.h"

namespace pos
{
VolumeIo::VolumeIo(void* buffer, uint32_t unitCount, std::string arrayName)
: Ubio(buffer, unitCount, arrayName),
  volumeId(UINT32_MAX),
  originCore(INVALID_CORE),
  isGc(false)
{
}

VolumeIo::VolumeIo(const VolumeIo& volumeIo)
: Ubio(volumeIo),
  volumeId(volumeIo.volumeId),
  originCore(volumeIo.originCore),
  isGc(volumeIo.isGc),
  oldVsaForGc(volumeIo.oldVsaForGc)
{
}

VolumeIo::~VolumeIo(void)
{
}

VolumeIoSmartPtr
VolumeIo::Split(uint32_t sectors, bool tail)
{
    return nullptr;
}

VolumeIoSmartPtr
VolumeIo::GetOriginVolumeIo(void)
{
    VolumeIoSmartPtr originVolumeIo =
        std::dynamic_pointer_cast<VolumeIo>(GetOriginUbio());
    return originVolumeIo;
}

bool
VolumeIo::IsPollingNecessary(void)
{
    return false;
}

uint32_t
VolumeIo::GetVolumeId(void)
{
    return volumeId;
}

void
VolumeIo::SetSectorRba(uint64_t inputSectorRba)
{
    sectorRba = inputSectorRba;
}

uint64_t
VolumeIo::GetSectorRba(void)
{
    return sectorRba;
}

void
VolumeIo::SetVolumeId(uint32_t inputVolumeId)
{
    volumeId = inputVolumeId;
}

uint32_t
VolumeIo::GetOriginCore(void)
{
    return originCore;
}

void
VolumeIo::SetLsidEntry(StripeAddr& inputLsidEntry)
{
    lsidEntry = inputLsidEntry;
}

void
VolumeIo::SetOldLsidEntry(StripeAddr& inputLsidEntry)
{
    oldLsidEntry = inputLsidEntry;
}

const StripeAddr&
VolumeIo::GetLsidEntry(void)
{
    return lsidEntry;
}

const StripeAddr&
VolumeIo::GetOldLsidEntry(void)
{
    return oldLsidEntry;
}

const VirtualBlkAddr&
VolumeIo::GetVsa(void)
{
    return vsa;
}

void
VolumeIo::SetVsa(VirtualBlkAddr& inputVsa)
{
    vsa = inputVsa;
}

void
VolumeIo::SetGc(VirtualBlkAddr& oldVsa)
{
    isGc = true;
}

bool
VolumeIo::IsGc(void)
{
    return isGc;
}

const VirtualBlkAddr&
VolumeIo::GetOldVsa(void)
{
    return oldVsaForGc;
}
} // namespace pos