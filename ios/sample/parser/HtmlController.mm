
# include "Foundation+NNT.h"
# include "HtmlController.h"
# include "HtmlParser.h"

NNTAPP_BEGIN

HtmlView::HtmlView()
{
    text.set_background(ui::Color::White());
    text.set_editable(false);
    texted.set_background(ui::Color::White());
    texted.set_editable(false);
    
    add_sub(text);
    add_sub(texted);
    add_sub(html);
    add_sub(htmled);
}

void HtmlView::layout_subviews()
{
    CGRectLayoutHBox lyt(bounds(), 5);
    CGRectLayoutLinear lnr(lyt);
    lnr << (flex)1 << (flex)1;
    
    CGRectLayoutVBox lyt1(lyt << lnr, 5);
    CGRectLayoutLinear lnr1(lyt1);
    lnr1 << (flex)1 << (flex)1;    
    text.set_frame(lyt1 << lnr1);
    texted.set_frame(lyt1 << lnr1);
    
    CGRectLayoutVBox lyt2(lyt << lnr, 5);
    CGRectLayoutLinear lnr2(lyt2);
    lnr2 << (flex)1 << (flex)1;
    html.set_frame(lyt2 << lnr2);
    htmled.set_frame(lyt2 << lnr2);
}

void HtmlController::view_loaded()
{
    //ns::Data data(ns::URL(@"http://www.baidu.com"));
    ns::Data data(ns::URL::Bundle(@"test.html"));
    
    ns::String str(data, NSGB18030Encoding);
    view().text.set_text(str);
    
    html::Document doc(core::type_cast<core::data>(data));
    core::data rdata;
    doc.save(rdata);
    ns::String str1(data, NSGB18030Encoding);
    view().html.load(str1);
    
    html::Node::query_result result;
    //doc.jquery("li a.cls", result);
    //doc.jquery("#abc", result);
    //doc.jquery("div#abc", result);
    //doc.jquery("li#abc.blue", result);
    //doc.jquery("div#tab div#tab2 ul li", result);
    //doc.jquery("li[style = '#a1:.']", result);
    //doc.jquery("li[style]", result);
    doc.jquery("li.cls-1", result);
    
    if (result.size())
        trace_msg(@"got " + wsi::ns::String(result.size()));
    else
        trace_msg(@"empty .............");
    
    core::data ndata;
    for (uint i = 0; i < result.size(); ++i)
    {
        html::Node* node = (html::Node*)result[i];
        core::data da;
        node->save(da);
        ndata.append(da);
    }
    ns::String stred(core::type_cast<ns::Data>(ndata), NSGB18030Encoding);    
    view().texted.set_text(stred);
    view().htmled.load(stred);
}

NNTAPP_END