<?php
class attributes{

    private $servername = "localhost";
    private $username = "root";
    private $password = "";
    private $dbname = "agro";
    private $conn = null;

    // Device id
    private $id;
    // Temperature
    private $temperature;
    // GPS
    private $date_time;
    private $longitude;
    private $latitude;
    private $satlites;
    private $speed;

    public function __construct(){
        try{
            $this->conn = new PDO("mysql:host=$this->servername;dbname=$this->dbname", $this->username, $this->password);
            $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        }catch(PDOException $e){
            echo "Connection failed:".$e->getMessage();
        }
    }

    public function getserver(){
        return $this->servername;
    }

    /*public function __construct($id, $temp, $lon, $lat, $sat, $speed){
        return $this;
        
    }*/
} 

?>
