package wsi.model

import wsi.parser

trait IModel extends wsi.core.Object {

  def is_valid(result: => Any): Boolean
  def process(result: => Any): Boolean
  
}

class Model extends IModel {

    object CACHETIME {
        val CACHETIME_1MIN = 60
        val CACHETIME_15MIN = 900
        val CACHETIME_30MIN = 1800
        val CACHETIME_1HOUR = 3600
        val CACHETIME_3HOUR = 10800
        val CACHETIME_6HOUR = 21600
        val CACHETIME_12HOUR = 43200
        val CACHETIME_1DAY = 86400
        val CACHETIME_3DAY = 259200
        val CACHETIME_1WEEK = 604800
        val CACHETIME_2WEEK = 1209600
        val CACHETIME_1MON = 2592000
        val CACHETIME_1YEAR = 946080000
    }
    import CACHETIME._

    //! url for fetch data.
    var url: String = ""

    //! service name.
    var service: String = ""

    //! method
    var method: String = ""

    //! store the params.
    var params: Array[Any] = Array[Any]()

    //! object parser.
    var objparser: parser.IObjParser = null

    //! cache overdate time. 0 indicate not-overdate forever.	
    var cacheTime: Integer = 0

    //! if force update the cache item, set cacheTime to YES, will ignore cache and set the data back to cache. default is NO. will find object in default cache first.
    var cacheUpdate: Boolean = false

    //! verbose fatal, default is NO.
    var verbose: Boolean = false

    //! verbose waiting. default is NO.
    var verboseWait: Boolean = false

    //! verbose success. default is NO.
    var verboseSuc: Boolean = false

    //! memory usage. it may be used for present memory of object in model. so use it carefully.
    var memoryUsage: Integer = 0

    //! class for rpc.
    var classRpc: CLASS = null

    // empty impl.
    def is_valid(result: => Any): Boolean = true
    def process(result: => Any): Boolean = true
    
    //! get params.
    private val _params = collection.mutable.ArrayBuffer[Any]()
    private val _extend_datas = collection.mutable.ArrayBuffer[Any]()
    
    def get_params(): collection.mutable.ArrayBuffer[Any] = this._params
    def get_params_deep(): collection.mutable.ArrayBuffer[Any] = this._params
    def dup_params(): collection.mutable.ArrayBuffer[Any] = this._params.clone()
    def get_extend_datas(): collection.mutable.ArrayBuffer[Any] = this._extend_datas
    def get_extend_datas_deep(): collection.mutable.ArrayBuffer[Any] = this._extend_datas
    def dup_extend_datas(): collection.mutable.ArrayBuffer[Any] = this._extend_datas.clone()
    
    //! get url
    def get_url(): java.net.URL = new java.net.URL(this.url)
    
    //! collect all params.
    def collect(): collection.immutable.List[Any] = collection.immutable.List[Any](this.url, this.method, this.params)

    //! verbose.
    def active_verbose() = null
    def begin_waiting() = null
    def end_waiting() = null

}

object Model {
    
    def active_verbose(mdl:Model) = if (mdl.verbose) mdl.active_verbose()
    def active_verbose_success(mdl:Model) = if (mdl.verboseSuc) mdl.active_verbose()
    def begin_waiting(mdl:Model) = if (mdl.verboseWait) mdl.begin_waiting()
    def end_waiting(mdl:Model) = if (mdl.verboseWait) mdl.end_waiting()
    
}