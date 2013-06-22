
class Point:

    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def __eq__(self, r):
        if (r == None):
            return self.x == 0 and self.y == 0
        return self.x == r.x and self.y == r.y

ZeroPoint = Point()

class Size:

    def __init__(self, width = 0, height = 0):
        self.width = width
        self.height = height

    def __eq__(self, r):
        if (r == None):
            return self.width == 0 and self.height == 0
        return self.width == r.width and self.height == r.height

ZeroSize = Size()

class Rect:

    def __init__(self, origin = Point(), size = Size()):
        self.origin = origin
        self.size = size

    def __eq__(self, r):
        if (r == None):
            return self.origin == None and self.size == None
        return self.origin == r.origin and self.size == r.size

ZeroRect = Rect()
