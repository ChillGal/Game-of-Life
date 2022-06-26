# Game-of-Life
Conway's Game of Life implemented in C.

This was originally a task for a coursework but i have rewritten the code with extra functionality.

# Game rules

- Any live cell with two or three live neighbours survives.
- Any dead cell with three live neighbours becomes a live cell.
- All other live cells die in the next generation. Similarly, all other dead cells stay dead.

# Extra functionality added:
- Saving and loading settings
- Listing current settings
- Full edge wrap-around (this gives illusion of an infinite area for the cells while in a confined space)

# Functionality to add:
- Saving and loading game state
- Setting up an initial environment state
- Clearing the state
- Display generation information in window at same time as grid
- Toggle infinite border