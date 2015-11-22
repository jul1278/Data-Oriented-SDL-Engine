//
// Created by Julian  on 17/11/15.
//

#ifndef SDL_RTS_ICOMPONENT_H
#define SDL_RTS_ICOMPONENT_H

class IComponent
{
private:

    int id;

public:

    IComponent(int id);
    ~IComponent();

    int Id() { return this->id;}

    virtual void Update() = 0;

    virtual void SendMessage(IMessage* message);
    virtual void ReceiveMessage(IMessage* message);
};


#endif //SDL_RTS_ICOMPONENT_H
