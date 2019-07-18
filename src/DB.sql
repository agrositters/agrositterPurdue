use agrodb;
CREATE TABLE data(
    id VARCHAR(100) REFERENCES muser(id),
    temperature FLOAT,
    humidity FLOAT,
    date_time DATETIME,
    longitude VARCHAR(100),
    latitude VARCHAR(100),
    satlites INT,
    speed FLOAT,

    PRIMARY KEY(id, date_time)
);


// to test
use testdb;
CREATE TABLE data(
    temperature Float,
    humidity Float
);
