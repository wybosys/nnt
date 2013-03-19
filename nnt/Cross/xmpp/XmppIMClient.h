
# ifndef __WSI_XMPP_IMCLIENT_C44B02CF6C46437CAEB8B614343E6C39_H_INCLUDED
# define __WSI_XMPP_IMCLIENT_C44B02CF6C46437CAEB8B614343E6C39_H_INCLUDED

# include "XmppClient.h"

XMPP_HEADER_BEGIN

WSIDECL_PRIVATE_HEAD_CXX(IMClient);

WSICLASS(IMClient);

class IMClient
: public Client
{
    WSIDECL_PRIVATE_CXX(IMClient);
    typedef Client super;
    
public:
    
    IMClient();
    ~IMClient();
    
    //! read counter.
    ulong roster_counter() const;
    
    WSIDECL_SIGNALS_SLOTS
    
};

WSI_STATIC_CONST cxx::signal_t kSignalGotPresence = "::wsi::xmpp::im::presence::got";
WSI_STATIC_CONST cxx::signal_t kSignalRosterComplete = "::wsi::xmpp::im::roster::complete";
WSI_STATIC_CONST cxx::signal_t kSignalNewMessage = "::wsi::xmpp::im::message::new";
WSI_STATIC_CONST cxx::signal_t kSignalHtmlMessage = "::wsi::xmpp::im::message::html::new";
WSI_STATIC_CONST cxx::signal_t kSignalShowChanged = "::wsi::xmpp::im::show::changed";
WSI_STATIC_CONST cxx::signal_t kSignalGotVCard = "::wsi::xmpp::im::vcardtemp::got";
WSI_STATIC_CONST cxx::signal_t kSignalXPhoto = "::wsi::xmpp::im::vcardtemp::x::photo";
WSI_STATIC_CONST cxx::signal_t kSignalGotField = "::wsi::xmpp::im::field::got";
WSI_STATIC_CONST cxx::signal_t kSignalMUCSubject = "::wsi::xmpp::im::muc::subject";
WSI_STATIC_CONST cxx::signal_t kSignalMUCPresence = "::wsi::xmpp::im::muc::presence::got";

XMPP_HEADER_END

# endif