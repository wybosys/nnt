
import curses, curses.textpad, curses.ascii, curses.panel
import traceback

class dialog:

	def init(self):
		self._wnd = curses.initscr()
		curses.start_color()
		curses.cbreak()
		self._wnd.keypad(True)
		curses.noecho()		
		self._wnd.refresh()

	def fin(self):
		curses.nocbreak()
		self._wnd.keypad(False)
		curses.echo()
		curses.endwin()

	def execute(self):
		try:
			self.init()
		except:
			self.fin()
			traceback.print_exc()
			return
		key = self._wnd.getch()
		while(1):
			if (key == ord('q')):
				break
		self.fin()