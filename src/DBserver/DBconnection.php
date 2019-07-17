<?php
class Dao
{
    private $servername = "localhost";
    private $username = "root";
    private $password = "";
    private $dbname = "agro";
    private $conn = null;

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

        switch($tname){
            case 'MovieDetail':
                // prepare and bind to insert moviedetail
                try{
                    $stmt = $this->conn->prepare("INSERT INTO MovieDetail(mid, title,
                    release_date, isAdult, popularity, vote_average, overview, imgsrc)
                    VALUES (:mid, :title, :release_date, :isAdult, :popularity, :vote_average,
                    :overview, :imgsrc)");
                    $stmt->bindParam(':mid', $mid);
                    $stmt->bindParam(":title", $title);
                    $stmt->bindParam(":release_date", $release_date);
                    $stmt->bindParam(":isAdult", $isAdult);
                    $stmt->bindParam(":popularity", $popularity);
                    $stmt->bindParam(":vote_average", $vote_average);
                    $stmt->bindParam(":overview", $overview);
                    $stmt->bindParam(":imgsrc", $imgsrc);

                    // insert
                    foreach ($objects as $elem) {
                        $mid = $elem->mid;
                        $title = $elem->title;
                        $release_date = $elem->release_date;
                        $isAdult = $elem->isAdult;                    
                        $popularity = $elem->popularity;
                        $vote_average = $elem->vote_average;
                        $overview = $elem->overview;
                        $imgsrc = $elem->imgsrc;

                        $stmt->execute();
                        $count++;
                    }
                }catch(PDOException $e){
                    echo "MovieDetail: Insert failed:".$e->getMessage();
                }
                break;

            case 'Schedule':
                // prepare and bind to insert schedule
                try{
                    $stmt = $this->conn->prepare("INSERT INTO Schedule(mid, time, venue, seatavailable, vsize)
                    VALUES (:mid, :time, :venue, :seatavailable, :vsize)");
                    $stmt->bindParam(':mid', $mid);
                    $stmt->bindParam(":time", $time);
                    $stmt->bindParam(":venue", $venue);
                    $stmt->bindParam(":seatavailable", $seatavailable);
                    $stmt->bindParam(":vsize", $seatavailable);

                    foreach ($objects as $elem) {
                        $mid = $elem->mid;
                        $time = $elem->time->format('Y-m-d H:i:s');
                        $venue = $elem->venue;
                        $seatavailable = $elem->seatavailable;
                    
                        $stmt->execute();
                        $count++;
                    }
                }catch(PDOException $e){
                    echo "Schedule Insert failed:".$e->getMessage();
                }
                break;
            case 'Seats':
                // prepare and bind to insert seats
                try{
                    $stmt = $this->conn->prepare("INSERT INTO seats(sid, row, col, isavailable)
                    VALUES (:sid, :row, :col, :isavailable)");
                    $stmt->bindParam(':sid', $sid);
                    $stmt->bindParam(":row", $row);
                    $stmt->bindParam(":col", $col);
                    $stmt->bindParam(":isavailable", $isavailable);

                    foreach ($objects as $elem) {
                        $sid = $elem->sid;
                        $row = $elem->row;
                        $col = $elem->col;
                        $isavailable = $elem->isavailable;     

                        $stmt->execute();
                        $count++;
                    }
                }catch(PDOException $e){
                    echo "Seats: Insert failed:".$e->getMessage();
                }
                break;
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