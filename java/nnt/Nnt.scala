package nnt

import nnt.core.Object

object NNT {
    
    def trace[T](obj:T) :Unit = {
        if (nnt.Compile.Release) return
        println(obj)
    }
	
}