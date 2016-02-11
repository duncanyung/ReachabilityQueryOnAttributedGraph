#!/bin/bash

make main

echo start_Run_Expr_Script


	function=1
#	fileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/soc-pokec-relationships.txt'
#	fileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/DBLP/graph_dblp.txt'
	fileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/roadNet-PA.txt'
	sFileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/super-roadNet-PA.txt'
	vSynopsisFileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vSynopsis-roadNet-PA.txt'
	eSynopsisFileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/eSynopsis-roadNet-PA.txt'
	vToSNMapFileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vTOSNMap-roadNet-PA.txt'
	queryFileName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/queries-roadNet-PA.txt'

#	attrFolderName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/'
#	hashFolderName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/'
#	attrFolderName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/DBLP/'
#	hashFolderName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/DBLP/'
	attrFolderName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/'
	hashFolderName='/home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/'


	numEAttr=5
	numVAttr=5
	maxDomainSize=20
	vRowSize=24
	eRowSize=24
	numQuery=1000
	useConstraint=1
	numSuperNode=1000
	synopsisSize=30
	

	#generate Attribute
#	./main 1 $fileName $attrFolderName $numVAttr $numEAttr $maxDomainSize $vRowSize $eRowSize
#run 1 /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/roadNet-PA.txt /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ 10 10 20 38 38

	#generate hash value
#	./main 3 $fileName $attrFolderName $hashFolderName

	#construct super graph and synopsis
#	./main 4 $fileName $attrFolderName $numVAttr $numEAttr $numSuperNode $synopsisSize $vRowSize $sFileName $vSynopsisFileName $eSynopsisFileName $vToSNMapFileName

	#generate Queries
	./main 5 $fileName $numQuery $attrFolderName $queryFileName

	#query algorithm
#	./main 6 $fileName $attrFolderName $hashFolderName $numEAttr $numVAttr $vRowSize $eRowSize $numQuery $useConstraint $numSuperNode $synopsisSize $sFileName $vSynopsisFileName $eSynopsisFileName $vToSNMapFileName $queryFileName

#	valgrind ./main 6 $fileName $attrFolderName $hashFolderName $numEAttr $numVAttr $vRowSize $eRowSize $numQuery $useConstraint $numSuperNode $synopsisSize $sFileName $vSynopsisFileName $eSynopsisFileName $vToSNMapFileName
#run 6 /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/roadNet-PA.txt /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/ 5 5 24 24 500 1 1000 30 /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/super-roadNet-PA.txt /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vSynopsis-roadNet-PA.txt /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/eSynopsis-roadNet-PA.txt /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/PA_RoadNetwork/vTOSNMap-roadNet-PA.txt





#0x7fff5f3fff50
#	COUNT=10000
#	while [ $COUNT -le 100000 ]; do
#	FN=$COUNT'_quick_server_test_with_pruning'
#	./qmain -query_data $QUERY_DATA -show_comment $SC -alg $alg -r $COUNT -testing $testing -client_update $CLIENT_UPDATE > $FN
#	echo $COUNT
#	let COUNT=COUNT+10000
#	done

#./main 1 /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/soc-pokec-relationships.txt /home/duncan/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/ 5 3 50 10

