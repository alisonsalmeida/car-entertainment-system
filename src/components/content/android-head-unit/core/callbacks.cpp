#include "callbacks.h"
#include "outputs.h"
#include "glib_utils.h"
#include "bt/ub_bluetooth.h"
#include "aa_auto.h"


// DesktopEventCallbacks::DesktopEventCallbacks() :
//     connected(false),
//     videoFocus(false),
//     audioFocus(false)
// {
// }

DesktopEventCallbacks::DesktopEventCallbacks(AAutoService *aa_service) :
    connected(false),
    videoFocus(false),
    audioFocus(false)
{
    this->aa_service = aa_service;
    g_hu = this->aa_service->g_hu;
    gst_app = this->aa_service->gst_app;
}

DesktopEventCallbacks::~DesktopEventCallbacks() {

}

int DesktopEventCallbacks::MediaPacket(int chan, uint64_t timestamp, const byte *buf, int len) {

    if (chan == AA_CH_VID && videoOutput) {
        videoOutput->MediaPacket(timestamp, buf, len);
    } else if (chan == AA_CH_AUD && audioOutput) {
        audioOutput->MediaPacketAUD(timestamp, buf, len);
    } else if (chan == AA_CH_AU1 && audioOutput) {
        audioOutput->MediaPacketAU1(timestamp, buf, len);
    }
    return 0;
}

void DesktopEventCallbacks::change_size_render(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if(videoOutput){
        videoOutput->ChangeSizeRender(x, y, width, height);
    }
}

void DesktopEventCallbacks::set_state_player(bool play) {
    if (videoOutput) {
        videoOutput->SetStatePlayer(play);
    }
}

int DesktopEventCallbacks::MediaStart(int chan) {
    if (chan == AA_CH_MIC) {
        printf("SHAI1 : Mic Started\n");
        micInput.Start(g_hu);
    }
    return 0;
}

int DesktopEventCallbacks::MediaStop(int chan) {
    if (chan == AA_CH_MIC) {
        micInput.Stop();
        printf("SHAI1 : Mic Stopped\n");
    }
    return 0;
}

void DesktopEventCallbacks::MediaSetupComplete(int chan) {
    printf("media setup complete \n");
    if (chan == AA_CH_VID) {
        VideoFocusHappened(true, VIDEO_FOCUS_REQUESTOR::HEADUNIT);
    }
}

void DesktopEventCallbacks::DisconnectionOrError() {
    printf("DisconnectionOrError\n");
    g_main_loop_quit(this->aa_service->gst_app.loop);
}

void DesktopEventCallbacks::CustomizeOutputChannel(int chan, HU::ChannelDescriptor::OutputStreamChannel &streamChannel) {
#if ASPECT_RATIO_FIX
    if (chan == AA_CH_VID) {
        auto videoConfig = streamChannel.mutable_video_configs(0);
        videoConfig->set_margin_height(30);
    }
#endif
}

void DesktopEventCallbacks::AudioFocusRequest(int chan, const HU::AudioFocusRequest &request)  {
    run_on_main_thread([this, chan, request](){
        HU::AudioFocusResponse response;
        if (request.focus_type() == HU::AudioFocusRequest::AUDIO_FOCUS_RELEASE) {
            audioOutput.reset();
            response.set_focus_type(HU::AudioFocusResponse::AUDIO_FOCUS_STATE_LOSS);
            audioFocus = false;
        } else {
            if (!audioOutput) {
                audioOutput.reset(new AudioOutput());
            }
            response.set_focus_type(HU::AudioFocusResponse::AUDIO_FOCUS_STATE_GAIN);
            audioFocus = true;
        }

        g_hu->hu_queue_command([chan, response](IHUConnectionThreadInterface & s) {
            s.hu_aap_enc_send_message(0, chan, HU_PROTOCOL_MESSAGE::AudioFocusResponse, response);
        });
        return false;
    });
}

void DesktopEventCallbacks::VideoFocusRequest(int chan, const HU::VideoFocusRequest &request) {
    VideoFocusHappened(request.mode() == HU::VIDEO_FOCUS_MODE_FOCUSED, VIDEO_FOCUS_REQUESTOR::ANDROID_AUTO);
}

std::string DesktopEventCallbacks::GetCarBluetoothAddress()
{
    return get_bluetooth_mac_address();
}

void DesktopEventCallbacks::HandlePhoneStatus(IHUConnectionThreadInterface& stream, const HU::PhoneStatus& phoneStatus) {
    printf("HandlePhoneStatus: %s\n", phoneStatus.DebugString().c_str());
}

