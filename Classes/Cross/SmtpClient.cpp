
# include "Core.h"
# include "SmtpClient.h"

# include <smtp/config.h>
# include <smtp/auth-client.h>
# include <smtp/libesmtp.h>

NNT_BEGIN_CXX
NNT_BEGIN_NS(cross)

NNTDECL_PRIVATE_BEGIN_CXX(SmtpClient)

static int authinteract (auth_client_request_t request, char **result, int fields,
                         void *arg)
{
    SmtpClient* client = (SmtpClient*)arg;
    core::data da = client->get_user();
    uint sz = MIN(da.length(), fields);
    memcpy(result, da.bytes(), sz);
    return 1;
};

static int tlsinteract (char *buf, int buflen, int rwflag, void *arg)
{
    SmtpClient* client = (SmtpClient*)arg;
    core::data da = client->get_password();
    uint sz = MIN(da.length(), buflen);
    memcpy(buf, da.bytes(), sz);
    return 1; 
}

static const char *readlinefp_cb (void **buf, int *len, void *arg)
{
    SmtpClient* client = (SmtpClient*)arg;
    core::data da = core::type_cast<core::data>(client->content.message);
    *buf = malloc(da.length());
    memcpy(*buf, da.bytes(), da.length());
    *len = da.length();
    return (char const*)*buf;
}

static void print_recipient_status (smtp_recipient_t recipient,
                             const char *mailbox, void *arg)
{
    const smtp_status_t *status;    
    status = smtp_recipient_status (recipient);
    printf ("%s: %d %s", mailbox, status->code, status->text);
}

static void event_cb (smtp_session_t session, int event_no, void *arg,...)
{
    va_list alist;
    int *ok;
    
    va_start(alist, arg);
    switch(event_no) {
        case SMTP_EV_CONNECT: 
        case SMTP_EV_MAILSTATUS:
        case SMTP_EV_RCPTSTATUS:
        case SMTP_EV_MESSAGEDATA:
        case SMTP_EV_MESSAGESENT:
        case SMTP_EV_DISCONNECT: break;
        case SMTP_EV_WEAK_CIPHER: {
            int bits;
            bits = va_arg(alist, long); ok = va_arg(alist, int*);
            printf("SMTP_EV_WEAK_CIPHER, bits=%d - accepted.\n", bits);
            *ok = 1; break;
        }
        case SMTP_EV_STARTTLS_OK:
            puts("SMTP_EV_STARTTLS_OK - TLS started here."); break;
        case SMTP_EV_INVALID_PEER_CERTIFICATE: {
            long vfy_result;
            vfy_result = va_arg(alist, long); ok = va_arg(alist, int*);
            //*ok = handle_invalid_peer_certificate(vfy_result);
            break;
        }
        case SMTP_EV_NO_PEER_CERTIFICATE: {
            ok = va_arg(alist, int*); 
            puts("SMTP_EV_NO_PEER_CERTIFICATE - accepted.");
            *ok = 1; break;
        }
        case SMTP_EV_WRONG_PEER_CERTIFICATE: {
            ok = va_arg(alist, int*);
            puts("SMTP_EV_WRONG_PEER_CERTIFICATE - accepted.");
            *ok = 1; break;
        }
        case SMTP_EV_NO_CLIENT_CERTIFICATE: {
            ok = va_arg(alist, int*); 
            puts("SMTP_EV_NO_CLIENT_CERTIFICATE - accepted.");
            *ok = 1; break;
        }
        default:
            printf("Got event: %d - ignored.\n", event_no);
    }
    va_end(alist);
}

void init()
{
    session = NULL;
    authctx = NULL;
    message = NULL;
}

void dealloc()
{
    smtp_destroy_session(session);
    auth_destroy_context(authctx);
}

void print_status()
{
    smtp_status_t const* status = smtp_message_transfer_status(message);
    printf ("%d %s", status->code,
            (status->text != NULL) ? status->text : "\n");
    smtp_enumerate_recipients (message, print_recipient_status, NULL);
}

void alloc()
{
    if (session)
        smtp_destroy_session(session);
    
    // create.
    session = smtp_create_session();    
    message = smtp_add_message(session);
    
    // set server.
    smtp_set_server(session, d_owner->server.c_str());
    
    // set auth.
    if (authctx)
        auth_destroy_context(authctx);
    authctx = auth_create_context();
    
    // set auth.
    auth_set_mechanism_flags (authctx, AUTH_PLUGIN_PLAIN, 0);
    auth_set_interact_cb (authctx, authinteract, d_owner);
    
    // set passwd.
    smtp_starttls_set_password_cb(tlsinteract, d_owner);
    smtp_set_eventcb(session, event_cb, d_owner);
    
    smtp_auth_set_context(session, authctx);
    
    smtp_set_messagecb(message, readlinefp_cb, d_owner);
}

smtp_session_t session;
smtp_message_t message;
auth_context_t authctx;

NNTDECL_PRIVATE_END_CXX

SmtpClient::SmtpClient()
{
    NNTDECL_PRIVATE_CONSTRUCT(SmtpClient);
}

SmtpClient::~SmtpClient()
{
    NNTDECL_PRIVATE_DESTROY();
}

core::data SmtpClient::get_user() const
{
    return core::type_cast<core::data>(user);
}

core::data SmtpClient::get_password() const
{
    return core::type_cast<core::data>(password);
}

bool SmtpClient::post()
{
    d_ptr->alloc();      
    
    smtp_set_header(d_ptr->message, "To", NULL, content.to.c_str());
    if (content.cc.empty() == false)
        smtp_set_header(d_ptr->message, "Cc", NULL, content.cc.c_str());
    if (content.bcc.empty() == false)
        smtp_set_header(d_ptr->message, "Bcc", NULL, content.bcc.c_str());

    smtp_set_reverse_path(d_ptr->message, content.from.c_str());
    
    smtp_set_header(d_ptr->message, "Subject", NULL, content.header.c_str());
    smtp_set_header_option(d_ptr->message, "Subject", Hdr_OVERRIDE, 1);
    
    if (!smtp_start_session(d_ptr->session))
    {
        trace_msg("failed to start smtp session.");
        
# ifdef NNT_DEBUG
        char buf[128];
        
        fprintf (stderr, "SMTP server problem: %s\n",
                 smtp_strerror (smtp_errno (), buf, sizeof buf)); 
# endif
        return false;
    }
    
    d_ptr->print_status();
    
    return true;
}

NNT_END_NS
NNT_END_CXX