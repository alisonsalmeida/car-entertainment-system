//
// Created by alison on 03/04/23.
//

#ifndef AA_AUTO_CONTROLLER_H
#define AA_AUTO_CONTROLLER_H

class IAAutoController {
public:
    virtual void set_render_rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) const = 0;
    virtual void mouse_press_event(unsigned int x, unsigned int y) const = 0;
    virtual void mouse_release_event(unsigned int x, unsigned int y) const = 0;
    virtual void mouse_move_event(unsigned int x, unsigned int y) const = 0;
    virtual void set_state_player(bool play) const = 0;

private:
    virtual void send_mouse_cmd(HU::TouchInfo::TOUCH_ACTION action, unsigned int x, unsigned int y) const = 0;
};


class AAController {
public:
    IAAutoController *aa_auto_controller = nullptr;

    AAController() {};
    void set_event_callbacks(IAAutoController *callbacks) {
        this->aa_auto_controller = callbacks;
    };

    void aa_set_render_rectangle(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
        this->aa_auto_controller->set_render_rectangle(x, y, width, height);
    }

    void aa_mouse_press_event(unsigned int x, unsigned int y) {
        this->aa_auto_controller->mouse_press_event(x, y);
    }

    void aa_mouse_release_event(unsigned int x, unsigned int y) {
        this->aa_auto_controller->mouse_release_event(x, y);
    }

    void aa_mouse_move_event(unsigned int x, unsigned int y) {
        this->aa_auto_controller->mouse_move_event(x, y);
    }

    void aa_set_state_player(bool play) {
        this->aa_auto_controller->set_state_player(play);
    }
};
#endif //AA_AUTO_CONTROLLER_H
