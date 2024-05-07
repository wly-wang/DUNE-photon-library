MERGE_LIST=""

for INDEX in 0 1 2 3 4 5 6 7 8 9
do
  MERGE_LIST="${MERGE_LIST} merge${INDEX}.root"
  hadd merge${INDEX}.root ../generate/process${INDEX}*/process*.root
done

hadd mergeAll.root $MERGE_LIST
