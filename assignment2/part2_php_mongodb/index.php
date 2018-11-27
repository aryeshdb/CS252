<?php

	$return = <<<HTML
	<!DOCTYPE html>
<html>
<head>
<title>Register</title>
<style>
	.register_form { 
		margin: 0 auto; 
		width:280px;
	}

</style>
</head>


<body>

	
	<form id="form1" action="query.php" method="post" class="register_form">
		<h1> Query1 </h1>
		<input type="hidden" name="action" value="query1">
		Which district has the most crime reported per capita<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>
	<form id="form2" action="query.php" method="post" class="register_form">
		<h1> Query2 </h1>
		<input type="hidden" name="action" value="query2">
		Which police station is the most inefficient in completing
investigations<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>
	<form id="form3" action="query.php" method="post" class="register_form">
		<h1> Query3 </h1>
		<input type="hidden" name="action" value="query3">
		Which crime laws are most and least uniquely applied in FIRs<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>

</body>
</html>
HTML;
	echo $return;

?>