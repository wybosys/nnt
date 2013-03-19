
UID_USER = 1000
GID_USER = 1000

UID_ROOT = 0
GID_WHEEL = 0

UID_ANONY = 1
GID_ANONY = 1

UID_SAMPLE = 2
GID_SAMPLE = 2

UID_TOOLKIT = 3
GID_TOOLKIT = 3

UID_AUTO = -1
GID_AUTO = -1

class User:
    
    name = ''
    fullname = ''
    uid = UID_ANONY
    gid = GID_ANONY
    prefix = ''
    
    def Root():
        ret = User()
        ret.name = ret.fullname = 'root'        
        ret.uid = UID_ROOT
        ret.gid = GID_WHEEL
        return ret

class Group:
    
    name = ''
    fullname = ''
    gid = GID_ANONY
    prefix = ''
    
    def Wheel():
        ret = Group()
        ret.name = ret.fullname = 'wheel'
        ret.gid = GID_WHEEL
        return ret
    