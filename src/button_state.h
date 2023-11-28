#ifndef BUTTON_STATE_H
#define BUTTON_STATE_H

enum ButtonState
{
    NORMAL = 0,
    PRESSED = 1
};

class ButtonStateModel
{
public:
    void ChangeState()
    {
        state_ = state_ == NORMAL ? PRESSED : NORMAL;
    }

    void Reset()
    {
        state_ = NORMAL;
    }

    ButtonState GetState() const
    {
        return state_;
    }

private:
    ButtonState state_{NORMAL};
};

#endif
