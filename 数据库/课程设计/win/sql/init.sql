USE hospital;
-- /*学生*/
-- create table Stu
-- (
--     Sno CHAR(10) PRIMARY KEY,
--     Sname CHAR(10) not NULL,
--     Age SMALLINT not NULL,
--     indent char(5),/*身份*/
--     MT char(10),/*医保类型*/
--     mon_unpay FLOAT,/*待付款*/
--     mon_payed FLOAT,/*已付金额*/
--     afr FLOAT /*报销*/
-- )character set = utf8;


-- /*药物及治疗表*/
-- CREATE table MaT
-- (
--     Mno char(20) PRIMARY KEY,/*药品M或治疗T的编号*/
--     Mname char(20) UNIQUE not null,
--     Pri FLOAT NOT NULL 

-- )character set = utf8;




-- /*诊疗记录*/
-- create table Me_Re 
-- (
--     Sno CHAR(10) not null ,
--     Pno CHAR(10),/*处方号随机产生*/
--     M_time DATE,
--     PRIMARY KEY (Pno),
--     FOREIGN KEY (Sno) REFERENCES Stu(Sno)
-- )character set = utf8;

-- /*处方记录*/
-- create table Pre
-- (
--     Pno CHAR(10),
--     Mno CHAR(10),
--     num SMALLINT,
--     mom_sum FLOAT,
--     payornot BOOLEAN,
--     PRIMARY key (Pno,Mno),
--     FOREIGN key (Mno) REFERENCES MaT(Mno),
--     FOREIGN key (Pno) REFERENCES Me_Re(Pno)
-- )character set = utf8;

-- ALTER TABLE Me_Re 
--     ADD COLUMN sym char(200),
--     ADD COLUMN res char(200);
--  ALTER TABLE Stu 
--      ADD COLUMN collage char(20);