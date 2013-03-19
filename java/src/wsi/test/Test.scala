package wsi.test

trait ITest extends wsi.core.Object {

    def run() :Unit
    
}

abstract class Test extends ITest {
    
    def assert(pass: Boolean) :Unit = {
        if (false == pass) {
            throw new RuntimeException("assert")
        }
    }
    
    def message(msg: Any) :Unit = println(msg.toString())
    
}