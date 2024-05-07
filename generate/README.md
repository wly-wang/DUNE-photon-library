This will take about 70 hours with 30 processes - best to leave it over a weekend. It's just lazy multiprocessing on a single compute server to avoid dealing with the grid.

Each process will generate 500000 photons for each voxel in a range, loaded from the list of relevant voxels created in the configuration step.

Voxel ranges are of varying length, so a round-robin process scheduler is used. A maximum range of 500 voxels for a single process is applied.

Simply execute python multiprocess.py, and go make a very large number of cups of tea.
