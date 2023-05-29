#ifndef AA_AUTO_H
#define AA_AUTO_H
#include <QFrame>

#include <glib.h>
#include <functional>
#include "hu_aap.h"
#include "src/components/content/android-head-unit/aa_auto_controller.h"

struct gst_app_t {
    GMainLoop *loop;
};

unsigned int get_cur_timestamp();

class AAutoService {

private:
    float g_dpi_scalefactor;

public:
    explicit AAutoService(QFrame *widget);
    void start(AAController *controller);

    IHUAnyThreadInterface *g_hu;
    QFrame *widget;
    int gst_loop(gst_app_t *app);
    gst_app_t gst_app;

};

#endif
