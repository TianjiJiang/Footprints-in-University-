USE hospital;
-- CREATE VIEW Stu_fin AS SELECT Sno,Sname,mom_unpay,mon_payed,afr FROM Stu;
-- CREATE VIEW Stu_info AS SELECT Sno,Sname,Age,collage,indent,MT FROM Stu;

-- create user 'reg_admin'@'localhost','pri_maker'@'localhost','Dr'@'localhost','fin_staff'@'localhost';

-- SET PASSWORD FOR "reg_admin"@"localhost" =  PASSWORD("123456");
-- SET PASSWORD FOR "pri_maker"@"localhost" =  PASSWORD("123456");
-- SET PASSWORD FOR "Dr"@"localhost" =  PASSWORD("123456");
-- SET PASSWORD FOR "fin_staff"@"localhost" =  PASSWORD("123456");

-- GRANT all ON hospital.Stu TO "reg_admin"@"localhost";
-- GRANT SELECT ON hospital.Me_Re TO "reg_admin"@"localhost";
-- GRANT INSERT ON hospital.Me_Re TO "reg_admin"@"localhost";
-- REVOKE ALL ON Stu FROM "reg_admin"@"localhost";
-- GRANT ALL ON Stu_info TO "reg_admin"@"localhost";
-- GRANT UPDATE ON Stu to "reg_admin"@"localhost";

-- GRANT ALL ON MaT to "pri_maker"@"localhost" ;
-- GRANT ALTER ON Pre TO "pri_maker"@"localhost";
-- Grant SELECT ON Me_Re TO "pri_maker"@"localhost";
-- Grant SELECT ON Pre TO "pri_maker"@"localhost";

-- grant all on Pre to "Dr"@"localhost";
-- GRANT SELECT,update on Me_Re to "Dr"@"localhost";
-- GRANT SELECT on MaT to "Dr"@"localhost";

-- GRANT SELECT ON MaT to "fin_staff"@"localhost";
-- GRANT SELECT on Stu to "fin_staff"@"localhost";
-- REVOKE alter on Stu from "fin_staff"@"localhost";
-- GRANT alter on Stu_fin to "fin_staff"@"localhost";



-- UPDATE Stu 
-- SET Sname = '蒋天济',Age = 19,collage = '自动化院',indent = '本科生',MT = '城镇居民'
-- WHERE Sno = '0101170216';
-- ALTER TABLE Me_Re MODIFY COLUMN M_time DATETIME;

GRANT update on Stu to "pri_maker"@"localhost";
