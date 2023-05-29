#ifndef CALLBACKS_H
#define CALLBACKS_H

#pragma once
#include <atomic>
#include "audio.h"
#include "command_server.h"
#include "aa_auto.h"
#include <asoundlib.h>
#include "src/components/content/android-head-unit/aa_auto_controller.h"

class VideoOutput;
class AudioOutput;

enum class VIDEO_FOCUS_REQUESTOR {
    HEADUNIT, // headunit (we) has requested video focus
    ANDROID_AUTO // AA phone app has requested video focus
};

class DesktopEventCallbacks : public IHUConnectionThreadEventCallbacks {
        std::unique_ptr<VideoOutput> videoOutput;
        std::unique_ptr<AudioOutput> audioOutput;

        MicInput micInput;
public:
        DesktopEventCallbacks(AAutoService *aa_service);
        ~DesktopEventCallbacks();

        virtual int MediaPacket(int chan, uint64_t timestamp, const byte * buf, int len) override;
        virtual int MediaStart(int chan) override;
        virtual int MediaStop(int chan) override;
        virtual void MediaSetupComplete(int chan) override;
        virtual void DisconnectionOrError() override;
        virtual void CustomizeOutputChannel(int chan, HU::ChannelDescriptor::OutputStreamChannel& streamChannel) override;
        virtual void AudioFocusRequest(int chan, const HU::AudioFocusRequest& request) override;
        virtual void VideoFocusRequest(int chan, const HU::VideoFocusRequest& request) override;

        virtual void HandlePhoneStatus(IHUConnectionThreadInterface& stream, const HU::PhoneStatus& phoneStatus) override;
        //Doesn't actually work yet
        //virtual void ShowingGenericNotifications(IHUConnectionThreadInterface& stream, bool bIsShowing) override;

        virtual std::string GetCarBluetoothAddress() override;

        void VideoFocusHappened(bool hasFocus, VIDEO_FOCUS_REQUESTOR videoFocusRequestor);
        void setThreadInterface(IHUAnyThreadInterface *ghu) {this->g_hu = ghu;};
        void change_size_render(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
        void set_state_player(bool play);

        std::atomic<bool> connected;
        std::atomic<bool> videoFocus;
        std::atomic<bool> audioFocus;

        AAutoService *aa_service;
        IHUAnyThreadInterface *g_hu;
        gst_app_t gst_app{};
};

class DesktopCommandServerCallbacks : public ICommandServerCallbacks
{
public:
    DesktopCommandServerCallbacks();

    DesktopEventCallbacks* eventCallbacks = nullptr;

    virtual bool IsConnected() const override;
    virtual bool HasAudioFocus() const override;
    virtual bool HasVideoFocus() const override;
    virtual void TakeVideoFocus() override;
    virtual std::string GetLogPath() const override;
};


class AAutoController: public IAAutoController
{
public:
    DesktopEventCallbacks *evCallback = nullptr;

    AAutoController() {};

    virtual void set_render_rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const override;
    virtual void mouse_press_event(unsigned int x, unsigned int y) const override;
    virtual void mouse_release_event(unsigned int x, unsigned int y) const override;
    virtual void mouse_move_event(unsigned int x, unsigned int y) const override;
    virtual void set_state_player(bool play) const override;

private:
    virtual void send_mouse_cmd(HU::TouchInfo::TOUCH_ACTION action, unsigned int x, unsigned int y) const override;
};

#endif
