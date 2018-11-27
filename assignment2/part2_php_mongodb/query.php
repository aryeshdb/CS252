<?php

$manager = new MongoDB\Driver\Manager("mongodb://localhost:27017");
$filter = [];




function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}



if(test_input($_POST["action"]) == "query1"){
	$options = [];
	$query = new MongoDB\Driver\Query($filter, $options);
	$rows = $manager->executeQuery('test.docs', $query); 
	$count=[];
	foreach ($rows as $row){
    	$count["$row->DISTRICT"]+=1;
	}
	$max=-1;
	foreach($count as $district=>$c){
		// echo $district." ".$c."<br>";
		if($c>$max){
			$max=$c;
			$dist=$district;
		}
	}
	echo "district with most crime reported per capita- ".$dist." with ".$max." cases";
	exit;
}

else if(test_input($_POST["action"]) == "query2"){
	$options = [
		'Status' => "Pending"
	];
	$query = new MongoDB\Driver\Query($filter, $options);
	$rows = $manager->executeQuery('test.docs', $query); 
	$count=[];
	foreach ($rows as $row){
    	$count["$row->PS"]+=1;
	}
	$max=-1;
	foreach($count as $ps=>$c){
		// echo $ps." ".$c."<br>";
		if($c>$max){
			$max=$c;
			$reqps=$ps;
		}
	}
	echo "police station which is the most inefficient in completing
investigations- ".$reqps." with ".$max." cases";
	exit;
}
else if(test_input($_POST["action"]) == "query3"){
	$options = [];
	$query = new MongoDB\Driver\Query($filter, $options);
	$rows = $manager->executeQuery('test.docs', $query); 
	$count=[];
	foreach ($rows as $row){
		foreach($row->Act_Section as $law){
			$count[$law]+=1;
		}
	}
	$max=-1;
	foreach($count as $law=>$c){
		// echo $law." ".$c."<br>";
		if($c>$max){
			$max=$c;
			$reqmaxlaw=$law;
		}
	}
	$min=$max;
	foreach($count as $law=>$c){
		if($c<$min){
			$min=$c;
			$reqminlaw=$law;
		}
	}
	echo "crime laws which are most uniquely applied in FIRs is ".$reqmaxlaw." with ".$max." cases<br>";
	echo "crime laws which are least uniquely applied in FIRs is ".$reqminlaw." with ".$min." cases";
	
	exit;
}

?>