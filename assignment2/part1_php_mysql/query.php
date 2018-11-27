<?php

$db = new mysqli("localhost", "tushar", "pass", "employees");

if ($db->connect_error)
{
	die("Connection failed: " . $db->connect_error);
}

function render($result){

	$return = <<<HTML
<!DOCTYPE html>
<html>
<head>
<title>All Registration</title>
<style>
	table{
		 border-collapse: collapse;
		 border: 1px solid black;
		 width:80%;
	}
	th,td{
		border: 1px solid black;
	 	border-collapse: collapse;	
	}
</style>
</head>
<body>
	<center><h2>Employees</h2></center>
	<br /><br />
	<center><table>
	<tr>
		<th>emp_no</th>
		<th>birth_date</th> 
		<th>first_name</th> 
		<th>last_name</th> 
		<th>gender</th>
		<th>hire_date</th>
		<th>dept_no</th>
		<th>dept_name</th>
		
	</tr>
HTML;
	while($row = $result->fetch_array())
  	{
		$return .= <<<HTML
<tr>
	<td>{$row['emp_no']}</td>
	<td>{$row['birth_date']}</td> 
	<td>{$row['first_name']}</td> 
	<td>{$row['last_name']}</td> 
	<td>{$row['gender']}</td>
	<td>{$row['hire_date']}</td>
	<td>{$row['dept_no']}</td>
	<td>{$row['dept_name']}</td>
</tr>
HTML;
  	}
	
		$return .= <<<HTML
	</table></center>
	</body>
</html>
HTML;
		
	echo $return;	
	exit;
}


function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}

if(test_input($_POST["action"]) == "query1"){
	$query1=test_input($_POST["query1"]);
	$textquery1=test_input($_POST["textquery1"]);
	if($query1 == "emp_no"){
		$result = $db->query("select employees.*, dept_emp.dept_no, departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no where employees.".$query1."=".$textquery1.";"); 
	}
	else if($query1 == "last_name"){
		$result = $db->query("select employees.*, dept_emp.dept_no, departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no where employees.".$query1."=\"".$textquery1."\";"); 
	} 
	else if($query1 == "dept_name"){
		$result = $db->query("select employees.*, dept_emp.dept_no, departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no where departments.dept_name=\"".$textquery1."\";"); 
	} 
    render($result);
    $result->close();
	exit;
}

else if(test_input($_POST["action"]) == "query2"){
	$result = $db->query("select  dept_emp.dept_no, count(*) as c, departments.dept_name from dept_emp  join departments on dept_emp.dept_no=departments.dept_no group by dept_no;");
	$max=-1;
	while($row = $result->fetch_array())
  	{
  		if($row['c']>=$max){
			$max=$row['c'];
			$maxdept=$row['dept_name'];
		}
  	}
	echo "max employee dept=$maxdept with count=$max";
	exit;
}

else if(test_input($_POST["action"]) == "query3"){
	$result = $db->query("select employees.*, dept_emp.dept_no, departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no where departments.dept_name=\"Development\" order by employees.hire_date desc;
");
	render($result);
	exit;
}

else if(test_input($_POST["action"]) == "query4"){
	$result = $db->query("select sum(case when gender='m' then 1 else 0 end) as s1,sum(case when gender='f' then 1 else 0 end) as s2,departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no group by departments.dept_no;");
	
	while($row = $result->fetch_array())
  	{
		$ratio=$row['s2']*1.0000/$row['s1'];
		$dept_name=$row['dept_name'];
		echo "dept=$dept_name and gender-ratio=$ratio <br>";
	}
	exit;
}
else if(test_input($_POST["action"]) == "query5"){
	$result1 = $db->query("select avg(salaries.salary) as s, employees.gender,departments.dept_name from employees join dept_emp on employees.emp_no=dept_emp.emp_no join departments on dept_emp.dept_no=departments.dept_no join salaries on salaries.emp_no=employees.emp_no group by departments.dept_name,employees.gender;");
	
	while($rowmale = $result1->fetch_array()){
		$rowfemale = $result1->fetch_array();
		$ratio = $rowfemale['s']*1.0000/$rowmale['s'];
		$dept_name=$rowmale['dept_name'];
		echo "dept=$dept_name and gender-pay-ratio=$ratio <br>";
	}
	
	exit;
}

?>