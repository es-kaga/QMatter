/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef APP_TASK_H
#define APP_TASK_H

#include <stdbool.h>
#include <stdint.h>

#include "AppEvent.h"

#include "FreeRTOS.h"
#include "timers.h" // provides FreeRTOS timer support
#include <platform/CHIPDeviceLayer.h>

#define APP_NAME "Base-Matter-app"

class AppTask
{

public:
    CHIP_ERROR StartAppTask();

    void PostEvent(const AppEvent * event);

    void UpdateClusterState();

private:
    friend AppTask & GetAppTask(void);

    CHIP_ERROR Init();
    static void InitServer(intptr_t arg);
    static void OpenCommissioning(intptr_t arg);

    void StartTimer(uint32_t aTimeoutMs);
    void CancelTimer(void);

    void DispatchEvent(AppEvent * event);

    static void AppTaskMain(void * pvParameter);
    static void ButtonEventHandler(uint8_t btnIdx, bool btnPressed);
    static void FunctionTimerEventHandler(AppEvent * aEvent);
    static void FunctionHandler(AppEvent * aEvent);
    static void TimerEventHandler(chip::System::Layer * aLayer, void * aAppState);

    enum Function_t
    {
        kFunction_NoneSelected   = 0,
        kFunction_SoftwareUpdate = 1,
        kFunction_FactoryReset   = 2,
        kFunction_Invalid
    } Function;

    Function_t mFunction;
    bool mFunctionTimerActive;

    static AppTask sAppTask;
};

inline AppTask & GetAppTask(void)
{
    return AppTask::sAppTask;
}

#endif // APP_TASK_H
