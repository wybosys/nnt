package wsi.cross

trait IRpc extends wsi.core.Object {
       
    //! comm with server.
    def call(model:wsi.model.Model, url:java.net.URL) :Any
    
}

abstract class Rpc extends IRpc {    
    
    object signals {
        val kSignalRpcBegin = "::wsi::cross::rpc::begin"
        val kSignalRpcEnd = "::wsi::cross::rpc::end"
    }
    import signals._
    
    this.register_signal(kSignalRpcBegin)
    this.register_signal(kSignalRpcEnd)
    
    //! begin call
    def begin_call() = {
        this.emit(kSignalRpcBegin)
    }
    
    //! end call
    def end_call() = {
        this.emit(kSignalRpcEnd)
    }
    
}