
import curses
import traceback
import core

global window

class App(core.Object):

    def init(self):
        global window
        window = curses.initscr()
        curses.start_color()
        curses.cbreak()
        window.keypad(True)
        curses.noecho()

    def fin(self):
        global window
        curses.nocbreak()
        window.keypad(False)
        curses.echo()
        curses.endwin()
        window = None
    
    def load(self):
        pass

    def execute(self):
        self.init()
        try:
            self.load()
            self.fin()
        except:
            self.fin()
            print(traceback.print_exc())
        pass

    @staticmethod
    def Window():
        global window
        return window

def trace_msg(msg):
    if (nnt.Core.Config.DEBUG):
        print(msg)
