/*
 * Copyright (C) 2022-2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PowerShare.h"

#include <android-base/file.h>
#include <android-base/logging.h>
#include <android-base/strings.h>
#include <android/binder_status.h>

#include <fstream>

#include "android/binder_auto_utils.h"

#define LOG_TAG "vendor.lineage.powershare-service.default"

namespace aidl {
namespace vendor {
namespace lineage {
namespace powershare {

PowerShare::PowerShare() {
    sharing_node_ = POWER_SHARE_NODE;
}

ndk::ScopedAStatus PowerShare::getMinBattery(int32_t* min_battery) {
    *min_battery = 0;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus PowerShare::setMinBattery(int32_t min_battery, int32_t* _aidl_return) {
    _aidl_return = 0;
    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus PowerShare::isEnabled(bool* _aidl_return) {
    std::string content;
    if (!android::base::ReadFileToString(sharing_node_, &content, true)) {
        LOG(ERROR) << "Failed to read current charging enabled value";
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    content = android::base::Trim(content);

    if (content == "1") {
        *_aidl_return = true;
    } else if (content == "0") {
        *_aidl_return = false;
    } else {
        LOG(ERROR) << "Unknown value " << content;
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }

    return ndk::ScopedAStatus::ok();
}

ndk::ScopedAStatus PowerShare::setEnabled(bool enabled, bool* _aidl_return) {
    const auto& value = enabled ? "1" : "0";
    if (!android::base::WriteStringToFile(value, sharing_node_, true)) {
        LOG(ERROR) << "Failed to write to powershare enable node: " << strerror(errno);
        *_aidl_return = false;
        return ndk::ScopedAStatus::fromExceptionCode(EX_ILLEGAL_STATE);
    }
    *_aidl_return = true;
    return ndk::ScopedAStatus::ok();
}

binder_status_t PowerShare::dump(int fd, const char** /* args */, uint32_t /* numArgs */) {
    bool enabled;
    isEnabled(&enabled);

    int min_battery;
    getMinBattery(&min_battery);

    dprintf(fd, "Powershare node: %s\n", sharing_node_.c_str());
    dprintf(fd, "Powershare enabled: %s\n", enabled ? "true" : "false");
    dprintf(fd, "Powershare min battery: %d\n", min_battery);

    return STATUS_OK;
}

}  // namespace powershare
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
