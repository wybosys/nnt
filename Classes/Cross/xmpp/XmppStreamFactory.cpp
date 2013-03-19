
# include "Core.h"
# include "XmppStreamFactory.h"

# include "./core/XmppFeatures.h"
# include "./core/XmppStream.h"

NNT_BEGIN_CXX
NNT_BEGIN_NS(xmpp)

StreamFactory::StreamFactory()
{
    register_object(cor::Features::FacObj);
    register_object(cor::Stream::FacObj);
}

StreamFactory::~StreamFactory()
{
    
}

bool StreamFactory::process(xmlnode_t const* node)
{
    if (node->name.empty() == false)
    {
		if (cor::Stream::couldload(node))
		{
        
			xmlattr_t const* attr = NULL;
        
			if (_client->idr.empty() &&
				(attr = node->attribute("id")))
			{
				_client->idr = attr->value;
			}
        
			if (_client->server.empty() &&
				(attr = node->attribute("from")))
			{
				_client->server = attr->value;
			}

			return super::process(node);
		}
    }

	if (cor::Features::couldload(node))
		return super::_process_self(node);

	return false;
}

NNT_END_NS
NNT_END_CXX