<?php
class DBconnection
{
    private $servername = "localhost";
    private $dbname = "agrodb";
    private $username = "agro";
    private $password = "Tlqkf1q2w3e4r!";
    private $conn = null;

    public function __construct(){
        try{
            $this->conn = new PDO("mysql:host=$this->servername;port=3306;dbname=$this->dbname", $this->username, $this->password);
            $this->conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        }catch(PDOException $e){
            echo "Connection failed:".$e->getMessage();
        }
    }

    public function getserver(){
        return $this->servername;
    }

    // select all datas from inputed table name
    public function select($tname, &$values, $sql= "SELECT * FROM"){
        if($this->conn == null)
            return -1;
        if($sql == "SELECT * FROM")
            $sql = $sql." $tname";
        try{
            $result = $this->conn->query($sql);
            $rcount = $result->rowCount();

            if($rcount >= 1){
                $values = $result;
                return $rcount;
            }
            else
                return $rcount;
        }catch(PDOException $e){
            echo "Select $tname failed:".$e->getMessage();
        }
    }
    public function insert($tname, $objects){
        if($this->conn == null)
            return -1;
        // insert row counter
        $count = 0;

        try{
            $stmt = $this->conn->prepare("INSERT INTO data(id,temperature,date_time,longitude,latitude,satlites,speed)
            VALUES (:id, :temperature, :date_time, :longitude, :latitude, :satlites, :speed)");
            $stmt->bindParam(':id', $id);
            $stmt->bindParam(":temperature", $temperature);
            $stmt->bindParam(":date_time", $date_time);
            $stmt->bindParam(":longitude", $longitude);
            $stmt->bindParam(":latitude", $latitude);
            $stmt->bindParam(":satlites", $satlites);
            $stmt->bindParam(":speed", $speed);
            // insert
            foreach ($objects as $elem) {
                $id = $elem->id;
                $temperature = $elem->temperature;
                $date_time = $elem->date_time;
                $longitude = $elem->longitude;
                $latitude = $elem->latitude;
                $satlites = $elem->satlites;
                $speed = $elem->speed;
                $stmt->execute();
                $count++;
            }
        }catch(PDOException $e){
            echo "data table: Insert failed:".$e->getMessage();
        }

        return $count;
    }

    public function delete($tname){
        if($this->conn == null)
            return -1;
        try{
            $sql = "DELETE FROM ". $tname;
            $result = $this->conn->query($sql);
            $rcount = $result->rowCount();
            if($rcount >= 1)    return $rcount;
            else    return $rcount;
        }catch(PDOException $e){
            echo "Delete $tname failed:".$e->getMessage();
        }
    }

}
?>
