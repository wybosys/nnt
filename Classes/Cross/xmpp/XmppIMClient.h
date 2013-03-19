
# ifndef __NNT_XMPP_IMCLIENT_C44B02CF6C46437CAEB8B614343E6C39_H_INCLUDED
# define __NNT_XMPP_IMCLIENT_C44B02CF6C46437CAEB8B614343E6C39_H_INCLUDED

# include "XmppClient.h"

XMPP_HEADER_BEGIN

NNTDECL_PRIVATE_HEAD_CXX(IMClient);

NNTCLASS(IMClient);

class IMClient
: public Client
{
    NNTDECL_PRIVATE_CXX(IMClient);
    typedef Client super;
    
public:
    
    IMClient();
    ~IMClient();
    
    //! read counter.
    ulong roster_counter() const;
    
    NNTDECL_SIGNALS_SLOTS
    
};

NNT_STATIC_CONST cxx::signal_t kSignalGotPresence = "::wsi::xmpp::im::presence::got";
NNT_STATIC_CONST cxx::signal_t kSignalRosterComplete = "::wsi::xmpp::im::roster::complete";
NNT_STATIC_CONST cxx::signal_t kSignalNewMessage = "::wsi::xmpp::im::message::new";
NNT_STATIC_CONST cxx::signal_t kSignalHtmlMessage = "::wsi::xmpp::im::message::html::new";
NNT_STATIC_CONST cxx::signal_t kSignalShowChanged = "::wsi::xmpp::im::show::changed";
NNT_STATIC_CONST cxx::signal_t kSignalGotVCard = "::wsi::xmpp::im::vcardtemp::got";
NNT_STATIC_CONST cxx::signal_t kSignalXPhoto = "::wsi::xmpp::im::vcardtemp::x::photo";
NNT_STATIC_CONST cxx::signal_t kSignalGotField = "::wsi::xmpp::im::field::got";
NNT_STATIC_CONST cxx::signal_t kSignalMUCSubject = "::wsi::xmpp::im::muc::subject";
NNT_STATIC_CONST cxx::signal_t kSignalMUCPresence = "::wsi::xmpp::im::muc::presence::got";

XMPP_HEADER_END

# endif