#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    char pinNumbers[10][2]; //The values of the pinpad
    bool pinPadReady;
    bool guiRngActive;
public:
    Model();
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void tick();
    void updateModelPinPad();
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
