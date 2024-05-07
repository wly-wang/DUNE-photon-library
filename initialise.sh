# Choose dune sw version
# LArSim from LARSOFT_SUITE_v09_90_00 or newer contains the automatic voxelisation from https://github.com/LArSoft/larsim/pull/135
ls /cvmfs/dune.opensciencegrid.org/products/dune/dunesw/
export MY_DUNE_VERSION=v09_90_00

# Env setup
source /cvmfs/dune.opensciencegrid.org/products/dune/setup_dune.sh
setup dunesw ${MY_DUNE_VERSION}d00 -q e20:prof

# Activate build area if there is one
source $PWD/localProducts_larsoft_*/setup

# Build
mrbsetenv
mrb i -j12
mrbslp

