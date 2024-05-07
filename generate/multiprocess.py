import os, subprocess, time, datetime

# Voxel ranges are very jagged
# Split the longer ones
MAX_VOXEL_RUN = 500

# Choose number of processes to use
N_PROCESSES = 30

# Set the fcl file name
FCL_FILE = "../configure/build_optical_library_dunevd_argon.fcl"

# Job submission
def startJob( voxelStart, voxelEnd, processCount ):
  totalVoxels = voxelEnd - voxelStart + 1
  print( "\tRunning with " + str( totalVoxels ) + " voxels: " + str( voxelStart ) + " - " + str( voxelEnd ) )

  workingDirectory = os.getcwd()
  processDirectory = os.path.join( workingDirectory, "process"+str( processCount ) )
  os.makedirs( processDirectory )
  os.chdir( processDirectory )

  # Set up the fcl file
  subprocess.run( "cp ../" + FCL_FILE + " .", shell=True )
  subprocess.run( 'echo "physics.producers.generator.FirstVoxel: ' + str( voxelStart ) + '" >> ' + FCL_FILE, shell=True )
  subprocess.run( 'echo "physics.producers.generator.LastVoxel: ' + str( voxelEnd ) + '" >> ' + FCL_FILE, shell=True )
  subprocess.run( 'echo "physics.producers.generator.N: 500000" >> ' + FCL_FILE, shell=True )
  subprocess.run( 'echo "services.TFileService.fileName: \\"process' + str( processCount ) + '_hist.root\\"" >> ' + FCL_FILE, shell=True )

  # Execute the LArSoft command
  command = "lar -n " + str( totalVoxels ) + " -c " + FCL_FILE + " &> log"
  process = subprocess.Popen( command, shell=True )

  os.chdir( workingDirectory )
  return process

# Input the voxel ranges (must be contiguous)
voxelInputFile = open( "../configure/other.voxels", "r" )

allVoxelRuns = []
currentVoxelRun = []
for line in voxelInputFile:

  # Process input
  voxel = int( line.strip() )

  # Fill contiguous ranges
  if not currentVoxelRun: # empty run
    currentVoxelRun.append( voxel )
  elif ( currentVoxelRun[-1] == voxel - 1 ) and ( len( currentVoxelRun ) < MAX_VOXEL_RUN ):
    currentVoxelRun.append( voxel )
  else:
    allVoxelRuns.append( currentVoxelRun )
    currentVoxelRun = [voxel]

# Don't forget the last run
allVoxelRuns.append( currentVoxelRun )

# Since the voxel runs are jagged, use an ad-hoc scheduler
voxelRunIndex = 0
allProcesses = [None] * N_PROCESSES

while voxelRunIndex < len( allVoxelRuns ):

  for processIndex in range( N_PROCESSES ):

    # Simple round-robin scheduler - look for finished processes and start new ones
    process = allProcesses[ processIndex ]
    if process is None or process.poll() is not None:

      voxelRun = allVoxelRuns[ voxelRunIndex ]
      print( "Starting " + str( voxelRunIndex ) + " of " + str( len( allVoxelRuns ) ) + " processes " + datetime.datetime.today().strftime('%Y-%m-%d %H:%M:%S') )
      allProcesses[ processIndex ] = startJob( voxelRun[0], voxelRun[-1], voxelRunIndex )
      voxelRunIndex += 1

      # Total processes not necessarily a multiple of N_PROCESSES
      if voxelRunIndex >= len( allVoxelRuns ):
        break

  time.sleep(5)

# Wait for last processes to terminate
for process in allProcesses:
  if process is not None:
    process.wait()

print( "All processes complete " + datetime.datetime.today().strftime('%Y-%m-%d %H:%M:%S') )
