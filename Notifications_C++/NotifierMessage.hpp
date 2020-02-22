#ifndef NOTIFIERMESSAGE_HPP
#define NOTIFIERMESSAGE_HPP
#include "ch.hpp"
#include "hal.h"

template <class MsgType>
class NotifierMessage
{
protected:
    uint16_t ref_count;
public:
    bool send(chibios_rt::Mailbox<MsgType, 1> *, MsgType *);
    bool dereference(void);
    void reset(void);
    NotifierMessage();
}__attribute__((aligned(sizeof(stkalign_t))));

#endif // NOTIFIERMESSAGE_HPP
