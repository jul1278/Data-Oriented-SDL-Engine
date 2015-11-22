//
// Created by Julian  on 18/11/15.
//

#ifndef SDL_RTS_IMESSAGE_H
#define SDL_RTS_IMESSAGE_H

enum MessageType
{
    GET_TRANSFORM,
    SET_TRANSFORM
};


class IMessage
{
private:

    MessageType messageType;

public:

    IMessage(MessageType messageType);
    ~IMessage();

    MessageType GetMessageType() const {return this->messageType;}

};

class GetTransformMessage : public IMessage
{
private:

public:

    GetTransformMessage(const MessageType &messageType, float x, float y, float angle) : IMessage(messageType)
    {

    }
};


#endif //SDL_RTS_IMESSAGE_H
