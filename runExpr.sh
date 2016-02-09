#!/bin/bash

make main

echo start_Run_Expr_Script


	function=1
#	fileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/soc-pokec-relationships.txt'
#	fileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/DBLP/graph_dblp.txt'
	fileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/roadNet-PA.txt'
	sFileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/super-roadNet-PA.txt'
	vSynopsisFileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vSynopsis-roadNet-PA.txt'
	eSynopsisFileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/eSynopsis-roadNet-PA.txt'
	vToSNMapFileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vTOSNMap-roadNet-PA.txt'

#	attrFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/'
#	hashFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/'
#	attrFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/DBLP/'
#	hashFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/DBLP/'
	attrFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/'
	hashFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/'


	numEAttr=5
	numVAttr=5
	maxDomainSize=20
	vRowSize=24
	eRowSize=24
	numQuery=100
	useConstraint=1
	numSuperNode=1000
	synopsisSize=30
	

	#generate Attribute
#	./main 1 $fileName $attrFolderName $numVAttr $numEAttr $maxDomainSize $vRowSize $eRowSize
#run 1 /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/roadNet-PA.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ 10 10 20 38 38

	#generate hash value
#	./main 3 $fileName $attrFolderName $hashFolderName

	#construct super graph and synopsis
#	./main 4 $fileName $attrFolderName $numVAttr $numEAttr $numSuperNode $synopsisSize $vRowSize $sFileName $vSynopsisFileName $eSynopsisFileName $vToSNMapFileName

	#query algorithm
	./main 5 $fileName $attrFolderName $hashFolderName $numEAttr $numVAttr $vRowSize $eRowSize $numQuery $useConstraint $numSuperNode $synopsisSize $sFileName $vSynopsisFileName $eSynopsisFileName $vToSNMapFileName
#	valgrind ./main 5 $fileName $attrFolderName $hashFolderName $numEAttr $numVAttr $vRowSize $eRowSize $numQuery $useConstraint $numSuperNode $synopsisSize $sFileName $vSynopsisFileName $eSynopsisFileName $vToSNMapFileName
#run 5 /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/roadNet-PA.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ 5 5 24 24 500 1 1000 30 /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/super-roadNet-PA.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vSynopsis-roadNet-PA.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/eSynopsis-roadNet-PA.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vTOSNMap-roadNet-PA.txt





#0x7fff5f3fff50
#	COUNT=10000
#	while [ $COUNT -le 100000 ]; do
#	FN=$COUNT'_quick_server_test_with_pruning'
#	./qmain -query_data $QUERY_DATA -show_comment $SC -alg $alg -r $COUNT -testing $testing -client_update $CLIENT_UPDATE > $FN
#	echo $COUNT
#	let COUNT=COUNT+10000
#	done

#./main 1 /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/soc-pokec-relationships.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/ 5 3 50 10

