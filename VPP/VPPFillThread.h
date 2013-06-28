/*
 * Copyright (C) 2012 Intel Corporation.  All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __VPP_FILL_THREAD_H
#define __VPP_FILL_THREAD_H

#include <media/stagefright/MetaData.h>
#include "VPPBuffer.h"
#include "VPPWorker.h"

#include <utils/threads.h>
#include <utils/Errors.h>

namespace android {

class VPPProcessor;

class VPPFillThread : public Thread {
    public:

        VPPFillThread(bool canCallJava, VPPWorker* vppWorker,
                    VPPBuffer *inputBuffer, const uint32_t inputBufferNum,
                    VPPBuffer *outputBuffer, const uint32_t outputBufferNum,
                    const bool *eos);
        virtual ~VPPFillThread();

        virtual status_t readyToRun();

        // Derived class must implement threadLoop(). The thread starts its life
        // here. There are two ways of using the Thread object:
        // 1) loop: if threadLoop() returns true, it will be called again if
        //          requestExit() wasn't called.
        // 2) once: if threadLoop() returns false, the thread will exit upon return.
        virtual bool threadLoop();
        bool isCurrentThread() const;

    public:
        Mutex mLock;
        // main thread send this condition to VPPFillThread,
        // VPPFillThread wait this condition to run
        Condition mRunCond;
        bool mWait;
        bool mError;

    private:
        VPPFillThread(const VPPFillThread &);
        VPPFillThread &operator=(const VPPFillThread &);

    private:
        android_thread_id_t mThreadId;
        VPPWorker *mVPPWorker;
        VPPBuffer *mInput;
        VPPBuffer *mOutput;
        const uint32_t mInputBufferNum;
        const uint32_t mOutputBufferNum;
        const bool *mEOS;
        bool mFirstInputFrame;
        uint32_t mInputFillIdx;
        uint32_t mOutputFillIdx;
};


} /* END namespace android */
#endif /* __VPP_FILL_THREAD_H*/
