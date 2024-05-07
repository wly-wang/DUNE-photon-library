lar -c build_optical_library_dunevd_argon.fcl -n 1 | tee log

grep "Automatic voxelisation x-dimension" -A 3 log
grep "Automatic voxelisation y-dimension" -A 3 log
grep "Automatic voxelisation z-dimension" -A 3 log
