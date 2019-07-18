<?php
class Row{

    // private $servername = "localhost";
    // private $username = "root";
    // private $password = "";
    // private $dbname = "agro";
    // private $conn = null;

    // Device id
    private $id;
    // Temperature
    private $temperature;
    private $humidity;
    // GPS
    private $date_time;
    private $longitude;
    private $latitude;
    private $satlites;
    private $speed;

    // public function __construct(){
    //     try{
    //         $this->conn = new PDO("mysql:host=$this->servername;dbname=$this->dbname", $this->username, $this->password);
    //         $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    //     }catch(PDOException $e){
    //         echo "Connection failed:".$e->getMessage();
    //     }
    // }



    public function __construct($id, $temp, $time, $lon, $lat, $sat, $speed){
        $this->id = $id;
        $this->temperature = $temp;
        $this->date_time = $time;
        $this->longitude = $lon;
        $this->latitude = $lat;
        $this->satlites = $sat;
        $this->speed = $speed;
    }

    // public function getserver(){
    //     return $this->servername;
    // }
}

?>
