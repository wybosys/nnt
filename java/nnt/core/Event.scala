package nnt.core

object Event {
    
	type signal_t = String
	type slot_t = Slot
	type slots_t = collection.mutable.ArrayBuffer[slot_t]
	type signals_t = collection.mutable.HashMap[signal_t, slots_t]
	type method_t = java.lang.reflect.Method
	
}

class Slot {        
    
    import Event._
    
    //! sender.
    var sender:nnt.core.Object = null
    
    //! handler.
    var handler:nnt.core.Object = null
    
    //! result.
    var result:Any = null
    
    //! shot count, -1 is not count, 0 is end. default is -1.
    var shotcount = -1
    
    //! the slot's signal when emit.
    var signal:signal_t = null
    
    //! drop the event, default is NO.
    var veto = false
    
    //! redirect signal.
    var redirect:signal_t = null    
    
    //! method
    var sel:method_t = null
}

class Event {
    
	import Event._
	
	private val _signals = new signals_t()
	
	//! register signal.
	def register_signal(sig:signal_t) :slots_t = {	   
		if (false == _signals.contains(sig)) {
		    var ret = new slots_t()
		    _signals(sig) = ret
		    return ret
		}		
		return _signals(sig)
	}
	
	//! emit.
	def emit(sig:signal_t) :Unit = {
	    val slots = _signals(sig)
	    slots.foreach((each:slot_t) => {
	        if (each.sel != null)
	        	each.sel.invoke(each.handler)
	        else if (each.redirect != null)
	            each.handler.emit(each.redirect)
	    })
	}
	
	//! connect.
	def connect(sig:signal_t, sel:method_t, hdl:nnt.core.Object) :slot_t = {
		val slot = new slot_t()
		slot.handler = hdl
		slot.sel = sel
		val slots = _signals(sig)
		slots.append(slot)
		return slot
	}
	
}