<?php

    include("object.php");
    include("DBconnection.php");

    Dao DBmanager = new Dao;

    $rawdata=$_POST['rawdata']
    
    Attributes objects = new attributes($rawdata);
    
    //parsing

    DBmanager.insert('default', objects);

?>
