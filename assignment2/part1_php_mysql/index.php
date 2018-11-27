
<?php
#session_start();

$db = new mysqli("localhost", "tushar", "pass", "employees");

if ($db->connect_error)
{
	die("Connection failed: " . $db->connect_error);
}

#$result = $db->query("select * from employees;")

#$result = $db->query("select employees.*, dept_emp.dept_no, departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no where employees.emp_no=206357;");

#echo $result;
/*
$result = $db->query("select * from employees;"); 
    printf("Select returned %d rows.\n", $result->num_rows);
    while($row = $result->fetch_array())
  	{
  		echo $row['emp_no'];
  		echo "<br />";
  	}
    /* free result set */


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
		Get Employee:<br />
		
		by emp_no:<input style="float:right;" type="radio" name="query1" value="emp_no" />
		<br /><br />
		
		by last name:<input style="float:right;" type="radio" name="query1" value="last_name" />
		<br /><br />
		
		by dept name: <input style="float:right;" type="radio" name="query1" value="dept_name" />
		<br /><br />
		<input style="float:left;" type="text" name="textquery1"  />
		<br /><br />
		<center><input type="submit" value="Query 1"></center>
		<br /><br /><br />
	</form>
	
	<form id="form3" action="query.php" method="post" class="register_form">
		<h1> Query2 </h1>
		<input type="hidden" name="action" value="query2">
		Get max employee dept<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>
	<form id="form3" action="query.php" method="post" class="register_form">
		<h1> Query3 </h1>
		<input type="hidden" name="action" value="query3">
		Get details ordered by tenure<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>
	<form id="form4" action="query.php" method="post" class="register_form">
		<h1> Query4 </h1>
		<input type="hidden" name="action" value="query4">
		Get gender ratio for each dept<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>
	<form id="form5" action="query.php" method="post" class="register_form">
		<h1> Query5 </h1>
		<input type="hidden" name="action" value="query5">
		Get gender pay ratio within dept<br />
		<center><input type="submit" value="GO"></center>
		<br /><br /><br />
	</form>

</body>
</html>
HTML;
	echo $return;
?>