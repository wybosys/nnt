
import curses
import curses.panel
import core, math

class Dialog:

    def __init__(self, size = None, parent = None):
        if (parent == None):
            f_new = core.cli.App.Window().subwin
        else:
            f_new = parent.derwin
        if (size == None):
            self.window = f_new(0, 0)
        else:
            self.window = f_new(size.height, size.width, 0, 0)
        self.panel = curses.panel.new_panel(self.window)
        self.panel.hide()
        curses.panel.update_panels()

    def execute(self):
        pass

    def close(self):
        pass

    def bounds(self):
        pass
