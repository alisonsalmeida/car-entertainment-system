// #include <glib.h>
#include <stdio.h>
#define GDK_VERSION_MIN_REQUIRED (GDK_VERSION_3_10)
// #include <gdk/gdk.h>
#include <time.h>

//This gets defined by SDL and breaks the protobuf headers
#undef Status

#include "hu_uti.h"
#include "hu_aap.h"

#include "outputs.h"
#include "callbacks.h"
#include "aa_auto.h"


AAutoService::AAutoService(QFrame *widget)
{
    this->widget = widget;
}

void AAutoService::start(AAController *controller)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    std::map<std::string, std::string> settings;

    hu_log_library_versions();
    this->g_dpi_scalefactor = 1;

    gst_app_t *app = &gst_app;
    int ret = 0;
    errno = 0;

    gst_init(NULL, NULL);

    //loop to emulate the caar
    while(true)
    {
        AAutoController aa_auto_controller;
        controller->set_event_callbacks(&aa_auto_controller);

        DesktopEventCallbacks callbacks(this);
        HUServer headunit(callbacks, settings);

        /* Start AA processing */
        ret = headunit.hu_aap_start(true, true);

        if (ret < 0) {
            printf("Phone is not connected. Connect a supported phone and restart.\n");
            continue;
        }

        callbacks.connected = true;
        this->g_hu = &headunit.GetAnyThreadInterface();
        callbacks.setThreadInterface(this->g_hu);
        aa_auto_controller.evCallback = &callbacks;

        // commandCallbacks.eventCallbacks = &callbacks;

        /* Start gstreamer pipeline and main loop */
        ret = gst_loop(app);
        if (ret < 0) {
            printf("STATUS:gst_loop() ret: %d\n", ret);
        }

        /* Stop AA processing */
        ret = headunit.hu_aap_shutdown();
        if (ret < 0) {
            printf("STATUS:hu_aap_stop() ret: %d\n", ret);
            continue;
        }

        this->g_hu = nullptr;
        callbacks.setThreadInterface(nullptr);
        aa_auto_controller.evCallback = nullptr;
    }

}
int AAutoService::gst_loop(gst_app_t *app)
{
    int ret;
    GstStateChangeReturn state_ret;

    app->loop = g_main_loop_new(NULL, FALSE);
    printf("Starting Android Auto.................\n");
    g_main_loop_run(app->loop);
    return ret;
}

unsigned int get_cur_timestamp() {
    struct timespec tp;
    /* Fetch the time stamp */
    clock_gettime(CLOCK_REALTIME, &tp);

    return tp.tv_sec * 1000000 + tp.tv_nsec / 1000;
}
