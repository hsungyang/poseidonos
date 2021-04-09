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

#pragma once

#include <string>

#include "mfs_config.h"
#include "mfs_fscontrol_api_base.h"
#include "mfs_log.h"

class MetaFsControlApiWrapperClass : public IMetaFsControlApiWrapperClass
{
public:
    virtual MetaFsReturnCode<MetaFsStatusCodeFsControlSpcf>
    Mount(void) override
    {
        MetaFsReturnCode<MetaFsStatusCodeFsControlSpcf> rc;

        MFS_TRACE_INFO("Fake MetaFS has been mounted");

        rc.sc = MetaFsStatusCodeFsControlSpcf::Success;

        return rc;
    }
    virtual MetaFsReturnCode<MetaFsStatusCodeFsControlSpcf>
    Unmount(void) override
    {
        MetaFsReturnCode<MetaFsStatusCodeFsControlSpcf> rc;

        rc.sc = MetaFsStatusCodeFsControlSpcf::Success;

        return rc;
    }
    virtual MetaFsReturnCode<MetaFsStatusCodeFsControlSpcf>
    Create(void) override
    {
        std::string cmd;
        int status;

        cmd.append("rm -rf ");
        cmd.append(FAKE_META_FILE_DIR);

        status = system(cmd.c_str());
        assert(0 == status);

        cmd.clear();
        cmd.append("mkdir ");
        cmd.append(FAKE_META_FILE_DIR);

        status = system(cmd.c_str());
        assert(0 == status);

        MetaFsReturnCode<MetaFsStatusCodeFsControlSpcf> rc;

        MFS_TRACE_INFO("New Fake MetaFS has been created");

        rc.sc = MetaFsStatusCodeFsControlSpcf::Success;

        return rc;
    }

private:
};