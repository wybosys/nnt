
# include "Core.h"
# include "XmppIMClient.h"

# include "XmppResponseFactory.h"
# include "XmppPresenceFactory.h"
# include "XmppMessageFactory.h"
# include "XmppInfoqueryFactory.h"

# include "im/XimShow.h"
# include "im/XimPriority.h"
# include "im/XimXPhoto.h"
# include "im/XimMessage.h"
# include "im/XimComposing.h"
# include "im/XimActive.h"

# include "xep/XepVersion.h"
# include "xep/XepXHtmlIm.h"
# include "xep/XepSubject.h"
# include "xep/XepMUC.h"

XMPP_BEGIN

NNTDECL_PRIVATE_BEGIN_CXX(IMClient)

void init()
{
    cnt_roster = 0;
}

void dealloc()
{
    PASS;
}

//! counter,
ulong cnt_roster;

NNTDECL_PRIVATE_END_CXX

IMClient::IMClient()
{
    NNTDECL_PRIVATE_CONSTRUCT(IMClient);
    
    // register handle.
    // register presence.
    PresenceFactory* fac_pres = _response_factory()->factory_presence();
    fac_pres->register_object(im::Show::FacObj);
    fac_pres->register_object(im::Priority::FacObj);
    fac_pres->register_object(im::XPhoto::FacObj);
    fac_pres->register_object(xep::muc::Presence::FacObj);
    
    // register message.
    MessageFactory* fac_msg = _response_factory()->factory_message();
    fac_msg->register_object(im::Composing::FacObj);
    fac_msg->register_object(im::Message::FacObj);
    fac_msg->register_object(im::Active::FacObj);
    fac_msg->register_object(xep::HtmlMessage::FacObj);
    fac_msg->register_object(xep::Subject::FacObj);
    
    // register iq.
    InfoqueryFactory* fac_iq = _response_factory()->factory_iq();
    fac_iq->register_object(xep::Version::FacObj);
}

IMClient::~IMClient()
{
    NNTDECL_PRIVATE_DESTROY();
}

NNTDECL_SIGNALS_BEGIN(IMClient, super)
NNT_SIGNAL(kSignalGotPresence)
NNT_SIGNAL(kSignalRosterComplete)
NNT_SIGNAL(kSignalNewMessage)
NNT_SIGNAL(kSignalHtmlMessage)
NNT_SIGNAL(kSignalShowChanged)
NNT_SIGNAL(kSignalGotVCard)
NNT_SIGNAL(kSignalXPhoto)
NNT_SIGNAL(kSignalGotField)
NNT_SIGNAL(kSignalMUCSubject)
NNT_SIGNAL(kSignalMUCPresence)
NNTDECL_SIGNALS_END

ulong IMClient::roster_counter() const
{
    return ++d_ptr->cnt_roster;
}

XMPP_END