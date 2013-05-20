
class Point:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

ZeroPoint = Point()

class Size:
    def __init__(self, width = 0, height = 0):
        self.width = width
        self.height = height

ZeroSize = Size()

class Rect:
    def __init__(self, origin = Point(), size = Size()):
        self.origin = origin
        self.size = size

ZeroRect = Rect()
