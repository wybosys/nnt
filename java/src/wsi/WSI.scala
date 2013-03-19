package wsi

import wsi.core.Object

object WSI {
    
    def trace[T](obj:T) :Unit = {
        if (wsi.Compile.Release) return
        println(obj)
    }
	
}