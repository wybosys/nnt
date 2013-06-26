
# include <Foundation+NNT.h>
# include "Model.h"

NETOBJ_BEGIN

class Task
: public cocos2d::CCObject
{
public:
        
    void wait()
    {
        pthread_join(hdl_thd, NULL);
    }
    
    //! start.
    bool start()
    {
        this->retain();
        
        int ret = pthread_create(&hdl_thd, NULL, wrapper_thd, this);
        return ret == 0;
    }
        
public:
    
    virtual int main()
    {
        return 0;
    }
    
protected:
    
    Task()
    {
        hdl_thd = 0;
        stop = false;
    }
    
    virtual ~Task()
    {
        stop = true;
        wait();
    }
    
    friend void* wrapper_thd(void*);
    static void* wrapper_thd(void* data)
    {
        Task* d_owner = (Task*)data;
        
        while (!d_owner->stop)
        {
            d_owner->main();
        }
        
        d_owner->release();
        
        pthread_exit(0);
        
        return NULL;
    }
    
    bool stop;
    
private:
    
    pthread_t hdl_thd;
    
};

class TaskItem
: public cocos2d::CCObject
{
public:
    
    TaskItem(NetObj* m, Model::cli_type* c, Model::respn_type* r)
    {
        model = m;
        m->retain();
        
        cli = c;
        c->retain();
        
        respn = r;
        r->retain();
    }
    
    TaskItem(TaskItem const& r)
    {
        model = r.model;
        model->retain();
        
        cli = r.cli;
        cli->retain();
        
        respn = r.respn;
        respn->retain();
    }
    
    ~TaskItem()
    {
        model->release();
        cli->release();
        respn->release();
    }
    
    NetObj* model;
    Model::cli_type* cli;
    Model::respn_type* respn;
    
};

# define DELEGATE_CALL(func) if (m->delegate) m->delegate->func;

class ModelCallbackTask
: public Task
{
public:
    
    ModelCallbackTask(TaskItem* i)
    {
        item = i;
        item->retain();
    }
    
    ~ModelCallbackTask()
    {
        item->release();
    }
    
    virtual int main()
    {
        work();
        
        stop = true;
        return 0;
    }
    
    void work()
    {
        NetObj* m = item->model;
        int code = item->respn->getResponseCode();
        
        if (code != 200)
        {
            DELEGATE_CALL(onFailResponsed(m));
            DELEGATE_CALL(onFailed(m));
            m->release();
            return;
        }
        
        vector<char> const& buf = *item->respn->getResponseData();
        json_tokener* tok = json_tokener_new();
        json_object* jobj = json_tokener_parse_ex(tok, &buf[0], buf.size());
        bool ret = tok->err == json_tokener_success;
        json_tokener_free(tok);
        if (!ret)
        {
            DELEGATE_CALL(onFailParsed(m));
            DELEGATE_CALL(onFailed(m));
            m->release();
            return;
        }
        
        // load default.
        json_object* ncode = json_object_object_get(jobj, "code");
        json_object* nmsg = json_object_object_get(jobj, "message");
        json_object* ndata = json_object_object_get(jobj, "data");
        if (!ncode || !nmsg || !ndata)
        {
            DELEGATE_CALL(onFailParsed(m));
            DELEGATE_CALL(onFailed(m));
            json_object_put(jobj);
            m->release();
            return;
        }
        
        m->code = json_object_get_int(ncode);
        m->message = json_object_get_string(nmsg);
        
        if (m->code != 0)
        {
            DELEGATE_CALL(onFailCalled(m, m->message.c_str()));
            DELEGATE_CALL(onFailed(m));
            json_object_put(jobj);
            m->release();
            return;
        }
        
        // from json to api.
        m->parse(ndata);
        
        // suc.
        DELEGATE_CALL(onSuccess(m));
        
        json_object_put(jobj);
        
        // retain in callApi.
        m->release();
    }
    
    TaskItem* item;
    
};

class ModelTask
: public Task
{
public:
    
    ModelTask()
    {
        queue = new cocos2d::CCArray;
        pthread_cond_init(&sleepcond_queue, NULL);
        pthread_mutex_init(&sleepcondmtx_queue, NULL);
        pthread_mutex_init(&mtx_queue, NULL);
    }
    
    ~ModelTask()
    {
        stop = true;
        pthread_cond_signal(&sleepcond_queue);
        pthread_cond_destroy(&sleepcond_queue);
        pthread_mutex_destroy(&sleepcondmtx_queue);
        pthread_mutex_destroy(&mtx_queue);
        queue->release();
    }
    
    void add(TaskItem* item)
    {
        pthread_mutex_lock(&mtx_queue);
        queue->addObject(item);
        pthread_mutex_unlock(&mtx_queue);
        
        pthread_cond_signal(&sleepcond_queue);
    }
    
    virtual int main()
    {
        while (!stop)
        {
            TaskItem* item = NULL;
            
            pthread_mutex_lock(&mtx_queue);
            if (queue->count() != 0)
            {
                item = dynamic_cast<TaskItem*>(queue->objectAtIndex(0));
                item->retain();
                queue->removeObjectAtIndex(0);
            }
            pthread_mutex_unlock(&mtx_queue);
            
            if (item == NULL)
            {
                pthread_cond_wait(&sleepcond_queue, &sleepcondmtx_queue);
                continue;
            }
            
            ModelCallbackTask* cbt = new ModelCallbackTask(item);
            cbt->start();
            cbt->release();
            
            item->release();
        }
        
        return 0;
    }
    
protected:
    
    cocos2d::CCArray* queue;
    pthread_cond_t sleepcond_queue;
    pthread_mutex_t sleepcondmtx_queue, mtx_queue;
    
};

Model::Model()
{
    task = new ModelTask;
    task->start();
}

Model::~Model()
{
    delete task;
}

void Model::cbHttpResponse(cli_type* cli, respn_type* respn)
{
    NetObj* m = (NetObj*)respn->getHttpRequest()->getUserData();
    TaskItem* item = new TaskItem(m, cli, respn);
    task->add(item);
    item->release();
}

void Model::callApi(NetObj* obj)
{
    NetObj::req_type* req = new NetObj::req_type;
    req->setRequestType(NetObj::req_type::kHttpPost);
    req->setUrl(obj->getFullUrl().c_str());
    req->setResponseCallback(this, httpresponse_selector(Model::cbHttpResponse));
    obj->retain();
    req->setUserData(obj);
    obj->initRequest(*req);
    cli_type::getInstance()->send(req);
    req->release();
}

NETOBJ_END
