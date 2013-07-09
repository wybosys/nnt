package nnt.core

class Object {
    
    private type store_stack_type = collection.mutable.ArrayBuffer[Any]    
    private type store_type = collection.mutable.HashMap[String, store_stack_type]
    private type attach_stack_type = collection.mutable.ArrayBuffer[AnyRef]
    private type attach_type = collection.mutable.HashMap[String, attach_stack_type]
    private type event_type = nnt.core.Event        

    private var _store: store_type = null
    private var _attach: attach_type = null
    private var _event: event_type = null   
    
    type SEL = java.lang.reflect.Method
    type CLASS = java.lang.Class[_]
    
    def method(sel:String, cls:CLASS*) :SEL = {
        this.getClass().getDeclaredMethod(sel, cls.toList : _*)
    }
    
    def event(): event_type = {
        if (_event == null) {
            _event = new event_type()
        }
        return _event
    }

    def store(): store_type = {
        if (_store == null) {
            _store = new store_type()
        }
        return _store
    }        
    
    def store_push(key:String, obj:Any): Unit = {
        var store = this.store()
        var array: store_stack_type = null
        if (store.get(key).isEmpty) {
            array = new store_stack_type()
            store += (key -> array)            
        }
        array += obj
    }
    
    def store_find(key:String): Any = {
        val stack = this.store()(key)
        if (stack.length == 0) {
            return None
        }        
        return stack(0)
    }
    
    def store_pop(key:String): Any = {
        val stack = this.store()(key)
        if (stack.length == 0) {
            return None
        }
        val ret = stack(0)
        stack.remove(0)
        return ret
    }
    
    def attach(): attach_type = {
        if (_attach == null) {
            _attach = new attach_type()
        }
        return _attach
    }        
    
    def attach_push(key:String, obj:AnyRef): Unit = {
        val attach = this.attach()
        var array: attach_stack_type = null
        if (store.get(key).isEmpty) {
            array = new attach_stack_type()
            attach += (key -> array)            
        }
        array += obj
    }
    
    def attach_find(key:String): AnyRef = {
        val stack = this.attach()(key)
        if (stack.length == 0) {
            return None
        }        
        return stack(0)
    }
    
    def attach_pop(key:String): AnyRef = {
        val stack = this.attach()(key)
        if (stack.length == 0) {
            return None
        }
        val ret = stack(0)
        stack.remove(0)
        return ret
    }
    
    // signals & slots.
    import Event._           
    def register_signal(sig:signal_t) :slots_t = this.event().register_signal(sig)   
    def emit(sig:signal_t) = this.event().emit(sig)
    def connect(sig:signal_t, sel:method_t, hdl:nnt.core.Object) :slot_t = this.event().connect(sig, sel, hdl)
    
    // traces.
    def trace[T](obj:T) = nnt.NNT.trace(obj)
    
}