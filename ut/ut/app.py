
import nnt
from homedlg import *

class App(nnt.core.cli.App):

    def load(self):
        self.home = HomeDialog()
        self.home.execute()

