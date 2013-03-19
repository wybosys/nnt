package wsi.test

import wsi.core.Object

object Core extends Test {

    def run() :Unit = {        
        var obj = new Object()
        obj.store_push("A", "First")
        assert("First" == obj.store_find("A"))     
        message(obj.store_pop("A"))
        
        // test signal slot.
        object slot extends Object {
            def act_test() = {
                trace("ACT TEST")
            }
        }
        obj.register_signal("TEST")
        obj.connect("TEST", slot.method("act_test"), slot)
        obj.emit("TEST")
    }
    
}