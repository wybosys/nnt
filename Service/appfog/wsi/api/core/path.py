
import imp

WSI = imp.find_module('wsi')[1]
API = imp.find_module('api', [WSI])[1]

