<?php
    require_once("DBconnection.php");
    // require_once("Row");
    require_once("RowTest.php");

    $value1 = 1.0;
    $value2 = 2.0;
    
    if(isset($_POST['test1'])) {
    	$value1 = $_POST['test1'];
    }else{
	echo 'no value1';
    }
    if(isset($_POST['test2'])){
    	$value2 = $_POST['test2'];
    }else{
	echo 'no value2';
    }

    $db = new DBconnection();
    // $row = new Row();
    $object = new RowTest($value1, $value2);

    //parsing
    $count = $db->insert('data', $object);

?>
