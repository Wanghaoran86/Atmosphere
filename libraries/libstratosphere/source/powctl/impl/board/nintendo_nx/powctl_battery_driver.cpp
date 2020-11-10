/*
 * Copyright (c) 2018-2020 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stratosphere.hpp>
#include "../../powctl_device_management.hpp"
#include "powctl_retry_helper.hpp"
#include "powctl_battery_driver.hpp"
#include "powctl_max17050_driver.hpp"

namespace ams::powctl::impl::board::nintendo_nx {

    namespace {

        constinit std::optional<BatteryDevice> g_battery_device;

        Max17050Driver &GetMax17050Driver() {
            static Max17050Driver s_max17050_driver;
            return s_max17050_driver;
        }

    }

    /* Generic API. */
    void BatteryDriver::InitializeDriver() {
        /* Initialize gpio library. */
        gpio::Initialize();

        /* Create battery device. */
        g_battery_device.emplace(this->IsEventHandlerEnabled());

        /* Initialize the Max17050Driver. */
        {
            size_t battery_vendor_size;
            char battery_vendor[0x18] = {};
            if (R_FAILED(cal::GetBatteryVendor(std::addressof(battery_vendor_size), battery_vendor, sizeof(battery_vendor)))) {
                battery_vendor[7] = 'A';
                battery_vendor_size = 0;
            }

            u8 battery_version = 0;
            if (R_FAILED(cal::GetBatteryVersion(std::addressof(battery_version)))) {
                battery_version = 0;
            }

            GetMax17050Driver().Initialize(battery_vendor, battery_version);
        }

        /* Register our device. */
        this->RegisterDevice(std::addressof(*g_battery_device));

        /* Register the charger device's code. */
        R_ABORT_UNLESS(powctl::impl::RegisterDeviceCode(powctl::DeviceCode_Max17050, std::addressof(*g_battery_device)));

    }

    void BatteryDriver::FinalizeDriver() {
        /* Unregister the charger device code. */
        powctl::impl::UnregisterDeviceCode(powctl::DeviceCode_Max17050);

        /* Unregister our device. */
        this->UnregisterDevice(std::addressof(*g_battery_device));

        /* Finalize Max17050Driver. */
        GetMax17050Driver().Finalize();

        /* Destroy the charger device. */
        g_battery_device = std::nullopt;

        /* Finalize gpio library. */
        gpio::Finalize();
    }

    Result BatteryDriver::GetDeviceSystemEvent(os::SystemEventType **out, IDevice *device) {
        /* Validate arguments. */
        R_UNLESS(out != nullptr,    powctl::ResultInvalidArgument());
        R_UNLESS(device != nullptr, powctl::ResultInvalidArgument());

        /* Check that we support event handlers. */
        R_UNLESS(this->IsEventHandlerEnabled(), powctl::ResultNotAvailable());

        *out = device->SafeCastTo<BatteryDevice>().GetSystemEvent();
        return ResultSuccess();
    }

    Result BatteryDriver::SetDeviceInterruptEnabled(IDevice *device, bool enable) {
        /* Validate arguments. */
        R_UNLESS(device != nullptr, powctl::ResultInvalidArgument());

        /* Set the interrupt enable. */
        device->SafeCastTo<BatteryDevice>().SetInterruptEnabled(enable);

        return ResultSuccess();
    }

    Result BatteryDriver::GetDeviceErrorStatus(u32 *out, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetDeviceErrorStatus(IDevice *device, u32 status) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatterySocRep(float *out_percent, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatterySocVf(float *out_percent, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryFullCapacity(int *out_mah, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryRemainingCapacity(int *out_mah, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryPercentageMinimumAlertThreshold(IDevice *device, float percentage) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryPercentageMaximumAlertThreshold(IDevice *device, float percentage) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryPercentageFullThreshold(IDevice *device, float percentage) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryAverageCurrent(int *out_ma, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryCurrent(int *out_ma, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryInternalState(void *dst, size_t *out_size, IDevice *device, size_t dst_size) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryInternalState(IDevice *device, const void *src, size_t src_size) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryNeedToRestoreParameters(bool *out, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryNeedToRestoreParameters(IDevice *device, bool en) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::IsBatteryI2cShutdownEnabled(bool *out, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryI2cShutdownEnabled(IDevice *device, bool en) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::IsBatteryPresent(bool *out, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryCycles(int *out, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryCycles(IDevice *device, int cycles) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryAge(float *out_percent, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryTemperature(float *out_c, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryMaximumTemperature(float *out_c, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryTemperatureMinimumAlertThreshold(IDevice *device, float c) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryTemperatureMaximumAlertThreshold(IDevice *device, float c) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryVCell(int *out_mv, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryAverageVCell(int *out_mv, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryAverageVCellTime(TimeSpan *out, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryVoltageMinimumAlertThreshold(IDevice *device, int mv) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::GetBatteryOpenCircuitVoltage(int *out_mv, IDevice *device) {
        /* TODO */
        AMS_ABORT();
    }

    Result BatteryDriver::SetBatteryVoltageMaximumAlertThreshold(IDevice *device, int mv) {
        /* TODO */
        AMS_ABORT();
    }

}