/*
void DesktopEventCallbacks::ShowingGenericNotifications(IHUConnectionThreadInterface& stream, bool bIsShowing) {
    printf("ShowingGenericNotifications: %s\n", bIsShowing ? "true" : "false");
}
*/

void DesktopEventCallbacks::VideoFocusHappened(bool hasFocus, VIDEO_FOCUS_REQUESTOR videoFocusRequestor) {
    run_on_main_thread([this, hasFocus, videoFocusRequestor](){
        if ((bool)videoOutput != hasFocus) {
            videoOutput.reset(hasFocus ? new VideoOutput(this) : nullptr);
        }
        
        videoFocus = hasFocus;
        bool unrequested = videoFocusRequestor != VIDEO_FOCUS_REQUESTOR::ANDROID_AUTO;

        g_hu->hu_queue_command([hasFocus, unrequested](IHUConnectionThreadInterface & s) {
            HU::VideoFocus videoFocusGained;
            videoFocusGained.set_mode(hasFocus ? HU::VIDEO_FOCUS_MODE_FOCUSED : HU::VIDEO_FOCUS_MODE_UNFOCUSED);
            videoFocusGained.set_unrequested(unrequested);
            s.hu_aap_enc_send_message(0, AA_CH_VID, HU_MEDIA_CHANNEL_MESSAGE::VideoFocus, videoFocusGained);
        });
        
        return false;
    });
}

DesktopCommandServerCallbacks::DesktopCommandServerCallbacks()
{

}

bool DesktopCommandServerCallbacks::IsConnected() const
{
    if (eventCallbacks)
    {
        return eventCallbacks->connected;
    }
    return false;
}

bool DesktopCommandServerCallbacks::HasAudioFocus() const
{
    if (eventCallbacks)
    {
        return eventCallbacks->audioFocus;
    }
    return false;
}

bool DesktopCommandServerCallbacks::HasVideoFocus() const
{
    if (eventCallbacks)
    {
        return eventCallbacks->videoFocus;
    }
    return false;
}

void DesktopCommandServerCallbacks::TakeVideoFocus()
{
    if (eventCallbacks && eventCallbacks->connected)
    {
        eventCallbacks->VideoFocusHappened(true, VIDEO_FOCUS_REQUESTOR::HEADUNIT);
    }
}

std::string DesktopCommandServerCallbacks::GetLogPath() const
{
    //no log
    return std::string();
}

void AAutoController::set_render_rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const {
    if(evCallback){
        evCallback->change_size_render(x, y, width, height);
    }
}

void AAutoController::mouse_press_event(unsigned int x, unsigned int y) const {
    if(evCallback){
        send_mouse_cmd(HU::TouchInfo::TOUCH_ACTION_PRESS, x, y);
    }
}

void AAutoController::mouse_release_event(unsigned int x, unsigned int y) const {
    if (evCallback){
        send_mouse_cmd(HU::TouchInfo::TOUCH_ACTION_RELEASE, x, y);
    }
}

void AAutoController::mouse_move_event(unsigned int x, unsigned int y) const {
    if (evCallback){
        send_mouse_cmd(HU::TouchInfo::TOUCH_ACTION_DRAG, x, y);
    }
}

void AAutoController::set_state_player(bool play) const {
    if (evCallback){
        evCallback->set_state_player(play);
    }
}

void AAutoController::send_mouse_cmd(HU::TouchInfo::TOUCH_ACTION action, unsigned int x, unsigned int y) const {
     // pega o tamanho atual do widget
     QSize size = evCallback->aa_service->widget->size();
     float normx = float(x) / float(size.width());
     float normy = float(y) / float(size.height());

     //normaliza para a resolucao do android auto
     x = (unsigned int) (normx * 1280);
     y = (unsigned int) (normy * 720);

     IHUAnyThreadInterface *cmd = evCallback->g_hu;

     cmd->hu_queue_command([action, x, y](IHUConnectionThreadInterface & s) {
         HU::InputEvent inputEvent;
         inputEvent.set_timestamp(get_cur_timestamp());
         HU::TouchInfo* touchEvent = inputEvent.mutable_touch();
         touchEvent->set_action(action);
         HU::TouchInfo::Location* touchLocation = touchEvent->add_location();
         touchLocation->set_x(x);
         touchLocation->set_y(y);
         touchLocation->set_pointer_id(0);

         /* Send touch event */

         int ret = s.hu_aap_enc_send_message(0, AA_CH_TOU, HU_INPUT_CHANNEL_MESSAGE::InputEvent, inputEvent);
         if (ret < 0) {
             printf("aa_touch_event(): hu_aap_enc_send() failed with (%d)\n", ret);
         }
     });
}
