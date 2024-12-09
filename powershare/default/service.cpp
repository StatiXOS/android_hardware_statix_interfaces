/*
 * Copyright (C) 2022-2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android/binder_manager.h>
#include <android/binder_process.h>

#include "PowerShare.h"

using ::aidl::vendor::lineage::powershare::PowerShare;

int main() {
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    std::shared_ptr<PowerShare> lh = ndk::SharedRefBase::make<PowerShare>();

    const std::string instance = std::string() + PowerShare::descriptor + "/default";
    binder_status_t status = AServiceManager_addService(lh->asBinder().get(), instance.c_str());
    CHECK_EQ(status, STATUS_OK);

    ABinderProcess_joinThreadPool();
    return EXIT_FAILURE;  // should not reach
}
