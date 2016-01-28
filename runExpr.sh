#!/bin/bash

make main

echo start_Run_Expr_Script


	function=1
	fileName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/soc-pokec-relationships.txt'
	attrFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/'
	hashFolderName='/Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/'
	numVAttr=10
	numEAttr=10
	maxDomainSize=20
	#generate Attribute
	./main 1 $fileName $attrFolderName $numVAttr $numEAttr $maxDomainSize

	#generate hash value
#	./main 3 $fileName $attrFolderName $hashFolderName

	#query algorithm
#	./main 5 $fileName $attrFolderName $hashFolderName 10 10

#	COUNT=10000
#	while [ $COUNT -le 100000 ]; do
#	FN=$COUNT'_quick_server_test_with_pruning'
#	./qmain -query_data $QUERY_DATA -show_comment $SC -alg $alg -r $COUNT -testing $testing -client_update $CLIENT_UPDATE > $FN
#	echo $COUNT
#	let COUNT=COUNT+10000
#	done

#./main 1 /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/soc-pokec-relationships.txt /Users/duncan/Documents/Documents/PhD_Thesis_Project/ReachabilityQueryOnAttributedGraph_Data/soc-pokec/ 5 3 50 10

