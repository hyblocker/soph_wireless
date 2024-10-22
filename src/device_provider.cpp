#include "device_provider.h"

vr::EVRInitError DeviceProvider::Init(vr::IVRDriverContext* pDriverContext) {
    VR_INIT_SERVER_DRIVER_CONTEXT(pDriverContext);

    vr::VRDriverLog()->Log("Hello world!");
    my_left_device_ = std::make_unique<ControllerDevice>(vr::TrackedControllerRole_LeftHand);
    vr::VRServerDriverHost()->TrackedDeviceAdded("SOPL1234",
        vr::TrackedDeviceClass_Controller,
        my_left_device_.get());

    my_right_device_ = std::make_unique<ControllerDevice>(vr::TrackedControllerRole_RightHand);
    vr::VRServerDriverHost()->TrackedDeviceAdded("SOPR5678",
        vr::TrackedDeviceClass_Controller,
        my_right_device_.get());

    return vr::VRInitError_None;
}

void DeviceProvider::Cleanup() {
    VR_CLEANUP_SERVER_DRIVER_CONTEXT();
}

const char* const* DeviceProvider::GetInterfaceVersions() {
    return vr::k_InterfaceVersions;
}

void DeviceProvider::RunFrame() {
    if (my_left_device_ != nullptr) {
        my_left_device_->RunFrame();
    }

    if (my_right_device_ != nullptr) {
        my_right_device_->RunFrame();
    }
}

bool DeviceProvider::ShouldBlockStandbyMode() {
    return false;
}

void DeviceProvider::EnterStandby() {

}

void DeviceProvider::LeaveStandby() {

}