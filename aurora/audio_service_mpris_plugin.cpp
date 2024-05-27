/**
 * SPDX-FileCopyrightText: Copyright 2023 Open Mobile Platform LLC <community@omp.ru>
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <audio_service_mpris/audio_service_mpris_plugin.h>


//#include <flutter/method-channel.h>
//#include <flutter/platform-methods.h>
#include <sys/utsname.h>

// namespace PlatformVersion {

// constexpr auto Version = "Linux";

// }


AudioServiceMprisPlugin::AudioServiceMprisPlugin(
    PluginRegistrar* registrar,
    std::unique_ptr<MethodChannel> methodChannel
) : m_methodChannel(std::move(methodChannel))
{
    RegisterMethodHandler();
}

void AudioServiceMprisPlugin::RegisterWithRegistrar(PluginRegistrar* registrar)
{
    auto methodChannel = std::make_unique<MethodChannel>(
        registrar->messenger(), "audio_service_mpris",
        &flutter::StandardMethodCodec::GetInstance());


    std::unique_ptr<AudioServiceMprisPlugin> plugin(new AudioServiceMprisPlugin(
        registrar,
        std::move(methodChannel)
    ));

    // Register plugin
    registrar->AddPlugin(std::move(plugin));

}

void AudioServiceMprisPlugin::RegisterMethodHandler()
{


    m_methodChannel->SetMethodCallHandler(
        [this](const MethodCall& call, std::unique_ptr<MethodResult> result) {
            if (call.method_name().compare("getPlatformVersion") == 0) {
                result->Success(onGetPlatformVersion(call));
            } else {
                result->Success();
            }
        });


}

std::string AudioServiceMprisPlugin::onGetPlatformVersion(const MethodCall &call)
{
    return "Linux";
}

void AudioServiceMprisPlugin::unimplemented(const MethodCall &call)
{
    //call.SendSuccessResponse(nullptr);
}
