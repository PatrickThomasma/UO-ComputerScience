from sdk_config import CHOICES, UNKNOWN, ROOT
from sdk_config import NROWS, NCOLS
import logging
logging.basicConfig()
log = logging.getLogger(__name__)
log.setLevel(logging.INFO)
import enum
from typing import Sequence, List, Set

# --------------------------------
#  The events for MVC
# --------------------------------

class Event(object):
 """Abstract base class of all events, both for MVC
 and for other purposes.
 """
 pass
# ---------------
# Listeners (base class)
# ---------------

class Listener(object):
 """Abstract base class for listeners.
 Subclass this to make the notification do
 something useful.
 """

 def __init__(self):
     """Default constructor for simple listeners without state"""
     pass

 def notify(self, event: Event):
     """The 'notify' method of the base class must be
     overridden in concrete classes.
     """
     raise NotImplementedError("You must override Listener.notify")
# --------------------------------------
# Events and listeners for Tile objects
# --------------------------------------

class EventKind(enum.Enum):
 TileChanged = 1
 TileGuessed = 2

class TileEvent(Event):
 """Abstract base class for things that happen
 to tiles. We always indicate the tile.  Concrete
 subclasses indicate the nature of the event.
 """

 def __init__(self, tile: 'Tile', kind: EventKind):
     self.tile = tile
     self.kind = kind
     # Note 'Tile' type is a forward reference;
     # Tile class is defined below

 def __str__(self):
     """Printed representation includes name of concrete subclass"""
     return f"{repr(self.tile)}"

class TileListener(Listener):
 def notify(self, event: TileEvent):
     raise NotImplementedError(
         "TileListener subclass needs to override notify(TileEvent)")

class Listenable:
 """Objects to which listeners (like a view component) can be attached"""

 def __init__(self):
     self.listeners = [ ]

 def add_listener(self, listener: Listener):
     self.listeners.append(listener)

 def notify_all(self, event: Event):
     for listener in self.listeners:
         listener.notify(event)

# ----------------------------------------------
#      Tile class
# ----------------------------------------------

class Tile(Listenable):
 """One tile on the Sudoku grid.
 Public attributes (read-only): value, which will be either
 UNKNOWN or an element of CHOICES; candidates, which will
 be a set drawn from CHOICES.  If value is an element of
 CHOICES,then candidates will be the singleton containing
 value.  If candidates is empty, then no tile value can
 be consistent with other tile values in the grid.
 value is a public read-only attribute; change it
 only through the access method set_value or indirectly
 through method remove_candidates.
 """

 def __init__(self, row: int, col: int, value=UNKNOWN):
     super().__init__()
     assert value == UNKNOWN or value in CHOICES
     self.row = row
     self.col = col
     self.set_value(value)
 def __str__(self):
     return self.value

 def set_value(self, value: str):
     if value in CHOICES:
         self.value = value
         self.candidates = {value}
     else:
         self.value = UNKNOWN
         self.candidates = set(CHOICES)
     self.notify_all(TileEvent(self, EventKind.TileChanged))

 def __repr__(self):

     return f"Tile({self.row}, {self.col}, '{self.value}')"

 def could_be(self, value: str) -> bool:
     """True iff value is a candidate value for this tile"""
     return value in self.candidates

 def remove_candidates(self, used_values: Set[str]):
     """The used values cannot be a value of this unknown tile.
     We remove those possibilities from the list of candidates.
     If there is exactly one candidate left, we set the
     value of the tile.
     Returns:  True means we eliminated at least one candidate,
     False means nothing changed (none of the 'used_values' was
     in our candidates set).
     """
     new_candidates = self.candidates.difference(used_values)
     if new_candidates == self.candidates:
         # Didn't remove any candidates
         return False
     self.candidates = new_candidates
     if len(self.candidates) == 1:
         self.set_value(new_candidates.pop())
     self.notify_all(TileEvent(self, EventKind.TileChanged))
     return True
# ------------------------------
#  Board class
# ------------------------------

class Board(object):
  """A board has a matrix of tiles"""

  def __init__(self):
      """The empty board"""
      # Row/Column structure: Each row contains columns
      self.tiles: List[List[Tile]] = [ ]
      self.groups: List[List[Tile]] = [ ]
      for row in range(NROWS):
          cols = [ ]
          for col in range(NCOLS):
              cols.append(Tile(row, col))
          self.tiles.append(cols)
      for row in self.tiles:
          self.groups.append(row)
      for col in range(NCOLS):
          bool = []
          for row in range(NROWS):
               bool.append(self.tiles[row][col])
          self.groups.append(bool)


      for block_row in range(ROOT):
          for block_col in range(ROOT):
              group = []
              for row in range(ROOT):
                  for col in range(ROOT):
                      row_addr = (ROOT * block_row) + row
                      col_addr = (ROOT * block_col) + col
                      group.append(self.tiles[row_addr][col_addr])
              self.groups.append(group)

  def set_tiles(self, tile_values: Sequence[Sequence[str]]):
      """Set the tile values a list of lists or a list of strings"""
      for row_num in range(NROWS):
          for col_num in range(NCOLS):
              tile = self.tiles[row_num][col_num]
              tile.set_value(tile_values[row_num][col_num])

  def __str__(self) -> str:
      """In Sadman Sudoku format"""
      row_syms = []
      for row in self.tiles:
          values = [tile.value for tile in row]
          row_syms.append("".join(values))
      return "\n".join(row_syms)

  def solve(self):
      progress = True
      while progress:
          progress = self.naked_single()
      return

  def is_consistent(self) -> bool:
      for group in self.groups:
          used_symbols = set()

          for tile in group:
              if tile.value != '.':
                   if tile.value in used_symbols:
                       return False
                       used_symbols.add(tile.value)
                   else:
                       used_symbols.add(tile.value)
      return True

  def naked_single(self) -> bool:
       """Eliminate candidates and check for sole remaining possibilities.
       Return value True means we crossed off at least one candidate.
       Return value False means we made no progress.
       """
       check = False
       for group in self.groups:
           s = set()

           for i in range (len(group)):
               s.add(group[i].value)
           for j in range(len(group)):
               if Tile.remove_candidates(group[j], s):
                   check = True
       return check

  def hidden_single(self) -> bool:
      """Return True if it makes progress (which will only be if it manages to place a value in a tile)
       and False otherwise."""
      check = False
      for group in self.groups:
          leftovers = set(CHOICES)
          for tile in group:
              if tile.value in leftovers:
                  leftovers.remove(tile.value)
          for tile in leftovers:
              counter = 0
              for tiles in group:
                  if tiles.could_be(tile):
                      counter += 1
                      can_track = tiles
              if counter == 1:
                  can_track.set_value(tile)
                  check = True
      return check

  def solve(self):
      """Repeat solution tactics until we
      don't make any progress, whether or not
      the board is solved.
      """
      progress = True
      while progress:
          progress = self.naked_single()
          self.hidden_single()
      return