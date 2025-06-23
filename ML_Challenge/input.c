#include "input.h"

#define JS_EVENT_BUTTON 0x01
#define JS_EVENT_AXIS 0x02
#define JS_EVENT_INIT 0x80

#define CONTROLLER_BUTTON_A 0
#define CONTROLLER_BUTTON_B 1
#define CONTROLLER_BUTTON_X 2
#define CONTROLLER_BUTTON_Y 3
#define CONTROLLER_BUTTON_LEFTSHOULDER 4
#define CONTROLLER_BUTTON_RIGHTSHOULDER 5
#define CONTROLLER_BUTTON_SELECT 6
#define CONTROLLER_BUTTON_START 7
#define CONTROLLER_BUTTON_MODE 8
#define CONTROLLER_BUTTON_L3 9
#define CONTROLLER_BUTTON_R3 10

#define CONTROLLER_AXIS_LEFTX 0
#define CONTROLLER_AXIS_LEFTY 1
#define CONTROLLER_AXIS_RIGHTX 3
#define CONTROLLER_AXIS_RIGHTY 4
#define CONTROLLER_AXIS_TRIGGERLEFT 2
#define CONTROLLER_AXIS_TRIGGERRIGHT 5
#define CONTROLLER_AXIS_DPADX 6
#define CONTROLLER_AXIS_DPADY 7

int g_joystick = -1;

void Input_update(Input *self)
{
    self->startPressed = false;
    //self->superButtonPressed = false;
    self->modePressed = false;
    self->speedLvlMinus = false;
    self->speedLvlPlus = false;
    
    struct js_event evt = { 0 };
    while (read (g_joystick, &evt, sizeof(evt)) > 0)
    {
        switch (evt.type)
        {
        case JS_EVENT_BUTTON:
            if (evt.value == 1)
            {
                Input_updateControllerButtonDown(self, evt.number);
            }
            else
            {
                Input_updateControllerButtonUp(self, evt.number);
            }
            break;

        case JS_EVENT_AXIS:
            Input_updateControllerAxisMotion(self, evt.number, evt.value);
            break;

        case JS_EVENT_INIT | JS_EVENT_BUTTON:
            break;

        case JS_EVENT_INIT | JS_EVENT_AXIS:
            break;

        default:
            break;
        }
    }
}

void Input_updateControllerButtonDown(Input *self, int button)
{
    switch (button)
    {
    case CONTROLLER_BUTTON_A:
        self->forwardDown = true;
        break;
    case CONTROLLER_BUTTON_B:
        self->backwardDown = true;
        break;
    case CONTROLLER_BUTTON_X:
        if (self->autoButtonToggle == false)
        {
            self->autoButtonToggle = true;
        }else{
            self->autoButtonToggle = false;
        }
        
        break;
    case CONTROLLER_BUTTON_Y:
        self->superButtonPressed = true;
        break;
    case CONTROLLER_BUTTON_START:
        printf("START\n");
        self->startPressed = true;
        break;
    case CONTROLLER_BUTTON_SELECT:
        printf("SELECT\n");
        break;
    case CONTROLLER_BUTTON_MODE:
        //printf("MODE\n");
        self->modePressed = true;
        break;
    case CONTROLLER_BUTTON_LEFTSHOULDER:
        self->speedLvlMinus = true;
        break;
    case CONTROLLER_BUTTON_RIGHTSHOULDER:
        self->speedLvlPlus = true;
        break;
    case CONTROLLER_BUTTON_L3:
        break;
    case CONTROLLER_BUTTON_R3:
        break;
    default: break;
    }
}

void Input_updateControllerButtonUp(Input *self, int button)
{
    switch (button)
    {
    case CONTROLLER_BUTTON_A:
        self->forwardDown = false;
        break;
    case CONTROLLER_BUTTON_B:
        self->backwardDown = false;
        break;
    case CONTROLLER_BUTTON_X:
        break;
    case CONTROLLER_BUTTON_Y:
        self->superButtonPressed = false;
        break;
    case CONTROLLER_BUTTON_START:
        break;
    case CONTROLLER_BUTTON_SELECT:
        break;
    case CONTROLLER_BUTTON_MODE:
        break;
    case CONTROLLER_BUTTON_LEFTSHOULDER:
        self->speedLvlMinus = false;
        break;
    case CONTROLLER_BUTTON_RIGHTSHOULDER:
        self->speedLvlPlus = false;
        break;
    case CONTROLLER_BUTTON_L3:
        break;
    case CONTROLLER_BUTTON_R3:
        break;
    default: break;
    }
}

void Input_updateControllerAxisMotion(Input *self, int axis, short value)
{
    switch (axis)
    {
    case CONTROLLER_AXIS_LEFTX:
        self->leftAxisX = (float)value / 32767.f;
        break;

    case CONTROLLER_AXIS_LEFTY:
        self->leftAxisY = (float)value / 32767.f;
        break;

    case CONTROLLER_AXIS_DPADX:
        self->leftAxisX = (float)value / 32767.f;
        break;

    case CONTROLLER_AXIS_DPADY:
        self->leftAxisY = (float)value / 32767.f;
        break;

    case CONTROLLER_AXIS_RIGHTX:
        self->rightAxisX = (float)value / 32767.f;
        break;

    case CONTROLLER_AXIS_RIGHTY:
        self->rightAxisY = (float)value / 32767.f;
        break;

    case CONTROLLER_AXIS_TRIGGERLEFT:
        break;

    case CONTROLLER_AXIS_TRIGGERRIGHT:
        break;

    default: break;
    }
}
