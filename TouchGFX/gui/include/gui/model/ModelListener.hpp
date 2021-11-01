#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    virtual ~ModelListener() {}
    void bind(Model* m)
    {
        model = m;
    }
    virtual void updatePinPad(char (*pinNumbers)[10][2]){}
    virtual void updateRngStatusModel(bool value){}

protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
