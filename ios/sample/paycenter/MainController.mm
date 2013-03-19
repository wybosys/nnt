
# include "Foundation+NNT.h"
# include "MainController.h"
# include "PayCenter.h"
# include "UnipayApi.h"
# include "MainModel.h"
# include "PayUtils.h"

NNTAPP_BEGIN

MainView::MainView()
{
    alipay.set_text(@"ALIPAY");
    bypay.set_text(@"UNIPAY-BYPAY");
    
    add_sub(alipay);
    add_sub(bypay);
}

void MainView::layout_subviews()
{
    layout::vbox lyt(bounds(), 5);
    layout::linear lnr(lyt);
    lnr << (flex)1 << (pixel)50 << (pixel)50 << (flex)1;
    
    lyt << lnr;
    
    alipay.set_frame(lyt << lnr);
    bypay.set_frame(lyt << lnr);
}

MainController::MainController()
{
    
}

void MainController::view_loaded()
{
    view().alipay.connect(kSignalButtonClicked, _action(_class::act_alipay), this);
    view().bypay.connect(kSignalButtonClicked, _action(_class::act_bypay), this);
}

void MainController::act_alipay()
{
    pay::Center pay;

    ns::MutableDictionary dict;
    dict[@"partner"] = @"2088102000947391";
    dict[@"seller"] = @"2088102000947391";
    dict[@"amount"] = number(0.01f);
    dict[@"callback_url"] = @"wsi://paycenter.sample.wsi";

    dict[@"private_key"] = @"MIICdwIBADANBgkqhkiG9w0BAQEFAASCAmEwggJdAgEAAoGBALaeckPlqpa5FWi1yxVAT3t1ezzojnCqzHQ5xI0r2XW7mr7YeXl+RVuVB8zxFboHrpdnlZp3sanS1Jj2xohlvGOMWHaZs3Ye3KVr+gaMm/A8qUv2B0euzd8U1AvZLMOFfBC17uXw9/x8gHLCRn5ud9tkgLIbRuolAAjMllCh7p/hAgMBAAECgYAPt0MOJM2xeuwkvsBja81rSoj4jOr1Nz2xIuePXp6wSxzeH7MUiZFeeEzbjkPYZqDX1spBKNvZSZOSNmqPgnHb2aT3A1HIeJzwuct03Uby83tZV+Zi2b+Pdv0kB1JPNrU8A2DfgbNBm1+iy3nabO2X9/GyochjszgC/uYSDnVuIQJBAPyzvQkna5OIeGX7Q4nGrn6sgoaD6UUWIknhbQN8qN+tt8T2xlenJYrH56T9WKLfOGu8EJFfupLWknFemL+zYq8CQQC5AJCE5BuAjXz3pMTLGj1GPB0rQj7QvAo0Cyz5tlf4CFK9jCVKwZ65BITM0zqMaZJhRWwAgaBWcRQABqdWdApvAkEAtZeX9VcNmDROiMJ58y0CQedH2NA8NjhEpaDHzOStGifk0jafq2ditAsZbFfedRRBoDHCGiWXlmN5UtyumbuX4wJACyftjxXyUp41mvlkpJrAdyvI1oL4Jr4wH1NNMwG77EkUNDnvRcLHP4D2QSO7tBvpp9P330/xy0SmYBoGnUACIQJBAIVqqXilDKr/R7ZxXHG4l4OG1yPdmqaQl+6amncEZAKdBnCBGX8mplda5BbpWN5p8YAmaHDBSleHvmUktG1LPcs=";
    dict[@"public_key"] = @"MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCFap2x07lpVflque96tyWzacJiMpaUYalTEexcYEGJFinho8xkh9YsiAbL333MAHB0sfVh70WFhlUrLAKLyZ8EXJVjvOjVdDuMsAMTTcuSI+441EzCzu0YkJSZI9Zsmam1GXAeEWWCEZFHNQBZVa1Qb9jiv0aJO+vuK3Xk4JVllQIDAQAB";

    pay.send(@"alipay", dict);
}

void MainController::act_bypay()
{
    instance_ref<ByPayModel> mdl;
    mdl->oid = pay::utils::orderid();
    mdl->time = tostr(pay::utils::ordertime());
    mdl->timeout = tostr(pay::utils::ordertime() + 200);
    mdl->amt = @"10.1";
    mdl->desc = @"TEST";
    mdl->backendurl = @"www.google.com";
    context::Serv().retrieve_async(mdl, _mdlaction(_class::mdl_bypay), this);
}

void MainController::mdl_bypay(AnyObject& any)
{
    pay::ByPay pay;
    pay.connect(kSignalPayFailed, _action(_class::cb_bypay_failed), this);
    pay.connect(kSignalPaySuccess, _action(_class::cb_bypay_suc), this);
    
    ByPayModel* mdl = any;
    pay.result() = ns::Data(mdl->result);
    pay.send(ns::Dictionary());
}

void MainController::cb_bypay_failed()
{
    core::Confirm::info(@"ByPay Failed.");
}

void MainController::cb_bypay_suc()
{
    core::Confirm::info(@"ByPay Success.");
}

NNTAPP_END
