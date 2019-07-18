<?php
    require_once("DBconnection.php");
    // require_once("Row");
    require_once("RowTest.php");

    $value1=$_POST['test1'];
    $value2=$_POST['test2'];

    $db = new DBconnection();
    // $row = new Row();
    $object = new RowTest($value1, $value2);
    
    //parsing
    DBmanager.insert('data', $object);
?>
