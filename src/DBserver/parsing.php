<?php

    include("object.php");
    include("DBconnection.php");

    Dao DBmanager = new Dao;

    $rawdata=$_POST['rawdata']
    
    Attributes objects = new attributes(//받은거 ㄲ);
    //parsing !!!!!!!


    DBmanager.insert('default', objects);

?>