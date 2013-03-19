
import account

NULL = 0x0
READ = 0x1
WRITE = 0x2
READWRITE = READ | WRITE

class Right:
    
    uid = account.UID_ANONY
    gid = account.GID_ANONY
    flag = 0x030303
    
    def user(self):
        return (self.flag & 0xff0000) >> 16
    
    def set_user(self, r):
        self.flag = (self.flag & 0x00ffff) | ((r & 0xff) << 16)
    
    def group(self):
        return (self.flag & 0xff00) >> 8
    
    def set_group(self, r):
        self.flag = (self.flag & 0xff00ff) | ((r & 0xff) << 8)
    
    def other(self):
        return self.flag & 0xff
    
    def set_other(self, r):
        self.flag = (self.flag & 0xffff00) | (r & 0xff)
        
    def is_read(self, v):
        return v & READ == READ
    
    def is_write(self, v):
        return v & WRITE == WRITE
    
    def is_execute(self, v):
        return v != NULL
    
    def discard_other(self):
        self.set_other(NULL)
        
    def discard_group(self):
        self.set_group(NULL)
        
    def discard_user(self):
        self.set_user(NULL)
    
    def check(self, r):
        if self.uid == r.uid:
            return self.user() & r.user() != 0
        if self.gid == r.gid:
            return self.group() & r.group() != 0
        return self.other() & r.other() != 0
            
