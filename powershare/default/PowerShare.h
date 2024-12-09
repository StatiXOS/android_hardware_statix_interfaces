/*
 * Copyright (C) 2022-2023 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <aidl/vendor/lineage/powershare/BnPowerShare.h>
#include <android/binder_status.h>

#include <string>

#include "android/binder_auto_utils.h"

namespace aidl {
namespace vendor {
namespace lineage {
namespace powershare {

struct PowerShare : public BnPowerShare {
  public:
    PowerShare();

    ndk::ScopedAStatus getMinBattery(int32_t* _aidl_return) override;
    ndk::ScopedAStatus isEnabled(bool* _aidl_return) override;
    ndk::ScopedAStatus setEnabled(bool enabled, bool* _aidl_return) override;
    ndk::ScopedAStatus setMinBattery(int32_t min_battery, int32_t* _aidl_return) override;
    binder_status_t dump(int fd, const char** args, uint32_t numArgs) override;

  private:
    std::string sharing_node_;
};

}  // namespace powershare
}  // namespace lineage
}  // namespace vendor
}  // namespace aidl
