<?php
    require_once("DBconnection.php");
    require_once("Row");

    $json_data = "json"
    if(isset($_POST['data'])) {
    	$json_data = $_POST['data'];
    }else{
	     echo "no json data";
    }

    $arr_data = json_decode($json_data, true);
    $db = new DBconnection();

    $object = new Row(
      $arr_data["id"],
      $arr_data["temperature"],
      $arr_data["humidity"],
      $arr_data["date_time"],
      $arr_data["latitude"],
      $arr_data["latitude"],
      $arr_data["satellites"],
      $arr_data["speed"]
    );

    //parsing
    $count = $db->insert('data', $object);

?>
